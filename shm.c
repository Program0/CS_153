#include "param.h"
#include "types.h"
#include "defs.h"
#include "x86.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "spinlock.h"

struct {
  struct spinlock lock;
  struct shm_page {
    uint id;
    char *frame;
    int refcnt;
  } shm_pages[64];
} shm_table;

void shminit() {
  int i;
  initlock(&(shm_table.lock), "SHM lock");
  acquire(&(shm_table.lock));
  for (i = 0; i< 64; i++) {
    shm_table.shm_pages[i].id =0;
    shm_table.shm_pages[i].frame =0;
    shm_table.shm_pages[i].refcnt =0;
  }
  release(&(shm_table.lock));
}

int shm_open(int id, char **pointer) {

    //you write this
    struct proc *curproc = myproc();
    int found, i;
    uint a;
    a = PGROUNDUP(curproc->sz);
    found = 0; 
    
    // We look through the table looking for the id. 
    acquire(&(shm_table.lock));    
    for(i = 0; i<64;i++){
        // If we find a shared frame, we update the stack and the shared page table
        if(id == shm_table.shm_pages[i].id){
            shm_table.shm_pages[i].refcnt++;
            // map the top of the page frame to the top of the stack 
            mappages(curproc->pgdir, (char *) a, PGSIZE, V2P(shm_table.shm_pages[i].frame), PTE_W | PTE_U);
            curproc->sz+=PGSIZE; // Update the top of the stack 
            *pointer = (char *) a; // Return the shared virtual address
            found = 1;
            // Release the lock on the shared page table
            release(&(shm_table.lock));
            return 0;
        }
    }
    if(!found){
        // Look for an empty page frame
        for(i = 0; i<64;i++){
            if(shm_table.shm_pages[i].id == 0){
                // Allocate memory, set memory, and repeat process as id is found
                shm_table.shm_pages[i].id = id;
                shm_table.shm_pages[i].frame = kalloc();
                memset(shm_table.shm_pages[i].frame, 0 , PGSIZE);
                shm_table.shm_pages[i].refcnt=1;
                // map the top of the page frame to the top of the stack 
                mappages(curproc->pgdir, (char *) a, PGSIZE, V2P(shm_table.shm_pages[i].frame), PTE_W | PTE_U);
                curproc->sz+=PGSIZE; // Update the top of the stack 
                *pointer = (char *) a; // Return the shared virtual address
                found = 1;
                // Release the lock on the shared page table
                release(&(shm_table.lock));
                return 0;                
            }
        }
        release(&(shm_table.lock));
        return -1; // We failed to find empty frame        
    }
    // If we reach here we failed.
    release(&(shm_table.lock));
    return -1; //added to remove compiler warning -- you should decide what to return
}


int shm_close(int id) {
    //you write this too!

    int i;    
    // Go through the table and look for the memory page
    acquire(&(shm_table.lock));    
    for(i = 0; i<64;i++){
        if(shm_table.shm_pages[i].id == id){
            shm_table.shm_pages[i].refcnt--;
            if(shm_table.shm_pages[i].refcnt <= 0){
                shm_table.shm_pages[i].frame = 0;
                shm_table.shm_pages[i].id = 0;
                release(&(shm_table.lock));
                return 0;
            }
            release(&(shm_table.lock));
            return 0;
        }            
    }
    release(&(shm_table.lock));
    // We never found it in the shared table
    return -1; //added to remove compiler warning -- you should decide what to return
}
