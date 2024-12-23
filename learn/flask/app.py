from flask import Flask, render_template, request

app = Flask(__name__)

@app.route('/test')
def index():
    return render_template("index.html")


@app.route('/greet')
def greet():
    # if "name" in request.args:
    #     name = request.args["name"]
    # else:
    #     name = "world"
    name = request.args.get("name", "world") # 1st parameter is for key and 2nd parameter is for default value
    return render_template("greet.html", name=name)


@app.route('/', methods=['GET', 'POST'])
def test():
    if request.method == 'POST':
        name = request.form.get('name')
        return render_template('greet.html', name=name)
    return render_template('index.html')
