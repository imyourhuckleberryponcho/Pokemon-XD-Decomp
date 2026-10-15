#include <dolphin/types.h>

// One cache block of _fsysBlockByteSize bytes, chained into per-file lists.
struct FsysBlock {
    FsysBlock* prev;
    FsysBlock* next;
    u8* data;
    u32 unkC;
};

extern "C" {

BOOL OSDisableInterrupts(void);
BOOL OSRestoreInterrupts(BOOL level);
u32 ARQGetChunkSize(void);
void* _fsysDoMalloc(u32 size);

static u8* _fsysBlock;
static FsysBlock* _fsysBlockManage;
static u32 _fsysBlockIndex;
static u32 _fsysBlockSize;
static u32 _fsysBlockBufferSize;
u32 _fsysBlockByteSize;

BOOL _fsysFreeBlock(FsysBlock** list, u8 all);

// Moves the last block of `from` to the end of `to`.
void _fsysMoveBlock(FsysBlock** from, FsysBlock** to) {
    FsysBlock* block;
    FsysBlock* last;
    BOOL intr = OSDisableInterrupts();

    block = *from;
    if (block != NULL) {
        while (block->next != NULL) {
            block = block->next;
        }
        if (block->prev != NULL) {
            block->prev->next = NULL;
        }
        if (*from == block) {
            *from = NULL;
        }
        block->prev = NULL;
        block->next = NULL;
        last = *to;
        if (last != NULL) {
            while (last->next != NULL) {
                last = last->next;
            }
            last->next = block;
            block->prev = last;
        } else {
            *to = block;
        }
    }
    OSRestoreInterrupts(intr);
}

// Puts `block` (and the blocks chained after it) in front of the list.
void _fsysAddBlock(FsysBlock** list, FsysBlock* block) {
    FsysBlock* head;
    FsysBlock* last;
    BOOL intr = OSDisableInterrupts();

    head = *list;
    if (head != NULL) {
        if (block->next != NULL) {
            for (last = block->next; last->next != NULL; last = last->next) {
            }
            last->next = head;
            head->prev = last;
        } else {
            block->next = head;
            head->prev = block;
        }
    }
    *list = block;
    OSRestoreInterrupts(intr);
}

void _fsysFreeBlockAll(FsysBlock** list) {
    for (;;) {
        if (*list == NULL) {
            break;
        }
        _fsysFreeBlock(list, 1);
    }
}

// Frees the first block of the list, or the last one if `first` is 0.
BOOL _fsysFreeBlock(FsysBlock** list, u8 first) {
    FsysBlock* block;
    BOOL intr = OSDisableInterrupts();

    block = *list;
    if (block != NULL) {
        if (!first) {
            while (block->next != NULL) {
                block = block->next;
            }
            if (block->prev != NULL) {
                block->prev->next = NULL;
            }
            if (*list == block) {
                *list = NULL;
            }
            block->data = NULL;
        } else {
            if (block->prev != NULL) {
                block->prev->next = block->next;
            }
            if (block->next != NULL) {
                block->next->prev = block->prev;
            }
            block->data = NULL;
            *list = block->next;
        }
    }
    OSRestoreInterrupts(intr);
    return TRUE;
}

FsysBlock* _fsysAllocBlock(void) {
    FsysBlock* found = NULL;
    BOOL intr = OSDisableInterrupts();
    FsysBlock* block;
    u32 i = _fsysBlockIndex;

    while (found == NULL) {
        block = &_fsysBlockManage[i];
        if (block->data == NULL) {
            found = block;
            block->data = _fsysBlock + i * _fsysBlockByteSize;
            block->prev = NULL;
            block->next = NULL;
            block->unkC = 0;
        }
        i++;
        if (i >= _fsysBlockSize) {
            i = 0;
        }
        if (_fsysBlockIndex == i) {
            break;
        }
    }
    _fsysBlockIndex = i;
    OSRestoreInterrupts(intr);
    return found;
}

BOOL _fsysInitBlock(u32 bufferSize) {
    u32 i;

    _fsysBlockIndex = 0;
    _fsysBlockByteSize = ARQGetChunkSize();
    _fsysBlockBufferSize = bufferSize;
    if (bufferSize == 0) {
        _fsysBlockBufferSize = 0x80000;
    }
    _fsysBlockSize = _fsysBlockBufferSize / _fsysBlockByteSize;
    if (_fsysBlockSize == 0) {
        return FALSE;
    }
    _fsysBlock = (u8*)_fsysDoMalloc(_fsysBlockByteSize * _fsysBlockSize);
    if (_fsysBlock == NULL) {
        return FALSE;
    }
    _fsysBlockManage = (FsysBlock*)_fsysDoMalloc(_fsysBlockSize * sizeof(FsysBlock));
    if (_fsysBlockManage == NULL) {
        return FALSE;
    }
    for (i = 0; i < _fsysBlockSize; i++) {
        _fsysBlockManage[i].prev = NULL;
        _fsysBlockManage[i].next = NULL;
        _fsysBlockManage[i].data = NULL;
        _fsysBlockManage[i].unkC = 0;
    }
    return TRUE;
}

}
