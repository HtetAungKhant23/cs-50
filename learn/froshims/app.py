from flask import Flask, render_template, request

app = Flask(__name__)

SPORTS = ['Football', 'Basketball', 'Table Tennis']

@app.route('/')
def index():
    return render_template('index.html', sports=SPORTS)

@app.route('/register', methods=['POST'])
def register():
    if not request.form.get('name') or request.form.get('sport') not in SPORTS:
        return render_template("failuer.html")
    name = request.form.get('name')
    sport = request.form.get('sport')
    return render_template('success.html', name=name, sport=sport)
