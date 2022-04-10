#include "StdAfx.h"
#ifdef ENABLE_CPP_PSM
#include "PythonPlayerSettingsModule.h"
#include "InstanceBase.h"
#include "../EffectLib/EffectManager.h"
#include "PythonSkill.h"
#include "../gamelib/RaceManager.h"
#include "PythonItem.h"
#include "PythonPlayer.h"
#include "PythonNetworkStream.h"

CRaceMotionData& pkMotionManager = CRaceMotionData();
static const DWORD GUILD_SKILL_DRAGONBLOOD = pkMotionManager.NAME_SKILL + 101;
static const DWORD GUILD_SKILL_DRAGONBLESS = pkMotionManager.NAME_SKILL + 102;
static const DWORD GUILD_SKILL_BLESSARMOR = pkMotionManager.NAME_SKILL + 103;
static const DWORD GUILD_SKILL_SPPEDUP = pkMotionManager.NAME_SKILL + 104;
static const DWORD GUILD_SKILL_DRAGONWRATH = pkMotionManager.NAME_SKILL + 105;
static const DWORD GUILD_SKILL_MAGICUP = pkMotionManager.NAME_SKILL + 106;

static const DWORD HORSE_SKILL_WILDATTACK = pkMotionManager.NAME_SKILL + 121;
static const DWORD HORSE_SKILL_CHARGE = pkMotionManager.NAME_SKILL + 122;
static const DWORD HORSE_SKILL_SPLASH = pkMotionManager.NAME_SKILL + 123;

const bool CPlayerSettingsModule::LoadInitData()
{
	CInstanceBase & pkBase = CInstanceBase();
	CRaceManager& pkManager = CRaceManager::Instance();
	CPythonPlayer& pkPlayer = CPythonPlayer::Instance();

	static const std::vector<TEffect> m_vecEffectData =
	{
		{ pkBase.EFFECT_DUST, "", "d:/ymir work/effect/etc/dust/dust.mse" } ,
		{ pkBase.EFFECT_HORSE_DUST, "", "d:/ymir work/effect/etc/dust/running_dust.mse" },
		{ pkBase.EFFECT_HIT, "", "d:/ymir work/effect/hit/blow_1/blow_1_low.mse" },

		{ pkBase.EFFECT_HPUP_RED, "", "d:/ymir work/effect/etc/recuperation/drugup_red.mse" },
		{ pkBase.EFFECT_SPUP_BLUE, "", "d:/ymir work/effect/etc/recuperation/drugup_blue.mse" },
		{ pkBase.EFFECT_SPEEDUP_GREEN, "", "d:/ymir work/effect/etc/recuperation/drugup_green.mse" },
		{ pkBase.EFFECT_DXUP_PURPLE, "", "d:/ymir work/effect/etc/recuperation/drugup_purple.mse" },

		{ pkBase.EFFECT_AUTO_HPUP, "", "d:/ymir work/effect/etc/recuperation/autodrugup_red.mse" },
		{ pkBase.EFFECT_AUTO_SPUP, "", "d:/ymir work/effect/etc/recuperation/autodrugup_blue.mse" },

		{ pkBase.EFFECT_RAMADAN_RING_EQUIP, "", "d:/ymir work/effect/etc/buff/buff_item1.mse" },

		{ pkBase.EFFECT_HALLOWEEN_CANDY_EQUIP, "", "d:/ymir work/effect/etc/buff/buff_item2.mse" },

		{ pkBase.EFFECT_HAPPINESS_RING_EQUIP, "", "d:/ymir work/effect/etc/buff/buff_item3.mse" },

		{ pkBase.EFFECT_LOVE_PENDANT_EQUIP, "", "d:/ymir work/effect/etc/buff/buff_item4.mse" },

#ifdef ENABLE_ACCE_SYSTEM
		{ pkBase.EFFECT_ACCE_SUCCEDED, "", "d:/ymir work/effect/etc/buff/buff_item6.mse" },
		{ pkBase.EFFECT_ACCE_EQUIP, "", "d:/ymir work/effect/etc/buff/buff_item7.mse" },
#endif

		{ pkBase.EFFECT_PENETRATE, "Bip01", "d:/ymir work/effect/hit/gwantong.mse" },
		//chrmgr.RegisterCacheEffect(chrmgr.EFFECT_BLOCK, {"", "d:/ymir work/effect/etc/" },
		//chrmgr.RegisterCacheEffect(chrmgr.EFFECT_DODGE, {"", "d:/ymir work/effect/etc/" },
		{ pkBase.EFFECT_FIRECRACKER, "", "d:/ymir work/effect/etc/firecracker/newyear_firecracker.mse" },
		{ pkBase.EFFECT_SPIN_TOP, "", "d:/ymir work/effect/etc/firecracker/paing_i.mse" },
		{ pkBase.EFFECT_SELECT, "", "d:/ymir work/effect/etc/click/click_select.mse" },
		{ pkBase.EFFECT_TARGET, "", "d:/ymir work/effect/etc/click/click_glow_select.mse" },
		{ pkBase.EFFECT_STUN, "Bip01 Head", "d:/ymir work/effect/etc/stun/stun.mse" },
		{ pkBase.EFFECT_CRITICAL, "Bip01 R Hand", "d:/ymir work/effect/hit/critical.mse" },


		{ pkBase.EFFECT_DAMAGE_TARGET, "", "d:/ymir work/effect/affect/damagevalue/target.mse" },
		{ pkBase.EFFECT_DAMAGE_NOT_TARGET, "", "d:/ymir work/effect/affect/damagevalue/nontarget.mse" },
		{ pkBase.EFFECT_DAMAGE_SELFDAMAGE, "", "d:/ymir work/effect/affect/damagevalue/damage.mse" },
		{ pkBase.EFFECT_DAMAGE_SELFDAMAGE2, "", "d:/ymir work/effect/affect/damagevalue/damage_1.mse" },
		{ pkBase.EFFECT_DAMAGE_POISON, "", "d:/ymir work/effect/affect/damagevalue/poison.mse" },
		{ pkBase.EFFECT_DAMAGE_MISS, "", "d:/ymir work/effect/affect/damagevalue/miss.mse" },
		{ pkBase.EFFECT_DAMAGE_TARGETMISS, "", "d:/ymir work/effect/affect/damagevalue/target_miss.mse" },
		//chrmgr.RegisterCacheEffect(chrmgr.EFFECT_DAMAGE_CRITICAL, "", "d:/ymir work/effect/affect/damagevalue/critical.mse" },

		//chrmgr.RegisterCacheEffect(chrmgr.EFFECT_SUCCESS, "",			"season1/effect/success.mse" },
		//chrmgr.RegisterCacheEffect(chrmgr.EFFECT_FAIL, "",	"season1/effect/fail.mse" },

		{ pkBase.EFFECT_LEVELUP_ON_14_FOR_GERMANY, "","season1/effect/paymessage_warning.mse" },
		{ pkBase.EFFECT_LEVELUP_UNDER_15_FOR_GERMANY, "", "season1/effect/paymessage_decide.mse"  },

		{ pkBase.EFFECT_PERCENT_DAMAGE1, "", "d:/ymir work/effect/hit/percent_damage1.mse" },
		{ pkBase.EFFECT_PERCENT_DAMAGE2, "", "d:/ymir work/effect/hit/percent_damage2.mse" },
		{ pkBase.EFFECT_PERCENT_DAMAGE3, "", "d:/ymir work/effect/hit/percent_damage3.mse" },

#ifdef ENABLE_SPHAERA_SYSTEM:
		{ pkBase.EFFECT_SPHAERA_ACTIVATE, "", "d:/ymir work/effect/etc/sphaera/sphaera_sky.mse" },
#endif
	};

	static std::vector<TRaceData> m_vecRaceData =
	{
		{ RACE_WARRIOR_M, "warrior_m.msm", "d:/ymir work/pc/warrior/intro/" },
		{ RACE_WARRIOR_W, "warrior_w.msm", "d:/ymir work/pc2/warrior/intro/" },		
		
		{ RACE_ASSASSIN_W, "assassin_w.msm", "d:/ymir work/pc/assassin/intro/" },
		{ RACE_ASSASSIN_M, "assassin_m.msm", "d:/ymir work/pc2/assassin/intro/" },
		
		{ RACE_SURA_M, "sura_m.msm", "d:/ymir work/pc/sura/intro/" },
		{ RACE_SURA_W, "sura_w.msm", "d:/ymir work/pc2/sura/intro/" },
		
		{ RACE_SHAMAN_W, "shaman_w.msm", "d:/ymir work/pc/shaman/intro/" },
		{ RACE_SHAMAN_M, "shaman_m.msm", "d:/ymir work/pc2/shaman/intro/" },
	};

	
	std::vector<SMotion> m_vecMotion =
	{
		{ pkMotionManager.NAME_INTRO_WAIT, "wait.msa", 0 },
		{ pkMotionManager.NAME_INTRO_SELECTED, "selected.msa", 0 },
		{ pkMotionManager.NAME_INTRO_NOT_SELECTED, "not_selected.msa", 0 },
	};

	pkBase.SetDustGap(DUST_GAP);
	pkBase.SetHorseDustGap(HORSE_DUST_GAP);

	for (const auto& it : m_vecEffectData)
	{
		pkBase.RegisterEffect(it.uiType, it.stBone, it.stEffect, true);
	}

	char szFileName[FILE_MAX_NUM];
	for (auto& it : m_vecRaceData)
	{	
		pkManager.CreateRace(it.dwRace);
		pkManager.SelectRace(it.dwRace);

		CRaceData* pRaceData = pkManager.GetSelectedRaceDataPointer();
		if (!pRaceData)
			return false;

		if (!pRaceData->LoadRaceData(it.stMSM))
		{
			return false;
		}
		
		pRaceData->RegisterMotionMode(pkMotionManager.MODE_GENERAL);
		for (const auto& it2 : m_vecMotion)
		{
			snprintf(szFileName, sizeof(szFileName), "%s%s", it.stIntroMotion, it2.stName);
			pRaceData->RegisterMotionData(pkMotionManager.MODE_GENERAL, it2.wMotionIndex, szFileName, it2.byPercentage);
		}
	}

	pkPlayer.RegisterEffect(pkPlayer.EFFECT_PICK, "d:/ymir work/effect/etc/click/click.mse", true);

	return true;
}

