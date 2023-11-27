#pragma once
#include "common.h"
#include "PadInput.h"
#include "CharaBase.h"

#define _USE_MATH_DEFINES
#include <math.h>

class Effect : 
	public CharaBase
{
private:

	ColorDate color_date;

	float v;

	float gauge_x, gauge_y;
	float diff_x, diff_y;

	int Flg;

public:
	Effect();
	~Effect();

	void Update(GameMain* main);
	void Draw()const;


	float SetLocation(Location _location);
	float SetGaugeLocation(Location _location);
	

	int SetFlg(int flg)
	{
		Flg = flg;
		return Flg;
	}

	int GetFlg() { return Flg; }

	void SetSplashColor(ColorDate color);
	ColorDate GetSplashColor() { return color_date; }

};

