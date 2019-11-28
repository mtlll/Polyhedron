// implementation of generic tools
#include "cube.h"

//
// Mike: Why override these? What is the use of that? malloc... there are faster and special ways to alloc.
//

// void *operator new(size_t size)
// {
//     void *p = malloc(size);
//     if(!p) abort();
//     return p;
// }

// void *operator new[](size_t size)
// {
//     void *p = malloc(size);
//     if(!p) abort();
//     return p;
// }

// void operator delete(void *p) { if(p) free(p); }

// void operator delete[](void *p) { if(p) free(p); }

// void *operator new(size_t size, bool err)
// {
//     void *p = malloc(size);
//     if(!p && err) abort();
//     return p;
// }

// void *operator new[](size_t size, bool err)
// {
//     void *p = malloc(size);
//     if(!p && err) abort();
//     return p;
//}