const bool CPlayerSettingsModule::LoadGameEffect()
{
	CInstanceBase& pkBase = CInstanceBase();
	CFlyingManager& pkFly = CFlyingManager::Instance();
	CPythonNetworkStream& pkNetworkStream = CPythonNetworkStream::Instance();

	char GM_MARK[FILE_MAX_NUM];
	snprintf(GM_MARK, sizeof(GM_MARK), "%s/effect/gm.mse", LocaleService_GetLocalePath());

	std::vector<TEffect> m_vecEffectData =
	{
		{ pkBase.EFFECT_SPAWN_APPEAR, "Bip01", "d:/ymir work/effect/etc/appear_die/monster_appear.mse" },
		{ pkBase.EFFECT_SPAWN_DISAPPEAR, "Bip01", "d:/ymir work/effect/etc/appear_die/monster_die.mse" },
		{ pkBase.EFFECT_FLAME_ATTACK, "equip_right_hand", "d:/ymir work/effect/hit/blow_flame/flame_3_weapon.mse" },
		{ pkBase.EFFECT_FLAME_HIT, "", "d:/ymir work/effect/hit/blow_flame/flame_3_blow.mse" },
		{ pkBase.EFFECT_FLAME_ATTACH, "", "d:/ymir work/effect/hit/blow_flame/flame_3_body.mse" },
		{ pkBase.EFFECT_ELECTRIC_ATTACK, "equip_right", "d:/ymir work/effect/hit/blow_electric/light_1_weapon.mse" },
		{ pkBase.EFFECT_ELECTRIC_HIT, "", "d:/ymir work/effect/hit/blow_electric/light_1_blow.mse" },
		{ pkBase.EFFECT_ELECTRIC_ATTACH, "", "d:/ymir work/effect/hit/blow_electric/light_1_body.mse" },
		{ pkBase.EFFECT_GYEONGGONG_BOOM, "Bip01", "d:/ymir work/effect/hit/gyeonggong_boom.mse" },

		{ pkBase.EFFECT_LEVELUP, "", "d:/ymir work/effect/etc/levelup_1/level_up.mse" },
		{ pkBase.EFFECT_SKILLUP, "", "d:/ymir work/effect/etc/skillup/skillup_1.mse" },

		{ pkBase.EFFECT_EMPIRE + 1, "Bip01", "d:/ymir work/effect/etc/empire/empire_A.mse" },
		{ pkBase.EFFECT_EMPIRE + 2, "Bip01", "d:/ymir work/effect/etc/empire/empire_B.mse" },
		{ pkBase.EFFECT_EMPIRE + 3, "Bip01", "d:/ymir work/effect/etc/empire/empire_C.mse" },

		{ pkBase.EFFECT_WEAPON + 1, "equip_right_hand", "d:/ymir work/pc/warrior/effect/geom_sword_loop.mse" },
		{ pkBase.EFFECT_WEAPON + 2, "equip_right_hand", "d:/ymir work/pc/warrior/effect/geom_spear_loop.mse" },

		{ pkBase.EFFECT_AFFECT + 3, "Bip01", "d:/ymir work/effect/hit/blow_poison/poison_loop.mse" },
		{ pkBase.EFFECT_AFFECT + 4, "", "d:/ymir work/effect/affect/slow.mse" },
		{ pkBase.EFFECT_AFFECT + 5, "Bip01 Head", "d:/ymir work/effect/etc/stun/stun_loop.mse" },
		{ pkBase.EFFECT_AFFECT + 6, "", "d:/ymir work/effect/etc/ready/ready.mse" },
		//{ pkBase.EFFECT_AFFECT+8, "", "d:/ymir work/guild/effect/10_construction.mse" },
		//{ pkBase.EFFECT_AFFECT+9, "", "d:/ymir work/guild/effect/20_construction.mse" },
		//{ pkBase.EFFECT_AFFECT+10, "", "d:/ymir work/guild/effect/20_upgrade.mse" },
		{ pkBase.EFFECT_AFFECT + 16, "", "d:/ymir work/pc/warrior/effect/gyeokgongjang_loop.mse" },
		{ pkBase.EFFECT_AFFECT + 17, "", "d:/ymir work/pc/assassin/effect/gyeonggong_loop.mse" },
		{ pkBase.EFFECT_AFFECT + 19, "Bip01 R Finger2", "d:/ymir work/pc/sura/effect/gwigeom_loop.mse" },
		{ pkBase.EFFECT_AFFECT + 20, "", "d:/ymir work/pc/sura/effect/fear_loop.mse" },
		{ pkBase.EFFECT_AFFECT + 21, "", "d:/ymir work/pc/sura/effect/jumagap_loop.mse" },
		{ pkBase.EFFECT_AFFECT + 22, "", "d:/ymir work/pc/shaman/effect/3hosin_loop.mse" },
		{ pkBase.EFFECT_AFFECT + 23, "", "d:/ymir work/pc/shaman/effect/boho_loop.mse" },
		{ pkBase.EFFECT_AFFECT + 24, "", "d:/ymir work/pc/shaman/effect/10kwaesok_loop.mse" },
		{ pkBase.EFFECT_AFFECT + 25, "", "d:/ymir work/pc/sura/effect/heuksin_loop.mse" },
		{ pkBase.EFFECT_AFFECT + 26, "", "d:/ymir work/pc/sura/effect/muyeong_loop.mse" },
		{ pkBase.EFFECT_AFFECT + 28, "Bip01", "d:/ymir work/effect/hit/blow_flame/flame_loop.mse" },
		{ pkBase.EFFECT_AFFECT + 29, "Bip01 R Hand", "d:/ymir work/pc/shaman/effect/6gicheon_hand.mse" },
		{ pkBase.EFFECT_AFFECT + 30, "Bip01 L Hand", "d:/ymir work/pc/shaman/effect/jeungryeok_hand.mse" },
		{ pkBase.EFFECT_AFFECT + 32, "Bip01 Head", "d:/ymir work/pc/sura/effect/pabeop_loop.mse" },
		{ pkBase.EFFECT_AFFECT + 33, "", "d:/ymir work/pc/warrior/effect/gyeokgongjang_loop.mse" },

		{ pkBase.EFFECT_AFFECT + 35, "", "d:/ymir work/effect/etc/guild_war_flag/flag_red.mse" },
		{ pkBase.EFFECT_AFFECT + 36, "", "d:/ymir work/effect/etc/guild_war_flag/flag_blue.mse" },
		{ pkBase.EFFECT_AFFECT + 37, "", "d:/ymir work/effect/etc/guild_war_flag/flag_yellow.mse" },

		{ pkBase.EFFECT_REFINED + 1, "PART_WEAPON", "D:/ymir work/pc/common/effect/sword/sword_7.mse" },
		{ pkBase.EFFECT_REFINED + 2, "PART_WEAPON", "D:/ymir work/pc/common/effect/sword/sword_8.mse" },
		{ pkBase.EFFECT_REFINED + 3, "PART_WEAPON", "D:/ymir work/pc/common/effect/sword/sword_9.mse" },

		{ pkBase.EFFECT_REFINED + 4, "PART_WEAPON_LEFT", "D:/ymir work/pc/common/effect/sword/sword_7_b.mse" },
		{ pkBase.EFFECT_REFINED + 5, "PART_WEAPON_LEFT", "D:/ymir work/pc/common/effect/sword/sword_8_b.mse" },
		{ pkBase.EFFECT_REFINED + 6, "PART_WEAPON_LEFT", "D:/ymir work/pc/common/effect/sword/sword_9_b.mse" },

		{ pkBase.EFFECT_REFINED + 7, "PART_WEAPON", "D:/ymir work/pc/common/effect/sword/sword_7_f.mse" },
		{ pkBase.EFFECT_REFINED + 8, "PART_WEAPON", "D:/ymir work/pc/common/effect/sword/sword_8_f.mse" },
		{ pkBase.EFFECT_REFINED + 9, "PART_WEAPON", "D:/ymir work/pc/common/effect/sword/sword_9_f.mse" },

		{ pkBase.EFFECT_REFINED + 10, "PART_WEAPON", "D:/ymir work/pc/common/effect/sword/sword_7_s.mse" },
		{ pkBase.EFFECT_REFINED + 11, "PART_WEAPON", "D:/ymir work/pc/common/effect/sword/sword_8_s.mse" },
		{ pkBase.EFFECT_REFINED + 12, "PART_WEAPON", "D:/ymir work/pc/common/effect/sword/sword_9_s.mse" },

		{ pkBase.EFFECT_REFINED + 13, "PART_WEAPON_LEFT", "D:/ymir work/pc/common/effect/sword/sword_7_s.mse" },
		{ pkBase.EFFECT_REFINED + 14, "PART_WEAPON_LEFT", "D:/ymir work/pc/common/effect/sword/sword_8_s.mse" },
		{ pkBase.EFFECT_REFINED + 15, "PART_WEAPON_LEFT", "D:/ymir work/pc/common/effect/sword/sword_9_s.mse" },

		{ pkBase.EFFECT_REFINED + 16, "Bip01", "D:/ymir work/pc/common/effect/armor/armor_7.mse" },
		{ pkBase.EFFECT_REFINED + 17, "Bip01", "D:/ymir work/pc/common/effect/armor/armor_8.mse" },
		{ pkBase.EFFECT_REFINED + 18, "Bip01", "D:/ymir work/pc/common/effect/armor/armor_9.mse" },

		{ pkBase.EFFECT_REFINED + 19, "Bip01", "D:/ymir work/pc/common/effect/armor/armor-4-2-1.mse" },
		{ pkBase.EFFECT_REFINED + 20, "Bip01", "D:/ymir work/pc/common/effect/armor/armor-4-2-2.mse" },		
		
		{ pkBase.EFFECT_REFINED + 21, "Bip01", "D:/ymir work/pc/common/effect/armor/armor-5-1.mse" },
		{ pkBase.EFFECT_REFINED + 22, "Bip01", "D:/ymir work/pc/common/effect/armor/armor_7th_01.mse" },



#ifdef ENABLE_ACCE_SYSTEM
		{ pkBase.EFFECT_REFINED + 23, "Bip01", "d:/ymir work/pc/common/effect/armor/acc_01.mse" },
#endif
		{ pkBase.EFFECT_EMOTICON + 0, "", "d:/ymir work/effect/etc/emoticon/sweat.mse" },
		{ pkBase.EFFECT_EMOTICON + 1, "", "d:/ymir work/effect/etc/emoticon/money.mse" },
		{ pkBase.EFFECT_EMOTICON + 2, "", "d:/ymir work/effect/etc/emoticon/happy.mse" },
		{ pkBase.EFFECT_EMOTICON + 3, "", "d:/ymir work/effect/etc/emoticon/love_s.mse" },		
		{ pkBase.EFFECT_EMOTICON + 4, "", "d:/ymir work/effect/etc/emoticon/love_l.mse" },
		{ pkBase.EFFECT_EMOTICON + 5, "", "d:/ymir work/effect/etc/emoticon/angry.mse" },
		{ pkBase.EFFECT_EMOTICON + 6, "", "d:/ymir work/effect/etc/emoticon/aha.mse" },
		{ pkBase.EFFECT_EMOTICON + 7, "", "d:/ymir work/effect/etc/emoticon/gloom.mse" },
		{ pkBase.EFFECT_EMOTICON + 8, "", "d:/ymir work/effect/etc/emoticon/sorry.mse" },
		{ pkBase.EFFECT_EMOTICON + 9, "", "d:/ymir work/effect/etc/emoticon/!_mix_back.mse" },
		{ pkBase.EFFECT_EMOTICON + 10, "", "d:/ymir work/effect/etc/emoticon/question.mse" },
		{ pkBase.EFFECT_EMOTICON + 11, "", "d:/ymir work/effect/etc/emoticon/fish.mse" },

	};

	enum
	{
		FLY_NONE,
		FLY_EXP,
		FLY_HP_MEDIUM,
		FLY_HP_BIG,
		FLY_SP_SMALL,
		FLY_SP_MEDIUM,
		FLY_SP_BIG,
		FLY_FIREWORK1,
		FLY_FIREWORK2,
		FLY_FIREWORK3,
		FLY_FIREWORK4,
		FLY_FIREWORK5,
		FLY_FIREWORK6,
		FLY_FIREWORK_XMAS,
		FLY_CHAIN_LIGHTNING,
		FLY_HP_SMALL,
		FLY_SKILL_MUYEONG,
#ifdef ENABLE_QUIVER_SYSTEM
		FLY_QUIVER_ATTACK_NORMAL,
#endif
	};

	std::vector<SFly> m_vecFlyData = {
		{ FLY_EXP, pkFly.INDEX_FLY_TYPE_NORMAL, "d:/ymir work/effect/etc/gathering/ga_piece_yellow_small2.msf" },
		{ FLY_HP_MEDIUM, pkFly.INDEX_FLY_TYPE_NORMAL, "d:/ymir work/effect/etc/gathering/ga_piece_red_small.msf" },
		{ FLY_HP_BIG, pkFly.INDEX_FLY_TYPE_NORMAL, "d:/ymir work/effect/etc/gathering/ga_piece_red_big.msf" },
		{ FLY_SP_SMALL, pkFly.INDEX_FLY_TYPE_NORMAL, "d:/ymir work/effect/etc/gathering/ga_piece_blue_warrior_small.msf" },
		{ FLY_SP_MEDIUM, pkFly.INDEX_FLY_TYPE_NORMAL, "d:/ymir work/effect/etc/gathering/ga_piece_blue_small.msf" },
		{ FLY_SP_BIG, pkFly.INDEX_FLY_TYPE_NORMAL, "d:/ymir work/effect/etc/gathering/ga_piece_blue_big.msf" },
		{ FLY_FIREWORK1, pkFly.INDEX_FLY_TYPE_FIRE_CRACKER, "d:/ymir work/effect/etc/firecracker/firecracker_1.msf" },
		{ FLY_FIREWORK2, pkFly.INDEX_FLY_TYPE_FIRE_CRACKER, "d:/ymir work/effect/etc/firecracker/firecracker_2.msf" },
		{ FLY_FIREWORK3, pkFly.INDEX_FLY_TYPE_FIRE_CRACKER, "d:/ymir work/effect/etc/firecracker/firecracker_3.msf" },
		{ FLY_FIREWORK4, pkFly.INDEX_FLY_TYPE_FIRE_CRACKER, "d:/ymir work/effect/etc/firecracker/firecracker_4.msf" },
		{ FLY_FIREWORK5, pkFly.INDEX_FLY_TYPE_FIRE_CRACKER, "d:/ymir work/effect/etc/firecracker/firecracker_5.msf" },
		{ FLY_FIREWORK6, pkFly.INDEX_FLY_TYPE_FIRE_CRACKER, "d:/ymir work/effect/etc/firecracker/firecracker_6.msf" },
		{ FLY_FIREWORK_XMAS, pkFly.INDEX_FLY_TYPE_FIRE_CRACKER, "d:/ymir work/effect/etc/firecracker/firecracker_xmas.msf" },
		{ FLY_CHAIN_LIGHTNING, pkFly.INDEX_FLY_TYPE_NORMAL, "d:/ymir work/pc/shaman/effect/pokroe.msf" },
		{ FLY_HP_SMALL, pkFly.INDEX_FLY_TYPE_NORMAL, "d:/ymir work/effect/etc/gathering/ga_piece_red_smallest.msf" },
		{ FLY_SKILL_MUYEONG, pkFly.INDEX_FLY_TYPE_AUTO_FIRE, "d:/ymir work/pc/sura/effect/muyeong_fly.msf" },
#ifdef ENABLE_QUIVER_SYSTEM:
		{ FLY_QUIVER_ATTACK_NORMAL, pkFly.INDEX_FLY_TYPE_NORMAL, "d:/ymir work/pc/assassin/effect/arrow_02.msf" },
#endif
	};

	std::vector<char*> v_vecEmoticonString = {
		":sweat:", ":money:", ":happy:", ":love_s:", ":love_l:", ":angry:",
		":aha:", ":gloom:", ":sorry:", ":mix_back:", ":question:", ":fish:"
	};

	// GM_EFFECT
	TEffect effect;
	effect.uiType = pkBase.EFFECT_AFFECT + 0;
	memcpy(effect.stBone, "Bip01", sizeof(effect.stBone));
	memcpy(effect.stEffect, GM_MARK, sizeof(effect.stEffect));

	m_vecEffectData.push_back(effect);
	// GM_EFFECT
	
	for (const auto& it : m_vecEffectData)
	{
		pkBase.RegisterEffect(it.uiType, it.stBone, it.stEffect, false);
	}	
	
	for (const auto& it : m_vecFlyData)
	{
		pkFly.RegisterIndexedFlyData(it.dwIndex, it.byType, it.stName);
	}

	for (const auto & emotionString : v_vecEmoticonString)
	{
		pkNetworkStream.RegisterEmoticonString(emotionString);
	}

	return true;
}

