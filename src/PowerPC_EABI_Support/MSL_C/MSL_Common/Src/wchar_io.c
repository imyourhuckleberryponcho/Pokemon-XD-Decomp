#define NULL 0

enum { __closed_file };
enum { __unoriented, __char_oriented, __wide_oriented };

typedef struct {
    unsigned int open_mode : 2;
    unsigned int io_mode : 3;
    unsigned int buffer_mode : 2;
    unsigned int file_kind : 3;
    unsigned int file_orientation : 2;
    unsigned int binary_io : 1;
} __file_modes;

typedef struct _FILE {
    unsigned long handle;
    __file_modes mode;
} FILE;

int fwide(FILE* stream, int mode) {
    int orientation;
    int result;

    if (stream == NULL || stream->mode.file_kind == __closed_file) {
        return 0;
    }
    orientation = stream->mode.file_orientation;
    switch (orientation) {
    case __unoriented:
        if (mode > 0) {
            stream->mode.file_orientation = __wide_oriented;
        } else if (mode < 0) {
            stream->mode.file_orientation = __char_oriented;
        }
        result = mode;
        break;
    case __wide_oriented:
        result = 1;
        break;
    case __char_oriented:
        result = -1;
        break;
    }
    return result;
}
