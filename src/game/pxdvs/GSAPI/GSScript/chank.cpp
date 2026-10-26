#include <dolphin/types.h>

extern "C" int memcmp(const void* a, const void* b, unsigned long n);

struct ChankHeader {
    char id[4];
    s32 size;
    s32 no;
    u8 unkC[4];
};

class CChank {
public:
    char* m_data;
    char* m_end;
    s32 m_count;

    CChank();
    virtual ~CChank() {}
    char* searchSubChankID(const char* id);
    char* searchChankID(const char* id, long no);
};

class CChankBlock : public CChank {
public:
    virtual ~CChankBlock() {}
    BOOL loadFromMemory(char* data, char* id);
};

BOOL CChankBlock::loadFromMemory(char* data, char* id) {
    ChankHeader* header;
    s32 size;
    char* p;
    char* end;

    m_data = data;
    header = (ChankHeader*)m_data;
    if (header == NULL) {
        return TRUE;
    }
    if (id != NULL && memcmp(header, id, 4) != 0) {
        return FALSE;
    }
    m_count = 0;
    p = m_data + sizeof(ChankHeader);
    m_end = end = m_data + header->size;
    while (end > p) {
        size = ((ChankHeader*)p)->size;
        m_count++;
        p += size;
    }
    return TRUE;
}

char* CChank::searchSubChankID(const char* id) {
    char* p;
    s32 i;

    if (m_data == NULL) {
        return NULL;
    }
    p = m_data + sizeof(ChankHeader);
    for (i = 0; i < m_count; i++) {
        if (memcmp(p, id, 4) == 0) {
            return p;
        }
        p += ((ChankHeader*)p)->size;
    }
    return NULL;
}

char* CChank::searchChankID(const char* id, long no) {
    char* p;
    s32 i;

    if (m_data == NULL) {
        return NULL;
    }
    p = m_data + sizeof(ChankHeader);
    for (i = 0; i < m_count; i++) {
        if (((ChankHeader*)p)->no == no && memcmp(p, id, 4) == 0) {
            return p;
        }
        p += ((ChankHeader*)p)->size;
    }
    return NULL;
}

CChank::CChank() {
    m_data = NULL;
}
