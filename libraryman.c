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
int64 verifyCredentials(char* username, int64 hash);
// Registers new user by creating a login token for the user
// Returns 0 if token is created successfully
// Returns 1 if username already exists
int createNewToken(char* username, int64 hash);
// Removes a user by permenantly deleting the login token from server
void deleteTokenPermenantly(char* username);

// ##########################################################################################################################

/* Mock Local Database Interactor*/

// Saves login token in a file
void saveToken(int64 token);
// Reads current user login token and verifies it
void getAndVerifyToken(int64 token);
// Deletes current user login token
void deleteToken();

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


// ##########################################################################################################################

/*Business Logic Layer*/

// Takes username and password and authenticates the user;
void login(char* username, char* password);
// Logs the user out
void logout();
// Registers New User
int registerUser(char* username, char* password);
// Removes User
void removeUser(char* username);

// ##########################################################################################################################

int main(){
 printf("%llu", generateSaltedHash("zzzzzzAzzzzzzzz", generateSalt("heelo")));
 //printf("%d", validatePassword("he1Hlloooo"));
 //printf("%d", generateSalt("hello"));

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

int64 verifyCredentials(char* username, int64 hash){}

void login(char* username, char* password){
    int salt = generateSalt(username);
    int64 p_hash = generateSaltedHash(password, salt);
    int64 token = verifyCredentials(username, p_hash);
    //saveToken(token);
}

int registerUser(char* username, char* password){
    int p_status = validatePassword(password);
    if(p_status==0){
        int salt = generateSalt(username);
        generateSaltedHash(password, salt);
    }else{
        return p_status;
    }

}