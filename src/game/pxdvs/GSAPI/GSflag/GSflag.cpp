#include <dolphin/types.h>

#pragma pool_strings off

struct FlagData {
    u8 level : 2;
    u8 length : 6;
    u8 unk1;
    u16 pos;
    u16 unk4;
};

struct FlagLevel {
    u32 numWords;
    u32* bits;
};

extern "C" {

extern FlagData* flag_data;
extern u32* flag_data_number;
extern FlagLevel* flag_level;
static u32 _flagAND[33] = {
    0x00000000, 0x00000001, 0x00000003, 0x00000007, 0x0000000F, 0x0000001F, 0x0000003F, 0x0000007F, 0x000000FF, 0x000001FF, 0x000003FF, 0x000007FF, 0x00000FFF, 0x00001FFF, 0x00003FFF, 0x00007FFF, 0x0000FFFF, 0x0001FFFF, 0x0003FFFF, 0x0007FFFF, 0x000FFFFF, 0x001FFFFF, 0x003FFFFF, 0x007FFFFF, 0x00FFFFFF, 0x01FFFFFF, 0x03FFFFFF, 0x07FFFFFF, 0x0FFFFFFF, 0x1FFFFFFF, 0x3FFFFFFF, 0x7FFFFFFF, 0xFFFFFFFF,
};

void GSlogWrite(const char* fmt, ...);

static u32 _flagGet(u32* bits, FlagData* data, u32 id);
static void _flagSet(u32* bits, FlagData* data, u32 id, u32 value);
static u32 _flagGetBitLength(u32 value);
void GSflagInitBitPos(FlagData* data, u32 count, u32 limit1, u32 limit2, u32 limit3);
u32 GSflagGet(u32 id);
void GSflagSet(u32 id, u32 value);

bool GSflagTest(u32 id) {
    return GSflagGet(id) != 0;
}

void GSflagOff(u32 id) {
    GSflagSet(id, 0);
}

void GSflagOn(u32 id) {
    GSflagSet(id, 1);
}

u32 GSflagGet(u32 id) {
    return _flagGet(flag_level[flag_data[id].level].bits, flag_data, id);
}

void GSflagSet(u32 id, u32 value) {
    _flagSet(flag_level[flag_data[id].level].bits, flag_data, id, value);
}

static u32 _flagGet(u32* bits, FlagData* data, u32 id) {
    u32 pos;
    u32 word;
    u32 length;
    u32 shift;

    if (bits == NULL) {
        GSlogWrite("ERROR[GSflagGet]:Initialization has not finished.\n");
        return 0;
    }
    pos = data[id].pos;
    length = data[id].length;
    word = pos >> 5;
    shift = pos & 0x1F;
    if (length > 1) {
        u32 low = bits[word];
        u32 high = bits[word + 1];

        low >>= shift;
        high <<= 32 - shift;
        return (high | low) & _flagAND[length];
    }
    return (bits[word] >> shift) & 1;
}

static void _flagSet(u32* bits, FlagData* data, u32 id, u32 value) {
    u32 length;
    u32 pos;
    u32 bitLength;
    u32 word;
    u32 shift;

    if (bits == NULL) {
        GSlogWrite("ERROR[GSflagSet]:Initialization has not finished.\n");
        return;
    }
    pos = data[id].pos;
    length = data[id].length;
    bitLength = _flagGetBitLength(value);
    if (bitLength > length) {
        GSlogWrite("ERROR[GSflagSet]:Overflow BitValue FlagID=%d Value=%d (%d BitLength=%d)>(Limit=%dBit).\n", id,
                   value, value, bitLength, length);
        value &= _flagAND[length];
    }
    word = pos >> 5;
    shift = pos & 0x1F;
    if (length > 1) {
        u32 low = bits[word];
        u32 v = value << shift;
        low &= ~(_flagAND[length] << shift);
        bits[word] = v | low;
        if (length + shift >= 32) {
            u32 high;
            u32 over = length + shift - 32;
            high = bits[word + 1];
            v = value >> (length - over);
            high &= ~_flagAND[over];
            bits[word + 1] = v | high;
        }
    } else if (value == 0) {
        bits[word] &= ~(1 << shift);
    } else {
        bits[word] |= 1 << shift;
    }
}

static u32 _flagGetBitLength(u32 value) {
    return 32 - __cntlzw(value);
}

void GSflagClear(u32 level) {
    u32* bits = flag_level[level].bits;
    u32 num;
    u32 i;
    if (bits == NULL) {
        GSlogWrite("ERROR[GSflagClear]:Initialization has not finished.\n");
        return;
    }
    num = flag_level[level].numWords;
    for (i = 0; i < num; i++) {
        bits[i] = 0;
    }
}

#pragma dont_inline on
void GSflagInit(u32* bits1, u32 num1, u32* bits2, u32 num2, u32* bits3, u32 num3) {
    GSflagInitBitPos(flag_data, *flag_data_number, num1, num2, num3);
    flag_level[1].bits = bits1;
    flag_level[2].bits = bits2;
    flag_level[3].bits = bits3;
    flag_level[1].numWords = num1;
    flag_level[2].numWords = num2;
    flag_level[3].numWords = num3;
    GSflagClear(1);
    GSflagClear(2);
    GSflagClear(3);
}
#pragma dont_inline reset

void GSflagInitBitPos(FlagData* flags, u32 count, u32 limit1, u32 limit2, u32 limit3) {
    FlagData* data = flags;
    u16 pos1 = 0;
    u16 pos2 = 0;
    u16 pos3 = 0;
    u32 i;

    for (i = 0; i < count; data++, i++) {
        u32 length = data->length;
        if (length > 32) {
            GSlogWrite("ERROR[GSflagInit]:Overflow BitLength FlagID=%d (Length=%d)>(Limit=%dBit).\n", i, length, 32);
            data->length = 32;
        } else if (length == 0) {
            GSlogWrite("ERROR[GSflagInit]:Zero BitLength FlagID=%d (Length=%d)>(Limit=%dBit).\n", i, length, 32);
            data->length = 1;
        }
        switch (data->level) {
        case 1:
            data->pos = pos1;
            pos1 += data->length;
            break;
        case 2:
            data->pos = pos2;
            pos2 += data->length;
            break;
        case 3:
            data->pos = pos3;
            pos3 += data->length;
            break;
        }
    }
    if (limit1 <= (pos1 + 31) / 32) {
        GSlogWrite("ERROR[GSflagInit]:Overflow FlagLevel0 (Use Bytes=%d)>=(Limit Bytes=%d).\n", (pos1 + 31) / 32, limit1);
    }
    if (limit2 <= (pos2 + 31) / 32) {
        GSlogWrite("ERROR[GSflagInit]:Overflow FlagLevel1 (Use Bytes=%d)>=(Limit Bytes=%d).\n", (pos2 + 31) / 32, limit2);
    }
    if (limit3 <= (pos3 + 31) / 32) {
        GSlogWrite("ERROR[GSflagInit]:Overflow FlagLevel2 (Use Bytes=%d)>=(Limit Bytes=%d).\n", (pos3 + 31) / 32, limit3);
    }
}

}
