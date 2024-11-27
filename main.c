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
  srand(getpid());
  if (p1<0){
    perror("fork failed\n");
    exit(1);
  }
  else if (!p1){
    int s = rand()%5+1;
    printf("%d %dsec\n", getpid(), s);
    sleep(s);
    printf("%d finished after %d seconds.\n", getpid(), s);
    exit(s);
  }
  else{
    p2 = fork();
    if (p2<0){
      perror("fork failed\n");
      exit(1);
    }
    else if (!p2){
      int s = rand()%5+1;
      printf("%d %dsec\n", getpid(), s);
      sleep(s);
      printf("%d finished after %d seconds.\n", getpid(), s);
      exit(s);
    }
    else{
      int status;
      pid_t child= wait(&status);
      if (child == -1) {
        perror("wait failed\n");
        exit(1);
      }
      if (WIFEXITED(status)){
        printf("Main Process %d is done. Child %d slept for %d sec\n", getpid(), child, WEXITSTATUS(status));
      }
    }
  }
  return 0;
}
