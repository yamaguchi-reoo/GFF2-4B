#pragma once

#define DEBUG true		//デバッグ用表示や操作を適用するか false=適用しない true=適用

//画面サイズ
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define G_POWER			1	//重力の強さ
#define PLAYER_WIDTH  75	//プレイヤーの幅
#define PLAYER_HEIGHT 150	//プレイヤーの高さ

//スクロール関連
#define LEFT_END	300
#define RIGHT_END	750
#define SCREEN_LEFT_END 0
#define FLOOR_NUM	3	//床の数


#define BAMBOO_NUM 3 //竹の積まれている数

//攻撃時に誰が攻撃したのか判断する用
#define PLAYER	0	//プレイヤー
#define ENEMY	1	//敵

//攻撃の種類
#define MELEE 0		//近接攻撃
#define WAVES 1		//飛ぶ斬撃
#define BULLET 2	//遠距離

