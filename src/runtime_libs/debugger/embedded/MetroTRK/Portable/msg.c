typedef int DSError;

typedef struct TRKBuffer {
    unsigned int unk0;
    unsigned int position;
    unsigned int length;
    unsigned int unkC;
    unsigned char data[0x880];
} TRKBuffer;

int TRKWriteUARTN(const void* bytes, unsigned int length);
void MWTRACE(unsigned char level, char* fmt, ...);

DSError TRKMessageSend(TRKBuffer* msg) {
    DSError write_err = TRKWriteUARTN(msg->data, msg->length);
    MWTRACE(1, "MessageSend : cc_write returned %ld\n", write_err);
    return 0;
}
