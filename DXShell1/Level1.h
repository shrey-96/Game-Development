#pragma once
#include "GameLevel.h"
#include <cstdlib>
#include <ctime>
#include <time.h>


class Level1 : public GameLevel
{
	float y;
	float ySpeed;
	float *** Array3D;
	SpriteSheet* sprites;
	SpriteSheet* planet1;
	SpriteSheet* planet2;
	SpriteSheet* planet3;
	int fx1, fy1;
	int fx2, fy2;
	int fx3, fy3;
	bool ChangePosition;


public:
	void Load() override;
	void Unload() override;
	void Update() override;
	void Render() override;

	int GetRand(int range);

};
