#!/usr/bin/python3
import sqlite3, argparse



def load(conn, user: str):
	row = conn.execute("SELECT balance FROM balances WHERE username LIKE '"+user+"';").fetchone()
	if not row:
		balance = 0
	else:
		balance = row[0]
	with open("surelyJsonFromServerAndNotLocallyStoredFile.exe.jpeg.png.piesek", "w", encoding="utf-8") as f:
		f.write(str(balance))

def save(conn, user: str, balance: int):
	rows = conn.execute("SELECT * FROM balances WHERE username LIKE '"+user+"';")
	size = 0
	for row in rows:
		size += 1
	if size > 0:
		conn.execute("UPDATE balances SET balance = "+str(balance)+" WHERE username LIKE '"+user+"';")
	else:
		conn.execute("INSERT INTO balances (username, balance) VALUES ('"+user+"', "+str(balance)+");")
	conn.commit()

def pay(conn, user_from: str, user_to: str, amount: int):
	row_from = conn.execute("SELECT balance FROM balances WHERE username LIKE '"+user_from+"';").fetchone()
	if not row_from:
		return
	row_to = conn.execute("SELECT balance FROM balances WHERE username LIKE '"+user_to+"';").fetchone()
	if not row_to:
		conn.execute("INSERT INTO balances (username, balance) VALUES ('"+user_to+"', 0);")
	conn.execute("UPDATE balances SET balance = balance - "+str(amount)+" WHERE username LIKE '"+user_from+"';")
	conn.execute("UPDATE balances SET balance = balance + "+str(amount)+" WHERE username LIKE '"+user_to+"';")
	conn.commit()

def main():
	conn = sqlite3.connect('balances.db')
	parser = argparse.ArgumentParser(prog="persist")
	parser.add_argument('-u', '--user', type=str)
	parser.add_argument('-b', '--balance', type=int)
	parser.add_argument('-t', '--to', type=str)
	args = parser.parse_args().__dict__
	
	user = args['user']
	balance = args['balance']
	to = args['to']
	
	if not user:
		return
	if not to:
		if not balance:
			load(conn, user)
		else:
			save(conn, user, balance)
	else:
		pay(conn, user, to, balance)

	conn.close()
	
	
