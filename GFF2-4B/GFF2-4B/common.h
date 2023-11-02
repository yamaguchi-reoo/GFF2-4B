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

#define ATTACK_NUM 100   //画面に存在できる最大の攻撃数

//攻撃時に誰が攻撃したのか判断する用
#define PLAYER	0	//プレイヤー
#define ENEMY	1	//敵

//攻撃の種類
#define MELEE 0		//近接攻撃
#define BULLET 1	//遠距離攻撃（波動も含む）

//ステージ(ゴリ押し、最終手段)
#define STAGE_HEIGHT 16									//ステージのブロックの縦の個数
#define STAGE_WIDTH  32									//ステージのブロックの横の個数
#define BOX_SIZE	(SCREEN_HEIGHT/STAGE_HEIGHT)		//ステージのブロック一つ当たりの大きさ(とりま正方形)
//エネミーの数
#define ZAKURO_MAX 5 //ザクロの最大数
#define IRUKA_MAX 5 //ザクロの最大数