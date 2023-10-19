#pragma once
#include "BoxCollider.h"

class Player :
	public BoxCollider
{
private:
	float acs[4]; //‰Á‘¬“x 0=‰º•ûŒü 1=ã•ûŒü 2=‰E•ûŒü 3=¶•ûŒü
public:
	Player();
	~Player();
	void Update();
	void Draw()const;
	//d—Í‚ª“­‚­
	void GiveGravity();
	//Œ¸‘¬ˆ—
	void DecAcs(int num);
};
