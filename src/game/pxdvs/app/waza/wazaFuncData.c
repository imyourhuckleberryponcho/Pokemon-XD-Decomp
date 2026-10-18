#include <dolphin/types.h>

// Per-move handler table: AI value/hit/damage callbacks and battle-animation (WZX) callbacks.
typedef void (*WazaFunc)(void);

typedef struct WazaFuncData {
    WazaFunc aiValue;
    WazaFunc aiHit;
    WazaFunc aiDamage;
    WazaFunc aiDamageFightPokemon;
    WazaFunc wzxType;
    WazaFunc wzxVariation;
} WazaFuncData;

extern void fightTrainerAiWazaValueNull(void);
extern void fightTrainerAiWazaHitNull(void);
extern void fightTrainerAiWazaDamageNull(void);
extern void fightTrainerAiWazaDamageFightPokemonNull(void);
extern void fightWazaWzxTypeFuncNull(void);
extern void fightWazaWzxVariationFuncNull(void);
extern void fightTrainerAiWazaValueTuujouIryoku(void);
extern void fightTrainerAiWazaHit000(void);
extern void fightTrainerAiWazaDamage000(void);
extern void fightTrainerAiWazaDamageFightPokemon000(void);
extern void fightWazaWzxTypeFuncNormal(void);
extern void fightWazaWzxVariationFuncNormal(void);
extern void fightTrainerAiWazaValuePhyKuritikaru(void);
extern void fightTrainerAiWazaHit043(void);
extern void fightTrainerAiWazaDamage043(void);
extern void fightTrainerAiWazaDamageFightPokemon043(void);
extern void fightTrainerAiWazaHit029(void);
extern void fightTrainerAiWazaDamage029(void);
extern void fightTrainerAiWazaDamageFightPokemon029(void);
extern void fightTrainerAiWazaHit034(void);
extern void fightTrainerAiWazaDamage034(void);
extern void fightTrainerAiWazaDamageFightPokemon034(void);
extern void fightTrainerAiWazaValueIryokuHonoo(void);
extern void fightTrainerAiWazaHit004(void);
extern void fightTrainerAiWazaDamage004(void);
extern void fightTrainerAiWazaDamageFightPokemon004(void);
extern void fightTrainerAiWazaValueTuikaKoori(void);
extern void fightTrainerAiWazaHit005(void);
extern void fightTrainerAiWazaDamage005(void);
extern void fightTrainerAiWazaDamageFightPokemon005(void);
extern void fightTrainerAiWazaValueTuikaMahi(void);
extern void fightTrainerAiWazaHit006(void);
extern void fightTrainerAiWazaDamage006(void);
extern void fightTrainerAiWazaDamageFightPokemon006(void);
extern void fightTrainerAiWazaValueItigekihissatu(void);
extern void fightTrainerAiWazaHit038(void);
extern void fightTrainerAiWazaDamage038(void);
extern void fightTrainerAiWazaDamageFightPokemon038(void);
extern void fightTrainerAiWazaValueKamaitati(void);
extern void fightTrainerAiWazaHit039(void);
extern void fightTrainerAiWazaDamage039(void);
extern void fightTrainerAiWazaDamageFightPokemon039(void);
extern void fightWazaWzxTypeFuncTame(void);
extern void fightTrainerAiWazaValueKougekiAppu(void);
extern void fightTrainerAiWazaHit050(void);
extern void fightTrainerAiWazaDamage050(void);
extern void fightTrainerAiWazaDamageFightPokemon050(void);
extern void fightWazaWzxTypeFuncSpc(void);
extern void fightTrainerAiWazaHit149(void);
extern void fightTrainerAiWazaDamage149(void);
extern void fightTrainerAiWazaDamageFightPokemon149(void);
extern void fightTrainerAiWazaValueKyouseikoutai(void);
extern void fightTrainerAiWazaHit028(void);
extern void fightTrainerAiWazaDamage028(void);
extern void fightTrainerAiWazaDamageFightPokemon028(void);
extern void fightTrainerAiWazaValueSorawotobu(void);
extern void fightTrainerAiWazaHit155(void);
extern void fightTrainerAiWazaDamage155(void);
extern void fightTrainerAiWazaDamageFightPokemon155(void);
extern void fightTrainerAiWazaValueSokubaku(void);
extern void fightTrainerAiWazaHit042(void);
extern void fightTrainerAiWazaDamage042(void);
extern void fightTrainerAiWazaDamageFightPokemon042(void);
extern void fightTrainerAiWazaValueTuikaHirumi(void);
extern void fightTrainerAiWazaHit150(void);
extern void fightTrainerAiWazaDamage150(void);
extern void fightTrainerAiWazaDamageFightPokemon150(void);
extern void fightTrainerAiWazaHit044(void);
extern void fightTrainerAiWazaDamage044(void);
extern void fightTrainerAiWazaDamageFightPokemon044(void);
extern void fightTrainerAiWazaHit045(void);
extern void fightTrainerAiWazaDamage045(void);
extern void fightTrainerAiWazaDamageFightPokemon045(void);
extern void fightTrainerAiWazaHit031(void);
extern void fightTrainerAiWazaDamage031(void);
extern void fightTrainerAiWazaDamageFightPokemon031(void);
extern void fightTrainerAiWazaValueMeityuuDaun(void);
extern void fightTrainerAiWazaHit023(void);
extern void fightTrainerAiWazaDamage023(void);
extern void fightTrainerAiWazaDamageFightPokemon023(void);
extern void fightTrainerAiWazaHit048(void);
extern void fightTrainerAiWazaDamage048(void);
extern void fightTrainerAiWazaDamageFightPokemon048(void);
extern void fightTrainerAiWazaValueAbareru(void);
extern void fightTrainerAiWazaHit027(void);
extern void fightTrainerAiWazaDamage027(void);
extern void fightTrainerAiWazaDamageFightPokemon027(void);
extern void fightTrainerAiWazaHit198(void);
extern void fightTrainerAiWazaDamage198(void);
extern void fightTrainerAiWazaDamageFightPokemon198(void);
extern void fightTrainerAiWazaValueBougyoDaun(void);
extern void fightTrainerAiWazaHit019(void);
extern void fightTrainerAiWazaDamage019(void);
extern void fightTrainerAiWazaDamageFightPokemon019(void);
extern void fightWazaWzxTypeFuncAtt(void);
extern void fightTrainerAiWazaValueTuikaDoku(void);
extern void fightTrainerAiWazaHit002(void);
extern void fightTrainerAiWazaDamage002(void);
extern void fightTrainerAiWazaDamageFightPokemon002(void);
extern void fightTrainerAiWazaHit077(void);
extern void fightTrainerAiWazaDamage077(void);
extern void fightTrainerAiWazaDamageFightPokemon077(void);
extern void fightTrainerAiWazaValueKougekiDaun(void);
extern void fightTrainerAiWazaHit018(void);
extern void fightTrainerAiWazaDamage018(void);
extern void fightTrainerAiWazaDamageFightPokemon018(void);
extern void fightTrainerAiWazaValueNemurare(void);
extern void fightTrainerAiWazaHit001(void);
extern void fightTrainerAiWazaDamage001(void);
extern void fightTrainerAiWazaDamageFightPokemon001(void);
extern void fightTrainerAiWazaValueKonran(void);
extern void fightTrainerAiWazaHit049(void);
extern void fightTrainerAiWazaDamage049(void);
extern void fightTrainerAiWazaDamageFightPokemon049(void);
extern void fightTrainerAiWazaValueTeiryouDameeji(void);
extern void fightTrainerAiWazaHit130(void);
extern void fightTrainerAiWazaDamage130(void);
extern void fightTrainerAiWazaDamageFightPokemon130(void);
extern void fightTrainerAiWazaValueKanasibari(void);
extern void fightTrainerAiWazaHit086(void);
extern void fightTrainerAiWazaDamage086(void);
extern void fightTrainerAiWazaDamageFightPokemon086(void);
extern void fightTrainerAiWazaValueTuikouBougyoDaun(void);
extern void fightTrainerAiWazaHit069(void);
extern void fightTrainerAiWazaDamage069(void);
extern void fightTrainerAiWazaDamageFightPokemon069(void);
extern void fightTrainerAiWazaValueSiroikiri(void);
extern void fightTrainerAiWazaHit046(void);
extern void fightTrainerAiWazaDamage046(void);
extern void fightTrainerAiWazaDamageFightPokemon046(void);
extern void fightWazaWzxTypeFuncAllAlly(void);
extern void fightTrainerAiWazaValueTuikouKonran(void);
extern void fightTrainerAiWazaHit076(void);
extern void fightTrainerAiWazaDamage076(void);
extern void fightTrainerAiWazaDamageFightPokemon076(void);
extern void fightTrainerAiWazaValueTuikouSubayasaDaun(void);
extern void fightTrainerAiWazaHit070(void);
extern void fightTrainerAiWazaDamage070(void);
extern void fightTrainerAiWazaDamageFightPokemon070(void);
extern void fightTrainerAiWazaValueOororabiimu(void);
extern void fightTrainerAiWazaHit068(void);
extern void fightTrainerAiWazaDamage068(void);
extern void fightTrainerAiWazaDamageFightPokemon068(void);
extern void fightTrainerAiWazaValueHandou(void);
extern void fightTrainerAiWazaHit080(void);
extern void fightTrainerAiWazaDamage080(void);
extern void fightTrainerAiWazaDamageFightPokemon080(void);
extern void fightTrainerAiWazaHit196(void);
extern void fightTrainerAiWazaDamage196(void);
extern void fightTrainerAiWazaDamageFightPokemon196(void);
extern void fightWazaWzxVariationFuncKetaguri(void);
extern void fightTrainerAiWazaValueKauntaa(void);
extern void fightTrainerAiWazaHit089(void);
extern void fightTrainerAiWazaDamage089(void);
extern void fightTrainerAiWazaDamageFightPokemon089(void);
extern void fightTrainerAiWazaHit087(void);
extern void fightTrainerAiWazaDamage087(void);
extern void fightTrainerAiWazaDamageFightPokemon087(void);
extern void fightWazaWzxTypeFuncNormal2(void);
extern void fightWazaWzxVariationFuncTikyuunage(void);
extern void fightTrainerAiWazaValueKyuusyuu(void);
extern void fightTrainerAiWazaHit003(void);
extern void fightTrainerAiWazaDamage003(void);
extern void fightTrainerAiWazaDamageFightPokemon003(void);
extern void fightWazaWzxTypeFuncVampire(void);
extern void fightTrainerAiWazaValueToriaezutukae(void);
extern void fightTrainerAiWazaHit084(void);
extern void fightTrainerAiWazaDamage084(void);
extern void fightTrainerAiWazaDamageFightPokemon084(void);
extern void fightTrainerAiWazaValueTokukouAppu(void);
extern void fightTrainerAiWazaHit013(void);
extern void fightTrainerAiWazaDamage013(void);
extern void fightTrainerAiWazaDamageFightPokemon013(void);
extern void fightTrainerAiWazaValueSpeKuritikaru(void);
extern void fightTrainerAiWazaValueSooraabiimu(void);
extern void fightTrainerAiWazaHit151(void);
extern void fightTrainerAiWazaDamage151(void);
extern void fightTrainerAiWazaDamageFightPokemon151(void);
extern void fightTrainerAiWazaValueDoku(void);
extern void fightTrainerAiWazaHit066(void);
extern void fightTrainerAiWazaDamage066(void);
extern void fightTrainerAiWazaDamageFightPokemon066(void);
extern void fightTrainerAiWazaValueMahi(void);
extern void fightTrainerAiWazaHit067(void);
extern void fightTrainerAiWazaDamage067(void);
extern void fightTrainerAiWazaDamageFightPokemon067(void);
extern void fightTrainerAiWazaValueSubayasaDaun(void);
extern void fightTrainerAiWazaHit020(void);
extern void fightTrainerAiWazaDamage020(void);
extern void fightTrainerAiWazaDamageFightPokemon020(void);
extern void fightTrainerAiWazaHit041(void);
extern void fightTrainerAiWazaDamage041(void);
extern void fightTrainerAiWazaDamageFightPokemon041(void);
extern void fightTrainerAiWazaValueHonoonouzu(void);
extern void fightTrainerAiWazaHit152(void);
extern void fightTrainerAiWazaDamage152(void);
extern void fightTrainerAiWazaDamageFightPokemon152(void);
extern void fightTrainerAiWazaValueJisin(void);
extern void fightTrainerAiWazaHit147(void);
extern void fightTrainerAiWazaDamage147(void);
extern void fightTrainerAiWazaDamageFightPokemon147(void);
extern void fightTrainerAiWazaHit033(void);
extern void fightTrainerAiWazaDamage033(void);
extern void fightTrainerAiWazaDamageFightPokemon033(void);
extern void fightTrainerAiWazaValueTuikouTokubouDaun(void);
extern void fightTrainerAiWazaHit072(void);
extern void fightTrainerAiWazaDamage072(void);
extern void fightTrainerAiWazaDamageFightPokemon072(void);
extern void fightTrainerAiWazaHit010(void);
extern void fightTrainerAiWazaDamage010(void);
extern void fightTrainerAiWazaDamageFightPokemon010(void);
extern void fightTrainerAiWazaValueKousokuidou(void);
extern void fightTrainerAiWazaHit052(void);
extern void fightTrainerAiWazaDamage052(void);
extern void fightTrainerAiWazaDamageFightPokemon052(void);
extern void fightTrainerAiWazaValueKouPuraioritii(void);
extern void fightTrainerAiWazaHit103(void);
extern void fightTrainerAiWazaDamage103(void);
extern void fightTrainerAiWazaDamageFightPokemon103(void);
extern void fightTrainerAiWazaHit081(void);
extern void fightTrainerAiWazaDamage081(void);
extern void fightTrainerAiWazaDamageFightPokemon081(void);
extern void fightTrainerAiWazaHit153(void);
extern void fightTrainerAiWazaDamage153(void);
extern void fightTrainerAiWazaDamageFightPokemon153(void);
extern void fightTrainerAiWazaValueRandamuSentaku(void);
extern void fightTrainerAiWazaHit082(void);
extern void fightTrainerAiWazaDamage082(void);
extern void fightTrainerAiWazaDamageFightPokemon082(void);
extern void fightWazaWzxTypeFuncAttDefSpc(void);
extern void fightTrainerAiWazaHit059(void);
extern void fightTrainerAiWazaDamage059(void);
extern void fightTrainerAiWazaDamageFightPokemon059(void);
extern void fightTrainerAiWazaValueKaihirituAppu(void);
extern void fightTrainerAiWazaHit016(void);
extern void fightTrainerAiWazaDamage016(void);
extern void fightTrainerAiWazaDamageFightPokemon016(void);
extern void fightTrainerAiWazaValueKaihuku2(void);
extern void fightTrainerAiWazaHit032(void);
extern void fightTrainerAiWazaDamage032(void);
extern void fightTrainerAiWazaDamageFightPokemon032(void);
extern void fightTrainerAiWazaValueBougyoAppu(void);
extern void fightTrainerAiWazaHit011(void);
extern void fightTrainerAiWazaDamage011(void);
extern void fightTrainerAiWazaDamageFightPokemon011(void);
extern void fightTrainerAiWazaHit108(void);
extern void fightTrainerAiWazaDamage108(void);
extern void fightTrainerAiWazaDamageFightPokemon108(void);
extern void fightTrainerAiWazaValueMarukunaru(void);
extern void fightTrainerAiWazaHit156(void);
extern void fightTrainerAiWazaDamage156(void);
extern void fightTrainerAiWazaDamageFightPokemon156(void);
extern void fightTrainerAiWazaHit051(void);
extern void fightTrainerAiWazaDamage051(void);
extern void fightTrainerAiWazaDamageFightPokemon051(void);
extern void fightTrainerAiWazaValueHikarinokabe(void);
extern void fightTrainerAiWazaHit035(void);
extern void fightTrainerAiWazaDamage035(void);
extern void fightTrainerAiWazaDamageFightPokemon035(void);
extern void fightTrainerAiWazaValueKuroikiri(void);
extern void fightTrainerAiWazaHit025(void);
extern void fightTrainerAiWazaDamage025(void);
extern void fightTrainerAiWazaDamageFightPokemon025(void);
extern void fightTrainerAiWazaValueRihurekutaa(void);
extern void fightTrainerAiWazaHit065(void);
extern void fightTrainerAiWazaDamage065(void);
extern void fightTrainerAiWazaDamageFightPokemon065(void);
extern void fightTrainerAiWazaHit047(void);
extern void fightTrainerAiWazaDamage047(void);
extern void fightTrainerAiWazaDamageFightPokemon047(void);
extern void fightTrainerAiWazaHit026(void);
extern void fightTrainerAiWazaDamage026(void);
extern void fightTrainerAiWazaDamageFightPokemon026(void);
extern void fightTrainerAiWazaValueTokubetuYuusen(void);
extern void fightTrainerAiWazaHit083(void);
extern void fightTrainerAiWazaDamage083(void);
extern void fightTrainerAiWazaDamageFightPokemon083(void);
extern void fightTrainerAiWazaValueOomugaesi(void);
extern void fightTrainerAiWazaHit009(void);
extern void fightTrainerAiWazaDamage009(void);
extern void fightTrainerAiWazaDamageFightPokemon009(void);
extern void fightTrainerAiWazaValueJibaku(void);
extern void fightTrainerAiWazaHit007(void);
extern void fightTrainerAiWazaDamage007(void);
extern void fightTrainerAiWazaDamageFightPokemon007(void);
extern void fightWazaWzxTypeFuncAttDef(void);
extern void fightTrainerAiWazaValueHittyuu(void);
extern void fightTrainerAiWazaHit017(void);
extern void fightTrainerAiWazaDamage017(void);
extern void fightTrainerAiWazaDamageFightPokemon017(void);
extern void fightTrainerAiWazaValueRokettoZutuki(void);
extern void fightTrainerAiWazaHit145(void);
extern void fightTrainerAiWazaDamage145(void);
extern void fightTrainerAiWazaDamageFightPokemon145(void);
extern void fightTrainerAiWazaValueDowasure(void);
extern void fightTrainerAiWazaHit054(void);
extern void fightTrainerAiWazaDamage054(void);
extern void fightTrainerAiWazaDamageFightPokemon054(void);
extern void fightTrainerAiWazaHit157(void);
extern void fightTrainerAiWazaDamage157(void);
extern void fightTrainerAiWazaDamageFightPokemon157(void);
extern void fightTrainerAiWazaValueYumekui(void);
extern void fightTrainerAiWazaHit008(void);
extern void fightTrainerAiWazaDamage008(void);
extern void fightTrainerAiWazaDamageFightPokemon008(void);
extern void fightTrainerAiWazaValueGoddobaado(void);
extern void fightTrainerAiWazaHit075(void);
extern void fightTrainerAiWazaDamage075(void);
extern void fightTrainerAiWazaDamageFightPokemon075(void);
extern void fightTrainerAiWazaHit057(void);
extern void fightTrainerAiWazaDamage057(void);
extern void fightTrainerAiWazaDamageFightPokemon057(void);
extern void fightWazaWzxTypeFuncHensin(void);
extern void fightTrainerAiWazaHit088(void);
extern void fightTrainerAiWazaDamage088(void);
extern void fightTrainerAiWazaDamageFightPokemon088(void);
extern void fightTrainerAiWazaHit085(void);
extern void fightTrainerAiWazaDamage085(void);
extern void fightTrainerAiWazaDamageFightPokemon085(void);
extern void fightTrainerAiWazaValueNemuru(void);
extern void fightTrainerAiWazaHit037(void);
extern void fightTrainerAiWazaDamage037(void);
extern void fightTrainerAiWazaDamageFightPokemon037(void);
extern void fightTrainerAiWazaHit030(void);
extern void fightTrainerAiWazaDamage030(void);
extern void fightTrainerAiWazaDamageFightPokemon030(void);
extern void fightTrainerAiWazaValueToraiatakku(void);
extern void fightTrainerAiWazaHit036(void);
extern void fightTrainerAiWazaDamage036(void);
extern void fightTrainerAiWazaDamageFightPokemon036(void);
extern void fightTrainerAiWazaValueIkarinomaeba(void);
extern void fightTrainerAiWazaHit040(void);
extern void fightTrainerAiWazaDamage040(void);
extern void fightTrainerAiWazaDamageFightPokemon040(void);
extern void fightTrainerAiWazaValueMigawari(void);
extern void fightTrainerAiWazaHit079(void);
extern void fightTrainerAiWazaDamage079(void);
extern void fightTrainerAiWazaDamageFightPokemon079(void);
extern void fightWazaWzxTypeFuncMigawari(void);
extern void fightTrainerAiWazaHit095(void);
extern void fightTrainerAiWazaDamage095(void);
extern void fightTrainerAiWazaDamageFightPokemon095(void);
extern void fightTrainerAiWazaHit104(void);
extern void fightTrainerAiWazaDamage104(void);
extern void fightTrainerAiWazaDamageFightPokemon104(void);
extern void fightWazaWzxVariationFuncTripleKick(void);
extern void fightTrainerAiWazaValueDouguUbau(void);
extern void fightTrainerAiWazaHit105(void);
extern void fightTrainerAiWazaDamage105(void);
extern void fightTrainerAiWazaDamageFightPokemon105(void);
extern void fightTrainerAiWazaValueKoukanKinsi(void);
extern void fightTrainerAiWazaHit106(void);
extern void fightTrainerAiWazaDamage106(void);
extern void fightTrainerAiWazaDamageFightPokemon106(void);
extern void fightTrainerAiWazaValueRokkuon(void);
extern void fightTrainerAiWazaHit094(void);
extern void fightTrainerAiWazaDamage094(void);
extern void fightTrainerAiWazaDamageFightPokemon094(void);
extern void fightTrainerAiWazaValueAkumu(void);
extern void fightTrainerAiWazaHit107(void);
extern void fightTrainerAiWazaDamage107(void);
extern void fightTrainerAiWazaDamageFightPokemon107(void);
extern void fightTrainerAiWazaValueJikokaitou(void);
extern void fightTrainerAiWazaHit125(void);
extern void fightTrainerAiWazaDamage125(void);
extern void fightTrainerAiWazaDamageFightPokemon125(void);
extern void fightTrainerAiWazaValueNemuriKoudou(void);
extern void fightTrainerAiWazaHit092(void);
extern void fightTrainerAiWazaDamage092(void);
extern void fightTrainerAiWazaDamageFightPokemon092(void);
extern void fightTrainerAiWazaValueNoroi(void);
extern void fightTrainerAiWazaHit109(void);
extern void fightTrainerAiWazaDamage109(void);
extern void fightTrainerAiWazaDamageFightPokemon109(void);
extern void fightTrainerAiWazaHit099(void);
extern void fightTrainerAiWazaDamage099(void);
extern void fightTrainerAiWazaDamageFightPokemon099(void);
extern void fightTrainerAiWazaHit093(void);
extern void fightTrainerAiWazaDamage093(void);
extern void fightTrainerAiWazaDamageFightPokemon093(void);
extern void fightTrainerAiWazaHit060(void);
extern void fightTrainerAiWazaDamage060(void);
extern void fightTrainerAiWazaDamageFightPokemon060(void);
extern void fightTrainerAiWazaValueUrami(void);
extern void fightTrainerAiWazaHit100(void);
extern void fightTrainerAiWazaDamage100(void);
extern void fightTrainerAiWazaDamageFightPokemon100(void);
extern void fightTrainerAiWazaValueMamoru(void);
extern void fightTrainerAiWazaHit111(void);
extern void fightTrainerAiWazaDamage111(void);
extern void fightTrainerAiWazaDamageFightPokemon111(void);
extern void fightTrainerAiWazaValueHaradaiko(void);
extern void fightTrainerAiWazaHit142(void);
extern void fightTrainerAiWazaDamage142(void);
extern void fightTrainerAiWazaDamageFightPokemon142(void);
extern void fightTrainerAiWazaValueDorokake(void);
extern void fightTrainerAiWazaHit073(void);
extern void fightTrainerAiWazaDamage073(void);
extern void fightTrainerAiWazaDamageFightPokemon073(void);
extern void fightTrainerAiWazaValueTuikouMeityuuDaun(void);
extern void fightTrainerAiWazaValueMakibisi(void);
extern void fightTrainerAiWazaHit112(void);
extern void fightTrainerAiWazaDamage112(void);
extern void fightTrainerAiWazaDamageFightPokemon112(void);
extern void fightWazaWzxTypeFuncAllEnemy(void);
extern void fightTrainerAiWazaValueDenjihou(void);
extern void fightTrainerAiWazaValueMiyaburu(void);
extern void fightTrainerAiWazaHit113(void);
extern void fightTrainerAiWazaDamage113(void);
extern void fightTrainerAiWazaDamageFightPokemon113(void);
extern void fightTrainerAiWazaValueMitizure(void);
extern void fightTrainerAiWazaHit098(void);
extern void fightTrainerAiWazaDamage098(void);
extern void fightTrainerAiWazaDamageFightPokemon098(void);
extern void fightTrainerAiWazaHit114(void);
extern void fightTrainerAiWazaDamage114(void);
extern void fightTrainerAiWazaDamageFightPokemon114(void);
extern void fightTrainerAiWazaValueKogoerukaze(void);
extern void fightTrainerAiWazaValueSunaarasi(void);
extern void fightTrainerAiWazaHit115(void);
extern void fightTrainerAiWazaDamage115(void);
extern void fightTrainerAiWazaDamageFightPokemon115(void);
extern void fightTrainerAiWazaValueKoraeru(void);
extern void fightTrainerAiWazaHit116(void);
extern void fightTrainerAiWazaDamage116(void);
extern void fightTrainerAiWazaDamageFightPokemon116(void);
extern void fightTrainerAiWazaHit058(void);
extern void fightTrainerAiWazaDamage058(void);
extern void fightTrainerAiWazaDamageFightPokemon058(void);
extern void fightTrainerAiWazaValueKorogaru(void);
extern void fightTrainerAiWazaHit117(void);
extern void fightTrainerAiWazaDamage117(void);
extern void fightTrainerAiWazaDamageFightPokemon117(void);
extern void fightWazaWzxVariationFuncKorogaru(void);
extern void fightTrainerAiWazaHit101(void);
extern void fightTrainerAiWazaDamage101(void);
extern void fightTrainerAiWazaDamageFightPokemon101(void);
extern void fightTrainerAiWazaValueIbaru(void);
extern void fightTrainerAiWazaHit118(void);
extern void fightTrainerAiWazaDamage118(void);
extern void fightTrainerAiWazaDamageFightPokemon118(void);
extern void fightTrainerAiWazaHit119(void);
extern void fightTrainerAiWazaDamage119(void);
extern void fightTrainerAiWazaDamageFightPokemon119(void);
extern void fightWazaWzxVariationFuncRenzokugiri(void);
extern void fightTrainerAiWazaValueHaganenotubasa(void);
extern void fightTrainerAiWazaHit138(void);
extern void fightTrainerAiWazaDamage138(void);
extern void fightTrainerAiWazaDamageFightPokemon138(void);
extern void fightTrainerAiWazaValueMeromero(void);
extern void fightTrainerAiWazaHit120(void);
extern void fightTrainerAiWazaDamage120(void);
extern void fightTrainerAiWazaDamageFightPokemon120(void);
extern void fightTrainerAiWazaHit097(void);
extern void fightTrainerAiWazaDamage097(void);
extern void fightTrainerAiWazaDamageFightPokemon097(void);
extern void fightTrainerAiWazaValueAroma(void);
extern void fightTrainerAiWazaHit102(void);
extern void fightTrainerAiWazaDamage102(void);
extern void fightTrainerAiWazaDamageFightPokemon102(void);
extern void fightTrainerAiWazaHit121(void);
extern void fightTrainerAiWazaDamage121(void);
extern void fightTrainerAiWazaDamageFightPokemon121(void);
extern void fightWazaWzxVariationFuncOngaesi(void);
extern void fightTrainerAiWazaHit122(void);
extern void fightTrainerAiWazaDamage122(void);
extern void fightTrainerAiWazaDamageFightPokemon122(void);
extern void fightWazaWzxVariationFuncPresent(void);
extern void fightTrainerAiWazaHit123(void);
extern void fightTrainerAiWazaDamage123(void);
extern void fightTrainerAiWazaDamageFightPokemon123(void);
extern void fightWazaWzxVariationFuncYatuatari(void);
extern void fightTrainerAiWazaHit124(void);
extern void fightTrainerAiWazaDamage124(void);
extern void fightTrainerAiWazaDamageFightPokemon124(void);
extern void fightTrainerAiWazaValueItamiwake(void);
extern void fightTrainerAiWazaHit091(void);
extern void fightTrainerAiWazaDamage091(void);
extern void fightTrainerAiWazaDamageFightPokemon091(void);
extern void fightWazaWzxTypeFuncItamiwake(void);
extern void fightTrainerAiWazaHit126(void);
extern void fightTrainerAiWazaDamage126(void);
extern void fightTrainerAiWazaDamageFightPokemon126(void);
extern void fightWazaWzxVariationFuncMagnitude(void);
extern void fightTrainerAiWazaValueBakuretuPanti(void);
extern void fightTrainerAiWazaValueBatontatti(void);
extern void fightTrainerAiWazaHit127(void);
extern void fightTrainerAiWazaDamage127(void);
extern void fightTrainerAiWazaDamageFightPokemon127(void);
extern void fightTrainerAiWazaValueAnkooru(void);
extern void fightTrainerAiWazaHit090(void);
extern void fightTrainerAiWazaDamage090(void);
extern void fightTrainerAiWazaDamageFightPokemon090(void);
extern void fightTrainerAiWazaValueOiuti(void);
extern void fightTrainerAiWazaHit128(void);
extern void fightTrainerAiWazaDamage128(void);
extern void fightTrainerAiWazaDamageFightPokemon128(void);
extern void fightWazaWzxVariationFuncOiuchi(void);
extern void fightTrainerAiWazaHit129(void);
extern void fightTrainerAiWazaDamage129(void);
extern void fightTrainerAiWazaDamageFightPokemon129(void);
extern void fightTrainerAiWazaValueKaihiDaun(void);
extern void fightTrainerAiWazaHit024(void);
extern void fightTrainerAiWazaDamage024(void);
extern void fightTrainerAiWazaDamageFightPokemon024(void);
extern void fightTrainerAiWazaValueTuikaKougekiAppu(void);
extern void fightTrainerAiWazaHit139(void);
extern void fightTrainerAiWazaDamage139(void);
extern void fightTrainerAiWazaDamageFightPokemon139(void);
extern void fightTrainerAiWazaValueAteminage(void);
extern void fightTrainerAiWazaHit078(void);
extern void fightTrainerAiWazaDamage078(void);
extern void fightTrainerAiWazaDamageFightPokemon078(void);
extern void fightTrainerAiWazaValueKaihuku1(void);
extern void fightTrainerAiWazaHit132(void);
extern void fightTrainerAiWazaDamage132(void);
extern void fightTrainerAiWazaDamageFightPokemon132(void);
extern void fightWazaWzxVariationFuncWeatherHP(void);
extern void fightTrainerAiWazaHit133(void);
extern void fightTrainerAiWazaDamage133(void);
extern void fightTrainerAiWazaDamageFightPokemon133(void);
extern void fightTrainerAiWazaHit134(void);
extern void fightTrainerAiWazaDamage134(void);
extern void fightTrainerAiWazaDamageFightPokemon134(void);
extern void fightTrainerAiWazaHit135(void);
extern void fightTrainerAiWazaDamage135(void);
extern void fightTrainerAiWazaDamageFightPokemon135(void);
extern void fightTrainerAiWazaHit146(void);
extern void fightTrainerAiWazaDamage146(void);
extern void fightTrainerAiWazaDamageFightPokemon146(void);
extern void fightTrainerAiWazaValueAmagoi(void);
extern void fightTrainerAiWazaHit136(void);
extern void fightTrainerAiWazaDamage136(void);
extern void fightTrainerAiWazaDamageFightPokemon136(void);
extern void fightTrainerAiWazaValueNihonbare(void);
extern void fightTrainerAiWazaHit137(void);
extern void fightTrainerAiWazaDamage137(void);
extern void fightTrainerAiWazaDamageFightPokemon137(void);
extern void fightTrainerAiWazaValueMiraakooto(void);
extern void fightTrainerAiWazaHit144(void);
extern void fightTrainerAiWazaDamage144(void);
extern void fightTrainerAiWazaDamageFightPokemon144(void);
extern void fightTrainerAiWazaValueJikoanji(void);
extern void fightTrainerAiWazaHit143(void);
extern void fightTrainerAiWazaDamage143(void);
extern void fightTrainerAiWazaDamageFightPokemon143(void);
extern void fightTrainerAiWazaValueZennouryokuappu(void);
extern void fightTrainerAiWazaHit140(void);
extern void fightTrainerAiWazaDamage140(void);
extern void fightTrainerAiWazaDamageFightPokemon140(void);
extern void fightTrainerAiWazaHit148(void);
extern void fightTrainerAiWazaDamage148(void);
extern void fightTrainerAiWazaDamageFightPokemon148(void);
extern void fightTrainerAiWazaHit154(void);
extern void fightTrainerAiWazaDamage154(void);
extern void fightTrainerAiWazaDamageFightPokemon154(void);
extern void fightTrainerAiWazaValueNekodamasi(void);
extern void fightTrainerAiWazaHit158(void);
extern void fightTrainerAiWazaDamage158(void);
extern void fightTrainerAiWazaDamageFightPokemon158(void);
extern void fightTrainerAiWazaValueSawagu(void);
extern void fightTrainerAiWazaHit159(void);
extern void fightTrainerAiWazaDamage159(void);
extern void fightTrainerAiWazaDamageFightPokemon159(void);
extern void fightTrainerAiWazaValueTakuwaeru(void);
extern void fightTrainerAiWazaHit160(void);
extern void fightTrainerAiWazaDamage160(void);
extern void fightTrainerAiWazaDamageFightPokemon160(void);
extern void fightTrainerAiWazaHit161(void);
extern void fightTrainerAiWazaDamage161(void);
extern void fightTrainerAiWazaDamageFightPokemon161(void);
extern void fightWazaWzxVariationFuncHakidasu(void);
extern void fightTrainerAiWazaHit162(void);
extern void fightTrainerAiWazaDamage162(void);
extern void fightTrainerAiWazaDamageFightPokemon162(void);
extern void fightWazaWzxVariationFuncNomikomu(void);
extern void fightTrainerAiWazaValueArare(void);
extern void fightTrainerAiWazaHit164(void);
extern void fightTrainerAiWazaDamage164(void);
extern void fightTrainerAiWazaDamageFightPokemon164(void);
extern void fightTrainerAiWazaHit165(void);
extern void fightTrainerAiWazaDamage165(void);
extern void fightTrainerAiWazaDamageFightPokemon165(void);
extern void fightTrainerAiWazaValueOdareru(void);
extern void fightTrainerAiWazaHit166(void);
extern void fightTrainerAiWazaDamage166(void);
extern void fightTrainerAiWazaDamageFightPokemon166(void);
extern void fightTrainerAiWazaValueOnibi(void);
extern void fightTrainerAiWazaHit167(void);
extern void fightTrainerAiWazaDamage167(void);
extern void fightTrainerAiWazaDamageFightPokemon167(void);
extern void fightTrainerAiWazaHit168(void);
extern void fightTrainerAiWazaDamage168(void);
extern void fightTrainerAiWazaDamageFightPokemon168(void);
extern void fightTrainerAiWazaHit169(void);
extern void fightTrainerAiWazaDamage169(void);
extern void fightTrainerAiWazaDamageFightPokemon169(void);
extern void fightTrainerAiWazaValueKiaipanti(void);
extern void fightTrainerAiWazaHit170(void);
extern void fightTrainerAiWazaDamage170(void);
extern void fightTrainerAiWazaDamageFightPokemon170(void);
extern void fightTrainerAiWazaValueKituke(void);
extern void fightTrainerAiWazaHit171(void);
extern void fightTrainerAiWazaDamage171(void);
extern void fightTrainerAiWazaDamageFightPokemon171(void);
extern void fightTrainerAiWazaValueKonoyubitomare(void);
extern void fightTrainerAiWazaHit172(void);
extern void fightTrainerAiWazaDamage172(void);
extern void fightTrainerAiWazaDamageFightPokemon172(void);
extern void fightTrainerAiWazaValueSizennotikara(void);
extern void fightTrainerAiWazaHit173(void);
extern void fightTrainerAiWazaDamage173(void);
extern void fightTrainerAiWazaDamageFightPokemon173(void);
extern void fightTrainerAiWazaValueJyuuden(void);
extern void fightTrainerAiWazaHit174(void);
extern void fightTrainerAiWazaDamage174(void);
extern void fightTrainerAiWazaDamageFightPokemon174(void);
extern void fightTrainerAiWazaHit175(void);
extern void fightTrainerAiWazaDamage175(void);
extern void fightTrainerAiWazaDamageFightPokemon175(void);
extern void fightTrainerAiWazaValueTedasuke(void);
extern void fightTrainerAiWazaHit176(void);
extern void fightTrainerAiWazaDamage176(void);
extern void fightTrainerAiWazaDamageFightPokemon176(void);
extern void fightWazaWzxTypeFuncTedasuke(void);
extern void fightTrainerAiWazaValuetorikku(void);
extern void fightTrainerAiWazaHit177(void);
extern void fightTrainerAiWazaDamage177(void);
extern void fightTrainerAiWazaDamageFightPokemon177(void);
extern void fightTrainerAiWazaHit178(void);
extern void fightTrainerAiWazaDamage178(void);
extern void fightTrainerAiWazaDamageFightPokemon178(void);
extern void fightTrainerAiWazaHit179(void);
extern void fightTrainerAiWazaDamage179(void);
extern void fightTrainerAiWazaDamageFightPokemon179(void);
extern void fightWazaWzxTypeFuncNegaigoto(void);
extern void fightTrainerAiWazaHit180(void);
extern void fightTrainerAiWazaDamage180(void);
extern void fightTrainerAiWazaDamageFightPokemon180(void);
extern void fightTrainerAiWazaHit181(void);
extern void fightTrainerAiWazaDamage181(void);
extern void fightTrainerAiWazaDamageFightPokemon181(void);
extern void fightTrainerAiWazaValueBakadikara(void);
extern void fightTrainerAiWazaHit182(void);
extern void fightTrainerAiWazaDamage182(void);
extern void fightTrainerAiWazaDamageFightPokemon182(void);
extern void fightTrainerAiWazaValueMajikkukooto(void);
extern void fightTrainerAiWazaHit183(void);
extern void fightTrainerAiWazaDamage183(void);
extern void fightTrainerAiWazaDamageFightPokemon183(void);
extern void fightWazaWzxTypeFuncMagiccort(void);
extern void fightTrainerAiWazaValueRisaikuru(void);
extern void fightTrainerAiWazaHit184(void);
extern void fightTrainerAiWazaDamage184(void);
extern void fightTrainerAiWazaDamageFightPokemon184(void);
extern void fightTrainerAiWazaValueRibenji(void);
extern void fightTrainerAiWazaHit185(void);
extern void fightTrainerAiWazaDamage185(void);
extern void fightTrainerAiWazaDamageFightPokemon185(void);
extern void fightTrainerAiWazaValueKawarawari(void);
extern void fightTrainerAiWazaHit186(void);
extern void fightTrainerAiWazaDamage186(void);
extern void fightTrainerAiWazaDamageFightPokemon186(void);
extern void fightWazaWzxTypeFuncKawarawari(void);
extern void fightWazaWzxVariationFuncKawarawari(void);
extern void fightTrainerAiWazaHit187(void);
extern void fightTrainerAiWazaDamage187(void);
extern void fightTrainerAiWazaDamageFightPokemon187(void);
extern void fightTrainerAiWazaValueHatakiotosu(void);
extern void fightTrainerAiWazaHit188(void);
extern void fightTrainerAiWazaDamage188(void);
extern void fightTrainerAiWazaDamageFightPokemon188(void);
extern void fightTrainerAiWazaValueGamusyara(void);
extern void fightTrainerAiWazaHit189(void);
extern void fightTrainerAiWazaDamage189(void);
extern void fightTrainerAiWazaDamageFightPokemon189(void);
extern void fightTrainerAiWazaHit190(void);
extern void fightTrainerAiWazaDamage190(void);
extern void fightTrainerAiWazaDamageFightPokemon190(void);
extern void fightTrainerAiWazaValueSukirusuwappu(void);
extern void fightTrainerAiWazaHit191(void);
extern void fightTrainerAiWazaDamage191(void);
extern void fightTrainerAiWazaDamageFightPokemon191(void);
extern void fightTrainerAiWazaValueHuuin(void);
extern void fightTrainerAiWazaHit192(void);
extern void fightTrainerAiWazaDamage192(void);
extern void fightTrainerAiWazaDamageFightPokemon192(void);
extern void fightWazaWzxTypeFuncHuuin(void);
extern void fightTrainerAiWazaValueRihuressyu(void);
extern void fightTrainerAiWazaHit193(void);
extern void fightTrainerAiWazaDamage193(void);
extern void fightTrainerAiWazaDamageFightPokemon193(void);
extern void fightTrainerAiWazaHit194(void);
extern void fightTrainerAiWazaDamage194(void);
extern void fightTrainerAiWazaDamageFightPokemon194(void);
extern void fightTrainerAiWazaValueYokodori(void);
extern void fightTrainerAiWazaHit195(void);
extern void fightTrainerAiWazaDamage195(void);
extern void fightTrainerAiWazaDamageFightPokemon195(void);
extern void fightTrainerAiWazaValueHimitunotikara(void);
extern void fightTrainerAiWazaHit197(void);
extern void fightTrainerAiWazaDamage197(void);
extern void fightTrainerAiWazaDamageFightPokemon197(void);
extern void fightTrainerAiWazaHit213(void);
extern void fightTrainerAiWazaDamage213(void);
extern void fightTrainerAiWazaDamageFightPokemon213(void);
extern void fightTrainerAiWazaHit053(void);
extern void fightTrainerAiWazaDamage053(void);
extern void fightTrainerAiWazaDamageFightPokemon053(void);
extern void fightTrainerAiWazaValueTuikouTokukouDaun(void);
extern void fightTrainerAiWazaHit071(void);
extern void fightTrainerAiWazaDamage071(void);
extern void fightTrainerAiWazaDamageFightPokemon071(void);
extern void fightTrainerAiWazaValueHurahuradansu(void);
extern void fightTrainerAiWazaHit199(void);
extern void fightTrainerAiWazaDamage199(void);
extern void fightTrainerAiWazaDamageFightPokemon199(void);
extern void fightTrainerAiWazaValueBureizukikku(void);
extern void fightTrainerAiWazaHit200(void);
extern void fightTrainerAiWazaDamage200(void);
extern void fightTrainerAiWazaDamageFightPokemon200(void);
extern void fightTrainerAiWazaHit201(void);
extern void fightTrainerAiWazaDamage201(void);
extern void fightTrainerAiWazaDamageFightPokemon201(void);
extern void fightWazaWzxVariationFuncIceball(void);
extern void fightTrainerAiWazaValueDokudokunokiba(void);
extern void fightTrainerAiWazaHit202(void);
extern void fightTrainerAiWazaDamage202(void);
extern void fightTrainerAiWazaDamageFightPokemon202(void);
extern void fightTrainerAiWazaValueUezaabooru(void);
extern void fightTrainerAiWazaHit203(void);
extern void fightTrainerAiWazaDamage203(void);
extern void fightTrainerAiWazaDamageFightPokemon203(void);
extern void fightWazaWzxVariationFuncWeatherBall(void);
extern void fightTrainerAiWazaValueTokubouDaun(void);
extern void fightTrainerAiWazaHit062(void);
extern void fightTrainerAiWazaDamage062(void);
extern void fightTrainerAiWazaDamageFightPokemon062(void);
extern void fightTrainerAiWazaValueOobaahiito(void);
extern void fightTrainerAiWazaHit204(void);
extern void fightTrainerAiWazaDamage204(void);
extern void fightTrainerAiWazaDamageFightPokemon204(void);
extern void fightTrainerAiWazaValueKanarazuSubayasaDaun(void);
extern void fightTrainerAiWazaValueKusuguruDaun(void);
extern void fightTrainerAiWazaHit205(void);
extern void fightTrainerAiWazaDamage205(void);
extern void fightTrainerAiWazaDamageFightPokemon205(void);
extern void fightTrainerAiWazaValueKosumopawaa(void);
extern void fightTrainerAiWazaHit206(void);
extern void fightTrainerAiWazaDamage206(void);
extern void fightTrainerAiWazaDamageFightPokemon206(void);
extern void fightTrainerAiWazaHit207(void);
extern void fightTrainerAiWazaDamage207(void);
extern void fightTrainerAiWazaDamageFightPokemon207(void);
extern void fightTrainerAiWazaValueBirudoAppu(void);
extern void fightTrainerAiWazaHit208(void);
extern void fightTrainerAiWazaDamage208(void);
extern void fightTrainerAiWazaDamageFightPokemon208(void);
extern void fightTrainerAiWazaValueTobihaneru(void);
extern void fightTrainerAiWazaValuePoizunteeru(void);
extern void fightTrainerAiWazaHit209(void);
extern void fightTrainerAiWazaDamage209(void);
extern void fightTrainerAiWazaDamageFightPokemon209(void);
extern void fightTrainerAiWazaHit210(void);
extern void fightTrainerAiWazaDamage210(void);
extern void fightTrainerAiWazaDamageFightPokemon210(void);
extern void fightTrainerAiWazaValueMeisou(void);
extern void fightTrainerAiWazaHit211(void);
extern void fightTrainerAiWazaDamage211(void);
extern void fightTrainerAiWazaDamageFightPokemon211(void);
extern void fightTrainerAiWazaValueRyuunomai(void);
extern void fightTrainerAiWazaHit212(void);
extern void fightTrainerAiWazaDamage212(void);
extern void fightTrainerAiWazaDamageFightPokemon212(void);
extern void fightTrainerAiWazaValueSaikobuusuto(void);
extern void fightTrainerAiWazaValueDarkEnd(void);
extern void fightTrainerAiWazaValueDarkWeather(void);
extern void fightTrainerAiWazaHit215(void);
extern void fightTrainerAiWazaDamage215(void);
extern void fightTrainerAiWazaDamageFightPokemon215(void);
extern void fightTrainerAiWazaValueDarkHold(void);
extern void fightTrainerAiWazaValueDarkMist(void);
extern void fightTrainerAiWazaHit214(void);
extern void fightTrainerAiWazaDamage214(void);
extern void fightTrainerAiWazaDamageFightPokemon214(void);
extern void fightTrainerAiWazaValueDarkPanic(void);
extern void fightTrainerAiWazaValueDarkRemove(void);
extern void fightTrainerAiWazaHit216(void);
extern void fightTrainerAiWazaDamage216(void);
extern void fightTrainerAiWazaDamageFightPokemon216(void);
extern void fightTrainerAiWazaValueDarkHalf(void);
extern void fightTrainerAiWazaHit217(void);
extern void fightTrainerAiWazaDamage217(void);
extern void fightTrainerAiWazaDamageFightPokemon217(void);

