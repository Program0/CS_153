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
	
  int ret_pid, exit_status, pid1, pid2, pid3;
 // use this part to test wait(int pid, int* status, int options)

 printf(1, "\nTest 2: testing waitpid(int pid, int* status, int options):\n");

      // Test that exit passes 0 to proc status for successful exit
      if( !(pid1 = fork())){
          printf(1, "I am the child. My pid is %d, My exit status is %d\n", getpid(),0 );
          exit(0);
      }

      if(pid1){
          ret_pid = waitpid(pid1, &exit_status, 0);
          printf(1, "I am your father, waiting for the child with pid %d. \n", pid1);
          printf(1, "The child's pid is %d and has exited with status %d\n", ret_pid, exit_status);
      }

      printf(1,"\n\nTesting for exit return value other than 0.\n");

      // Test that exit passes 100 to the proc status
      if(!(pid2 = fork())){
          printf(1, "I am the child. My pid is %d, My exit status is %d\n", getpid(),0 );
          exit(100);         
      }

      // Test that exit_status is 100 from child's exit(100) call. Used for custom exit codes.
      if(pid2){
          ret_pid = waitpid(pid2, &exit_status, 0);
          int parentpid = getpid();
          printf(1,"I am your father with pid %d, waiting for the child with pid %d. Exit status will return 100 \n", parentpid, pid2);
          printf(1, "The pid %d I waited for has exited with status %d\n", ret_pid, exit_status); 
      }

      printf(1,"\n\nTesting for wait returns -1.\n");

      // Test that successful exit is passed to proc struct
      if(!(pid3 = fork())){
          printf(1, "I am the child. My pid is %d, My exit status is %d\n", getpid(),0 );
          exit(0);         
      }
      // Test that waitpid returns -1 if pid is not found. Should have a zombie process after this.
      if(pid3){
          int parentpid = getpid();
          ret_pid = waitpid(-1, &exit_status, 0);

          printf(1,"I am a father with pid %d, waiting for a child with fake pid -1. waitpid will return -1 \n", parentpid);
          printf(1, "The pid I waited for was not found and waitpid returned %d. Exit status of child is discarded and is %d\n", ret_pid, exit_status); 

          ret_pid = waitpid(pid3, &exit_status, 0);
          //printf(1, "I am your father, waiting for the child with pid %d. \n", pid);
          //printf(1, "The child's pid is %d and has exited with status %d\n", ret_pid, exit_status);
      }


      return 0;
  }
     

