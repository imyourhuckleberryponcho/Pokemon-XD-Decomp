typedef int DSError;
typedef struct TRKBuffer TRKBuffer;

DSError TRKGetFreeBuffer(int* bufIdx, TRKBuffer** msg);
void TRKReleaseBuffer(int idx);
DSError TRKTargetAddStopInfo(TRKBuffer* msg);
DSError TRKTargetAddExceptionInfo(TRKBuffer* msg);
DSError TRKRequestSend(TRKBuffer* msg, int* bufIdx, unsigned int p1, unsigned int p2, int p3);

#define kDSNotifyStopped 0x90

DSError TRKDoNotifyStopped(int cmd) {
    DSError err;
    int reqIdx;
    int bufIdx;
    TRKBuffer* msg;

    err = TRKGetFreeBuffer(&bufIdx, &msg);
    if (err == 0) {
        if (err == 0) {
            if (cmd == kDSNotifyStopped) {
                TRKTargetAddStopInfo(msg);
            } else {
                TRKTargetAddExceptionInfo(msg);
            }
        }
        err = TRKRequestSend(msg, &reqIdx, 2, 3, 1);
        if (err == 0) {
            TRKReleaseBuffer(reqIdx);
        }
        TRKReleaseBuffer(bufIdx);
    }
    return err;
}