const bool CPlayerSettingsModule::RegisterEmotionAnis(char stFolder[FILE_MAX_NUM])
{
	CRaceManager& pkManager = CRaceManager::Instance();

	CRaceData* pRaceData = pkManager.GetSelectedRaceDataPointer();
	if (!pRaceData)
		return false;

	std::vector<SMotion> m_vecEmotion =
	{
		{ pkMotionManager.NAME_CLAP, "clap.msa", 0 },
		{ pkMotionManager.NAME_CHEERS_1, "cheers_1.msa", 0 },
		{ pkMotionManager.NAME_CHEERS_2, "cheers_2.msa", 0 },
		{ pkMotionManager.NAME_DANCE_1, "dance_1.msa", 0 },
		{ pkMotionManager.NAME_DANCE_2, "dance_2.msa", 0 },
		{ pkMotionManager.NAME_DANCE_3, "dance_3.msa", 0 },
		{ pkMotionManager.NAME_DANCE_4, "dance_4.msa", 0 },
		{ pkMotionManager.NAME_DANCE_5, "dance_5.msa", 0 },
		{ pkMotionManager.NAME_DANCE_6, "dance_6.msa", 0 },
		{ pkMotionManager.NAME_CONGRATULATION, "congratulation.msa", 0 },
		{ pkMotionManager.NAME_FORGIVE, "forgive.msa", 0 },
		{ pkMotionManager.NAME_ANGRY, "angry.msa", 0 },
		{ pkMotionManager.NAME_ATTRACTIVE, "attractive.msa", 0 },
		{ pkMotionManager.NAME_SAD, "sad.msa", 0 },
		{ pkMotionManager.NAME_SHY, "shy.msa", 0 },
		{ pkMotionManager.NAME_CHEERUP, "cheerup.msa", 0 },
		{ pkMotionManager.NAME_BANTER, "banter.msa", 0 },
		{ pkMotionManager.NAME_JOY, "joy.msa", 0 },
		{ pkMotionManager.NAME_FRENCH_KISS_WITH_WARRIOR, "french_kiss_with_warrior.msa", 0 },
		{ pkMotionManager.NAME_FRENCH_KISS_WITH_ASSASSIN, "french_kiss_with_assassin.msa", 0 },
		{ pkMotionManager.NAME_FRENCH_KISS_WITH_SURA, "french_kiss_with_sura.msa", 0 },
		{ pkMotionManager.NAME_FRENCH_KISS_WITH_SHAMAN, "french_kiss_with_shaman.msa", 0 },
		{ pkMotionManager.NAME_KISS_WITH_WARRIOR, "kiss_with_warrior.msa", 0 },
		{ pkMotionManager.NAME_KISS_WITH_ASSASSIN, "kiss_with_assassin.msa", 0 },
		{ pkMotionManager.NAME_KISS_WITH_SURA, "kiss_with_sura.msa", 0 },
		{ pkMotionManager.NAME_KISS_WITH_SHAMAN, "kiss_with_shaman.msa", 0 },
		{ pkMotionManager.NAME_SLAP_HIT_WITH_WARRIOR, "slap_hit.msa", 0 },
		{ pkMotionManager.NAME_SLAP_HIT_WITH_ASSASSIN, "slap_hit.msa", 0 },
		{ pkMotionManager.NAME_SLAP_HIT_WITH_SURA, "slap_hit.msa", 0 },
		{ pkMotionManager.NAME_SLAP_HIT_WITH_SHAMAN, "slap_hit.msa", 0 },
		{ pkMotionManager.NAME_SLAP_HURT_WITH_WARRIOR, "slap_hurt.msa", 0 },
		{ pkMotionManager.NAME_SLAP_HURT_WITH_ASSASSIN, "slap_hurt.msa", 0 },
		{ pkMotionManager.NAME_SLAP_HURT_WITH_SURA, "slap_hurt.msa", 0 },
		{ pkMotionManager.NAME_SLAP_HURT_WITH_SHAMAN, "slap_hurt.msa", 0 },
	};

	char szFileName[FILE_MAX_NUM];
	pRaceData->RegisterMotionMode(pkMotionManager.MODE_GENERAL);
	for (const auto& it : m_vecEmotion)
	{
		snprintf(szFileName, sizeof(szFileName), "%s%s%s", stFolder, "action/", it.stName);
		pRaceData->RegisterMotionData(pkMotionManager.MODE_GENERAL, it.wMotionIndex, szFileName, it.byPercentage);
	}	
	
	pRaceData->RegisterMotionMode(pkMotionManager.MODE_WEDDING_DRESS);
	for (const auto& it : m_vecEmotion)
	{
		snprintf(szFileName, sizeof(szFileName), "%s%s%s", stFolder, "action/", it.stName);
		pRaceData->RegisterMotionData(pkMotionManager.MODE_WEDDING_DRESS, it.wMotionIndex, szFileName, it.byPercentage);
	}
	
	std::vector<SMotion> m_vecEmotionDress =
	{
		{ pkMotionManager.NAME_WAIT, "wait.msa", 0 },
		{ pkMotionManager.NAME_WALK, "walk.msa", 0 },
		{ pkMotionManager.NAME_RUN, "walk.msa", 0 },
	};

	pRaceData->RegisterMotionMode(pkMotionManager.MODE_WEDDING_DRESS);
	for (const auto& it : m_vecEmotionDress)
	{
		snprintf(szFileName, sizeof(szFileName), "%s%s%s", stFolder, "wedding/", it.stName);
		pRaceData->RegisterMotionData(pkMotionManager.MODE_WEDDING_DRESS, it.wMotionIndex, szFileName, it.byPercentage);
	}

	return true;
}

const bool CPlayerSettingsModule::LoadGeneralMotion(char stFolder[FILE_MAX_NUM])
{
	CRaceManager& pkManager = CRaceManager::Instance();

	CRaceData* pRaceData = pkManager.GetSelectedRaceDataPointer();
	if (!pRaceData)
		return false;
	
	std::vector<SMotion> m_vecBasicMotion =
	{
		{ pkMotionManager.NAME_WAIT, "wait.msa", 0 },
		{ pkMotionManager.NAME_WALK, "walk.msa", 0 },
		{ pkMotionManager.NAME_RUN, "run.msa", 0 },
		{ pkMotionManager.NAME_DAMAGE, "damage.msa", 50 },
		{ pkMotionManager.NAME_DAMAGE, "damage_1.msa", 50 },
		{ pkMotionManager.NAME_DAMAGE_BACK, "damage_2.msa", 50 },
		{ pkMotionManager.NAME_DAMAGE_BACK, "damage_3.msa", 50 },
		{ pkMotionManager.NAME_DAMAGE_FLYING, "damage_flying.msa", 0 },
		{ pkMotionManager.NAME_STAND_UP, "falling_stand.msa", 0 },
		{ pkMotionManager.NAME_DAMAGE_FLYING_BACK, "back_damage_flying.msa", 0 },
		{ pkMotionManager.NAME_STAND_UP_BACK, "back_falling_stand.msa", 0 },
		{ pkMotionManager.NAME_DEAD, "dead.msa", 0 },
		{ pkMotionManager.NAME_DIG, "dig.msa", 0 },
	};

	char szFileName[FILE_MAX_NUM];
	pRaceData->RegisterMotionMode(pkMotionManager.MODE_GENERAL);
	for (const auto& it : m_vecBasicMotion)
	{
		snprintf(szFileName, sizeof(szFileName), "%s%s%s", stFolder, "general/", it.stName);
		pRaceData->RegisterMotionData(pkMotionManager.MODE_GENERAL, it.wMotionIndex, szFileName, it.byPercentage);
	}

	return true;
}

