from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

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


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    return apology("TODO")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Check symbol is valid
        if not request.form.get("symbol"):
            return apology("must provide stock symbol", 403)

        # Check number of shares is valid
        elif not request.form.get("nshares"):
            return apology("must provide number of shares", 403)

        elif float(request.form.get("nshares")) < 0 or not float(request.form.get("nshares")).is_integer():
            return apology("must provide valid input for shares", 403)

        # Lookup stock and number of shares
        stock = lookup(request.form.get("symbol"))
        nshares = int(request.form.get("nshares"))

        if not stock:
            return apology("stock not valid", 403)

        # Retrieve user cash amount
        rows = db.execute("SELECT * FROM users WHERE id = :id", id = session["user_id"])
        cash = rows[0]['cash']

        # Ensure user has sufficient cash
        if cash >= (stock["price"] * nshares):

            # Add stock purchase into portfolio
            key = db.execute("INSERT INTO portfolio ('id', 'stock','price','nshares') VALUES(:id, :stock, :price, :nshares)",
            id = session["user_id"], stock = stock['symbol'], price = stock['price'], nshares = nshares)

            #Deduct cash from users account
            check = db.execute("UPDATE users SET cash = :ncash WHERE id = :id", ncash = cash - (stock["price"] * nshares),
            id = session["user_id"])

            return render_template("index.html")

        else:
            return apology("cash amount insufficient", 403)

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


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

    # User reached route via POST
    if request.method == "POST":

        # Check symbol is valid
        if not request.form.get("symbol"):
            return apology("must provide stock symbol", 403)

        stock = lookup(request.form.get("symbol"))

        return render_template("quoted.html", stock = stock, price = usd(stock['price']))

    # User reached route via GET
    else:
        return render_template("quote.html")




@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Ensure confirmation password was submitted
        elif not request.form.get("confirmation"):
            return apology("must provide confirmation", 403)

        if request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords must match", 403)

        # Save down username and hashed password
        username = request.form.get("username")
        hash = generate_password_hash(request.form.get("password"))

        # Query database for username
        key = db.execute("INSERT INTO users ('username','hash') VALUES(:username, :hash)",
        username = username, hash = hash)

        # Ensure username is unique
        if not key:
            return apology("username already exists", 403)

        # Remember which user has logged in
        session["user_id"] = key

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    return apology("TODO")


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)