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

[]  Ensure All files have proper extensions (not necessary, but instructor wants)
[]  Submit documentation as a PDF - add pictures
[]  Add Code Comments


*/
#include <stdio.h>
#include <getopt.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>

// Check if file exists
// Returns error if not found
int exists( char *input ) {
  FILE *file;
  if ( file = fopen(input, "r")) { 
    fclose(file);
    // printf("File Exists\n");
    return 0;
  } // If file can be opened in "read" state, then it exists and return default state
  else {
    printf("File \'%s\' not found.\n", input);
    return 1;
  } // If file cannot be opened, return an error
}

// Sleeps program
// Can take input in fractional or full seconds.
int sleepp( float fsecs ) {
  int secs = (int)fsecs;

  if(ceilf(fsecs) == fsecs) { // Checks if the time input is an integer. Could have also used floor()
    sleep(secs); // If integer, use integer sleep function
    return 0;
  }
  else {
    float sleep_dec = fsecs - floor(fsecs);
    float sleep_who = fsecs - sleep_dec;
    float sleep_mic = sleep_dec * 1000000;
    sleep(sleep_who); 
    usleep(sleep_mic);
    return 0; // If not an integer, seperate into integer and decimal components, convert decimal to microseconds, then use appropriate sleep functions accordingly
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
  return 0; // Takes line array, and indexes into it in reverse
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
    //printf("File not found\n");
    return 1; // Throws error if "file" is not defined
  }

  if (rev == 1) {
    while ((read = getline(&line, &len, file)) != -1) {
      sleepp(wait);
      printf("%s", line);
      reverse(line);
      fflush(stdout); // prints line, reverses line, flushes 
    }
  }
  else if (rev == 0) {
    while ((read = getline(&line, &len, file)) != -1) {
      sleepp(wait);
      printf("%s", line);
      fflush(stdout); // prints line, flushes
    }
  }
  return 0;
}

void printHelp(char **argv) {
  printf("Usage: %s [OPTIONS] File\n", argv[0]);
  printf("Takes an input file, reads contents, and prints to STDOUT line by line.\n\n");  
  printf("Options:\n");
  printf("  -h            Display this help message\n");
  printf("  -r            Reverse each line\n");
  printf("  -d [delay]    Specify a delay in seconds or fractions thereof\n");
  printf("                Example: -d 0.5 for a 500 milliseconds delay\n");
} // Prints help message




int main( int argc, char **argv ) {
  // argc - num of args ; argv[] is index
  // argc - 1=no args 2=one arg

  opterr=0; // Prevents getopt from sending default errors
  int opt;
  int opt_help=0;
  int opt_delay=0;
  float opt_delay_time=0;
  int opt_reverse=0;

  // Usage statement on no arguments
  if (argc < 2) {
    printHelp(argv);
    return 1;
  } // If no arguments are passed, print usage/help

  while((opt = getopt(argc, argv, "rhd:")) != -1)
    {
      switch(opt)
	{
	case 'h': // If -h found, set opt_help=1
	  opt_help=1;
	  break;
	  
	case 'r': // If -r found, set opt_reverse = 1 
	  opt_reverse=1;
	  break;
	  
	case 'd': // If -d found, and no extra arg, throw error. If -d found with arg, set opt_delay=1 and opt_delay_time=the converted value of the arg
	  if (optarg == NULL) {
	    fprintf(stderr, "Please enter a delay time.\n");
	    return 1;
	  }
	  else {
	    opt_delay=1;
	    opt_delay_time=atof(optarg);
	  }
	  break;
	  
	case '?': // Extra cases, throw error
	  fprintf(stderr, "Option not recognized: %c\n", optopt);
	  return 1;
	}
    }

  if (opt_help == 1) {
    printHelp(argv);
  }

  while(optind < argc && *argv[optind] != '-'){ // Process non option args as files to run the file_ops command off of
    exists(argv[optind]);
    file_ops(argv[optind], opt_delay_time, opt_reverse);
    optind++;
  }
  

  return 0; // End of program
}
