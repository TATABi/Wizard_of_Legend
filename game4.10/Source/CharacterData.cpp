#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"
#include "CharacterData.h"

namespace game_framework {

	CharacterData& CharacterData::Instance()
	{
		static CharacterData instance;
		return instance;
	}

	CharacterData::CharacterData()
	{
		_money = 0;
		_diamond = 0;
		_hp = 500;
		_max_hp = 500;
		_mp = 0;
		_max_mp = 100;
		_attack_coefficient = 1;
		_defense_coefficient = 1;
		_blood_suck_coefficient = 0;
		_move_coefficient = 1;
		_cd_coefficient = 1;
		_mp_charge_coefficient = 0.8;
		_isInvincible = false;
		_isLockHP = false;
		_stage = _money_found = _diamond_collected = _enemies_defeated = 0;
		_isAttackBuff = _isSpeedBuff = _isCooldownBuff = false;
		_isSuperMode = false;
	}

	//--------------------�]�w��--------------------//

	void CharacterData::AddMoney(int d_money)
	{
		_money += d_money;
		_money > 999 ? _money = 999 : NULL;
		_money < 0 ? _money = 0 : NULL;
	}

	void CharacterData::SetMoney(int money)
	{
		_money = money;
		_money > 999 ? _money = 999 : NULL;
		_money < 0 ? _money = 0 : NULL;
	}

	void CharacterData::AddDiamond(int d_diamond)
	{
		_diamond += d_diamond;
		_diamond > 999 ? _diamond = 999 : NULL;
		_diamond < 0 ? _diamond = 0 : NULL;
	}

	void CharacterData::SetDiamond(int diamond)
	{
		_diamond = diamond;
		_diamond > 999 ? _diamond = 999 : NULL;
		_diamond < 0 ? _diamond = 0 : NULL;
	}

	void CharacterData::AddHP(int d_hp)
	{
		if (!_isLockHP || d_hp >= 0)
		{
			_isInvincible && d_hp < 0 ? d_hp = 0 : NULL;
			_hp += d_hp;
			_hp > _max_hp ? _hp = _max_hp : NULL;
			_hp < 0 ? _hp = 0 : NULL;
		}
	}

	void CharacterData::SetHP(int hp)
	{
		_hp = hp;
		_hp > _max_hp ? _hp = _max_hp : NULL;
		_hp < 0 ? _hp = 0 : NULL;
	}

	void CharacterData::AddMaxHP(int d_max_hp)
	{
		_max_hp += d_max_hp;
		_max_hp < 0 ? _max_hp = 0 : NULL;
		_hp > _max_hp ? _hp = _max_hp : NULL;
	}

	void CharacterData::SetMaxHP(int max_hp)
	{
		_max_hp = max_hp;
		_max_hp < 0 ? _max_hp = 0 : NULL;
		_hp > _max_hp ? _hp = _max_hp : NULL;
	}

	void CharacterData::AddMP(int d_mp)
	{
		if (!_isMagicBuff)
			_mp += d_mp;
		else
			d_mp < 0 ? _mp += d_mp : NULL;

		_mp > _max_mp ? _mp = _max_mp, _isMagicBuff = true : NULL;
		_mp <= 0 ? (_mp = 0, _isMagicBuff = false) : NULL;
	}

	void CharacterData::AttackBuff(bool isOpened)
	{
		if (isOpened)
			_isAttackBuff ? NULL : (SetAttackCoefficient(1.3), _isAttackBuff = true);
		else
			_isAttackBuff ? (SetAttackCoefficient(-1.3), _isAttackBuff = false) : NULL;
	}

	void CharacterData::SpeedBuff(bool isOpened)
	{
		if (isOpened)
			_isSpeedBuff ? NULL : (SetMoveCoefficient(1.3), _isSpeedBuff = true);
		else
			_isSpeedBuff ? (SetMoveCoefficient(-1.3), _isSpeedBuff = false) : NULL;
	}

	void CharacterData::CooldownBuff(bool isOpened)
	{
		if (isOpened)
			_isCooldownBuff ? NULL : (SetCDCoefficient(0.7), _isCooldownBuff = true);
		else
			_isCooldownBuff ? (SetCDCoefficient(-0.7), _isCooldownBuff = false) : NULL;
	}

