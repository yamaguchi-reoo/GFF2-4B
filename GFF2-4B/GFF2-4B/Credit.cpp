#include "Title.h"
#include "Credit.h"
#include "PadInput.h"

#define CREDIT_ALPHA_MAX 180

//画像初期化
void Credit::ImageLoad(int& _handle, const char* _file_name)
{
	try
	{
		_handle = LoadGraph(_file_name);
		if (_handle == -1)
		{
			throw _file_name;
		}
	}
	catch (const char& err)
	{
		printf("%sがありません。", &err);
	}
}

//コンストラクタ
Credit::Credit()
{
	ImageLoad(end_roll01_image, "resource/images/EndRoll/EndRoll01.png");
	ImageLoad(end_roll02_image, "resource/images/EndRoll/EndRoll02.png");
	ImageLoad(end_roll03_image, "resource/images/EndRoll/EndRoll03.png");
	ImageLoad(end_roll04_image, "resource/images/EndRoll/EndRoll04.png");
	ImageLoad(end_roll05_image, "resource/images/EndRoll/EndRoll05.png");
	ImageLoad(end_roll_makimono, "resource/images/EndRoll/EndRollMakimono.png");
	ImageLoad(credit_navigation, "resource/images/EndRoll/Navigation.png");

	
	credit_timer = 0.f;
	credit_alpha = 0;
	alpha_sub_flg = false;
}

Credit::~Credit()
{
}

AbstractScene* Credit::Update()
{
	if (credit_timer >= 1200 || PadInput::OnButton(XINPUT_BUTTON_A))
	{
		return nullptr;
	}

	//240になるまでalpha値を加算
	if ((credit_alpha <= CREDIT_ALPHA_MAX) && (alpha_sub_flg == false))
	{ 
		credit_alpha += 1; 
	}
	//240以上になったらalpha値を減算するflgをOnにする
	else if (credit_alpha >= CREDIT_ALPHA_MAX) 
	{
		alpha_sub_flg = true; 
	}
	//flgがOnの間減算
	if (alpha_sub_flg == true)
	{
		credit_alpha -= 1;
	}
	if (credit_alpha <= 0)
	{
		alpha_sub_flg = false;
	}

	credit_timer += 1;
	return this;
}

void Credit::Draw() const
{
	DrawGraph(0, 0, end_roll_makimono, FALSE);
	DrawGraph(340, 660, credit_navigation, TRUE);
	if (credit_timer >= (CREDIT_ALPHA_MAX * 0) && credit_timer <= (CREDIT_ALPHA_MAX * 2))
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, credit_alpha);
		DrawGraph(0, 0, end_roll01_image, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
	if (credit_timer >= (CREDIT_ALPHA_MAX * 2) && credit_timer <= (CREDIT_ALPHA_MAX * 4))
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, credit_alpha);
		DrawGraph(0, 0, end_roll02_image, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
	if (credit_timer >= (CREDIT_ALPHA_MAX * 4) && credit_timer <= (CREDIT_ALPHA_MAX * 6))
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, credit_alpha);
		DrawGraph(0, 0, end_roll03_image, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
	if (credit_timer >= (CREDIT_ALPHA_MAX * 6) && credit_timer <= (CREDIT_ALPHA_MAX * 8))
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, credit_alpha);
		DrawGraph(0, 0, end_roll04_image, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
	if (credit_timer >= (CREDIT_ALPHA_MAX * 8) && credit_timer <= (CREDIT_ALPHA_MAX * 10))
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, credit_alpha);
		DrawGraph(0, 0, end_roll05_image, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
}