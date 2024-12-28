import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    stocks = db.execute(
        "SELECT u.cash, t.symbol, SUM(t.shares) AS shares FROM users u LEFT JOIN transactions t ON u.id = t.user_id WHERE u.id = ? GROUP BY t.symbol", session['user_id'])
    cash = stocks[0]['cash']
    shareTotalPrice = 0
    if stocks[0]['symbol'] == None:
        stocks = []
    for stock in stocks:
        price = lookup(stock['symbol'])['price']
        total = price * stock['shares']
        stock['price'] = usd(price)
        stock['total'] = usd(total)
        shareTotalPrice += total
    return render_template("index.html", stocks=stocks, cash=usd(cash), total=usd(shareTotalPrice+cash))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == 'POST':
        symbol = request.form.get('symbol')
        if not symbol:
            return apology('must provide symbol', 400)
        res = lookup(symbol)
        if res == None:
            return apology(f'Symbol {symbol} does not exist!')
        shares = request.form.get('shares')
        if not shares:
            return apology('must provide shares', 400)
        try:
            shares = int(shares)
        except ValueError:
            return apology("must provide integer value for shares", 400)
        if shares < 0:
            return apology("must provide positive integer value for shares", 400)

        user = db.execute("SELECT * FROM users WHERE id = ?", session['user_id'])

        if res['price'] * shares > user[0]['cash']:
            return apology("Insufficient balance", 400)

        db.execute("UPDATE users SET cash = ? WHERE id = ?",
                   user[0]['cash'] - res['price'] * shares, session['user_id'])
        db.execute("INSERT INTO transactions (user_id, name, shares, price, type, symbol) VALUES(?,?,?,?,?,?)",
                   session['user_id'], res['name'], shares, res['price'], 'buy', res['symbol'])

        return redirect("/")

    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions = db.execute(
        "SELECT t.symbol, t.time, t.shares, t.price, t.type FROM transactions t WHERE t.user_id = ?", session['user_id'])
    return render_template("history.html", transactions=transactions, usd_fun=usd)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == 'POST':
        symbol = request.form.get('symbol')
        if not symbol:
            return apology('must provide symbol', 400)
        res = lookup(symbol)
        if res == None:
            return apology(f'Symbol {symbol} does not exist!', 400)
        res['price'] = usd(res['price'])
        return render_template('quoted.html', res=res)
    return render_template('quote.html')


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == 'POST':
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        if not username:
            return apology("must provide username", 400)
        if not password:
            return apology("must provide password", 400)
        if not confirmation:
            return apology("must provide confirmation", 400)
        if password != confirmation:
            return apology("Password confirmation does not match", 400)
        hash = generate_password_hash(password, salt_length=16)
        try:
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash)
        except ValueError:
            return apology("The username is already taken. Please choose another one.", 400)
        return redirect("/login")
    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    stocks = db.execute(
        "SELECT u.cash, t.name, t.symbol, SUM(t.shares) AS shares FROM users u LEFT JOIN transactions t ON u.id = t.user_id WHERE u.id = ? GROUP BY t.symbol", session['user_id'])
    if request.method == 'POST':
        symbol = request.form.get('symbol')
        shares = request.form.get('shares')
        if not symbol or not any(stock['symbol'] == symbol for stock in stocks):
            return apology("must provide own share", 400)
        if not shares:
            return apology('must provide shares', 400)
        try:
            shares = int(shares)
        except ValueError:
            return apology("must provide integer value for shares", 400)
        if shares < 0:
            return apology("must provide positive integer value for shares", 400)

        if any(stock['symbol'] == symbol and stock['shares'] < shares for stock in stocks):
            return apology("Insufficient shares", 400)

        res = lookup(symbol)
        currentPrice = res['price']

        db.execute("UPDATE users SET cash = ? WHERE id = ?",
                   stocks[0]['cash'] + currentPrice * shares, session['user_id'])
        db.execute("INSERT INTO transactions (user_id, name, shares, price, type, symbol) VALUES(?,?,?,?,?,?)",
                   session['user_id'], res['name'], -shares, currentPrice, 'sell', res['symbol'])

        return redirect("/")
    return render_template("sell.html", stocks=stocks)
