#pragma once
#include "CharaBase.h"

//���z�N���X
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

