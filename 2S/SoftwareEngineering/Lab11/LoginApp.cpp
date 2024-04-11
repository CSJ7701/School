//This program demonstrates an exploit of buffer overflows.

/*
 * The code of this program (and HashApp) are available online as Replit repos:
 * 	LoginApp: https://bit.ly/MyLoginApp
 * 	HashApp: https://bit.ly/MyHashApp
*/

/* User names and passwords (plain and encrypted)
 * This table is NOT available to the bad actor

 * User Name    - Plain Password  - Password Hash
 *  root	        - 	rrr			  -  156
 *  ncage       	- 	nnn                       -  14A
 *  jbonjovi            - 	jjj		          -  13E
 *
 */

#include <iostream>
#include <string.h>
using namespace std;

class LoginModule {

private:
int userCount = 3; //Number of users in the system
char **userNames; // List of user names
char **hashedPasswords; // List of hashed password

/*
The retrieveHashedPassword function checks whether an input user name is among the
system user names, and outputs the corresponding password hash.
It returns false if the user is not found, true otherwise.
*/
bool retrieveHashedPassword(char *inputUsername, char *hashedPassword) {
	for (int index = 0; index < userCount; index++) {
		if (strcmp(inputUsername, userNames[index]) == 0) {
			strcpy(hashedPassword, hashedPasswords[index]);
			return true;
		}
	}
	return false;
}

public:
//A simple string-to-string hashing function
void myHash(char *input, char *output) {
	//Sum ASCII codes
	unsigned int hashNum = 0;
	for (unsigned int index = 0; index < strlen(input); index++)
		{hashNum += input[index];}

//Convert to hex
int temp=0, counter=0;
while (hashNum != 0) {
	temp= hashNum % 16;
	if (temp<10){output[counter]=temp+48;}else{output[counter]=temp+55;}
	counter++; hashNum = hashNum / 16;
}

//Reverse hex
char tchar; int j=0; int i = strlen(output)-1;
while (i>j) {tchar = output[i]; output[i]=output[j];output[j]=tchar;i--;j++;}
}

//The constructor allocates and initializes two arrays (userNames & hashedPasswords)
LoginModule() {
	setbuf(stdout, NULL);
	userNames = (char**) malloc(userCount * sizeof(char*));
	hashedPasswords = (char**) malloc(userCount * sizeof(char*));
	for (int index = 0; index < userCount; index++)
		{userNames[index] = (char*) malloc(4 * sizeof(char));
		hashedPasswords[index] = (char*) malloc(4 * sizeof(char));}

	strcpy(userNames[0], "root");	strcpy(hashedPasswords[0], "156");
	strcpy(userNames[1], "ncage");	strcpy(hashedPasswords[1], "14A");
	strcpy(userNames[2], "jbonjovi");	strcpy(hashedPasswords[2], "13E");
}

~LoginModule() 	{ // Free dynamically allocated memory
	for (int index = 0; index < userCount; index++)
		{free(userNames[index]);free(hashedPasswords[index]);}

	free(userNames);	free(hashedPasswords);
}


bool initiateLogin() {
	// For storing the hash of the password entered by the user.
	char hashedInputPass[4];

	// For storing the hash of the correct password of the user being authenticated.
	char hashedStoredPass[4];

	//For storing the plain text password as entered by the user.
	char inputPass[4];

	//For storing the user name entered by the user.
	char inputUsername[5];

	cout<< "Please enter your user name :";
	cin >> inputUsername;

	//Lookup the entered username in the list of known users
	bool foundUser = retrieveHashedPassword(inputUsername,	hashedStoredPass);
	if (!foundUser) {return false;} //If the user name is not known, the login fails

	cout << "\nPlease enter your password :";
	cin >> inputPass; //Get plain text password from the user

	myHash(inputPass, hashedInputPass); // Hash the plain text password

	cout << inputPass;
	cout << "\n";
	cout << hashedStoredPass;
	cout << "\n";
	cout << hashedInputPass;

	//if the hash of the entered password matches the hash of the user being authenticated,
	if(strcmp(hashedStoredPass, hashedInputPass)==0)
	 {return true;} // then login succeeds
	else
	 {return false;} // otherwise, it fails
}

};

int main(int argc, char* argv[]) {
LoginModule loginModule;

bool isAuthetnicated = loginModule.initiateLogin();

if (isAuthetnicated) {
	cout<< "\nAccess Granted!"<<endl;
} else {
	cout << "\nAccess Denied!"<<endl;
}

}
