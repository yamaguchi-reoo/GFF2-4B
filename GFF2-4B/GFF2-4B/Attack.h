#pragma once
#include "BoxCollider.h"

#define ATTACK_EREA_SHIFT_Y -50	 //UŒ‚”ÍˆÍ‚ğ‚¸‚ç‚·
class Attack :
	public BoxCollider
{
private:
	AttackData attack_data;		//UŒ‚‚É•K—v‚Èî•ñŠi”[
	bool attack_flg;	//UŒ‚‚ª”­¶‚µ‚Ä‚¢‚é‚©‚Ìƒtƒ‰ƒO
	bool can_apply_damage;		//ƒ_ƒ[ƒW‚ğ—^‚¦‚ç‚ê‚é‚©”»’f


public:
	Attack();
	~Attack();
	void Update(Location _location, Erea _erea);
	void Draw()const;
	//UŒ‚‚ğ”­¶‚³‚¹‚é(_attackdata = UŒ‚‚µ‚½ƒvƒŒƒCƒ„[‚à‚µ‚­‚Í“G‚ÌUŒ‚‚É•K—v‚Èî•ñ)
	void SpawnAttack(AttackData _attackdata);
	//UŒ‚‚ª”­¶‚µ‚Ä‚¢‚é‚©”»’f
	bool GetAttackFlg() { return attack_flg; }
	//Šeî•ñ‚ğæ“¾
	AttackData GetAttackData() { return attack_data; }
	//ƒ_ƒ[ƒW‚ğ—^‚¦‚ç‚ê‚é‚©”»’f
	bool GetCanApplyDamage() { return can_apply_damage; }
	//UŒ‚‚ğÁ‚·
	void DeleteAttack() { attack_flg = false; }
};
