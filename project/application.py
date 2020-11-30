from flask import Flask, redirect, render_template, request
import sqlite3

app = Flask(__name__)


# Route for main page, viewing index.html
@app.route("/")
def index():
    return render_template("index.html", page="")


# Route for todos page, viewing todos.html
@app.route("/todos")
def todos():
    return render_template("todos.html", page="todos")
    
    
# Route for converters page, viewing converters.html
@app.route("/converters")
def converters():
    return render_template("converters.html", page="converters")
    

# Route for etc page, viewing etc.html
@app.route("/etc")
def etc():
    return render_template("etc.html", page="etc")
