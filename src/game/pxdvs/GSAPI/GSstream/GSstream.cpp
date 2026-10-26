#include <dolphin/types.h>
#include <libc/stdarg.h>
#include <libc/stdio.h>
#include <libc/string.h>

extern "C" {
s32 GSdvdWrite(void* file, const char* data, long size, s32 offset);
bool GSdvdOpenTest(const char* path);
s32 GSdvdRemove(const char* path);
void* GSdvdCreate(const char* path);
void GSdvdClose(void* file);
}

class GSstreamFileOutput {
public:
    GSstreamFileOutput();
    ~GSstreamFileOutput();
    bool open(const char* path);
    bool is_open() const;
    bool write(const char* data, long size);
    bool writeString(const char* str);
    bool writePrintf(const char* fmt, ...);

private:
    void* m_file;
    s32 m_offset;
};

bool GSstreamFileOutput::writePrintf(const char* fmt, ...) {
    va_list args;
    char buf[0x200];
    va_start(args, fmt);
    vsprintf(buf, fmt, args);
    return writeString(buf);
}

bool GSstreamFileOutput::writeString(const char* str) {
    long len = strlen(str);
    write(str, len);
    return true;
}

bool GSstreamFileOutput::write(const char* data, long size) {
    if (GSdvdWrite(m_file, data, size, m_offset) < 0) {
        return false;
    }
    m_offset += size;
    return true;
}

bool GSstreamFileOutput::is_open() const {
    return m_file != NULL;
}

#pragma dont_inline on
bool GSstreamFileOutput::open(const char* path) {
    if (m_file != NULL) {
        return false;
    }
    if (GSdvdOpenTest(path) && GSdvdRemove(path) == 0) {
        return false;
    }
    m_file = GSdvdCreate(path);
    m_offset = 0;
    return is_open();
}
#pragma dont_inline reset

GSstreamFileOutput::~GSstreamFileOutput() {
    if (m_file != NULL) {
        GSdvdClose(m_file);
    }
}

GSstreamFileOutput::GSstreamFileOutput() {
    m_file = NULL;
}
