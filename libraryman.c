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
#include<time.h>
#include<unistd.h>

typedef unsigned long long int64;
static void (*SCREEN)();
static char USERNAME[20] = "\0";

struct bookClass {
	// Changed 50 to 150 to create a PR
	char id[150];
	char bookTitle[150];
	char author[150];
	int quantity;
	int issued;
};

struct bookList {
	struct bookClass book;
	struct bookList* next;
};


struct bookInfo {
	char id[50];
	char bookTitle[50];
	char author[50];
};


struct bookInfoList {
	struct bookInfo book;
	time_t time;
	struct bookInfoList* next;
};


struct txtFile{
	char line[50];
	struct txtFile* next;
};

struct users{
	char username[20];
	struct users* next;
};

struct bookVendors{
	char id[50];
	char bookTitle[50];
	char author[50];
	char vendor[50];
};

struct bookVendorList{
	struct bookVendors book;
	struct bookVendorList* next;
};
// ##########################################################################################################################

/* Mock Server APIs */

// Verifies credentials and creates and returns login token for maintaining login session 
// Returns 0 and points token pointer to the login token if the credentials are correct
// Returns 1 if the credentials are incorrect
// Returns -1 if the file does not open
int verifyCredentials(char* username, int64 hash, char *token);
int verifyCredentialsForAdmin(char* username, int64 hash, char *token);
// Registers new user by creating a login token for the user
// Returns 0 if token is created successfully
// Returns 1 if username already exists
// Returns -1 if the file does not open
int createNewToken(char* username, int64 hash);
// Removes a user by permanently deleting the login token from server
int deleteTokenPermanently(char* username);
// Returns all users in userlist
int viewUsers(struct users* userlist);
// Verifies requested token and puts username in the username argument
// Returns 0 if the token is verified
// Returns 1 if the token is not verified
// Returns -1 if file does not open
int verifyToken(char* token, char* username);
// Public API for searching through the book store
// Returns -1 if the file does not open
// Returns the number of books that matched
int searchBooks(char* book, struct bookList* books);
// Public API for getting book info of the requested Issue No
// Returns -1 if the file does not open
// Returns 0 if the book is found
// Returns 1 if the book is NOT found
int getBookByID(char* id, struct bookClass *book);
// Authenticated API for getting wish list info
int getWishListInfo(char* token, struct bookInfoList* books);
// Authenticated API for returning the info of the book issued
int getIssuedBookInfo(char* token, struct bookInfoList* books);
// Authenticated API to issue a book
int issueBook(char* token, struct bookInfo book, time_t time);
// Returns a issued book
// Returns -1 if file does not open
// Returns 0 if book successfully returned
// Returns 1 if the book NOT found
int returnBook(char* token, char* id);
int viewBooksFromMarket(struct bookVendorList* books);
int viewBookFromMarketByID(char* id, struct bookVendors* book);
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
int loginAsAdmin(char* username, char* password);
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
// Returns the size of user and userlist
int getAllUsers(struct users* userlist);
// Removes User
int removeUser(char* username);
int deleteMyAccount(char* username);
int viewBookByID(char* id, struct bookClass* book);
// Issues book if available
// Increases issue count by 1 if issued successfully
// Returns -1 if something went wrong
// Returns 0 if book issued successfully
// Returns 1 if book not available
// Returns 2 if book is already issued
int issueBookByID(char* id);
int getAllIssuedBooks(struct bookInfoList* books);
// searches the book store for the given keyword
// Returns -1 if something went wrong
// Returns the number of books that matched
int search(char* book, struct bookList* books);
// Finds the books that are due
void dueBooks();
// Returns an issued book to the library
// Decreases Issued Count by 1 if successfully returned
// Returns -1 if something went wrong
// Returns 0 if book successfully returned
// Returns 1 if book is not issued
int returnIssued(char* id);
int searchUsers(char* suser,struct users* userlist);
int getBooksFromMarket(struct bookVendorList* books);
int getBookFromMarketByID(char* id, struct bookVendors* book);
int buyBookFromMarket(char* id, char* issueID, int quantity);
// ##########################################################################################################################

/*UI Layer*/

void newScreen(void (*screen)());

void splashScreen();
void welcomeScreen();
void loginUI();
void registerUI();
void homeScreen();
void homeScreenAdmin();
void issuedBookUI();
void bookStoreUI();
void settingsScreen();
void searchScreen();
void searchScreenAdmin();
void searchUsersScreen();
void allUsersScreen();
void loginAsAdminUI();
void bookMarketUI();
void systemCrash();
void createNotification(int size, struct bookInfoList* books);
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
		int i = 0;
		int a = 0;
		loadScreen(SCREEN);
	}
	//loadScreen(splashScreen);
	//struct bookClass *book = (struct bookClass*) malloc(sizeof(struct bookClass));
	//int ret = getBookByID("issueno", book);
	//printf("%d\n%s", ret, book->bookTitle);
	//struct bookList* books = (struct bookList*) malloc(sizeof(struct bookList));
	//int size = searchBooks("issue", books);
	//printf("%d\n%s", size, books->book.bookTitle);
	//int size = getWishListInfo("tosen", books);
	//printf("%d\n%s",size, books->book.id);
	//struct bookInfo book = {
	//.id = "issueNo2",
	//.bookTitle = "New Title",
	//.author = "Ayush"
	//};
	//int ret = issueBook("token", book, 123123);
	//printf("%d\n", ret);
	//sleep(10);
	//ret = returnBook("token", "issueNo2");
	//printf("%d\n", ret);
	//int ret = issueBookByID("tokentok", "issueNo4");
	//printf("%d\n", ret);
	//int ret = returnBook("token2", "issueNo4");
	//printf("%d\n", ret);
	//struct users* userslist = (struct users*) malloc(sizeof(struct users*));
	//int ret = viewUsers(userslist);
	//printf("%d\n%s", ret, userslist->username);
	//int ret = deleteTokenPermanently("ayushsumanyo");
	//printf("%d\n", ret);
	//int ret = registerUser("aush", "abcDef123", "abcDef123");
	//printf("%d\n", ret);
}

// ##########################################################################################################################

