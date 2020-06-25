/* README */
// # This project is developed by Ayush Suman
// ##########################################################################################################################
// # Since we are not integrating network calls and database calls 
//      Server data is mocked with files stored in ./Server dir
//      Data from local database is mocked with files stored in ./Database dir
//
// # Server APIs section contains function declarations 
//      which will interact with files from mock Server i.e. ./Server dir in this case.
// # Local Database Interactor section contains function declaration 
//      which will interact with files from mock Local Database i.e. ./Database dir
// # Business Logic Layer section contains model functions
// # Backend Library section contains some backend functions 
//      that will help us with the software development
// ##########################################################################################################################





/* Code */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef unsigned long long int64;
static void (*SCREEN)();
static char* USERNAME;

struct bookClass {
	char id[20];
	char bookTitle[20];
	char author[20];
	int quantity;
	int issued;
};

struct bookList {
	struct bookClass book;
	struct bookList* next;
};


struct bookInfo {
	char id[20];
	char bookTitle[20];
	char author[20];
};


struct bookInfoList {
	struct bookInfo book;
	struct bookInfoList* next;
};


// ##########################################################################################################################

/* Mock Server APIs */

// Verifies credentials and creates and returns login token for maintaining login session 
// Returns 0 and points token pointer to the login token if the credentials are correct
// Returns 1 if the credentials are incorrect
// Returns -1 if the file does not open
int verifyCredentials(char* username, int64 hash, char *token);

// Registers new user by creating a login token for the user
// Returns 0 if token is created successfully
// Returns 1 if username already exists
// Returns -1 if the file does not open
int createNewToken(char* username, int64 hash);
// Removes a user by permenantly deleting the login token from server
void deleteTokenPermenantly(char* username);
// Verifies requested token and puts username in the username argument
// Returns 0 if the token is verified
// Returns 1 if the token is not verified
// Returns -1 if file does not open
int verifyToken(char* token, char* username);
// Public API for searching through the book store
int searchBooks(char* book, struct bookList* books);
// Public API for getting book info of the requested Issue No
int getBookByID(char* id, struct bookClass *book);
// API for getting wish list info
int getWishListInfo(char* token, struct bookInfoList books);
// API for returning the info of the book issued
int getIssuedBookInfo(char* token, struct bookInfoList books);
// ##########################################################################################################################

/* Mock Local Database Interactor*/

// Saves login token in a file
// Returns -1 if the file does not open
// Returns 0 if the token is successfully stored
int saveToken(char* token);
// Reads current user login token
// Returns -1 if the file does not open
// Returns 0 if token is successfully read and put into token argument
int getToken(char* token);
// Deletes current user login token
// Returns -1 if the file does not open
// Returns 0 if the token is successfully deleted
int deleteToken();

// ##########################################################################################################################

/*Backend Library*/

// Generates Salt
int generateSalt(char* username);
// Takes password and a predifined random salt value to generate a hash
// Will be used to verify login credentials
int64 generateSaltedHash(char* password, int salt);
// Validates password for its strength and length
// Returns 0 if password is valid
// Returns 1 if password is too short or too long
// Returns 2 if invalid characters are used in the password
// Returns 3 if password is too weak
int validatePassword(char* password);
// Confirms password
// Returns 0 if the passwords match
// Returns 1 if the password does not match
int matchPassword(char* password, char* passwordc);
// Validates username to contain no whitespaces or invalid characters
// Returns 0 if username is valid
// Returns 1 if username contains invalid characters
// Returns 2 if username is longer than 16 characters
int validateUsername(char* username);
// Generates unique token for a username
char* generateToken(char* username, int64 hash);
// Clears the previous screen and loads new screen
void loadScreen(void (*screen)());

// ##########################################################################################################################

/*Business Logic Layer*/

// Takes username and password and authenticates the user;
// Returns -1 if something went wrong
// Returns 0 if the user is successfully logged in
// Returns 1 if the username or the password was incorrect
// Returns
int login(char* username, char* password);
// Logs the user out
void logout();
// Looks for login token and verifies it
// Returns username if the token is verified
char* getCurrentUser();
// Registers New User
// Returns -1 if something went wrong
// Returns 0 if the user is registerd successfully
// Returns 1 if the user already exists
// Returns 2 if the password size is not correct
// Returns 3 if the password contains invalid characters
// Returns 4 if the password is too weak
// Returns 5 if the username contains invaiid characters
// Returns 6 if the username is longer than 16 characters
// Returns 7 if the passwords does not match
int registerUser(char* username, char* password, char* passwordc);
// Removes User
void removeUser(char* username);