const bool CPlayerSettingsModule::LoadGameWarrior(DWORD dwRace, char stFolder[FILE_MAX_NUM])
{
	CRaceManager& pkManager = CRaceManager::Instance();
	pkManager.SelectRace(dwRace);

	if (!LoadGeneralMotion(stFolder))
		return false;

	CRaceData* pRaceData = pkManager.GetSelectedRaceDataPointer();
	if (!pRaceData)
		return false;

	if (!pRaceData->SetMotionRandomWeight(pkMotionManager.MODE_GENERAL, pkMotionManager.NAME_WAIT, 0, 70))
		return false;

	std::vector<SMotion> m_vecMotionGeneral =
	{
		{ pkMotionManager.NAME_WAIT, "wait_1.msa", 30 },
		{ pkMotionManager.NAME_COMBO_ATTACK_1, "attack.msa", 50 },
		{ pkMotionManager.NAME_COMBO_ATTACK_1, "attack_1.msa", 50 },
	};

	char szFileName[FILE_MAX_NUM];
	pRaceData->RegisterMotionMode(pkMotionManager.MODE_GENERAL);
	for (const auto& it : m_vecMotionGeneral)
	{
		snprintf(szFileName, sizeof(szFileName), "%s%s%s", stFolder, "general/", it.stName);
		pRaceData->RegisterMotionData(pkMotionManager.MODE_GENERAL, it.wMotionIndex, szFileName, it.byPercentage);
	}

	std::vector<SMotion> m_vecMotionSkill =
	{
		{ GUILD_SKILL_DRAGONBLOOD, "guild_yongsinuipi.msa", 0 },
		{ GUILD_SKILL_DRAGONBLESS, "guild_yongsinuichukbok.msa", 0 },
		{ GUILD_SKILL_BLESSARMOR, "guild_seonghwigap.msa", 0 },
		{ GUILD_SKILL_SPPEDUP, "guild_gasokhwa.msa", 0 },
		{ GUILD_SKILL_DRAGONWRATH, "guild_yongsinuibunno.msa", 0 },
		{ GUILD_SKILL_MAGICUP, "guild_jumunsul.msa", 0 },
	};

	std::vector<std::pair<BYTE, const char*>> m_vecSkillName = {
		{ 1, "samyeon" },
		{ 2, "palbang" },
		{ 3, "jeongwi" },
		{ 4, "geomgyeong" },
		{ 5, "tanhwan" },
		{ 6, "gihyeol" },	
		{ 16, "gigongcham" },
		{ 17, "gyeoksan" },
		{ 18, "daejin" },
		{ 19, "cheongeun" },
		{ 20, "geompung" },
		{ 21, "noegeom" },
	};

	
	char szSkillName[FILE_MAX_NUM];
	char szSkillAdd[4] = "";
	for (WORD i = 0; i < CPythonSkill::SKILL_EFFECT_COUNT; i++)
	{
		for (auto& it : m_vecSkillName)
		{
			SMotion motion;

			motion.wMotionIndex = pkMotionManager.NAME_SKILL + (i * CPythonSkill::SKILL_GRADEGAP) + it.first;
			motion.byPercentage = 0;

			if (i > 0)
				snprintf(szSkillAdd, sizeof(szSkillAdd), "_%d", i + 1);
			else
				snprintf(szSkillAdd, sizeof(szSkillAdd), "");

			snprintf(motion.stName, sizeof(motion.stName), "%s%s.msa", it.second, szSkillAdd);
			m_vecMotionSkill.push_back(motion);
		}
	}

	pRaceData->RegisterMotionMode(pkMotionManager.MODE_GENERAL);
	for (const auto& it : m_vecMotionSkill)
	{
		snprintf(szFileName, sizeof(szFileName), "%s%s%s", stFolder, "skill/", it.stName);
		pRaceData->RegisterMotionData(pkMotionManager.MODE_GENERAL, it.wMotionIndex, szFileName, it.byPercentage);
	}
	
	pRaceData->ReserveComboAttack(pkMotionManager.MODE_GENERAL, COMBO_TYPE_1, 1);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_GENERAL, COMBO_TYPE_1, COMBO_INDEX_1, pkMotionManager.NAME_COMBO_ATTACK_1);

	RegisterEmotionAnis(stFolder);

	std::vector<SMotion> m_vecMotionSword =
	{
		{ pkMotionManager.NAME_WAIT, "wait.msa", 50 },
		{ pkMotionManager.NAME_WAIT, "wait_1.msa", 50 },
		{ pkMotionManager.NAME_WALK, "walk.msa", 0 },
		{ pkMotionManager.NAME_RUN, "run.msa", 0 },
		{ pkMotionManager.NAME_DAMAGE, "damage.msa", 50 },
		{ pkMotionManager.NAME_DAMAGE, "damage_1.msa", 50 },
		{ pkMotionManager.NAME_DAMAGE_BACK, "damage_2.msa", 50 },
		{ pkMotionManager.NAME_DAMAGE_BACK, "damage_3.msa", 50 },
		{ pkMotionManager.NAME_COMBO_ATTACK_1, "combo_01.msa", 0 },
		{ pkMotionManager.NAME_COMBO_ATTACK_2, "combo_02.msa", 0 },
		{ pkMotionManager.NAME_COMBO_ATTACK_3, "combo_03.msa", 0 },
		{ pkMotionManager.NAME_COMBO_ATTACK_4, "combo_04.msa", 0 },
		{ pkMotionManager.NAME_COMBO_ATTACK_5, "combo_05.msa" , 0},
		{ pkMotionManager.NAME_COMBO_ATTACK_6, "combo_06.msa", 0 },
		{ pkMotionManager.NAME_COMBO_ATTACK_7, "combo_07.msa", 0 },
	};

	pRaceData->RegisterMotionMode(pkMotionManager.MODE_ONEHAND_SWORD);
	for (const auto& it : m_vecMotionSword)
	{
		snprintf(szFileName, sizeof(szFileName), "%s%s%s", stFolder, "onehand_sword/", it.stName);
		pRaceData->RegisterMotionData(pkMotionManager.MODE_ONEHAND_SWORD, it.wMotionIndex, szFileName, it.byPercentage);
	}

	pRaceData->ReserveComboAttack(pkMotionManager.MODE_ONEHAND_SWORD, COMBO_TYPE_1, 4);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_ONEHAND_SWORD, COMBO_TYPE_1, COMBO_INDEX_1, pkMotionManager.NAME_COMBO_ATTACK_1);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_ONEHAND_SWORD, COMBO_TYPE_1, COMBO_INDEX_2, pkMotionManager.NAME_COMBO_ATTACK_2);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_ONEHAND_SWORD, COMBO_TYPE_1, COMBO_INDEX_3, pkMotionManager.NAME_COMBO_ATTACK_3);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_ONEHAND_SWORD, COMBO_TYPE_1, COMBO_INDEX_4, pkMotionManager.NAME_COMBO_ATTACK_4);	
	
	pRaceData->ReserveComboAttack(pkMotionManager.MODE_ONEHAND_SWORD, COMBO_TYPE_2, 5);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_ONEHAND_SWORD, COMBO_TYPE_2, COMBO_INDEX_1, pkMotionManager.NAME_COMBO_ATTACK_1);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_ONEHAND_SWORD, COMBO_TYPE_2, COMBO_INDEX_2, pkMotionManager.NAME_COMBO_ATTACK_2);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_ONEHAND_SWORD, COMBO_TYPE_2, COMBO_INDEX_3, pkMotionManager.NAME_COMBO_ATTACK_3);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_ONEHAND_SWORD, COMBO_TYPE_2, COMBO_INDEX_4, pkMotionManager.NAME_COMBO_ATTACK_5);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_ONEHAND_SWORD, COMBO_TYPE_2, COMBO_INDEX_5, pkMotionManager.NAME_COMBO_ATTACK_7);
	
	pRaceData->ReserveComboAttack(pkMotionManager.MODE_ONEHAND_SWORD, COMBO_TYPE_3, 6);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_ONEHAND_SWORD, COMBO_TYPE_3, COMBO_INDEX_1, pkMotionManager.NAME_COMBO_ATTACK_1);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_ONEHAND_SWORD, COMBO_TYPE_3, COMBO_INDEX_2, pkMotionManager.NAME_COMBO_ATTACK_2);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_ONEHAND_SWORD, COMBO_TYPE_3, COMBO_INDEX_3, pkMotionManager.NAME_COMBO_ATTACK_3);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_ONEHAND_SWORD, COMBO_TYPE_3, COMBO_INDEX_4, pkMotionManager.NAME_COMBO_ATTACK_5);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_ONEHAND_SWORD, COMBO_TYPE_3, COMBO_INDEX_5, pkMotionManager.NAME_COMBO_ATTACK_6);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_ONEHAND_SWORD, COMBO_TYPE_3, COMBO_INDEX_6, pkMotionManager.NAME_COMBO_ATTACK_4);

	std::vector<SMotion> m_vecMotionTwoHandSword =
	{
		{ pkMotionManager.NAME_WAIT, "wait.msa", 70 },
		{ pkMotionManager.NAME_WAIT, "wait_1.msa", 30 },
		{ pkMotionManager.NAME_WALK, "walk.msa", 0 },
		{ pkMotionManager.NAME_RUN, "run.msa", 0 },
		{ pkMotionManager.NAME_DAMAGE, "damage.msa", 50 },
		{ pkMotionManager.NAME_DAMAGE, "damage_1.msa", 50 },
		{ pkMotionManager.NAME_DAMAGE_BACK, "damage_2.msa", 50 },
		{ pkMotionManager.NAME_DAMAGE_BACK, "damage_3.msa", 50 },
		{ pkMotionManager.NAME_COMBO_ATTACK_1, "combo_01.msa", 0 },
		{ pkMotionManager.NAME_COMBO_ATTACK_2, "combo_02.msa", 0 },
		{ pkMotionManager.NAME_COMBO_ATTACK_3, "combo_03.msa", 0 },
		{ pkMotionManager.NAME_COMBO_ATTACK_4, "combo_04.msa", 0 },
		{ pkMotionManager.NAME_COMBO_ATTACK_5, "combo_05.msa", 0 },
		{ pkMotionManager.NAME_COMBO_ATTACK_6, "combo_06.msa", 0 },
		{ pkMotionManager.NAME_COMBO_ATTACK_7, "combo_07.msa", 0 },
	};

	pRaceData->RegisterMotionMode(pkMotionManager.MODE_TWOHAND_SWORD);
	for (const auto& it : m_vecMotionSword)
	{
		snprintf(szFileName, sizeof(szFileName), "%s%s%s", stFolder, "twohand_sword/", it.stName);
		pRaceData->RegisterMotionData(pkMotionManager.MODE_TWOHAND_SWORD, it.wMotionIndex, szFileName, it.byPercentage);
	}

	pRaceData->ReserveComboAttack(pkMotionManager.MODE_TWOHAND_SWORD, COMBO_TYPE_1, 4);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_TWOHAND_SWORD, COMBO_TYPE_1, COMBO_INDEX_1, pkMotionManager.NAME_COMBO_ATTACK_1);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_TWOHAND_SWORD, COMBO_TYPE_1, COMBO_INDEX_2, pkMotionManager.NAME_COMBO_ATTACK_2);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_TWOHAND_SWORD, COMBO_TYPE_1, COMBO_INDEX_3, pkMotionManager.NAME_COMBO_ATTACK_3);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_TWOHAND_SWORD, COMBO_TYPE_1, COMBO_INDEX_4, pkMotionManager.NAME_COMBO_ATTACK_4);

	pRaceData->ReserveComboAttack(pkMotionManager.MODE_TWOHAND_SWORD, COMBO_TYPE_2, 5);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_TWOHAND_SWORD, COMBO_TYPE_2, COMBO_INDEX_1, pkMotionManager.NAME_COMBO_ATTACK_1);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_TWOHAND_SWORD, COMBO_TYPE_2, COMBO_INDEX_2, pkMotionManager.NAME_COMBO_ATTACK_2);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_TWOHAND_SWORD, COMBO_TYPE_2, COMBO_INDEX_3, pkMotionManager.NAME_COMBO_ATTACK_3);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_TWOHAND_SWORD, COMBO_TYPE_2, COMBO_INDEX_4, pkMotionManager.NAME_COMBO_ATTACK_5);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_TWOHAND_SWORD, COMBO_TYPE_2, COMBO_INDEX_5, pkMotionManager.NAME_COMBO_ATTACK_7);

	pRaceData->ReserveComboAttack(pkMotionManager.MODE_TWOHAND_SWORD, COMBO_TYPE_3, 6);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_TWOHAND_SWORD, COMBO_TYPE_3, COMBO_INDEX_1, pkMotionManager.NAME_COMBO_ATTACK_1);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_TWOHAND_SWORD, COMBO_TYPE_3, COMBO_INDEX_2, pkMotionManager.NAME_COMBO_ATTACK_2);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_TWOHAND_SWORD, COMBO_TYPE_3, COMBO_INDEX_3, pkMotionManager.NAME_COMBO_ATTACK_3);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_TWOHAND_SWORD, COMBO_TYPE_3, COMBO_INDEX_4, pkMotionManager.NAME_COMBO_ATTACK_5);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_TWOHAND_SWORD, COMBO_TYPE_3, COMBO_INDEX_5, pkMotionManager.NAME_COMBO_ATTACK_6);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_TWOHAND_SWORD, COMBO_TYPE_3, COMBO_INDEX_6, pkMotionManager.NAME_COMBO_ATTACK_4);

	std::vector<SMotion> m_vecMotionFishing =
	{
		{ pkMotionManager.NAME_WAIT, "wait.msa", 0 },
		{ pkMotionManager.NAME_WALK, "walk.msa", 0 },
		{ pkMotionManager.NAME_RUN, "run.msa", 0 },
		{ pkMotionManager.NAME_FISHING_THROW, "throw.msa", 0 },
		{ pkMotionManager.NAME_FISHING_WAIT, "fishing_wait.msa", 0 },
		{ pkMotionManager.NAME_FISHING_STOP, "fishing_cancel.msa", 0 },
		{ pkMotionManager.NAME_FISHING_REACT, "fishing_react.msa", 0 },
		{ pkMotionManager.NAME_FISHING_CATCH, "fishing_catch.msa", 0 },
		{ pkMotionManager.NAME_FISHING_FAIL, "fishing_fail.msa", 0 },
	};

	pRaceData->RegisterMotionMode(pkMotionManager.MODE_FISHING);
	for (const auto& it : m_vecMotionFishing)
	{
		snprintf(szFileName, sizeof(szFileName), "%s%s%s", stFolder, "fishing/", it.stName);
		pRaceData->RegisterMotionData(pkMotionManager.MODE_FISHING, it.wMotionIndex, szFileName, it.byPercentage);
	}
	
	std::vector<SMotion> m_vecMotionHorse =
	{
		{ pkMotionManager.NAME_WAIT, "wait.msa", 90 },
		{ pkMotionManager.NAME_WAIT, "wait_1.msa", 9 },
		{ pkMotionManager.NAME_WAIT, "wait_2.msa", 1 },
		{ pkMotionManager.NAME_WALK, "walk.msa", 0 },
		{ pkMotionManager.NAME_RUN, "run.msa", 0 },
		{ pkMotionManager.NAME_DAMAGE, "damage.msa", 0 },
		{ pkMotionManager.NAME_DAMAGE_BACK, "damage.msa", 0 },
		{ pkMotionManager.NAME_DEAD, "dead.msa", 0 },
		{ HORSE_SKILL_CHARGE, "skill_charge.msa", 0 },
	};

	pRaceData->RegisterMotionMode(pkMotionManager.MODE_HORSE);
	for (const auto& it : m_vecMotionHorse)
	{
		snprintf(szFileName, sizeof(szFileName), "%s%s%s", stFolder, "horse/", it.stName);
		pRaceData->RegisterMotionData(pkMotionManager.MODE_HORSE, it.wMotionIndex, szFileName, it.byPercentage);
	}

	std::vector<SMotion> m_vecMotionHorseSword =
	{
		{ pkMotionManager.NAME_COMBO_ATTACK_1, "combo_01.msa", 0 },
		{ pkMotionManager.NAME_COMBO_ATTACK_2, "combo_02.msa", 0 },
		{ pkMotionManager.NAME_COMBO_ATTACK_3, "combo_03.msa", 0 },
		{ HORSE_SKILL_WILDATTACK, "skill_wildattack.msa", 0 },
		{ HORSE_SKILL_SPLASH, "skill_splash.msa", 0 },
	};

	pRaceData->RegisterMotionMode(pkMotionManager.MODE_HORSE_ONEHAND_SWORD);
	for (const auto& it : m_vecMotionHorseSword)
	{
		snprintf(szFileName, sizeof(szFileName), "%s%s%s", stFolder, "horse_onehand_sword/", it.stName);
		pRaceData->RegisterMotionData(pkMotionManager.MODE_HORSE_ONEHAND_SWORD, it.wMotionIndex, szFileName, it.byPercentage);
	}

	pRaceData->ReserveComboAttack(pkMotionManager.MODE_HORSE_ONEHAND_SWORD, COMBO_TYPE_1, 3);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_HORSE_ONEHAND_SWORD, COMBO_TYPE_1, COMBO_INDEX_1, pkMotionManager.NAME_COMBO_ATTACK_1);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_HORSE_ONEHAND_SWORD, COMBO_TYPE_1, COMBO_INDEX_2, pkMotionManager.NAME_COMBO_ATTACK_2);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_HORSE_ONEHAND_SWORD, COMBO_TYPE_1, COMBO_INDEX_3, pkMotionManager.NAME_COMBO_ATTACK_3);

	std::vector<SMotion> m_vecMotionHorseTwoHandSword =
	{
		{ pkMotionManager.NAME_COMBO_ATTACK_1, "combo_01.msa", 0 },
		{ pkMotionManager.NAME_COMBO_ATTACK_2, "combo_02.msa", 0 },
		{ pkMotionManager.NAME_COMBO_ATTACK_3, "combo_03.msa", 0 },
		{ HORSE_SKILL_WILDATTACK, "skill_wildattack.msa", 0 },
		{ HORSE_SKILL_SPLASH, "skill_splash.msa", 0 },
	};

	pRaceData->RegisterMotionMode(pkMotionManager.MODE_HORSE_TWOHAND_SWORD);
	for (const auto& it : m_vecMotionHorseTwoHandSword)
	{
		snprintf(szFileName, sizeof(szFileName), "%s%s%s", stFolder, "horse_twohand_sword/", it.stName);
		pRaceData->RegisterMotionData(pkMotionManager.MODE_HORSE_TWOHAND_SWORD, it.wMotionIndex, szFileName, it.byPercentage);
	}

	pRaceData->ReserveComboAttack(pkMotionManager.MODE_HORSE_TWOHAND_SWORD, COMBO_TYPE_1, 3);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_HORSE_TWOHAND_SWORD, COMBO_TYPE_1, COMBO_INDEX_1, pkMotionManager.NAME_COMBO_ATTACK_1);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_HORSE_TWOHAND_SWORD, COMBO_TYPE_1, COMBO_INDEX_2, pkMotionManager.NAME_COMBO_ATTACK_2);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_HORSE_TWOHAND_SWORD, COMBO_TYPE_1, COMBO_INDEX_3, pkMotionManager.NAME_COMBO_ATTACK_3);

	pRaceData->RegisterAttachingBoneName(CRaceData::PART_WEAPON, "equip_right_hand");

#ifdef ENABLE_ACCE_SYSTEM
	pRaceData->RegisterAttachingBoneName(CRaceData::PART_ACCE, "Bip01 Spine2");
#endif

	return true;
}

