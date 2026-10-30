#include <dolphin/types.h>

struct GSvec { f32 x, y, z; };
struct GSspline {
    s32 interpolation, dataType;
    u8 capacity, count, reservedA, timeCount;
    void* values;
    f32* coefficients;
    f32* times;
    f32 firstTime, lastTime;
    void* allocation;
    void* dataAllocation;
};

static const struct {
    char text0[60];
    char text1[44];
    char text2[60];
    char text3[40];
    char text4[68];
    char text5[60];
    char text6[48];
    char text7[68];
    char text8[56];
    char text9[48];
    char text10[56];
    char text11[56];
    char text12[80];
    char text13[84];
    char text14[76];
} messages = {
    "GSsplineGetVectorValue: spline parameters not initialised!",
    "GSsplineGetVectorValue: wrong data type!",
    "GSsplineGetFloatValue: spline parameters not initialised!",
    "GSsplineGetFloatValue: wrong data type!",
    "GSsplineAddControlVectorValue: Warning! We are going back in Time!",
    "GSsplineAddControlVectorValue: cannot add control point!",
    "GSsplineAddControlVectorValue: wrong data type!",
    "GSsplineAddControlFloatValue: Warning! We are going back in Time!",
    "GSsplineAddControlFloatValue: cannot add control point!",
    "GSsplineAddControlFloatValue: wrong data type!",
    "GSsplineInitialise: invalid number of control points!",
    "GSsplineCreate: too few control points; minimum is 2!",
    "GSsplineCreate: invalid number of control points. Forcing Linear interpolation!",
    "GSsplineCreate: invalid number of control points. Forcing Lagrance interpolation!",
    "GSsplineCreate: spline has 2 control points; forcing Linear interpolation!"
};
extern "C" {
void* GSmemAlloc(u32);
void GSmemFree(void*);
void GSlogWrite(const char*, ...);

void GSsplineFree(GSspline* spline) {
    if (spline) {
        GSmemFree(spline->dataAllocation);
        GSmemFree(spline->allocation);
    }
}

void GSsplineAddControlVectorValue(GSspline* spline, GSvec* value, f32 time) {
    const char* text = messages.text0;
    if (spline) {
        if (spline->dataType == 1) {
            if (spline->count < spline->capacity) {
                u8 addTime = 1;
                if ((spline->interpolation == 1 || spline->interpolation == 2) && spline->count % 3 != 0)
                    addTime = 0;
                GSvec* point = (GSvec*)spline->values + spline->count;
                point->x = value->x; point->y = value->y; point->z = value->z;
                spline->times[spline->count] = time;
                spline->count++;
                if (addTime) {
                    u8 timeIndex = spline->timeCount;
                    spline->times[timeIndex] = time;
                    if (timeIndex == 0) spline->firstTime = time;
                    else if (time < spline->times[timeIndex - 1]) GSlogWrite(text + 0xcc);
                    if (spline->count == spline->capacity) spline->lastTime = time;
                    spline->timeCount++;
                }
            } else GSlogWrite(text + 0x110);
        } else GSlogWrite(text + 0x14c);
    }
}

GSspline* GSsplineCreate(s32 interpolation, s32 dataType, u8 count) {
    GSspline* spline = 0;
    const char* text = messages.text0;
    if (count < 2) { GSlogWrite(text + 0x260); return 0; }
    if ((interpolation == 1 || interpolation == 2) && (count - 1) % 3 != 0) {
        if (count == 2) { GSlogWrite(text + 0x298); interpolation = 0; }
        else { GSlogWrite(text + 0x2e8); interpolation = 3; }
    } else if (count == 2 && interpolation != 0) {
        interpolation = 0; GSlogWrite(text + 0x33c);
    }
    void* allocated = GSmemAlloc(sizeof(GSspline));
    if (allocated) {
        spline = (GSspline*)allocated;
        spline->allocation = allocated;
        spline->interpolation = interpolation;
        spline->dataType = dataType;
        spline->count = 0;
        spline->timeCount = 0;
        switch (interpolation) {
        case 0:
            if (dataType == 1) {
                void* data = GSmemAlloc(count * 16);
                if (data) {
                    spline->dataAllocation = data;
                    spline->values = data;
                    spline->coefficients = 0;
                    spline->times = (f32*)((GSvec*)data + count);
                    spline->capacity = count;
                    spline->dataType = 1;
                } else { GSmemFree(spline->allocation); spline = 0; }
            }
            else {
                void* data = GSmemAlloc(count * 8);
                if (data) {
                    spline->dataAllocation = data;
                    spline->values = data;
                    spline->coefficients = 0;
                    spline->times = (f32*)data + count;
                    spline->capacity = count;
                    spline->dataType = 0;
                } else { GSmemFree(spline->allocation); spline = 0; }
            }
            break;
        case 1: case 2:
            if (dataType == 1) {
                void* data = GSmemAlloc(count * 12 + ((count + 2) / 3) * 4);
                if (data) {
                    spline->dataAllocation = data;
                    spline->values = data;
                    spline->coefficients = 0;
                    spline->times = (f32*)((GSvec*)data + count);
                    spline->capacity = count;
                    spline->dataType = 1;
                } else { GSmemFree(spline->allocation); spline = 0; }
            }
            else {
                void* data = GSmemAlloc((count + (count + 2) / 3) * 4);
                if (data) {
                    spline->dataAllocation = data;
                    spline->values = data;
                    spline->coefficients = 0;
                    spline->times = (f32*)data + count;
                    spline->capacity = count;
                    spline->dataType = 0;
                } else { GSmemFree(spline->allocation); spline = 0; }
            }
            break;
        default:
            if (dataType == 1) {
                void* data = GSmemAlloc(count * 20);
                if (data) {
                    spline->dataAllocation = data;
                    spline->values = data;
                    f32* coefficients = (f32*)((GSvec*)data + count);
                    spline->coefficients = coefficients;
                    spline->times = coefficients + count;
                    spline->capacity = count;
                    spline->dataType = 1;
                } else { GSmemFree(spline->allocation); spline = 0; }
            }
            else {
                void* data = GSmemAlloc(count * 3 * sizeof(f32));
                if (data) {
                    spline->dataAllocation = data;
                    spline->values = data;
                    f32* coefficients = (f32*)data + count;
                    spline->coefficients = coefficients;
                    spline->times = coefficients + count;
                    spline->capacity = count;
                    spline->dataType = 0;
                } else { GSmemFree(spline->allocation); spline = 0; }
            }
            break;
        }
    }
    return spline;
}
}
