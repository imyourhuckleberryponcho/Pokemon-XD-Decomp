#include <dolphin/types.h>

typedef struct ComboData {
    u8 type;
    u8 order;
    u8 pad[2];
    s32 (*func)(void);
    s32 (*continueFunc)(void);
} ComboData;

extern s32 fightAiCombo_null(void);
extern s32 fightAiCombo_null_Continue(void);
extern s32 fightAiCombo_Nihonbare_Sooraabiimu_2(void);
extern s32 fightAiCombo_Nihonbare_Honoo_2(void);
extern s32 fightAiCombo_Amagoi_Kaminari_2(void);
extern s32 fightAiCombo_Amagoi_Mizu_2(void);
extern s32 fightAiCombo_Nihonbare_Whezaabooru_2(void);
extern s32 fightAiCombo_Amagoi_Whezaabooru_2(void);
extern s32 fightAiCombo_Sunaarasi_Whezaabooru_2(void);
extern s32 fightAiCombo_Arare_Whezaabooru_2(void);
extern s32 fightAiCombo_Kinokonohousi_Kiaipanti_2(void);
extern s32 fightAiCombo_Nemurase_Yumekui_2(void);
extern s32 fightAiCombo_Daibakuhatu_Koraeru_2(void);
extern s32 fightAiCombo_Tedasuke_Iryoku_2(void);
extern s32 fightAiCombo_Zisin_Mamoru_2(void);
extern s32 fightAiCombo_Haradaiko_Zikoanzi_2(void);
extern s32 fightAiCombo_Daibakuhatu_Daibakuhatu_2(void);
extern s32 fightAiCombo_Hurahuradansu_Irekae_2(void);
extern s32 fightAiCombo_Zisin_Irekae_2(void);
extern s32 fightAiCombo_Daibakuhatu_Irekae_2(void);
extern s32 fightAiCombo_StatusUp_Batontatti_1(void);
extern s32 fightAiCombo_Batontatti_Nekodamasi_2(void);
extern s32 fightAiCombo_Batontatti_Nekodamasi_Continue(void);
extern s32 fightAiCombo_Batontatti_Zikoanzi_2(void);
extern s32 fightAiCombo_Batontatti_Zikoanzi_Continue(void);
extern s32 fightAiCombo_Makibisi_Hoeru_2(void);
extern s32 fightAiCombo_Konran_DefDown_2(void);
extern s32 fightAiCombo_Amaikaori_Hubuki_2(void);
extern s32 fightAiCombo_Amaikaori_Hubuki_Continue(void);
extern s32 fightAiCombo_Nihonbare_Asanohizasi_2(void);
extern s32 fightAiCombo_Nihonbare_Irekae_2(void);
extern s32 fightAiCombo_Amagoi_Irekae_2(void);
extern s32 fightAiCombo_Sunaarasi_Irekae_2(void);
extern s32 fightAiCombo_Sukirusuwappu_Irekae_2(void);
extern s32 fightAiCombo_Sukirusuwappu_Irekae_Continue(void);
extern s32 fightAiCombo_Konoyubitomare_StatusUp_2(void);
extern s32 fightAiCombo_Konoyubitomare_Kiaipanti_2(void);
extern s32 fightAiCombo_Horobinouta_Irekae_2(void);
extern s32 fightAiCombo_Dokudoku_Karagenki_2(void);
extern s32 fightAiCombo_Honoo_Irekae_2(void);
extern s32 fightAiCombo_Horobinouta_Irekae2_2(void);
extern s32 fightAiCombo_Ibaru_Irekae_2(void);
extern s32 fightAiCombo_Hakaikousen_Hoeru_2(void);
extern s32 fightAiCombo_Daibakuhatu_Horobinouta_2(void);
extern s32 fightAiCombo_Migawari_Kisikaisei_1(void);
extern s32 fightAiCombo_Torikku_Kodawarihatimaki_1(void);
extern s32 fightAiCombo_Konran_DefDown_1(void);
extern s32 fightAiCombo_Amaikaori_Hubuki_1(void);
extern s32 fightAiCombo_Sukirusuwappu_Irekae_1(void);
extern s32 fightAiCombo_Darkweather_DarkIryoku_2(void);
extern s32 fightAiCombo_Darkmist_Darkpanic_2(void);
extern s32 fightAiCombo_Darkmist_Darkhold_2(void);
extern s32 fightAiCombo_Darkmist_Darkend_2(void);
extern s32 fightAiCombo_Darkdown_PhyatkIryoku_2(void);
extern s32 fightAiCombo_DarkWeather_Whezaabooru_2(void);

