import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime
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
    db.execute('''CREATE TABLE IF NOT EXISTS history (Id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, user_id TEXT NOT NULL,Name TEXT NOT NULL,Symbol TEXT NOT NULL,Shares INTEGER NOT NULL, Price REAL ,Transacted TEXT NOT NULL);''')
    rows=db.execute("select Symbol,Name,sum(Shares) as Shares,Price,(Shares*Price) as TOTAL from history where user_id=:user_id group by Symbol;",user_id=session["user_id"])
    cash= float(db.execute("select cash from users where id=:id", id = session["user_id"])[0]["cash"])
    sharesPrices=0
    for row in rows:
        row["Price"]=round(lookup(row["Symbol"])["price"],2)
        row["TOTAL"]=row["Price"]*row["Shares"]
        sharesPrices=sharesPrices+row["TOTAL"]
        row["Price"]=usd(row["Price"])
        row["TOTAL"]=usd(row["TOTAL"])
    TOTAL=cash+sharesPrices

    return render_template("portfolio.html",rows=rows,TOTAL=usd(round(TOTAL,2)),CASH=usd(round(cash,2)))
    # return render_template("portfolio.html",rows=rows,TOTAL=usd(round(float(TOTAL,2))),CASH=usd(round(float(CASH,2))))

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method==("POST"):
        if not request.form.get("symbol"):
            return apology(" missing symbol", 400)
        if not lookup(request.form.get("symbol")):
            return apology("missing symbol", 400)
        if not request.form.get("shares"):
            return apology(" missing shares", 400)
        try:
            shares = int(request.form.get("shares"))
        except ValueError:
            return apology("invalid shares", 400)

        cash= float(db.execute("select cash from users where id=:id", id = session["user_id"])[0]["cash"])
        shares= float(request.form.get("shares"))
        current_price=lookup(request.form.get("symbol"))["price"]
        transaction_cost = shares*current_price
        if cash<transaction_cost:
            return apology("can't afford", 400)
        else:
            now = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
            db.execute('''CREATE TABLE IF NOT EXISTS history (Id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, user_id TEXT NOT NULL,Name TEXT NOT NULL,Symbol TEXT NOT NULL,Shares INTEGER NOT NULL, Price REAL ,Transacted TEXT NOT NULL);''')
            db.execute('''INSERT INTO  history (user_id,Name,Symbol,Shares, Price,Transacted) VALUES (:user_id,:Name,:Symbol, :Shares, :Price,:Transacted)''',user_id = session["user_id"],Name = lookup(request.form.get("symbol"))["name"],Symbol = request.form.get("symbol"),Shares = shares,Price = current_price,Transacted = now)
            db.execute(''' UPDATE users set cash=:cash where id=:id''', cash= cash-transaction_cost, id=session["user_id"])
            # Redirect user to home page
            flash("Bought!")
            return redirect("/")
    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    rows=db.execute("select Symbol, Shares, Price, Transacted from history where user_id=:user_id ;",user_id=session["user_id"])

    for row in rows:
        row["Price"]=usd(row["Price"])

    return render_template("history.html", rows=rows )
















@app.route("/account", methods=["GET", "POST"])
@login_required
def account():
    """Show account settings"""
        # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure password was submitted
        if not request.form.get("password"):
            return apology("must provide password", 403)
        # Query database for password
        rows = db.execute("SELECT hash FROM users WHERE id = :id", id=session["user_id"])
        # Ensure password is correct
        if not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid password", 403)
        elif not request.form.get("newPassword"):
            return apology("must provide new password", 403)
        elif not request.form.get("newPassword")==request.form.get("confirmation"):
            return apology("new paswords should match", 403)
        db.execute("UPDATE users set hash=:hash WHERE id = :id", id=session["user_id"], hash=generate_password_hash(request.form.get("newPassword")))
        flash("Your Password has changed successfully!")
        return redirect("/")
    return render_template("account.html")
















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
        flash('You were successfully logged in')
        return redirect("/")
    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")

@app.route("/logout")
def logout():
    """Log user out"""
    # Forget any user_id
    session.clear()
    flash('You were successfully logged out!')
    # Redirect user to login form
    return redirect("/")

@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method == "POST":
        if lookup(request.form.get("symbol")):
            return render_template("quoted.html",   symbol=lookup(request.form.get("symbol"))["symbol"],
                                                    name=lookup(request.form.get("symbol"))["name"],
                                                    price= usd(lookup(request.form.get("symbol"))["price"]))
        return apology("missing symbol", 400)
    return render_template("quote.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)
        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))
        if len(rows) == 1:
            return apology("username already exists", 403)
        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)
        elif not request.form.get("password")==request.form.get("confirmation"):
            return apology("paswords should match", 403)
        db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)", username=request.form.get("username"), hash=generate_password_hash(request.form.get("password")))
        db.execute('''CREATE TABLE IF NOT EXISTS history (Id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, user_id TEXT NOT NULL,Name TEXT NOT NULL,Symbol TEXT NOT NULL,Shares INTEGER NOT NULL, Price REAL ,Transacted TEXT NOT NULL);''')
        flash("You were successfully registered")
        # Redirect user to home page
        return redirect("/")
    return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    row=db.execute("select Symbol,sum(Shares) from history where user_id =:user_id  group by Symbol having sum(Shares)>0 ",user_id=session["user_id"])
    symbols=[]

    for i in row:
        symbols.append(i["Symbol"])

    if request.method==("POST"):
        if not request.form.get("symbol"):
            return apology(" missing symbol", 400)
        if not lookup(request.form.get("symbol")):
            return apology("missing symbol", 400)
        if not request.form.get("shares"):
            return apology(" missing shares", 400)
        ownedshare=db.execute("select sum(Shares) from history where user_id=:user_id and Symbol = :symbol",user_id=session["user_id"],symbol =request.form.get("symbol"))[0]["sum(Shares)"]
        toBeSoldShares= int(request.form.get("shares"))
        if toBeSoldShares>ownedshare:
             return apology("too many shares", 400)
        else:
            current_price=lookup(request.form.get("symbol"))["price"]
            transactionRevenue = round(toBeSoldShares*current_price,2)
            cash= round(float(db.execute("select cash from users where id=:id", id = session["user_id"])[0]["cash"]),2)
            now = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
            db.execute('''INSERT INTO  history (user_id,Name,Symbol,Shares, Price,Transacted) VALUES (:user_id,:Name,:Symbol, :Shares, :Price,:Transacted)''',user_id = session["user_id"],Name = lookup(request.form.get("symbol"))["name"],Symbol = request.form.get("symbol"),Shares = -toBeSoldShares,Price = current_price,Transacted = now)
            db.execute(''' UPDATE users set cash=:cash where id=:id''', cash= cash+transactionRevenue, id=session["user_id"])
        flash("Sold!")
        # Redirect user to home page
        return redirect("/")
    return render_template("sell.html",symbols=symbols)



def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)

# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
