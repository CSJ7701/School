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
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

int debug( int argc, char **argv ) {

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


  return 0;
}

int exists( char *input ) {
  FILE *file;
  if (file = fopen(input, "r")) {
    fclose(file);
    printf("File exists\n");
    return 1;
  }
  else {
    printf("File \'%s\' not found.\n", input);
    return 0; }
}

int sleepp( float fsecs ) {

  int secs = (int)fsecs;

  if(ceilf(fsecs) == fsecs) {
    //    printf("sleep input in whole seconds: %i\n", secs);
    sleep(secs);
    return 0;
  }
  else {
    float sleep_dec = fsecs - floor(fsecs);
    float sleep_who = fsecs - sleep_dec;
    float sleep_mic = sleep_dec * 1000000;
    //    printf("Sleep input: %f seconds and %f microseconds\n", sleep_who, sleep_mic);
    sleep(sleep_who);
    usleep(sleep_mic);
    return 0;
  }

  return 0;
}

int reverse( char *input ) {

  int length = 0;
  int rev_length;
  
  while (input[length] != '\0') {
    // printf("%c", input[length]);
    length++;
  }
  //  printf("%c", input[length-1]);

  rev_length = length-2;
  while (rev_length != -1) {
    printf("%c", input[rev_length]);
    rev_length--;
  }
  printf("%c", input[length-1]);
  return 0;
}

int file_ops( char *input, float wait ) {
  FILE *file;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  file = fopen(input, "r");
  if (file == NULL) {
    printf("File not found\n");
    return(1);
  }

  
  while ((read = getline(&line, &len, file)) != -1) {
    // printf("Sleeping for %f seconds.\n", wait);
    sleepp(wait);
    // printf("Retrieved line of length %zu :  ", read);
    printf("%s", line);
    reverse(line);
  }

  return 0;
}

int main( int argc, char **argv ) {
  // argc = number of command line arguments ; argv[] = the index to select each argument (argv[1] is the first argument.)
  // no arguments - argc = 1
  opterr=0; // Prevents getopt from printing default error messages - lets me specify my own


  // Variable Declaration
  int opt;


  // Handle Options

  if (argc < 2) {
    fprintf(stderr, "Usage: %s [FILE] [OPT]\n", argv[0]);
    return 1;
  }
  
    while((opt = getopt(argc, argv, "df:")) != -1)
    {
      switch(opt)
	{
	  
	case 'd':
	  debug(argc, argv);
	  break;
	  
	case 'f':
	  if (optind >= argc) {
	    printf("Please enter a wait time\n");
	    return 1;
	  }
	  else {
	    while(optind < argc && *argv[optind] != '-'){
	      float wait = atof(argv[optind]);
	      printf("Input to sleepp: %f\n", wait);
	      //sleepp(wait);
	      exists(optarg);
	      file_ops(optarg, wait);
	      optind++;
	  }
	  }
	  break;
	  
	case '?':
	  fprintf(stderr, "Option not recognized: %c\n", optopt);
	  return 1;
	  
	}
    }

  // End of program
  return 0;
}
