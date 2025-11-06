#pragma once

#include "Level3DRender/LevelRender.h"

class Player;
class GameCamera;
class BackGround;
class Jumpitem;
class GoastEnemy;

class Game : public IGameObject
{
public:
	Game() {}
	~Game() {}
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	void InitSky();

	FontRender m_timerRender;

	float m_timer = 30.0f;
	SkyCube* m_skyCube = nullptr; //スカイキューブ　（空の実装）
	int m_skyCubeType = enSkyCubeType_Day;
	
private:
	Player    * player;
	GameCamera* gamecamera;
	BackGround* background;
	Jumpitem  * jumpitem;
	GoastEnemy* goastenemy;
};

