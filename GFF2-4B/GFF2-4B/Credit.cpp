#include "Credit.h"
#include "DxLib.h"
#include "GameMain.h"
#include "PadInput.h"

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
void Credit::Draw()const
{
	DrawFormatString(1000, 680, 0xff000f, "—V‚ñ‚Å‚­‚ê‚Ä‚ ‚è‚ª‚Æ‚¤!");
	//DrawFormatString(1000, 600, 0xff000f, "%d", credit_timer);
}