const bool CPlayerSettingsModule::LoadGameAssassin(DWORD dwRace, char stFolder[FILE_MAX_NUM])
{
	CRaceManager& pkManager = CRaceManager::Instance();
	pkManager.SelectRace(dwRace);

	if (!LoadGeneralMotion(stFolder))
		return false;

	CRaceData* pRaceData = pkManager.GetSelectedRaceDataPointer();
	if (!pRaceData)
		return false;

	if (!pRaceData->SetMotionRandomWeight(pkMotionManager.MODE_GENERAL, pkMotionManager.NAME_WAIT, 0, 70))
		return false;

	std::vector<SMotion> m_vecMotionGeneral =
	{
		{ pkMotionManager.NAME_WAIT, "wait_1.msa", 30 },
		{ pkMotionManager.NAME_COMBO_ATTACK_1, "attack.msa", 50 },
		{ pkMotionManager.NAME_COMBO_ATTACK_1, "attack_1.msa", 50 },
	};

	char szFileName[FILE_MAX_NUM];
	pRaceData->RegisterMotionMode(pkMotionManager.MODE_GENERAL);
	for (const auto& it : m_vecMotionGeneral)
	{
		snprintf(szFileName, sizeof(szFileName), "%s%s%s", stFolder, "general/", it.stName);
		pRaceData->RegisterMotionData(pkMotionManager.MODE_GENERAL, it.wMotionIndex, szFileName, it.byPercentage);
	}

	std::vector<SMotion> m_vecMotionSkill =
	{
		{ GUILD_SKILL_DRAGONBLOOD, "guild_yongsinuipi.msa", 0 },
		{ GUILD_SKILL_DRAGONBLESS, "guild_yongsinuichukbok.msa", 0 },
		{ GUILD_SKILL_BLESSARMOR, "guild_seonghwigap.msa", 0 },
		{ GUILD_SKILL_SPPEDUP, "guild_gasokhwa.msa", 0 },
		{ GUILD_SKILL_DRAGONWRATH, "guild_yongsinuibunno.msa", 0 },
		{ GUILD_SKILL_MAGICUP, "guild_jumunsul.msa", 0 },
	};

	std::vector<std::pair<BYTE, const char*>> m_vecSkillName = {
		{ 1, "amseup" },
		{ 2, "gungsin" },
		{ 3, "charyun" },
		{ 4, "eunhyeong" },
		{ 5, "sangong" },
		{ 6, "seomjeon" },
		{ 16, "yeonsa" },
		{ 17, "gwangyeok" },
		{ 18, "hwajo" },
		{ 19, "gyeonggong" },
		{ 20, "dokgigung" },
		{ 21, "seomgwang" },
	};

	char szSkillName[FILE_MAX_NUM];
	char szSkillAdd[4] = "";
	for (WORD i = 0; i < CPythonSkill::SKILL_EFFECT_COUNT; i++)
	{
		for (auto& it : m_vecSkillName)
		{
			SMotion motion;

			motion.wMotionIndex = pkMotionManager.NAME_SKILL + (i * CPythonSkill::SKILL_GRADEGAP) + it.first;
			motion.byPercentage = 0;

			if (i > 0)
				snprintf(szSkillAdd, sizeof(szSkillAdd), "_%d", i + 1);
			else
				snprintf(szSkillAdd, sizeof(szSkillAdd), "");

			snprintf(motion.stName, sizeof(motion.stName), "%s%s.msa", it.second, szSkillAdd);
			m_vecMotionSkill.push_back(motion);
		}
	}

	pRaceData->RegisterMotionMode(pkMotionManager.MODE_GENERAL);
	for (const auto& it : m_vecMotionSkill)
	{
		snprintf(szFileName, sizeof(szFileName), "%s%s%s", stFolder, "skill/", it.stName);
		pRaceData->RegisterMotionData(pkMotionManager.MODE_GENERAL, it.wMotionIndex, szFileName, it.byPercentage);
	}

	pRaceData->ReserveComboAttack(pkMotionManager.MODE_GENERAL, COMBO_TYPE_1, 1);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_GENERAL, COMBO_TYPE_1, COMBO_INDEX_1, pkMotionManager.NAME_COMBO_ATTACK_1);

	RegisterEmotionAnis(stFolder);

	std::vector<SMotion> m_vecMotionSword =
	{
		{ pkMotionManager.NAME_WAIT, "wait.msa", 70 },
		{ pkMotionManager.NAME_WAIT, "wait_1.msa", 30 },
		{ pkMotionManager.NAME_WALK, "walk.msa" , 0 },
		{ pkMotionManager.NAME_RUN, "run.msa" , 0 },
		{ pkMotionManager.NAME_DAMAGE, "damage.msa", 50 },
		{ pkMotionManager.NAME_DAMAGE, "damage_1.msa", 50 },
		{ pkMotionManager.NAME_DAMAGE_BACK, "damage_2.msa", 50 },
		{ pkMotionManager.NAME_DAMAGE_BACK, "damage_3.msa", 50 },
		{ pkMotionManager.NAME_COMBO_ATTACK_1, "combo_01.msa" , 0 },
		{ pkMotionManager.NAME_COMBO_ATTACK_2, "combo_02.msa" , 0 },
		{ pkMotionManager.NAME_COMBO_ATTACK_3, "combo_03.msa" , 0 },
		{ pkMotionManager.NAME_COMBO_ATTACK_4, "combo_04.msa" , 0 },
		{ pkMotionManager.NAME_COMBO_ATTACK_5, "combo_05.msa" , 0 },
		{ pkMotionManager.NAME_COMBO_ATTACK_6, "combo_06.msa" , 0 },
		{ pkMotionManager.NAME_COMBO_ATTACK_7, "combo_07.msa" , 0 },
	};

	pRaceData->RegisterMotionMode(pkMotionManager.MODE_ONEHAND_SWORD);
	for (const auto& it : m_vecMotionSword)
	{
		snprintf(szFileName, sizeof(szFileName), "%s%s%s", stFolder, "onehand_sword/", it.stName);
		pRaceData->RegisterMotionData(pkMotionManager.MODE_ONEHAND_SWORD, it.wMotionIndex, szFileName, it.byPercentage);
	}

	pRaceData->ReserveComboAttack(pkMotionManager.MODE_ONEHAND_SWORD, COMBO_TYPE_1, 4);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_ONEHAND_SWORD, COMBO_TYPE_1, COMBO_INDEX_1, pkMotionManager.NAME_COMBO_ATTACK_1);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_ONEHAND_SWORD, COMBO_TYPE_1, COMBO_INDEX_2, pkMotionManager.NAME_COMBO_ATTACK_2);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_ONEHAND_SWORD, COMBO_TYPE_1, COMBO_INDEX_3, pkMotionManager.NAME_COMBO_ATTACK_3);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_ONEHAND_SWORD, COMBO_TYPE_1, COMBO_INDEX_4, pkMotionManager.NAME_COMBO_ATTACK_4);

	pRaceData->ReserveComboAttack(pkMotionManager.MODE_ONEHAND_SWORD, COMBO_TYPE_2, 5);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_ONEHAND_SWORD, COMBO_TYPE_2, COMBO_INDEX_1, pkMotionManager.NAME_COMBO_ATTACK_1);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_ONEHAND_SWORD, COMBO_TYPE_2, COMBO_INDEX_2, pkMotionManager.NAME_COMBO_ATTACK_2);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_ONEHAND_SWORD, COMBO_TYPE_2, COMBO_INDEX_3, pkMotionManager.NAME_COMBO_ATTACK_3);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_ONEHAND_SWORD, COMBO_TYPE_2, COMBO_INDEX_4, pkMotionManager.NAME_COMBO_ATTACK_5);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_ONEHAND_SWORD, COMBO_TYPE_2, COMBO_INDEX_5, pkMotionManager.NAME_COMBO_ATTACK_7);

	pRaceData->ReserveComboAttack(pkMotionManager.MODE_ONEHAND_SWORD, COMBO_TYPE_3, 6);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_ONEHAND_SWORD, COMBO_TYPE_3, COMBO_INDEX_1, pkMotionManager.NAME_COMBO_ATTACK_1);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_ONEHAND_SWORD, COMBO_TYPE_3, COMBO_INDEX_2, pkMotionManager.NAME_COMBO_ATTACK_2);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_ONEHAND_SWORD, COMBO_TYPE_3, COMBO_INDEX_3, pkMotionManager.NAME_COMBO_ATTACK_3);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_ONEHAND_SWORD, COMBO_TYPE_3, COMBO_INDEX_4, pkMotionManager.NAME_COMBO_ATTACK_5);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_ONEHAND_SWORD, COMBO_TYPE_3, COMBO_INDEX_5, pkMotionManager.NAME_COMBO_ATTACK_6);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_ONEHAND_SWORD, COMBO_TYPE_3, COMBO_INDEX_6, pkMotionManager.NAME_COMBO_ATTACK_4);

	std::vector<SMotion> m_vecMotionDagger =
	{
		{ pkMotionManager.NAME_WAIT, "wait.msa", 70 },
		{ pkMotionManager.NAME_WAIT, "wait_1.msa", 30 },
		{ pkMotionManager.NAME_WALK, "walk.msa", 0 },
		{ pkMotionManager.NAME_RUN, "run.msa", 0 },
		{ pkMotionManager.NAME_DAMAGE, "damage.msa", 50 },
		{ pkMotionManager.NAME_DAMAGE, "damage_1.msa", 50 },
		{ pkMotionManager.NAME_DAMAGE_BACK, "damage_2.msa", 50 },
		{ pkMotionManager.NAME_DAMAGE_BACK, "damage_3.msa", 50 },
		{ pkMotionManager.NAME_COMBO_ATTACK_1, "combo_01.msa", 0 },
		{ pkMotionManager.NAME_COMBO_ATTACK_2, "combo_02.msa", 0 },
		{ pkMotionManager.NAME_COMBO_ATTACK_3, "combo_03.msa", 0 },
		{ pkMotionManager.NAME_COMBO_ATTACK_4, "combo_04.msa", 0 },
		{ pkMotionManager.NAME_COMBO_ATTACK_5, "combo_05.msa", 0 },
		{ pkMotionManager.NAME_COMBO_ATTACK_6, "combo_06.msa", 0 },
		{ pkMotionManager.NAME_COMBO_ATTACK_7, "combo_07.msa", 0 },
		{ pkMotionManager.NAME_COMBO_ATTACK_8, "combo_08.msa", 0 },
	};

	pRaceData->RegisterMotionMode(pkMotionManager.MODE_DUALHAND_SWORD);
	for (const auto& it : m_vecMotionDagger)
	{
		snprintf(szFileName, sizeof(szFileName), "%s%s%s", stFolder, "dualhand_sword/", it.stName);
		pRaceData->RegisterMotionData(pkMotionManager.MODE_DUALHAND_SWORD, it.wMotionIndex, szFileName, it.byPercentage);
	}

	pRaceData->ReserveComboAttack(pkMotionManager.MODE_DUALHAND_SWORD, COMBO_TYPE_1, 4);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_DUALHAND_SWORD, COMBO_TYPE_1, COMBO_INDEX_1, pkMotionManager.NAME_COMBO_ATTACK_1);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_DUALHAND_SWORD, COMBO_TYPE_1, COMBO_INDEX_2, pkMotionManager.NAME_COMBO_ATTACK_2);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_DUALHAND_SWORD, COMBO_TYPE_1, COMBO_INDEX_3, pkMotionManager.NAME_COMBO_ATTACK_3);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_DUALHAND_SWORD, COMBO_TYPE_1, COMBO_INDEX_4, pkMotionManager.NAME_COMBO_ATTACK_4);

	pRaceData->ReserveComboAttack(pkMotionManager.MODE_DUALHAND_SWORD, COMBO_TYPE_2, 5);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_DUALHAND_SWORD, COMBO_TYPE_2, COMBO_INDEX_1, pkMotionManager.NAME_COMBO_ATTACK_1);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_DUALHAND_SWORD, COMBO_TYPE_2, COMBO_INDEX_2, pkMotionManager.NAME_COMBO_ATTACK_2);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_DUALHAND_SWORD, COMBO_TYPE_2, COMBO_INDEX_3, pkMotionManager.NAME_COMBO_ATTACK_3);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_DUALHAND_SWORD, COMBO_TYPE_2, COMBO_INDEX_4, pkMotionManager.NAME_COMBO_ATTACK_5);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_DUALHAND_SWORD, COMBO_TYPE_2, COMBO_INDEX_5, pkMotionManager.NAME_COMBO_ATTACK_7);

	pRaceData->ReserveComboAttack(pkMotionManager.MODE_DUALHAND_SWORD, COMBO_TYPE_3, 6);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_DUALHAND_SWORD, COMBO_TYPE_3, COMBO_INDEX_1, pkMotionManager.NAME_COMBO_ATTACK_1);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_DUALHAND_SWORD, COMBO_TYPE_3, COMBO_INDEX_2, pkMotionManager.NAME_COMBO_ATTACK_2);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_DUALHAND_SWORD, COMBO_TYPE_3, COMBO_INDEX_3, pkMotionManager.NAME_COMBO_ATTACK_3);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_DUALHAND_SWORD, COMBO_TYPE_3, COMBO_INDEX_4, pkMotionManager.NAME_COMBO_ATTACK_5);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_DUALHAND_SWORD, COMBO_TYPE_3, COMBO_INDEX_5, pkMotionManager.NAME_COMBO_ATTACK_6);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_DUALHAND_SWORD, COMBO_TYPE_3, COMBO_INDEX_6, pkMotionManager.NAME_COMBO_ATTACK_8);	
	
	std::vector<SMotion> m_vecMotionBow =
	{
		{ pkMotionManager.NAME_WAIT, "wait.msa", 70 },
		{ pkMotionManager.NAME_WAIT, "wait_1.msa", 30},
		{ pkMotionManager.NAME_WALK, "walk.msa", 0 },
		{ pkMotionManager.NAME_RUN, "run.msa", 0 },
		{ pkMotionManager.NAME_DAMAGE, "damage.msa", 50},
		{ pkMotionManager.NAME_DAMAGE, "damage_1.msa", 50},
		{ pkMotionManager.NAME_DAMAGE_BACK, "damage_2.msa", 50},
		{ pkMotionManager.NAME_DAMAGE_BACK, "damage_3.msa", 50},
		{ pkMotionManager.NAME_COMBO_ATTACK_1, "attack.msa", 0 },
	};

	pRaceData->RegisterMotionMode(pkMotionManager.MODE_BOW);
	for (const auto& it : m_vecMotionBow)
	{
		snprintf(szFileName, sizeof(szFileName), "%s%s%s", stFolder, "bow/", it.stName);
		pRaceData->RegisterMotionData(pkMotionManager.MODE_BOW, it.wMotionIndex, szFileName, it.byPercentage);
	}

	pRaceData->ReserveComboAttack(pkMotionManager.MODE_BOW, COMBO_TYPE_1, 1);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_BOW, COMBO_TYPE_1, COMBO_INDEX_1, pkMotionManager.NAME_COMBO_ATTACK_1);

	std::vector<SMotion> m_vecMotionFishing =
	{
		{ pkMotionManager.NAME_WAIT, "wait.msa", 0 },
		{ pkMotionManager.NAME_WALK, "walk.msa", 0 },
		{ pkMotionManager.NAME_RUN, "run.msa", 0 },
		{ pkMotionManager.NAME_FISHING_THROW, "throw.msa", 0 },
		{ pkMotionManager.NAME_FISHING_WAIT, "fishing_wait.msa", 0 },
		{ pkMotionManager.NAME_FISHING_STOP, "fishing_cancel.msa", 0 },
		{ pkMotionManager.NAME_FISHING_REACT, "fishing_react.msa", 0 },
		{ pkMotionManager.NAME_FISHING_CATCH, "fishing_catch.msa", 0 },
		{ pkMotionManager.NAME_FISHING_FAIL, "fishing_fail.msa", 0 },
	};

	pRaceData->RegisterMotionMode(pkMotionManager.MODE_FISHING);
	for (const auto& it : m_vecMotionFishing)
	{
		snprintf(szFileName, sizeof(szFileName), "%s%s%s", stFolder, "fishing/", it.stName);
		pRaceData->RegisterMotionData(pkMotionManager.MODE_FISHING, it.wMotionIndex, szFileName, it.byPercentage);
	}

	std::vector<SMotion> m_vecMotionHorse =
	{
		{ pkMotionManager.NAME_WAIT, "wait.msa", 90 },
		{ pkMotionManager.NAME_WAIT, "wait_1.msa", 9 },
		{ pkMotionManager.NAME_WAIT, "wait_2.msa", 1 },
		{ pkMotionManager.NAME_WALK, "walk.msa", 0 },
		{ pkMotionManager.NAME_RUN, "run.msa", 0 },
		{ pkMotionManager.NAME_DAMAGE, "damage.msa", 0 },
		{ pkMotionManager.NAME_DAMAGE_BACK, "damage.msa", 0 },
		{ pkMotionManager.NAME_DEAD, "dead.msa", 0 },
		{ HORSE_SKILL_CHARGE, "skill_charge.msa", 0 },
	};

	pRaceData->RegisterMotionMode(pkMotionManager.MODE_HORSE);
	for (const auto& it : m_vecMotionHorse)
	{
		snprintf(szFileName, sizeof(szFileName), "%s%s%s", stFolder, "horse/", it.stName);
		pRaceData->RegisterMotionData(pkMotionManager.MODE_HORSE, it.wMotionIndex, szFileName, it.byPercentage);
	}

	std::vector<SMotion> m_vecMotionHorseSword =
	{
		{ pkMotionManager.NAME_COMBO_ATTACK_1, "combo_01.msa", 0 },
		{ pkMotionManager.NAME_COMBO_ATTACK_2, "combo_02.msa", 0 },
		{ pkMotionManager.NAME_COMBO_ATTACK_3, "combo_03.msa", 0 },
		{ HORSE_SKILL_WILDATTACK, "skill_wildattack.msa", 0 },
		{ HORSE_SKILL_SPLASH, "skill_splash.msa", 0 },
	};

	pRaceData->RegisterMotionMode(pkMotionManager.MODE_HORSE_ONEHAND_SWORD);
	for (const auto& it : m_vecMotionHorseSword)
	{
		snprintf(szFileName, sizeof(szFileName), "%s%s%s", stFolder, "horse_onehand_sword/", it.stName);
		pRaceData->RegisterMotionData(pkMotionManager.MODE_HORSE_ONEHAND_SWORD, it.wMotionIndex, szFileName, it.byPercentage);
	}

	pRaceData->ReserveComboAttack(pkMotionManager.MODE_HORSE_ONEHAND_SWORD, COMBO_TYPE_1, 3);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_HORSE_ONEHAND_SWORD, COMBO_TYPE_1, COMBO_INDEX_1, pkMotionManager.NAME_COMBO_ATTACK_1);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_HORSE_ONEHAND_SWORD, COMBO_TYPE_1, COMBO_INDEX_2, pkMotionManager.NAME_COMBO_ATTACK_2);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_HORSE_ONEHAND_SWORD, COMBO_TYPE_1, COMBO_INDEX_3, pkMotionManager.NAME_COMBO_ATTACK_3);

	std::vector<SMotion> m_vecMotionHorseDagger =
	{
		{ pkMotionManager.NAME_COMBO_ATTACK_1, "combo_01.msa", 0 },
		{ pkMotionManager.NAME_COMBO_ATTACK_2, "combo_02.msa", 0 },
		{ pkMotionManager.NAME_COMBO_ATTACK_3, "combo_03.msa", 0 },
		{ HORSE_SKILL_WILDATTACK, "skill_wildattack.msa", 0 },
		{ HORSE_SKILL_SPLASH, "skill_splash.msa", 0 },
	};

	pRaceData->RegisterMotionMode(pkMotionManager.MODE_HORSE_DUALHAND_SWORD);
	for (const auto& it : m_vecMotionHorseDagger)
	{
		snprintf(szFileName, sizeof(szFileName), "%s%s%s", stFolder, "horse_dualhand_sword/", it.stName);
		pRaceData->RegisterMotionData(pkMotionManager.MODE_HORSE_DUALHAND_SWORD, it.wMotionIndex, szFileName, it.byPercentage);
	}

	pRaceData->ReserveComboAttack(pkMotionManager.MODE_HORSE_DUALHAND_SWORD, COMBO_TYPE_1, 3);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_HORSE_DUALHAND_SWORD, COMBO_TYPE_1, COMBO_INDEX_1, pkMotionManager.NAME_COMBO_ATTACK_1);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_HORSE_DUALHAND_SWORD, COMBO_TYPE_1, COMBO_INDEX_2, pkMotionManager.NAME_COMBO_ATTACK_2);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_HORSE_DUALHAND_SWORD, COMBO_TYPE_1, COMBO_INDEX_3, pkMotionManager.NAME_COMBO_ATTACK_3);
	
	std::vector<SMotion> m_vecMotionHorseBow =
	{
		{ pkMotionManager.NAME_WAIT, "wait.msa", 90 },
		{ pkMotionManager.NAME_WAIT, "wait_1.msa", 9 },
		{ pkMotionManager.NAME_WAIT, "wait_2.msa", 1 },
		{ pkMotionManager.NAME_RUN, "run.msa", 0 },
		{ pkMotionManager.NAME_DAMAGE, "damage.msa", 0 },
		{ pkMotionManager.NAME_DEAD, "dead.msa", 0 },
		{ pkMotionManager.NAME_COMBO_ATTACK_1, "attack.msa", 0 },
		{ HORSE_SKILL_WILDATTACK, "skill_wildattack.msa", 0 },
		{ HORSE_SKILL_SPLASH, "skill_splash.msa", 0 },
	};

	pRaceData->RegisterMotionMode(pkMotionManager.MODE_HORSE_BOW);
	for (const auto& it : m_vecMotionHorseBow)
	{
		snprintf(szFileName, sizeof(szFileName), "%s%s%s", stFolder, "horse_bow/", it.stName);
		pRaceData->RegisterMotionData(pkMotionManager.MODE_HORSE_BOW, it.wMotionIndex, szFileName, it.byPercentage);
	}

	pRaceData->ReserveComboAttack(pkMotionManager.MODE_HORSE_BOW, COMBO_TYPE_1, 3);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_HORSE_BOW, COMBO_TYPE_1, COMBO_INDEX_1, pkMotionManager.NAME_COMBO_ATTACK_1);

	pRaceData->RegisterAttachingBoneName(CRaceData::PART_WEAPON, "equip_right");
	pRaceData->RegisterAttachingBoneName(CRaceData::PART_WEAPON_LEFT, "equip_left");

