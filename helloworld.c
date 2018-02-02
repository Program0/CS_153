#include "types.h"
#include "user.h"



int main(int argc, char *argv[])
{
//Tests the implementation of waitpid. 	
  int testWaitPid(void);

  printf(1, "\n This program tests the correctness of waitpid.\n");
	testWaitPid();
	 exit(0);
 }
  
int testWaitPid(void){
	
  int ret_pid, exit_status, pid;
 // use this part to test wait(int pid, int* status, int options)

 printf(1, "\nTest 2: testing waitpid(int pid, int* status, int options):\n");

      if( !(pid = fork())){
          printf(1, "I am the child. My pid is %d, My exit status is %d\n", getpid(),0 );
          exit(0);
      }

      if(pid){
          ret_pid = waitpid(pid, &exit_status, 0);
          printf(1, "I am your father, waiting for the child with pid %d. \n", pid);
          printf(1, "The child's pid is %d and has exited with status %d\n", ret_pid, exit_status);
      }

      printf(1,"Testing for exit status failed.\n");

      if(!(pid = fork())){
          printf(1, "I am the child. My pid is %d, My exit status is %d\n", getpid(),0 );
          exit(0);         
      }

      if(pid){
          int parentpid = getpid();
          ret_pid = waitpid(-1, &exit_status, 0);

          printf(1,"I am your father with pid %d, waiting for the child with pid %d. waitpid is using NULL and returns -1 \n", parentpid, pid);
          printf(1, "The pid %d I waited for has exited with status %d\n", ret_pid, exit_status); 

          ret_pid = waitpid(pid, &exit_status, 0);
          printf(1, "I am your father, waiting for the child with pid %d. \n", pid);
          printf(1, "The child's pid is %d and has exited with status %d\n", ret_pid, exit_status);
      }

      return 0;
  }
     