// ##########################################################################################################################

/*UI Layer*/

void newScreen(void (*screen)());
void splashScreen();
void welcomeScreen();
void loginUI();
void registerUI();
void homeScreen();
void issuedBookUI();
void bookStoreUI();
 
// ##########################################################################################################################

int main(){
 	//printf("%llu", generateSaltedHash("zzzzzyAzzzzzzzz", generateSalt("heelo")));
 	//printf("%d", validatePassword("he1Hlloooo"));
 	//printf("%d", generateSalt("hello"));
 	//printf("%d", validateUsername("jkh56Shello"));
	//char token[50];
	//int a=verifyCredentials("asdfghjkl", 123223, token);
	//printf("%d ", a);
	//printf("%s", token);
	//int ret = createNewToken("aush", 1525);
	//printf("%d", ret);
	//saveToken("Ty");
	//int ret = login("ayush", "123456");
	//printf("%d", ret);
	//char* token = generateToken("ayush", 15243);
	//int ret=registerUser("ayushsumanyo", "Password123");
	//login("ayushsumanyo", "Password123");
	//welcomeScreen();
	//char* username = (char*) malloc(50 * sizeof(char));
	//int ret = verifyToken("lJf9SpfllcpnqyAKqy", username);
	//printf("%d\n%s", ret, username);
	newScreen(splashScreen);
	for(;;){
		loadScreen(SCREEN);
	}
	//loadScreen(splashScreen);
	//struct bookClass *book = (struct bookClass*) malloc(sizeof(struct bookClass));
	//int ret = getBookByID("issueno", book);
	//printf("%d\n%s", ret, book->bookTitle);
	//struct bookList* books = (struct bookList*) malloc(sizeof(struct bookList));
	//searchBooks("book", books);
	//printf("%s", books->next->book.bookTitle);
}

// ##########################################################################################################################

void newScreen(void (*screen)()){
	SCREEN = screen;
}

void splashScreen(){
	printf("WELCOME TO E-LIBRARY PORTAL\n\n");
	printf("Loading...\n");
	USERNAME = getCurrentUser();
	if(USERNAME == "\0"){
		newScreen(welcomeScreen);
	}else{
		newScreen(homeScreen);
	}
}


void welcomeScreen(){
	printf("WELCOME TO E-LIBRARY PORTAL\n\n");
option:	printf("If you are an old user, Press 1 to Log In\n");
	printf("If you are a new user, Press 2 to Register\n\n");
	int r = fgetc(stdin)-'0';
	if(r==1){
		newScreen(loginUI);
	} else if(r==2){
		newScreen(registerUI);
	} else {
		printf("NOT A VALID ENTRY!\nEnter Again:\n");
		goto option;
	}
}

void homeScreen(){
	printf("HOMESCREEN %s\n", USERNAME);
	exit(0);
}


void loginUI(){
	char username[500];
	char password[500];
	printf("\e[1;1H\e[2J");
	printf("Enter Username:\n");
	scanf("%s", username);
	printf("Enter Password:\n");
	scanf("%s", password);
	username[50]='\0';
	password[50]='\0';
	int ret = login(username, password);
	if(ret==0){
		printf("Logged In\n");
		printf("\e[1;1H\e[2J");
		newScreen(homeScreen);
	}else{
		printf("Incorrect username or password\n");
loginOption:	printf("Press 1 to try again\nPress 2 to return to Welcome page\n");
		int r=0;
		scanf("%d", &r);
		if(r==1){
			return;	
		}else if(r==2){
			newScreen(welcomeScreen);
		}else{
			printf("NOT A VALID ENTRY!\nEnter Again:\n");
			goto loginOption;
		}
	}
}