int buyBooksFromMarket(char* id, char* issueID, int quantity){
	struct bookClass* book = (struct bookClass*) malloc(sizeof(struct bookClass));
	int ret = getBookByID(issueID, book);
	if(ret != 1){
		return ret;
	}
	free(book);
	struct bookVendors* vbook = (struct bookVendors*) malloc(sizeof(struct bookVendors));
	int r = viewBookFromMarketByID(id, vbook);
	if(r==-1){
		return -1;
	}
	else if(r==1){
		return 2;
	}
	FILE* fp;
	fp = fopen("Server/bookStore.txt", "a");
	if(fp==NULL){
		return -1;
	}
	fputs(issueID, fp);
	fputs("\n", fp);
	fputs(vbook->bookTitle, fp);
	fputs(vbook->author, fp);
	char quan[50];
	sprintf(quan, "%d", quantity);
	fputs(quan, fp);
	fputs("\n", fp);
	fputs("0", fp);
	free(vbook);
	fclose(fp);
	return 1;
}

int viewBookFromMarketByID(char*  id, struct bookVendors* book){
	FILE* fp;
	fp = fopen("Server/bookMarket.txt", "r");
	if(fp==NULL){
		return -1;
	}
	char line[50];
	int s = 0;
	int linenum=0;
	while(fgets(line, 50, fp)){
		if(linenum%4==0){
			line[strlen(line)-1] = '\0';
			if(strcmp(line, id)==0){
				strcpy(book->id, line);
				fgets(line, 50, fp);
				strcpy(book->bookTitle, line);
				fgets(line, 50, fp);
				strcpy(book->author, line);
				fgets(line, 50, fp);
				strcpy(book->vendor, line);
				fclose(fp);
				return 0;
			}
		}
	}
	return 1;
}

int getBookFromMarketByID(char* id, struct bookVendors* book){
	return viewBookFromMarketByID(id, book);
}

int viewBooksFromMarket(struct bookVendorList* books){
	FILE* fp;
	fp = fopen("Server/bookMarket.txt", "r");
	if(fp==NULL){
		return -1;
	}
	char line[50];
	int s = 0;
	while(fgets(line, 50, fp)){
		s++;
		strcpy(books->book.id, line);
		fgets(line, 50, fp);
		strcpy(books->book.bookTitle, line);
		fgets(line, 50, fp);
		strcpy(books->book.author, line);
		fgets(line, 50, fp);
		strcpy(books->book.vendor, line);
		books->next = (struct bookVendorList*) malloc(sizeof(struct bookVendorList));
		books = books->next;
	}
	fclose(fp);
	return s;
}

int getBooksFromMarket(struct bookVendorList* books){
	return viewBooksFromMarket(books);
}
	
int viewBookByID(char* id, struct bookClass* book){
	return getBookByID(id, book);
}

void allUsersScreen(){
	struct users* userlist = (struct users*) malloc(sizeof(struct users*));
	struct users* last = userlist;
	int size = getAllUsers(userlist);
	if(size == -1){
		printf("Something went wrong\n");
		sleep(1);
		free(userlist);
		newScreen(homeScreenAdmin);
		return;
	}
	printf("Following are all the registered memebers of the library\n");
	for(int i=0;i<size;i++){
		printf("%s", last->username);
		last = last->next;
	}
uopti:	printf("\nPress 1 to select a user\n");
	printf("Press 2 to go to the main page\n");
	char rs[50];
	char usern[50];
	scanf("%s", rs);
	int r = atoi(rs);
	if(r==1){
		printf("Enter the username exactly as it to select it\n");
		scanf("%s", usern);
		struct users* l = userlist;
		for(int i=0; i<size; i++){
			l->username[strlen(l->username)-1]='\0';
			int cmp = strcmp(usern, l->username);
			if(cmp==0){
				goto userse;
			}
			l = l->next;
		}

	} else if(r==2){
		newScreen(homeScreenAdmin);
		return;
	} else {
		printf("NOT A VALID ENTRY!\nEnter Again:\n");
		goto uopti;
	}
userse: printf("Press 1 to delete the user %s\n", usern);
	printf("**note: You might lose books if you remove a member which has not returned the books yet\n");
	printf("Press 2 to go back\n");
	char ps[50];
	scanf("%s", ps);
	int p = atoi(ps);
	if(p==1){
		removeUser(usern);
		return;
	} else if(p==2){
		return;
	} else {
		printf("NOT A VALID ENTRY!\nEnter Again:\n");
		goto userse;
	}

}

int viewUsers(struct users* userlist){
	FILE* fp;
	fp = fopen("Server/tokenStore.txt", "r");
	if(fp == NULL){
		return -1;
	}
	struct users* user = userlist;
	char line[20];
	int size = 0;
	while(fgets(line, 20, fp)){
		strcpy(user->username, line);
		user->next = (struct users*) malloc(sizeof(struct users));
		user = user->next;
		size++;
		fgets(line, 20, fp);
		fgets(line, 20, fp);
	}
	fclose(fp);
	return size;
}

int searchUsers(char* suser, struct users* userlist){
	int ulen = strlen(suser);
	FILE* fp;
	fp = fopen("Server/tokenStore.txt", "r");
	if(fp == NULL){
		return -1;
	}
	struct users* user = userlist;
	char line[20];
	int size = 0;
	while(fgets(line, 20, fp)){
		int llen = strlen(line);
		for(int i=0; i<(llen-ulen);i++){
			int cmp = strncmp(suser, &line[i], ulen);
			if(cmp==0){
				size++;
				strcpy(userlist->username, line);
				userlist->next = (struct users*) malloc(sizeof(struct users));
				userlist = userlist->next;
				break;
			}
		}
	}
	return size;

}

