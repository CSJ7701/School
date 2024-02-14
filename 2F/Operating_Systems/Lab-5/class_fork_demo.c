/*****************************************
 * From Silbershatz, Chapter 3 problems (corrected):
 * 3.11 Including the initial parent process, how many processes
 * are created by the program below?
 * Add debugging statements to explore what it does.
 * Try using getpid(), fprintf(), and the return value from fork().
 *****************************************/
#include <stdio.h>
#include <unistd.h>


int main() {

  // print something useful here
  fprintf(stderr,"And thus, it begins...\n");
  int i;

  for (i = 0; i < 4; i++) {
    // print something useful here
    //printf("pid1: %i\n", getpid());
    int f = fork(); // check and use the return value new code block?
    //print something useful here
    printf("pid2: %i i: %i fork: %i\n", getpid(), i, f);
  }

  // print something useful here

  return 0;

} // end main()

/*
# of processes - 16



  -----
  i=0
  pid1 1

  pid2 1
  pid2 2

---

  i=1
  pid1 1
  pid1 2

  pid2 1
  pid2 2
  pid2 3
  pid2 4

  ---

  i=2
  pid1 1
  pid1 2
  pid1 3
  pid1 4

  pid2 1
  pid2 2
  pid2 3
  pid2 4
  pid2 5
  pid2 6
  pid2 7
  pid2 8

  ---

  i=3
  pid1 1
  pid1 2
  pid1 3
  pid1 4
  pid1 5
  pid1 6
  pid1 7
  pid1 8

  pid2 1
  pid2 2
  pid2 3
  pid2 4
  pid2 5
  pid2 6
  pid2 7
  pid2 8
  pid2 9
  pid2 10
  pid2 11
  pid2 12
  pid2 13
  pid2 14
  pid2 15
  pid2 16
*/