#ifdef ENABLE_ACCE_SYSTEM
	pRaceData->RegisterAttachingBoneName(CRaceData::PART_ACCE, "Bip01 Spine2");
#endif
	return true;
}

const bool CPlayerSettingsModule::LoadGameSura(DWORD dwRace, char stFolder[FILE_MAX_NUM])
{
	CRaceManager& pkManager = CRaceManager::Instance();
	pkManager.SelectRace(dwRace);

	if (!LoadGeneralMotion(stFolder))
		return false;

	CRaceData* pRaceData = pkManager.GetSelectedRaceDataPointer();
	if (!pRaceData)
		return false;

	std::vector<SMotion> m_vecMotionGeneral =
	{
		{ pkMotionManager.NAME_COMBO_ATTACK_1, "attack.msa", 50 },
		{ pkMotionManager.NAME_COMBO_ATTACK_1, "attack_1.msa", 50 },
	};

	char szFileName[FILE_MAX_NUM];
	pRaceData->RegisterMotionMode(pkMotionManager.MODE_GENERAL);
	for (const auto& it : m_vecMotionGeneral)
	{
		snprintf(szFileName, sizeof(szFileName), "%s%s%s", stFolder, "general/", it.stName);
		pRaceData->RegisterMotionData(pkMotionManager.MODE_GENERAL, it.wMotionIndex, szFileName, it.byPercentage);
	}

	std::vector<SMotion> m_vecMotionSkill =
	{
		{ GUILD_SKILL_DRAGONBLOOD, "guild_yongsinuipi.msa", 0 },
		{ GUILD_SKILL_DRAGONBLESS, "guild_yongsinuichukbok.msa", 0 },
		{ GUILD_SKILL_BLESSARMOR, "guild_seonghwigap.msa", 0 },
		{ GUILD_SKILL_SPPEDUP, "guild_gasokhwa.msa", 0 },
		{ GUILD_SKILL_DRAGONWRATH, "guild_yongsinuibunno.msa", 0 },
		{ GUILD_SKILL_MAGICUP, "guild_jumunsul.msa", 0 },
	};

	std::vector<std::pair<BYTE, const char*>> m_vecSkillName = {
		{ 1, "swaeryeong" },
		{ 2, "yonggwon" },
		{ 3, "gwigeom" },
		{ 4, "gongpo" },
		{ 5, "jumagap" },
		{ 6, "pabeop" },
		{ 16, "maryeong" },
		{ 17, "hwayeom" },
		{ 18, "muyeong" },
		{ 19, "heuksin" },
		{ 20, "tusok" },
		{ 21, "mahwan" },
	};

	char szSkillName[FILE_MAX_NUM];
	char szSkillAdd[4] = "";
	for (WORD i = 0; i < CPythonSkill::SKILL_EFFECT_COUNT; i++)
	{
		for (auto& it : m_vecSkillName)
		{
			SMotion motion;

			motion.wMotionIndex = pkMotionManager.NAME_SKILL + (i * CPythonSkill::SKILL_GRADEGAP) + it.first;
			motion.byPercentage = 0;

			if (i > 0)
				snprintf(szSkillAdd, sizeof(szSkillAdd), "_%d", i + 1);
			else
				snprintf(szSkillAdd, sizeof(szSkillAdd), "");

			snprintf(motion.stName, sizeof(motion.stName), "%s%s.msa", it.second, szSkillAdd);
			m_vecMotionSkill.push_back(motion);
		}
	}

	pRaceData->RegisterMotionMode(pkMotionManager.MODE_GENERAL);
	for (const auto& it : m_vecMotionSkill)
	{
		snprintf(szFileName, sizeof(szFileName), "%s%s%s", stFolder, "skill/", it.stName);
		pRaceData->RegisterMotionData(pkMotionManager.MODE_GENERAL, it.wMotionIndex, szFileName, it.byPercentage);
	}

	pRaceData->ReserveComboAttack(pkMotionManager.MODE_GENERAL, COMBO_TYPE_1, 1);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_GENERAL, COMBO_TYPE_1, COMBO_INDEX_1, pkMotionManager.NAME_COMBO_ATTACK_1);

	RegisterEmotionAnis(stFolder);

	std::vector<SMotion> m_vecMotionSword =
	{
		{ pkMotionManager.NAME_WAIT, "wait.msa", 0 },
		{ pkMotionManager.NAME_WALK, "walk.msa" , 0 },
		{ pkMotionManager.NAME_RUN, "run.msa" , 0 },
		{ pkMotionManager.NAME_DAMAGE, "damage.msa", 50 },
		{ pkMotionManager.NAME_DAMAGE, "damage_1.msa", 50 },
		{ pkMotionManager.NAME_DAMAGE_BACK, "damage_2.msa", 50 },
		{ pkMotionManager.NAME_DAMAGE_BACK, "damage_3.msa", 50 },
		{ pkMotionManager.NAME_COMBO_ATTACK_1, "combo_01.msa" , 0 },
		{ pkMotionManager.NAME_COMBO_ATTACK_2, "combo_02.msa" , 0 },
		{ pkMotionManager.NAME_COMBO_ATTACK_3, "combo_03.msa" , 0 },
		{ pkMotionManager.NAME_COMBO_ATTACK_4, "combo_04.msa" , 0 },
		{ pkMotionManager.NAME_COMBO_ATTACK_5, "combo_05.msa" , 0 },
		{ pkMotionManager.NAME_COMBO_ATTACK_6, "combo_06.msa" , 0 },
		{ pkMotionManager.NAME_COMBO_ATTACK_7, "combo_07.msa" , 0 },
	};

	pRaceData->RegisterMotionMode(pkMotionManager.MODE_ONEHAND_SWORD);
	for (const auto& it : m_vecMotionSword)
	{
		snprintf(szFileName, sizeof(szFileName), "%s%s%s", stFolder, "onehand_sword/", it.stName);
		pRaceData->RegisterMotionData(pkMotionManager.MODE_ONEHAND_SWORD, it.wMotionIndex, szFileName, it.byPercentage);
	}

	pRaceData->ReserveComboAttack(pkMotionManager.MODE_ONEHAND_SWORD, COMBO_TYPE_1, 4);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_ONEHAND_SWORD, COMBO_TYPE_1, COMBO_INDEX_1, pkMotionManager.NAME_COMBO_ATTACK_1);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_ONEHAND_SWORD, COMBO_TYPE_1, COMBO_INDEX_2, pkMotionManager.NAME_COMBO_ATTACK_2);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_ONEHAND_SWORD, COMBO_TYPE_1, COMBO_INDEX_3, pkMotionManager.NAME_COMBO_ATTACK_3);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_ONEHAND_SWORD, COMBO_TYPE_1, COMBO_INDEX_4, pkMotionManager.NAME_COMBO_ATTACK_4);

	pRaceData->ReserveComboAttack(pkMotionManager.MODE_ONEHAND_SWORD, COMBO_TYPE_2, 5);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_ONEHAND_SWORD, COMBO_TYPE_2, COMBO_INDEX_1, pkMotionManager.NAME_COMBO_ATTACK_1);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_ONEHAND_SWORD, COMBO_TYPE_2, COMBO_INDEX_2, pkMotionManager.NAME_COMBO_ATTACK_2);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_ONEHAND_SWORD, COMBO_TYPE_2, COMBO_INDEX_3, pkMotionManager.NAME_COMBO_ATTACK_3);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_ONEHAND_SWORD, COMBO_TYPE_2, COMBO_INDEX_4, pkMotionManager.NAME_COMBO_ATTACK_5);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_ONEHAND_SWORD, COMBO_TYPE_2, COMBO_INDEX_5, pkMotionManager.NAME_COMBO_ATTACK_7);

	pRaceData->ReserveComboAttack(pkMotionManager.MODE_ONEHAND_SWORD, COMBO_TYPE_3, 6);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_ONEHAND_SWORD, COMBO_TYPE_3, COMBO_INDEX_1, pkMotionManager.NAME_COMBO_ATTACK_1);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_ONEHAND_SWORD, COMBO_TYPE_3, COMBO_INDEX_2, pkMotionManager.NAME_COMBO_ATTACK_2);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_ONEHAND_SWORD, COMBO_TYPE_3, COMBO_INDEX_3, pkMotionManager.NAME_COMBO_ATTACK_3);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_ONEHAND_SWORD, COMBO_TYPE_3, COMBO_INDEX_4, pkMotionManager.NAME_COMBO_ATTACK_5);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_ONEHAND_SWORD, COMBO_TYPE_3, COMBO_INDEX_5, pkMotionManager.NAME_COMBO_ATTACK_6);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_ONEHAND_SWORD, COMBO_TYPE_3, COMBO_INDEX_6, pkMotionManager.NAME_COMBO_ATTACK_4);

	std::vector<SMotion> m_vecMotionFishing =
	{
		{ pkMotionManager.NAME_WAIT, "wait.msa", 0 },
		{ pkMotionManager.NAME_WALK, "walk.msa", 0 },
		{ pkMotionManager.NAME_RUN, "run.msa", 0 },
		{ pkMotionManager.NAME_FISHING_THROW, "throw.msa", 0 },
		{ pkMotionManager.NAME_FISHING_WAIT, "fishing_wait.msa", 0 },
		{ pkMotionManager.NAME_FISHING_STOP, "fishing_cancel.msa", 0 },
		{ pkMotionManager.NAME_FISHING_REACT, "fishing_react.msa", 0 },
		{ pkMotionManager.NAME_FISHING_CATCH, "fishing_catch.msa", 0 },
		{ pkMotionManager.NAME_FISHING_FAIL, "fishing_fail.msa", 0 },
	};

	pRaceData->RegisterMotionMode(pkMotionManager.MODE_FISHING);
	for (const auto& it : m_vecMotionFishing)
	{
		snprintf(szFileName, sizeof(szFileName), "%s%s%s", stFolder, "fishing/", it.stName);
		pRaceData->RegisterMotionData(pkMotionManager.MODE_FISHING, it.wMotionIndex, szFileName, it.byPercentage);
	}

	std::vector<SMotion> m_vecMotionHorse =
	{
		{ pkMotionManager.NAME_WAIT, "wait.msa", 90 },
		{ pkMotionManager.NAME_WAIT, "wait_1.msa", 9 },
		{ pkMotionManager.NAME_WAIT, "wait_2.msa", 1 },
		{ pkMotionManager.NAME_WALK, "walk.msa", 0 },
		{ pkMotionManager.NAME_RUN, "run.msa", 0 },
		{ pkMotionManager.NAME_DAMAGE, "damage.msa", 0 },
		{ pkMotionManager.NAME_DAMAGE_BACK, "damage.msa", 0 },
		{ pkMotionManager.NAME_DEAD, "dead.msa", 0 },
		{ HORSE_SKILL_CHARGE, "skill_charge.msa", 0 },
		{ HORSE_SKILL_CHARGE, "skill_splash.msa", 0 },
	};

	pRaceData->RegisterMotionMode(pkMotionManager.MODE_HORSE);
	for (const auto& it : m_vecMotionHorse)
	{
		snprintf(szFileName, sizeof(szFileName), "%s%s%s", stFolder, "horse/", it.stName);
		pRaceData->RegisterMotionData(pkMotionManager.MODE_HORSE, it.wMotionIndex, szFileName, it.byPercentage);
	}

	std::vector<SMotion> m_vecMotionHorseSword =
	{
		{ pkMotionManager.NAME_COMBO_ATTACK_1, "combo_01.msa", 0 },
		{ pkMotionManager.NAME_COMBO_ATTACK_2, "combo_02.msa", 0 },
		{ pkMotionManager.NAME_COMBO_ATTACK_3, "combo_03.msa", 0 },
		{ HORSE_SKILL_WILDATTACK, "skill_wildattack.msa", 0 },
	};

	pRaceData->RegisterMotionMode(pkMotionManager.MODE_HORSE_ONEHAND_SWORD);
	for (const auto& it : m_vecMotionHorseSword)
	{
		snprintf(szFileName, sizeof(szFileName), "%s%s%s", stFolder, "horse_onehand_sword/", it.stName);
		pRaceData->RegisterMotionData(pkMotionManager.MODE_HORSE_ONEHAND_SWORD, it.wMotionIndex, szFileName, it.byPercentage);
	}

	pRaceData->ReserveComboAttack(pkMotionManager.MODE_HORSE_ONEHAND_SWORD, COMBO_TYPE_1, 3);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_HORSE_ONEHAND_SWORD, COMBO_TYPE_1, COMBO_INDEX_1, pkMotionManager.NAME_COMBO_ATTACK_1);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_HORSE_ONEHAND_SWORD, COMBO_TYPE_1, COMBO_INDEX_2, pkMotionManager.NAME_COMBO_ATTACK_2);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_HORSE_ONEHAND_SWORD, COMBO_TYPE_1, COMBO_INDEX_3, pkMotionManager.NAME_COMBO_ATTACK_3);

	pRaceData->RegisterAttachingBoneName(CRaceData::PART_WEAPON, "equip_right");

