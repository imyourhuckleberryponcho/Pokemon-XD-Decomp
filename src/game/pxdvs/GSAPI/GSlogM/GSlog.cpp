// Source order is bottom-to-top (-inline deferred).
#include <dolphin/types.h>
#pragma pool_strings off
#include <libc/stdarg.h>

extern "C" {
void* GSmemAlloc(u32 size);
void GSmemFree(void* ptr);
void* OSGetCurrentThread();
u32 strlen(const char* s);
char* strchr(const char* s, int c);
}

static char _logOutputBuf[0x100];
static char _logTimeStampBuf[0x14];
static char* _inthexTable = "0123456789ABCDEF";

static u8* _logBuffer;
static u16* _lenBuffer;
static u32 _logBufSize;
static u32 _logLineCount;
static u32 _logMaxLines;
static u32 _logStampMode;
static void* _mainThread;

void logStrRev(char* start) {
    char* end = &start[strlen(start) - 1];

    while (start < end) {
        *start ^= *end;
        *end ^= *start;
        *start++ ^= *end--;
    }
}

int logStr2Int(char* s) {
    int value = 0;

    while (*s != 0) {
        if (*s < '0' || *s > '9') {
            break;
        }
        value *= 10;
        value += *s++ - '0';
    }
    return value;
}

void logInt2Str(int value, char* buf) {
    char* p = buf;
    u8 negative = 0;

    if (value < 0) {
        negative = 1;
        value = -value;
    }
    do {
        *p++ = _inthexTable[value % 10];
        value /= 10;
    } while (value != 0);
    if (negative == 1) {
        *p++ = '-';
    }
    *p = 0;
    logStrRev(buf);
}

void logHex2Str(u32 value, char* buf, bool upper) {
    char* p = buf;

    do {
        *p = _inthexTable[value & 0xF];
        if (!upper && *p >= 'A') {
            *p += 'a' - 'A';
        }
        value >>= 4;
        p++;
    } while (value != 0);
    *p = 0;
    logStrRev(buf);
}

void logFloat2Str(f32 value, char* buf, char* fraction) {
    int whole;
    int zeros;
    f32 scale;
    char* p;
    int length;

    if (value < 0.0f) {
        *buf++ = '-';
        value = -value;
    }
    whole = value;
    logInt2Str(whole, buf);
    value -= whole;
    scale = 0.1f;
    for (zeros = 0; zeros < 10; zeros++) {
        if (scale <= value) {
            break;
        }
        scale /= 10.0f;
    }
    char* q = fraction;
    while (zeros-- != 0) {
        *q++ = '0';
    }
    value *= 1000000000.0f;
    whole = value;
    logInt2Str(whole, q);
    length = strlen(fraction);
    p = fraction + length;
    while (length < 10) {
        *p++ = '0';
        length++;
    }
    *p = 0;
}

