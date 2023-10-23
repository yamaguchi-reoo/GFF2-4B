#pragma once
#include "CharaBase.h"

//‰¼‘zƒNƒ‰ƒX
class Zakuro :public CharaBase
{
private:
	bool zakuro_flg;
public:
	Zakuro();
	~Zakuro();

	void Update(GameMain* main)override;
	void Draw()const override;

};