#ifdef ENABLE_ACCE_SYSTEM
	pRaceData->RegisterAttachingBoneName(CRaceData::PART_ACCE, "Bip01 Spine2");
#endif

	return true;
}

const bool CPlayerSettingsModule::LoadGameShaman(DWORD dwRace, char stFolder[FILE_MAX_NUM])
{
	CRaceManager& pkManager = CRaceManager::Instance();
	pkManager.SelectRace(dwRace);

	if (!LoadGeneralMotion(stFolder))
		return false;

	CRaceData* pRaceData = pkManager.GetSelectedRaceDataPointer();
	if (!pRaceData)
		return false;

	std::vector<SMotion> m_vecMotionGeneral =
	{
		{ pkMotionManager.NAME_COMBO_ATTACK_1, "attack.msa", 50 },
		{ pkMotionManager.NAME_COMBO_ATTACK_1, "attack_1.msa", 50 },
	};

	char szFileName[FILE_MAX_NUM];
	pRaceData->RegisterMotionMode(pkMotionManager.MODE_GENERAL);
	for (const auto& it : m_vecMotionGeneral)
	{
		snprintf(szFileName, sizeof(szFileName), "%s%s%s", stFolder, "general/", it.stName);
		pRaceData->RegisterMotionData(pkMotionManager.MODE_GENERAL, it.wMotionIndex, szFileName, it.byPercentage);
	}

	std::vector<SMotion> m_vecMotionSkill =
	{
		{ pkMotionManager.NAME_SKILL + 1, "bipabu.msa" },
		{ pkMotionManager.NAME_SKILL + 2, "yongpa.msa" },
		{ pkMotionManager.NAME_SKILL + 3, "paeryong.msa" },
		{ pkMotionManager.NAME_SKILL + 4, "hosin_target.msa" },
		{ pkMotionManager.NAME_SKILL + 5, "boho_target.msa" },
		{ pkMotionManager.NAME_SKILL + 6, "gicheon_target.msa" },		
		{ pkMotionManager.NAME_SKILL + 16, "noejeon.msa" },
		{ pkMotionManager.NAME_SKILL + 17, "byeorak.msa" },
		{ pkMotionManager.NAME_SKILL + 18, "pokroe.msa" },
		{ pkMotionManager.NAME_SKILL + 19, "jeongeop_target.msa" },
		{ pkMotionManager.NAME_SKILL + 20, "kwaesok_target.msa" },
		{ pkMotionManager.NAME_SKILL + 21, "jeungryeok_target.msa" },
		{ GUILD_SKILL_DRAGONBLOOD, "guild_yongsinuipi.msa", 0 },
		{ GUILD_SKILL_DRAGONBLESS, "guild_yongsinuichukbok.msa", 0 },
		{ GUILD_SKILL_BLESSARMOR, "guild_seonghwigap.msa", 0 },
		{ GUILD_SKILL_SPPEDUP, "guild_gasokhwa.msa", 0 },
		{ GUILD_SKILL_DRAGONWRATH, "guild_yongsinuibunno.msa", 0 },
		{ GUILD_SKILL_MAGICUP, "guild_jumunsul.msa", 0 },
	};

	std::vector<std::pair<BYTE, const char*>> m_vecSkillName = {
		{ 1, "bipabu" },
		{ 2, "yongpa" },
		{ 3, "paeryong" },
		{ 4, "hosin" },
		{ 5, "boho" },
		{ 6, "gicheon" },
		{ 16, "noejeon" },
		{ 17, "byeorak" },
		{ 18, "pokroe" },
		{ 19, "jeongeop" },
		{ 20, "kwaesok" },
		{ 21, "jeungryeok" },
	};

	char szSkillName[FILE_MAX_NUM];
	char szSkillAdd[4] = "";
	for (WORD i = 1; i < CPythonSkill::SKILL_EFFECT_COUNT; i++)
	{
		for (auto& it : m_vecSkillName)
		{
			SMotion motion;

			motion.wMotionIndex = pkMotionManager.NAME_SKILL + (i * CPythonSkill::SKILL_GRADEGAP) + it.first;
			motion.byPercentage = 0;

			snprintf(szSkillAdd, sizeof(szSkillAdd), "_%d", i + 1);
			snprintf(motion.stName, sizeof(motion.stName), "%s%s.msa", it.second, szSkillAdd);
			m_vecMotionSkill.push_back(motion);
		}
	}

	pRaceData->RegisterMotionMode(pkMotionManager.MODE_GENERAL);
	for (const auto& it : m_vecMotionSkill)
	{
		snprintf(szFileName, sizeof(szFileName), "%s%s%s", stFolder, "skill/", it.stName);
		pRaceData->RegisterMotionData(pkMotionManager.MODE_GENERAL, it.wMotionIndex, szFileName, it.byPercentage);
	}

	pRaceData->ReserveComboAttack(pkMotionManager.MODE_GENERAL, COMBO_TYPE_1, 1);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_GENERAL, COMBO_TYPE_1, COMBO_INDEX_1, pkMotionManager.NAME_COMBO_ATTACK_1);

	RegisterEmotionAnis(stFolder);

	std::vector<SMotion> m_vecMotionFan =
	{
		{ pkMotionManager.NAME_WAIT, "wait.msa", 0 },
		{ pkMotionManager.NAME_WALK, "walk.msa", 0 },
		{ pkMotionManager.NAME_RUN, "run.msa", 0 },
		{ pkMotionManager.NAME_DAMAGE, "damage.msa", 50,},
		{ pkMotionManager.NAME_DAMAGE, "damage_1.msa", 50, },
		{ pkMotionManager.NAME_DAMAGE_BACK, "damage_2.msa", 50,},
		{ pkMotionManager.NAME_DAMAGE_BACK, "damage_3.msa", 50, },
		{ pkMotionManager.NAME_COMBO_ATTACK_1, "combo_01.msa", 0 },
		{ pkMotionManager.NAME_COMBO_ATTACK_2, "combo_02.msa", 0 },
		{ pkMotionManager.NAME_COMBO_ATTACK_3, "combo_03.msa", 0 },
		{ pkMotionManager.NAME_COMBO_ATTACK_4, "combo_04.msa", 0 },
		{ pkMotionManager.NAME_COMBO_ATTACK_5, "combo_05.msa", 0 },
		{ pkMotionManager.NAME_COMBO_ATTACK_6, "combo_06.msa", 0 },
		{ pkMotionManager.NAME_COMBO_ATTACK_7, "combo_07.msa", 0 },
	};

	pRaceData->RegisterMotionMode(pkMotionManager.MODE_FAN);
	for (const auto& it : m_vecMotionFan)
	{
		snprintf(szFileName, sizeof(szFileName), "%s%s%s", stFolder, "fan/", it.stName);
		pRaceData->RegisterMotionData(pkMotionManager.MODE_FAN, it.wMotionIndex, szFileName, it.byPercentage);
	}

	pRaceData->ReserveComboAttack(pkMotionManager.MODE_FAN, COMBO_TYPE_1, 4);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_FAN, COMBO_TYPE_1, COMBO_INDEX_1, pkMotionManager.NAME_COMBO_ATTACK_1);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_FAN, COMBO_TYPE_1, COMBO_INDEX_2, pkMotionManager.NAME_COMBO_ATTACK_2);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_FAN, COMBO_TYPE_1, COMBO_INDEX_3, pkMotionManager.NAME_COMBO_ATTACK_3);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_FAN, COMBO_TYPE_1, COMBO_INDEX_4, pkMotionManager.NAME_COMBO_ATTACK_4);

	pRaceData->ReserveComboAttack(pkMotionManager.MODE_FAN, COMBO_TYPE_2, 5);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_FAN, COMBO_TYPE_2, COMBO_INDEX_1, pkMotionManager.NAME_COMBO_ATTACK_1);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_FAN, COMBO_TYPE_2, COMBO_INDEX_2, pkMotionManager.NAME_COMBO_ATTACK_2);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_FAN, COMBO_TYPE_2, COMBO_INDEX_3, pkMotionManager.NAME_COMBO_ATTACK_3);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_FAN, COMBO_TYPE_2, COMBO_INDEX_4, pkMotionManager.NAME_COMBO_ATTACK_5);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_FAN, COMBO_TYPE_2, COMBO_INDEX_5, pkMotionManager.NAME_COMBO_ATTACK_7);

	pRaceData->ReserveComboAttack(pkMotionManager.MODE_FAN, COMBO_TYPE_3, 6);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_FAN, COMBO_TYPE_3, COMBO_INDEX_1, pkMotionManager.NAME_COMBO_ATTACK_1);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_FAN, COMBO_TYPE_3, COMBO_INDEX_2, pkMotionManager.NAME_COMBO_ATTACK_2);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_FAN, COMBO_TYPE_3, COMBO_INDEX_3, pkMotionManager.NAME_COMBO_ATTACK_3);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_FAN, COMBO_TYPE_3, COMBO_INDEX_4, pkMotionManager.NAME_COMBO_ATTACK_5);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_FAN, COMBO_TYPE_3, COMBO_INDEX_5, pkMotionManager.NAME_COMBO_ATTACK_6);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_FAN, COMBO_TYPE_3, COMBO_INDEX_6, pkMotionManager.NAME_COMBO_ATTACK_4);	
	
	std::vector<SMotion> m_vecMotionBell =
	{
		{ pkMotionManager.NAME_WAIT, "wait.msa", 0 },
		{ pkMotionManager.NAME_WALK, "walk.msa", 0 },
		{ pkMotionManager.NAME_RUN, "run.msa", 0 },
		{ pkMotionManager.NAME_DAMAGE, "damage.msa", 50,},
		{ pkMotionManager.NAME_DAMAGE, "damage_1.msa", 50, },
		{ pkMotionManager.NAME_DAMAGE_BACK, "damage_2.msa", 50,},
		{ pkMotionManager.NAME_DAMAGE_BACK, "damage_3.msa", 50, },
		{ pkMotionManager.NAME_COMBO_ATTACK_1, "combo_01.msa", 0 },
		{ pkMotionManager.NAME_COMBO_ATTACK_2, "combo_02.msa", 0 },
		{ pkMotionManager.NAME_COMBO_ATTACK_3, "combo_03.msa", 0 },
		{ pkMotionManager.NAME_COMBO_ATTACK_4, "combo_04.msa", 0 },
		{ pkMotionManager.NAME_COMBO_ATTACK_5, "combo_05.msa", 0 },
		{ pkMotionManager.NAME_COMBO_ATTACK_6, "combo_06.msa", 0 },
		{ pkMotionManager.NAME_COMBO_ATTACK_7, "combo_07.msa", 0 },
	};

	pRaceData->RegisterMotionMode(pkMotionManager.MODE_BELL);
	for (const auto& it : m_vecMotionBell)
	{
		snprintf(szFileName, sizeof(szFileName), "%s%s%s", stFolder, "bell/", it.stName);
		pRaceData->RegisterMotionData(pkMotionManager.MODE_BELL, it.wMotionIndex, szFileName, it.byPercentage);
	}

	pRaceData->ReserveComboAttack(pkMotionManager.MODE_BELL, COMBO_TYPE_1, 4);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_BELL, COMBO_TYPE_1, COMBO_INDEX_1, pkMotionManager.NAME_COMBO_ATTACK_1);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_BELL, COMBO_TYPE_1, COMBO_INDEX_2, pkMotionManager.NAME_COMBO_ATTACK_2);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_BELL, COMBO_TYPE_1, COMBO_INDEX_3, pkMotionManager.NAME_COMBO_ATTACK_3);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_BELL, COMBO_TYPE_1, COMBO_INDEX_4, pkMotionManager.NAME_COMBO_ATTACK_4);

	pRaceData->ReserveComboAttack(pkMotionManager.MODE_BELL, COMBO_TYPE_2, 5);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_BELL, COMBO_TYPE_2, COMBO_INDEX_1, pkMotionManager.NAME_COMBO_ATTACK_1);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_BELL, COMBO_TYPE_2, COMBO_INDEX_2, pkMotionManager.NAME_COMBO_ATTACK_2);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_BELL, COMBO_TYPE_2, COMBO_INDEX_3, pkMotionManager.NAME_COMBO_ATTACK_3);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_BELL, COMBO_TYPE_2, COMBO_INDEX_4, pkMotionManager.NAME_COMBO_ATTACK_5);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_BELL, COMBO_TYPE_2, COMBO_INDEX_5, pkMotionManager.NAME_COMBO_ATTACK_7);

	pRaceData->ReserveComboAttack(pkMotionManager.MODE_BELL, COMBO_TYPE_3, 6);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_BELL, COMBO_TYPE_3, COMBO_INDEX_1, pkMotionManager.NAME_COMBO_ATTACK_1);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_BELL, COMBO_TYPE_3, COMBO_INDEX_2, pkMotionManager.NAME_COMBO_ATTACK_2);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_BELL, COMBO_TYPE_3, COMBO_INDEX_3, pkMotionManager.NAME_COMBO_ATTACK_3);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_BELL, COMBO_TYPE_3, COMBO_INDEX_4, pkMotionManager.NAME_COMBO_ATTACK_5);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_BELL, COMBO_TYPE_3, COMBO_INDEX_5, pkMotionManager.NAME_COMBO_ATTACK_6);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_BELL, COMBO_TYPE_3, COMBO_INDEX_6, pkMotionManager.NAME_COMBO_ATTACK_4);

	std::vector<SMotion> m_vecMotionFishing =
	{
		{ pkMotionManager.NAME_WAIT, "wait.msa", 0 },
		{ pkMotionManager.NAME_WALK, "walk.msa", 0 },
		{ pkMotionManager.NAME_RUN, "run.msa", 0 },
		{ pkMotionManager.NAME_FISHING_THROW, "throw.msa", 0 },
		{ pkMotionManager.NAME_FISHING_WAIT, "fishing_wait.msa", 0 },
		{ pkMotionManager.NAME_FISHING_STOP, "fishing_cancel.msa", 0 },
		{ pkMotionManager.NAME_FISHING_REACT, "fishing_react.msa", 0 },
		{ pkMotionManager.NAME_FISHING_CATCH, "fishing_catch.msa", 0 },
		{ pkMotionManager.NAME_FISHING_FAIL, "fishing_fail.msa", 0 },
	};

	pRaceData->RegisterMotionMode(pkMotionManager.MODE_FISHING);
	for (const auto& it : m_vecMotionFishing)
	{
		snprintf(szFileName, sizeof(szFileName), "%s%s%s", stFolder, "fishing/", it.stName);
		pRaceData->RegisterMotionData(pkMotionManager.MODE_FISHING, it.wMotionIndex, szFileName, it.byPercentage);
	}

	std::vector<SMotion> m_vecMotionHorse =
	{
		{ pkMotionManager.NAME_WAIT, "wait.msa", 90 },
		{ pkMotionManager.NAME_WAIT, "wait_1.msa", 9 },
		{ pkMotionManager.NAME_WAIT, "wait_2.msa", 1 },
		{ pkMotionManager.NAME_WALK, "walk.msa", 0 },
		{ pkMotionManager.NAME_RUN, "run.msa", 0 },
		{ pkMotionManager.NAME_DAMAGE, "damage.msa", 0 },
		{ pkMotionManager.NAME_DAMAGE_BACK, "damage.msa", 0 },
		{ pkMotionManager.NAME_DEAD, "dead.msa", 0 },
		{ HORSE_SKILL_CHARGE, "skill_charge.msa", 0 },
		{ HORSE_SKILL_CHARGE, "skill_splash.msa", 0 },
	};

	pRaceData->RegisterMotionMode(pkMotionManager.MODE_HORSE);
	for (const auto& it : m_vecMotionHorse)
	{
		snprintf(szFileName, sizeof(szFileName), "%s%s%s", stFolder, "horse/", it.stName);
		pRaceData->RegisterMotionData(pkMotionManager.MODE_HORSE, it.wMotionIndex, szFileName, it.byPercentage);
	}

	std::vector<SMotion> m_vecMotionHorseFan =
	{
		{ pkMotionManager.NAME_COMBO_ATTACK_1, "combo_01.msa", 0 },
		{ pkMotionManager.NAME_COMBO_ATTACK_2, "combo_02.msa", 0 },
		{ pkMotionManager.NAME_COMBO_ATTACK_3, "combo_03.msa", 0 },
		{ HORSE_SKILL_WILDATTACK, "skill_wildattack.msa", 0 },
	};

	pRaceData->RegisterMotionMode(pkMotionManager.MODE_HORSE_FAN);
	for (const auto& it : m_vecMotionHorseFan)
	{
		snprintf(szFileName, sizeof(szFileName), "%s%s%s", stFolder, "horse_fan/", it.stName);
		pRaceData->RegisterMotionData(pkMotionManager.MODE_HORSE_FAN, it.wMotionIndex, szFileName, it.byPercentage);
	}

	pRaceData->ReserveComboAttack(pkMotionManager.MODE_HORSE_FAN, COMBO_TYPE_1, 3);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_HORSE_FAN, COMBO_TYPE_1, COMBO_INDEX_1, pkMotionManager.NAME_COMBO_ATTACK_1);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_HORSE_FAN, COMBO_TYPE_1, COMBO_INDEX_2, pkMotionManager.NAME_COMBO_ATTACK_2);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_HORSE_FAN, COMBO_TYPE_1, COMBO_INDEX_3, pkMotionManager.NAME_COMBO_ATTACK_3);	
	
	std::vector<SMotion> m_vecMotionHorseBell =
	{
		{ pkMotionManager.NAME_COMBO_ATTACK_1, "combo_01.msa", 0 },
		{ pkMotionManager.NAME_COMBO_ATTACK_2, "combo_02.msa", 0 },
		{ pkMotionManager.NAME_COMBO_ATTACK_3, "combo_03.msa", 0 },
		{ HORSE_SKILL_WILDATTACK, "skill_wildattack.msa", 0 },
	};

	pRaceData->RegisterMotionMode(pkMotionManager.MODE_HORSE_BELL);
	for (const auto& it : m_vecMotionHorseBell)
	{
		snprintf(szFileName, sizeof(szFileName), "%s%s%s", stFolder, "horse_bell/", it.stName);
		pRaceData->RegisterMotionData(pkMotionManager.MODE_HORSE_BELL, it.wMotionIndex, szFileName, it.byPercentage);
	}

	pRaceData->ReserveComboAttack(pkMotionManager.MODE_HORSE_BELL, COMBO_TYPE_1, 3);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_HORSE_BELL, COMBO_TYPE_1, COMBO_INDEX_1, pkMotionManager.NAME_COMBO_ATTACK_1);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_HORSE_BELL, COMBO_TYPE_1, COMBO_INDEX_2, pkMotionManager.NAME_COMBO_ATTACK_2);
	pRaceData->RegisterComboAttack(pkMotionManager.MODE_HORSE_BELL, COMBO_TYPE_1, COMBO_INDEX_3, pkMotionManager.NAME_COMBO_ATTACK_3);

	pRaceData->RegisterAttachingBoneName(CRaceData::PART_WEAPON, "equip_right");
	pRaceData->RegisterAttachingBoneName(CRaceData::PART_WEAPON_LEFT, "equip_left");

