// STATUS: 263/272 exact. Permuter fix applied to pokemonBiosSetNicknamePtr. 9 remaining high-scorers (78-97%) have register/peephole diffs.
#include <game/pxdvs/app/pokemon/pokemon.hpp>
#include <game/pxdvs/app/pokemon/pokemonBios.hpp>
#include <game/pxdvs/app/pokemon/pokemonDB.hpp>
#include <game/relglobal.h>
#include <game/pxdvs//GSAPI/GSflag/GSflag.h>

extern "C" {

extern u32 pokemon_nakigoe_data_number;
extern u32 pokemon_nakigoe_data[];
extern u32* pokemon_dp_filter_data_number;
extern u8* pokemon_dp_filter_data;
extern u32 pokemon_friend_filter_data_number;
extern u8 pokemon_friend_filter_data[];
extern u32 pokemon_grow_data_number;
extern u8 pokemon_grow_data[];
extern u32 pokemon_tokusei_data_number;
extern u8 pokemon_tokusei_data[];
extern u32* pokemon_seikaku_rate_data_number;
extern u8* pokemon_seikaku_rate_data;
extern u32* pokemon_seikaku_data_number;
extern u8* pokemon_seikaku_data;

void GScharLenCpy(void* dst, const void* src, s32 len);
u8 pokemonGetDarkPokemonLevel(Pokemon* poke);
u8 pokemonWazaCheckValid(Pokemon* poke, u32 wazaNum);
u16 darkPokemonBiosGetTemotiDarkWaza(u16 id, s32 index);
u8 darkPokemonBiosGetReliveFlag(u16 id);
u8* wazaDataBiosGetPtr(u16 id);
u8 wazaDataBiosGetPp(u8* data);
static u32 _pokemon_waza_darkwaza[18] = {
    0x01640500, 0x01650500, 0x01660500, 0x01670500, 0x01680500, 0x01690500,
    0x016A0500, 0x016B0500, 0x016C0500, 0x016D0500, 0x016E0500, 0x016F0500,
    0x01700500, 0x01710500, 0x01720500, 0x01730500, 0x01740500, 0x01750500,
};
static u32 _pokemon_waza_hatena = 0x01760500;

















































































































































































































































































u32 pokemonNakigoeDataBiosGetDataAddress(u8* data) {
    if (data) goto non_null;
    return 0;
non_null:
    u16 index = *reinterpret_cast<u16*>(data + 0xE);
    if (index < pokemon_nakigoe_data_number) goto in_range;
    return 0;
in_range:
    return pokemon_nakigoe_data[index];
}

s32 pokemonDpFilterDataBiosGetValue(s8* data) {
    if (data) goto non_null;
    return 0;
non_null:
    u8 value = *(u8*)data;
    return (s8)value;
}

u32 pokemonDpFilterDataBiosGetPtr(u16 index) {
    if (index < *pokemon_dp_filter_data_number) goto in_range;
    return 0;
in_range:
    return (u32)(pokemon_dp_filter_data + index);
}

s32 pokemonFriendFilterDataBiosGetValue(s8* data, u8 index) {
    if (data) goto non_null;
    return 0;
non_null:
    if (index < 3) goto in_range;
    return 0;
in_range:
    return (s8)((u8*)data)[index];
}

u32 pokemonFriendFilterDataBiosGetPtr(u16 index) {
    if (index < pokemon_friend_filter_data_number) goto in_range;
    return 0;
in_range:
    return (u32)(pokemon_friend_filter_data + index * 3);
}

u32 pokemonTokuseiDataBiosGetDoc(u32* data) {
    if (data) goto non_null;
    return 0;
non_null:
    return data[2];
}

u32 pokemonTokuseiDataBiosGetName(u32* data) {
    if (data) goto non_null;
    return 0;
non_null:
    return data[1];
}

u32 pokemonTokuseiDataBiosGetPtr(u16 index) {
    if (index < pokemon_tokusei_data_number) goto in_range;
    return 0;
in_range:
    return (u32)((u8*)pokemon_tokusei_data + index * 0xC);
}

u32 pokemonSeikakuRateDataBiosGetWaru(PokemonSeikakuRateBios* data) {
    if (data) goto non_null;
    return 0;
non_null:
    return *((u8*)data + 1);
}

u32 pokemonSeikakuRateDataBiosGetKake(PokemonSeikakuRateBios* data) {
    if (data) goto non_null;
    return 0;
non_null:
    return *((u8*)data);
}

PokemonSeikakuRateBios* pokemonSeikakuRateDataBiosGetPtr(u32 index) {
    u32* countPtr = pokemon_seikaku_rate_data_number;
    if ((u8)(index & 0xFF) < *countPtr) goto in_range;
    return 0;
in_range:
    return (PokemonSeikakuRateBios*)(pokemon_seikaku_rate_data + ((u8)index * 2));
}

s32 pokemonSeikakuDataBiosGetReliveNadenade(u8* data) {
    if (data) goto non_null;
    return 0;
non_null:
    return (s8)data[4];
}

s32 pokemonSeikakuDataBiosGetReliveSodateya(u8* data) {
    if (data) goto non_null;
    return 0;
non_null:
    return (s8)data[3];
}

s32 pokemonSeikakuDataBiosGetReliveCall(u8* data) {
    if (data) goto non_null;
    return 0;
non_null:
    return (s8)data[2];
}

s32 pokemonSeikakuDataBiosGetReliveWalk(u8* data) {
    if (data) goto non_null;
    return 0;
non_null:
    return (s8)data[1];
}

s32 pokemonSeikakuDataBiosGetReliveFightout(u8* data) {
    if (data) goto non_null;
    return 0;
non_null:
    return (s8)data[0];
}

u32 pokemonSeikakuDataBiosGetNimblenessRateDataId(PokemonSeikakuDataBios* data) {
    if (data) goto non_null;
    return 0;
non_null:
    return *((u8*)data + 9);
}

u32 pokemonSeikakuDataBiosGetSpeDefRateDataId(PokemonSeikakuDataBios* data) {
    if (data) goto non_null;
    return 0;
non_null:
    return *((u8*)data + 8);
}

u32 pokemonSeikakuDataBiosGetSpeAtkRateDataId(PokemonSeikakuDataBios* data) {
    if (data) goto non_null;
    return 0;
non_null:
    return *((u8*)data + 7);
}

u32 pokemonSeikakuDataBiosGetPhyDefRateDataId(PokemonSeikakuDataBios* data) {
    if (data) goto non_null;
    return 0;
non_null:
    return *((u8*)data + 6);
}

u32 pokemonSeikakuDataBiosGetPhyAtkRateDataId(PokemonSeikakuDataBios* data) {
    if (data) goto non_null;
    return 0;
non_null:
    return *((u8*)data + 5);
}

u32 pokemonSeikakuDataBiosGetName(u32* data) {
    if (data) goto non_null;
    return 0;
non_null:
    return data[5];
}

PokemonSeikakuDataBios* pokemonSeikakuDataBiosGetPtr(u32 index) {
    index = (u8)index;
    u32* countPtr = pokemon_seikaku_data_number;
    if (index < *countPtr) goto in_range;
    return 0;
in_range:
    return (PokemonSeikakuDataBios*)(pokemon_seikaku_data + index * 0x28);
}

int pokemonGrowDataBiosGetExp(PokemonGrowDataBios* data, u8 level) {
    if (data) goto non_null;
    return 0;
non_null:
    if (level < 0x65) goto in_range;
    return 0;
in_range:
    return ((u32*)data)[level];
}

PokemonGrowDataBios* pokemonGrowDataBiosGetPtr(u8 index) {
    if (index < pokemon_grow_data_number) goto in_range;
    return 0;
in_range:
    return (PokemonGrowDataBios*)(pokemon_grow_data + index * 0x194);
}

void pokemonDataBiosSetKowaza(PokemonData* pdata, u16 idx, u16 data) {
    if (pdata && idx < 8) {
        pdata->kowaza[idx] = data;
    }
}

void pokemonDataBiosSetPkxDataId(PokemonData* pdata, u32 data) {
    if (pdata) {
        pdata->pkxDataId = data;
    }
}

void pokemonDataBiosSetNumPokemon(PokemonData* pdata, u16 data) {
    if (pdata) {
        pdata->numPokemon = data;
    }
}

void pokemonDataBiosSetNumZukan(PokemonData* pdata, u16 data) {
    if (pdata) {
        pdata->numZukan = data;
    }
}

void pokemonDataBiosSetTukamaetaFlag(PokemonData* pdata, bool data) {
    if (pdata) {
        GSflagSet(pdata->tukamaetaFlag, data);
    }
}

void pokemonDataBiosSetMitaFlag(PokemonData* pdata, bool data) {
    if (pdata) {
        GSflagSet(pdata->mitaFlag, data);
    }
}

void pokemonDataBiosSetVoice(PokemonData* pdata, u16 data) {
    if (pdata) {
        pdata->voice = data;
    }
}

void pokemonDataBiosSetDoc(PokemonData* pdata, u32 data) {
    if (pdata) {
        pdata->doc = data;
    }
}

void pokemonDataBiosSetWeight(PokemonData* pdata, u16 data) {
    if (pdata) {
        pdata->weight = data;
    }
}

void pokemonDataBiosSetHeight(PokemonData* pdata, u16 data) {
    if (pdata) {
        pdata->height = data;
    }
}

void pokemonDataBiosSetTypeName(PokemonData* pdata, u32 data) {
    if (pdata) {
        pdata->typeName = data;
    }
}

void pokemonDataBiosSetColor(PokemonData* pdata, u16 cgIdx, u8 data) {
    PokemonDataCgData* cgData = pokemonDataBiosGetCgDataPtr(pdata, cgIdx);
    if (cgData) {
        cgData->color = data;
    }
}

void pokemonDataBiosSetStatusFaceMenuSpriteId(PokemonData* pdata, u16 cgIdx, u16 data) {
    PokemonDataCgData* cgData = pokemonDataBiosGetCgDataPtr(pdata, cgIdx);
    if (cgData) {
        cgData->spriteId = data;
    }
}

void pokemonDataBiosSetPokebodyId(PokemonData* pdata, u16 cgIdx, u32 data) {
    PokemonDataCgData* cgData = pokemonDataBiosGetCgDataPtr(pdata, cgIdx);
    if (cgData) {
        cgData->pokebodyId = data;
    }
}

void pokemonDataBiosSetWazaMcn(PokemonData* pdata, u16 wazaIdx, bool data) {
    if (pdata && wazaIdx < 0x3a) {
        pdata->wazaMcn[wazaIdx] = data;
    }
}

void pokemonDataBiosSetGetWazaDataId(PokemonData* pdata, u16 wazaIdx, u16 data) {
    PokemonDataWaza* wazaData = pokemonDataBiosGetGetWazaPtr(pdata, wazaIdx);
    if (wazaData) {
        wazaData->dataId = data;
    }
}

void pokemonDataBiosSetGetWazaLevel(PokemonData* pdata, u16 wazaIdx, u8 data) {
    PokemonDataWaza* wazaData = pokemonDataBiosGetGetWazaPtr(pdata, wazaIdx);
    if (wazaData) {
        wazaData->level = data;
    }
}

void pokemonDataBiosSetSinkaPokemonDataId(PokemonData* pdata, u16 sinkaIdx, u16 data) {
    Sinka* sinkaData = pokemonDataBiosGetSinkaPtr(pdata, sinkaIdx);
    if (sinkaData) {
        sinkaData->pokemonDataId = data;
    }
}

void pokemonDataBiosSetSinkaBuff(PokemonData* pdata, u16 sinkaIdx, u16 data) {
    Sinka* sinkaData = pokemonDataBiosGetSinkaPtr(pdata, sinkaIdx);
    if (sinkaData) {
        sinkaData->buff = data;
    }
}

void pokemonDataBiosSetSinkaKind(PokemonData* pdata, u16 sinkaIdx, u8 data) {
    Sinka* sinkaData = pokemonDataBiosGetSinkaPtr(pdata, sinkaIdx);
    if (sinkaData) {
        sinkaData->kind = data;
    }
}

void pokemonDataBiosSetTokuseiDataId(PokemonData* pdata, u16 index, u8 data) {
    if (pdata && index < 2) {
        pdata->tokuseiDataId[index] = data;
    }
}

void pokemonDataBiosSetZokuseiDataId(PokemonData* pdata, u16 index, u8 data) {
    if (pdata && index < 2) {
        pdata->zokuseiDataId[index] = data;
    }
}

void pokemonDataBiosSetItemDataId(PokemonData* pdata, u16 index, u16 data) {
    if (pdata && index < 2) {
        pdata->itemDataId[index] = data;
    }
}

void pokemonDataBiosSetInitFriend(PokemonData* pdata, u16 data) {
    if (pdata) {
        pdata->initFriend = data;
    }
}

void pokemonDataBiosSetSexRatio(PokemonData* pdata, u8 data) {
    if (pdata) {
        pdata->sexRatio = data;
    }
}

void pokemonDataBiosSetGet(PokemonData* pdata, u8 data) {
    if (pdata) {
        pdata->get = data;
    }
}

void pokemonDataBiosSetGrowDataId(PokemonData* pdata, u8 data) {
    if (pdata) {
        pdata->growDataId = data;
    }
}

void pokemonDataBiosSetGiveExp(PokemonData* pdata, u16 data) {
    if (pdata) {
        pdata->giveExp = data;
    }
}

void pokemonDataBiosSetGiveNimblenessEffort(PokemonData* pdata, u16 data) {
    BasisStatus* statusData = pokemonDataBiosGetBasisStatusPtr(pdata, 1);
    if (statusData) {
        statusData->nimbleness = data;
    }
}

void pokemonDataBiosSetGiveSpeDefEffort(PokemonData* pdata, u16 data) {
    BasisStatus* statusData = pokemonDataBiosGetBasisStatusPtr(pdata, 1);
    if (statusData) {
        statusData->speDef = data;
    }
}

void pokemonDataBiosSetGiveSpeAtkEffort(PokemonData* pdata, u16 data) {
    BasisStatus* statusData = pokemonDataBiosGetBasisStatusPtr(pdata, 1);
    if (statusData) {
        statusData->speAtk = data;
    }
}

void pokemonDataBiosSetGivePhyDefEffort(PokemonData* pdata, u16 data) {
    BasisStatus* statusData = pokemonDataBiosGetBasisStatusPtr(pdata, 1);
    if (statusData) {
        statusData->phyDef = data;
    }
}

void pokemonDataBiosSetGivePhyAtkEffort(PokemonData* pdata, u16 data) {
    BasisStatus* statusData = pokemonDataBiosGetBasisStatusPtr(pdata, 1);
    if (statusData) {
        statusData->phyAtk = data;
    }
}

void pokemonDataBiosSetGiveMaxHpEffort(PokemonData* pdata, u16 data) {
    BasisStatus* statusData = pokemonDataBiosGetBasisStatusPtr(pdata, 1);
    if (statusData) {
        statusData->maxHp = data;
    }
}

void pokemonDataBiosSetBasisNimbleness(PokemonData* pdata, u16 data) {
    BasisStatus* statusData = pokemonDataBiosGetBasisStatusPtr(pdata, 0);
    if (statusData) {
        statusData->nimbleness = data;
    }
}

void pokemonDataBiosSetBasisSpeDef(PokemonData* pdata, u16 data) {
    BasisStatus* statusData = pokemonDataBiosGetBasisStatusPtr(pdata, 0);
    if (statusData) {
        statusData->speDef = data;
    }
}

void pokemonDataBiosSetBasisSpeAtk(PokemonData* pdata, u16 data) {
    BasisStatus* statusData = pokemonDataBiosGetBasisStatusPtr(pdata, 0);
    if (statusData) {
        statusData->speAtk = data;
    }
}

void pokemonDataBiosSetBasisPhyDef(PokemonData* pdata, u16 data) {
    BasisStatus* statusData = pokemonDataBiosGetBasisStatusPtr(pdata, 0);
    if (statusData) {
        statusData->phyDef = data;
    }
}

void pokemonDataBiosSetBasisPhyAtk(PokemonData* pdata, u16 data) {
    BasisStatus* statusData = pokemonDataBiosGetBasisStatusPtr(pdata, 0);
    if (statusData) {
        statusData->phyAtk = data;
    }
}

void pokemonDataBiosSetBasisMaxHp(PokemonData* pdata, u16 data) {
    BasisStatus* statusData = pokemonDataBiosGetBasisStatusPtr(pdata, 0);
    if (statusData) {
        statusData->maxHp = data;
    }
}

void pokemonDataBiosSetName(PokemonData* pdata, const char* data) {
    if (pdata) {
        pdata->name = data;
    }
}

void pokemonBiosSetEventGetFlag(Pokemon* poke, u32 data) {
    if (poke) {
        poke->eventGetFlag = (u8)data;
    }
}

void pokemonBiosSetFightTrainerPokemonDataId(Pokemon* poke, u16 data) {
    if (poke) {
        poke->fightTrainerPokemonDataId = data;
    }
}

void pokemonBiosSetPara1Amari(Pokemon* poke, u16 data) {
    if (poke) {
        poke->setPara1Amari(data);
    }
}

void pokemonBiosSetAmari(Pokemon* poke, u16 data) {
    if (poke) {
        poke->setAmari(data);
    }
}

void pokemonBiosSetMailId(Pokemon* poke, u8 data) {
    if (poke) {
        poke->mailId = data;
    }
}

void pokemonBiosSetPcboxMark(Pokemon* poke, u8 data) {
    if (poke) {
        poke->pcboxMark = data;
    }
}

void pokemonBiosSetFlagAmari(Pokemon* poke, u8 data) {
    if (poke) {
        poke->flagAmari = data;
    }
}

void pokemonBiosSetFuseiFlag(Pokemon* poke, bool data) {
    if (poke) {
        poke->flags.bits.fusei = data;
    }
}

void pokemonBiosSetTokuseiFlag(Pokemon* poke, bool data) {
    if (poke) {
        if (pokemonDataBiosGetTokuseiDataId(pokemonDataBiosGetPtr(pokemonBiosGetPokemonDataId(poke)), 1) == 0) {
            data = false;
        }
        poke->flags.bits.tokusei = data;
    }
}

void pokemonBiosSetTamagoFlag(Pokemon* poke, bool data) {
    if (poke) {
        poke->flags.bits.tamago = data;
    }
}

void pokemonBiosSetPokerus(Pokemon* poke, u8 data) {
    if (poke) {
        poke->pokerus = data;
    }
}

void pokemonBiosSetAmariRibbon(Pokemon* poke, u8 data) {
    Ribbon* ribbon = pokemonBiosGetRibbonPtr(poke);
    if (ribbon != nullptr) {
        ribbon->bits.amari = data;
    }
}

void pokemonBiosSetWorldRibbon(Pokemon* poke, u8 data) {
    Ribbon* ribbon = pokemonBiosGetRibbonPtr(poke);
    if (ribbon != nullptr) {
        ribbon->bits.world = data;
    }
}

void pokemonBiosSetEarthRibbon(Pokemon* poke, u8 data) {
    Ribbon* ribbon = pokemonBiosGetRibbonPtr(poke);
    if (ribbon != nullptr) {
        ribbon->bits.earth = data;
    }
}

void pokemonBiosSetNationalRibbon(Pokemon* poke, u8 data) {
    Ribbon* ribbon = pokemonBiosGetRibbonPtr(poke);
    if (ribbon != nullptr) {
        ribbon->bits.national = data;
    }
}

void pokemonBiosSetCountryRibbon(Pokemon* poke, u8 data) {
    Ribbon* ribbon = pokemonBiosGetRibbonPtr(poke);
    if (ribbon != nullptr) {
        ribbon->bits.country = data;
    }
}

void pokemonBiosSetSkyRibbon(Pokemon* poke, u8 data) {
    Ribbon* ribbon = pokemonBiosGetRibbonPtr(poke);
    if (ribbon != nullptr) {
        ribbon->bits.sky = data;
    }
}

void pokemonBiosSetLandRibbon(Pokemon* poke, u8 data) {
    Ribbon* ribbon = pokemonBiosGetRibbonPtr(poke);
    if (ribbon != nullptr) {
        ribbon->bits.land = data;
    }
}

void pokemonBiosSetMarineRibbon(Pokemon* poke, u8 data) {
    Ribbon* ribbon = pokemonBiosGetRibbonPtr(poke);
    if (ribbon != nullptr) {
        ribbon->bits.marine = data;
    }
}

void pokemonBiosSetGanbaRibbon(Pokemon* poke, u8 data) {
    Ribbon* ribbon = pokemonBiosGetRibbonPtr(poke);
    if (ribbon != nullptr) {
        ribbon->bits.ganba = data;
    }
}

void pokemonBiosSetBromideRibbon(Pokemon* poke, u8 data) {
    Ribbon* ribbon = pokemonBiosGetRibbonPtr(poke);
    if (ribbon != nullptr) {
        ribbon->bits.bromide = data;
    }
}

void pokemonBiosSetVictoryRibbon(Pokemon* poke, u8 data) {
    Ribbon* ribbon = pokemonBiosGetRibbonPtr(poke);
    if (ribbon != nullptr) {
        ribbon->bits.victory = data;
    }
}

void pokemonBiosSetWinningRibbon(Pokemon* poke, u8 data) {
    Ribbon* ribbon = pokemonBiosGetRibbonPtr(poke);
    if (ribbon != nullptr) {
        ribbon->bits.winning = data;
    }
}

void pokemonBiosSetChampRibbon(Pokemon* poke, u8 data) {
    Ribbon* ribbon = pokemonBiosGetRibbonPtr(poke);
    if (ribbon != nullptr) {
        ribbon->bits.champ = data;
    }
}

void pokemonBiosSetFur(Pokemon* poke, u8 data) {
    if (poke) {
        poke->fur = data;
    }
}

void pokemonBiosSetStrongMedal(Pokemon* poke, u8 data) {
    ExpandStatus* status = pokemonBiosGetExpandStatusPtr(poke, 1);
    if (status != nullptr) {
        status->strong = data;
    }
}

void pokemonBiosSetCleverMedal(Pokemon* poke, u8 data) {
    ExpandStatus* status = pokemonBiosGetExpandStatusPtr(poke, 1);
    if (status != nullptr) {
        status->clever = data;
    }
}

void pokemonBiosSetCuteMedal(Pokemon* poke, u8 data) {
    ExpandStatus* status = pokemonBiosGetExpandStatusPtr(poke, 1);
    if (status != nullptr) {
        status->cute = data;
    }
}

void pokemonBiosSetBeautifulMedal(Pokemon* poke, u8 data) {
    ExpandStatus* status = pokemonBiosGetExpandStatusPtr(poke, 1);
    if (status != nullptr) {
        status->beautiful = data;
    }
}

void pokemonBiosSetStyleMedal(Pokemon* poke, u8 data) {
    ExpandStatus* status = pokemonBiosGetExpandStatusPtr(poke, 1);
    if (status != nullptr) {
        status->style = data;
    }
}

void pokemonBiosSetStrong(Pokemon* poke, u8 data) {
    ExpandStatus* status = pokemonBiosGetExpandStatusPtr(poke, 0);
    if (status != nullptr) {
        status->strong = data;
    }
}

void pokemonBiosSetClever(Pokemon* poke, u8 data) {
    ExpandStatus* status = pokemonBiosGetExpandStatusPtr(poke, 0);
    if (status != nullptr) {
        status->clever = data;
    }
}

void pokemonBiosSetCute(Pokemon* poke, u8 data) {
    ExpandStatus* status = pokemonBiosGetExpandStatusPtr(poke, 0);
    if (status != nullptr) {
        status->cute = data;
    }
}

void pokemonBiosSetBeautiful(Pokemon* poke, u8 data) {
    ExpandStatus* status = pokemonBiosGetExpandStatusPtr(poke, 0);
    if (status != nullptr) {
        status->beautiful = data;
    }
}

void pokemonBiosSetStyle(Pokemon* poke, u8 data) {
    ExpandStatus* status = pokemonBiosGetExpandStatusPtr(poke, 0);
    if (status != nullptr) {
        status->style = data;
    }
}

void pokemonBiosSetDp(Pokemon* poke, s32 data) {
    if (poke) {
        if (data >= 0xFFFF)
        {
            data = 0xFFFF;
        }
        poke->setDarkPointDirect(data);
    }
}

void pokemonBiosSetDarkpokemonDataId(Pokemon* poke, u16 data) {
    if (poke) {
        poke->darkPokemonDataID = data;
    }
}

void pokemonBiosSetFriend(Pokemon* poke, u16 data) {
    if (poke) {
        poke->setFriendLevel(data);
    }
}

void pokemonBiosSetNimblenessRnd(Pokemon* poke, u16 data) {
    if (poke) {
        poke->setNimblenessRnd(data);
    }
}

void pokemonBiosSetSpeDefRnd(Pokemon* poke, u16 data) {
    if (poke) {
        poke->setSpeDefRnd(data);
    }
}

void pokemonBiosSetSpeAtkRnd(Pokemon* poke, u16 data) {
    if (poke) {
        poke->setSpeAtkRnd(data);
    }
}

void pokemonBiosSetPhyDefRnd(Pokemon* poke, u16 data) {
    if (poke) {
        poke->setPhyDefRnd(data);
    }
}

void pokemonBiosSetPhyAtkRnd(Pokemon* poke, u16 data) {
    if (poke) {
        poke->setPhyAtkRnd(data);
    }
}

void pokemonBiosSetMaxHpRnd(Pokemon* poke, u16 data) {
    if (poke) {
        poke->setMaxHpRnd(data);
    }
}

void pokemonBiosSetNimblenessEffort(Pokemon* poke, u16 data) {
    if (poke) {
        poke->setNimblenessEffort(data);
    }
}

void pokemonBiosSetSpeDefEffort(Pokemon* poke, u16 data) {
    if (poke) {
        poke->setSpeDefEffort(data);
    }
}

void pokemonBiosSetSpeAtkEffort(Pokemon* poke, u16 data) {
    if (poke) {
        poke->setSpeAtkEffort(data);
    }
}

void pokemonBiosSetPhyDefEffort(Pokemon* poke, u16 data) {
    if (poke) {
        poke->setPhyDefEffort(data);
    }
}

void pokemonBiosSetPhyAtkEffort(Pokemon* poke, u16 data) {
    if (poke) {
        poke->setPhyAtkEffort(data);
    }
}

void pokemonBiosSetMaxHpEffort(Pokemon* poke, u16 data) {
    if (poke) {
        poke->setMaxHpEffort(data);
    }
}

void pokemonBiosSetNimbleness(Pokemon* poke, u16 data) {
    if (poke) {
        poke->setNimbleness(data);
    }
}

void pokemonBiosSetSpeDef(Pokemon* poke, u16 data) {
    if (poke) {
        poke->setSpeDef(data);
    }
}

void pokemonBiosSetSpeAtk(Pokemon* poke, u16 data) {
    if (poke) {
        poke->setSpeAtk(data);
    }
}

void pokemonBiosSetPhyDef(Pokemon* poke, u16 data) {
    if (poke) {
        poke->setPhyDef(data);
    }
}

void pokemonBiosSetPhyAtk(Pokemon* poke, u16 data) {
    if (poke) {
        poke->setPhyAtk(data);
    }
}

void pokemonBiosSetMaxHp(Pokemon* poke, u16 data) {
    if (poke) {
        poke->setMaxHp(data);
    }
}

void pokemonBiosSetHp(Pokemon* poke, s16 data) {
    if (poke) {
        poke->hp = data;
        u16 maxHp = pokemonBiosGetMaxHp(poke);
        if (maxHp < poke->hp)
        {
            poke->hp = maxHp;
        }
    }
}

void pokemonBiosSetItemDataId(Pokemon* poke, u16 data) {
    if (poke) {
        poke->itemDataID = data;
    }
}

void pokemonBiosSetPokemonWazaPpCount(Pokemon* poke, u32 wazaNum, u8 count) {
    PokemonWaza* waza = pokemonBiosGetPokemonWazaPtr(poke, wazaNum, 0);
    if (waza) {
        if (count > 3) {
            count = 3;
        }
        if (pokemonWazaCheckValid(poke, wazaNum) == 1) {
            if (wazaDataBiosGetPp(wazaDataBiosGetPtr(pokemonBiosGetPokemonWazaDataId(poke, wazaNum))) <= 4) {
                return;
            }
        }
        waza->ppCount = count;
    }
}

void pokemonBiosSetPokemonWazaPp(Pokemon* poke, u32 wazaNum, u8 data) {
    PokemonWaza* waza = pokemonBiosGetPokemonWazaPtr(poke, wazaNum, 0);
    if (waza) {
        u8 maxPp = pokemonWazaGetMaxPP(poke, wazaNum);
        if (maxPp < data) {
            data = maxPp;
        }
        waza->pp = data;
    }
}

void pokemonBiosSetPokemonWazaDataId(Pokemon* poke, u32 wazaNum, u32 data) {
    PokemonWaza* waza = pokemonBiosGetPokemonWazaPtr(poke, wazaNum, 0);
    if (waza) {
        waza->dataId = data;
    }
}

void pokemonBiosSetConditionAmari(Pokemon* poke, u32 data) {
    if (poke) {
        poke->conditionAmari = data;
    }
}

void pokemonBiosSetLevel(Pokemon* poke, u8 data) {
    if (poke) {
        if (data > 100) {
            data = 100;
        }
        poke->level = data;
    }
}

void pokemonBiosSetPoolFriend(Pokemon* poke, u16 data) {
    if (poke) {
        poke->setPoolFriendLevel(data);
    }
}

void pokemonBiosSetPoolExp(Pokemon* poke, u32 data) {
    if (poke) {
        poke->setPoolExp(data);
    }
}

void pokemonBiosSetExp(Pokemon* poke, u32 data) {
    if (poke) {
        poke->exp = data;
    }
}

void pokemonBiosSetNicknameOrgPtr(Pokemon* poke, void* data) {
    if (poke == 0 || data == 0) {
        return;
    }
    GScharLenCpy(poke->nicknameOrg, data, 11);
}

void pokemonBiosSetNicknamePtr(Pokemon* poke, void* data) {
    if (poke == 0 || data == 0) {
        return;
    }
    GScharLenCpy(poke->nickname, data, 11);
    pokemonBiosSetNicknameOrgPtr(poke, data);
}

void pokemonBiosSetCatchTrainerNamePtr(Pokemon* poke, void* data) {
    if (poke == 0 || data == 0) {
        return;
    }
    GScharLenCpy(poke->catchTrainerName, data, 11);
}

void pokemonBiosSetCatchTrainerRnd(Pokemon* poke, u32 data) {
    if (poke) {
        poke->catchTrainerRnd = data;
    }
}

void pokemonBiosSetCatchTrainerSex(Pokemon* poke, u8 data) {
    if (poke) {
        poke->catchTrainerSex = data;
    }
}

void pokemonBiosSetCatchBallId(Pokemon* poke, u8 data) {
    if (poke) {
        poke->catchBallId = data;
    }
}

void pokemonBiosSetCatchLevel(Pokemon* poke, u8 data) {
    if (poke) {
        poke->catchLevel = data;
    }
}

void pokemonBiosSetCatchFloorId(Pokemon* poke, u16 data) {
    if (poke) {
        poke->catchFloorId = data;
    }
}

void pokemonBiosSetRnd(Pokemon* poke, u32 data) {
    if (poke) {
        poke->rnd = data;
    }
}

void pokemonBiosSetPokemonDataId(Pokemon* poke, u16 data) {
    if (poke) {
        poke->dataID = data;
    }
}

u16 pokemonDataBiosGetKowaza(PokemonData* pdata, u16 idx) {
    if (pdata == nullptr) {
        return 0;
    }
    if (idx >= 8) {
        return 0;
    }
    return pdata->kowaza[idx];
}

u32 pokemonDataBiosGetPkxDataId(PokemonData* pdata) {
    if (pdata == nullptr) {
        return 0;
    }
    return pdata->pkxDataId;
}

u16 pokemonDataBiosGetNumPokemon(PokemonData* pdata) {
    if (pdata == nullptr) {
        return 0;
    }
    return pdata->numPokemon;
}

u16 pokemonDataBiosGetNumZukan(PokemonData* pdata) {
    if (pdata == nullptr) {
        return 0;
    }
    return pdata->numZukan;
}

bool pokemonDataBiosGetTukamaetaFlag(PokemonData* pdata) {
    if (pdata == nullptr) {
        return 0;
    }
    return GSflagGet(pdata->tukamaetaFlag);
}

bool pokemonDataBiosGetMitaFlag(PokemonData* pdata) {
    if (pdata == nullptr) {
        return 0;
    }
    return GSflagGet(pdata->mitaFlag);
}

u16 pokemonDataBiosGetVoice(PokemonData* pdata) {
    if (pdata == nullptr) {
        return 0;
    }
    return pdata->voice;
}

u32 pokemonDataBiosGetDoc(PokemonData* pdata) {
    if (pdata == nullptr) {
        return 0;
    }
    return pdata->doc;
}

u16 pokemonDataBiosGetWeight(PokemonData* pdata) {
    if (pdata == nullptr) {
        return 0;
    }
    return pdata->weight;
}

u16 pokemonDataBiosGetHeight(PokemonData* pdata) {
    if (pdata == nullptr) {
        return 0;
    }
    return pdata->height;
}

u32 pokemonDataBiosGetTypeName(PokemonData* pdata) {
    if (pdata == nullptr) {
        return 0;
    }
    return pdata->typeName;
}

u8 pokemonDataBiosGetColor(PokemonData* pdata, u16 unk) {
    PokemonDataCgData* cgData = pokemonDataBiosGetCgDataPtr(pdata, unk);
    if (cgData == nullptr) {
        return 0;
    }

    return cgData->color;
}

u16 pokemonDataBiosGetStatusFaceMenuSpriteId(PokemonData* pdata, u16 unk) {
    PokemonDataCgData* cgData = pokemonDataBiosGetCgDataPtr(pdata, unk);
    if (cgData == nullptr) {
        return 0;
    }

    return cgData->spriteId;
}

u32 pokemonDataBiosGetPokebodyId(PokemonData* pdata, u16 unk) {
    PokemonDataCgData* cgData = pokemonDataBiosGetCgDataPtr(pdata, unk);
    if (cgData == nullptr) {
        return 0;
    }

    return cgData->pokebodyId;
}

PokemonDataCgData* pokemonDataBiosGetCgDataPtr(PokemonData* pdata, u16 cgIdx) {
    if (pdata == nullptr) {
        return nullptr;
    }
    if (cgIdx >= 2) {
        return nullptr;
    }

    return &pdata->cgData[cgIdx];
}

bool pokemonDataBiosGetWazaMcn(PokemonData* pdata, u16 index) {
    if (pdata == nullptr) {
        return false;
    }
    if (index >= 58) {
        return false;
    }
    return pdata->wazaMcn[index];
}

u16 pokemonDataBiosGetGetWazaDataId(PokemonData* pdata, u16 wazaIdx) {
    PokemonDataWaza* waza = pokemonDataBiosGetGetWazaPtr(pdata, wazaIdx);
    if (waza == nullptr) {
        return 0;
    }

    return waza->dataId;
}

u8 pokemonDataBiosGetGetWazaLevel(PokemonData* pdata, u16 wazaIdx) {
    PokemonDataWaza* waza = pokemonDataBiosGetGetWazaPtr(pdata, wazaIdx);
    if (waza == nullptr) {
        return 0;
    }

    return waza->level;
}

PokemonDataWaza* pokemonDataBiosGetGetWazaPtr(PokemonData* pdata, u16 wazaIdx) {
    if (pdata == nullptr) {
        return nullptr;
    }
    if (wazaIdx >= 20) {
        return nullptr;
    }

    return &pdata->waza[wazaIdx];
}

u16 pokemonDataBiosGetSinkaPokemonDataId(PokemonData* pdata, u16 sinkaIdx) {
    Sinka* sinka = pokemonDataBiosGetSinkaPtr(pdata, sinkaIdx);
    if (sinka == nullptr) {
        return 0;
    }

    return sinka->pokemonDataId;
}

u16 pokemonDataBiosGetSinkaBuff(PokemonData* pdata, u16 sinkaIdx) {
    Sinka* sinka = pokemonDataBiosGetSinkaPtr(pdata, sinkaIdx);
    if (sinka == nullptr) {
        return 0;
    }

    return sinka->buff;
}

u8 pokemonDataBiosGetSinkaKind(PokemonData* pdata, u16 sinkaIdx) {
    Sinka* sinka = pokemonDataBiosGetSinkaPtr(pdata, sinkaIdx);
    if (sinka == nullptr) {
        return 0;
    }

    return sinka->kind;
}

Sinka* pokemonDataBiosGetSinkaPtr(PokemonData* pdata, u16 sinkaIdx) {
    if (pdata == nullptr) {
        return nullptr;
    }
    if (sinkaIdx >= 5) {
        return nullptr;
    }

    return &pdata->sinka[sinkaIdx];
}

u8 pokemonDataBiosGetTokuseiDataId(PokemonData* pdata, u16 index) {
    if (pdata == nullptr) {
        return 0;
    }
    if (index >= 2) {
        return 0;
    }

    return pdata->tokuseiDataId[index];
}

u8 pokemonDataBiosGetZokuseiDataId(PokemonData* pdata, u16 index) {
    if (pdata == nullptr) {
        return 0;
    }
    if (index >= 2) {
        return 0;
    }

    return pdata->zokuseiDataId[index];
}

u16 pokemonDataBiosGetItemDataId(PokemonData* pdata, u16 itemIdx) {
    if (pdata == nullptr) {
        return 0;
    }
    if (itemIdx >= 2) {
        return 0;
    }

    return pdata->itemDataId[itemIdx];
}

u16 pokemonDataBiosGetInitFriend(PokemonData* pdata) {
    if (pdata == nullptr) {
        return 0;
    }
    return pdata->initFriend;
}

u8 pokemonDataBiosGetSexRatio(PokemonData* pdata) {
    if (pdata == nullptr) {
        return 0;
    }
    return pdata->sexRatio;
}

u8 pokemonDataBiosGetGet(PokemonData* pdata) {
    if (pdata == nullptr) {
        return 0;
    }
    return pdata->get;
}

u8 pokemonDataBiosGetGrowDataId(PokemonData* pdata) {
    if (pdata == nullptr) {
        return 0;
    }
    return pdata->growDataId;
}

u16 pokemonDataBiosGetGiveExp(PokemonData* pdata) {
    if (pdata == nullptr) {
        return 0;
    }
    return pdata->giveExp;
}

u16 pokemonDataBiosGetGiveNimblenessEffort(PokemonData* pdata) {
    const BasisStatus* status = pokemonDataBiosGetBasisStatusPtr(pdata, 1);
    if (status == nullptr) {
        return 0;
    }
    return status->nimbleness;
}

u16 pokemonDataBiosGetGiveSpeDefEffort(PokemonData* pdata) {
    const BasisStatus* status = pokemonDataBiosGetBasisStatusPtr(pdata, 1);
    if (status == nullptr) {
        return 0;
    }
    return status->speDef;
}

u16 pokemonDataBiosGetGiveSpeAtkEffort(PokemonData* pdata) {
    const BasisStatus* status = pokemonDataBiosGetBasisStatusPtr(pdata, 1);
    if (status == nullptr) {
        return 0;
    }
    return status->speAtk;
}

u16 pokemonDataBiosGetGivePhyDefEffort(PokemonData* pdata) {
    const BasisStatus* status = pokemonDataBiosGetBasisStatusPtr(pdata, 1);
    if (status == nullptr) {
        return 0;
    }
    return status->phyDef;
}

u16 pokemonDataBiosGetGivePhyAtkEffort(PokemonData* pdata) {
    const BasisStatus* status = pokemonDataBiosGetBasisStatusPtr(pdata, 1);
    if (status == nullptr) {
        return 0;
    }
    return status->phyAtk;
}

u16 pokemonDataBiosGetGiveMaxHpEffort(PokemonData* pdata) {
    const BasisStatus* status = pokemonDataBiosGetBasisStatusPtr(pdata, 1);
    if (status == nullptr) {
        return 0;
    }
    return status->maxHp;
}

u16 pokemonDataBiosGetBasisNimbleness(PokemonData* pdata) {
    const BasisStatus* status = pokemonDataBiosGetBasisStatusPtr(pdata, 0);
    if (status == nullptr) {
        return 0;
    }
    return status->nimbleness;
}

u16 pokemonDataBiosGetBasisSpeDef(PokemonData* pdata) {
    const BasisStatus* status = pokemonDataBiosGetBasisStatusPtr(pdata, 0);
    if (status == nullptr) {
        return 0;
    }
    return status->speDef;
}

u16 pokemonDataBiosGetBasisSpeAtk(PokemonData* pdata) {
    const BasisStatus* status = pokemonDataBiosGetBasisStatusPtr(pdata, 0);
    if (status == nullptr) {
        return 0;
    }
    return status->speAtk;
}

u16 pokemonDataBiosGetBasisPhyDef(PokemonData* pdata) {
    const BasisStatus* status = pokemonDataBiosGetBasisStatusPtr(pdata, 0);
    if (status == nullptr) {
        return 0;
    }
    return status->phyDef;
}

u16 pokemonDataBiosGetBasisPhyAtk(PokemonData* pdata) {
    const BasisStatus* status = pokemonDataBiosGetBasisStatusPtr(pdata, 0);
    if (status == nullptr) {
        return 0;
    }
    return status->phyAtk;
}

u16 pokemonDataBiosGetBasisMaxHp(PokemonData* pdata) {
    const BasisStatus* status = pokemonDataBiosGetBasisStatusPtr(pdata, 0);
    if (status == nullptr) {
        return 0;
    }
    return status->maxHp;
}

BasisStatus* pokemonDataBiosGetBasisStatusPtr(PokemonData* pdata, u16 statusIdx) {
    if (pdata == nullptr) {
        return nullptr;
    }
    if (statusIdx >= 2) {
        return nullptr;
    }
    return &pdata->basisStatus[statusIdx];
}

const char* pokemonDataBiosGetName(PokemonData* pdata) {
    if (pdata == nullptr) {
        return nullptr;
    }
    return pdata->name;
}

PokemonData* pokemonDataBiosGetPtr(u16 pokeNum) {
    u32 maxPokeNum = *pokemon_data_number;
    if (pokeNum >= maxPokeNum) {
        return nullptr;
    }
    return &pokemon_data[pokeNum];
}

u8 pokemonBiosGetEventGetFlag(Pokemon* poke) {
    if (poke == nullptr) {
        return 0;
    }
    return poke->eventGetFlag != 0;
}

u16 pokemonBiosGetFightTrainerPokemonDataId(Pokemon* poke) {
    if (poke == nullptr) {
        return 0;
    }
    return poke->fightTrainerPokemonDataId;
}

u16 pokemonBiosGetPara1Amari(Pokemon* poke) {
    if (poke == nullptr) {
        return 0;
    }
    return poke->getPara1Amari();
}

u16 pokemonBiosGetAmari(Pokemon* poke) {
    if (poke == nullptr) {
        return 0;
    }
    return poke->getAmari();
}

u8 pokemonBiosGetMailId(Pokemon* poke) {
    if (poke == nullptr) {
        return 0;
    }
    return poke->mailId;
}

u8 pokemonBiosGetPcboxMark(Pokemon* poke) {
    if (poke == nullptr) {
        return 0;
    }
    return poke->pcboxMark;
}

u8 pokemonBiosGetFlagAmari(Pokemon* poke) {
    if (poke == nullptr) {
        return 0;
    }
    return poke->flagAmari;
}

u8 pokemonBiosGetFuseiFlag(Pokemon* poke) {
    if (poke == nullptr) {
        return 0;
    }
    return poke->flags.bits.fusei != 0;
}

u8 pokemonBiosGetTokuseiFlag(Pokemon* poke) {
    if (!poke) {
        return 0;
    }
    if (pokemonDataBiosGetTokuseiDataId(pokemonDataBiosGetPtr(pokemonBiosGetPokemonDataId(poke)), 1) == 0) {
        return 0;
    }
    return poke->flags.bits.tokusei != 0;
}

u8 pokemonBiosGetTamagoFlag(Pokemon* poke) {
    if (poke == nullptr) {
        return 0;
    }
    return poke->flags.bits.tamago != 0;
}

u8 pokemonBiosGetPokerus(Pokemon* poke) {
    if (poke == nullptr) {
        return 0;
    }
    return poke->pokerus;
}

u8 pokemonBiosGetAmariRibbon(Pokemon* poke) {
    if (poke == nullptr) {
        return 0;
    }
    Ribbon* ribbon = poke->getRibbon();
    return ribbon->bits.amari;
}

u8 pokemonBiosGetWorldRibbon(Pokemon* poke) {
    Ribbon* ribbon = pokemonBiosGetRibbonPtr(poke);
    if (ribbon == nullptr) {
        return nullptr;
    }
    return ribbon->bits.world != 0;
}

u8 pokemonBiosGetEarthRibbon(Pokemon* poke) {
    Ribbon* ribbon = pokemonBiosGetRibbonPtr(poke);
    if (ribbon == nullptr) {
        return nullptr;
    }
    return ribbon->bits.earth != 0;
}

u8 pokemonBiosGetNationalRibbon(Pokemon* poke) {
    Ribbon* ribbon = pokemonBiosGetRibbonPtr(poke);
    if (ribbon == nullptr) {
        return nullptr;
    }
    return ribbon->bits.national != 0;
}

u8 pokemonBiosGetCountryRibbon(Pokemon* poke) {
    Ribbon* ribbon = pokemonBiosGetRibbonPtr(poke);
    if (ribbon == nullptr) {
        return nullptr;
    }
    return ribbon->bits.country != 0;
}

u8 pokemonBiosGetSkyRibbon(Pokemon* poke) {
    Ribbon* ribbon = pokemonBiosGetRibbonPtr(poke);
    if (ribbon == nullptr) {
        return nullptr;
    }
    return ribbon->bits.sky != 0;
}

u8 pokemonBiosGetLandRibbon(Pokemon* poke) {
    Ribbon* ribbon = pokemonBiosGetRibbonPtr(poke);
    if (ribbon == nullptr) {
        return nullptr;
    }
    return ribbon->bits.land != 0;
}

u8 pokemonBiosGetMarineRibbon(Pokemon* poke) {
    Ribbon* ribbon = pokemonBiosGetRibbonPtr(poke);
    if (ribbon == nullptr) {
        return nullptr;
    }
    return ribbon->bits.marine != 0;
}

u8 pokemonBiosGetGanbaRibbon(Pokemon* poke) {
    Ribbon* ribbon = pokemonBiosGetRibbonPtr(poke);
    if (ribbon == nullptr) {
        return nullptr;
    }
    return ribbon->bits.ganba != 0;
}

u8 pokemonBiosGetBromideRibbon(Pokemon* poke) {
    Ribbon* ribbon = pokemonBiosGetRibbonPtr(poke);
    if (ribbon == nullptr) {
        return nullptr;
    }
    return ribbon->bits.bromide != 0;
}

u8 pokemonBiosGetVictoryRibbon(Pokemon* poke) {
    Ribbon* ribbon = pokemonBiosGetRibbonPtr(poke);
    if (ribbon == nullptr) {
        return nullptr;
    }
    return ribbon->bits.victory != 0;
}

u8 pokemonBiosGetWinningRibbon(Pokemon* poke) {
    Ribbon* ribbon = pokemonBiosGetRibbonPtr(poke);
    if (ribbon == nullptr) {
        return nullptr;
    }
    return ribbon->bits.winning != 0;
}

u8 pokemonBiosGetChampRibbon(Pokemon* poke) {
    Ribbon* ribbon = pokemonBiosGetRibbonPtr(poke);
    if (ribbon == nullptr) {
        return nullptr;
    }
    return ribbon->bits.champ != 0;
}

Ribbon* pokemonBiosGetRibbonPtr(Pokemon* poke) {
    if (poke == nullptr) {
        return nullptr;
    }
    return poke->getRibbon();
}

u8 pokemonBiosGetFur(Pokemon* poke) {
    if (poke == nullptr) {
        return 0;
    }
    return poke->fur;
}

u8 pokemonBiosGetStrongMedal(Pokemon* poke) {
    ExpandStatus* status = pokemonBiosGetExpandStatusPtr(poke, 1);
    if (status == nullptr) {
        return nullptr;
    }
    return status->strong;
}

u8 pokemonBiosGetCleverMedal(Pokemon* poke) {
    ExpandStatus* status = pokemonBiosGetExpandStatusPtr(poke, 1);
    if (status == nullptr) {
        return nullptr;
    }
    return status->clever;
}

u8 pokemonBiosGetCuteMedal(Pokemon* poke) {
    ExpandStatus* status = pokemonBiosGetExpandStatusPtr(poke, 1);
    if (status == nullptr) {
        return nullptr;
    }
    return status->cute;
}

u8 pokemonBiosGetBeautifulMedal(Pokemon* poke) {
    ExpandStatus* status = pokemonBiosGetExpandStatusPtr(poke, 1);
    if (status == nullptr) {
        return nullptr;
    }
    return status->beautiful;
}

u8 pokemonBiosGetStyleMedal(Pokemon* poke) {
    ExpandStatus* status = pokemonBiosGetExpandStatusPtr(poke, 1);
    if (status == nullptr) {
        return nullptr;
    }
    return status->style;
}

u8 pokemonBiosGetStrong(Pokemon* poke) {
    ExpandStatus* status = pokemonBiosGetExpandStatusPtr(poke, 0);
    if (status == nullptr) {
        return nullptr;
    }
    return status->strong;
}

u8 pokemonBiosGetClever(Pokemon* poke) {
    ExpandStatus* status = pokemonBiosGetExpandStatusPtr(poke, 0);
    if (status == nullptr) {
        return nullptr;
    }
    return status->clever;
}

u8 pokemonBiosGetCute(Pokemon* poke) {
    ExpandStatus* status = pokemonBiosGetExpandStatusPtr(poke, 0);
    if (status == nullptr) {
        return nullptr;
    }
    return status->cute;
}

u8 pokemonBiosGetBeautiful(Pokemon* poke) {
    ExpandStatus* status = pokemonBiosGetExpandStatusPtr(poke, 0);
    if (status == nullptr) {
        return nullptr;
    }
    return status->beautiful;
}

u8 pokemonBiosGetStyle(Pokemon* poke) {
    ExpandStatus* status = pokemonBiosGetExpandStatusPtr(poke, 0);
    if (status == nullptr) {
        return nullptr;
    }
    return status->style;
}

ExpandStatus* pokemonBiosGetExpandStatusPtr(Pokemon* poke, u16 statusNum) {
    if (poke == nullptr) {
        return nullptr;
    }
    if (statusNum >= MAX_EXPAND_STATUS) {
        return nullptr;
    }
    return &poke->expandStatus[statusNum];
}

u32 pokemonBiosGetInitDp(Pokemon* poke) {
    if (poke) goto non_null;
    return 0;
non_null:
    u16 id = pokemonBiosGetDarkpokemonDataId(poke);
    if (id) goto in_range;
    return 0;
in_range:
    return darkPokemonBiosGetDarkPoint(id);
}

bool pokemonBiosGetDarkFlag(Pokemon* poke) {
    if (poke) goto non_null;
    return 0;
non_null:
    if (pokemonBiosGetDarkpokemonDataId(poke)) goto in_range;
    return 0;
in_range:
    u16 id = pokemonBiosGetDarkpokemonDataId(poke);
    return !(darkPokemonBiosGetReliveFlag(id));
}

u32 pokemonBiosGetPoolFriend(Pokemon* poke) {
    if (poke == nullptr) {
        return 0;
    }
    return poke->getPoolFriendLevel();
}

u32 pokemonBiosGetPoolExp(Pokemon* poke) {
    if (poke == nullptr) {
        return 0;
    }
    return poke->getPoolExp();
}

s32 pokemonBiosGetDp(Pokemon* poke) {
    if (poke == nullptr) {
        return 0;
    }
    return poke->getDarkPointDirect();
}

u16 pokemonBiosGetDarkpokemonDataId(Pokemon* poke) {
    if (poke == nullptr) {
        return 0;
    }
    return poke->darkPokemonDataID;
}

u16 pokemonBiosGetFriend(Pokemon* poke) {
    if (poke == nullptr) {
        return 0;
    }
    return poke->getFriendLevel();
}

u8 pokemonBiosGetNimblenessRnd(Pokemon* poke) {
    if (poke == nullptr) {
        return 0;
    }
    return poke->getNimblenessRnd();
}

u8 pokemonBiosGetSpeDefRnd(Pokemon* poke) {
    if (poke == nullptr) {
        return 0;
    }
    return poke->getSpeDefRnd();
}

u8 pokemonBiosGetSpeAtkRnd(Pokemon* poke) {
    if (poke == nullptr) {
        return 0;
    }
    return poke->getSpeAtkRnd();
}

u8 pokemonBiosGetPhyDefRnd(Pokemon* poke) {
    if (poke == nullptr) {
        return 0;
    }
    return poke->getPhyDefRnd();
}

u8 pokemonBiosGetPhyAtkRnd(Pokemon* poke) {
    if (poke == nullptr) {
        return 0;
    }
    return poke->getPhyAtkRnd();
}

u8 pokemonBiosGetMaxHpRnd(Pokemon* poke) {
    if (poke == nullptr) {
        return 0;
    }
    return poke->getMaxHpRnd();
}

u16 pokemonBiosGetNimblenessEffort(Pokemon* poke) {
    if (poke == nullptr) {
        return 0;
    }
    return poke->getNimblenessEffort();
}

u16 pokemonBiosGetSpeDefEffort(Pokemon* poke) {
    if (poke == nullptr) {
        return 0;
    }
    return poke->getSpeDefEffort();
}

u16 pokemonBiosGetSpeAtkEffort(Pokemon* poke) {
    if (poke == nullptr) {
        return 0;
    }
    return poke->getSpeAtkEffort();
}

u16 pokemonBiosGetPhyDefEffort(Pokemon* poke) {
    if (poke == nullptr) {
        return 0;
    }
    return poke->getPhyDefEffort();
}

u16 pokemonBiosGetPhyAtkEffort(Pokemon* poke) {
    if (poke == nullptr) {
        return 0;
    }
    return poke->getPhyAtkEffort();
}

u16 pokemonBiosGetMaxHpEffort(Pokemon* poke) {
    if (poke == nullptr) {
        return 0;
    }
    return poke->getMaxHpEffort();
}

u16 pokemonBiosGetNimbleness(Pokemon* poke) {
    if (poke == nullptr) {
        return 0;
    }
    return poke->getNimbleness();
}

u16 pokemonBiosGetSpeDef(Pokemon* poke) {
    if (poke == nullptr) {
        return 0;
    }
    return poke->getSpeDef();
}

u16 pokemonBiosGetSpeAtk(Pokemon* poke) {
    if (poke == nullptr) {
        return 0;
    }
    return poke->getSpeAtk();
}

u16 pokemonBiosGetPhyDef(Pokemon* poke) {
    if (poke == nullptr) {
        return 0;
    }
    return poke->getPhyDef();
}

u16 pokemonBiosGetPhyAtk(Pokemon* poke) {
    if (poke == nullptr) {
        return 0;
    }
    return poke->getPhyAtk();
}

u16 pokemonBiosGetMaxHp(Pokemon* poke) {
    if (poke == nullptr) {
        return 0;
    }
    return poke->getMaxHp();
}

u16 pokemonBiosGetHp(Pokemon* poke) {
    if (poke == nullptr) {
        return 0;
    }
    return poke->hp;
}

u16 pokemonBiosGetItemDataId(Pokemon* poke) {
    if (poke == nullptr) {
        return 0;
    }
    return poke->itemDataID;
}

u8 pokemonBiosGetPokemonWazaPpCount(Pokemon* poke, u32 wazaNum) {
    PokemonWaza* waza = pokemonBiosGetPokemonWazaPtr(poke, wazaNum, 1);
    if (waza == nullptr) {
        return 0;
    }
    return waza->ppCount;
}

u8 pokemonBiosGetPokemonWazaPp(Pokemon* poke, u32 wazaNum) {
    PokemonWaza* waza = pokemonBiosGetPokemonWazaPtr(poke, wazaNum, 1);
    if (waza == nullptr) {
        return 0;
    }
    return waza->pp;
}

u16 pokemonBiosGetPokemonWazaDataId(Pokemon* poke, u32 wazaNum) {
    PokemonWaza* waza = pokemonBiosGetPokemonWazaPtr(poke, wazaNum, 1);
    if (waza == nullptr) {
        return 0;
    }
    return waza->dataId;
}

PokemonWaza* pokemonBiosGetPokemonWazaPtr(Pokemon* poke, u32 wazaNum, u8 unk) {
    u8 darkWazaCount = 0;
    u8 hidden[4] = {0, 0, 0, 0};
    u8 i;

    if (!poke) {
        return 0;
    }
    u8 darkLevel = pokemonGetDarkPokemonLevel(poke);
    if (darkLevel >= 5) {
        darkWazaCount = 3;
    } else if (darkLevel >= 4) {
        darkWazaCount = 2;
    } else if (darkLevel >= 2) {
        darkWazaCount = 1;
    }

    for (i = 0; i < 4; i++) {
        hidden[i] = 0;
        if (darkPokemonBiosGetTemotiDarkWaza(pokemonBiosGetDarkpokemonDataId(poke), i) < 0x163 && darkWazaCount != 0) {
            hidden[i] = 1;
            darkWazaCount--;
        }
    }

    if (wazaNum >= 4) {
        wazaNum -= 4;
        if (wazaNum >= 4) {
            return 0;
        }
    } else if (pokemonBiosGetDarkFlag(poke) == 1) {
        u16 darkWaza = darkPokemonBiosGetTemotiDarkWaza(pokemonBiosGetDarkpokemonDataId(poke), wazaNum);
        if (darkWaza > 0x163 && darkWaza < 0x176) {
            return (PokemonWaza*)&_pokemon_waza_darkwaza[darkWaza - 0x164];
        }
        if (hidden[wazaNum] == 0) {
            return (PokemonWaza*)&_pokemon_waza_hatena;
        }
    }
    return (PokemonWaza*)((u8*)poke + 0x80 + wazaNum * 4);
}

u32 pokemonBiosGetConditionAmari(Pokemon* poke) {
    if (poke == nullptr) {
        return nullptr;
    }
    return poke->conditionAmari;
}

u8 pokemonBiosGetLevel(Pokemon* poke) {
    if (poke == nullptr) {
        return 0;
    }
    return poke->level;
}

u32 pokemonBiosGetExp(Pokemon* poke) {
    if (poke == nullptr) {
        return 0;
    }
    return poke->exp;
}

char* pokemonBiosGetNicknameOrgPtr(Pokemon* poke) {
    if (poke == nullptr) {
        return nullptr;
    }
    return &poke->nicknameOrg[0];
}

char* pokemonBiosGetNicknamePtr(Pokemon* poke) {
    if (poke == nullptr) {
        return nullptr;
    }
    return &poke->nickname[0];
}

char* pokemonBiosGetCatchTrainerNamePtr(Pokemon* poke) {
    if (poke == nullptr) {
        return nullptr;
    }
    return &poke->catchTrainerName[0];
}

u32 pokemonBiosGetCatchTrainerRnd(Pokemon* poke) {
    if (poke == nullptr) {
        return 0;
    }
    return poke->catchTrainerRnd;
}

u8 pokemonBiosGetCatchTrainerSex(Pokemon* poke) {
    if (poke == nullptr) {
        return 0;
    }
    return poke->catchTrainerSex;
}

u8 pokemonBiosGetCatchBallId(Pokemon* poke) {
    if (poke == nullptr) {
        return 0;
    }
    return poke->catchBallId;
}

u8 pokemonBiosGetCatchLevel(Pokemon* poke) {
    if (poke == nullptr) {
        return 0;
    }
    return poke->catchLevel;
}

u16 pokemonBiosGetCatchFloorId(Pokemon* poke) {
    if (poke == nullptr) {
        return 0;
    }
    return poke->catchFloorId;
}

Attest* pokemonBiosGetAttest(Pokemon* poke) {
    if (poke == nullptr) {
        return nullptr;
    }
    return &poke->attest;
}

u32 pokemonBiosGetRnd(Pokemon* poke) {
    if (poke == nullptr) {
        return 0;
    }
    return poke->rnd;
}

u16 pokemonBiosGetPokemonDataId(Pokemon* poke) {
    if (poke == nullptr) {
        return 0;
    }
    return poke->dataID;
}

void pokemonWazaBiosCopy(PokemonWaza* wazaDst, const PokemonWaza* wazaSrc) {
    if (wazaDst == nullptr) {
        return;
    }
    if (wazaSrc == nullptr) {
        return;
    }
    wazaDst->dataId = wazaSrc->dataId;
    wazaDst->pp = wazaSrc->pp;
    wazaDst->ppCount = wazaSrc->ppCount;
}

void pokemonBiosCopy(Pokemon* pokeDst, const Pokemon* pokeSrc) {
    if (pokeDst != nullptr && pokeSrc != nullptr) {
        memcpy(pokeDst, pokeSrc, sizeof(Pokemon));
    }
}

}
