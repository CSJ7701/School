/*

  ┓┏              ┓   ┏┓
  ┣┫┏┓┏┳┓┏┓┓┏┏┏┓┏┓┃┏  ┣┓
  ┛┗┗┛┛┗┗┗ ┗┻┛┗┛┛ ┛┗  ┗┛

  -- TODO --
  * Add [-H] flag to print a valid HTTP header before the first file is printed to STDOUT.
  "HTTP/1.0 200
  Content-type: text/plain

  CONTENT HERE"

  * Add [-P] flag that will run the program in parallel - default setting is to run multiple files in serial.

  * Add [-L logfilename] that will APPEND error messages to the logfile
  IFF user chooses to run this program in the "parallel" setting, append ".xxxxx" extension where xxxxx is the PID of the child process.
     - For each file, before the first line, log timestamp and filename. ONLY these go to logfile, normal output is printed to STDOUT.
     - If the program cannot print to logfile, throw an error and exit.

  * Create a commandline function (do not have to add to path - simply write bash script) that calls program, pipes output to listening   NCAT process.
  e.g. bashfunc filename [file] -H | ncat -l 5342 (Should write loop to take all inputs to bashfunc and pass to the homework.out)

*/
#include <stdio.h>
#include <getopt.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>


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

// Sleeps and Prints. If rev is 1, reverse
int file_ops( char *input, float wait, int rev ) {
  FILE *file;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  int input_type;
  int wait_time = (int)(wait*1000000);

  if(input==NULL){ // If command is passed without a filename argument, assume STDIN
    input_type=0;
    file=fdopen(0,"r");
  }
  else{ // If command is passed with file input, do stuff
    file = fopen(input, "r"); // File descriptor
    if (file == NULL) { // Checks whether file exists. This should replace exists()
      fprintf(stderr, "File \'%s\' not found.\n", input);
      return (1);
    }
  }

  if (rev == 1) {
    while ((read = getline(&line, &len, file)) != -1) {
      usleep(wait_time);
      printf("%s", line);
      reverse(line);
      fflush(stdout);
    }
  }

  else if (rev == 0) {
    while ((read = getline(&line, &len, file)) != -1) {
      usleep(wait_time);
      printf("%s", line);
      fflush(stdout);
    }
  }
  return 0;
}

int printHelp(char **argv) {
  printf("\n");
  printf("Usage: %s [OPTIONS] File\n", argv[0]);
  printf("Takes an input file, reads contents, and prints to STDOUT line by line.\n\n");
  printf("Options:\n");
  printf("  -h            Display this help message\n");
  printf("  -r            Reverse each line\n");
  printf("  -d [delay]    Specify a delay in seconds or fractions thereof\n");
  printf("                Example: -d 0.5 for a 500 milliseconds delay\n");
  printf("\n");
  return 0;
}

int printHTTP() {

  return 0;
}

int main( int argc, char **argv ) {
  opterr=0;
  int opt;
  int opt_help=0;
  int opt_delay=0;
  float opt_delay_time=0;
  int opt_reverse=0;
  int child = -1;
  int wait_status;

  while((opt = getopt(argc, argv, "rHphd:L:")) != -1)
    {
      switch(opt)
        {
        case 'h':
          opt_help=1;
          break;

        case 'r':
          opt_reverse=1;
          break;

        case 'd':
          if (optarg == NULL) {
            fprintf(stderr, "Please enter a delay time.\n");
            return 1;
          }
          else {
            opt_delay=1;
            opt_delay_time=atof(optarg);
          }
          break;

        case H:
          printf("FIX ME\n");
          break;

        case p:
          printf("FIX ME2\n");
          break;

        case L:
          printf("FIX ME, BUT FIRST: %s\n", optarg);
          break;

        case '?':
          fprintf(stderr, "Option not recognized: %c\n", optopt);
          return 1;
        }
    }

  if (opt_help == 1) {
    printHelp(argv);
    return 0;
  }

  if(optind < argc){
    while(optind < argc){
      if ((child == -1) || (child != 0)){
        child = fork();
        //printf("ChildPID=%d, OPTIND=%d, MYPID=%d\n", child, optind, getpid());
        if (child == 0) {
          file_ops(argv[optind], opt_delay_time, opt_reverse);
        }
      }
      optind++;
    } // Should create a child for each file. This removes the need to run file_ops in the while loop.

    waitpid(-1, &wait_status, 0);

      // Run code for each file argument, dont forget optind++
      // file_ops(argv[optind], opt_delay_time, opt_reverse);
    }

  else {
    file_ops(NULL, opt_delay_time, opt_reverse);
  }

  return 0;
}
