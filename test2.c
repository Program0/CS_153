#include "types.h"
#include "user.h"
#include "stddef.h"

int main(int argc, char *argv[])
{
    // Tests the implementation of setPriority and getPriority system calls. 	
    void testSetPriority(void);

    // Tests the implementation of setPriority and getPriority system calls. 	
    void testGetPriority(void);

    // Testing priority aging
    void testPriorityAging(void);

    // Testing the time information
    void testTimeInfo(void);
    
    // Test priority donation/inheritance
    void testPriorityInheritance(void);
    
    printf(1, "\n This program tests the correctness of lab 2.\n");
  
    if (atoi(argv[1]) == 1){
        testSetPriority();
        testGetPriority();
    }
    else if (atoi(argv[1]) == 2)
        testPriorityAging();
    else if (atoi(argv[1]) == 3)
        testPriorityInheritance();
    else if (atoi(argv[1]) == 4)
        testTimeInfo();

    else
        printf(1, "\ntype \"test2 1\" to test set and get priority, \"test2 2\" to test priority aging, \"test2 3\" to test priority donation/inheritance, \"test2 4\" to test time information \n");
  
    // End of test
    exit(0);
 }

void testPriorityAging(void){
    int pid;

    printf(1,"\nTesting priority aging. \nWe set the parent's priority to 20 and the children's priority to 10\n");
    printf(1,"\nWe make the parent wait to avoid zombies\n");
    printf(1,"\nI am the parent %d with priority %d\n", getpid(),getpriority(getpid()));
    setpriority(20);
    printf(1,"\nI am the parent %d with priority %d after setting priority\n", getpid(),getpriority(getpid()));
    printf(1,"\nI run first and other process wait for me. So, my priority decrements to lower priority.\n");
     
    for (int i = 0; i <  3; i++) {
    // Create a new process
    pid = fork();
    
    if (pid > 0) {
        continue;
    }
    
    else if (pid == 0) {
        int priority1, priority2; 
        setpriority(10);
        // First time we run we get a priority
        priority1 = getpriority(getpid());
        printf(1,"\nchild# %d with priority %d has started! \n", getpid(), priority1);
		for (int j=0;j<50000;j++) {
			for(int k=0;k<10000;k++) {
				asm("nop");
			}
		}
		
		// Test priority change after running
		priority2 = getpriority(getpid());				
		printf(1, "\nchild# %d with priority %d has finished! \n", getpid(), priority2);
		exit(0);
        }
        else {
			printf(2," \n Error \n");
			
        }
	}

	if(pid > 0) {
	    int priority;
	    priority = getpriority(getpid());
		printf(1,"\nI am the parent %d with priority %d before waiting\n", getpid(),priority);

/*
        for (int i = 0; i < 3; i++){
            wait(NULL);        
        }
*/
        printf(1,"\nI am the parent %d with priority %d\n after waiting", getpid(),priority);
    }
}

void testPriorityInheritance(void)
{
    int pid, exit_status;
    pid = fork();
    setpriority(5);
    if( pid == 0 ){
        printf(1,"\nMy parent has waited for me.\n");
        printf(1,"\nI am child %d with priority %d: \n", getpid(),getpriority(getpid()));
        
        // Wait so that priority changes
        for (int j=0;j<50000;j++) {
		    for(int k=0;k<10000;k++) {
		        asm("nop"); 
		    }
        }
        exit(0);       
    }
    if(pid > 0 ){
        int ret_value;
        printf(1,"\nI am parent %d, and priority %d: \n", getpid(),getpriority(getpid()));
        printf(1,"\nBefore waiting child %d has priority %d: \n", pid,getpriority(pid));        
        int prior = getpriority(pid);
        // Wait so that child is not reaped yet.
        for (int j=0;j<50000;j++) {
		    for(int k=0;k<10000;k++) {
		        asm("nop"); 
		    }
        }
        ret_value = waitpid(pid, &exit_status, 0);
        if(ret_value == pid)
            printf(1,"\nSuccess!\n");

        printf(1,"\nI am parent %d, and priority %d: \n", getpid(),getpriority(getpid()));
        printf(1,"\nAfter waiting child %d, has priority %d\n", pid, prior);
    }
}

void testTimeInfo(void)
{
    int pid;
    pid = fork();
    if( pid == 0 ){
        printf(1,"\nI am child %d, with time info: \n", getpid());
        timeinfo(getpid());
    }
    if(pid > 0 ){
        wait(NULL);
        printf(1,"\nI am parent %d, with time info: \n", getpid());
        timeinfo(getpid());
        printf(1,"\nMy child %d, has time info:\n", pid);
        timeinfo(pid);
    }
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

