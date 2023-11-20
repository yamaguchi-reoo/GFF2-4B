#pragma once
#include"BoxCollider.h"
//‰¼‘zƒNƒ‰ƒX
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
	//virtual void EnemyPush(int num, Location _sub_location, Erea _sub_erea) = 0;

};