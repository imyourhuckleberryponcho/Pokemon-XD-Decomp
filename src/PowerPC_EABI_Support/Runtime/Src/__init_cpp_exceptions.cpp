extern "C" {

extern char _eti_init_info[];
int __register_fragment(void* info, char* TOC);
void __unregister_fragment(int fragmentID);

static int fragmentID = -2;

void __fini_cpp_exceptions(void) {
    if (fragmentID != -2) {
        __unregister_fragment(fragmentID);
        fragmentID = -2;
    }
}

void __init_cpp_exceptions(void) {
    if (fragmentID == -2) {
        register char* toc;
        asm { mr toc, r2 }
        fragmentID = __register_fragment(_eti_init_info, toc);
    }
}

}

__declspec(section ".ctors") extern void* const __init_cpp_exceptions_reference = __init_cpp_exceptions;
__declspec(section ".dtors") extern void* const __fini_cpp_exceptions_reference = __fini_cpp_exceptions;