WazaFuncData waza_func_data[] = {
    {fightTrainerAiWazaValueNull, fightTrainerAiWazaHitNull, fightTrainerAiWazaDamageNull, fightTrainerAiWazaDamageFightPokemonNull, fightWazaWzxTypeFuncNull, fightWazaWzxVariationFuncNull},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit000, fightTrainerAiWazaDamage000, fightTrainerAiWazaDamageFightPokemon000, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValuePhyKuritikaru, fightTrainerAiWazaHit043, fightTrainerAiWazaDamage043, fightTrainerAiWazaDamageFightPokemon043, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit029, fightTrainerAiWazaDamage029, fightTrainerAiWazaDamageFightPokemon029, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit029, fightTrainerAiWazaDamage029, fightTrainerAiWazaDamageFightPokemon029, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit000, fightTrainerAiWazaDamage000, fightTrainerAiWazaDamageFightPokemon000, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit034, fightTrainerAiWazaDamage034, fightTrainerAiWazaDamageFightPokemon034, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueIryokuHonoo, fightTrainerAiWazaHit004, fightTrainerAiWazaDamage004, fightTrainerAiWazaDamageFightPokemon004, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuikaKoori, fightTrainerAiWazaHit005, fightTrainerAiWazaDamage005, fightTrainerAiWazaDamageFightPokemon005, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuikaMahi, fightTrainerAiWazaHit006, fightTrainerAiWazaDamage006, fightTrainerAiWazaDamageFightPokemon006, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit000, fightTrainerAiWazaDamage000, fightTrainerAiWazaDamageFightPokemon000, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit000, fightTrainerAiWazaDamage000, fightTrainerAiWazaDamageFightPokemon000, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueItigekihissatu, fightTrainerAiWazaHit038, fightTrainerAiWazaDamage038, fightTrainerAiWazaDamageFightPokemon038, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueKamaitati, fightTrainerAiWazaHit039, fightTrainerAiWazaDamage039, fightTrainerAiWazaDamageFightPokemon039, fightWazaWzxTypeFuncTame, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueKougekiAppu, fightTrainerAiWazaHit050, fightTrainerAiWazaDamage050, fightTrainerAiWazaDamageFightPokemon050, fightWazaWzxTypeFuncSpc, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit000, fightTrainerAiWazaDamage000, fightTrainerAiWazaDamageFightPokemon000, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit149, fightTrainerAiWazaDamage149, fightTrainerAiWazaDamageFightPokemon149, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit000, fightTrainerAiWazaDamage000, fightTrainerAiWazaDamageFightPokemon000, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueKyouseikoutai, fightTrainerAiWazaHit028, fightTrainerAiWazaDamage028, fightTrainerAiWazaDamageFightPokemon028, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueSorawotobu, fightTrainerAiWazaHit155, fightTrainerAiWazaDamage155, fightTrainerAiWazaDamageFightPokemon155, fightWazaWzxTypeFuncTame, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueSokubaku, fightTrainerAiWazaHit042, fightTrainerAiWazaDamage042, fightTrainerAiWazaDamageFightPokemon042, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit000, fightTrainerAiWazaDamage000, fightTrainerAiWazaDamageFightPokemon000, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit000, fightTrainerAiWazaDamage000, fightTrainerAiWazaDamageFightPokemon000, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuikaHirumi, fightTrainerAiWazaHit150, fightTrainerAiWazaDamage150, fightTrainerAiWazaDamageFightPokemon150, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit044, fightTrainerAiWazaDamage044, fightTrainerAiWazaDamageFightPokemon044, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit000, fightTrainerAiWazaDamage000, fightTrainerAiWazaDamageFightPokemon000, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit045, fightTrainerAiWazaDamage045, fightTrainerAiWazaDamageFightPokemon045, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuikaHirumi, fightTrainerAiWazaHit031, fightTrainerAiWazaDamage031, fightTrainerAiWazaDamageFightPokemon031, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueMeityuuDaun, fightTrainerAiWazaHit023, fightTrainerAiWazaDamage023, fightTrainerAiWazaDamageFightPokemon023, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuikaHirumi, fightTrainerAiWazaHit031, fightTrainerAiWazaDamage031, fightTrainerAiWazaDamageFightPokemon031, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit000, fightTrainerAiWazaDamage000, fightTrainerAiWazaDamageFightPokemon000, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit029, fightTrainerAiWazaDamage029, fightTrainerAiWazaDamageFightPokemon029, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueItigekihissatu, fightTrainerAiWazaHit038, fightTrainerAiWazaDamage038, fightTrainerAiWazaDamageFightPokemon038, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit000, fightTrainerAiWazaDamage000, fightTrainerAiWazaDamageFightPokemon000, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuikaMahi, fightTrainerAiWazaHit006, fightTrainerAiWazaDamage006, fightTrainerAiWazaDamageFightPokemon006, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueSokubaku, fightTrainerAiWazaHit042, fightTrainerAiWazaDamage042, fightTrainerAiWazaDamageFightPokemon042, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit048, fightTrainerAiWazaDamage048, fightTrainerAiWazaDamageFightPokemon048, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueAbareru, fightTrainerAiWazaHit027, fightTrainerAiWazaDamage027, fightTrainerAiWazaDamageFightPokemon027, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit198, fightTrainerAiWazaDamage198, fightTrainerAiWazaDamageFightPokemon198, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueBougyoDaun, fightTrainerAiWazaHit019, fightTrainerAiWazaDamage019, fightTrainerAiWazaDamageFightPokemon019, fightWazaWzxTypeFuncAtt, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuikaDoku, fightTrainerAiWazaHit002, fightTrainerAiWazaDamage002, fightTrainerAiWazaDamageFightPokemon002, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuikaDoku, fightTrainerAiWazaHit077, fightTrainerAiWazaDamage077, fightTrainerAiWazaDamageFightPokemon077, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit029, fightTrainerAiWazaDamage029, fightTrainerAiWazaDamageFightPokemon029, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueBougyoDaun, fightTrainerAiWazaHit019, fightTrainerAiWazaDamage019, fightTrainerAiWazaDamageFightPokemon019, fightWazaWzxTypeFuncAtt, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuikaHirumi, fightTrainerAiWazaHit031, fightTrainerAiWazaDamage031, fightTrainerAiWazaDamageFightPokemon031, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueKougekiDaun, fightTrainerAiWazaHit018, fightTrainerAiWazaDamage018, fightTrainerAiWazaDamageFightPokemon018, fightWazaWzxTypeFuncAtt, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueKyouseikoutai, fightTrainerAiWazaHit028, fightTrainerAiWazaDamage028, fightTrainerAiWazaDamageFightPokemon028, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueNemurare, fightTrainerAiWazaHit001, fightTrainerAiWazaDamage001, fightTrainerAiWazaDamageFightPokemon001, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueKonran, fightTrainerAiWazaHit049, fightTrainerAiWazaDamage049, fightTrainerAiWazaDamageFightPokemon049, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTeiryouDameeji, fightTrainerAiWazaHit130, fightTrainerAiWazaDamage130, fightTrainerAiWazaDamageFightPokemon130, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueKanasibari, fightTrainerAiWazaHit086, fightTrainerAiWazaDamage086, fightTrainerAiWazaDamageFightPokemon086, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuikouBougyoDaun, fightTrainerAiWazaHit069, fightTrainerAiWazaDamage069, fightTrainerAiWazaDamageFightPokemon069, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueIryokuHonoo, fightTrainerAiWazaHit004, fightTrainerAiWazaDamage004, fightTrainerAiWazaDamageFightPokemon004, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueIryokuHonoo, fightTrainerAiWazaHit004, fightTrainerAiWazaDamage004, fightTrainerAiWazaDamageFightPokemon004, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueSiroikiri, fightTrainerAiWazaHit046, fightTrainerAiWazaDamage046, fightTrainerAiWazaDamageFightPokemon046, fightWazaWzxTypeFuncAllAlly, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit000, fightTrainerAiWazaDamage000, fightTrainerAiWazaDamageFightPokemon000, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit000, fightTrainerAiWazaDamage000, fightTrainerAiWazaDamageFightPokemon000, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit000, fightTrainerAiWazaDamage000, fightTrainerAiWazaDamageFightPokemon000, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuikaKoori, fightTrainerAiWazaHit005, fightTrainerAiWazaDamage005, fightTrainerAiWazaDamageFightPokemon005, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuikaKoori, fightTrainerAiWazaHit005, fightTrainerAiWazaDamage005, fightTrainerAiWazaDamageFightPokemon005, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuikouKonran, fightTrainerAiWazaHit076, fightTrainerAiWazaDamage076, fightTrainerAiWazaDamageFightPokemon076, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuikouSubayasaDaun, fightTrainerAiWazaHit070, fightTrainerAiWazaDamage070, fightTrainerAiWazaDamageFightPokemon070, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueOororabiimu, fightTrainerAiWazaHit068, fightTrainerAiWazaDamage068, fightTrainerAiWazaDamageFightPokemon068, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueHandou, fightTrainerAiWazaHit080, fightTrainerAiWazaDamage080, fightTrainerAiWazaDamageFightPokemon080, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit000, fightTrainerAiWazaDamage000, fightTrainerAiWazaDamageFightPokemon000, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit000, fightTrainerAiWazaDamage000, fightTrainerAiWazaDamageFightPokemon000, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit048, fightTrainerAiWazaDamage048, fightTrainerAiWazaDamageFightPokemon048, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit196, fightTrainerAiWazaDamage196, fightTrainerAiWazaDamageFightPokemon196, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncKetaguri},
    {fightTrainerAiWazaValueKauntaa, fightTrainerAiWazaHit089, fightTrainerAiWazaDamage089, fightTrainerAiWazaDamageFightPokemon089, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTeiryouDameeji, fightTrainerAiWazaHit087, fightTrainerAiWazaDamage087, fightTrainerAiWazaDamageFightPokemon087, fightWazaWzxTypeFuncNormal2, fightWazaWzxVariationFuncTikyuunage},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit000, fightTrainerAiWazaDamage000, fightTrainerAiWazaDamageFightPokemon000, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueKyuusyuu, fightTrainerAiWazaHit003, fightTrainerAiWazaDamage003, fightTrainerAiWazaDamageFightPokemon003, fightWazaWzxTypeFuncVampire, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueKyuusyuu, fightTrainerAiWazaHit003, fightTrainerAiWazaDamage003, fightTrainerAiWazaDamageFightPokemon003, fightWazaWzxTypeFuncVampire, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueToriaezutukae, fightTrainerAiWazaHit084, fightTrainerAiWazaDamage084, fightTrainerAiWazaDamageFightPokemon084, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTokukouAppu, fightTrainerAiWazaHit013, fightTrainerAiWazaDamage013, fightTrainerAiWazaDamageFightPokemon013, fightWazaWzxTypeFuncSpc, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueSpeKuritikaru, fightTrainerAiWazaHit043, fightTrainerAiWazaDamage043, fightTrainerAiWazaDamageFightPokemon043, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueSooraabiimu, fightTrainerAiWazaHit151, fightTrainerAiWazaDamage151, fightTrainerAiWazaDamageFightPokemon151, fightWazaWzxTypeFuncTame, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueDoku, fightTrainerAiWazaHit066, fightTrainerAiWazaDamage066, fightTrainerAiWazaDamageFightPokemon066, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueMahi, fightTrainerAiWazaHit067, fightTrainerAiWazaDamage067, fightTrainerAiWazaDamageFightPokemon067, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueNemurare, fightTrainerAiWazaHit001, fightTrainerAiWazaDamage001, fightTrainerAiWazaDamageFightPokemon001, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueAbareru, fightTrainerAiWazaHit027, fightTrainerAiWazaDamage027, fightTrainerAiWazaDamageFightPokemon027, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueSubayasaDaun, fightTrainerAiWazaHit020, fightTrainerAiWazaDamage020, fightTrainerAiWazaDamageFightPokemon020, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTeiryouDameeji, fightTrainerAiWazaHit041, fightTrainerAiWazaDamage041, fightTrainerAiWazaDamageFightPokemon041, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueHonoonouzu, fightTrainerAiWazaHit042, fightTrainerAiWazaDamage042, fightTrainerAiWazaDamageFightPokemon042, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuikaMahi, fightTrainerAiWazaHit006, fightTrainerAiWazaDamage006, fightTrainerAiWazaDamageFightPokemon006, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuikaMahi, fightTrainerAiWazaHit006, fightTrainerAiWazaDamage006, fightTrainerAiWazaDamageFightPokemon006, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueMahi, fightTrainerAiWazaHit067, fightTrainerAiWazaDamage067, fightTrainerAiWazaDamageFightPokemon067, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuikaMahi, fightTrainerAiWazaHit152, fightTrainerAiWazaDamage152, fightTrainerAiWazaDamageFightPokemon152, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit000, fightTrainerAiWazaDamage000, fightTrainerAiWazaDamageFightPokemon000, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueJisin, fightTrainerAiWazaHit147, fightTrainerAiWazaDamage147, fightTrainerAiWazaDamageFightPokemon147, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueItigekihissatu, fightTrainerAiWazaHit038, fightTrainerAiWazaDamage038, fightTrainerAiWazaDamageFightPokemon038, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueSorawotobu, fightTrainerAiWazaHit155, fightTrainerAiWazaDamage155, fightTrainerAiWazaDamageFightPokemon155, fightWazaWzxTypeFuncTame, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueDoku, fightTrainerAiWazaHit033, fightTrainerAiWazaDamage033, fightTrainerAiWazaDamageFightPokemon033, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuikouKonran, fightTrainerAiWazaHit076, fightTrainerAiWazaDamage076, fightTrainerAiWazaDamageFightPokemon076, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuikouTokubouDaun, fightTrainerAiWazaHit072, fightTrainerAiWazaDamage072, fightTrainerAiWazaDamageFightPokemon072, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueNemurare, fightTrainerAiWazaHit001, fightTrainerAiWazaDamage001, fightTrainerAiWazaDamageFightPokemon001, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueKougekiAppu, fightTrainerAiWazaHit010, fightTrainerAiWazaDamage010, fightTrainerAiWazaDamageFightPokemon010, fightWazaWzxTypeFuncSpc, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueKousokuidou, fightTrainerAiWazaHit052, fightTrainerAiWazaDamage052, fightTrainerAiWazaDamageFightPokemon052, fightWazaWzxTypeFuncSpc, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueKouPuraioritii, fightTrainerAiWazaHit103, fightTrainerAiWazaDamage103, fightTrainerAiWazaDamageFightPokemon103, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit081, fightTrainerAiWazaDamage081, fightTrainerAiWazaDamageFightPokemon081, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueNull, fightTrainerAiWazaHit153, fightTrainerAiWazaDamage153, fightTrainerAiWazaDamageFightPokemon153, fightWazaWzxTypeFuncSpc, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTeiryouDameeji, fightTrainerAiWazaHit087, fightTrainerAiWazaDamage087, fightTrainerAiWazaDamageFightPokemon087, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueRandamuSentaku, fightTrainerAiWazaHit082, fightTrainerAiWazaDamage082, fightTrainerAiWazaDamageFightPokemon082, fightWazaWzxTypeFuncAttDefSpc, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueBougyoDaun, fightTrainerAiWazaHit059, fightTrainerAiWazaDamage059, fightTrainerAiWazaDamageFightPokemon059, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueKaihirituAppu, fightTrainerAiWazaHit016, fightTrainerAiWazaDamage016, fightTrainerAiWazaDamageFightPokemon016, fightWazaWzxTypeFuncSpc, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueKaihuku2, fightTrainerAiWazaHit032, fightTrainerAiWazaDamage032, fightTrainerAiWazaDamageFightPokemon032, fightWazaWzxTypeFuncSpc, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueBougyoAppu, fightTrainerAiWazaHit011, fightTrainerAiWazaDamage011, fightTrainerAiWazaDamageFightPokemon011, fightWazaWzxTypeFuncSpc, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueKaihirituAppu, fightTrainerAiWazaHit108, fightTrainerAiWazaDamage108, fightTrainerAiWazaDamageFightPokemon108, fightWazaWzxTypeFuncSpc, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueMeityuuDaun, fightTrainerAiWazaHit023, fightTrainerAiWazaDamage023, fightTrainerAiWazaDamageFightPokemon023, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueKonran, fightTrainerAiWazaHit049, fightTrainerAiWazaDamage049, fightTrainerAiWazaDamageFightPokemon049, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueBougyoAppu, fightTrainerAiWazaHit011, fightTrainerAiWazaDamage011, fightTrainerAiWazaDamageFightPokemon011, fightWazaWzxTypeFuncSpc, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueMarukunaru, fightTrainerAiWazaHit156, fightTrainerAiWazaDamage156, fightTrainerAiWazaDamageFightPokemon156, fightWazaWzxTypeFuncSpc, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueBougyoAppu, fightTrainerAiWazaHit051, fightTrainerAiWazaDamage051, fightTrainerAiWazaDamageFightPokemon051, fightWazaWzxTypeFuncSpc, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueHikarinokabe, fightTrainerAiWazaHit035, fightTrainerAiWazaDamage035, fightTrainerAiWazaDamageFightPokemon035, fightWazaWzxTypeFuncAllAlly, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueKuroikiri, fightTrainerAiWazaHit025, fightTrainerAiWazaDamage025, fightTrainerAiWazaDamageFightPokemon025, fightWazaWzxTypeFuncSpc, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueRihurekutaa, fightTrainerAiWazaHit065, fightTrainerAiWazaDamage065, fightTrainerAiWazaDamageFightPokemon065, fightWazaWzxTypeFuncAllAlly, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueToriaezutukae, fightTrainerAiWazaHit047, fightTrainerAiWazaDamage047, fightTrainerAiWazaDamageFightPokemon047, fightWazaWzxTypeFuncSpc, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit026, fightTrainerAiWazaDamage026, fightTrainerAiWazaDamageFightPokemon026, fightWazaWzxTypeFuncTame, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTokubetuYuusen, fightTrainerAiWazaHit083, fightTrainerAiWazaDamage083, fightTrainerAiWazaDamageFightPokemon083, fightWazaWzxTypeFuncAtt, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueOomugaesi, fightTrainerAiWazaHit009, fightTrainerAiWazaDamage009, fightTrainerAiWazaDamageFightPokemon009, fightWazaWzxTypeFuncNull, fightWazaWzxVariationFuncNull},
    {fightTrainerAiWazaValueJibaku, fightTrainerAiWazaHit007, fightTrainerAiWazaDamage007, fightTrainerAiWazaDamageFightPokemon007, fightWazaWzxTypeFuncAttDef, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit000, fightTrainerAiWazaDamage000, fightTrainerAiWazaDamageFightPokemon000, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuikaMahi, fightTrainerAiWazaHit006, fightTrainerAiWazaDamage006, fightTrainerAiWazaDamageFightPokemon006, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuikaDoku, fightTrainerAiWazaHit002, fightTrainerAiWazaDamage002, fightTrainerAiWazaDamageFightPokemon002, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuikaDoku, fightTrainerAiWazaHit002, fightTrainerAiWazaDamage002, fightTrainerAiWazaDamageFightPokemon002, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuikaHirumi, fightTrainerAiWazaHit031, fightTrainerAiWazaDamage031, fightTrainerAiWazaDamageFightPokemon031, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueIryokuHonoo, fightTrainerAiWazaHit004, fightTrainerAiWazaDamage004, fightTrainerAiWazaDamageFightPokemon004, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit000, fightTrainerAiWazaDamage000, fightTrainerAiWazaDamageFightPokemon000, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueSokubaku, fightTrainerAiWazaHit042, fightTrainerAiWazaDamage042, fightTrainerAiWazaDamageFightPokemon042, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueHittyuu, fightTrainerAiWazaHit017, fightTrainerAiWazaDamage017, fightTrainerAiWazaDamageFightPokemon017, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueRokettoZutuki, fightTrainerAiWazaHit145, fightTrainerAiWazaDamage145, fightTrainerAiWazaDamageFightPokemon145, fightWazaWzxTypeFuncTame, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit029, fightTrainerAiWazaDamage029, fightTrainerAiWazaDamageFightPokemon029, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuikouSubayasaDaun, fightTrainerAiWazaHit070, fightTrainerAiWazaDamage070, fightTrainerAiWazaDamageFightPokemon070, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueDowasure, fightTrainerAiWazaHit054, fightTrainerAiWazaDamage054, fightTrainerAiWazaDamageFightPokemon054, fightWazaWzxTypeFuncSpc, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueMeityuuDaun, fightTrainerAiWazaHit023, fightTrainerAiWazaDamage023, fightTrainerAiWazaDamageFightPokemon023, fightWazaWzxTypeFuncAtt, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueKaihuku2, fightTrainerAiWazaHit157, fightTrainerAiWazaDamage157, fightTrainerAiWazaDamageFightPokemon157, fightWazaWzxTypeFuncSpc, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit045, fightTrainerAiWazaDamage045, fightTrainerAiWazaDamageFightPokemon045, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueMahi, fightTrainerAiWazaHit067, fightTrainerAiWazaDamage067, fightTrainerAiWazaDamageFightPokemon067, fightWazaWzxTypeFuncAtt, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueYumekui, fightTrainerAiWazaHit008, fightTrainerAiWazaDamage008, fightTrainerAiWazaDamageFightPokemon008, fightWazaWzxTypeFuncAttDefSpc, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueDoku, fightTrainerAiWazaHit066, fightTrainerAiWazaDamage066, fightTrainerAiWazaDamageFightPokemon066, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit029, fightTrainerAiWazaDamage029, fightTrainerAiWazaDamageFightPokemon029, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueKyuusyuu, fightTrainerAiWazaHit003, fightTrainerAiWazaDamage003, fightTrainerAiWazaDamageFightPokemon003, fightWazaWzxTypeFuncVampire, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueNemurare, fightTrainerAiWazaHit001, fightTrainerAiWazaDamage001, fightTrainerAiWazaDamageFightPokemon001, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueGoddobaado, fightTrainerAiWazaHit075, fightTrainerAiWazaDamage075, fightTrainerAiWazaDamageFightPokemon075, fightWazaWzxTypeFuncTame, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueRandamuSentaku, fightTrainerAiWazaHit057, fightTrainerAiWazaDamage057, fightTrainerAiWazaDamageFightPokemon057, fightWazaWzxTypeFuncHensin, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuikouSubayasaDaun, fightTrainerAiWazaHit070, fightTrainerAiWazaDamage070, fightTrainerAiWazaDamageFightPokemon070, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuikouKonran, fightTrainerAiWazaHit076, fightTrainerAiWazaDamage076, fightTrainerAiWazaDamageFightPokemon076, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueNemurare, fightTrainerAiWazaHit001, fightTrainerAiWazaDamage001, fightTrainerAiWazaDamageFightPokemon001, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueMeityuuDaun, fightTrainerAiWazaHit023, fightTrainerAiWazaDamage023, fightTrainerAiWazaDamageFightPokemon023, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTeiryouDameeji, fightTrainerAiWazaHit088, fightTrainerAiWazaDamage088, fightTrainerAiWazaDamageFightPokemon088, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueNull, fightTrainerAiWazaHit085, fightTrainerAiWazaDamage085, fightTrainerAiWazaDamageFightPokemon085, fightWazaWzxTypeFuncAtt, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueBougyoAppu, fightTrainerAiWazaHit051, fightTrainerAiWazaDamage051, fightTrainerAiWazaDamageFightPokemon051, fightWazaWzxTypeFuncSpc, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueSpeKuritikaru, fightTrainerAiWazaHit043, fightTrainerAiWazaDamage043, fightTrainerAiWazaDamageFightPokemon043, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueJibaku, fightTrainerAiWazaHit007, fightTrainerAiWazaDamage007, fightTrainerAiWazaDamageFightPokemon007, fightWazaWzxTypeFuncAttDef, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit029, fightTrainerAiWazaDamage029, fightTrainerAiWazaDamageFightPokemon029, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit044, fightTrainerAiWazaDamage044, fightTrainerAiWazaDamageFightPokemon044, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueNemuru, fightTrainerAiWazaHit037, fightTrainerAiWazaDamage037, fightTrainerAiWazaDamageFightPokemon037, fightWazaWzxTypeFuncSpc, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuikaHirumi, fightTrainerAiWazaHit031, fightTrainerAiWazaDamage031, fightTrainerAiWazaDamageFightPokemon031, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuikaHirumi, fightTrainerAiWazaHit031, fightTrainerAiWazaDamage031, fightTrainerAiWazaDamageFightPokemon031, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueKougekiAppu, fightTrainerAiWazaHit010, fightTrainerAiWazaDamage010, fightTrainerAiWazaDamageFightPokemon010, fightWazaWzxTypeFuncSpc, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueRandamuSentaku, fightTrainerAiWazaHit030, fightTrainerAiWazaDamage030, fightTrainerAiWazaDamageFightPokemon030, fightWazaWzxTypeFuncSpc, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueToraiatakku, fightTrainerAiWazaHit036, fightTrainerAiWazaDamage036, fightTrainerAiWazaDamageFightPokemon036, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueIkarinomaeba, fightTrainerAiWazaHit040, fightTrainerAiWazaDamage040, fightTrainerAiWazaDamageFightPokemon040, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValuePhyKuritikaru, fightTrainerAiWazaHit043, fightTrainerAiWazaDamage043, fightTrainerAiWazaDamageFightPokemon043, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueMigawari, fightTrainerAiWazaHit079, fightTrainerAiWazaDamage079, fightTrainerAiWazaDamageFightPokemon079, fightWazaWzxTypeFuncMigawari, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueNull, fightTrainerAiWazaHit048, fightTrainerAiWazaDamage048, fightTrainerAiWazaDamageFightPokemon048, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueNull, fightTrainerAiWazaHit095, fightTrainerAiWazaDamage095, fightTrainerAiWazaDamageFightPokemon095, fightWazaWzxTypeFuncAttDefSpc, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit104, fightTrainerAiWazaDamage104, fightTrainerAiWazaDamageFightPokemon104, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncTripleKick},
    {fightTrainerAiWazaValueDouguUbau, fightTrainerAiWazaHit105, fightTrainerAiWazaDamage105, fightTrainerAiWazaDamageFightPokemon105, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueKoukanKinsi, fightTrainerAiWazaHit106, fightTrainerAiWazaDamage106, fightTrainerAiWazaDamageFightPokemon106, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueRokkuon, fightTrainerAiWazaHit094, fightTrainerAiWazaDamage094, fightTrainerAiWazaDamageFightPokemon094, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueAkumu, fightTrainerAiWazaHit107, fightTrainerAiWazaDamage107, fightTrainerAiWazaDamageFightPokemon107, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueJikokaitou, fightTrainerAiWazaHit125, fightTrainerAiWazaDamage125, fightTrainerAiWazaDamageFightPokemon125, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueNemuriKoudou, fightTrainerAiWazaHit092, fightTrainerAiWazaDamage092, fightTrainerAiWazaDamageFightPokemon092, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueNoroi, fightTrainerAiWazaHit109, fightTrainerAiWazaDamage109, fightTrainerAiWazaDamageFightPokemon109, fightWazaWzxTypeFuncAttDef, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit099, fightTrainerAiWazaDamage099, fightTrainerAiWazaDamageFightPokemon099, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueRandamuSentaku, fightTrainerAiWazaHit093, fightTrainerAiWazaDamage093, fightTrainerAiWazaDamageFightPokemon093, fightWazaWzxTypeFuncSpc, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValuePhyKuritikaru, fightTrainerAiWazaHit043, fightTrainerAiWazaDamage043, fightTrainerAiWazaDamageFightPokemon043, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueSubayasaDaun, fightTrainerAiWazaHit060, fightTrainerAiWazaDamage060, fightTrainerAiWazaDamageFightPokemon060, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit099, fightTrainerAiWazaDamage099, fightTrainerAiWazaDamageFightPokemon099, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueUrami, fightTrainerAiWazaHit100, fightTrainerAiWazaDamage100, fightTrainerAiWazaDamageFightPokemon100, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuikaKoori, fightTrainerAiWazaHit005, fightTrainerAiWazaDamage005, fightTrainerAiWazaDamageFightPokemon005, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueMamoru, fightTrainerAiWazaHit111, fightTrainerAiWazaDamage111, fightTrainerAiWazaDamageFightPokemon111, fightWazaWzxTypeFuncSpc, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueKouPuraioritii, fightTrainerAiWazaHit103, fightTrainerAiWazaDamage103, fightTrainerAiWazaDamageFightPokemon103, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueSubayasaDaun, fightTrainerAiWazaHit060, fightTrainerAiWazaDamage060, fightTrainerAiWazaDamageFightPokemon060, fightWazaWzxTypeFuncAtt, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueHittyuu, fightTrainerAiWazaHit017, fightTrainerAiWazaDamage017, fightTrainerAiWazaDamageFightPokemon017, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueKonran, fightTrainerAiWazaHit049, fightTrainerAiWazaDamage049, fightTrainerAiWazaDamageFightPokemon049, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueHaradaiko, fightTrainerAiWazaHit142, fightTrainerAiWazaDamage142, fightTrainerAiWazaDamageFightPokemon142, fightWazaWzxTypeFuncAtt, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuikaDoku, fightTrainerAiWazaHit002, fightTrainerAiWazaDamage002, fightTrainerAiWazaDamageFightPokemon002, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueDorokake, fightTrainerAiWazaHit073, fightTrainerAiWazaDamage073, fightTrainerAiWazaDamageFightPokemon073, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuikouMeityuuDaun, fightTrainerAiWazaHit073, fightTrainerAiWazaDamage073, fightTrainerAiWazaDamageFightPokemon073, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueMakibisi, fightTrainerAiWazaHit112, fightTrainerAiWazaDamage112, fightTrainerAiWazaDamageFightPokemon112, fightWazaWzxTypeFuncAllEnemy, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueDenjihou, fightTrainerAiWazaHit006, fightTrainerAiWazaDamage006, fightTrainerAiWazaDamageFightPokemon006, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueMiyaburu, fightTrainerAiWazaHit113, fightTrainerAiWazaDamage113, fightTrainerAiWazaDamageFightPokemon113, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueMitizure, fightTrainerAiWazaHit098, fightTrainerAiWazaDamage098, fightTrainerAiWazaDamageFightPokemon098, fightWazaWzxTypeFuncSpc, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueToriaezutukae, fightTrainerAiWazaHit114, fightTrainerAiWazaDamage114, fightTrainerAiWazaDamageFightPokemon114, fightWazaWzxTypeFuncAttDef, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueKogoerukaze, fightTrainerAiWazaHit070, fightTrainerAiWazaDamage070, fightTrainerAiWazaDamageFightPokemon070, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueMamoru, fightTrainerAiWazaHit111, fightTrainerAiWazaDamage111, fightTrainerAiWazaDamageFightPokemon111, fightWazaWzxTypeFuncSpc, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit029, fightTrainerAiWazaDamage029, fightTrainerAiWazaDamageFightPokemon029, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueRokkuon, fightTrainerAiWazaHit094, fightTrainerAiWazaDamage094, fightTrainerAiWazaDamageFightPokemon094, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueAbareru, fightTrainerAiWazaHit027, fightTrainerAiWazaDamage027, fightTrainerAiWazaDamageFightPokemon027, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueSunaarasi, fightTrainerAiWazaHit115, fightTrainerAiWazaDamage115, fightTrainerAiWazaDamageFightPokemon115, fightWazaWzxTypeFuncAtt, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueKyuusyuu, fightTrainerAiWazaHit003, fightTrainerAiWazaDamage003, fightTrainerAiWazaDamageFightPokemon003, fightWazaWzxTypeFuncVampire, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueKoraeru, fightTrainerAiWazaHit116, fightTrainerAiWazaDamage116, fightTrainerAiWazaDamageFightPokemon116, fightWazaWzxTypeFuncSpc, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueKougekiDaun, fightTrainerAiWazaHit058, fightTrainerAiWazaDamage058, fightTrainerAiWazaDamageFightPokemon058, fightWazaWzxTypeFuncAtt, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueKorogaru, fightTrainerAiWazaHit117, fightTrainerAiWazaDamage117, fightTrainerAiWazaDamageFightPokemon117, fightWazaWzxTypeFuncNormal2, fightWazaWzxVariationFuncKorogaru},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit101, fightTrainerAiWazaDamage101, fightTrainerAiWazaDamageFightPokemon101, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueIbaru, fightTrainerAiWazaHit118, fightTrainerAiWazaDamage118, fightTrainerAiWazaDamageFightPokemon118, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueKaihuku2, fightTrainerAiWazaHit157, fightTrainerAiWazaDamage157, fightTrainerAiWazaDamageFightPokemon157, fightWazaWzxTypeFuncSpc, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuikaMahi, fightTrainerAiWazaHit006, fightTrainerAiWazaDamage006, fightTrainerAiWazaDamageFightPokemon006, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit119, fightTrainerAiWazaDamage119, fightTrainerAiWazaDamageFightPokemon119, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncRenzokugiri},
    {fightTrainerAiWazaValueHaganenotubasa, fightTrainerAiWazaHit138, fightTrainerAiWazaDamage138, fightTrainerAiWazaDamageFightPokemon138, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueKoukanKinsi, fightTrainerAiWazaHit106, fightTrainerAiWazaDamage106, fightTrainerAiWazaDamageFightPokemon106, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueMeromero, fightTrainerAiWazaHit120, fightTrainerAiWazaDamage120, fightTrainerAiWazaDamageFightPokemon120, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueNemuriKoudou, fightTrainerAiWazaHit097, fightTrainerAiWazaDamage097, fightTrainerAiWazaDamageFightPokemon097, fightWazaWzxTypeFuncAtt, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueAroma, fightTrainerAiWazaHit102, fightTrainerAiWazaDamage102, fightTrainerAiWazaDamageFightPokemon102, fightWazaWzxTypeFuncAllAlly, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit121, fightTrainerAiWazaDamage121, fightTrainerAiWazaDamageFightPokemon121, fightWazaWzxTypeFuncNormal2, fightWazaWzxVariationFuncOngaesi},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit122, fightTrainerAiWazaDamage122, fightTrainerAiWazaDamageFightPokemon122, fightWazaWzxTypeFuncNormal2, fightWazaWzxVariationFuncPresent},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit123, fightTrainerAiWazaDamage123, fightTrainerAiWazaDamageFightPokemon123, fightWazaWzxTypeFuncNormal2, fightWazaWzxVariationFuncYatuatari},
    {fightTrainerAiWazaValueToriaezutukae, fightTrainerAiWazaHit124, fightTrainerAiWazaDamage124, fightTrainerAiWazaDamageFightPokemon124, fightWazaWzxTypeFuncAllAlly, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueItamiwake, fightTrainerAiWazaHit091, fightTrainerAiWazaDamage091, fightTrainerAiWazaDamageFightPokemon091, fightWazaWzxTypeFuncItamiwake, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueJikokaitou, fightTrainerAiWazaHit125, fightTrainerAiWazaDamage125, fightTrainerAiWazaDamageFightPokemon125, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueJisin, fightTrainerAiWazaHit126, fightTrainerAiWazaDamage126, fightTrainerAiWazaDamageFightPokemon126, fightWazaWzxTypeFuncNormal2, fightWazaWzxVariationFuncMagnitude},
    {fightTrainerAiWazaValueBakuretuPanti, fightTrainerAiWazaHit076, fightTrainerAiWazaDamage076, fightTrainerAiWazaDamageFightPokemon076, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit000, fightTrainerAiWazaDamage000, fightTrainerAiWazaDamageFightPokemon000, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuikaMahi, fightTrainerAiWazaHit006, fightTrainerAiWazaDamage006, fightTrainerAiWazaDamageFightPokemon006, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueBatontatti, fightTrainerAiWazaHit127, fightTrainerAiWazaDamage127, fightTrainerAiWazaDamageFightPokemon127, fightWazaWzxTypeFuncSpc, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueAnkooru, fightTrainerAiWazaHit090, fightTrainerAiWazaDamage090, fightTrainerAiWazaDamageFightPokemon090, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueOiuti, fightTrainerAiWazaHit128, fightTrainerAiWazaDamage128, fightTrainerAiWazaDamageFightPokemon128, fightWazaWzxTypeFuncNormal2, fightWazaWzxVariationFuncOiuchi},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit129, fightTrainerAiWazaDamage129, fightTrainerAiWazaDamageFightPokemon129, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueKaihiDaun, fightTrainerAiWazaHit024, fightTrainerAiWazaDamage024, fightTrainerAiWazaDamageFightPokemon024, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuikouBougyoDaun, fightTrainerAiWazaHit069, fightTrainerAiWazaDamage069, fightTrainerAiWazaDamageFightPokemon069, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuikaKougekiAppu, fightTrainerAiWazaHit139, fightTrainerAiWazaDamage139, fightTrainerAiWazaDamageFightPokemon139, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueAteminage, fightTrainerAiWazaHit078, fightTrainerAiWazaDamage078, fightTrainerAiWazaDamageFightPokemon078, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueKaihuku1, fightTrainerAiWazaHit132, fightTrainerAiWazaDamage132, fightTrainerAiWazaDamageFightPokemon132, fightWazaWzxTypeFuncSpc, fightWazaWzxVariationFuncWeatherHP},
    {fightTrainerAiWazaValueKaihuku1, fightTrainerAiWazaHit133, fightTrainerAiWazaDamage133, fightTrainerAiWazaDamageFightPokemon133, fightWazaWzxTypeFuncSpc, fightWazaWzxVariationFuncWeatherHP},
    {fightTrainerAiWazaValueKaihuku1, fightTrainerAiWazaHit134, fightTrainerAiWazaDamage134, fightTrainerAiWazaDamageFightPokemon134, fightWazaWzxTypeFuncSpc, fightWazaWzxVariationFuncWeatherHP},
    {fightTrainerAiWazaValueTokubetuYuusen, fightTrainerAiWazaHit135, fightTrainerAiWazaDamage135, fightTrainerAiWazaDamageFightPokemon135, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValuePhyKuritikaru, fightTrainerAiWazaHit043, fightTrainerAiWazaDamage043, fightTrainerAiWazaDamageFightPokemon043, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuikaHirumi, fightTrainerAiWazaHit146, fightTrainerAiWazaDamage146, fightTrainerAiWazaDamageFightPokemon146, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueAmagoi, fightTrainerAiWazaHit136, fightTrainerAiWazaDamage136, fightTrainerAiWazaDamageFightPokemon136, fightWazaWzxTypeFuncAtt, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueNihonbare, fightTrainerAiWazaHit137, fightTrainerAiWazaDamage137, fightTrainerAiWazaDamageFightPokemon137, fightWazaWzxTypeFuncAtt, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuikouTokubouDaun, fightTrainerAiWazaHit072, fightTrainerAiWazaDamage072, fightTrainerAiWazaDamageFightPokemon072, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueMiraakooto, fightTrainerAiWazaHit144, fightTrainerAiWazaDamage144, fightTrainerAiWazaDamageFightPokemon144, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueJikoanji, fightTrainerAiWazaHit143, fightTrainerAiWazaDamage143, fightTrainerAiWazaDamageFightPokemon143, fightWazaWzxTypeFuncSpc, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueKouPuraioritii, fightTrainerAiWazaHit103, fightTrainerAiWazaDamage103, fightTrainerAiWazaDamageFightPokemon103, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueZennouryokuappu, fightTrainerAiWazaHit140, fightTrainerAiWazaDamage140, fightTrainerAiWazaDamageFightPokemon140, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuikouTokubouDaun, fightTrainerAiWazaHit072, fightTrainerAiWazaDamage072, fightTrainerAiWazaDamageFightPokemon072, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueToriaezutukae, fightTrainerAiWazaHit148, fightTrainerAiWazaDamage148, fightTrainerAiWazaDamageFightPokemon148, fightWazaWzxTypeFuncAtt, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuikouBougyoDaun, fightTrainerAiWazaHit069, fightTrainerAiWazaDamage069, fightTrainerAiWazaDamageFightPokemon069, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueSokubaku, fightTrainerAiWazaHit042, fightTrainerAiWazaDamage042, fightTrainerAiWazaDamageFightPokemon042, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit154, fightTrainerAiWazaDamage154, fightTrainerAiWazaDamageFightPokemon154, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueNekodamasi, fightTrainerAiWazaHit158, fightTrainerAiWazaDamage158, fightTrainerAiWazaDamageFightPokemon158, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueSawagu, fightTrainerAiWazaHit159, fightTrainerAiWazaDamage159, fightTrainerAiWazaDamageFightPokemon159, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTakuwaeru, fightTrainerAiWazaHit160, fightTrainerAiWazaDamage160, fightTrainerAiWazaDamageFightPokemon160, fightWazaWzxTypeFuncSpc, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit161, fightTrainerAiWazaDamage161, fightTrainerAiWazaDamageFightPokemon161, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncHakidasu},
    {fightTrainerAiWazaValueKaihuku2, fightTrainerAiWazaHit162, fightTrainerAiWazaDamage162, fightTrainerAiWazaDamageFightPokemon162, fightWazaWzxTypeFuncSpc, fightWazaWzxVariationFuncNomikomu},
    {fightTrainerAiWazaValueIryokuHonoo, fightTrainerAiWazaHit004, fightTrainerAiWazaDamage004, fightTrainerAiWazaDamageFightPokemon004, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueArare, fightTrainerAiWazaHit164, fightTrainerAiWazaDamage164, fightTrainerAiWazaDamageFightPokemon164, fightWazaWzxTypeFuncAtt, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueRandamuSentaku, fightTrainerAiWazaHit165, fightTrainerAiWazaDamage165, fightTrainerAiWazaDamageFightPokemon165, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueOdareru, fightTrainerAiWazaHit166, fightTrainerAiWazaDamage166, fightTrainerAiWazaDamageFightPokemon166, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueOnibi, fightTrainerAiWazaHit167, fightTrainerAiWazaDamage167, fightTrainerAiWazaDamageFightPokemon167, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueMitizure, fightTrainerAiWazaHit168, fightTrainerAiWazaDamage168, fightTrainerAiWazaDamageFightPokemon168, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit169, fightTrainerAiWazaDamage169, fightTrainerAiWazaDamageFightPokemon169, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueKiaipanti, fightTrainerAiWazaHit170, fightTrainerAiWazaDamage170, fightTrainerAiWazaDamageFightPokemon170, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueKituke, fightTrainerAiWazaHit171, fightTrainerAiWazaDamage171, fightTrainerAiWazaDamageFightPokemon171, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueKonoyubitomare, fightTrainerAiWazaHit172, fightTrainerAiWazaDamage172, fightTrainerAiWazaDamageFightPokemon172, fightWazaWzxTypeFuncSpc, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueSizennotikara, fightTrainerAiWazaHit173, fightTrainerAiWazaDamage173, fightTrainerAiWazaDamageFightPokemon173, fightWazaWzxTypeFuncNull, fightWazaWzxVariationFuncNull},
    {fightTrainerAiWazaValueJyuuden, fightTrainerAiWazaHit174, fightTrainerAiWazaDamage174, fightTrainerAiWazaDamageFightPokemon174, fightWazaWzxTypeFuncSpc, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueRandamuSentaku, fightTrainerAiWazaHit175, fightTrainerAiWazaDamage175, fightTrainerAiWazaDamageFightPokemon175, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTedasuke, fightTrainerAiWazaHit176, fightTrainerAiWazaDamage176, fightTrainerAiWazaDamageFightPokemon176, fightWazaWzxTypeFuncTedasuke, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValuetorikku, fightTrainerAiWazaHit177, fightTrainerAiWazaDamage177, fightTrainerAiWazaDamageFightPokemon177, fightWazaWzxTypeFuncAttDefSpc, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueRandamuSentaku, fightTrainerAiWazaHit178, fightTrainerAiWazaDamage178, fightTrainerAiWazaDamageFightPokemon178, fightWazaWzxTypeFuncAtt, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueToriaezutukae, fightTrainerAiWazaHit179, fightTrainerAiWazaDamage179, fightTrainerAiWazaDamageFightPokemon179, fightWazaWzxTypeFuncNegaigoto, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTokubetuYuusen, fightTrainerAiWazaHit180, fightTrainerAiWazaDamage180, fightTrainerAiWazaDamageFightPokemon180, fightWazaWzxTypeFuncSpc, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueToriaezutukae, fightTrainerAiWazaHit181, fightTrainerAiWazaDamage181, fightTrainerAiWazaDamageFightPokemon181, fightWazaWzxTypeFuncSpc, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueBakadikara, fightTrainerAiWazaHit182, fightTrainerAiWazaDamage182, fightTrainerAiWazaDamageFightPokemon182, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueMajikkukooto, fightTrainerAiWazaHit183, fightTrainerAiWazaDamage183, fightTrainerAiWazaDamageFightPokemon183, fightWazaWzxTypeFuncMagiccort, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueRisaikuru, fightTrainerAiWazaHit184, fightTrainerAiWazaDamage184, fightTrainerAiWazaDamageFightPokemon184, fightWazaWzxTypeFuncSpc, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueRibenji, fightTrainerAiWazaHit185, fightTrainerAiWazaDamage185, fightTrainerAiWazaDamageFightPokemon185, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueKawarawari, fightTrainerAiWazaHit186, fightTrainerAiWazaDamage186, fightTrainerAiWazaDamageFightPokemon186, fightWazaWzxTypeFuncKawarawari, fightWazaWzxVariationFuncKawarawari},
    {fightTrainerAiWazaValueNemurare, fightTrainerAiWazaHit187, fightTrainerAiWazaDamage187, fightTrainerAiWazaDamageFightPokemon187, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueHatakiotosu, fightTrainerAiWazaHit188, fightTrainerAiWazaDamage188, fightTrainerAiWazaDamageFightPokemon188, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueGamusyara, fightTrainerAiWazaHit189, fightTrainerAiWazaDamage189, fightTrainerAiWazaDamageFightPokemon189, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit190, fightTrainerAiWazaDamage190, fightTrainerAiWazaDamageFightPokemon190, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueSukirusuwappu, fightTrainerAiWazaHit191, fightTrainerAiWazaDamage191, fightTrainerAiWazaDamageFightPokemon191, fightWazaWzxTypeFuncAttDefSpc, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueHuuin, fightTrainerAiWazaHit192, fightTrainerAiWazaDamage192, fightTrainerAiWazaDamageFightPokemon192, fightWazaWzxTypeFuncHuuin, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueRihuressyu, fightTrainerAiWazaHit193, fightTrainerAiWazaDamage193, fightTrainerAiWazaDamageFightPokemon193, fightWazaWzxTypeFuncSpc, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueMitizure, fightTrainerAiWazaHit194, fightTrainerAiWazaDamage194, fightTrainerAiWazaDamageFightPokemon194, fightWazaWzxTypeFuncAtt, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueYokodori, fightTrainerAiWazaHit195, fightTrainerAiWazaDamage195, fightTrainerAiWazaDamageFightPokemon195, fightWazaWzxTypeFuncSpc, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueHimitunotikara, fightTrainerAiWazaHit197, fightTrainerAiWazaDamage197, fightTrainerAiWazaDamageFightPokemon197, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueSorawotobu, fightTrainerAiWazaHit155, fightTrainerAiWazaDamage155, fightTrainerAiWazaDamageFightPokemon155, fightWazaWzxTypeFuncTame, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit029, fightTrainerAiWazaDamage029, fightTrainerAiWazaDamageFightPokemon029, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueRandamuSentaku, fightTrainerAiWazaHit213, fightTrainerAiWazaDamage213, fightTrainerAiWazaDamageFightPokemon213, fightWazaWzxTypeFuncSpc, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTokukouAppu, fightTrainerAiWazaHit053, fightTrainerAiWazaDamage053, fightTrainerAiWazaDamageFightPokemon053, fightWazaWzxTypeFuncSpc, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuikouTokubouDaun, fightTrainerAiWazaHit072, fightTrainerAiWazaDamage072, fightTrainerAiWazaDamageFightPokemon072, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuikouTokukouDaun, fightTrainerAiWazaHit071, fightTrainerAiWazaDamage071, fightTrainerAiWazaDamageFightPokemon071, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueKougekiDaun, fightTrainerAiWazaHit058, fightTrainerAiWazaDamage058, fightTrainerAiWazaDamageFightPokemon058, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueHurahuradansu, fightTrainerAiWazaHit199, fightTrainerAiWazaDamage199, fightTrainerAiWazaDamageFightPokemon199, fightWazaWzxTypeFuncAtt, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueBureizukikku, fightTrainerAiWazaHit200, fightTrainerAiWazaDamage200, fightTrainerAiWazaDamageFightPokemon200, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueToriaezutukae, fightTrainerAiWazaHit201, fightTrainerAiWazaDamage201, fightTrainerAiWazaDamageFightPokemon201, fightWazaWzxTypeFuncSpc, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueKorogaru, fightTrainerAiWazaHit117, fightTrainerAiWazaDamage117, fightTrainerAiWazaDamageFightPokemon117, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncIceball},
    {fightTrainerAiWazaValueTuikaHirumi, fightTrainerAiWazaHit150, fightTrainerAiWazaDamage150, fightTrainerAiWazaDamageFightPokemon150, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueKaihuku2, fightTrainerAiWazaHit032, fightTrainerAiWazaDamage032, fightTrainerAiWazaDamageFightPokemon032, fightWazaWzxTypeFuncSpc, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit000, fightTrainerAiWazaDamage000, fightTrainerAiWazaDamageFightPokemon000, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueDokudokunokiba, fightTrainerAiWazaHit202, fightTrainerAiWazaDamage202, fightTrainerAiWazaDamageFightPokemon202, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuikouBougyoDaun, fightTrainerAiWazaHit069, fightTrainerAiWazaDamage069, fightTrainerAiWazaDamageFightPokemon069, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueHandou, fightTrainerAiWazaHit080, fightTrainerAiWazaDamage080, fightTrainerAiWazaDamageFightPokemon080, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueHandou, fightTrainerAiWazaHit080, fightTrainerAiWazaDamage080, fightTrainerAiWazaDamageFightPokemon080, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuikaKougekiAppu, fightTrainerAiWazaHit139, fightTrainerAiWazaDamage139, fightTrainerAiWazaDamageFightPokemon139, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuikaHirumi, fightTrainerAiWazaHit150, fightTrainerAiWazaDamage150, fightTrainerAiWazaDamageFightPokemon150, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueUezaabooru, fightTrainerAiWazaHit203, fightTrainerAiWazaDamage203, fightTrainerAiWazaDamageFightPokemon203, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncWeatherBall},
    {fightTrainerAiWazaValueAroma, fightTrainerAiWazaHit102, fightTrainerAiWazaDamage102, fightTrainerAiWazaDamageFightPokemon102, fightWazaWzxTypeFuncAllAlly, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTokubouDaun, fightTrainerAiWazaHit062, fightTrainerAiWazaDamage062, fightTrainerAiWazaDamageFightPokemon062, fightWazaWzxTypeFuncAtt, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValuePhyKuritikaru, fightTrainerAiWazaHit043, fightTrainerAiWazaDamage043, fightTrainerAiWazaDamageFightPokemon043, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueOobaahiito, fightTrainerAiWazaHit204, fightTrainerAiWazaDamage204, fightTrainerAiWazaDamageFightPokemon204, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueMiyaburu, fightTrainerAiWazaHit113, fightTrainerAiWazaDamage113, fightTrainerAiWazaDamageFightPokemon113, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueKanarazuSubayasaDaun, fightTrainerAiWazaHit070, fightTrainerAiWazaDamage070, fightTrainerAiWazaDamageFightPokemon070, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueZennouryokuappu, fightTrainerAiWazaHit140, fightTrainerAiWazaDamage140, fightTrainerAiWazaDamageFightPokemon140, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTokubouDaun, fightTrainerAiWazaHit062, fightTrainerAiWazaDamage062, fightTrainerAiWazaDamageFightPokemon062, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueNemurare, fightTrainerAiWazaHit001, fightTrainerAiWazaDamage001, fightTrainerAiWazaDamageFightPokemon001, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueKusuguruDaun, fightTrainerAiWazaHit205, fightTrainerAiWazaDamage205, fightTrainerAiWazaDamageFightPokemon205, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueKosumopawaa, fightTrainerAiWazaHit206, fightTrainerAiWazaDamage206, fightTrainerAiWazaDamageFightPokemon206, fightWazaWzxTypeFuncAtt, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit190, fightTrainerAiWazaDamage190, fightTrainerAiWazaDamageFightPokemon190, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuikouKonran, fightTrainerAiWazaHit076, fightTrainerAiWazaDamage076, fightTrainerAiWazaDamageFightPokemon076, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueHittyuu, fightTrainerAiWazaHit017, fightTrainerAiWazaDamage017, fightTrainerAiWazaDamageFightPokemon017, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuikaHirumi, fightTrainerAiWazaHit150, fightTrainerAiWazaDamage150, fightTrainerAiWazaDamageFightPokemon150, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit207, fightTrainerAiWazaDamage207, fightTrainerAiWazaDamageFightPokemon207, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueSokubaku, fightTrainerAiWazaHit042, fightTrainerAiWazaDamage042, fightTrainerAiWazaDamageFightPokemon042, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueItigekihissatu, fightTrainerAiWazaHit038, fightTrainerAiWazaDamage038, fightTrainerAiWazaDamageFightPokemon038, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuikouMeityuuDaun, fightTrainerAiWazaHit073, fightTrainerAiWazaDamage073, fightTrainerAiWazaDamageFightPokemon073, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit029, fightTrainerAiWazaDamage029, fightTrainerAiWazaDamageFightPokemon029, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueHittyuu, fightTrainerAiWazaHit017, fightTrainerAiWazaDamage017, fightTrainerAiWazaDamageFightPokemon017, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit029, fightTrainerAiWazaDamage029, fightTrainerAiWazaDamageFightPokemon029, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueBougyoAppu, fightTrainerAiWazaHit051, fightTrainerAiWazaDamage051, fightTrainerAiWazaDamageFightPokemon051, fightWazaWzxTypeFuncSpc, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueKoukanKinsi, fightTrainerAiWazaHit106, fightTrainerAiWazaDamage106, fightTrainerAiWazaDamageFightPokemon106, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueKougekiAppu, fightTrainerAiWazaHit010, fightTrainerAiWazaDamage010, fightTrainerAiWazaDamageFightPokemon010, fightWazaWzxTypeFuncSpc, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit000, fightTrainerAiWazaDamage000, fightTrainerAiWazaDamageFightPokemon000, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueHandou, fightTrainerAiWazaHit080, fightTrainerAiWazaDamage080, fightTrainerAiWazaDamageFightPokemon080, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueBirudoAppu, fightTrainerAiWazaHit208, fightTrainerAiWazaDamage208, fightTrainerAiWazaDamageFightPokemon208, fightWazaWzxTypeFuncSpc, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTobihaneru, fightTrainerAiWazaHit155, fightTrainerAiWazaDamage155, fightTrainerAiWazaDamageFightPokemon155, fightWazaWzxTypeFuncTame, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueKanarazuSubayasaDaun, fightTrainerAiWazaHit070, fightTrainerAiWazaDamage070, fightTrainerAiWazaDamageFightPokemon070, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValuePoizunteeru, fightTrainerAiWazaHit209, fightTrainerAiWazaDamage209, fightTrainerAiWazaDamageFightPokemon209, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueDouguUbau, fightTrainerAiWazaHit105, fightTrainerAiWazaDamage105, fightTrainerAiWazaDamageFightPokemon105, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit198, fightTrainerAiWazaDamage198, fightTrainerAiWazaDamageFightPokemon198, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueHittyuu, fightTrainerAiWazaHit017, fightTrainerAiWazaDamage017, fightTrainerAiWazaDamageFightPokemon017, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueToriaezutukae, fightTrainerAiWazaHit210, fightTrainerAiWazaDamage210, fightTrainerAiWazaDamageFightPokemon210, fightWazaWzxTypeFuncAtt, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueMeisou, fightTrainerAiWazaHit211, fightTrainerAiWazaDamage211, fightTrainerAiWazaDamageFightPokemon211, fightWazaWzxTypeFuncSpc, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueSpeKuritikaru, fightTrainerAiWazaHit043, fightTrainerAiWazaDamage043, fightTrainerAiWazaDamageFightPokemon043, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueRyuunomai, fightTrainerAiWazaHit212, fightTrainerAiWazaDamage212, fightTrainerAiWazaDamageFightPokemon212, fightWazaWzxTypeFuncSpc, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit029, fightTrainerAiWazaDamage029, fightTrainerAiWazaDamageFightPokemon029, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueHittyuu, fightTrainerAiWazaHit017, fightTrainerAiWazaDamage017, fightTrainerAiWazaDamageFightPokemon017, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuikouKonran, fightTrainerAiWazaHit076, fightTrainerAiWazaDamage076, fightTrainerAiWazaDamageFightPokemon076, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueToriaezutukae, fightTrainerAiWazaHit148, fightTrainerAiWazaDamage148, fightTrainerAiWazaDamageFightPokemon148, fightWazaWzxTypeFuncAtt, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueSaikobuusuto, fightTrainerAiWazaHit204, fightTrainerAiWazaDamage204, fightTrainerAiWazaDamageFightPokemon204, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueNull, fightTrainerAiWazaHitNull, fightTrainerAiWazaDamageNull, fightTrainerAiWazaDamageFightPokemonNull, fightWazaWzxTypeFuncNull, fightWazaWzxVariationFuncNull},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit000, fightTrainerAiWazaDamage000, fightTrainerAiWazaDamageFightPokemon000, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit000, fightTrainerAiWazaDamage000, fightTrainerAiWazaDamageFightPokemon000, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit000, fightTrainerAiWazaDamage000, fightTrainerAiWazaDamageFightPokemon000, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueDarkEnd, fightTrainerAiWazaHit048, fightTrainerAiWazaDamage048, fightTrainerAiWazaDamageFightPokemon048, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit000, fightTrainerAiWazaDamage000, fightTrainerAiWazaDamageFightPokemon000, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit000, fightTrainerAiWazaDamage000, fightTrainerAiWazaDamageFightPokemon000, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit000, fightTrainerAiWazaDamage000, fightTrainerAiWazaDamageFightPokemon000, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueIryokuHonoo, fightTrainerAiWazaHit004, fightTrainerAiWazaDamage004, fightTrainerAiWazaDamageFightPokemon004, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuikaMahi, fightTrainerAiWazaHit006, fightTrainerAiWazaDamage006, fightTrainerAiWazaDamageFightPokemon006, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuikaKoori, fightTrainerAiWazaHit005, fightTrainerAiWazaDamage005, fightTrainerAiWazaDamageFightPokemon005, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueTuujouIryoku, fightTrainerAiWazaHit000, fightTrainerAiWazaDamage000, fightTrainerAiWazaDamageFightPokemon000, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueDarkWeather, fightTrainerAiWazaHit215, fightTrainerAiWazaDamage215, fightTrainerAiWazaDamageFightPokemon215, fightWazaWzxTypeFuncAtt, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueDarkHold, fightTrainerAiWazaHit106, fightTrainerAiWazaDamage106, fightTrainerAiWazaDamageFightPokemon106, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueDarkMist, fightTrainerAiWazaHit214, fightTrainerAiWazaDamage214, fightTrainerAiWazaDamageFightPokemon214, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueDarkPanic, fightTrainerAiWazaHit049, fightTrainerAiWazaDamage049, fightTrainerAiWazaDamageFightPokemon049, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueBougyoDaun, fightTrainerAiWazaHit059, fightTrainerAiWazaDamage059, fightTrainerAiWazaDamageFightPokemon059, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueDarkRemove, fightTrainerAiWazaHit216, fightTrainerAiWazaDamage216, fightTrainerAiWazaDamageFightPokemon216, fightWazaWzxTypeFuncAllEnemy, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueDarkHalf, fightTrainerAiWazaHit217, fightTrainerAiWazaDamage217, fightTrainerAiWazaDamageFightPokemon217, fightWazaWzxTypeFuncNormal, fightWazaWzxVariationFuncNormal},
    {fightTrainerAiWazaValueNull, fightTrainerAiWazaHitNull, fightTrainerAiWazaDamageNull, fightTrainerAiWazaDamageFightPokemonNull, fightWazaWzxTypeFuncNull, fightWazaWzxVariationFuncNull},
};

u32 waza_func_data_number = sizeof(waza_func_data) / sizeof(waza_func_data[0]);
