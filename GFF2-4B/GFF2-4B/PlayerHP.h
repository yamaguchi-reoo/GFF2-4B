#pragma once

class PlayerHP
{
private:
	int hpImage;  //画像用変数
	int playerHP; //プレイヤーのHP

public:
	PlayerHP();  //コンストラクタ
	~PlayerHP(); //デストラクタ

	void Update(int hp); //更新処理
	void Draw()const; //描画処理
};

