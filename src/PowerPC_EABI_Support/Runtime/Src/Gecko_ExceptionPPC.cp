#define MAXFRAGMENTS 1

typedef struct FragmentInfo {
    void* exception_info;
    char* TOC;
    int active;
} FragmentInfo;

static FragmentInfo fragmentinfo[MAXFRAGMENTS];

extern "C" void __unregister_fragment(int fragmentID) {
    FragmentInfo* f;
    if (fragmentID >= 0 && fragmentID < MAXFRAGMENTS) {
        f = &fragmentinfo[fragmentID];
        f->exception_info = 0;
        f->TOC = 0;
        f->active = 0;
    }
}

extern "C" int __register_fragment(void* info, char* TOC) {
    FragmentInfo* f;
    int i;
    for (i = 0, f = fragmentinfo; i < MAXFRAGMENTS; ++i, ++f) {
        if (f->active == 0) {
            f->exception_info = info;
            f->TOC = TOC;
            f->active = 1;
            return i;
        }
    }
    return -1;
}
