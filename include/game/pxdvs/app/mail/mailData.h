#ifndef GAME_MAILDATA_H
#define GAME_MAILDATA_H

#include <dolphin/types.h>

struct MailData {
    u32 senderName;
    u32 subject;
    u32 contents;
    u32 attachFileGroup;
    u32 openFlag;
};

#endif
