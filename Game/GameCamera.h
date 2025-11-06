#pragma once
#include "camera/SpringCamera.h" //このコードをインクルードしないとばねカメラを使用できない。
class Player;

class GameCamera : public IGameObject
{
public:
	GameCamera(){}
	~GameCamera(){}
	bool Start();
	void Update();

	Player* m_player;
	Vector3 m_toCameraPos;
	SpringCamera m_springCamera;//ばねカメラ
};

