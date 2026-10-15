typedef int DSError;

DSError TRKInitializeNub(void);
void TRKNubWelcome(void);
void TRKNubMainLoop(void);
DSError TRKTerminateNub(void);
void MWTRACE(unsigned char level, char* fmt, ...);

static DSError TRK_mainError;

void TRK_main(void) {
    MWTRACE(1, "TRK_Main \n");
    TRK_mainError = TRKInitializeNub();
    if (TRK_mainError == 0) {
        TRKNubWelcome();
        TRKNubMainLoop();
    }
    TRK_mainError = TRKTerminateNub();
}
