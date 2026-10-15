#ifndef DARK_POKEMON_H
#define DARK_POKEMON_H

#include <global.h>

enum darkPokemonWhere { place0, place1, place2, place3, place4, place5, place6 };
enum darkPokemonStatus { darkPokemonStatus0, darkPokemonStatus1, darkPokemonStatus2, darkPokemonStatus3, darkPokemonStatusRelive };
enum darkPokemonSnatchWho { darkPokemonSnatchWho0, darkPokemonSnatchWho1, darkPokemonSnatchWho2, darkPokemonSnatchWho3 };

struct DarkPokemon {
    u8 unk0x0[60]; // 0x0, temp until struct figured out
    void setPlace(darkPokemonWhere, u8);
    u32 getWalkCount() const;
    void setWalkCount(u32 count);
    void setSnatchInfoLevel(u8 level);
    u32 getRnd() const;
    void setRnd(u32 rnd);
    void setReversPattern(u8 pattern);
    u8 getReversPattern() const;
    u16 getInitDarkPointDirect() const;
    void setCatchBallID(u16 ballId);
    u8 getCatchBallID() const;
    void setDarkPokemonID(u16 id);
    u16 getDarkPokemonID() const;
    void setPokemonID(u16 id);
    u16 getPokemonID() const;
    void setOrgTrainer(u16 trainer);
    u16 getOrgTrainer() const;
    u8 getSnatchIndex() const;
    const u16* getTrainerName() const;
    void setTrainerName(const u16* name);
    void setReversMode(bool revers);
    bool isReversMode() const;
    void setSnatchFromWho(darkPokemonSnatchWho who);
    darkPokemonSnatchWho getSnatchFromWho() const;
    void setPoolFriendLevel(u16 level);
    u32 getPoolFriendLevel() const;
    void setPoolExp(u32 exp);
    u32 getPoolExp() const;
    void setDarkPointDirect(s32 value);
    s32 getDarkPointDirect() const;
    u8 getStatusRnd(u8 index) const;
    void setStatusRnd(u8 index, u8 value);
    s32 getStatus() const;
    u16 getCatchFloorId() const;
    void setSnatchIndex(u8 index);
    void addStatus(darkPokemonStatus status);
    void setCatchFloorId(u16 floorId);
    void setUpdate(bool update);
    bool isUpdate() const;
    void setEscapeTime(u32 time);
    u32 getEscapeTime() const;
    void setSnatchTime(u32 time);
    u32 getSnatchTime() const;
    void setStatus(darkPokemonStatus status);
    bool isInformation() const;
    void setInformation(bool information);
    void init();
    bool isSnach() const;
    bool isRelive() const;
    void getPlace(darkPokemonWhere& where, u8& floor) const;
    void setWazaNew(u8 index, bool isNew);
    bool isWazaNew(u8 index) const;
    void setDarkPoint(f32 value);
    f32 getDarkPoint() const;
};

extern "C" DarkPokemon* darkPokemonGetDarkPokemon(u32 index);

#endif
