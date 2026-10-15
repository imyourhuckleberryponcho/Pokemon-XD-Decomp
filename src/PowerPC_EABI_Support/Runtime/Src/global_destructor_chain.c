typedef void (*DestructorFunction)(void* object, int flag);

typedef struct DestructorChain {
    struct DestructorChain* next;
    DestructorFunction destructor;
    void* object;
} DestructorChain;

DestructorChain* __global_destructor_chain;

void __destroy_global_chain(void) {
    DestructorChain* gdc;
    while ((gdc = __global_destructor_chain) != 0) {
        __global_destructor_chain = gdc->next;
        gdc->destructor(gdc->object, -1);
    }
}
