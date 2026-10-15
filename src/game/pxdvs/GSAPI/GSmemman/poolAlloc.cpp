// WIP (NonMatching): like sysdolmem (same GSmemman library), the original keeps values in saved
// registers needlessly and spills/reloads parameters (e.g. GSmemAllocPool saves r31 unused).
// Flags, compiler versions, optimization pragmas and `register` did not reproduce it.
#include <dolphin/types.h>

extern "C" {
void* GSmemAllocClr(u32 size);
void* memset(void* dst, int c, unsigned long n);
}

// Fixed-size cell allocator; free cells are chained through their first word.
class GSmemPoolAllocator {
public:
    void dump();
    bool isRegistration(void* cell);
    u32 getFreeCell() const;
    void freeCell(void* cell);
    void* allocCell();
    void init(unsigned long num, unsigned long size);

    u32 m_used;
    u32 m_peak;
    u32 m_num;
    u32 m_cellSize;
    u8* m_start;
    u8* m_end;
    void** m_free;
};

#define POOL_MAX 32

static GSmemPoolAllocator _poolArea[POOL_MAX];

static void _setDabr(unsigned long addr);
static unsigned long _getDabr();

extern "C" {

u32 GSmemGetFreePool(GSmemPoolAllocator* pool) {
    if (pool != NULL) {
        return pool->getFreeCell();
    }
    return 0;
}

void GSmemDumpPool(GSmemPoolAllocator* pool) {
    int i;
    if (pool != NULL) {
        pool->dump();
        return;
    }
    for (i = 0; i < POOL_MAX; i++) {
        if (_poolArea[i].m_num != 0) {
            _poolArea[i].dump();
        }
    }
}

bool GSmemIsRegistrationPool(GSmemPoolAllocator* pool, void* cell) {
    return pool->isRegistration(cell);
}

void GSmemFreePool(GSmemPoolAllocator* pool, void* cell) {
    if (cell != NULL) {
        pool->freeCell(cell);
    }
}

void* GSmemAllocPool(GSmemPoolAllocator* pool) {
    return pool->allocCell();
}

GSmemPoolAllocator* GSmemCreatePool(unsigned long num, unsigned long size) {
    int i;
    for (i = 0; i < POOL_MAX; i++) {
        if (_poolArea[i].m_num == 0) {
            break;
        }
    }
    if (_poolArea[i].m_num != 0) {
        return NULL;
    }
    _poolArea[i].init(num, size);
    return &_poolArea[i];
}

void GSmemInitPool(void) {
    memset(_poolArea, 0, sizeof(_poolArea));
}

}

void GSmemPoolAllocator::dump() {}

bool GSmemPoolAllocator::isRegistration(void* cell) {
    if (cell == NULL) {
        return false;
    }
    if (cell >= m_start && cell < m_end) {
        return true;
    }
    return false;
}

u32 GSmemPoolAllocator::getFreeCell() const {
    return m_num - m_used;
}

void GSmemPoolAllocator::freeCell(void* cell) {
    if (cell != NULL) {
        void** link = (void**)((u8*)cell - 4);
        unsigned long dabr;
        *link = m_free;
        m_used--;
        dabr = _getDabr();
        _setDabr(0);
        m_free = link;
        _setDabr(dabr);
    }
}

void* GSmemPoolAllocator::allocCell() {
    void** cell = m_free;
    unsigned long dabr = _getDabr();
    _setDabr(0);
    if (cell != NULL) {
        m_free = (void**)*cell;
    } else {
        _setDabr(dabr);
        return NULL;
    }
    _setDabr(dabr);
    memset(cell, 0, m_cellSize);
    m_used++;
    if (m_used > m_peak) {
        m_peak = m_used;
    }
    return cell + 1;
}

void GSmemPoolAllocator::init(unsigned long num, unsigned long size) {
    u8* cell;
    u8* prev;
    u32 i;

    size = (size + 7) & ~3;
    m_num = num;
    m_cellSize = size;
    m_start = (u8*)GSmemAllocClr((num + 1) * size);
    m_end = m_start + num * size;
    m_free = (void**)m_start;
    prev = NULL;
    cell = m_start;
    for (i = 0; i < num; i++) {
        u8* next = cell + size;
        prev = cell;
        *(u8**)cell = next;
        cell = next;
    }
    *(u8**)prev = NULL;
}

// Data address breakpoint (used to catch writes to freed cells in debug builds).
static void _setDabr(unsigned long addr) {}

static unsigned long _getDabr() {
    return 0;
}
