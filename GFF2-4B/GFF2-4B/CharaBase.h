#pragma once
#include"BoxCollider.h"
//‰¼‘zƒNƒ‰ƒX
class GameMain;

enum  class Direction {
	RIGHT = 0,
	LEFT,
	RIGHT_FALL,
	LEFT_FALL
};

struct ColorDate {
	float magenta;
	float syan;
	float yellow;
};

class CharaBase : public BoxCollider
{
protected:
	ColorDate Date{ 0 };
	int image = 0;
	float speed = 0;
	int hp = 0;

private:
	virtual void Update(GameMain* main) = 0;
	virtual void Draw()const = 0;
};