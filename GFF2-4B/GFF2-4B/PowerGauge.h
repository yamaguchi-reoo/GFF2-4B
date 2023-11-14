#pragma once
#include "CharaBase.h"

#define PI    3.1415926535897932384626433832795f

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

	int powerFlg; //(0:それ以外 1:強化中 2:強化解除)

	int image[3];  //画像用変数

	int MaskHandle[2]; //マスク画像用変数

	float num; //画像回転用
	int i,j; //画像回転用

	int rotaFlg; //画像回転アニメーション用フラグ(0:それ以外 1:アニメーション中)

	int remainder; //溢れた分

public:
	PowerGauge();  //コンストラクタ
	~PowerGauge(); //デストラクタ

	void Update(GameMain* main); //更新処理
	void Draw()const; //描画処理

	float CalculateVolume(float volume, float h); //ゲージの溜まり具合を計算
	void VolumeSet();  //ゲージの溜まり具合を計算した値を代入
	void BlackGauge(); //時間経過で黒のゲージを減らす
	int PowerGaugeState(); //強化状態かどうか渡す
	void SetPowerFlg(int i); //強化状態かどうかを保存する変数の値を引数の値に変更
	void SetVolume(ColorDate color); //敵が落とした色、量をゲージに加算
	void CheckVolumeMax(); //CMYKのゲージがMAXかチェックする
	void RotaGauge(); //強化ゲージの回転処理
	void InitGauge(); //強化状態が終わった後の初期化処理
	int GetColorRem() { return remainder; } //溢れた分を返す
	void SetColorRem(); //強化ゲージから溢れた分を0にリセット
};
