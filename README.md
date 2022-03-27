# Projekt do předmětu IC1

## Prerekvizity:

- Linux Debian
- GCC (C compiler)
- Git (`sudo apt install git`)
- Python3 (`sudo apt install python3`)
- Pip (`sudo apt install python3-pip`)
- Pexpect (`python3 -m pip install pexpect`)
- GDB (GNU Debugger)
- Zrušení ASLR ochrany (`echo 0 | sudo tee /proc/sys/kernel/randomize_va_space`, `sudo nano /etc/sysctl.d/01-disable-aslr.conf` a napsat `kernel.randomize_va_space = 0`)

## Jak to zkompilovat?

- `gcc -ggdb -m32 -fno-stack-protector ./wallet.c -o wallet.o`

## Jak to vyzkoušet?

- `./exploit.py`
- Zkopírovat si vygenerované heslo
- `./wallet.o`
- Objeví se `Login: `, netřeba vyplňovat, nebo lze použít kterýkoli login ze souboru `stash`
- Objeví se `Password: `, vložit vygenerované heslo z exploit.py, dojde k buffer overflow a získáme admin access.

## Jak pokračovat?

- Zatím máme jen login, tak se snažte
- Ďakujem za pozornost, doviďenia