	void CharacterData::SetAttackCoefficient(float coefficient)
	{
		coefficient >= 0 ? _attack_coefficient *= coefficient : _attack_coefficient /= (-coefficient);
	}

	void CharacterData::SetDefenseCoefficient(float coefficient)
	{
		coefficient >= 0 ? _defense_coefficient *= coefficient : _defense_coefficient /= (-coefficient);
	}

	void CharacterData::SetBloodSuckCoefficient(float coefficient)
	{
		coefficient >= 0 ? _blood_suck_coefficient *= coefficient : _blood_suck_coefficient /= (-coefficient);
	}

	void CharacterData::SetMoveCoefficient(float coefficient)
	{
		coefficient >= 0 ? _move_coefficient *= coefficient : _move_coefficient /= (-coefficient);
	}

	void CharacterData::SetCDCoefficient(float coefficient)
	{
		coefficient >= 0 ? _cd_coefficient *= coefficient : _cd_coefficient /= (-coefficient);
	}

	void CharacterData::SetMPChargeCoefficient(float coefficient)
	{
		coefficient >= 0 ? _mp_charge_coefficient *= coefficient : _mp_charge_coefficient /= (-coefficient);
	}

	void CharacterData::SetInvincible(bool isInvincible)
	{
		_isInvincible = isInvincible;
	}

	void CharacterData::ResetStatus()
	{
		_hp = _max_hp;
		_isMagicBuff = false;
		_mp = _money = _stage = _money_found = _diamond_collected = _enemies_defeated = 0;
		AttackBuff(false);
		SpeedBuff(false);
		CooldownBuff(false);
		_isSuperMode ? SuperMode(false) : NULL;
	}

	void CharacterData::SetMagicBuff(bool isBuff)
	{
		_isMagicBuff = isBuff;
	}

	vector<int> CharacterData::GetStageResult()
	{
		vector<int> result;
		result.push_back(_stage);
		result.push_back(_money_found);
		result.push_back(_diamond_collected);
		result.push_back(_enemies_defeated);

		return result;
	}

	void CharacterData::SetStage(int stage)
	{
		_stage = stage;
	}

	void CharacterData::AddMoneyCollected(int gold)
	{
		_money_found += gold;
	}

	void CharacterData::AddDiamondCollected(int diamond)
	{
		_diamond_collected += diamond;
	}
	
	void CharacterData::AddEnemiesDefeated(int num)
	{
		_enemies_defeated += num;
	}

	//-------------------Cheat--------------------//

	void CharacterData::LockHP(bool isOpen)
	{
		isOpen ? _isLockHP = true : _isLockHP = false;
	}

	void CharacterData::SuperMode(bool isOpen)
	{
		int flag;
		isOpen ? flag = 1 : flag = -1;
		LockHP(isOpen);
		SetAttackCoefficient(100 * flag);
		AddMoney(999 * flag);
		AddDiamond(999 * flag); 
		_isSuperMode = isOpen;
	}

	//--------------------����--------------------//

	int CharacterData::MONEY() { return _money; }

	int CharacterData::DIAMOND() { return _diamond; }

	int CharacterData::HP() { return _hp; }

	int CharacterData::MAX_HP() { return _max_hp; }

	int CharacterData::MP() { return _mp; }

	int CharacterData::MAX_MP() { return _max_mp; }

	float CharacterData::ATTACK_COEFFICIENT() { return _attack_coefficient; }

	float CharacterData::DEFENSE_COEFFICIENT() { return _defense_coefficient; }

	float CharacterData::BLOOD_SUCK_COEFFICIENT() { return _blood_suck_coefficient; }

	float CharacterData::MOVE_COEFFICIENT() { return _move_coefficient; }

	float CharacterData::CD_COEFFICIENT() { return _cd_coefficient; }

	float CharacterData::MP_CHARGE_COEFFICIENT() { return _mp_charge_coefficient; }

	bool CharacterData::ISVINCIBLE() { return _isInvincible; }

	bool CharacterData::ISMAGICBUFF() { return _isMagicBuff; }

	bool CharacterData::ISATTACKBUFF() { return _isAttackBuff; }

	bool CharacterData::ISSPEEDBUFF() { return _isSpeedBuff; }

	bool CharacterData::ISCOOLDOWNBUFF() { return _isCooldownBuff; }

	bool CharacterData::ISSUPERMODE() { return _isSuperMode; }
}