void registerUI(){
	char* username;
	char* password;
	char* passwordc;
enter:	printf("Enter New Username:\n");
	scanf("%s", username);
	printf("Enter Password:\n");
	scanf("%s", password);
	printf("Enter the password again:\n");
	scanf("%s", passwordc);
	int ret = registerUser(username, password, passwordc);
	if(ret == 0){
		printf("User successfully registered");
		printf("Hit ENTER to continue...");
		char c;
		scanf("%c", &c);
		newScreen(welcomeScreen);
		return;

	} else if(ret == 7){
		printf("Password does not match\n");
	} else if(ret == 1){
		printf("User already exists\n");
	} else if(ret == 2){
		printf("Password length should be >=8 and <= 16\n");
	} else if(ret == 3){
		printf("Password should contain characters from 0 to 9, a to z and A to z\n");
	} else if(ret == 4){
		printf("Password is too weak. Should have atleast one uppercase, one lowercase and one numerical character\n");	
	} else if(ret == 5){
		printf("Username should contain characters from 0 to 9, a to z and A to Z\n");
	} else if(ret == 6){
		printf("Username should not be longer than 16 characters\n");
	} else {
		printf("Something Went Wrong!");
	}
registerOption:	printf("Press 1 to try again\nPress 2 to return to Welcome page\n");
		int r=0;
		scanf("%d", &r);
		if(r==1){
			return;	
		}else if(r==2){
			newScreen(welcomeScreen);
		}else{
			printf("NOT A VALID ENTRY!\nEnter Again:\n");
			goto registerOption;
		}
	

}

char* getCurrentUser(){
	char* token = (char*) malloc(50*sizeof(char));
	int re = getToken(token);
	if(re == 1){
		return "\0";
	}
	char* username = (char*) malloc(50*sizeof(char));
	int ret = verifyToken(token, username);
	if(ret==0){
		return username;
	} else {
		return "\0";
	}
}

void loadScreen(void (*screen)()){
	printf("\e[1;1H\e[2J");
	screen();
}

int verifyToken(char* token, char* username){
	FILE* fp;
	char gToken[50];
	int tlen = strlen(token);
	fp = fopen("Server/tokenStore.txt", "r");
	if(fp ==NULL){
		free(token);
		return -1;
	}
	int equals=0;
	int linenum=0;
	while(fgets(gToken, 50, fp)){
		if((linenum%3)==2){
			for(int i=0; i<tlen; i++){
				if(gToken[i] == token[i]){
					equals=1;	
				}else{
					equals=0;
					break;
				}
			}
			if(equals==1){
				rewind(fp);
				linenum++;
				linenum/=3;
				for(int m=0; m<=linenum;m+=3){
					fgets(username, 50, fp);
				}
				username[strlen(username)-1]='\0';
				free(token);
				return 0;
			}
		}
		linenum++;
	}
	free(token);
	return 1;

}

int getToken(char* token){
	FILE* fp;
	fp = fopen("Local/token.txt", "r");
	if(fp==NULL){
		return -1;
	}
	fgets(token, 50, fp);
	if(token[0] == '\0'){
		free(token);
		return 1;
	}
	fclose(fp);
	return 0;
}

int generateSalt(char* username){
    	int ulen= strlen(username);
    	int salt=1;
    	for(int i=0; i<ulen; i++){
        	salt *= ((int) username[i] * (i+1));
    	}
    	salt %=127;
    	return salt;
}

int64 generateSaltedHash(char* password, int salt){
    	int passlen = strlen(password);
    	int passint[passlen];
    	static const int keyArray[]={23,29,17,13,19,23,37,7,7,31,11,13,5,7,41,5};
    	for(int i=0; i<passlen; i++){
        	passint[i]=(int) password[i];
    	}
    	passint[0]+=(salt%10);
    	passint[passlen-1]+=(salt%10);
    	int* x = malloc(sizeof(int64)*passlen);
    	for(int i=0; i<passlen; i++){
        	x[i]=(int64) keyArray[i];
        	for(int j=0; j<passint[i];j++){
            		x[i]=(x[i]* (int64) keyArray[i])%(134217757);
        	}
    	}
    	int64 hash= (int64) salt;
    	for(int i=0; i<passlen; i++){
        	hash+=x[i];
    	}
    	free(x);
    	return hash;
}

int matchPassword(char* password, char* passwordc){
	int plen = strlen(password);
	if(plen != strlen(passwordc)){
		return 1;		
	}
	for(int i=0; i<plen; i++){
		if(password[i]!= passwordc[i]){
			return 1;
		}
	}
	return 0;
}

