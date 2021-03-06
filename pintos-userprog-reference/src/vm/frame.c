#include "vm/frame.h"
#include <debug.h>
#include "threads/malloc.h"
#include "userprog/debug_helper.h"
#include "threads/vaddr.h"
/* #include "userprog/process.c" */
#include "threads/thread.h"
#include "userprog/pagedir.h"
int *framearray;


void init_framearray(){  
  printf("Initialize\n");
  framearray=calloc(FRAME_SIZE,4);
  if(framearray==NULL)
    PANIC("unexpected failure-Out of memory for frame table\n");
}

void * frame_alloc(){
  int i=0;
  printf("hello \n");
  for(i=256;i<FRAME_SIZE;i++){
    printf("framesixze: %d , %d \n",FRAME_SIZE,i);
    

    if(framearray[i]==0){
      printf("i: %d \n",i); 
      printf("Getting kernel page..\n");
      void * temp= palloc_get_page(0);
      printf("Getting user page..\n");
      void *tempuser=palloc_get_page(PAL_USER); 
      tempuser=tempuser-PHYS_BASE;
      printf("temp(kernel)=%p\n",temp);
      printf("tempuser=%p\n",tempuser);
      framearray[i]=((int)temp >> 12);
    
      pagedir_set_page(thread_current()->pagedir,tempuser,temp,true);
      
      return temp;
    }
    
  }
  PANIC("cannot allocate frame");
  
  
  }

void frame_free(void *page){
  int i=0;

  for(i=256;i<FRAME_SIZE;i++){
    
    if(page==pagedir_get_page((thread_current())->pagedir,(void *)(framearray[i]<<12)))
       framearray[i]==0;
       }
    palloc_free_page(page);
}  