void searchUsersScreen(){
	printf("Type in your search:\n");
	char userss[50];
	scanf("%s", userss);
	struct users* userlist = (struct users*) malloc(sizeof(struct users*));
	struct users* last = userlist; 
	int size = searchUsers(userss, userlist);
	for(int i=0; i<size; i++){
		printf("%s", last->username);
		last = last->next;
	}
uoptir:	printf("\nPress 1 to select a user\n");
	printf("Press 2 to search again\n");
	printf("Press 3 to go to the main page\n");
	char rs[50];
	char usern[50];
	scanf("%s", rs);
	int r = atoi(rs);
	if(r==1){
		printf("Enter the username exactly as it to select it\n");
		scanf("%s", usern);
		struct users* l = userlist;
		for(int i=0; i<size; i++){
			l->username[strlen(l->username)-1]='\0';
			int cmp = strcmp(usern, l->username);
			if(cmp==0){
				goto userser;
			}
			l = l->next;
		}

	} else if(r==2){
		return;
	} else if(r==3){
		newScreen(homeScreenAdmin);
		return;
	}else{
		printf("NOT A VALID ENTRY!\nEnter Again:\n");
		goto uoptir;
	}
userser: printf("Press 1 to delete the user %s\n", usern);
	printf("**note: You might lose books if you remove a member which has not returned the books yet\n");
	printf("Press 2 to go back\n");
	char ps[50];
	scanf("%s", ps);
	int p = atoi(ps);
	if(p==1){
		removeUser(usern);
		return;
	} else if(p==2){
		return;
	} else {
		printf("NOT A VALID ENTRY!\nEnter Again:\n");
		goto userser;
	}
}

int getAllUsers(struct users* userlist){
	return viewUsers(userlist);	
}

int removeUser(char* username){
	return deleteTokenPermanently(username);	
}

int deleteMyAccount(char* username){
	int ret = deleteTokenPermanently(username);
	if(ret!=0){
		return ret;
	}
	deleteToken();
	return 0;
}

int deleteTokenPermanently(char* username){
	FILE* fp;
	fp = fopen("Server/tokenStore.txt", "r");
	if(fp==NULL){
		return -1;
	}
	struct txtFile* original = (struct txtFile*) malloc(sizeof(struct txtFile));
	struct txtFile* txtfile = original;
	struct txtFile* last = txtfile;
	int filesize = 0;
	char line[20];
	while(fgets(line, 20, fp)){
		strcpy(last->line, line);
		filesize++;
		last->next = malloc(sizeof(struct txtFile));
		last = last->next;
	}
	fp = freopen("Server/tokenStore.txt", "w", fp);
	for(int i=0; i<filesize;i++){
		if(i!=0){fputs("\n", fp);}

		txtfile->line[strlen(txtfile->line)-1]='\0';
		if(strcmp(txtfile->line, username)==0){
			for(int j=0; j<3; j++){
				i++;
				txtfile = txtfile->next;
			}
		i++;
		txtfile->line[strlen(txtfile->line)-1]='\0';
		}
		fputs(txtfile->line, fp);
				txtfile = txtfile->next;
	}
	for(int i=0; i<filesize; i++){
		free(original);
		original = original->next;
	}
	fclose(fp);
	return 0;
}

void deleteToken(){
	FILE* fp;
	fp = fopen("Local/token.txt","w");
	fclose(fp);
}

void logout(){
	deleteToken();
}


void searchScreen(){
	printf("Type in your search:\n");
	char searchText[500];
	scanf("%s", searchText);
	searchText[49]='\0';
	struct bookList* books = (struct bookList*) malloc(sizeof(struct bookList));
	int size = search(searchText, books);
	struct bookList* last = books;
	for(int i=0; i<size; i++){
		printf("%d.\n", (i+1));
		printf("Issue No: %s", last->book.id);
		printf("Book Title: %s\n", last->book.bookTitle);
		printf("Author: %s\n", last->book.author);
		printf("Quanitity: %d\n", last->book.quantity);
		printf("No of Books Issued: %d\n\n", last->book.issued);
		last = last->next;
	}
searchoption:	printf("\nPress 1 to search again\n");
	printf("Press 2 to select a book from the result\n");
	printf("Press 3 to go to main page\n");
	char rs[50];
	scanf("%s", rs);
	int r = atoi(rs);
	if(r==1){
		return;
	} else if(r==2){
		printf("Enter the Issue No exactly as it is of the book that you want to select:\n");
		char issue[500];
		scanf("%s", issue);
		issue[49]= '\0';
		struct bookClass* book = (struct bookClass*) malloc(sizeof(struct bookClass));
		int getb = viewBookByID(issue, book);
		printf("%d\n", getb);
		if(getb==-1){
			printf("Something went wrong\n");
			printf("Try Again\n");
			free(book);
			goto searchoption;
		} else if(getb==0){
			if(book->quantity > book->issued){
				printf("Do you want to issue this book?\n\n");
				printf("Issue No: %s\n", book->id);
				printf("Book Title: %s\n", book->bookTitle);
				printf("Author: %s\n", book->author);
issueoption:				printf("\nPress 1 to issue the book\n");
				printf("Press 2 to go back\n");
				char ps[50];
				scanf("%s", ps);
				int p = atoi(ps);
				if(p==1){
					int g = issueBookByID(book->id);
					if(g==0){
						printf("Book Issued Successfully\n");
						sleep(2);
						free(book);
						newScreen(homeScreen);
						return;
					} else if(g==-1){
						printf("Something went Wrong\n");
						printf("Try Again\n");
					} else if(g==1){
						printf("Book Not Availabe\n");
						printf("Try Again\n");
					} else if(g==-2){
						newScreen(systemCrash);
						return;
					} else if(g==2){
						printf("Book already issued\n");
					}
					free(book);
					sleep(2);
					goto searchoption;
				} else if(p==2){
					free(book);
					goto searchoption;
				} else {
					printf("NOT A VALID ENTRY!\nEnter Again:\n");
					goto issueoption;
				}
			} else{
				printf("Book is not available for now.\n\n");
				printf("Issue No: %s\n", book->id);
				printf("Book Title: %s\n", book->bookTitle);
				printf("Author: %s\n", book->author);
				sleep(2);
				free(book);
				goto searchoption;
			}
		} else {
			printf("\nNo such book\n");
			free(book);
			goto searchoption;
		}

	} else if(r==3){
		newScreen(homeScreen);
	} else{
		printf("NOT A VALID ENTRY!\nEnter Again:\n");
		goto searchoption;
	}
}