ComboData comboid[] = {
    {0, 0, {0}, fightAiCombo_null, fightAiCombo_null_Continue},
    {2, 0, {0}, fightAiCombo_Nihonbare_Sooraabiimu_2, fightAiCombo_null_Continue},
    {2, 0, {0}, fightAiCombo_Nihonbare_Honoo_2, fightAiCombo_null_Continue},
    {2, 0, {0}, fightAiCombo_Amagoi_Kaminari_2, fightAiCombo_null_Continue},
    {2, 0, {0}, fightAiCombo_Amagoi_Mizu_2, fightAiCombo_null_Continue},
    {2, 0, {0}, fightAiCombo_Nihonbare_Whezaabooru_2, fightAiCombo_null_Continue},
    {2, 0, {0}, fightAiCombo_Amagoi_Whezaabooru_2, fightAiCombo_null_Continue},
    {2, 0, {0}, fightAiCombo_Sunaarasi_Whezaabooru_2, fightAiCombo_null_Continue},
    {2, 0, {0}, fightAiCombo_Arare_Whezaabooru_2, fightAiCombo_null_Continue},
    {2, 0, {0}, fightAiCombo_Kinokonohousi_Kiaipanti_2, fightAiCombo_null_Continue},
    {2, 0, {0}, fightAiCombo_Nemurase_Yumekui_2, fightAiCombo_null_Continue},
    {2, 0, {0}, fightAiCombo_Daibakuhatu_Koraeru_2, fightAiCombo_null_Continue},
    {2, 0, {0}, fightAiCombo_Tedasuke_Iryoku_2, fightAiCombo_null_Continue},
    {2, 0, {0}, fightAiCombo_Zisin_Mamoru_2, fightAiCombo_null_Continue},
    {2, 0, {0}, fightAiCombo_Haradaiko_Zikoanzi_2, fightAiCombo_null_Continue},
    {2, 0, {0}, fightAiCombo_Daibakuhatu_Daibakuhatu_2, fightAiCombo_null_Continue},
    {2, 1, {0}, fightAiCombo_Hurahuradansu_Irekae_2, fightAiCombo_null_Continue},
    {2, 1, {0}, fightAiCombo_Zisin_Irekae_2, fightAiCombo_null_Continue},
    {2, 1, {0}, fightAiCombo_Daibakuhatu_Irekae_2, fightAiCombo_null_Continue},
    {1, 0, {0}, fightAiCombo_StatusUp_Batontatti_1, fightAiCombo_null_Continue},
    {2, 0, {0}, fightAiCombo_Batontatti_Nekodamasi_2, fightAiCombo_Batontatti_Nekodamasi_Continue},
    {2, 0, {0}, fightAiCombo_Batontatti_Zikoanzi_2, fightAiCombo_Batontatti_Zikoanzi_Continue},
    {2, 0, {0}, fightAiCombo_Makibisi_Hoeru_2, fightAiCombo_null_Continue},
    {2, 0, {0}, fightAiCombo_Konran_DefDown_2, fightAiCombo_null_Continue},
    {2, 0, {0}, fightAiCombo_Amaikaori_Hubuki_2, fightAiCombo_Amaikaori_Hubuki_Continue},
    {2, 0, {0}, fightAiCombo_Nihonbare_Asanohizasi_2, fightAiCombo_null_Continue},
    {2, 1, {0}, fightAiCombo_Nihonbare_Irekae_2, fightAiCombo_null_Continue},
    {2, 1, {0}, fightAiCombo_Amagoi_Irekae_2, fightAiCombo_null_Continue},
    {2, 1, {0}, fightAiCombo_Sunaarasi_Irekae_2, fightAiCombo_null_Continue},
    {2, 0, {0}, fightAiCombo_Sukirusuwappu_Irekae_2, fightAiCombo_Sukirusuwappu_Irekae_Continue},
    {2, 0, {0}, fightAiCombo_Konoyubitomare_StatusUp_2, fightAiCombo_null_Continue},
    {2, 0, {0}, fightAiCombo_Konoyubitomare_Kiaipanti_2, fightAiCombo_null_Continue},
    {2, 1, {0}, fightAiCombo_Horobinouta_Irekae_2, fightAiCombo_null_Continue},
    {2, 0, {0}, fightAiCombo_Dokudoku_Karagenki_2, fightAiCombo_null_Continue},
    {2, 1, {0}, fightAiCombo_Honoo_Irekae_2, fightAiCombo_null_Continue},
    {2, 1, {0}, fightAiCombo_Horobinouta_Irekae2_2, fightAiCombo_null_Continue},
    {2, 1, {0}, fightAiCombo_Ibaru_Irekae_2, fightAiCombo_null_Continue},
    {2, 0, {0}, fightAiCombo_Hakaikousen_Hoeru_2, fightAiCombo_null_Continue},
    {2, 0, {0}, fightAiCombo_Daibakuhatu_Horobinouta_2, fightAiCombo_null_Continue},
    {1, 0, {0}, fightAiCombo_Migawari_Kisikaisei_1, fightAiCombo_null_Continue},
    {1, 0, {0}, fightAiCombo_Torikku_Kodawarihatimaki_1, fightAiCombo_null_Continue},
    {1, 0, {0}, fightAiCombo_Konran_DefDown_1, fightAiCombo_null_Continue},
    {1, 0, {0}, fightAiCombo_Amaikaori_Hubuki_1, fightAiCombo_null_Continue},
    {1, 0, {0}, fightAiCombo_Sukirusuwappu_Irekae_1, fightAiCombo_Sukirusuwappu_Irekae_Continue},
    {2, 0, {0}, fightAiCombo_Darkweather_DarkIryoku_2, fightAiCombo_null_Continue},
    {2, 0, {0}, fightAiCombo_Darkmist_Darkpanic_2, fightAiCombo_null_Continue},
    {2, 0, {0}, fightAiCombo_Darkmist_Darkhold_2, fightAiCombo_null_Continue},
    {2, 0, {0}, fightAiCombo_Darkmist_Darkend_2, fightAiCombo_null_Continue},
    {2, 0, {0}, fightAiCombo_Darkdown_PhyatkIryoku_2, fightAiCombo_null_Continue},
    {2, 0, {0}, fightAiCombo_DarkWeather_Whezaabooru_2, fightAiCombo_null_Continue},
};
