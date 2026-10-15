#include <dolphin/mtx.h>

struct GSbezier {
    Vec start;
    Vec end;
    Vec control1;
    Vec control2;
};

extern "C" {

// Unknown function that was dead-stripped from the final link. It used 1.0f,
// which puts that constant first in .sdata2.
f32 GSbezierOneMinus(f32 t) { return 1.0f - t; }

void GSbezierCalculateVector(Vec* out, GSbezier* bezier, f32 t) {
    Vec tmp;
    if (t < 0.0f) {
        t = 0.0f;
    }
    if (t > 1.0f) {
        t = 1.0f;
    }
    f32 t2 = t * t;
    f32 it = 1.0f - t;
    f32 it2 = it * it;
    PSVECScale(&bezier->start, out, it2 * it);
    PSVECScale(&bezier->control1, &tmp, 3.0f * t * it2);
    PSVECAdd(out, &tmp, out);
    PSVECScale(&bezier->control2, &tmp, 3.0f * t2 * it);
    PSVECAdd(out, &tmp, out);
    PSVECScale(&bezier->end, &tmp, t2 * t);
    PSVECAdd(out, &tmp, out);
}

}
