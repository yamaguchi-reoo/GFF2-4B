#pragma once
#include"BoxCollider.h"
//仮想クラス
class GameMain;


struct ColorDate {
	float magenta;
	float cyan;
	float yellow;
};

class CharaBase : public BoxCollider
{
protected:
	ColorDate Date{ 0 };
	int image = 0;
	float speed = 0;
	int hp = 0;

public:
	virtual void Update(GameMain* main) = 0;
	virtual void Draw()const = 0;
	virtual void ReverseDirection() {}  // デフォルト実装は何もしない
  // 向きを取得するメソッドも追加
	virtual bool GetDirection() const { return true; }

};