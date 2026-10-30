
#include <dolphin/types.h>
#pragma pool_strings off

#ifndef M2C_MACROS_H
#define M2C_MACROS_H
typedef s32 M2C_UNK; typedef s8 M2C_UNK8; typedef s16 M2C_UNK16; typedef s32 M2C_UNK32; typedef s64 M2C_UNK64;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(u32)(expr))
#define M2C_ERROR(desc) (0)
#define M2C_TRAP_IF(cond) (0)
#define M2C_BREAK() (0)
#define M2C_SYNC() (0)
#ifdef __cplusplus
template <int N> struct M2C_Blob { u8 b[N]; };
#define M2C_STRUCT_COPY(dst, src, size) (*(M2C_Blob<size>*)(dst) = *(M2C_Blob<size>*)(src))
#else
#define M2C_STRUCT_COPY(dst, src, size) (*(dst) = *(src))
#endif
#define M2C_CARRY 0
#define MULT_HI(a, b) ((s32)(((s64)(s32)(a) * (s64)(s32)(b)) >> 32))
#define MULTU_HI(a, b) ((u32)(((u64)(u32)(a) * (u64)(u32)(b)) >> 32))
#endif
struct GSmemCell;
struct GSmemHeapDesc;
enum OSHeapHandle { OSHeapHandle_draft_dummy };

