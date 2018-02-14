#pragma once
#include "GameLevel.h"
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
	int f1;
	int f2;
	bool ChangePosition;


public:
	void Load() override;
	void Unload() override;
	void Update() override;
	void Render() override;

};
