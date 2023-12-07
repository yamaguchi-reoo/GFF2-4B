#include "SelectStage.h"
#include "Title.h"
#include "GameMain.h"
#include "PadInput.h"
#include"SoundManager.h"

int SelectStage::stage_num = 0;
int SelectStage::goal_flg[3] = {1,1,1}; //デバック用に1

//コンストラクタ
SelectStage::SelectStage()
{
	botton_flg = false;
	img[0] = LoadGraph("resource/images/SelectStage/SelectCursor.png");
	img[1] = LoadGraph("resource/images/SelectStage/Stage1.png");
	img[2] = LoadGraph("resource/images/SelectStage/Stage2.png");
	img[3] = LoadGraph("resource/images/SelectStage/Stage3.png");
	img[4] = LoadGraph("resource/images/SelectStage/Stage1w.png");
	img[5] = LoadGraph("resource/images/SelectStage/Stage2w.png");
	img[6] = LoadGraph("resource/images/SelectStage/Stage3w.png");
	img[7] = LoadGraph("resource/images/Result/makimono1.png");
	img[8] = LoadGraph("resource/images/Result/makimono2.png");
	img[9] = LoadGraph("resource/images/Result/makimono3.png");
	img[10] = LoadGraph("resource/images/SelectStage/SelectStageFont.png");


	x1 = 0;
	x2 = 640;

	/*x1 = -460;
	x2 = 1100;*/
	anim_flg = 0;
}

//デストラクタ
SelectStage::~SelectStage()
{
}

// 描画以外の更新を実装
AbstractScene* SelectStage::Update()
{
	if (anim_flg == 0)
	{
		AnimMakimono();
	}
	else
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
			else if (goal_flg[0] == 1)
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
			SoundManager::StartSound(SYSTEM_SELECT_SOUND);
		{

			return new GameMain(stage_num);
		}

		//Bボタンが押されたらタイトルに遷移
		if (
#ifdef _DEBUG
			PadInput::OnButton(XINPUT_BUTTON_B) || KeyInput::OnKey(KEY_INPUT_SPACE)
#else
			PadInput::OnButton(XINPUT_BUTTON_B)
#endif
			)
		{
			return new Title();
		}
	}
	return this;
}

//描画に関することを実装
void SelectStage::Draw() const
{
	DrawBox(0, 0, 1280, 720, 0x666464, TRUE);

	DrawGraph(80, 25, img[8], TRUE);

	switch (stage_num)
	{
		case 0:
			DrawCircle(330, 240 + 75, 120, 0x000000, TRUE, 1);
			DrawCircle(660 - 20, 240 + 75, 120, 0x000000, FALSE, 5);
			DrawCircle(980 - 25, 240 + 75, 120, 0x000000, FALSE, 5);
			DrawGraph(245, 220 + 75, img[4], TRUE);
			DrawGraph(580 - 20, 220 + 75, img[2], TRUE);
			DrawGraph(895 - 25, 220 + 75, img[3], TRUE);
			DrawOval(325, 550 + 50, 25, 10, 0x000000, TRUE);
			DrawOval(640, 550 + 50, 25, 10, 0x000000, FALSE);
			DrawOval(955, 550 + 50, 25, 10, 0x000000, FALSE);

			break;

		case 1:
			DrawCircle(330, 240 + 75, 120, 0x000000, FALSE, 5);
			DrawCircle(660 - 20, 240 + 75, 120, 0x000000, TRUE, 1);
			DrawCircle(980 - 25, 240 + 75, 120, 0x000000, FALSE, 5);
			DrawGraph(245, 220 + 75, img[1], TRUE);
			DrawGraph(580 - 20, 220 + 75, img[5], TRUE);
			DrawGraph(895 - 25, 220 + 75, img[3], TRUE);
			DrawOval(325, 550 + 50, 25, 10, 0x000000, FALSE);
			DrawOval(640, 550 + 50, 25, 10, 0x000000, TRUE);
			DrawOval(955, 550 + 50, 25,10, 0x000000, FALSE);
			break;

		case 2:
			DrawCircle(330, 240 + 75, 120, 0x000000, FALSE, 5);
			DrawCircle(660 - 20, 240 + 75, 120, 0x000000, FALSE, 5);
			DrawCircle(980 - 25, 240 + 75, 120, 0x000000, TRUE, 1);
			DrawGraph(245, 220 + 75, img[1], TRUE);
			DrawGraph(580 - 20, 220 + 75, img[2], TRUE);
			DrawGraph(895 - 25, 220 + 75, img[6], TRUE);
			DrawOval(325, 550 + 50, 25, 10, 0x000000, FALSE);
			DrawOval(640, 550 + 50, 25, 10, 0x000000, FALSE);
			DrawOval(955, 550 + 50, 25, 10, 0x000000, TRUE);
			break;

		default:
		break;
	}

	if (goal_flg[0] == 1)
	{
		SetFontSize(20);
		DrawFormatString(380, 592, 0x000000, "- - - - - - - - - -");

		if (goal_flg[1] == 1)
		{
			SetFontSize(20);
			DrawFormatString(695, 592, 0x000000, "- - - - - - - - - -");
		}
	}

	DrawGraph(265 + (stage_num * 317), 410 + 60, img[0], TRUE);

	DrawGraph(440, 130, img[10], TRUE);

	//巻物
	DrawGraph(x1, 0, img[9], TRUE);
	DrawGraph(x2, 0, img[7], TRUE);

#ifdef _DEBUG

	SetFontSize(30);
	//DrawFormatString(450, 130, 0x000000, "ステージを選択してください");

#endif // !_DEBUG
}

//クリアしたステージを保存
void SelectStage::SetGoalFlg(int stage_num)
{
	goal_flg[stage_num] = 1;
}

void SelectStage::AnimMakimono(void)
{
	if (x2 < 1100)
	{
		x1 -= 10;
		x2 += 10;
	}
	else
	{
		anim_flg = 1;
	}


	/*if (x2 > 640)
	{
		x1 += 20;
		x2 -= 20;
	}
	else
	{
		anim_flg = 1;
	}*/

}