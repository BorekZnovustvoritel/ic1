#!/usr/bin/python3
import re, os

users = []

def loadUsers() -> None:
	lines = None
	with open("stash", "r", encoding="utf-8") as file:
		lines = file.readlines()
	for line in lines:
		if not re.match(r"^\w+:\w+;\d$", line):
			continue
		username, pass_and_role = line.split(":")
		password, role = pass_and_role.split(";")
		role = int(role.replace("\n", ""))
		users.append({"username": username, "password": password, "isAdmin": role})
	return users

def editUser(username: str) -> None:
	os.system("clear")
	index = 0
	user = None
	for u in users:
		if u["username"] == username:
			user = u
			break
		index += 1
	if not user:
		input("User not found! Press Enter to continue.")
		os.system("clear")
		return
	s = "Current username: {u}\nNew username: ".format(u=user["username"])
	username = input(s)
	if username != "":
		users[index]["username"] = username
	s = "Current password: {u}\nNew password: ".format(u=user['password'])
	password = input(s)
	if password != "":
		users[index]["password"] = password
	s = "User currently is not an admin. Input '1' to make him an admin: " if user["isAdmin"] != 1 else "User currently is an admin. Input '1' to make him stay admin: "
	role = input(s)
	if role != "1":
		users[index]["isAdmin"] = 0
	else:
		users[index]["isAdmin"] = 1
	os.system("clear")

def save() -> None:	
	lines = ["{u}:{p};{r}\n".format(u=user["username"], p=user["password"], r=user["isAdmin"]) for user in users]
	lines.append("\n")
	with open("stash", "w", encoding="utf-8") as f:
		f.writelines(lines)

def main():
	os.system("clear")
	loadUsers()
	while True:
		print("Currently available users:")
		for u in users:
			s = u["username"]
			if u["isAdmin"] == 1:
				s += ", ADMIN"
			print(s)
		i = input("Type name to edit or 'exit' to exit. ")
		if i == "exit":
			break
		editUser(i)
	save()
	
	
	
