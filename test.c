#include "types.h"
#include "user.h"
#include "stddef.h"

int main(int argc, char *argv[])
{
    // Tests the implementation of setPriority and getPriority system calls. 	
    unsigned int __attribute__((optimize("O0"))) testAllocated(unsigned int);
   
    printf(1, "\n This program tests the correctness of lab 3.\n");
    int i;
    if (atoi(argv[1]) == 1){
        printf(1,"\nWe call a recursive function 1000 times to increase the stack size\n");
        i = testAllocated(1000);
        printf(1,"\nWe ran testAllocated %d \n", i);
    }
    else
        printf(1, "\ntype \"test 1\" to test stack memory allocation. \n");
  
    // End of test
    exit();
 }

unsigned int testAllocated(unsigned int n){
    if(n == 0){
        return 1;
    }
    if(n % 200 == 0)
        stack_info();
    return 1 + testAllocated(n-1);
}
