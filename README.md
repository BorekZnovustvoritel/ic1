# Projekt do předmětu IC1

## Prerekvizity:

- Linux Debian
- GCC (C compiler)
- Git (`sudo apt install git`)
- Python3 (`sudo apt install python3`)
- Pip (`sudo apt install python3-pip`)
- Pexpect (`python3 -m pip install pexpect`)
- SetupTools (`python3 -m pip install setuptools`)
- GDB (GNU Debugger)
- Zrušení ASLR ochrany (`echo 0 | sudo tee /proc/sys/kernel/randomize_va_space`, `sudo nano /etc/sysctl.d/01-disable-aslr.conf` a napsat `kernel.randomize_va_space = 0`)

## Jak to zkompilovat?

- `sudo gcc -ggdb -m32 -fno-stack-protector ./wallet.c -o wallet.o; sudo chmod u+s wallet.o`
- `sudo python3 -m pip install editUsers/`
- `sudo chmod a+rwx /usr/local/lib/python3.5/dist-packages/editUsers/main.py`
- `python3 -m pip install persist/`

## Jak to vyzkoušet?

### Buffer Overflow

- `./exploit1.py`
- Zkopírovat si vygenerované heslo
- `./wallet.o`
- Objeví se `Login: `, netřeba vyplňovat, nebo lze použít kterýkoli login ze souboru `stash`
- Objeví se `Password: `, vložit vygenerované heslo z exploit.py, dojde k buffer overflow a získáme admin access.

### Python Hijacking
- `./exploit2.py`
- Přihlásit se jako nějaký admin account (může se použít i Buffer Overflow exploit k tomuto accessu)
- Zvolit admin tools (možnost 3)
- Otevře se shell uživatele `root`

### Integer Overflow
- `chmod 755 exploit3.py`
- `./exploit3.py`
- Přihlásit se jako libovolný user account (např. `piesek` a `kotek`)
- Skript vykoná integer overflow a na zvoleném účtu máte maximum peněz

### Python PATH hijacking
- `./exploit4.py`
- `./wallet.o` a přihlásit se jako kterýkoli user

## Jak pokračovat?

- 3 exploity ze zadání hotovy
- Udělat další podle libosti?
- Zkrášlit app v C - pozor na rozbití maker (.excpect  musí odpovídat), zůstatek zvlášt pro každý účet v stash?
- Ďakujem za pozornost, doviďenia

