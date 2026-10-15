#include <dolphin/types.h>

#pragma peephole off

struct MailData {
    u32 senderName;
    u32 subject;
    u32 contents;
    u32 attachFileGroup;
    u32 openFlag;
};

// The player's mailbox in the save data.
struct Mailbox {
    u16 ids[32];
    u16 count;
    u8 unread[4];
    u8 sortMode;
    u8 unk47;
    u16 sendCnt;
};

extern "C" {
extern MailData* mailData;
extern u32* mailData_number;
Mailbox* savedataGetStatus(s32, s32);
void* memset(void* dst, int c, unsigned long n);
void mailMainInit(void);
}

#define MAILBOX() savedataGetStatus(0, 10)

static inline MailData* mailGetPtr(int id) {
    if (id <= 0 || id > *mailData_number) {
        return NULL;
    }
    return &mailData[id];
}

static inline s32 mailGetIDInMailbox(int index) {
    Mailbox* box = MAILBOX();
    if (index < 0 || index >= MAILBOX()->count) {
        return -1;
    }
    return box->ids[index];
}

// Byte index into Mailbox::unread for a mail id, or -1.
static inline int mailGetUnreadBit(int id, u8& mask) {
    if (id < 0 || id >= 32) {
        return -1;
    }
    mask = 1 << (7 - id % 8);
    return id / 8;
}

extern "C" {

u16 mailGetSendCntCondValue(int id) {
    return 0;
}

u8 mailGetSendCntCond(int id) {
    return 0;
}

u32 mailGetOpenFlag(int id) {
    MailData* mail = mailGetPtr(id);
    if (mail == NULL) {
        return 0;
    }
    return mail->openFlag;
}

u32 mailGetSendCondition(int id) {
    return 0;
}

u8 mailGetSendCondType(int id) {
    return 0;
}

u16 mailGetSendRate(int id) {
    return 0;
}

u32 mailGetAttachFileGroup(int id) {
    MailData* mail = mailGetPtr(id);
    if (mail == NULL) {
        return 0;
    }
    return mail->attachFileGroup;
}

u8 mailGetSortMode(void) {
    return MAILBOX()->sortMode;
}

u16 mailGetSendCnt(void) {
    return MAILBOX()->sendCnt;
}

u32 mailGetNbMailData(void) {
    return *mailData_number;
}

u32 mailGetContents(int id) {
    MailData* mail = mailGetPtr(id);
    if (mail == NULL) {
        return 0;
    }
    return mail->contents;
}

u32 mailGetSenderName(int id) {
    MailData* mail = mailGetPtr(id);
    if (mail == NULL) {
        return 0;
    }
    return mail->senderName;
}

u32 mailGetSubject(int id) {
    MailData* mail = mailGetPtr(id);
    if (mail == NULL) {
        return 0;
    }
    return mail->subject;
}

bool mailChkReceiveMail(int id) {
    Mailbox* box = MAILBOX();
    int i;
    if (id <= 0 || id > *mailData_number) {
        return false;
    }
    for (i = 0; i < box->count; i++) {
        if (id == box->ids[i]) {
            break;
        }
    }
    if (i >= box->count) {
        return false;
    }
    return true;
}

bool mailAddMailbox(int id) {
    Mailbox* box = MAILBOX();
    int byte;
    u8 mask;
    if (id <= 0 || id > *mailData_number) {
        return false;
    }
    if (box->count >= 32) {
        return false;
    }
    box->ids[box->count] = id;
    box->count++;
    box = MAILBOX();
    byte = mailGetUnreadBit(id, mask);
    if (byte >= 0) {
        box->unread[byte] &= ~mask;
    }
    return true;
}

s32 mailGetReceiveNumber(int id) {
    int i;
    int found = 0;
    for (i = 0; i < MAILBOX()->count && !found; i++) {
        if (id == mailGetIDInMailbox(i)) {
            found = 1;
        }
    }
    if (!found) {
        return -1;
    }
    return i;
}

s32 mailGetMailIDInMailbox(int index) {
    return mailGetIDInMailbox(index);
}

u16 mailGetNbMailInMailbox(void) {
    return MAILBOX()->count;
}

void mailInitMailbox(Mailbox* box) {
    int i;
    memset(box, 0, sizeof(Mailbox));
    box->sortMode = 0;
    for (i = 0; i < 32; i++) {
        box->ids[i] = 0xFF;
    }
    mailMainInit();
}

}
