#include <dolphin/types.h>
#pragma pool_strings off

class GSmemPoolAllocator {
public:
    void freeCell(void* cell);
    void* allocCell();
};

typedef u8 (*resFreeFunc)(void* mem, u32 grp, u32 id);

struct _resEntry {
    u8 allocated;
    u8 locked;
    u8 registered;
    void* mem;
    u32 grp;
    u32 id;
    resFreeFunc freeFunc;
    _resEntry* next;
    _resEntry* prev;
};

extern "C" {
void GSlogWrite(const char* fmt, ...);
void GSmemDumpPool(GSmemPoolAllocator* pool);
GSmemPoolAllocator* GSmemCreatePool(unsigned long num, unsigned long size);
void* GSmemAlloc(u32 size);
void* GSmemAllocAlign(u32 size, u32 align);
void GSmemFree(void* mem);
}

static _resEntry* _resStructList;
static GSmemPoolAllocator* _resEntryAllocator;

_resEntry* resFindResource(unsigned long grp, unsigned long id);
_resEntry* resFreeResource(_resEntry* entry, bool unlink);

extern "C" {

void GSresIsUniqueID(u32 grp, u32 id, u8 unique) {
    _resEntry* e = resFindResource(grp, id);
    if (e != 0) {
        e->registered = unique;
    }
}

void GSresUnlockResource(u32 grp, u32 id) {
    _resEntry* e = resFindResource(grp, id);
    if (e != 0) {
        e->locked = 0;
    }
}

void GSresLockResource(u32 grp, u32 id) {
    _resEntry* e = resFindResource(grp, id);
    if (e != 0) {
        e->locked = 1;
    }
}

#pragma dont_inline on
void GSresDumpGroup(u32 grp) {
    _resEntry* e = _resStructList;
    GSmemDumpPool(_resEntryAllocator);
    GSlogWrite("alloc registMem   grpID resID      freeFunc\n");
    GSlogWrite("-----------------------------------------------\n");
    for (; e != 0; e = e->next) {
        if (e->grp == grp || grp == (u32)-1) {
            GSlogWrite("  %c   0x%08x  %04d  0x%08x 0x%08x\n", e->allocated ? 'o' : ' ', e->mem,
                       e->grp, e->id, e->freeFunc);
        }
    }
}

#pragma dont_inline reset
void GSresDumpAll() {
    GSresDumpGroup((u32)-1);
}

void GSresFreeGroup(u32 grp) {
    _resEntry* e = _resStructList;
    while (e != 0) {
        _resEntry* n;
        if (e->grp == grp) {
            n = resFreeResource(e, true);
        } else {
            n = e->next;
        }
        e = n;
    }
}

void GSresFreeResource(u32 grp, u32 id) {
    _resEntry* e = resFindResource(grp, id);
    if (e != 0) {
        resFreeResource(e, true);
    }
}

void GSresFreeResourceAllGroup(u32 id) {
    _resEntry* e = _resStructList;
    while (e != 0) {
        if (e->registered != 0 && e->id == id) {
            resFreeResource(e, true);
            return;
        }
        e = e->next;
    }
}

void* GSresGetResourceAllGroup(u32 id) {
    _resEntry* e = _resStructList;
    while (e != 0) {
        if (e->registered != 0 && e->id == id && e->locked == 0) {
            return e->mem;
        }
        e = e->next;
    }
    return 0;
}

void* GSresGetResource(u32 grp, u32 id) {
    _resEntry* e = resFindResource(grp, id);
    if (e == 0 || e->locked != 0) {
        return 0;
    }
    return e->mem;
}

void GSresRegisterResource(void* mem, u32 grp, u32 id, resFreeFunc freeFunc);

void GSresChangeResourceAdress(void* mem, u32 grp, u32 id, resFreeFunc freeFunc) {
    _resEntry* e = resFindResource(grp, id);
    if (e == 0) {
        if (mem != 0) {
            GSresRegisterResource(mem, grp, id, freeFunc);
        }
        return;
    }
    if (mem == 0) {
        resFreeResource(e, true);
        return;
    }
    resFreeResource(e, false);
    e->allocated = 0;
    e->mem = mem;
    e->freeFunc = freeFunc;
}

void GSresRegisterResource(void* mem, u32 grp, u32 id, resFreeFunc freeFunc) {
    _resEntry* e = resFindResource(grp, id);
    if (mem == 0) {
        if (e != 0) {
            resFreeResource(e, true);
        }
        return;
    }
    if (e != 0) {
        if (e->allocated != 0) {
            return;
        }
        if (e->mem != mem) {
            if (e->freeFunc != 0) {
                e->freeFunc(e->mem, grp, id);
            }
            e->mem = mem;
        }
        e->freeFunc = freeFunc;
        return;
    }
    e = (_resEntry*)_resEntryAllocator->allocCell();
    if (e == 0) {
        GSlogWrite("GSres: error -- no free pool\n");
        return;
    }
    if (_resStructList != 0) {
        _resStructList->prev = e;
    }
    e->next = _resStructList;
    e->prev = 0;
    _resStructList = e;
    e->allocated = 0;
    e->locked = 0;
    e->registered = 1;
    e->mem = mem;
    e->grp = grp;
    e->id = id;
    e->freeFunc = freeFunc;
}

void* GSresAllocResourceAlign(u32 size, u32 align, u32 grp, u32 id, resFreeFunc freeFunc) {
    _resEntry* e;
    if (resFindResource(grp, id) != 0) {
        return 0;
    }
    e = (_resEntry*)_resEntryAllocator->allocCell();
    if (e == 0) {
        GSlogWrite("GSres: error -- no free pool\n");
        return 0;
    }
    e->mem = GSmemAllocAlign(size, align);
    if (e->mem == 0) {
        _resEntryAllocator->freeCell(e);
        return 0;
    }
    if (_resStructList != 0) {
        _resStructList->prev = e;
    }
    e->next = _resStructList;
    e->prev = 0;
    _resStructList = e;
    e->allocated = 1;
    e->locked = 0;
    e->registered = 1;
    e->grp = grp;
    e->id = id;
    e->freeFunc = freeFunc;
    return e->mem;
}

void* GSresAllocResource(u32 size, u32 grp, u32 id, resFreeFunc freeFunc) {
    _resEntry* e;
    if (resFindResource(grp, id) != 0) {
        return 0;
    }
    e = (_resEntry*)_resEntryAllocator->allocCell();
    if (e == 0) {
        GSlogWrite("GSres: error -- no free pool\n");
        return 0;
    }
    e->mem = GSmemAlloc(size);
    if (e->mem == 0) {
        _resEntryAllocator->freeCell(e);
        return 0;
    }
    if (_resStructList != 0) {
        _resStructList->prev = e;
    }
    e->next = _resStructList;
    e->prev = 0;
    _resStructList = e;
    e->allocated = 1;
    e->locked = 0;
    e->registered = 1;
    e->grp = grp;
    e->id = id;
    e->freeFunc = freeFunc;
    return e->mem;
}

void GSresInit(u32 count) {
    _resEntryAllocator = GSmemCreatePool(count, sizeof(_resEntry));
}

}

_resEntry* resFreeResource(_resEntry* entry, bool unlink) {
    _resEntry* next;
    if (entry->freeFunc != 0) {
        if (entry->freeFunc(entry->mem, entry->grp, entry->id) == 0) {
            return entry->next;
        }
    }
    if (entry->allocated != 0) {
        if (entry->mem != 0) {
            GSmemFree(entry->mem);
            entry->mem = 0;
        }
        entry->allocated = 0;
    }
    entry->mem = 0;
    next = entry->next;
    if (unlink) {
        if (entry->prev != 0) {
            entry->prev->next = entry->next;
        } else {
            _resStructList = entry->next;
        }
        if (next != 0) {
            next->prev = entry->prev;
        }
        _resEntryAllocator->freeCell(entry);
    }
    return next;
}

_resEntry* resFindResource(unsigned long grp, unsigned long id) {
    _resEntry* e = _resStructList;
    while (e != 0) {
        if (e->grp == grp && e->id == id) {
            return e;
        }
        e = e->next;
    }
    return 0;
}
