#ifndef GAME_SHARED_BINSTREAM_H
#define GAME_SHARED_BINSTREAM_H
// GSBinWriteStream / GSBinReadStream layout , as used by matched peopleSave, tiga,
// tvariant, floorFieldCamera. Methods are DECLARED only: the original defines them as inline
// functions; define the bodies you need as `inline` at the BOTTOM of your .cpp (after their callers)
// so they come out as weak functions at the end of the object like the target. Copy bodies from
// src/game/pxdvs/app/floor/floorFieldCamera.cpp or src/game/pxdvs/app/people/peopleSave.cpp.
#include <dolphin/types.h>

class GSBinWriteStream {
public:
    u8* begin;        // 0x00
    u8* current;      // 0x04
    s32 size;         // 0x08
    void* allocation; // 0x0C
    u8 writing;       // 0x10
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
    u8* begin;   // 0x00
    u8* current; // 0x04
    s32 size;    // 0x08
    GSBinReadStream(void* data, u32 length);
    u8 readU8();
    bool readBool();
    u16 readU16();
    u32 readU32();
    f32 readFloat();
};

#endif
