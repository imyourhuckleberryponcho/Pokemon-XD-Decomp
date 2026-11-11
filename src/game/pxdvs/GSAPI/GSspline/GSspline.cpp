#include <dolphin/types.h>
#include "game/gcdata.h"

#pragma pool_strings off

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

extern "C" {
void* GSmemAlloc(u32);
void GSmemFree(void*);
void GSlogWrite(const char*, ...);

static void GSsplineGetVectorValue(GSspline* spline) {
    if (spline->coefficients == 0) GSlogWrite("GSsplineGetVectorValue: spline parameters not initialised!");
    else GSlogWrite("GSsplineGetVectorValue: wrong data type!");
}

static void GSsplineGetFloatValue(GSspline* spline) {
    if (spline->coefficients == 0) GSlogWrite("GSsplineGetFloatValue: spline parameters not initialised!");
    else GSlogWrite("GSsplineGetFloatValue: wrong data type!");
}

void GSsplineFree(GSspline* spline) {
    if (spline) {
        GSmemFree(spline->dataAllocation);
        GSmemFree(spline->allocation);
    }
}

void GSsplineAddControlVectorValue(GSspline* spline, GSvec* value, f32 time) {
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
                    else if (time < spline->times[timeIndex - 1]) GSlogWrite("GSsplineAddControlVectorValue: Warning! We are going back in Time!");
                    if (spline->count == spline->capacity) spline->lastTime = time;
                    spline->timeCount++;
                }
            } else GSlogWrite("GSsplineAddControlVectorValue: cannot add control point!");
        } else GSlogWrite("GSsplineAddControlVectorValue: wrong data type!");
    }
}

static void GSsplineAddControlFloatValue(GSspline* spline) {
    if (spline->count == 0) GSlogWrite("GSsplineAddControlFloatValue: Warning! We are going back in Time!");
    else if (spline->count == 1) GSlogWrite("GSsplineAddControlFloatValue: cannot add control point!");
    else GSlogWrite("GSsplineAddControlFloatValue: wrong data type!");
}

static void GSsplineInitialise(GSspline* spline) {
    if (spline->count < 2) GSlogWrite("GSsplineInitialise: invalid number of control points!");
}

GSspline* GSsplineCreate(s32 interpolation, s32 dataType, u8 count) {
    GSspline* spline = 0;
    if (count < 2) { GSlogWrite("GSsplineCreate: too few control points; minimum is 2!"); return 0; }
    if ((interpolation == 1 || interpolation == 2) && (count - 1) % 3 != 0) {
        if (count == 2) { GSlogWrite("GSsplineCreate: invalid number of control points. Forcing Linear interpolation!"); interpolation = 0; }
        else { GSlogWrite("GSsplineCreate: invalid number of control points. Forcing Lagrance interpolation!"); interpolation = 3; }
    } else if (count == 2 && interpolation != 0) {
        interpolation = 0; GSlogWrite("GSsplineCreate: spline has 2 control points; forcing Linear interpolation!");
    }
    void* allocated = GSmemAlloc(GC_SIZE(sizeof(GSspline), 40));
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
                    spline->coefficients = 0;
                    spline->times = (f32*)data + count;
                    spline->values = data;
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
                    spline->coefficients = 0;
                    spline->times = (f32*)data + count;
                    spline->values = data;
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