int validateUsername(char* username){
    	int ulen= strlen(username);
	if(ulen>16){
		return 2;
	}
    	for(int i=0; i<ulen;i++){
        	if(('0'<=username[i] && username[i]<='9')||('A'<=username[i] && username[i]<='Z')||('a'<=username[i] && username[i]<='z')){
            		continue;
        	}else{
            		return 1;
        	}
    	}
    	return 0;
}

int validatePassword(char* password){
    	int passlen= strlen(password);
    	if(passlen<8 || passlen>16){
        	return 1;
    	}
    	int intcount=0;
    	int lowercount=0;
    	int uppercount=0;
    	for(int i=0;i<passlen;i++){
        	if('0'<=*(password+i) && *(password+i)<='9'){
            		intcount++;
        	} else if('A'<= *(password+i) && *(password+i)<='Z'){
            		uppercount++;
        	} else if('a'<= *(password+i) && *(password+i)<='z'){
            		lowercount++;
        	} else {
            		return 2;
        	}
    	}
    	if(intcount==0 || lowercount==0 || uppercount==0){
		printf("%d %d %d\n", intcount, lowercount, uppercount);
        	return 3;
    	}
    	return 0;
}

int login(char* username, char* password){
    	int salt = generateSalt(username);
    	int64 p_hash = generateSaltedHash(password, salt);
    	char token[50];
    	int ret = verifyCredentials(username, p_hash, token);
	if(ret != 0){
		return ret;
	}
    	return saveToken(token);
	
}

int saveToken(char* token){
	FILE* fp;
	fp = fopen("Local/token.txt", "w");
	if(fp ==NULL){
		return -1;
	}
	fputs(token, fp);
	fclose(fp);
	return 0;
}

int registerUser(char* username, char* password, char* passwordc){
    	int match = matchPassword(password, passwordc); 
	if(match==1){
		return 7;
	}
	int u_status = validateUsername(username);
    	if(u_status!=0){
        	return u_status+4;
    	}
    	int p_status = validatePassword(password);
    	if(p_status!=0){
		printf("Password not validated");
        	return p_status+1;
	}
	int salt = generateSalt(username);
        int64 hash = generateSaltedHash(password, salt);
	int ret = createNewToken(username, hash);
	return ret;
}

char* generateToken(char* username, int64 hash){
	int ulen = strlen(username);
	char* token;
	token = (char*) malloc(19*sizeof(char));
	int c;
	int s=0;
	int h = hash%13;
	for(int i = 0; i<ulen; i++){
		c= (int) username[i];
		s+= (int) username[i];
		c%=62;
		for(int j=0; j<i+h; j++){
			c*=c;
			c%=62;
		}
		if(0<=c && c<10){
			token[i] = c+'0';
		}
		if(10<=c && c<36){
			token[i] = c-10+'A';
		}
		if(36<=c && c<62){
			token[i] = c-36+'a';
		}
	}
	for(int i=ulen;i<18;i++){
		h = hash%62;
		h%=62;
		for(int j = 0; j<i;j++){
			h*=h;
			h%=62;
			s*=s;
			s%=62;
		}
		h+=s;
		h%=62;
		if(0<=h && h<10){
			token[i] = h+'0';
		}
		if(10<=h && h<36){
			token[i] = h-10+'A';
		}
		if(36<=h && h<62){
			token[i] = h-36+'a';
		}

	}
	token[18]='\0';
	return token;

}

int createNewToken(char* username, int64 hash){
	int ulen = strlen(username);
	char ha[50];
	int hlen = sprintf(ha, "%llu", hash);
	
	FILE* fp;
	fp = fopen("./Server/tokenStore.txt", "r");
	if(fp==NULL){
		return -1;
	}
	char line[50];
	int linenum=0;
	int equals=0; 		
	while(fgets(line, 50, fp)){
		if((linenum%3) == 0 ){
			if(ulen==(strlen(line)-1)){
				for(int i=0; i<ulen; i++){
					if(username[i]==line[i]){
						equals=1;			
					}else{
						equals=0;
						break;
					}
				}
			}
		}
		if(equals==1){
			return 1;
		}
		linenum++;
	}
	fp = freopen("Server/tokenStore.txt", "a", fp);
	fputs(username, fp);
	fputs("\n", fp);
	fputs(ha, fp);
	fputs("\n", fp);
	char* token=generateToken(username, hash);
	fputs(token, fp);
	fputs("\n", fp);
	fclose(fp);
	free(token);
}

