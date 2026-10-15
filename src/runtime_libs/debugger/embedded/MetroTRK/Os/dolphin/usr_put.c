typedef int BOOL;

BOOL GetTRKConnected(void);
void SetTRKConnected(BOOL connected);
void OSReport(const char* msg);

BOOL usr_puts_serial(const char* msg) {
    BOOL connect_ = 0;
    char c;
    char buf[2];

    while (!connect_ && (c = *msg++) != '\0') {
        BOOL connect = GetTRKConnected();

        buf[0] = c;
        buf[1] = '\0';

        SetTRKConnected(0);
        OSReport(buf);
        SetTRKConnected(connect);

        connect_ = 0;
    }
    return connect_;
}

void usr_put_initialize(void) {}
