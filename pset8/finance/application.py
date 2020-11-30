import os

from cs50 import SQL
from flask import Flask, flash, flash, jsonify, redirect, render_template, request, session, url_for
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime
import pytz

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    rows = db.execute("SELECT * FROM history WHERE u_id=:u_id ORDER BY symbol", u_id=session.get("user_id"))
    sharesValue = 0
    symbols = []
    shareKinds = []
    for row in rows:
        symbol = row["symbol"]
        price = lookup(symbol)['price']
        sharesValue = sharesValue + round((price * row["shares"]), 2)
        if (symbol in symbols):
            for item in shareKinds:
                if item["symbol"] == symbol:
                    item["shares"] = item["shares"] + row["shares"]
                    if item["shares"] == 0:
                        symbols.remove(symbol)
                        shareKinds = [i for i in shareKinds if not (i['symbol'] == symbol)]
        else:
            symbols.append(symbol)
            shareKinds.append({ "symbol": symbol, "name": row["name"], "shares": row["shares"], "price": price })

    row = db.execute("SELECT * FROM users WHERE id=:id", id=session.get("user_id"))
    cash = row[0]["cash"]

    return render_template("index.html", bottom="YOU ARE LOGGED IN!", top=200, shareKinds=shareKinds, cash=cash, sharesValue=sharesValue)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    method = request.method

    if method == "GET":
        return render_template("buy.html")

    company = request.form.get("symbol")
    if company == "":
        return render_template("buy.html", message="Enter a company symbol.")
    if not lookup(company):
        return render_template("buy.html", method="GET", message='Company symbol [ {company} ] not found...'.format(company=company.upper()))
    shares = request.form.get("shares")
    if not shares or int(shares) < 1:
        return render_template("buy.html", message="Buy some shares.")

    row = db.execute("SELECT * FROM users WHERE id=:id", id=session.get("user_id"))
    cash = row[0]["cash"]

    name = lookup(company)['name']
    price = lookup(company)['price']
    symbol = lookup(company)['symbol']
    total = round(price*int(shares), 2)
    if cash < total:
        return render_template("buy.html", message="You have not enough cash.")

    # datetime object containing current date and time
    tz_NY = pytz.timezone('America/New_York')
    now = datetime.now(tz_NY)
    dt_string = now.strftime("%Y-%m-%d %H:%M:%S") # YYYY-mm-dd H:M:S

    cashBalance = cash - total
    db.execute("UPDATE users SET cash=:cash WHERE id=:id", id=session.get("user_id"), cash=cashBalance)
    db.execute("INSERT INTO history (shares, price, transacted, u_id, symbol, name) VALUES (:shares, :price, :transacted, :u_id, :symbol, :name)", shares=int(shares), price=price, transacted=dt_string, u_id=session.get("user_id"), symbol=symbol, name=name)

    rows = db.execute("SELECT * FROM history WHERE u_id=:u_id", u_id=session.get("user_id"))

    return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    rows = db.execute("SELECT * FROM history WHERE u_id=:u_id", u_id=session.get("user_id"))
    return render_template("history.html", rows=rows)


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
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
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
    method = request.method
    company = request.form.get("symbol")
    if company == "":
        return render_template("buy.html", message="Enter a company symbol.")

    # User reached route via GET (as by submitting a form via GET)
    if method == "GET":
        return render_template("quote.html", method=method)

    # User reached route via POST (as by submitting a form via POST)
    if not lookup(company):
        return render_template("quote.html", method="GET", message='Company symbol [ {company} ] not found...'.format(company=company.upper()))
    name = lookup(company)['name']
    price = lookup(company)['price']
    symbol = lookup(company)['symbol']
    return render_template("quote.html", method=method, symbol=symbol, name=name, price=price)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Forget any user_id
    session.clear()

    # User reached route via GET (as by clicking a link or via redirect)
    if request.method == "GET":
        return render_template("/register.html")

    # User reached route via POST (as by submitting a form via POST)
    username = request.form.get("username")
    password = request.form.get("password")
    again = request.form.get("again")
    if not username or not password or not again:
        return apology("Please fill in all the boxes!")
    if password != again:
        return apology("Check if you entered the same passwords...")
    hash = generate_password_hash(password)
    db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)", username=username, hash=hash)
    return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    method = request.method

    if method == "POST":

        # INSERT INTO history table
        symbol = request.form.get("symbol")
        if symbol == "Choose Your Stock":
            flash("Choose your stock first.")
            return redirect("sell")
        name = lookup(symbol)['name']
        price = lookup(symbol)['price']
        share = request.form.get("shares")
        if not share or int(share) < 1:
            flash("Sell some shares.")
            return redirect("sell")
        shares = int(request.form.get("shares")) * -1
        ownedShares = 0;

        symbolRows = db.execute("SELECT * FROM history WHERE (u_id=:u_id) AND (symbol=:symbol)", u_id=session.get("user_id"), symbol=symbol)
        for symbolRow in symbolRows:
            ownedShares = ownedShares + symbolRow["shares"]

        if ownedShares < shares*-1:
            flash("Not Enough Shares")
            return redirect("sell")
        total = round((shares * price), 2)

        # datetime object containing current date and time
        tz_NY = pytz.timezone('America/New_York')
        now = datetime.now(tz_NY)
        dt_string = now.strftime("%Y-%m-%d %H:%M:%S") # YYYY-mm-dd H:M:S

        db.execute("INSERT INTO history (shares, price, transacted, u_id, symbol, name) VALUES (:shares, :price, :transacted, :u_id, :symbol, :name)", shares=shares, price=price, transacted=dt_string, u_id=session.get("user_id"), symbol=symbol, name=name)

        # UPDATE user cash
        row = db.execute("SELECT * FROM users WHERE id=:id", id=session.get("user_id"))
        cash = row[0]["cash"]
        cashBalance = cash - total
        db.execute("UPDATE users SET cash=:cash WHERE id=:id", id=session.get("user_id"), cash=cashBalance)
            # rows = db.execute("SELECT * FROM history WHERE u_id=:u_id", u_id=session.get("user_id"))

        return render_template("sell.html", method=method, shares=shares*-1, name=name, symbol=symbol, total=total*-1, dt_string=dt_string)

    rows = db.execute("SELECT * FROM history WHERE (u_id=:u_id) ORDER BY symbol", u_id=session.get("user_id"))

    shares = request.form.get("shares")
    sharesValue = 0
    symbols = []
    shareKinds = []
    for row in rows:
        symbol = row["symbol"]
        price = lookup(symbol)['price']
        sharesValue = sharesValue + round((price * row["shares"]), 2)
        if (symbol in symbols):
            for item in shareKinds:
                if item["symbol"] == symbol:
                    item["shares"] = item["shares"] + row["shares"]
                    if item["shares"] == 0:
                        symbols.remove(symbol)
                        shareKinds = [i for i in shareKinds if not (i['symbol'] == symbol)]
        else:
            symbols.append(symbol)
            shareKinds.append({ "symbol": symbol, "name": row["name"], "shares": row["shares"], "price": price })

    row = db.execute("SELECT * FROM users WHERE id=:id", id=session.get("user_id"))
    cash = row[0]["cash"]
    return render_template("sell.html", method=method, shareKinds=shareKinds, message="message")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
