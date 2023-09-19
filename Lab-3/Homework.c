/*


 /$$   /$$                                                                     /$$              /$$$$$$
| $$  | $$                                                                    | $$             /$$__  $$
| $$  | $$  /$$$$$$  /$$$$$$/$$$$   /$$$$$$  /$$  /$$  /$$  /$$$$$$   /$$$$$$ | $$   /$$      |__/  \ $$
| $$$$$$$$ /$$__  $$| $$_  $$_  $$ /$$__  $$| $$ | $$ | $$ /$$__  $$ /$$__  $$| $$  /$$/        /$$$$$$/
| $$__  $$| $$  \ $$| $$ \ $$ \ $$| $$$$$$$$| $$ | $$ | $$| $$  \ $$| $$  \__/| $$$$$$/        /$$____/
| $$  | $$| $$  | $$| $$ | $$ | $$| $$_____/| $$ | $$ | $$| $$  | $$| $$      | $$_  $$       | $$
| $$  | $$|  $$$$$$/| $$ | $$ | $$|  $$$$$$$|  $$$$$/$$$$/|  $$$$$$/| $$      | $$ \  $$      | $$$$$$$$
|__/  |__/ \______/ |__/ |__/ |__/ \_______/ \_____/\___/  \______/ |__/      |__/  \__/      |________/

This function takes a single argument.
If that argument is a file, then do STUFF


*/

#include <stdio.h>

int main( int argc, char **argv[] ) { // argc = number of command line arguments ; argv[] = the index to select each argument (argv[1] is the fist argument.
  // no arguments - argc = 1

  //Variable Declaration


  // Main Functions

  // // Check arguments
  printf("\n=== Argument Check ===\n");
  if( argc == 2 ) {
    printf("Correct number of arguments\n");
  }
  else if( argc > 2 ) {
    printf("Too Many Arguments\n");
  }
  else {
    printf("Please enter an argument\n");
  }
  printf("\n");

  // // Check whether file exists
  printf("\n=== File Check ===\n");
  if (file = fopen(argv[2], "r")) {
    fclose(file);
    printf("File Exists\n");
  }
  else {
    printf("File Does Not Exist\n");
  }



  // End of program
  return 0;
}
