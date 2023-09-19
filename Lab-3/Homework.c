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
#include <getopt.h>

int debug( int argc, char **argv ) {



  return 0;
}

int main( int argc, char **argv ) { // argc = number of command line arguments ; argv[] = the index to select each argument (argv[1] is the fist argument.
  // no arguments - argc = 1

  // Variable Declaration


  // Main Functions




  // Debug

  // // Basic Arg Check
  printf("\n=== Initial Check ===\n");
  printf("Num args: %d\n", argc);
  printf("Arg 1: %s\n", argv[0]);
  printf("Arg 2: %s\n", argv[1]);
  printf("Arg 3: %s\n", argv[2]);


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
  FILE *file;
  if (file = fopen(argv[1], "r")) {
    fclose(file);
    printf("File Exists\n");
  }
  else {
    printf("File Does Not Exist\n");
  }
  printf("\n");

  // End of program
  return 0;
}
