#ifndef GAME_PCSPARE_H
#define GAME_PCSPARE_H
#define PC_SPARE_SPECIES 256
#define PC_SPARE_MOVES 256
#define PC_SPARE_ITEMS 256
#define PC_SPARE_ABILITIES 178

#ifdef __MWERKS__
#define PC_SPARE_ROWS(orig, spare)
#define PC_SPARE_COUNT(table, orig) (sizeof(table) / sizeof((table)[0]))
#define PC_SPARE_CHECK(table, orig) \
    typedef char table##_orig_rows_check[(sizeof(table) / sizeof((table)[0]) == (orig)) ? 1 : -1]
#else
#define PC_SPARE_ROWS(orig, spare) ((orig) + (spare))
#define PC_SPARE_COUNT(table, orig) (orig)
#define PC_SPARE_CHECK(table, orig) \
    typedef char table##_orig_rows_check[(sizeof(table) / sizeof((table)[0]) >= (orig)) ? 1 : -1]
#endif

#endif