void searchScreenAdmin(){
	printf("Type in your search:\n");
	char searchText[500];
	scanf("%s", searchText);
	searchText[49]='\0';
	struct bookList* books = (struct bookList*) malloc(sizeof(struct bookList));
	int size = search(searchText, books);
	struct bookList* last = books;
	for(int i=0; i<size; i++){
		printf("%d.\n", (i+1));
		printf("Issue No: %s", last->book.id);
		printf("Book Title: %s\n", last->book.bookTitle);
		printf("Author: %s\n", last->book.author);
		printf("Quanitity: %d\n", last->book.quantity);
		printf("No of Books Issued: %d\n\n", last->book.issued);
		last = last->next;
	}
searchadminoption:	printf("\nPress 1 to search again\n");
		printf("Press 2 to go to main page\n");
		char rs[50];
		scanf("%s", rs);
		int r = atoi(rs);
		if(r==1){
			return;
		}else if(r==2){
			newScreen(homeScreenAdmin);
		} else{
			printf("NOT A VALID ENTRY!\nEnter Again:\n");
			goto searchadminoption;
		}

}

int returnIssued(char* id){
	char token[20];
	int ret = getToken(token);
	if(ret == -1){
		return -1;
	}
	return returnBook(token, id);
}

void dueBooks(){
	char token[50];
	int ret = getToken(token);
	int s = 0;
	struct bookInfoList* books = (struct bookInfoList*) malloc(sizeof(struct bookInfoList));
	struct bookInfoList* last = books;
	int size = getIssuedBookInfo(token, books);
	time_t t = time(NULL);
	struct bookInfoList* booklist = (struct bookInfoList*) malloc(sizeof(struct bookInfoList));
	struct bookInfoList* head = booklist;
	for(int i=0; i<size; i++){
		if((t-last->time)>1296000){
			printf("%ld", (last->time-t));
			s++;
			strcpy(head->book.id, last->book.id);
			strcpy(head->book.bookTitle, last->book.bookTitle);
			strcpy(head->book.author, last->book.author);
			head->time = last->time;
			head->next = (struct bookInfoList*) malloc(sizeof(struct bookInfoList));
			head = head->next;
		}
		last = last->next;
	}
	for(int i=0; i<size; i++){
		free(books);
		books = books->next;
	}
	createNotification(s, booklist);
}

void newScreen(void (*screen)()){
	SCREEN = screen;
}

void splashScreen(){
	printf("WELCOME TO E-LIBRARY PORTAL\n\n");
	printf("Loading\n");
	sleep(1);
	printf(".\n");
	sleep(1);
	printf(".\n");
	sleep(1);
	printf(".\n");
	sleep(1);
	strcpy(USERNAME, getCurrentUser());
	if(USERNAME[0] == '\0'){
		newScreen(welcomeScreen);
	}else{
		newScreen(homeScreen);
	}
}


void welcomeScreen(){
	printf("WELCOME TO E-LIBRARY PORTAL\n\n");
option:	printf("If you are an old user, Press 1 to Log In\n");
	printf("If you are a new user, Press 2 to Register\n");
	printf("If you are the admin, Press 3 to Log In as Admin\n");
	printf("To exit from the program, Press 4\n\n");
	char rs[50];
	scanf("%s", rs);
	int r = atoi(rs);
	if(r==1){
		newScreen(loginUI);
	} else if(r==2){
		newScreen(registerUI);
	} else if(r==3){
		newScreen(loginAsAdminUI);
	} else if(r==4){
		exit(0);
	} else {
		printf("NOT A VALID ENTRY!\nEnter Again:\n");
		goto option;
	}
}

void issuedBookUI(){
	struct bookInfoList* books = (struct bookInfoList*) malloc(sizeof(struct bookInfoList));
	int size = getAllIssuedBooks(books);
	struct bookInfoList* last = books;
	if(size ==-1){
		printf("Something Went Wrong");
		newScreen(homeScreen);
		sleep(2);
	}
	printf("Following are the books issued by you\n\n");
	for(int i = 0; i<size; i++){
		printf("%d\n", i+1);
		printf("Issue No: %s\n", last->book.id);
		printf("Book Title: %s\n", last->book.bookTitle);
		printf("Author: %s\n", last->book.author);
		char* ti = ctime(&(last->time));
		printf("Issued at: %s\n\n", ti);
		last = last->next;
	}
	for(int i=0; i<size; i++){
		free(books);
		books = books->next;
	}
issoption:	printf("Press 1 to select a book\n");
	printf("Press 2 to go to main page\n");
	char rs[50];
	scanf("%s", rs);
	int r = atoi(rs);
	if(r==1){
		printf("Enter the Issue No of the book that you want to return exactly as it is\n");
		char issuen[50];
		scanf("%s", issuen);
		int ret = returnIssued(issuen);
		if(ret==1){
			printf("No such book issued\n");
			printf("Try again\n");
			goto issoption;
		} else if(ret == -1){
			printf("Something went wrong\n");
			printf("Try again\n");
			goto issoption;
		} else if(ret == -2){
			newScreen(systemCrash);
			return;
		} else {
			printf("Book returned successfully to the library\n");
			sleep(2);
			return;
		}
	} else if(r==2){
		newScreen(homeScreen);
	} else{
		printf("NOT A VALID ENTRY!\nEnter Again:\n");
		goto issoption;
	}

}

void settingsScreen(){
	printf("**note: Upcoming feature--password change**\n\n");
setopt:	printf("Press 1 to delete your account\n");
	printf("Press 2 to return to the main page\n");
	char rs[50];
	scanf("%s", rs);
	int r = atoi(rs);
	if(r==1){
		struct bookInfoList* books = (struct bookInfoList*) malloc(sizeof(struct bookInfoList));
		int s = getAllIssuedBooks(books);
		if(s>0){
			printf("You have not returned few issued books\n");
			printf("Return all books to successfully delete your membership\n");
			sleep(4);
			newScreen(homeScreen);
			return;
		}else{
			int ret = deleteMyAccount(USERNAME);
			if(ret ==-1){
				printf("Something went wrong\n");
				sleep(1);
				return;
			}
			newScreen(welcomeScreen);
			return;
		}
	} else if(r==2){
	
	} else {
		printf("NOT A VALID ENTRY!\nEnter Again:\n");
		goto setopt;
	}
}

