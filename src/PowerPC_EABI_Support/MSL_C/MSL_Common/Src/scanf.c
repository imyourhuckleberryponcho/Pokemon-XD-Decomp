#include "math.h"
#include "stdarg.h"
#include "ctype.h"
#include "stdio.h"
#include "PowerPC_EABI_Support/MSL_C/MSL_Common/stdio_api.h"

typedef s64 intmax_t;

#define PTRDIFF __typeof__((char*)0 - (char*)0)
typedef PTRDIFF ptrdiff_t;

enum argument_options {
	normal_argument,
	char_argument,
	short_argument,
	long_argument,
	long_long_argument,
	double_argument,
	long_double_argument,
	wchar_argument
};

typedef u8 char_map[32];

typedef struct {
	u8 suppress_assignment;
	u8 field_width_specified;
	u8 argument_options;
	u8 conversion_char;
	int field_width;
	char_map char_set;
} scan_format;

#define set_char_map(map, ch) map[(u8)ch >> 3] |= (1 << (ch & 7))
#define tst_char_map(map, ch) (map[(u8)ch >> 3] & (1 << (ch & 7)))

int __StringRead(void* pPtr, int ch, int act);

int __StringRead(void* pPtr, int ch, int act)
{
	char ret;
	__InStrCtrl* Iscp = (__InStrCtrl*)pPtr;

	switch (act) {
	case __GetAChar:
		ret = *(Iscp->NextChar);

		if (ret == '\0') {
			Iscp->NullCharDetected = 1;
			return -1;
		} else {
			Iscp->NextChar++;
			return (u8)ret;
		}

	case __UngetAChar:
		if (Iscp->NullCharDetected == 0) {
			Iscp->NextChar--;
		} else {
			Iscp->NullCharDetected = 0;
		}

		return ch;

	case __TestForError:
		return Iscp->NullCharDetected;
	}

	return 0;
}
