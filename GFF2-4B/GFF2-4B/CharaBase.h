#pragma once
//���z�N���X
class GameMain;

class CharaBase
{
protected:
	int image = 0;
	float speed = 0;
private:
	virtual void Update(GameMain* main) = 0;

	virtual void Draw()const = 0;

	virtual void Hit() = 0;
};