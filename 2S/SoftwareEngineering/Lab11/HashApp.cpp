//This program is a driver for the myHash function used in the LoginApp.
//You can use it to generate hash codes

#include <iostream>
#include <string.h>
using namespace std;

void myHash(char *input, char *output) {
	//Sum ASCII codes
	unsigned int hashNum = 0;
	for (unsigned int index = 0; index < strlen(input); index++) {
		hashNum += input[index];
	}

//Convert to hex
	int temp = 0, counter = 0;
	while (hashNum != 0) {
		temp = hashNum % 16;
		if (temp < 10) {
			output[counter] = temp + 48;
		} else {
			output[counter] = temp + 55;
		}
		counter++;
		hashNum = hashNum / 16;
	}

//Reverse hex
	char tchar;
	int j = 0;
	int i = strlen(output) - 1;
	while (i > j) {
		tchar = output[i];
		output[i] = output[j];
		output[j] = tchar;
		i--;
		j++;
	}
}
int main(int argc, char *argv[]) {
	setbuf(stdout, NULL);

	char PlainText[4];
	char HashText[4];

	cout << "Please enter plain text :";
	cin >> PlainText;
	myHash(PlainText, HashText);
	cout << "\nCorresponding hash: " << HashText << endl;

}
