import random
from flask import Flask, render_template, request

app = Flask(__name__)

@app.route("/")
def index():
    rNumber = random.randint(1, 10)
    number = random.randint(0, 1)
    return render_template("index.html", name="Jinook", rNumber=rNumber, number=number)
    
@app.route("/goodbye")
def bye():
    return "Goodbye!"
    
@app.route("/hello")
def hello():
    name = request.args.get("name")
    if not name:
        return render_template("failure.html")
    return render_template("hello.html", name=name)