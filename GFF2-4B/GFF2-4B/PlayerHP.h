#pragma once

class PlayerHP
{
private:
	int hpImage[6];  //画像用変数
	int player_hp; //プレイヤーのHP
	int draw_hp; //HP点滅用変数
	int flash_flg; //HP点滅用変数
	int flash_hp; //点滅させるHP

public:
	//コンストラクタ
	PlayerHP();  

	//デストラクタ
	~PlayerHP();

	//更新処理
	void Update(int hp);

	//描画処理
	void Draw()const;

	//HP点滅
	void FlashHP(void);

	//HP消滅
	void AnimHP(void);
};