void createNotification(int size, struct bookInfoList* books){
	if(size>0){
	printf("You have %d books due\n", size);
	printf("Kindly return the following books to the library\n");
	for(int i = 0; i<size; i++){
		printf("%d\n", i+1);
		printf("Issue No: %s\n", books->book.id);
		printf("Book Title: %s\n", books->book.bookTitle);
		printf("Author: %s\n", books->book.author);
		char* ti = ctime(&(books->time));
		printf("Issued at: %s\n\n", ti);
		books = books->next;
	}
	}
}

void homeScreen(){
	printf("WELCOME %s\n\n", USERNAME);
	printf("This is your online portal to the library\n");
	dueBooks();
homeoption:	printf("Press 1 to search for books\n");
	printf("Press 2 to view all the available books\n");
	printf("Press 3 to view books issued by you\n");
	printf("Press 4 to go to settings page\n");
	printf("Press 5 to Log Out\n");
	printf("Press 6 to exit program\n\n");
	char rs[50];
	scanf("%s", rs);
	int r = atoi(rs);
	if(r==1){
		newScreen(searchScreen);
	} else if(r==2){
		newScreen(bookStoreUI);
	} else if(r==3){
		newScreen(issuedBookUI);	
	} else if(r==4){
		newScreen(settingsScreen);
	} else if(r==5){
		logout();
		newScreen(welcomeScreen);	
	} else if(r==6){
		exit(0);
	} else {
		printf("NOT A VALID ENTRY!\nEnter Again:\n");
		goto homeoption;

	}
}

void bookStoreUIAdmin(){
		struct bookList* books = (struct bookList*) malloc(sizeof(struct bookList));
		int s = search("", books);
		struct bookList* last = books;
		for(int i=0; i<s; i++){
			printf("%d\n", i+1);
			printf("Issue No: %s", last->book.id);
			printf("Book Title: %s\n", last->book.bookTitle);
			printf("Author: %s\n", last->book.author);
			printf("Quantity: %d\n", last->book.quantity);
			printf("No of books issued: %d\n\n", last->book.issued);
			last = last->next;
		}
		if(s==-1){
			printf("Something went wrong\n");
			sleep(2);
			newScreen(homeScreenAdmin);
			return;
		}
opti:		printf("Press 1 to go to main page");
		char inp[50];
		scanf("%s", inp);
		int is = atoi(inp); 
		if(is==1){
			newScreen(homeScreenAdmin);
			return;
		} else {
			printf("NOT A VALID ENTRY!\nEnter Again:\n");
			goto opti;
		}


}

void bookStoreUI(){
		struct bookList* books = (struct bookList*) malloc(sizeof(struct bookList));
		int s = search("", books);
		struct bookList* last = books;
		for(int i=0; i<s; i++){
			printf("%d\n", i+1);
			printf("Issue No: %s", last->book.id);
			printf("Book Title: %s\n", last->book.bookTitle);
			printf("Author: %s\n", last->book.author);
			printf("Quantity: %d\n", last->book.quantity);
			printf("No of books issued: %d\n\n", last->book.issued);
			last = last->next;
		}

		if(s==-1){
			printf("Something went wrong\n");
			sleep(2);
			newScreen(homeScreen);
			return;
		}
homeop:		printf("\nPress 1 to select a book\n");
		printf("Press 2 to go to main page\n");
		char rs[50];
		scanf("%s", rs);
		int r = atoi(rs);
		if(r==1){
			printf("Enter the Issue No exactly as it is of the book that you want to select:\n");
			char issue[500];
			scanf("%s", issue);
			issue[49]= '\0';
			struct bookClass* book = (struct bookClass*) malloc(sizeof(struct bookClass));
			int getb = viewBookByID(issue, book);
			if(getb==-1){
				printf("Something went wrong\n");
				printf("Try Again\n");
				free(book);
				goto homeop;
			} else if(getb==0){
				if(book->quantity > book->issued){
					printf("Do you want to issue this book?\n\n");
					printf("Issue No: %s\n", book->id);
					printf("Book Title: %s\n", book->bookTitle);
					printf("Author: %s\n", book->author);
issuesoption:				printf("\nPress 1 to issue the book\n");
					printf("Press 2 to go back\n");
					char ps[50];
					scanf("%s", ps);
					int p = atoi(ps);
					if(p==1){
						int g = issueBookByID(book->id);
						if(g==0){
							printf("Book Issued Successfully\n");
							sleep(2);
							free(book);
							newScreen(homeScreen);
							return;
						} else if(g==-1){
							printf("Something went Wrong\n");
							printf("Try Again\n");
						} else if(g==1){
							printf("Book Not Availabe\n");
							printf("Try Again\n");
						} else if(g==-2){
							newScreen(systemCrash);
							return;
							return;
						} else if(g==2){
							printf("Book already issued\n");
						}
						free(book);
						sleep(2);
						goto homeop;
					} else if(p==2){
						free(book);
						goto homeop;
					} else {
						printf("NOT A VALID ENTRY!\nEnter Again:\n");
						goto issuesoption;
					}
				} else{
					printf("Book is not available for now.\n\n");
					printf("Issue No: %s\n", book->id);
					printf("Book Title: %s\n", book->bookTitle);
					printf("Author: %s\n", book->author);
					sleep(2);
					free(book);
					goto homeop;
				}
			} else {
				printf("\nNo such book\n");
				free(book);
				goto homeop;
			}
		} else if(r==2){
			newScreen(homeScreen);
			return;
		} else	{
			printf("NOT A VALID ENTRY!\nEnter Again:\n");
			goto homeop;
		}
}


void homeScreenAdmin(){
	printf("Welcome %s\n", USERNAME);
	printf("Manage the library through this online portal\n");
homeadminoption:	printf("Press 1 to search for books\n");
	printf("Press 2 to view all the books\n");
	printf("Press 3 to search for users\n");
	printf("Press 4 to list all the users\n");
	printf("Press 5 to buy books from vendors\n");
	printf("Press 6 to Log Out\n");
	printf("Press 7 to exit the program\n\n");
	char rs[50];
	scanf("%s", rs);
	int r = atoi(rs);
	if(r==1){
		newScreen(searchScreenAdmin);
	} else if(r==2){
		newScreen(bookStoreUIAdmin);
	} else if(r==3){
		newScreen(searchUsersScreen);
	} else if(r==4){
		newScreen(allUsersScreen);
	} else if(r==5){
		newScreen(bookMarketUI);
	} else if(r==6){
		logout();
		newScreen(welcomeScreen);
	} else if(r==7){
		exit(0);
	} else{
		printf("NOT A VALID ENTRY!\nEnter Again:\n");
		goto homeadminoption;

	}

}

