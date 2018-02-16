#include "types.h"
#include "user.h"
#include "stddef.h"

// Tests the implementation of setPriority and getPriority system calls. 	
void testSetPriority(void);

// Tests the implementation of setPriority and getPriority system calls. 	
void testGetPriority(void);

// Testing priority aging
void testPriorityAging(void);

int main(int argc, char *argv[])
{
   printf(1, "\n This program tests the correctness of lab 2.\n");
  
   if (atoi(argv[1]) == 1){
       testSetPriority();
       testGetPriority();
   }
   else if (atoi(argv[1]) == 2)
       exit(0);
   else 
       printf(1, "\ntype \"test 1\" to test set and get priority, \"test 2\" to test priority aging \n");
  
    // End of test
    exit(0);
 }

void testPriorityAging(void){
}
  
void testSetPriority(void)
{
   int pid, changeResult, newpriority;
   pid = getpid();
   newpriority = 15;
   printf(1,"\nTesting setPriority(pid) function call\n");    
   printf(1,"\nI am process with pid: %d, my priority is: %d. I am changing my priority to 15\n", pid, getpriority(pid));
   changeResult = setprioritypid(pid,newpriority);
   if(changeResult < 0){
       printf(1,"\nFailed to change priority\n");
   } else {
       printf(1,"\nSuccess changing priority. Change result is %d\n", changeResult);
   }
   printf(1,"\nAfter the change my priority is: %d\n", getpriority(pid));
}

void testGetPriority(void)
{
   int pid, priority;
   pid = getpid();
   priority = getpriority(pid);
   printf(1,"\nTesting getPriority(pid) function call\n");    
   printf(1,"\nI am process with pid: %d, my priority is: %d\n", pid, priority);
}

