#define EOF -1

extern unsigned char __lower_map[256];

inline int tolower(int c) {
    return (c == EOF) ? EOF : (int)__lower_map[(unsigned char)c];
}

int stricmp(const char* s1, const char* s2) {
    char c1, c2;
    while (1) {
        c1 = tolower(*s1++);
        c2 = tolower(*s2++);
        if (c1 < c2) {
            return -1;
        }
        if (c1 > c2) {
            return 1;
        }
        if (c1 == 0) {
            return 0;
        }
    }
}
