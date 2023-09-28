/*

 /$$   /$$                                                                     /$$              /$$$$$$
| $$  | $$                                                                    | $$             /$$__  $$
| $$  | $$  /$$$$$$  /$$$$$$/$$$$   /$$$$$$  /$$  /$$  /$$  /$$$$$$   /$$$$$$ | $$   /$$      |__/  \ $$
| $$$$$$$$ /$$__  $$| $$_  $$_  $$ /$$__  $$| $$ | $$ | $$ /$$__  $$ /$$__  $$| $$  /$$/         /$$$$$/
| $$__  $$| $$  \ $$| $$ \ $$ \ $$| $$$$$$$$| $$ | $$ | $$| $$  \ $$| $$  \__/| $$$$$$/         |___  $$
| $$  | $$| $$  | $$| $$ | $$ | $$| $$_____/| $$ | $$ | $$| $$  | $$| $$      | $$_  $$        /$$  \ $$
| $$  | $$|  $$$$$$/| $$ | $$ | $$|  $$$$$$$|  $$$$$/$$$$/|  $$$$$$/| $$      | $$ \  $$      |  $$$$$$/
|__/  |__/ \______/ |__/ |__/ |__/ \_______/ \_____/\___/  \______/ |__/      |__/  \__/       \______/

Expected command format - ./Homework.out -d delay(#) -? -? -? File File File
 - All file names will follow options
 - Options can be in any order (this is getopt default)
 - File names should be only remaining arguments after options.




*/
#include <stdio.h>
#include <getopt.h>
#include <math.h>

// Check if file exists
// Returns error if not found
int exists( char *input ) {
  FILE *file;
  if ( file = fopen(input, "r")) {
    fclose(file);
    printf("File Exists\n");
    return 0;
  }
  else {
    printf("File \'%s\' not found.\n", input);
    return 1;
  }
}

// Sleeps program
// Can take input in fractional or full seconds.
int sleepp( float fsecs ) {
  int secs = (int)fsecs;

  if(ceilf(fsecs) == fsecs) {
    sleep(secs);
    return 0;
  }
  else {
    float sleep_dec = fsecs - floor(fsecs);
    float sleep_who = fsecs - sleep_dec;
    float sleep_mic = sleep_dec * 1000000;
    sleep(sleep_who);
    usleep(sleep_mic);
    return 0;
  }
  return 0;
}

// Reverses input line
int reverse( char *input ) {
  int length = 0;
  int rev_length;

  while (input[length] != '\0') {
    length++;
  }
  rev_length = length-2;
  while (rev_length != -1) {
    printf("%c", input[rev_length]);
    rev_length--;
  }
  printf("%c", input[length-1]);
  return 0;
}

// Handles sleeping and printing
// if rev is 1, reverse
int file_ops( char *input, float wait, int rev ) {
  FILE *file;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  file = fopen(input, "r");
  if (file == NULL) {
    printf("File not found\n");
    return(1);
  }

  if (rev == 1) {
    while ((read = getline(&line, &len, file)) != -1) {
      sleepp(wait);
      printf("%s", line);
      reverse(line);
      fflush(stdout);
    }
  }
  else if (rev == 0) {
    while ((read = getline(&line, &len, file)) != -1) {
      sleepp(wait);
      printf("%s", line);
      fflush(stdout);
    }
  }
  return 0;
}


int main( int argc, char **argv ) {

  // Getopt to process options
  // DO NOT CALL FUNCTIONS, Set variables in getopt.
  // h, d

  return 0; // End of program
}
