#include <dolphin/types.h>

typedef struct FightActionKindData {
    u8 pri;
    u8 unk1[3];
    void (*flowFunc)(void);
    void (*dispFunc)(void);
} FightActionKindData;

extern void fightActionFlowNullFunc(void);
extern void fightActionDispNullFunc(void);
extern void fightActionFlowKaijou(void);
extern void fightActionDispKaijou(void);
extern void fightActionFlowKaisiPre(void);
extern void fightActionDispKaisiPre(void);
extern void fightActionFlowKaisiNyuujouTrainer(void);
extern void fightActionDispKaisiNyuujouTrainer(void);
extern void fightActionFlowKaisiNyuujouPokemon(void);
extern void fightActionDispKaisiNyuujouPokemon(void);
extern void fightActionFlowKaisiPost(void);
extern void fightActionDispKaisiPost(void);
extern void fightActionFlowTenkouInit(void);
extern void fightActionDispTenkouInit(void);
extern void fightActionFlowAllFightTrainerSelectFightAction(void);
extern void fightActionDispAllFightTrainerSelectFightAction(void);
extern void fightActionFlowFightNigeru(void);
extern void fightActionDispFightNigeru(void);
extern void fightActionFlowFightOutPokemonIrekae(void);
extern void fightActionDispFightOutPokemonIrekae(void);
extern void fightActionFlowFightTrainerCall(void);
extern void fightActionDispFightTrainerCall(void);
extern void fightActionFlowAllFightOutPokemonDoFightAction(void);
extern void fightActionDispAllFightOutPokemonDoFightAction(void);
extern void fightActionFlowWazaKiaipantiPre(void);
extern void fightActionDispWazaKiaipantiPre(void);
extern void fightActionFlowOneTurnPost(void);
extern void fightActionDispOneTurnPost(void);
extern void fightActionFlowSyuuryouPre(void);
extern void fightActionDispSyuuryouPre(void);
extern void fightActionFlowSyuuryou(void);
extern void fightActionDispSyuuryou(void);
extern void fightActionFlowSyuuryouPost(void);
extern void fightActionDispSyuuryouPost(void);
extern void fightActionFlowHeijou(void);
extern void fightActionDispHeijou(void);
extern void fightActionFlowFightTrainerUseItem(void);
extern void fightActionDispFightTrainerUseItem(void);
extern void fightActionFlowFightOutPokemonOutWaza(void);
extern void fightActionDispFightOutPokemonOutWaza(void);

FightActionKindData fight_action_kind_data[] = {
    {0xFF, {0}, fightActionFlowNullFunc, fightActionDispNullFunc},
    {0xFF, {0}, fightActionFlowKaijou, fightActionDispKaijou},
    {0xFF, {0}, fightActionFlowKaisiPre, fightActionDispKaisiPre},
    {0xFF, {0}, fightActionFlowKaisiNyuujouTrainer, fightActionDispKaisiNyuujouTrainer},
    {0xFF, {0}, fightActionFlowKaisiNyuujouPokemon, fightActionDispKaisiNyuujouPokemon},
    {0xFF, {0}, fightActionFlowKaisiPost, fightActionDispKaisiPost},
    {0xFF, {0}, fightActionFlowTenkouInit, fightActionDispTenkouInit},
    {0xFF, {0}, fightActionFlowAllFightTrainerSelectFightAction, fightActionDispAllFightTrainerSelectFightAction},
    {0, {0}, fightActionFlowFightNigeru, fightActionDispFightNigeru},
    {3, {0}, fightActionFlowFightOutPokemonIrekae, fightActionDispFightOutPokemonIrekae},
    {2, {0}, fightActionFlowFightTrainerCall, fightActionDispFightTrainerCall},
    {0xFF, {0}, fightActionFlowAllFightOutPokemonDoFightAction, fightActionDispAllFightOutPokemonDoFightAction},
    {0xFF, {0}, fightActionFlowWazaKiaipantiPre, fightActionDispWazaKiaipantiPre},
    {0xFF, {0}, fightActionFlowOneTurnPost, fightActionDispOneTurnPost},
    {0xFF, {0}, fightActionFlowSyuuryouPre, fightActionDispSyuuryouPre},
    {0xFF, {0}, fightActionFlowSyuuryou, fightActionDispSyuuryou},
    {0xFF, {0}, fightActionFlowSyuuryouPost, fightActionDispSyuuryouPost},
    {0xFF, {0}, fightActionFlowHeijou, fightActionDispHeijou},
    {1, {0}, fightActionFlowFightTrainerUseItem, fightActionDispFightTrainerUseItem},
    {4, {0}, fightActionFlowFightOutPokemonOutWaza, fightActionDispFightOutPokemonOutWaza},
};

u32 fight_action_kind_data_number = sizeof(fight_action_kind_data) / sizeof(fight_action_kind_data[0]);
