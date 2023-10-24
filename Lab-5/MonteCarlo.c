
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define NUM_THREADS 4
#define NUM_ITER 1000000

void *monte_carlo(void *threadid) {

}


int rand_point () {
  a = -1+2*((float)rand())/RAND_MAX;
  return 0;
}


int main() {
    pthread_t threads[NUM_THREADS];
	
	// Pre
    
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, monte_carlo, (void *)(size_t)i);
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], &status);
    }

	//Post

    printf("PI = %.4f\n", (double)total / (NUM_ITER * NUM_THREADS) * 4);
    return 0;
}

