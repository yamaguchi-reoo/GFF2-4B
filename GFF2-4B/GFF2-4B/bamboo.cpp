#include "bamboo.h"
#include "PadInput.h"

Bamboo::Bamboo(float pos_y)
{
	location.x = 900;
	location.y = 500 + pos_y;
	erea.width = 40;
	erea.height = 60;

	flg = true;
}

Bamboo::~Bamboo()
{
}

void Bamboo::Update()
{
	if (PadInput::OnButton(XINPUT_BUTTON_Y)) {
		ReverseFlg();
	}
}

void Bamboo::Draw() const
{
	if (flg == true) {
		DrawBoxAA(location.x, location.y, location.x + erea.width, location.y + erea.height, 0xffffff, FALSE);
	}
}

void Bamboo::ReverseFlg()
{
	flg = false;
}
