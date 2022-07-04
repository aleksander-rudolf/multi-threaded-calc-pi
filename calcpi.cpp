// count_pixels() calculates the number of pixels that fall into a circle
// using the algorithm explained here:
//
// https://en.wikipedia.org/wiki/Approximations_of_%CF%80
//
// count_pixels() takes 2 paramters:
//  r         =  the radius of the circle
//  n_threads =  the number of threads you should create

#include "calcpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <pthread.h>

struct TMem{
    pthread_t tid;
    int start, end, radius;
    uint64_t per_thread_count = 0;
};

void* threadFunction(void * args){
  struct TMem *tm = (struct TMem *) args;
  double rsq = (double)tm->radius * (double)tm->radius;
  uint64_t count = 0;

  //Use Pythagorean theorem to approximate the area of the circle in Quadrant I.
  for(double x = tm->start; x <= tm->end; x++)
    for(double y = 0; y <= tm->radius; y++)
      if( x*x + y*y <= rsq) count++;

  tm->per_thread_count = count;
  pthread_exit(NULL);
}

uint64_t count_pixels(int r, int n_threads){
  
  TMem tarr[n_threads];

  int quotient = r/n_threads;
  int remainder = r%n_threads;

  uint64_t count = 0;

  //Determine the range of pixels (start and end points) on the x-axis in Quadrant I for each thread to handle.
  for(long i=0; i < n_threads; i++){
    tarr[i].radius = r;
    if(i == 0){
      tarr[i].start = 1;
      if(remainder != 0){
        tarr[i].end = tarr[i].start + quotient;
        remainder--;
      }
      else{
        tarr[i].end = tarr[i].start + quotient - 1;
      }
    }
    else{
      tarr[i].start = tarr[i-1].end + 1;
      if(remainder != 0){
        tarr[i].end = tarr[i].start + quotient;
        remainder--;
      }
      else{
        tarr[i].end = tarr[i].start + quotient - 1;
      }
    }

    //Create threads.
    if(0 != pthread_create(&tarr[i].tid, 0, threadFunction, &tarr[i])){
      printf("Error: pthread_create failed\n");
      exit(-1);
    }
  }

  //Join threads.
  for(int i=0; i< n_threads; i++){
    pthread_join(tarr[i].tid, NULL);
    count += tarr[i].per_thread_count;
  }
  return count * 4 + 1;
}