int verifyCredentials(char* username, int64 hash, char* token){	
	int ulen =  strlen(username);
	char ha[50];
	int hlen = sprintf(ha, "%llu", hash);
	FILE* fp;
	fp = fopen("Server/tokenStore.txt", "r");
	if(fp == NULL){
		return -1;
	}
	char line[50];
	int linenum=0;
	int equals=0; 		
	while(fgets(line, 50, fp)){
		if((linenum%3) == 0 ){
			if(ulen==(strlen(line)-1)){
				for(int i=0; i<ulen; i++){
					if(username[i]==line[i]){
						equals=1;			
					}else{
						equals=0;
						break;
					}
				}
			}
		}
		if(equals==1){
			fgets(line, 50, fp);
			int creds=0;
			if(hlen== (strlen(line)-1)){
				for(int i=0; i<hlen; i++){
					if(ha[i]==line[i]){
						creds=1;
					}else{
						creds=0;
						break;
					}
				}
			}
			if(creds==0){
				fclose(fp);
				return 1;
			}else{
				fgets(line, 50, fp);
				for(int i=0; i<50; i++){
					if(line[i]=='\n'){
						token[i] ='\0';
						break;
					}
					token[i] = line[i];
				}
				fclose(fp);
				return 0;
			}
		}
		linenum++;
	}
	fclose(fp);
	return 1;

}

int getBookByID(char* id, struct bookClass *book){
	FILE* fp;
	fp = fopen("Server/bookStore.txt", "r");
	if(fp==NULL){
		return -1;
	}
	char line[20];
	int linenum=0;
	while(fgets(line, 20, fp)){
		if((linenum%5)==0){
			line[strlen(line)-1]='\0';
			int cmp = strcmp(id, line);
			if(cmp==0){
				strcpy(book->id, line);	
				fgets(line, 20, fp);
				line[strlen(line)-1]='\0';
				strcpy(book->bookTitle, line);	
				fgets(line, 20, fp);
				line[strlen(line)-1]='\0';
				strcpy(book->author, line);	
				fgets(line, 20, fp);
				line[strlen(line)-1]='\0';
				book->quantity = atoi(line);
				fgets(line, 20, fp);
				line[strlen(line)-1]='\0';
				book->issued = atoi(line);
				fclose(fp);
				return 0;
			}
		}
		linenum++;
	}
	fclose(fp);
	return 1;

}

int searchBooks(char* book, struct bookList *books){
	int size = 0;
	FILE* fp;
	fp = fopen("Server/bookStore.txt", "r");
	if(fp==NULL){
		return -1;
	}
	struct bookList* booklist = books;
	int blen = strlen(book);
	char line[20];
	int blocknum=0;
	while(fgets(line, 20, fp)){
nextblock:	for(int i=0; i<5; i++){
			int llen = strlen(line);
			if(llen>blen){
				for(int i=0; i<llen-blen; i++){
					int cmp = strncmp(book, &line[i], blen);
					if(cmp==0){
						rewind(fp);
						for(int j=0; j<=blocknum*5; j++){
							fgets(line, 20, fp);
						}
						booklist->next = (struct bookList*) malloc(sizeof(struct bookList));
						strcpy(booklist->book.id, line);	
						fgets(line, 20, fp);
						line[strlen(line)-1]='\0';
						strcpy(booklist->book.bookTitle, line);	
						fgets(line, 20, fp);
						line[strlen(line)-1]='\0';
						strcpy(booklist->book.author, line);	
						fgets(line, 20, fp);
						line[strlen(line)-1]='\0';
						booklist->book.quantity = atoi(line);
						fgets(line, 20, fp);
						line[strlen(line)-1]='\0';
						booklist->book.issued = atoi(line);
						booklist = booklist->next;
						size++;
						if(fgets(line, 20, fp)){
							blocknum++;
							goto nextblock;
						}else{
							fclose(fp);
							return size;
						}
					}
				}
			}
			fgets(line, 20, fp);
		}
		blocknum++;
	}

	fclose(fp);
	return 0;

}



















