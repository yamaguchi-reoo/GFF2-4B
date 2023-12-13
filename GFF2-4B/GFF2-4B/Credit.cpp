#include "Title.h"
#include "Credit.h"

//コンストラクタ
Credit::Credit()
{
	credit_timer = 0;
}

Credit::~Credit()
{
}

AbstractScene* Credit::Update()
{
	if (credit_timer >= 180)
	{
		return nullptr;
	}

	credit_timer += 1;
	return this;
}

void Credit::Draw() const
{
	DrawFormatString(700, 680, 0xfafafa, "thank you for playing");
}