#pragma once

//画面サイズ
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define G_POWER			1	//重力の強さ
#define PLAYER_WIDTH  75	//プレイヤーの幅
#define PLAYER_HEIGHT 160	//プレイヤーの高さ

//スクロール関連
#define LEFT_END	300
#define RIGHT_END	750
#define SCREEN_LEFT_END 0
#define FLOOR_NUM	3	//床の数

//竹
#define BAMBOO_NUM 3 //竹の積まれている数
#define BAMBOO_MAX 15 //竹の最大数

#define ATTACK_NUM 200   //画面に存在できる最大の攻撃数
#define ATTACK_SUB_NUM 100   //forする際の存在できる最大の攻撃数

//攻撃時に誰が攻撃したのか判断する用
#define PLAYER	0	//プレイヤー
#define ENEMY	1	//敵

//攻撃の種類
#define MELEE 0		//近接攻撃
#define BULLET 1	//遠距離攻撃（波動も含む）

//ステージ	
#define BOX_HEIGHT	45					//ステージのブロック一つ当たりの高さ
#define BOX_WIDTH	48					//ステージのブロック一つ当たりの幅
#define MAX_STAGE_HEIGHT 60				//ステージのブロックの縦の最大個数
#define MAX_STAGE_WIDTH  3000			//ステージのブロックの横の最大個数
#define STAGE_GOAL (BOX_WIDTH*5)		//ステージでゴールとなる座標
#define SIGH_BOARD_NUM 5				//看板の数
//エネミーの数
#define ZAKURO_MAX 35	//ザクロの最大数
#define IRUKA_MAX 20		//イルカの最大数
#define HIMAWARI_MAX 20	//ひまわりの最大数

//エフェクト
#define SPLASH_MAX 50

//アイテム
#define ITEM_MAX 10 //画面に出現できるアイテムの最大数
#define JAR_MAX 7  //壺の最大数

#define PLAYER_SLASH_ONE 0
#define PLAYER_SLASH_TWO 1
#define PLAYER_SLASH_THREE 2
#define PLAYER_SLASH_FOUR 3
#define PLAYER_JUMP_SLASH 4
#define PLAYER_JUMP_SLASH_END 5
#define POWERUP_PLAYER_SLASH_ONE 6
#define POWERUP_PLAYER_SLASH_TWO 7
#define POWERUP_PLAYER_SLASH_THREE 8
#define POWERUP_PLAYER_SLASH_FOUR 9
#define POWERUP_PLAYER_JUMP_SLASH 10
#define POWERUP_PLAYER_JUMP_SLASH_END 11
#define HIMAWARI_BULLET 12
#define BOSSZAKURO_WAVES 13
#define BOSSHIMAWARI_BULLET 14