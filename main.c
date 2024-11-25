#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <time.h>
int main(){
  printf("%d about to create 2 child processes.\n", getpid());
  pid_t p1;
  pid_t p2;
  p1 = fork();
  // p2 = fork();
  srand(getpid());
  if (p1<0 || p2<0){
    perror("fork failed\n");
    exit(1);
  }
  else if (!p1){
    int s = rand()%5+1;
    printf("%d %dsec\n", getpid(), s);
    sleep(s);
    printf("%d finished after %d seconds.\n", getpid(), s);
  }
  else if (!p2){
    int s = rand()%5+1;
    printf("%d %dsec\n", getpid(), s);
    sleep(s);
    printf("%d finished after %d seconds.\n", getpid(), s);
  }
  else{
    p2 = fork();
    int status;
    wait(&status);
    if (WIFEXITED(status)){
      printf("Main Process %d is done. Child %d slept for ___ sec\n", getpid(), p1);
    }
  }
}
