#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 10

char *inputString(size_t *size){
    char *str;
    unsigned base = 32;
    int ch;
    size_t len = 0;
    str = realloc(NULL, sizeof(char)*base);
    if(!str)return str;
    while('\n'!=(ch=fgetc(stdin))){
        str[len++]=ch;
        if(len==base){
            str = realloc(str, sizeof(char)*(base+=16));
            if(!str)return str;
        }
    }
    str[len++]='\0';
    *size = len;
    return realloc(str, sizeof(char)*len);
}
int strcmp(const char* str1, const char* str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) return 1;
        i++;
    }
    if (str1[i] == str2[i] && str1[i] == '\0') return 0;
    return 1;
}
void strcopy(char *dest, char *src) {
    unsigned int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
}

short authenticate(char *login, char *password) {
    int isAdmin = 0;
    char userData[2][MAX_LENGTH]; //both are overflowable
    char data[2][MAX_LENGTH];
    int charIndex = 0;
    short nameOrPassword = 0; // 0 for name, 1 for password
    strcopy(userData[0], login);
    strcopy(userData[1], password);
    FILE* in = fopen("stash", "r");
    char ch;
    while ((ch = fgetc(in)) != EOF) {
        if (ch == '\n') {
            data[1][charIndex] = '\0';
            if (strcmp(login, data[0]) == 0) {
                if (strcmp(password, data[1]) == 0) {
                    fclose(in);
                    return 1;
                }
            }
            charIndex = 0;
            nameOrPassword = 0;
        }
        else if (ch == ':') {
            data[0][charIndex+1] = '\0';
            charIndex = 0;
            nameOrPassword = 1;
        }
        else {
            if (charIndex < MAX_LENGTH-2) { //overflow from text loading is not possible, I hope
                data[nameOrPassword][charIndex] = ch;
                data[nameOrPassword][charIndex+1] = '\0';
                charIndex++;
            }
        }
    }
    fclose(in);
    if (isAdmin) return 2;
    printf("%d", isAdmin);
    return 0;
}

int main() {
    long loglen = 0;
    printf("Login as: ");
    char* bufferlog = inputString(&loglen);
    long passlen = 0;
    printf("\nPassword: ");
    char* bufferpass = inputString(&passlen);
    int ans = authenticate(bufferlog, bufferpass);
    printf("\nAuthentication value: %d", ans);
    return 0;
}
