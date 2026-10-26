#ifndef GAME_SHARED_BINSTREAM_H
#define GAME_SHARED_BINSTREAM_H
#include <dolphin/types.h>

class GSBinWriteStream {
public:
    u8* begin;
    u8* current;
    s32 size;
    void* allocation;
    u8 writing;
    GSBinWriteStream();
    GSBinWriteStream(void* data, u32 length);
    GSBinWriteStream(unsigned long size);
    ~GSBinWriteStream();
    void writeU8(u8 n);
    void writeS8(s8 n);
    void writeBool(bool n);
    void writeU16(u16 n);
    void writeU32(u32 n);
    void writeFloat(f32 n);
    s32 getWriteSize() const;
    u8* getTop() const;
};

class GSBinReadStream {
public:
    u8* begin;
    u8* current;
    s32 size;
    GSBinReadStream(void* data, u32 length);
    u8 readU8();
    bool readBool();
    u16 readU16();
    u32 readU32();
    f32 readFloat();
};

#endif