void systemCrash(){
	printf("System Crashed due to unexpected failure\n");
	printf("Kindly restore the Server from the backup folder\n");
	sleep(4);
	exit(0);
}

void bookMarketUI(){
	struct bookVendorList* books = (struct bookVendorList*) malloc(sizeof(struct bookVendorList));
	struct bookVendorList* last = books;
	int ret = getBooksFromMarket(books);
	if(ret == -1){
	printf("Something went wrong\n");
	sleep(2);
	newScreen(homeScreenAdmin);
	return;
	}
	printf("Following are the books available in the market\n\n");
	for(int i = 0; i<ret; i++){
		printf("%d\n", i+1);
		printf("Book ID: %s", last->book.id);
		printf("Book Title: %s", last->book.bookTitle);
		printf("Author: %s", last->book.author);
		printf("Vendor: %s\n", last->book.vendor);
		last=last->next;
	}
venopt:	printf("\nPress 1 to buy a book\n");
	printf("Press 2 to go to the main page\n");
	char ps[50];
	scanf("%s", ps);
	int p = atoi(ps);
	if(p==1){
		printf("\nEnter the id of the book that you want to buy exactly as it is\n");
		char ide[50];
		scanf("%s", ide);
		printf("Enter an issueID that you want to give to the book. Must be unique\n");
		char issueide[50];
		scanf("%s", issueide);
		char quae[50];
		int qua = 0;
entquat:	printf("Enter the quantity of book that you want to purchase\n");
		scanf("%s", quae);
		qua = atoi(quae);
		if(qua==0){
			printf("Not a valid quantity\n");
			goto entquat;
		}
		int getr = buyBooksFromMarket(ide, issueide, qua);
		if(getr == -1){
			printf("Something went wrong\n");
			goto venopt;
		} else if(getr == 0){
			printf("Issue ID given already exists\n");
			goto venopt;
		} else if(getr == 2){
			printf("No such book in the market\n");
			goto venopt;
		} else {
			printf("Book purchased successfully!\n");
			sleep(2);
			newScreen(homeScreenAdmin);
			return;
		}
	} else if(p==2){
		newScreen(homeScreenAdmin);
		return;
	} else {
		printf("NOT A VALID ENTRY!\nEnter Again\n");
		goto venopt;
	}
}