#ifdef ENABLE_ACCE_SYSTEM
	pRaceData->RegisterAttachingBoneName(CRaceData::PART_ACCE, "Bip01 Spine2");
#endif

	return true;
}

const bool CPlayerSettingsModule::LoadGameSound()
{
	std::vector<TSound> m_vecSound = {
		{ CPythonItem::USESOUND_DEFAULT, "sound/ui/drop.wav" },
		{ CPythonItem::USESOUND_ACCESSORY, "sound/ui/equip_ring_amulet.wav" },
		{ CPythonItem::USESOUND_ARMOR, "sound/ui/equip_metal_armor.wav" },
		{ CPythonItem::USESOUND_BOW, "sound/ui/equip_bow.wav" },
		{ CPythonItem::USESOUND_WEAPON, "sound/ui/equip_metal_weapon.wav" },
		{ CPythonItem::USESOUND_POTION, "sound/ui/eat_potion.wav" },
		{ CPythonItem::USESOUND_PORTAL, "sound/ui/potal_scroll.wav" },
	};
	
	CPythonItem& rkItem = CPythonItem::Instance();

	for (const auto &it : m_vecSound)
		rkItem.SetUseSoundFileName(it.dwType, it.stName);	
	
	std::vector<TSound> m_vecDropSound = {
		{ CPythonItem::DROPSOUND_DEFAULT, "sound/ui/drop.wav" },
		{ CPythonItem::DROPSOUND_ACCESSORY, "sound/ui/equip_ring_amulet.wav" },
		{ CPythonItem::DROPSOUND_ARMOR, "sound/ui/equip_metal_armor.wav" },
		{ CPythonItem::DROPSOUND_BOW, "sound/ui/equip_bow.wav" },
		{ CPythonItem::DROPSOUND_WEAPON, "sound/ui/equip_metal_weapon.wav" },
	};
	
	for (const auto &it : m_vecDropSound)
		rkItem.SetDropSoundFileName(it.dwType, it.stName);

	return true;
}

const bool CPlayerSettingsModule::LoadGameSkill()
{
	return true;
}

PyObject* cpsmInitData(PyObject* poSelf, PyObject* poArgs)
{
	CPlayerSettingsModule::LoadInitData();
	return Py_BuildNone();
}

PyObject* cpsmLoadGameSound(PyObject* poSelf, PyObject* poArgs)
{
	CPlayerSettingsModule::LoadGameSound();
	return Py_BuildNone();
}

PyObject* cpsmLoadGameEffect(PyObject* poSelf, PyObject* poArgs)
{
	CPlayerSettingsModule::LoadGameEffect();
	return Py_BuildNone();
}

PyObject* cpsmLoadGameWarrior(PyObject* poSelf, PyObject* poArgs)
{
	CPlayerSettingsModule::LoadGameWarrior(CPlayerSettingsModule::RACE_WARRIOR_M, "d:/ymir work/pc/warrior/");
	CPlayerSettingsModule::LoadGameWarrior(CPlayerSettingsModule::RACE_WARRIOR_W, "d:/ymir work/pc2/warrior/");
	return Py_BuildNone();
}

PyObject* cpsmLoadGameAssassin(PyObject* poSelf, PyObject* poArgs)
{
	CPlayerSettingsModule::LoadGameAssassin(CPlayerSettingsModule::RACE_ASSASSIN_W, "d:/ymir work/pc/assassin/");
	CPlayerSettingsModule::LoadGameAssassin(CPlayerSettingsModule::RACE_ASSASSIN_M, "d:/ymir work/pc2/assassin/");
	return Py_BuildNone();
}

PyObject* cpsmLoadGameSura(PyObject* poSelf, PyObject* poArgs)
{
	CPlayerSettingsModule::LoadGameSura(CPlayerSettingsModule::RACE_SURA_M, "d:/ymir work/pc/sura/");
	CPlayerSettingsModule::LoadGameSura(CPlayerSettingsModule::RACE_SURA_W, "d:/ymir work/pc2/sura/");
	return Py_BuildNone();
}

PyObject* cpsmLoadGameShaman(PyObject* poSelf, PyObject* poArgs)
{
	CPlayerSettingsModule::LoadGameShaman(CPlayerSettingsModule::RACE_SHAMAN_W, "d:/ymir work/pc/shaman/");
	CPlayerSettingsModule::LoadGameShaman(CPlayerSettingsModule::RACE_SHAMAN_M, "d:/ymir work/pc2/shaman/");
	return Py_BuildNone();
}

PyObject* cpsmLoadGameSkill(PyObject* poSelf, PyObject* poArgs)
{
	CPlayerSettingsModule::LoadGameSkill();
	return Py_BuildNone();
}

void initplayersettingsmodule()
{
	static PyMethodDef s_methods[] =
	{
		{ "InitData",					cpsmInitData,						METH_VARARGS },
		{ "LoadGameSound",				cpsmLoadGameSound,					METH_VARARGS },
		{ "LoadGameEffect",				cpsmLoadGameEffect,					METH_VARARGS },
		{ "LoadGameWarrior",			cpsmLoadGameWarrior,				METH_VARARGS },
		{ "LoadGameAssassin",			cpsmLoadGameAssassin,				METH_VARARGS },
		{ "LoadGameSura",				cpsmLoadGameSura,					METH_VARARGS },
		{ "LoadGameShaman",				cpsmLoadGameShaman,					METH_VARARGS },
		{ "LoadGameSkill",				cpsmLoadGameSkill,					METH_VARARGS },


		{ NULL,								NULL,								NULL		 },
	};

	PyObject* poModule = Py_InitModule("cpsm", s_methods);
}
#endif