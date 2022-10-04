#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "pthread_barrier_mac.h"
#include "genetic_algorithm.h"
//#include "param.h"

typedef struct param
{
	const sack_object *objects;
	int object_count;
    int generations_count;
    int sack_capacity;

    int threads_count;
    int id; 
    pthread_barrier_t* barrier;
    
} param;

int main(int argc, char *argv[]) {
	// array with all the objects that can be placed in the sack
	sack_object *objects = NULL;

	// number of objects
	int object_count = 0;

	// maximum weight that can be carried in the sack
	int sack_capacity = 0;

	// number of generations
	int generations_count = 0;

	// number of threads
	int threads_count = 0;

	if (!read_input(&objects, &object_count, &sack_capacity, &generations_count, &threads_count, argc, argv)) {
		return 0;
	}

	pthread_t threads[threads_count];
	param status;
	int r;

	// create barrier 
	// pthread_barrier_t barrier;

	// r = pthread_barrier_init(&barrier, NULL, threads_count);

	// if (r != 0) {
	// 	printf("Barrier init failed!");

	// 	return -1;
	// } 
	// end barrier create

	status.objects = objects;
	status.object_count = object_count;
	status.generations_count = generations_count;
	status.sack_capacity = sack_capacity;
	status.threads_count = threads_count;
	status.barrier = &barrier;

	for (int i = 0; i < threads_count; i++) {
		status.id = i;
		r = pthread_create(&threads[i], NULL, run_genetic_algorithm,(void*) &status);
	 	if (r) {
			printf("Eroare la crearea thread-ului %d\n", i);
			exit(-1);
		}
	}

	//run_genetic_algorithm(objects, object_count, generations_count, sack_capacity);
	//run_genetic_algorithm(&status);

	//final join
	for (int i = 0; i < threads_count; i++) {
		r = pthread_join(threads[i], NULL);
	 if (r) {
			printf("Eroare la asteptarea thread-ului %d\n", i);
			exit(-1);
		}
	}

	r = pthread_barrier_destroy(&barrier);
	if (r != 0) {
		printf("Barrier destroy failed!");
		return -1;
	} 

	free(objects);

	return 0;
}
