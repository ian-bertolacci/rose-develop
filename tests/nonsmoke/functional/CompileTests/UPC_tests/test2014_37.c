typedef struct 
   {
     shared int * ptr;
   } SupLib;

void subroutine(shared SupLib *suplib) 
   {
#if 1
     int i;
     i = *((*suplib).ptr);
#endif
#if 1
     int j;
     j = *(suplib->ptr);
#endif
#if 1
     shared int* j_ptr;
     j_ptr = (suplib->ptr);
#endif
#if 1
     suplib = 0L;
#endif
   }