extern "C" {

void logVsnprintf_float(char* output, u32 capacity, char* format, va_list args) {
    static char spec[16];
    static char field[16];
    static char fraction[16];
    char* src = format;
    char* dst = output;
    char* token;
    char* text;
    u8 done = 0;
    u8 parsing = 0;
    u8 ready = 0;
    u8 leftJustify = 0;
    u8 zeroPad = 0;
    int width;
    u32 hex;
    int number;
    f32 value;

    while (!done) {
        if (!parsing) {
            if (*src == '%') {
                if (src[1] == '%') {
                    *dst++ = '%';
                    src++;
                } else {
                    token = spec;
                    parsing = 1;
                }
            } else {
                *dst++ = *src;
            }
        } else {
            switch (*src) {
            case 'c':
                text = field;
                field[0] = va_arg(args, int);
                field[1] = 0;
                ready = 1;
                break;
            case 'd':
                number = va_arg(args, int);
                logInt2Str(number, field);
                text = field;
                ready = 1;
                break;
            case 'f':
                value = va_arg(args, double);
                logFloat2Str(value, field, fraction);
                text = field;
                ready = 1;
                break;
            case 's':
                text = va_arg(args, char*);
                ready = 1;
                break;
            case 'X':
            case 'x':
                hex = va_arg(args, u32);
                if (*src == 'X') {
                    logHex2Str(hex, field, true);
                } else {
                    logHex2Str(hex, field, false);
                }
                text = field;
                ready = 1;
                break;
            default:
                *token++ = *src;
                break;
            }

            if (ready == 1) {
                int length;

                *token = 0;
                token = spec;
                if (*token == '-') {
                    leftJustify = 1;
                    token++;
                }
                if (*token == '0') {
                    zeroPad = 1;
                    token++;
                }
                width = logStr2Int(token);
                length = strlen(text);
                if (width > length) {
                    width -= length;
                    if (!leftJustify) {
                        while (width-- != 0 && (u32)(dst - output) < capacity) {
                            if (zeroPad) {
                                *dst++ = '0';
                            } else {
                                *dst++ = ' ';
                            }
                        }
                    }
                }
                while (*text != 0 && (u32)(dst - output) < capacity) {
                    *dst++ = *text++;
                }
                if (*src == 'f') {
                    char* dot;

                    text = fraction;
                    length = strlen(fraction);
                    dot = strchr(token, '.');
                    if (dot != 0) {
                        width = logStr2Int(dot + 1);
                        if (width > 0 && length > width) {
                            text[width] = 0;
                        }
                    }
                    *dst++ = '.';
                    while (*text != 0 && (u32)(dst - output) < capacity) {
                        *dst++ = *text++;
                    }
                }
                if (leftJustify == 1) {
                    while (width-- != 0 && (u32)(dst - output) < capacity) {
                        *dst++ = ' ';
                    }
                }
                leftJustify = 0;
                zeroPad = 0;
                parsing = 0;
                ready = 0;
            }
        }

        if (*src == 0 || (u32)(dst - output) >= capacity) {
            done = 1;
        }
        src++;
    }
    *dst = 0;
}


static void logVsnprintfDead(char* output, u32 capacity, char* format, va_list args) {
    static char fmtbuf[16];
    static char cvtbuf[16];
    static char cvtbuf2[16];
    fmtbuf[0] = 0;
    cvtbuf[0] = 0;
    cvtbuf2[0] = 0;
}

static void logWriteDead(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    logVsnprintf_float(_logOutputBuf, 0xFF, (char*)fmt, args);
    _logOutputBuf[0xFF] = 0;
    logVsnprintf_float(_logTimeStampBuf, 0x14, "%d/%02d %d:%02d:%02d] ", args);
}


void GSlogWrite(const char* fmt, ...);

u32 GSlogInit(u32 size, u32 stampMode) {
    _logStampMode = stampMode;
    _logBufSize = size;
    if (size == 0) {
        GSlogWrite("GSlog: Init OK, no buffer\n");
        return 1;
    }

    _logBuffer = (u8*)GSmemAlloc(size);
    if (_logBuffer == 0) {
        GSlogWrite("GSlog: Init FAILED\n");
        return 0;
    }

    _logMaxLines = size >> 7;
    _lenBuffer = (u16*)GSmemAlloc((size >> 6) & ~1);
    if (_lenBuffer == 0) {
        GSmemFree(_logBuffer);
        GSlogWrite("GSlog: Init FAILED\n");
        return 0;
    }

    _mainThread = OSGetCurrentThread();
    GSlogWrite("GSlog: Init OK, log buffer size %d bytes\n", _logBufSize);
    return 1;
}

void GSlogSetIP() {}

void GSlogWrite(const char* fmt, ...) {}

void GSlogWritef(const char* fmt, ...) {}

u32 GSlogGetLineCount() {
    return _logBuffer == 0 ? 0 : _logLineCount;
}

u32 GSlogGetLine(u32 count) {
    u16* entries;
    u32 sum;
    u32 i;

    if (_logBuffer == 0) {
        return 0;
    }
    if (count > _logLineCount) {
        return 0;
    }
    entries = _lenBuffer;
    sum = 0;
    for (i = 0; i < count; i++) {
        sum += entries[i];
    }
    return (u32)_logBuffer + sum;
}

}
