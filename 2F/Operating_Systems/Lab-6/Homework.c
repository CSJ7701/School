/*

.##.....##..#######..##.....##.########.##......##..#######..########..##....##....########
.##.....##.##.....##.###...###.##.......##..##..##.##.....##.##.....##.##...##.....##......
.##.....##.##.....##.####.####.##.......##..##..##.##.....##.##.....##.##..##......##......
.#########.##.....##.##.###.##.######...##..##..##.##.....##.########..#####.......#######.
.##.....##.##.....##.##.....##.##.......##..##..##.##.....##.##...##...##..##............##
.##.....##.##.....##.##.....##.##.......##..##..##.##.....##.##....##..##...##.....##....##
.##.....##..#######..##.....##.########..###..###...#######..##.....##.##....##.....######.

Goal:
Refactor homework to spawn a process for each file argument.
Final program should be able to process each file in a seperate process
**QUESTION** - should each of these children run at the same time, e.g. should the parent create all children, then wait; or should the               parent create a child, wait for it to die, then create the next child?
**ANSWER**   - Create multiple before waiting for all to die.

Each child should have its own delays
**QUESTION** - does this mean that we should be specifying a different delay for each file, or is this just saying that each child shou               ld take the previously defined delay, and it should simply run on a different "clock cycle"?
**ANSWER**   - Same delay time for all files, run on seperate "clocks"

Parent will process no files - use waitpid() to wait until child(ren) die.



Notes:
Fork returns 0 for (___) and PID for (___). Use this in an if statement to make parent wait.

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

int main( int argc, char **argv ) {
  opterr=0;
  int opt;
  int opt_help=0;
  int opt_delay=0;
  float opt_delay_time=0;
  int opt_reverse=0;
  int child = -1;
  int wait_status;

  while((opt = getopt(argc, argv, "rhd:")) != -1)
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
