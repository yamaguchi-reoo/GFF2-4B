#include "GameClear.h"
#include "PadInput.h"
#include "Title.h"
#include "Result.h"

void GameClear::ImageLoad(int& _handle, const char* _file_name)
{
	try 
	{
		_handle = LoadGraph(_file_name);
		if(_handle == -1)
		{
			throw _file_name;
		}
	}
	catch (const char& err)
	{
		printf("%sがありません。", &err);
	}
}

GameClear::GameClear(int _stage_num)
{
	//カットイン演出用画像
	ImageLoad(cut_in01, "resource/images/GameClear/CutIn01.png");
	ImageLoad(cut_in02, "resource/images/GameClear/CutIn02.png");
	
	//クリアフォント表示
	ImageLoad(stage_goal_image, "resource/font/StageClear.png");
	ImageLoad(boss_beat_image, "resource/font/BossStageClear.png");

	//背景画像用変数
	ImageLoad(clear_back_image, "resource/images/GameClear/GameClearImage.png");

	//カットイン01の座標変数
	cut_in01_loc.x = 0.0f;			//X座標
	cut_in01_loc.y = 0.0f;			//Y座標

	//カットイン02の座標変数
	cut_in02_loc.x = 0.0f;			//X座標
	cut_in02_loc.y = 0.0f;			//Y座標

	stage_num = _stage_num;			//stage数情報格納用変数

	clear_font_alpha = 0;			//クリア画像のα値

	font_flg = false;				//クリアフォント表示用フラグ
	scene_change_timer = 0;			//シーン遷移カウント用タイマー
}

GameClear::~GameClear()
{
}

AbstractScene* GameClear::Update()
{
	//------ カットイン演出 ------//
	//カットイン01のX座標が300以下かつカットイン02のX座標が-300以上なら4ずつ動かす
	if (cut_in01_loc.x >= -CUTIN_POS_TIMING && cut_in02_loc.x <= (CUTIN_POS_TIMING))
	{
		//カットイン用画像のX座標を動かす
		cut_in01_loc.x += -4.f;
		cut_in02_loc.x += 4.f;
	}
	//カットイン01のX座標が300以上かつカットイン02のX座標が-300以下なら30ずつ動かす
	if (cut_in01_loc.x <= -CUTIN_POS_TIMING && cut_in02_loc.x >= (CUTIN_POS_TIMING))
	{
		//カットイン用画像のX座標を動かす
		cut_in01_loc.x += -90.f;
		cut_in02_loc.x += 90.f;
		if (cut_in01_loc.x <= -1280.f && cut_in02_loc.x >= 1280.f) { font_flg = true; }
	}

	//------ シーン遷移処理 ------//
	if (
#ifdef _DEBUG
		//デバッグモードの間Aボタン/Enterキーを押すと画面遷移
		PadInput::OnButton((XINPUT_BUTTON_A) || KeyInput::OnKey(KEY_INPUT_RETURN))
#else	
		//ReleaseモードならAボタンで画面遷移
		PadInput::OnButton(XINPUT_BUTTON_A)
#endif
		) 
	{
		//リザルト画面へ遷移
		return new Result();
	}
	//シーン切り替え用タイマーが30を越えたらResult画面に切り替え
	if (scene_change_timer >= 30) { return new Result; }

	//フォント表示用フラグのOn,Offの切り替え処理
	if (font_flg == true) { clear_font_alpha += 5; }
	//フォント表示が完了したらタイマーを起動する
	if (clear_font_alpha >= 255) { scene_change_timer += 1; }

	return this;
}

void GameClear::Draw() const
{
	//背景画像表示
	DrawGraph(0, 0, clear_back_image, TRUE);

	//カットイン画面表示
	DrawGraphF(cut_in01_loc.x, cut_in01_loc.y, cut_in01, TRUE);
	DrawGraphF(cut_in02_loc.x, cut_in02_loc.y, cut_in02, TRUE);

	//透明度設定
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, clear_font_alpha);
	//現在のステージがBossステージ以外ならstage_goal_imageを表示
	//現在のステージがBossステージならboss_beat_imageを表示

	if (stage_num != 3) { DrawGraphF(250.f, 50.f, stage_goal_image, TRUE); }

	if (stage_num == 3) { DrawGraphF(250.f, 50.f, boss_beat_image, TRUE); }

	//描画ブレンドをNoBlendにする
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}