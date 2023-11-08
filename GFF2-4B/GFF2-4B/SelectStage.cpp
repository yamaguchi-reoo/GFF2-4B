#include "SelectStage.h"
#include "GameMain.h"
#include "PadInput.h"

int SelectStage::stage_num = 0;
int SelectStage::goal_flg[3] = {1,1,1}; //デバック用に1

//コンストラクタ
SelectStage::SelectStage()
{
	botton_flg = false;
	img = LoadGraph("resource/images/SelectCursor.png");
}

//デストラクタ
SelectStage::~SelectStage()
{
}

// 描画以外の更新を実装
AbstractScene* SelectStage::Update()
{
	if (PadInput::TipLeftLStick(STICKL_X) <= -1 && botton_flg == false)
	{//左移動
		botton_flg = true;

		--stage_num;

		if (goal_flg[1] == 1)
		{
			if (stage_num < 0)
			{
				stage_num = 2;
			}
		}
		else
		{
			if (stage_num < 0)
			{
				stage_num = 0;
			}
		}
		
	}
	else if (PadInput::TipLeftLStick(STICKL_X) >= 1 && botton_flg == false)
	{//右移動
		botton_flg = true;

		++stage_num;

		if (goal_flg[1] == 1)
		{
			if (stage_num > 2)
			{
				stage_num = 0;
			}
		}
		else if(goal_flg[0] == 1)
		{
			if (stage_num > 1)
			{
				stage_num = 1;
			}
		}
		else
		{
			if (stage_num > 0)
			{
				stage_num = 0;
			}
		}
		
	}
	else if (PadInput::TipLeftLStick(STICKL_X) > -1 && PadInput::TipLeftLStick(STICKL_X) < 1 && PadInput::OnButton(XINPUT_BUTTON_B) == false)
	{//何もしてないとき
		botton_flg = false;
	}

	//Aボタンが押されたらゲームメインに遷移
	if (PadInput::OnButton(XINPUT_BUTTON_A) == true)
	{
		return new GameMain(stage_num);
	}

	return this;
}

//描画に関することを実装
void SelectStage::Draw() const
{
	SetFontSize(16);
	DrawBox(0, 0, 1280, 720, 0xadadad, TRUE);

	switch (stage_num)
	{
		case 0:
			DrawCircle(350, 200, 100, 0x000000, 1, 1);
			DrawCircle(650, 200, 100, 0xffffff, 1, 1);
			DrawCircle(950, 200, 100, 0xffffff, 1, 1);
			DrawFormatString(310, 200, 0xffffff, "ステージ1");
			DrawFormatString(610, 200, 0x000000, "ステージ2");
			DrawFormatString(910, 200, 0x000000, "ステージ3");
			break;

		case 1:
			DrawCircle(350, 200, 100, 0xffffff, 1, 1);
			DrawCircle(650, 200, 100, 0x000000, 1, 1);
			DrawCircle(950, 200, 100, 0xffffff, 1, 1);
			DrawFormatString(310, 200, 0x000000, "ステージ1");
			DrawFormatString(610, 200, 0xffffff, "ステージ2");
			DrawFormatString(910, 200, 0x000000, "ステージ3");
			break;

		case 2:
			DrawCircle(350, 200, 100, 0xffffff, 1, 1);
			DrawCircle(650, 200, 100, 0xffffff, 1, 1);
			DrawCircle(950, 200, 100, 0x000000, 1, 1);
			DrawFormatString(310, 200, 0x000000, "ステージ1");
			DrawFormatString(610, 200, 0x000000, "ステージ2");
			DrawFormatString(910, 200, 0xffffff, "ステージ3");
			break;

		default:
		break;
	}

	DrawGraph(280 + (stage_num * 310), 400, img, TRUE);

#ifdef _DEBUG

	DrawFormatString(0, 0, 0xffffff, "%d", stage_num);

#endif // !_DEBUG
}

//クリアしたステージを保存
void SelectStage::SetGoalFlg(int stage_num)
{
	goal_flg[stage_num] = 1;
}