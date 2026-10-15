typedef unsigned long size_t;

extern "C" void* __copy(char* to, char* from, size_t size) {
    char* p;
    if (to != 0 && size != 0) {
        p = to;
        do {
            *p = *from;
            from++;
            p++;
            size--;
        } while (size != 0);
    }
    return to;
}
