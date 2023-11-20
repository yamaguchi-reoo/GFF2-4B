#pragma once
#include<stdio.h>
#include "BoxCollider.h"

class HealItem :
	public BoxCollider
{
private:
	bool spawn_flg;
	int heal_image;
public:

	HealItem(/*float pos_x, float pos_y*/);
	~HealItem();

	void Update();
	void Draw()const;

	//スポーンフラグをセット
	void SetSpawnFlg(bool _flg) { spawn_flg = _flg; }
	void SetReturnFlg() { spawn_flg = false; }

	int GetSpawnFlg() { return spawn_flg; }

	void SetLocation(Location _location);
};

