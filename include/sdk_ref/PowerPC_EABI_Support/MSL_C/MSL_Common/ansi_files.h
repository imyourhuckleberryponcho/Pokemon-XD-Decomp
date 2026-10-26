#ifndef _MSL_COMMON_ANSI_FILES_H
#define _MSL_COMMON_ANSI_FILES_H

#include "types.h"

typedef u32 __file_handle;
typedef u32 fpos_t;
typedef struct _IO_FILE _IO_FILE, *P_IO_FILE;

#define __ungetc_buffer_size 2

enum __file_kinds { __closed_file, __disk_file, __console_file, __unavailable_file };

enum __file_orientation { __unoriented, __char_oriented, __wide_oriented };

typedef struct __file_modes {
	u32 open_mode : 2;
	u32 io_mode : 3;
	u32 buffer_mode : 2;
	u32 file_kind : 3;

#ifdef _MSL_WIDE_CHAR
	u32 file_orientation : 2;
#endif

	u32 binary_io : 1;
} file_modes;

enum __io_states { __neutral, __writing, __reading, __rereading };

typedef struct __file_states {
	u32 io_state : 3;
	u32 free_buffer : 1;

	u8 eof;
	u8 error;
} file_states;

typedef void* __ref_con;
typedef void (*__idle_proc)(void);
typedef int (*__pos_proc)(__file_handle file, fpos_t* position, int mode, __ref_con ref_con);
typedef int (*__io_proc)(__file_handle file, char* buff, size_t* count, __ref_con ref_con);
typedef int (*__close_proc)(__file_handle file);

struct _IO_FILE {
	__file_handle mHandle;
	file_modes mMode;
	file_states mState;
	u8 mIsDynamicallyAllocated;
	u8 mCharBuffer;
	u8 mCharBufferOverflow;
	u8 mUngetcBuffer[__ungetc_buffer_size];
	wchar_t mUngetcWideBuffer[__ungetc_buffer_size];
	u32 mPosition;
	char* mBuffer;
	u32 mBufferSize;
	char* mBufferPtr;
	u32 mBufferLength;
	u32 mBufferAlignment;
	u32 mBufferLength2;
	u32 mBufferPosition;
	__pos_proc positionFunc;
	__io_proc readFunc;
	__io_proc writeFunc;
	__close_proc closeFunc;
	__ref_con ref_con;
	_IO_FILE* mNextFile;
};

typedef struct _IO_FILE FILE;

extern FILE __files[4];

#ifdef __cplusplus
extern "C" {
#endif

int fflush(FILE* __stream);
void free(void*);
int __flush_buffer(FILE* file, size_t* length);
void __prep_buffer(FILE* file);
u32 __flush_all();

#ifdef __cplusplus
};
#endif

#endif
