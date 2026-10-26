#include "types.h"
#include "PowerPC_EABI_Support/MSL_C/MSL_Common/ansi_files.h"
#include "PowerPC_EABI_Support/MSL_C/MSL_Common/critical_regions.h"

static char stdin_buff[0x100];
static char stdout_buff[0x100];
static char stderr_buff[0x100];

extern void fclose(FILE*);
extern int __read_console(u32, char*, u32*, void*);
extern int __write_console(u32, char*, u32*, void*);
extern int __close_console(u32);

FILE __files[4] =
{
	{ 0,
	  0,
	  1,
	  1,
	  __console_file,
	  0,
	  __neutral,
	  0,
	  0,
	  0,
	  0,
	  0,
	  0,
	  0,
	  0,
	  0,
	  0,
	  0,
	  stdin_buff,
	  sizeof(stdin_buff),
	  stdin_buff,
	  0,
	  0,
	  0,
	  0,
	  nullptr,
	  &__read_console,
	  &__write_console,
	  &__close_console,
	  0,
	  &__files[1]
	},
	{ 1,
	  0,
	  2,
	  1,
	  __console_file,
	  0,
	  __neutral,
	  0,
	  0,
	  0,
	  0,
	  0,
	  0,
	  0,
	  0,
	  0,
	  0,
	  0,
	  stdout_buff,
	  sizeof(stdout_buff),
	  stdout_buff,
	  0,
	  0,
	  0,
	  0,
	  nullptr,
	  &__read_console,
	  &__write_console,
	  &__close_console,
	  0,
	  &__files[2]
	},
	{ 2,
	  0,
	  2,
	  0,
	  __console_file,
	  0,
	  __neutral,
	  0,
	  0,
	  0,
	  0,
	  0,
	  0,
	  0,
	  0,
	  0,
	  0,
	  0,
	  stderr_buff,
	  sizeof(stderr_buff),
	  stderr_buff,
	  0,
	  0,
	  0,
	  0,
	  nullptr,
	  &__read_console,
	  &__write_console,
	  &__close_console,
	  0,
	  &__files[3]
	},
};

u32 __flush_all();
void __close_all();

u32 __flush_all()
{
	u32 retval = 0;
	FILE* __stream;
	__stream = &__files[0];
	while (__stream) {
		if ((__stream->mMode.file_kind) && (fflush(__stream))) {
			retval = -1;
		}
		__stream = __stream->mNextFile;
	};
	return retval;
}

void __close_all()
{
	FILE* p = &__files[0];
	FILE* plast;

	__begin_critical_region(stdin_access);

	while (p) {
		if (p->mMode.file_kind != __closed_file) {
			fclose(p);
		}

		plast = p;
		p     = p->mNextFile;
		if (plast->mIsDynamicallyAllocated)
			free(plast);
		else {
			plast->mMode.file_kind = __unavailable_file;
			if ((p != NULL) && p->mIsDynamicallyAllocated)
				plast->mNextFile = nullptr;
		}
	}

	__end_critical_region(stdin_access);
}
