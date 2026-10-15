#include <dolphin/types.h>

#pragma peephole off

enum FootStepCounter {
    FOOT_STEP_COUNTER_0
};

// State of the "you've got mail" notification.
struct MailReceiveWork {
    s32 active;
    s32 timer;
    u32 sound;
    s32 unkC;
};

extern "C" {
s32 mailGetReceiveNumber(int id);
void mailAddMailbox(int id);
s32 mailGetNbMailData(void);
void GSsndStop(u32 sound, s32, s32);
u16 mailGetSendRate(int id);
u8 mailGetSendCntCond(int id);
u16 mailGetSendCntCondValue(int id);
u16 mailGetSendCnt(void);
u8 mailGetSendCondType(int id);
u32 mailGetSendCondition(int id);
u32 GSflagGet(u32 flag);
void floorExecScriptInteger(u32 script, s32, s32, s32, s32);
s32 floorGetScriptResult(void);
f32 HSD_Randf(void);
void heroMoveAddStepCallback(void (*callback)(long, FootStepCounter, long), s32);
}

static MailReceiveWork ReceiveWork;

static int chkMailSend(int id, f32 rnd);
static void cbStep(long, FootStepCounter, long);

static inline void receiveStart() {
    if (ReceiveWork.active == 0) {
        ReceiveWork.active = 1;
        ReceiveWork.timer = 0;
        ReceiveWork.sound = 0;
        ReceiveWork.unkC = 0;
    }
}

extern "C" {

void mailMainSendByScrpt(int id) {
    u16 mailId = id;
    if (mailGetReceiveNumber(mailId) < 0) {
        mailAddMailbox(mailId);
        receiveStart();
    }
}

void mailMainSendAllMail(void) {
    s32 num = mailGetNbMailData();
    int i;
    int sent = 0;
    for (i = 1; i < num; i++) {
        if (chkMailSend(i, -1.0f)) {
            mailAddMailbox(i);
            sent = 1;
        }
    }
    if (sent) {
        receiveStart();
    }
}

void mailMainReceiveTerminate(void) {
    ReceiveWork.timer = 600;
    if (ReceiveWork.sound != 0) {
        GSsndStop(ReceiveWork.sound, 0, 0);
    }
}

void mailMainReceiveStart(void) {
    receiveStart();
}

}

// Whether mail `id` should arrive now; rnd < 0 skips the random chance.
static int chkMailSend(int id, f32 rnd) {
    u8 cntCond;
    u16 cntValue;
    u16 rate;
    u16 cnt;
    int ok;
    int result;

    if (mailGetReceiveNumber(id) >= 0) {
        return 0;
    }
    rate = mailGetSendRate(id);
    if (rate == 0xFFFF) {
        return 0;
    }
    if (rnd >= 0.015625f * rate / 1000.0f) {
        return 0;
    }
    cntCond = mailGetSendCntCond(id);
    if (cntCond == 0xFF) {
        return 0;
    }
    cntValue = mailGetSendCntCondValue(id);
    if (cntValue == 0xFFFF) {
        return 0;
    }
    cnt = mailGetSendCnt();
    ok = 0;
    switch (cntCond) {
    case 0:
        if (cnt == cntValue) {
            ok = 1;
        }
        break;
    case 1:
        if (cnt > cntValue) {
            ok = 1;
        }
        break;
    case 2:
        if (cnt < cntValue) {
            ok = 1;
        }
        break;
    case 3:
        if (cnt >= cntValue) {
            ok = 1;
        }
        break;
    case 4:
        if (cnt <= cntValue) {
            ok = 1;
        }
        break;
    case 5:
        if (cnt != cntValue) {
            ok = 1;
        }
        break;
    case 6:
        ok = 1;
        break;
    }
    if (ok == 0) {
        return 0;
    }
    {
        u8 condType = mailGetSendCondType(id);
        u32 condition;
        if (condType == 0xFF) {
            return 0;
        }
        result = 0;
        switch (condType) {
        case 0:
            result = 1;
            break;
        case 1:
            condition = mailGetSendCondition(id);
            if (condition != 0xFFFFFFFF && GSflagGet(condition) != 0) {
                result = 1;
            }
            break;
        case 2:
            condition = mailGetSendCondition(id);
            if (condition != 0xFFFFFFFF && condition != 0) {
                floorExecScriptInteger(condition, 0, 0, 0, 0);
                if (floorGetScriptResult() != 0) {
                    result = 1;
                }
            }
            break;
        }
    }
    return result;
}

static void cbStep(long, FootStepCounter, long) {
    f32 rnd = HSD_Randf();
    s32 num = mailGetNbMailData();
    int i;
    int sent = 0;
    for (i = 0; i < num; i++) {
        if (chkMailSend(i, rnd)) {
            mailAddMailbox(i);
            sent = 1;
        }
    }
    if (sent) {
        receiveStart();
    }
}

extern "C" {

void mailMainInit(void) {
    heroMoveAddStepCallback(cbStep, 0);
    ReceiveWork.active = 0;
    ReceiveWork.sound = 0;
    ReceiveWork.unkC = 0;
}

}
