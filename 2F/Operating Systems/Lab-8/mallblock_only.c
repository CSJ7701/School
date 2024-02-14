/****************************************
 * void *wastemem(struct optblock *opts)
 * Waste/allocate the user-requested amount of memory per call.
 * Return a pointer to the allocated block.
 * The CALLING function is responsible for freeing it (or not!)
 *
 * Note that a pointer to a block of options is passed in as an
 * argument, and this code uses several of the fields in that optblock
 * struct. Your code is surely structured differently, so you must
 * change the parameters and references in this example to be
 * compatible with your own code! This file will not compile
 * standalone.
 * 
 * In your code you will likely need to:
 *    #include <errno.h>
 ****************************************/

/* HINT: Convert to for compatibility with YOUR code!:
   void *wastemem(double userreq, int logflag, FILE* logfd) {...}
*/
void *wastemem(struct optblock *opts) {

  int *mallblock = NULL;
  long mallocnum = 1024*1024*opts->malval; // 1 computer-million * user request

  printf("malloc'ing a pile of RAM....\n");
  // of this architecture's integer, so technically 1k*1k*probably_8bytes
  mallblock = calloc(mallocnum, sizeof(int));
  if (mallblock <= 0) {
    char failmsg[128];
    snprintf(failmsg, sizeof(failmsg), "failed to allocate malllock: %s\n", strerror(errno));
    fprintf(stderr, "%s", failmsg);
    /* This makes things complicated, so let's comment it out: 
    if (opts->logflag) {
      fprintf(opts->logfd, "%s", failmsg);
    }
    */
    return NULL;
  } else {
    // init with 1's. forces page table allocation because "lazy" optimizations
    memset(mallblock, 1, mallocnum);
    printf("successfully allocated mallblock\n");
  }
  return mallblock; // pointer to this block must be saved by caller, else leaky
} // end wastemem()

