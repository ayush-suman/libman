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
// Verifies requested token
void verifyToken(int64 token);

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
// Validates username to contain no whitespaces or invalid characters
// Returns 0 if username is valid
// Returns 1 if username contains invalid characters
// Returns 2 if username is longer than 16 characters
int validateUsername(char* username);

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
// Looks for login token and verifies the user's authentication
void getCurrentUser();
// Registers New User
// Returns -1 if something went wrong
// Returns 0 if the user is registerd successfully
// Returns 1 if the user already exists
// Returns 2 if the password size is not correct
// Returns 3 if the password contains invalid characters
// Returns 4 if the password is too weak
// Returns 5 if the username contains invaiid characters
// Returns 6 if the username is longer than 16 characters
int registerUser(char* username, char* password);
// Removes User
void removeUser(char* username);


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
	int ret = login("ayush", "123456");
	printf("%d", ret);
}

// ##########################################################################################################################



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

int validateUsername(char* username){
    	int ulen= strlen(username);
	if(ulen>16){
		return 2;
	}
    	for(int i; i<ulen;i++){
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
    	for(int i;i<passlen;i++){
        	if('0'<=password[i] && password[i]<='9'){
            		intcount++;
        	} else if('A'<=password[i] && password[i]<='Z'){
            		uppercount++;
        	} else if('a'<=password[i] && password[i]<='z'){
            		lowercount++;
        	} else {
            		return 2;
        	}
    	}
    	if(intcount==0 || lowercount==0 || uppercount==0){
        	return 3;
    	}
    	return 0;
}

int login(char* username, char* password){
    	int salt = generateSalt(username);
    	int64 p_hash = generateSaltedHash(password, salt);
    	char token[50];
	printf("%llu\n", p_hash);
    	int ret = verifyCredentials(username, p_hash, token);
	if(ret != 0){
		return ret;
	}
	printf("%s\n", token);
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

int registerUser(char* username, char* password){
    	int u_status = validateUsername(username);
    	if(u_status!=0){
        	return u_status+4;
    	}
    	int p_status = validatePassword(password);
    	if(p_status!=0){
        	return p_status+1;
	}
	int salt = generateSalt(username);
        int64 hash = generateSaltedHash(password, salt);
	int ret = createNewToken(username, hash);
	return ret;
}

int createNewToken(char* username, int64 hash){
	int ulen = strlen(username);
	char ha[30];
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
	//generateToken;
	fputs("Token", fp);
	fputs("\n", fp);
	fclose(fp);
}

int verifyCredentials(char* username, int64 hash, char *token){	
	int ulen =  strlen(username);
	char ha[30];
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


