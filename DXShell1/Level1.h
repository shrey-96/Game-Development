#pragma once
#include "GameLevel.h"
#include <time.h>


class Level1 : public GameLevel
{
	float y;
	float ySpeed;
	float ** ArrayofPoints;
	SpriteSheet* sprites;
	SpriteSheet* planet1;
	SpriteSheet* planet2;
	SpriteSheet* planet3;
	int rand1 = 2;
	int rand2 = 14;
	int rand3 = 32;
	bool ChangePosition = true;
	int what;


public:
	void Load() override;
	void Unload() override;
	void Update() override;
	void Render() override;
	void DeleteArray();

};
