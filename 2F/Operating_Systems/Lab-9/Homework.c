/*
  _ _                                    _     ___
  | | | ___ ._ _ _  ___  _ _ _  ___  _ _ | |__ |_  |
  |   |/ . \| ' ' |/ ._>| | | |/ . \| '_>| / /  / /
  |_|_|\___/|_|_|_|\___.|__/_/ \___/|_|  |_\_\ /_/

- Implementing file locking
- Memory Function



 */
#include <stdio.h>
#include <getopt.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>
#include <errno.h>


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

void *wastemem( ulong memsize ) {
  int *mallblock = NULL;
  ulong mallocnum = 1024*1024*memsize;

  printf("DOING SOME STUFF...");
  mallblock=calloc(mallocnum, sizeof(int));

  if (mallblock <= 0) {
    char failmsg[128];
    snprintf(failmsg, sizeof(failmsg), "Failed to allocate mallloc: %s\n", strerror(errno));
    fprintf(stderr, "%s", failmsg);
    return NULL;
  } else {
    memset(mallblock, 1, mallocnum);
    printf("Successfully allocated mallblock\n");
  } return mallblock;
}

// Sleeps and Prints. If rev is 1, reverse
int file_ops( char *input, float wait, int rev, ulong mem ) {
  FILE *file;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  int input_type;
  int wait_time = (int)(wait*1000000);
  int *mempoint = NULL;

  if (mem != 0) {
    mempoint=wastemem(mem);
  }

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

    while ((read = getline(&line, &len, file)) != -1) {
      usleep(wait_time);
      printf("%s", line);
      if (rev == 1) {
        reverse(line);
      }
      fflush(stdout);
    }

  free(mempoint);
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
  printf("Content-type: text/plain\n");
  printf("\n");
  return 0;
}

int log_status( int child, char *file, char *logfile ) {
  int PID;
  char filename[100];
  time_t timething;
  char timebuff[128];

  time(&timething);
  ctime_r(&timething, timebuff);



  if(child == 0) {
    PID=getpid();
    snprintf(filename, sizeof(filename), "%s.%d", logfile, PID);
    FILE *logfile_full = fopen(filename, "a+");
    if (logfile_full == NULL)
      {
	fprintf(stderr, "Unable to open file %s\nFull Path: %s",logfile,realpath(logfile, NULL));
	exit(1);
      }
    fprintf(logfile_full, "[ %s ]\n %s \n\n", realpath(file, NULL), timebuff);
    fclose(logfile_full);
    return 0;
  }
  else {
    FILE *logfile_full = fopen(logfile, "a+");
    if (logfile_full == NULL)
      {
	char path[100];
	getcwd(path, 100);
	fprintf(stderr, "Unable to open file %s\nCurrentPath: %s\n",logfile,path);
	exit(1);
      }
    fprintf(logfile_full, "[ %s ]\n %s \n", realpath(file, NULL), timebuff);
    return 0;
  }
}



int main( int argc, char **argv ) {
  opterr=0;
  int opt;
  int opt_help=0;
  int opt_delay=0;
  float opt_delay_time=0;
  int opt_reverse=0;
  int opt_http=0;
  int opt_parallel=0;
  int child = -1;
  int wait_status;
  char *opt_log=NULL;
  ulong opt_mem=0;

  while((opt = getopt(argc, argv, "rHphd:L:m:")) != -1)
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

        case 'H':
          opt_http=1;
          break;

        case 'm':
          opt_mem=atol(optarg);
          break;

        case 'p':
          opt_parallel=1;
          break;

        case 'L':
          opt_log=optarg;
          break;

        case '?':
          fprintf(stderr, "Option not recognized: %c\n", optopt);
          return 1;
        }
    }
  if (opt_http == 1) {
    printHTTP();}

  if (opt_help == 1) {
    printHelp(argv);
    return 0;}


  if(optind < argc){
    while(optind < argc){

      if (((child == -1) || (child != 0)) && (opt_parallel == 1)){
	if(opt_log){
	  log_status(child, argv[optind], opt_log);
	}
	child = fork();
	//printf("ChildPID=%d, OPTIND=%d, MYPID=%d\n", child, optind, getpid());
	if (child == 0) {
	  file_ops(argv[optind], opt_delay_time, opt_reverse, opt_mem);

	}
      } else {
	if(opt_log){
	  log_status(child, argv[optind], opt_log);}
	file_ops(argv[optind], opt_delay_time, opt_reverse, opt_mem);
      }
      optind++;
    } // Should create a child for each file. This removes the need to run file_ops in the while loop.
    while(waitpid(-1, &wait_status, 0) != -1){;}
    // Run code for each file argument, dont forget optind++
    // file_ops(argv[optind], opt_delay_time, opt_reverse);
  }

  else {
    file_ops(NULL, opt_delay_time, opt_reverse, opt_mem);
  }


  return 0;
}
