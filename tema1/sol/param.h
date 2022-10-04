#ifndef PARAM_H
#define PARAM_H

#include "sack_object.h"
#include "individual.h"
//#include "pthread_barrier_mac.h"
#include <pthread.h>

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

#endif