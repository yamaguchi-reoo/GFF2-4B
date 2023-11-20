#pragma once
#include "CharaBase.h"

#define PI    3.1415926535897932384626433832795f  //π

//ゲージ
struct GuegeBase
{
	float x;	  //色つける四角の右下座標(x)
	float y;	  //色つける四角の右下座標(y)
	float h;  //色つける四角の高さ
	float volume; //色の溜まり具合
	float ratio;  //ゲージの溜まり具合
	int maxFlg;   //CMYの場合(0:ゲージMAX未満 1:ゲージMAX),黒の場合(0:それ以外 1:ゲージが黒の状態
};

class PowerGauge :public CharaBase
{
private:
	GuegeBase magenta; //マゼンタ
	GuegeBase cyan;    //シアン
	GuegeBase yellow;  //イエロー
	GuegeBase black;   //黒

	int power_flg; //(0:それ以外 1:強化中 2:強化解除)

	int image[3];  //画像用変数

	int mask_handle[2]; //マスク画像用変数

	float num; //画像回転用
	int i,j; //画像回転用

	int rota_flg; //画像回転アニメーション用フラグ(0:それ以外 1:アニメーション中)

	int remainder; //溢れた分

public:
	//コンストラクタ
	PowerGauge();

	//デストラクタ
	~PowerGauge();

	//更新処理
	void Update(GameMain* main);

	//描画処理
	void Draw()const;

	//ゲージの溜まり具合を計算
	float CalculateVolume(float volume, float h);

	//ゲージの溜まり具合を計算した値を代入
	void VolumeSet(); 

	//時間経過で黒のゲージを減らす
	void BlackGauge(); 

	//強化状態かどうか渡す
	int PowerGaugeState(); 

	//強化状態かどうかを保存する変数の値を引数の値に変更
	void SetPowerFlg(int i);

	//敵が落とした色、量をゲージに加算
	void SetVolume(ColorDate color); 

	//CMYKのゲージがMAXかチェックする
	void CheckVolumeMax(); 

	//強化ゲージの回転処理
	void RotaGauge(); 

	//強化状態が終わった後の初期化処理
	void InitGauge(); 

	//強化ゲージから溢れた分を返す
	int GetColorRem() { return remainder; } 

	//強化ゲージから溢れた分を0にリセット
	void ResetColorRem(); 

	// マゼンタゲージの量を取得
	float GetMagentaVolume() const {
		return magenta.volume;
	}

	// イエローゲージの量を取得
	float GetYellowVolume() const {
		return yellow.volume;
	}

	// シアンゲージの量を取得
	float GetCyanVolume() const {
		return cyan.volume;
	}
};
