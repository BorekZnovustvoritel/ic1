from supersecretpasswordstash import etc_shadow


def auth(login: str, password: str) -> bool:
    if (ans := getattr(etc_shadow, login, None)) is not None:
        if password == ans:
            return True
    return False
