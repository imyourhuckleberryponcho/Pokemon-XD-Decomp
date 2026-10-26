#ifndef SYSDOLPHIN_BASELIB_DEBUG_H
#define SYSDOLPHIN_BASELIB_DEBUG_H

#include <Runtime/platform.h>

#include <dolphin/os.h> // IWYU pragma: keep

typedef void (*ReportCallback)(const unsigned char*, size_t);
typedef void (*PanicCallback)(OSContext*, ...);

ATTRIBUTE_NORETURN void __assert(const char*, u32, const char*);

void HSD_LogInit(void);
ATTRIBUTE_NORETURN void HSD_Panic(const char*, u32, const char*);



#ifndef HSD_FILE_NAME
#define HSD_FILE_NAME __FILE__
#endif


#define HSD_ASSERT_IN(file, line, cond)                                           ((cond) ? ((void) 0) : __assert(file, line, #cond))

#ifdef MUST_MATCH
#define HSD_ASSERT(line, cond)                                                \
    ((cond) ? ((void) 0) : __assert(HSD_FILE_NAME, line, #cond))
#define HSD_ASSERTMSG(line, cond, msg)                                        \
    ((cond) ? ((void) 0) : __assert(HSD_FILE_NAME, line, msg))
#define HSD_ASSERTREPORT(line, cond, ...)                                     \
    ((cond) ? (void) 0                                                        \
            : (OSReport(__VA_ARGS__), __assert(HSD_FILE_NAME, line, #cond)))
#else
#define HSD_ASSERT(line, cond)                                                \
    ((cond) ? ((void) 0) : __assert(HSD_FILE_NAME, __LINE__, #cond))
#define HSD_ASSERTMSG(line, cond, msg)                                        \
    ((cond) ? ((void) 0) : __assert(HSD_FILE_NAME, __LINE__, msg))
#define HSD_ASSERTREPORT(line, cond, ...)                                     \
    ((cond) ? (void) 0                                                        \
            : (OSReport(__VA_ARGS__), __assert(HSD_FILE_NAME, __LINE__, #cond)))
#endif

void HSD_SetReportCallback(ReportCallback cb);
void HSD_SetPanicCallback(PanicCallback cb);

#endif
