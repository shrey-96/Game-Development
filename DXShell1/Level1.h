#pragma once
#include "GameLevel.h"


class Level1 : public GameLevel
{
	float y;
	float ySpeed;
	SpriteSheet* sprites;
	SpriteSheet* planet1;
	SpriteSheet* planet2;
	SpriteSheet* planet3;

public:
	void Load() override;
	void Unload() override;
	void Update() override;
	void Render() override;

};
