import sqlite3

conn = sqlite3.connect('balances.db')

conn.execute("""CREATE TABLE IF NOT EXISTS balances (
			id INTEGER PRIMARY KEY AUTOINCREMENT,
			username VARCHAR(50),
			balance INTEGER);""")
conn.close();