void loginAsAdminUI(){
	char username[500];
	char password[500];
	printf("Enter Username:\n");
	scanf("%s", username);
	printf("Enter Password:\n");
	scanf("%s", password);
	username[49]='\0';
	password[49]='\0';
	int ret = loginAsAdmin(username, password);
	if(ret==0){
		printf("Logged In\n");
		newScreen(homeScreenAdmin);
	}else{
		printf("Incorrect username or password\n");
loginOption:	printf("Press 1 to try again\nPress 2 to return to Welcome page\n");
		char rs[50];
		scanf("%s", rs);
		int r = atoi(rs);
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

void loginUI(){
	char username[500];
	char password[500];
	printf("Enter Username:\n");
	scanf("%s", username);
	printf("Enter Password:\n");
	scanf("%s", password);
	username[49]='\0';
	password[49]='\0';
	int ret = login(username, password);
	if(ret==0){
		printf("Logged In\n");
		sleep(1);
		newScreen(homeScreen);
	}else{
		printf("Incorrect username or password\n");
loginOption:	printf("Press 1 to try again\nPress 2 to return to Welcome page\n");
		char rs[50];
		scanf("%s", rs);
		int r = atoi(rs);
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
	char username[500];
	char password[500];
	char passwordc[500];
enter:	printf("Enter New Username:\n");
	scanf("%s", username);
	printf("Enter Password:\n");
	scanf("%s", password);
	printf("Enter the password again:\n");
	scanf("%s", passwordc);
	username[49]='\0';
	password[49]='\0';
	passwordc[49]='\0';
	int ret = registerUser(username, password, passwordc);
	if(ret == 0){
		printf("User successfully registered\n");
		sleep(2);
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
		char rs[50];
		scanf("%s", rs);
		int r = atoi(rs);
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
		deleteToken();
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
				linenum--;
				linenum--;
				for(int m=0; m<=linenum;m++){
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
	strcpy(USERNAME, username);
    	return saveToken(token);
	
}

int loginAsAdmin(char* username, char* password){
    	int salt = generateSalt(username);
    	int64 p_hash = generateSaltedHash(password, salt);
    	char token[50];
    	int ret = verifyCredentialsForAdmin(username, p_hash, token);
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

int verifyCredentialsForAdmin(char* username, int64 hash, char* token){
	int ulen =  strlen(username);
	char ha[50];
	int hlen = sprintf(ha, "%llu", hash);
	FILE* fp;
	fp = fopen("Server/adminTokenStore.txt", "r");
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
	char line[50];
	int linenum=0;
	while(fgets(line, 50, fp)){
		if((linenum%5)==0){
			line[strlen(line)-1]='\0';
			int cmp = strcmp(id, line);
			if(cmp==0){
				strcpy(book->id, line);	
				fgets(line, 50, fp);
				line[strlen(line)-1]='\0';
				strcpy(book->bookTitle, line);	
				fgets(line, 50, fp);
				line[strlen(line)-1]='\0';
				strcpy(book->author, line);	
				fgets(line, 50, fp);
				line[strlen(line)-1]='\0';
				book->quantity = atoi(line);
				fgets(line, 50, fp);
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

int search(char* book, struct bookList* books){
	return searchBooks(book, books);
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
	char line[50];
	int blocknum=0;
	while(fgets(line, 50, fp)){
nextblock:	for(int i=0; i<5; i++){
			int llen = strlen(line);
			if(llen>blen){
				for(int i=0; i<llen-blen; i++){
					int cmp = strncmp(book, &line[i], blen);
					if(cmp==0){
						rewind(fp);
						for(int j=0; j<=blocknum*5; j++){
							fgets(line, 50, fp);
						}
						size++;
						booklist->next = (struct bookList*) malloc(sizeof(struct bookList));
						strcpy(booklist->book.id, line);	
						fgets(line, 50, fp);
						line[strlen(line)-1]='\0';
						strcpy(booklist->book.bookTitle, line);	
						fgets(line, 50, fp);
						line[strlen(line)-1]='\0';
						strcpy(booklist->book.author, line);	
						fgets(line, 50, fp);
						line[strlen(line)-1]='\0';
						booklist->book.quantity = atoi(line);
						fgets(line, 50, fp);
						line[strlen(line)-1]='\0';
						booklist->book.issued = atoi(line);
						booklist = booklist->next;
						if(fgets(line, 50, fp)){
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
	return size;

}

int getWishListInfo(char* token, struct bookInfoList* books){
	FILE* fp;
	fp = fopen("Server/wishList.txt", "r");
	if(fp==NULL){
		return -1;
	}
	int tokenline=1;
	char line[50];
	while(fgets(line, 50, fp)){
		if(tokenline==1){
			line[strlen(line)-1]='\0';
			int cmp = strcmp(token, line);
			if(cmp==0){
				int size = 0;
				struct bookInfoList* booklist = books;
				fgets(line, 50, fp);
				while(1){
					booklist->next = (struct bookInfoList*) malloc(sizeof(struct bookInfoList));
					line[strlen(line)-1]='\0';
					strcpy(booklist->book.id, line);
					fgets(line, 50, fp);
					line[strlen(line)-1]='\0';
					strcpy(booklist->book.bookTitle, line);
					fgets(line, 50, fp);
					line[strlen(line)-1]='\0';
					strcpy(booklist->book.author, line);
					size++;
					booklist = booklist->next;
					fgets(line, 50, fp);
					if(strcmp(line, "\n")==0){
						fclose(fp);
						return size;
					}
				}
			}

		
		}
		if(line[0] =='\n'){
			tokenline = 1;
		}else{
			tokenline = 0;
		}

	}
	fclose(fp);
	return 0;
}

int getAllIssuedBooks(struct bookInfoList* books){
	char token[50];
	int ret = getToken(token);
	if(ret==-1){
		return -1;
	}
	return getIssuedBookInfo(token, books);


}

int getIssuedBookInfo(char* token, struct bookInfoList* books){
	FILE* fp;
	fp = fopen("Server/issuedBooks.txt", "r");
	if(fp==NULL){
		return -1;
	}
	int tokenline=1;
	char line[50];
	while(fgets(line, 50, fp)){
		if(tokenline==1){
			line[strlen(line)-1]='\0';
			int cmp = strcmp(token, line);
			if(cmp==0){
				int size = 0;
				struct bookInfoList* booklist = books;
				fgets(line, 50, fp);
				while(1){
					booklist->next = (struct bookInfoList*) malloc(sizeof(struct bookInfoList));
					line[strlen(line)-1]='\0';
					strcpy(booklist->book.id, line);
					fgets(line, 50, fp);
					line[strlen(line)-1]='\0';
					strcpy(booklist->book.bookTitle, line);
					fgets(line, 50, fp);
					line[strlen(line)-1]='\0';
					strcpy(booklist->book.author, line);
					fgets(line, 50, fp);
					line[strlen(line)-1]='\0';
					booklist->time = atoi(line);
					size++;
					booklist = booklist->next;
					fgets(line, 50, fp);
					if(strcmp(line, "\n")==0){
						fclose(fp);
						return size;
					}
				}
			}

		
		}
		if(line[0] =='\n'){
			tokenline = 1;
		}else{
			tokenline = 0;
		}

	}
	fclose(fp);
	return 0;
}

int issueBookByID(char* id){
	char token[20];
	int ret = getToken(token);
	if(ret == -1){
		return -1;
	}
	struct bookInfoList* books = (struct bookInfoList*) malloc(sizeof(struct bookInfoList));
	struct bookInfoList* list = books;
	int s = getIssuedBookInfo(token, books);
	for(int i=0; i<s; i++){
		if(strcmp(books->book.id, id) == 0){
			for(int i=0; i<s;i++){
				free(list);
				list = list->next;
			}	
			return 2;
		}
		books = books->next;
	}
	for(int i=0; i<s;i++){
		free(list);
		list = list->next;
	}
	time_t t = time(NULL);
	struct bookClass* book = (struct bookClass*) malloc(sizeof(struct bookClass));
	int r = getBookByID(id, book);
	struct bookInfo booki;
	strcpy(booki.id, book->id);
	strcpy(booki.bookTitle, book->bookTitle);
	strcpy(booki.author, book->author);
	free(book);
	return issueBook(token, booki, t);
}

int issueBook(char* token, struct bookInfo book, time_t time){
	FILE* fp;
	fp = fopen("Server/issuedBooks.txt", "r");
	if(fp==NULL){
		return -1;
	}
	int exists = 0;
	char line[50];
	int filesi = 0;
	struct txtFile* original = (struct txtFile*) malloc(sizeof(struct txtFile));
	struct txtFile* txtfile = original;
	struct txtFile* last = txtfile;
	while(fgets(line, 50, fp)){
		filesi++;
		last->next = (struct txtFile*) malloc(sizeof(struct txtFile));
		strcpy(last->line, line);
		last = last->next;
	}
	last->next = NULL;
	fp = freopen("Server/issuedBooks.txt", "w", fp);
	for(int i = 0; i<filesi; i++){
		fputs(txtfile->line, fp);
		txtfile->line[strlen(txtfile->line)-1] = '\0';
		if(strcmp(txtfile->line, token)==0){
			exists = 1;
			fputs(book.id, fp);
			fputs("\n", fp);
			fputs(book.bookTitle, fp);
			fputs("\n", fp);
			fputs(book.author, fp);
			fputs("\n", fp);
			char timeS[50];
			sprintf(timeS, "%ld", time);
			fputs(timeS, fp);
			fputs("\n", fp);
		}
		txtfile = txtfile->next;
	}
	if(exists == 0){
		fputs(token, fp);
		fputs("\n", fp);
		fputs(book.id, fp);
		fputs("\n", fp);
		fputs(book.bookTitle, fp);
		fputs("\n", fp);
		fputs(book.author, fp);
		fputs("\n", fp);
		char timeS[50];
		sprintf(timeS, "%ld", time);
		fputs(timeS, fp);
		fputs("\n", fp);
		fputs("\n", fp);

	}
	for(int i = 0; i<filesi; i++){
		free(original);
		original = original->next;
	}
	fp = freopen("Server/bookStore.txt", "r", fp);
	if(fp==NULL){
		return -2;
	}
	int filesize=0;
	struct txtFile* originals = (struct txtFile*) malloc(sizeof(struct txtFile));
	struct txtFile* txtfiles = originals;
	struct txtFile* lasts = txtfiles;
	while(fgets(line, 50, fp)){
		lasts->next = (struct txtFile*) malloc(sizeof(struct txtFile));
		strcpy(lasts->line, line);
		lasts = lasts->next;
		filesize++;
	}
	fp = freopen("Server/bookStore.txt", "w", fp);
	fputs(txtfiles->line, fp);
	for(int i=0; i<filesize; i++){

		if((i%5)==0){
			txtfiles->line[strlen(txtfiles->line)-1]='\0';
			if(strcmp(txtfiles->line, book.id)==0){
				txtfiles = txtfiles->next;
				fputs(txtfiles->line, fp);
				txtfiles = txtfiles->next;
				fputs(txtfiles->line, fp);
				txtfiles = txtfiles->next;
				fputs(txtfiles->line, fp);
				txtfiles = txtfiles->next;
				int issued = atoi(txtfiles->line);
				issued++;
				sprintf(txtfiles->line, "%d\n", issued);
				fputs(txtfiles->line, fp);
				for(int j=i; j<(filesize-5); j++){
					txtfiles=txtfiles->next;
					fputs(txtfiles->line, fp);
				}
				goto ending;
			}
	
		}
		txtfiles = txtfiles->next;	
		fputs(txtfiles->line, fp);

	}
ending:	for(int i=0; i<filesize; i++){
		free(originals);
		originals = originals->next;
	}
	fclose(fp);
	return 0;
}


int returnBook(char* token, char* id){
	FILE* fp;
	fp = fopen("Server/issuedBooks.txt", "r");
	if(fp == NULL){
		return -1;
	}
	int match=1;
	int success = 0;
	int exists = 0;
	int try = 0;
	char line[50];
	int filesi=0;
	struct txtFile* original = (struct txtFile*) malloc(sizeof(struct txtFile));
	struct txtFile* txtfile = original; 
	struct txtFile* last = txtfile;
	while(fgets(line, 50, fp)){
		filesi++;
		last->next = (struct txtFile*) malloc(sizeof(struct txtFile));
		strcpy(last->line, line);
		last = last->next;
	}
	fp = freopen("Server/issuedBooks.txt", "w", fp);
	for(int i=0; i<filesi; i++){
returnL:	fputs(txtfile->line, fp);
		if(strncmp(txtfile->line, token, strlen(token))==0){
returnLoop:		txtfile = txtfile->next;
			if(txtfile->line[0] != '\n'){
				try++;
				txtfile->line[strlen(txtfile->line)-1]='\0';
				if(strcmp(txtfile->line, id)==0){
					match=0;
					for(int j=0; j<4; j++){
						txtfile = txtfile->next;
						i++;
					}
					i++;
					success = 1;
					if((txtfile->line[0]=='\n')&&(try==1)){
						exists = 1;
					}
					goto returnL;
					
				}else{
				
					fputs(txtfile->line, fp);
					fputs("\n", fp);
					i++;
					goto returnLoop; 
				}
			}else{
				goto returnL;
			}
		}
		txtfile = txtfile->next;
	}
	for(int i=0; i<filesi; i++){
		free(original);
		original = original->next;
	}
	if(exists==1){
		fp = freopen("Server/issuedBooks.txt", "r", fp);
		original = (struct txtFile*) malloc(sizeof(struct txtFile));
		txtfile = original; 
		last = txtfile;
		int filesize=0;
		while(fgets(line, 50, fp)){
			filesize++;
			last->next = (struct txtFile*) malloc(sizeof(struct txtFile));
			strcpy(last->line, line);
			last = last->next;
		}
		fp = freopen("Server/issuedBooks.txt", "w", fp);
		for(int i=0; i<filesize-2; i++){
			if(strncmp(txtfile->line, token, strlen(token))==0){
				txtfile = txtfile->next;
				i++;
				txtfile = txtfile->next;
				i++;
			}
			fputs(txtfile->line,fp);
			txtfile = txtfile->next;
		}
		for(int i=0; i<filesize;i++){
			free(original);
			original=original->next;
		}
	}
	fclose(fp);
	if(success ==1){
	fp = fopen("Server/bookStore.txt", "r");
	if(fp==NULL){
		return -2;
	}
	int fils=0;
	original = (struct txtFile*) malloc(sizeof(struct txtFile));
	txtfile = original;
	last = txtfile;
	while(fgets(line, 50, fp)){
		fils++;
		last->next = (struct txtFile*) malloc(sizeof(struct txtFile));
		strcpy(last->line, line);
		last = last->next;
	}
	fp = freopen("Server/bookStore.txt", "w", fp);
	fputs(txtfile->line, fp);
	for(int i=0; i<fils; i++){
		if((i%5)==0){
			txtfile->line[strlen(txtfile->line)-1]='\0';
			if(strcmp(txtfile->line, id)==0){
				txtfile = txtfile->next;
				fputs(txtfile->line, fp);
				txtfile = txtfile->next;
				fputs(txtfile->line, fp);
				txtfile = txtfile->next;
				fputs(txtfile->line, fp);
				txtfile = txtfile->next;
				int issued = atoi(txtfile->line);
				issued--;
				sprintf(txtfile->line, "%d\n", issued);
				fputs(txtfile->line, fp);
				for(int j=i; j<(fils-5); j++){
					txtfile=txtfile->next;
					fputs(txtfile->line, fp);
				}
				goto ending;
			}
	
		}
		txtfile = txtfile->next;	
		fputs(txtfile->line, fp);

	}
ending:	for(int i=0; i<fils; i++){
		free(original);
		original = original->next;
	}	fclose(fp);
	}
	return match;

}





















