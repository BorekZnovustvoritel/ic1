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

- `gcc -ggdb -m32 -fno-stack-protector ./wallet.c -o wallet.o`
- `sudo python3 -m pip install ~/ic1/editUsers/`
- `sudo chmod a+rwx /usr/local/lib/python3.5/dist-packages/editUsers/main.py`

## Jak to vyzkoušet?

### Buffer Overflow

- `./exploit.py`
- Zkopírovat si vygenerované heslo
- `./wallet.o`
- Objeví se `Login: `, netřeba vyplňovat, nebo lze použít kterýkoli login ze souboru `stash`
- Objeví se `Password: `, vložit vygenerované heslo z exploit.py, dojde k buffer overflow a získáme admin access.

### Python Hijacking
- `./exploit2.py`
- Přihlásit se jako nějaký admin account (může se použít i Buffer Overflow exploit k tomuto accessu)
- Zvolit admin tools (možnost 3)
- Otevře se shell uživatele `root`

## Jak pokračovat?

- Zatím máme jen login, tak se snažte
- Ďakujem za pozornost, doviďenia

