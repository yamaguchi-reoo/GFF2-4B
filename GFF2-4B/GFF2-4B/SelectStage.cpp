#include "SelectStage.h"
#include "GameMain.h"
#include "PadInput.h"

int SelectStage::stage_num = 0;
int SelectStage::goal_flg[3] = {1,1,1}; //デバック用に1

//コンストラクタ
SelectStage::SelectStage()
{
	botton_flg = false;
	img[0] = LoadGraph("resource/images/SelectCursor.png");
	img[1] = LoadGraph("resource/images/Stage1.png");
	img[2] = LoadGraph("resource/images/Stage2.png");
	img[3] = LoadGraph("resource/images/Stage3.png");
	img[4] = LoadGraph("resource/images/Stage1w.png");
	img[5] = LoadGraph("resource/images/Stage2w.png");
	img[6] = LoadGraph("resource/images/Stage3w.png");
}

//デストラクタ
SelectStage::~SelectStage()
{
}

// 描画以外の更新を実装
AbstractScene* SelectStage::Update()
{
	if (
#ifdef _DEBUG
	(PadInput::TipLeftLStick(STICKL_X) <= -1 || KeyInput::OnKey(KEY_INPUT_A))
#else
		PadInput::TipLeftLStick(STICKL_X) <= -1
#endif
		 && botton_flg == false)
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
	else if (
#ifdef _DEBUG
	(PadInput::TipLeftLStick(STICKL_X) >= 1 || KeyInput::OnKey(KEY_INPUT_D))
#else
	PadInput::TipLeftLStick(STICKL_X) >= 1
#endif
		&& botton_flg == false)
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
	{
		//何もしてないとき
		botton_flg = false;
	}

	//Aボタンが押されたらゲームメインに遷移
	if (
#ifdef _DEBUG
		PadInput::OnButton(XINPUT_BUTTON_A) || KeyInput::OnKey(KEY_INPUT_RETURN)
#else
		PadInput::OnButton(XINPUT_BUTTON_A)
#endif
		)
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
			DrawCircle(330, 240, 120, 0x000000, 1, 1);
			DrawCircle(660, 240, 120, 0xffffff, 1, 1);
			DrawCircle(980, 240, 120, 0xffffff, 1, 1);
			//DrawFormatString(310, 200, 0xffffff, "ステージ1");
			//DrawFormatString(610, 200, 0x000000, "ステージ2");
			//DrawFormatString(910, 200, 0x000000, "ステージ3");
			DrawGraph(245, 220, img[4], TRUE);
			DrawGraph(580, 220, img[2], TRUE);
			DrawGraph(895, 220, img[3], TRUE);

			break;

		case 1:
			DrawCircle(330, 240, 120, 0xffffff, 1, 1);
			DrawCircle(660, 240, 120, 0x000000, 1, 1);
			DrawCircle(980, 240, 120, 0xffffff, 1, 1);
			//DrawFormatString(310, 200, 0x000000, "ステージ1");
			//DrawFormatString(610, 200, 0xffffff, "ステージ2");
			//DrawFormatString(910, 200, 0x000000, "ステージ3");
			DrawGraph(245, 220, img[1], TRUE);
			DrawGraph(580, 220, img[5], TRUE);
			DrawGraph(895, 220, img[3], TRUE);
			break;

		case 2:
			DrawCircle(330, 240, 120, 0xffffff, 1, 1);
			DrawCircle(660, 240, 120, 0xffffff, 1, 1);
			DrawCircle(980, 240, 120, 0x000000, 1, 1);
			//DrawFormatString(310, 200, 0x000000, "ステージ1");
			//DrawFormatString(610, 200, 0x000000, "ステージ2");
			//DrawFormatString(910, 200, 0xffffff, "ステージ3");
			DrawGraph(245, 220, img[1], TRUE);
			DrawGraph(580, 220, img[2], TRUE);
			DrawGraph(895, 220, img[6], TRUE);
			break;

		default:
		break;
	}

	DrawGraph(260 + (stage_num * 330), 410, img[0], TRUE);

#ifdef _DEBUG

	SetFontSize(30);
	DrawFormatString(450, 40, 0x000000, "ステージを選択してください");

#endif // !_DEBUG
}

//クリアしたステージを保存
void SelectStage::SetGoalFlg(int stage_num)
{
	goal_flg[stage_num] = 1;
}