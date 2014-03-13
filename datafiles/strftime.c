#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

int main(){
  printf("==================================================================\n");
  printf("usage of func time\n");
  printf("==================================================================\n");
  time_t t;
  time(&t);
  printf("return value of func time : %zu\n",time(&t));
  printf("fill time value in tmp    : %zu\n", t);
  printf("\n");

  printf("==================================================================\n");
  printf("usage of func clock_gettime\n");
  printf("==================================================================\n");
  int rtn_clock;
  struct timespec tsp1;
  rtn_clock = clock_gettime(CLOCK_REALTIME, &tsp1);
  printf("return value : %d\n", rtn_clock);
  
  printf("second value : %zu\n",tsp1.tv_sec);
  printf("nanosecond value : %zu\n",tsp1.tv_nsec);
  printf("\n");
  
  printf("==================================================================\n");
  printf("usage of func clock_getres\n");
  printf("==================================================================\n");
  clockid_t clocks[]= {  
    CLOCK_REALTIME,  
    CLOCK_MONOTONIC,  
    CLOCK_PROCESS_CPUTIME_ID,  
    CLOCK_THREAD_CPUTIME_ID,  
    (clockid_t) -1,  
  };  
  
  int i;  
  for(i = 0; clocks[i] != (clockid_t) -1; i++) {  
    struct timespec res;  
    int ret;  
    ret = clock_getres(clocks[i], &res);  
    if (ret)  
      perror("clock_getres");  
    else
      printf("clock = [%d],sec = [%ld],nsec = [%ld]\n",
             i, res.tv_sec, res.tv_nsec);  
  }  
  printf("\n");

  printf("==================================================================\n");
  printf("usage of func gettimeofday\n");
  printf("==================================================================\n");
  struct timeval tp;
  gettimeofday(&tp,NULL);

  printf("seconds part   : %zu\n",tp.tv_sec);
  printf("suseconds part : %zu\n",tp.tv_usec);  
  printf("\n");
  
  printf("==================================================================\n");
  printf("usage of func strftime\n");
  printf("==================================================================\n");
  time_t t2;
  struct tm *tmp;
  char buf1[16];
  char buf2[64];

  tmp = localtime(&t2);
  if (strftime(buf1, 16, "time and date: %r, %a %b %d, %Y", tmp) == 0)
    printf("buffer length 16 is too small\n");
  else
    printf("%s\n", buf1);
  if (strftime(buf2, 64, "time and date: %r, %a %b %d, %Y", tmp) == 0)
    printf("buffer length 64 is too small\n");
  else
    printf("%s\n", buf2);
  printf("\n");
  
  exit(0);
}
