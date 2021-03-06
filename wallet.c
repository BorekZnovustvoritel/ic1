#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

#define MAX_LENGTH 10
int balance;
char* username;

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
	int isAuth = 0;
	int isAdmin = 0;
	char userPassword[MAX_LENGTH]; //overflowable
    char data[2][MAX_LENGTH]; //contains the "view" from stash
    int charIndex = 0;
    short nameOrPassword = 0; // 0 for name, 1 for password
    
    FILE* in = fopen("stash", "r");
    char ch;
    while ((ch = fgetc(in)) != EOF) {
        if (ch == '\n') {
            data[1][charIndex] = '\0';
            if (strcmp(login, data[0]) == 0) {
				break;
            }
            charIndex = 0;
            nameOrPassword = 0;
			isAdmin = 0;
        }
		else if (ch == ';') {
			isAdmin = fgetc(in) - '0';
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
    strcopy(userPassword, password); // Here we can overflow the userPassword buffer into isAdmin
	if (strcmp(userPassword, data[1]) == 0) {
        isAuth = 1;
    }
    if (isAdmin) return 2; // admin login
	if (isAuth) return 1; // normal login
    return 0; // login not successful
}

int menu(char** list, int len) {
	system("clear");
	printf("Choose an option:\n");
	for (int i = 0; i < len; i++) {
		printf("%d .. %s\n", i, list[i]);
	}
	printf("%d .. Exit\n", len);
	int out = -1;
	while (out > len || out < 0) {
		scanf("%d", &out);
	}
	getchar(); // to clear the stdin buffer
	return out;
}

void loadBalance() { // Initiate global value
	char buffer[100];
	sprintf(buffer, "python3 -m persist -u %s", username);
	system(buffer);
	FILE* in = fopen("surelyJsonFromServerAndNotLocallyStoredFile.exe.jpeg.png.piesek", "r");
	fscanf(in, "%d", &balance);
	fclose(in);
}

void persistBalance() { // Store global value into a file
	char buffer[100];
	sprintf(buffer, "python3 -m persist -b %d -u %s", balance, username);
	system(buffer);
}

void printBalance() {
	system("clear");
	printf("Your balance is: $%d\nPress enter to continue.\n", balance);
	getchar();
}

void tweakUsers() {
	system("clear");
	system("python3 -m editUsers");
}

void pay(){
	system("clear");
	int payment = -1;
	while (payment < 0) {
		printf("Enter positive amount of money to pay: ");
		scanf("%d", &payment);
		getchar();
	}
	size_t length;
	printf("Enter recipient: ");
	char* recipient = inputString(&length);
	char buffer[150];
	sprintf(buffer, "python3 -m persist -u %s -t %s -b %d", username, recipient, payment);
	system(buffer);
	free(recipient);
	printf("Press enter to continue.\n");
	getchar();
	balance -= payment;
}

void adminMenu() {
	system("clear");
	loadBalance();
	short exit = 0;
	char* options[3] = {"Pay", "Check balance", "Admin tools"};
	do {
		switch(menu(options, 3)) {
			case 0: //Pay
				pay();
			break;
			case 1: //Check balance
				printBalance();
			break;
			case 2: //Admin tools
				tweakUsers();
			break;
			default: //Exit
				exit = 1;
			break;
		}
	} while (!exit);
	persistBalance(); //saves the current amount of money
}

void userMenu() {
	system("clear");
	loadBalance();
	short exit = 0;
	char* options[2] = {"Pay", "Check balance"};
	do {
		switch(menu(options, 2)) {
			case 0: //Pay
				pay();
			break;
			case 1: //Check balance
				printBalance();
			break;
			default: //Exit
				exit = 1;
			break;
		}
	} while (!exit);
	persistBalance();
}

int main() {
	setuid(0);
	system("clear");
	printf("CRYPTOWALLET TM\n\n");
    size_t loglen = 0;
    printf("Login as: ");
    username = inputString(&loglen);
    size_t passlen = 0;
    printf("\nPassword: ");
    char* bufferpass = inputString(&passlen);
	int ans = authenticate(username, bufferpass);
    switch(ans) {
		case 1:
			userMenu();
		break;
		case 2:
			adminMenu();
		break;
		default:
			printf("\nLOGIN FAILED!\n");
		break;
	}
	
	free(bufferpass);
	free(username);
	
    return 0;
}