extern "C" {



struct GSmemCell {
    GSmemCell* prev;
    GSmemCell* next;
    s32 size;
    u32 addr;
    s16 layer;
    u32 get_area(GSmemHeapDesc*);
    u32 start() { return addr; }
    s32 getSize() { return size; }
    GSmemCell* getNext() { GSmemCell* n = next; return n; }
    u32 end() { return addr + size; }
    void init(int);
    void clear();
};
struct GSmemHeapDesc {
    s32 size;
    GSmemCell* free;
    GSmemCell* allocated;
    s32 type;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    GSmemCell* freeCells;
    u8 unk24[8];
    u8 unk2C;
    u8 pad2D[3];
    void addfreeCellList(GSmemCell*);
    s32 getHeaderSize();
    GSmemCell* searchAllocCell(void*);
    GSmemCell* createNewCell();
};

extern "C" {
s16 GSmemGetCurrentLayer();
s32 GSmemVisitHeapAllocated(s32 heap, void (*func)(u32, s32, u64), u64 user);
void* OSAllocFromHeap(OSHeapHandle heap, u32 size);
s32 OSCheckHeap(OSHeapHandle heap);
s32 OSCreateExternalHeap(s32 p0, s32 p1, s32 *p2, s32 p3);
OSHeapHandle OSCreateHeap(void* start, void* end);
void OSDestroyHeap(OSHeapHandle heap);
void OSFreeToHeap(OSHeapHandle heap, void* ptr);
s32 OSGetHeapFreeSize(s32 p0, s32 *p1, s32 *p2);
s32 OSGetHeapSize(s32 p0);
s32 OSGetHeapType(s32 p0);
void* OSInitAlloc(void* arenaStart, void* arenaEnd, int maxHeaps);
s32 OSReferentSize(void *p0);
void OSReport(const char* msg, ...);
s32 OSSetAllocMethodHeap(s32 p0, s32 p1);
OSHeapHandle OSSetCurrentHeap(OSHeapHandle heap);
s32 OSShrinkHeap(OSHeapHandle heap, void* ptr, u32 size);
void* memset(void* dst, int val, size_t n);
}
extern "C++" {
static s32* DLAddFront(GSmemCell* p0, GSmemCell* p1);
static s32* DLExtract(GSmemCell* p0, GSmemCell* p1);
static GSmemCell* DLInsert(GSmemCell* list, GSmemCell* cell, GSmemHeapDesc* hd);
}
static void* HeapArray;
static s32 NumHeaps;
static u32 ArenaStart;
static u32 ArenaEnd;
s32 __OSCurrHeap = -1;
static s8 _allocFillMode;
static s8 _freeFillMode;
void GSmemDumpHeapInfo(void) {
}
extern "C" {
s32 OSSetAllocMethodHeap(s32 p0, s32 p1) {
    s32 temp_r3;
    u8 *temp_r31;

    temp_r31 = (u8 *)HeapArray + (p0 * 0x30);
    temp_r3 = M2C_FIELD(temp_r31, s32 *, 0x10);
    M2C_FIELD(temp_r31, s32 *, 0x10) = p1;
    return temp_r3;
}
}

extern "C" {
s32 OSGetHeapType(s32 heap) {
    GSmemHeapDesc* hd = &((GSmemHeapDesc*)HeapArray)[heap];
    return hd->type;
}
}

extern "C" {
s32 OSGetHeapFreeSize(s32 heap, s32* total, s32* largest) {
    s32 sum = 0;
    s32 max = 0;
    if (heap < 0 || heap >= NumHeaps) {
        if (total != NULL) {
            *total = 0;
        }
        if (largest != NULL) {
            *largest = 0;
        }
        return 0;
    }
    GSmemHeapDesc* hd = &((GSmemHeapDesc*)HeapArray)[heap];
    for (GSmemCell* cell = hd->free; cell != NULL; cell = cell->next) {
        sum += cell->size;
        if (cell->size > max) {
            max = cell->size;
        }
    }
    if (total != NULL) {
        *total = sum;
    }
    if (largest != NULL) {
        *largest = max;
    }
    return 1;
}
}

extern "C" {
s32 OSGetHeapSize(s32 heap) {
    GSmemHeapDesc* hd;
    if (heap < 0 || heap >= NumHeaps) {
        return 0;
    }
    hd = &((GSmemHeapDesc*)HeapArray)[heap];
    return hd->size;
}
}

extern "C" {
s32 GSmemVisitHeapAllocated(s32 heap, void (*func)(u32, s32, u64), u64 user) {
    s32 count = 0;
    if (((GSmemHeapDesc*)HeapArray)[heap].size <= 0 || func == NULL) {
        return 0;
    }
    if (((GSmemHeapDesc*)HeapArray)[heap].size >= 0) {
        for (GSmemCell* cell = ((GSmemHeapDesc*)HeapArray)[heap].allocated; cell != NULL; cell = cell->next) {
            if (func != NULL) {
                func(cell->get_area(&((GSmemHeapDesc*)HeapArray)[heap]), cell->size, user);
            }
            count++;
        }
    }
    return count;
}
}

extern "C" {
s32 OSReferentSize(void* ptr) {
    s32* cell = (s32*)((u8*)ptr - 0x20);
    return cell[2] - 0x20;
}
}

extern "C" {

void OSDumpHeap(OSHeapHandle heap) {
    OSReport("\nOSDumpHeap(%d):\n", heap);
    OSReport("--------Inactive\n");
    OSReport("addr\tend\tsize\tprev\tnext\n");
    OSReport("--------Allocated\n");
    OSReport("%08xh\t%08xh\t%x\t%08xh\t%08xh\n", 0, 0, 0, 0, 0);
    OSReport("--------Free\n");
}

#define ASSERTREPORT(line, cond)                                              \
    if (!(cond)) {                                                            \
        OSReport("OSCheckHeap: Failed " #cond " in %d", line);                \
        return -1;                                                            \
    }
#define InRange(cell, start, end) ((u32)(start) <= (u32)(cell) && (u32)(cell) < (u32)(end))
#define OFFSET(n, a) (((u32)(n)) & ((a) - 1))
#define ALIGNMENT 32
#define HEADERSIZE ((sizeof(GSmemCell) + 31) & ~31)
#define MINOBJSIZE (HEADERSIZE + ALIGNMENT)
#define CHECK_CELLALIGN(hd, cell) ((hd)->type == 1 || ((hd)->type == 0 && OFFSET(cell, ALIGNMENT) == 0))

s32 OSCheckHeap(OSHeapHandle heap) {
    GSmemHeapDesc* hd;
    GSmemCell* cell;
    s32 total = 0;
    s32 free = 0;

    ASSERTREPORT(0x645, HeapArray);
    ASSERTREPORT(0x646, 0 <= heap && heap < NumHeaps);
    hd = &((GSmemHeapDesc*)HeapArray)[heap];
    ASSERTREPORT(0x649, 0 <= hd->size);

    ASSERTREPORT(0x64B, hd->allocated == NULL || hd->allocated->prev == NULL);

    for (cell = hd->allocated; cell; cell = cell->next) {
        if (hd->type == 0) {
            ASSERTREPORT(0x64F, InRange(cell, ArenaStart, ArenaEnd));
            ASSERTREPORT(0x650, CHECK_CELLALIGN( hd, cell));
        }
        ASSERTREPORT(0x652, cell->next == NULL || cell->next->prev == cell);
        ASSERTREPORT(0x653, MINOBJSIZE <= cell->size);
        ASSERTREPORT(0x654, OFFSET(cell->size, ALIGNMENT) == 0);
        total += cell->size;
        ASSERTREPORT(0x657, 0 < total && total <= hd->size);
    }

    ASSERTREPORT(0x65F, hd->free == NULL || hd->free->prev == NULL);

    for (cell = hd->free; cell; cell = cell->next) {
        if (hd->type == 0) {
            ASSERTREPORT(0x663, InRange(cell, ArenaStart, ArenaEnd));
            ASSERTREPORT(0x664, CHECK_CELLALIGN(hd, cell ));
            ASSERTREPORT(0x665, cell->next == NULL || (char*) cell + cell->size < (char*) cell->next);
        }
        ASSERTREPORT(0x667, cell->next == NULL || cell->next->prev == cell);
        ASSERTREPORT(0x668, MINOBJSIZE <= cell->size);
        ASSERTREPORT(0x669, OFFSET(cell->size, ALIGNMENT) == 0);
        total += cell->size;
        free += cell->size - hd->getHeaderSize();
        ASSERTREPORT(0x66D, 0 < total && total <= hd->size);
    }
    ASSERTREPORT(0x674, total == hd->size);
    return free;
}
}

extern "C" {
void OSDestroyHeap(OSHeapHandle heap) {
    GSmemHeapDesc* hd = &((GSmemHeapDesc*)HeapArray)[heap];
    hd->size = -1;
}
}

extern "C" {
s32 OSCreateExternalHeap(s32 start, s32 end, s32* cells, s32 count) {
    GSmemHeapDesc* hd;
    GSmemCell* cell;
    s32 i;
    s32 heap;

    end = end & ~0x1F;
    start = (start + 0x1F) & ~0x1F;
    memset(cells, 0, count * sizeof(GSmemCell));
    for (heap = 0; heap < NumHeaps; heap++) {
        hd = &((GSmemHeapDesc*)HeapArray)[heap];
        if (hd->size < 0) {
            hd->size = end - start;
            hd->unk10 = 0;
            hd->unk18 = (s32)cells;
            hd->unk1C = count;
            hd->type = 1;
            hd->unk14 = 1;
            cell = (GSmemCell*)hd->unk18;
            cell->init(hd->size);
            cell->addr = start;
            hd->free = cell;
            hd->allocated = NULL;
            hd->freeCells = NULL;
            for (i = 0; i < count; i++) {
                hd->addfreeCellList(&((GSmemCell*)cells)[i]);
            }
            return heap;
        }
    }
    return -1;
}
}

extern "C" {
OSHeapHandle OSCreateHeap(void* start, void* end) {
    int heap;
    GSmemHeapDesc* hd;
    GSmemCell* cell;

    OSReport("OSCreateHeap : start=%08xh, end=%08xh\n", start, end);
    start = (void*)(((u32)start + 0x1F) & ~0x1F);
    end = (void*)((u32)end & ~0x1F);
    for (heap = 0; heap < NumHeaps; heap++) {
        hd = &((GSmemHeapDesc*)HeapArray)[heap];
        if (hd->size < 0) {
            hd->size = (u32)end - (u32)start;
            cell = (GSmemCell*)start;
            cell->init(hd->size);
            cell->addr = (u32)cell;
            hd->free = cell;
            hd->allocated = 0;
            hd->unk2C = 0;
            return (OSHeapHandle)heap;
        }
    }
    return (OSHeapHandle)-1;
}
}

extern "C" {
void* OSInitAlloc(void* arenaStart, void* arenaEnd, int maxHeaps) {
    u32 arraySize;
    int i;
    GSmemHeapDesc* hd;

    OSReport("OSInitAlloc : arenaStart=%08xh, arenaEnd=%08xh, maxHeaps %d\n", arenaStart, arenaEnd, maxHeaps);
    arraySize = maxHeaps * sizeof(GSmemHeapDesc);
    HeapArray = arenaStart;
    NumHeaps = maxHeaps;

    for (i = 0; i < NumHeaps; i++) {
        hd = &((GSmemHeapDesc*)HeapArray)[i];
        hd->size = -1;
        hd->free = hd->allocated = 0;
        hd->type = 0;
        hd->unk14 = 0;
        hd->unk10 = 0;
        hd->unk18 = 0;
        hd->unk1C = 0;
        hd->unk2C = 0;
    }
    __OSCurrHeap = -1;
    arenaStart = (void*)((u32)((char*)HeapArray + arraySize));
    arenaStart = (void*)(((u32)arenaStart + 0x1F) & 0xFFFFFFE0);
    ArenaStart = (u32)arenaStart;
    ArenaEnd = (u32)arenaEnd & 0xFFFFFFE0;
    _allocFillMode = 0;
    _freeFillMode = 0;
    return arenaStart;
}
}

extern "C" {
OSHeapHandle OSSetCurrentHeap(OSHeapHandle p0) {
    s32 temp_r31;

    temp_r31 = __OSCurrHeap;
    __OSCurrHeap = p0;
    return (OSHeapHandle)(temp_r31);
}
}

extern "C" {
s32 OSShrinkHeap(OSHeapHandle heap, void* ptr, u32 size) {
    GSmemHeapDesc* hd;
    GSmemCell* cell;
    GSmemCell* newCell;
    u32 leftoverSize;
    s32 oldSize;

    if (size == 0) {
        return 0;
    }
    hd = &((GSmemHeapDesc*)HeapArray)[heap];
    size += hd->getHeaderSize();
    size = (size + 0x1F) & 0xFFFFFFE0;
    if (hd->type == 0) {
        if (ptr == NULL) {
            return 0;
        }
        cell = (GSmemCell*)((u8*)ptr - 0x20);
    } else {
        cell = hd->searchAllocCell(ptr);
    }
    oldSize = cell->getSize();
    leftoverSize = cell->getSize() - size;
    if (leftoverSize < 0x40) {
        return 1;
    }
    if (hd->type == 1) {
        newCell = hd->createNewCell();
        if (newCell == NULL) {
            return 0;
        }
        cell->size = size;
        newCell->addr = (u32)newCell;
    } else {
        newCell = (GSmemCell*)((u8*)cell->start() + size);
        cell->size = size;
        u32 end = cell->end();
        newCell->addr = end;
    }
    newCell->init(leftoverSize);
    hd->free = DLInsert(hd->free, newCell, hd);
    return 1;
}
}

extern "C" {
void OSFreeToHeap(OSHeapHandle heap, void* ptr) {
    GSmemHeapDesc* hd;
    GSmemCell* cell;

    hd = &((GSmemHeapDesc*)HeapArray)[heap];
    if (hd->type == 0) {
        if (ptr == NULL) {
            return;
        }
        cell = (GSmemCell*)((u32)ptr - 0x20);
    } else {
        cell = hd->searchAllocCell(ptr);
    }
    hd->allocated = (GSmemCell*)DLExtract(hd->allocated, cell);
    hd->free = DLInsert(hd->free, cell, hd);
}
}

extern "C" {
void* OSAllocFromHeap(OSHeapHandle heap, u32 size) {
    GSmemHeapDesc* hd;
    GSmemCell* cell;
    GSmemCell* c;
    GSmemCell* newCell;
    u32 leftoverSize;
    s32 max;

    hd = &((GSmemHeapDesc*)HeapArray)[heap];
    size += hd->getHeaderSize();
    size = (size + 0x1F) & 0xFFFFFFE0;
    if (hd->unk10 == 1) {
        cell = NULL;
        for (c = hd->free; c != NULL; c = c->next) {
            if ((s32)size <= c->getSize()) {
                if ((s32)size == c->getSize()) {
                    cell = c;
                    break;
                }
                if (cell != NULL) {
                    if (c->getSize() < cell->getSize()) {
                        cell = c;
                    }
                } else {
                    cell = c;
                }
            }
        }
    } else if (hd->unk10 == 3) {
        max = -1;
        cell = NULL;
        for (c = hd->free; c != NULL; c = c->getNext()) {
            if (max <= c->getSize()) {
                max = c->size;
                cell = c;
            }
        }
        if ((s32)size > max) {
            cell = NULL;
        }
    } else if (hd->unk10 == 3) {
        cell = NULL;
        for (c = hd->free; c != NULL; c = c->getNext()) {
            if ((s32)size <= c->size && cell < c) {
                cell = c;
            }
        }
    } else {
        for (cell = hd->free; cell != NULL; cell = cell->next) {
            if ((s32)size <= cell->size) {
                break;
            }
        }
    }
    if (cell == NULL) {
        hd->unk2C = 1;
        return NULL;
    }
    leftoverSize = cell->size - size;
    if (leftoverSize < 0x40U) {
        hd->free = (GSmemCell*)DLExtract(hd->free, cell);
    } else if (hd->unk10 == 3 && hd->type == 0) {
        newCell = cell;
        cell = (GSmemCell*)((u8*)cell + leftoverSize);
        newCell->size = leftoverSize;
        cell->init(size);
        cell->addr = (u32)cell;
    } else {
        if (hd->type == 1) {
            newCell = hd->createNewCell();
            if (newCell == NULL) {
                OSReport("OSAllocFromHeap: Warning- not free cell\n");
                hd->unk2C = 1;
                return NULL;
            }
            cell->size = size;
            newCell->init(leftoverSize);
            newCell->addr = cell->end();
        } else {
            newCell = (GSmemCell*)((u8*)cell + size);
            cell->size = size;
            newCell->init(leftoverSize);
            newCell->addr = (u32)newCell;
        }
        newCell->prev = cell->prev;
        newCell->next = cell->next;
        if (newCell->next != NULL) {
            newCell->next->prev = newCell;
        }
        if (newCell->prev != NULL) {
            newCell->prev->next = newCell;
        } else {
            hd->free = newCell;
        }
    }
    hd->allocated = (GSmemCell*)DLAddFront(hd->allocated, cell);
    cell->layer = GSmemGetCurrentLayer();
    hd->unk2C = 0;
    return (void*)cell->get_area(hd);
}
}

extern "C++" {
static GSmemCell* DLInsert(GSmemCell* list, GSmemCell* cell, GSmemHeapDesc* hd) {
    GSmemCell* prev;
    GSmemCell* next;
    GSmemCell* merged;

    for (next = list, prev = NULL; next; prev = next, next = next->next) {
        if (cell->start() <= next->start()) {
            break;
        }
    }
    cell->next = next;
    cell->prev = prev;
    if (next) {
        next->prev = cell;
        if (cell->end() == next->start()) {
            merged = next;
            cell->size += next->size;
            cell->next = next = next->next;
            if (next) {
                next->prev = cell;
            }
            merged->size = 0;
            if (hd != NULL && hd->type == 1) {
                hd->addfreeCellList(merged);
            }
        }
    }
    if (prev) {
        prev->next = cell;
        if (prev->end() == cell->start()) {
            merged = cell;
            prev->size += cell->size;
            prev->next = next;
            if (next) {
                next->prev = prev;
            }
            merged->size = 0;
            if (hd != NULL && hd->type == 1) {
                hd->addfreeCellList(merged);
            }
        }
        return list;
    }
    return cell;
}
}

extern "C++" {
static s32* DLExtract(GSmemCell* p0, GSmemCell* p1) {
    if ((s32 *) M2C_FIELD(p1, s32 **, 4) != NULL) {
        *M2C_FIELD(p1, s32 **, 4) = (long)(M2C_FIELD(p1, u8 **, 0));
    }
    if ((u8 *) M2C_FIELD(p1, u8 **, 0) == NULL) {
        return M2C_FIELD(p1, s32 **, 4);
    }
    M2C_FIELD(M2C_FIELD(p1, u8 **, 0), s32 **, 4) = (s32 *) M2C_FIELD(p1, s32 **, 4);
    return (s32 *) p0;
}
}

extern "C++" {
static s32* DLAddFront(GSmemCell* p0, GSmemCell* p1) {
    M2C_FIELD(p1, GSmemCell **, 4) = p0;
    M2C_FIELD(p1, s32 *, 0) = 0;
    if (p0 != NULL) {
        (*(s32*)(p0)) = (long)(p1);
    }
    return (s32 *) p1;
}
}

extern "C++" {
u32 GSmemCell::get_area(GSmemHeapDesc* heap) {
    u32 a = addr;
    return a + heap->getHeaderSize();
}
}

extern "C++" {
void GSmemCell::init(int size) {
    clear();
    this->size = size;
}
}

extern "C++" {
void GSmemCell::clear() {
    M2C_FIELD(this, s32 *, 0) = 0;
    M2C_FIELD(this, s32 *, 4) = 0;
    M2C_FIELD(this, s32 *, 8) = 0;
}
}

extern "C++" {
GSmemCell* GSmemHeapDesc::searchAllocCell(void* ptr) {
    GSmemCell* cell;
    for (cell = allocated; cell != NULL; cell = cell->next) {
        u32 area = cell->get_area(this);
        if (area != (u32)ptr) {
            continue;
        }
        {
            return cell;
        }
    }
    return NULL;
}
}

extern "C++" {
void GSmemHeapDesc::addfreeCellList(GSmemCell* cell) {
    if (cell != NULL && cell->size == 0) {
        cell->prev = NULL;
        cell->next = NULL;
        if (freeCells == NULL) {
            freeCells = cell;
        } else {
            freeCells = (GSmemCell*)DLAddFront(freeCells, cell);
        }
    }
}
}

extern "C++" {
GSmemCell* GSmemHeapDesc::createNewCell() {
    GSmemCell* cell = freeCells;
    if (cell != NULL) {
        GSmemCell* c = freeCells;
        GSmemCell* head;
        GSmemCell* next = c->next;
        freeCells = next;
        if (freeCells != NULL) {
            head = freeCells;
            freeCells->prev = NULL;
            if (head) {
            }
        }
    }
    return cell;
}
}

extern "C++" {
s32 GSmemHeapDesc::getHeaderSize() {
    if ((s32) M2C_FIELD(this, s32 *, 0xC) == 0) {
        return 0x20;
    }
    return 0;
}
}


}
