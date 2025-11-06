#pragma once
class Player;
class Game;
class Jumpitem:public IGameObject
{
public:
	Jumpitem();
	~Jumpitem();

	bool Start();
	void Update();
	void Render(RenderContext& rc);
	void Move();
	void Rotation();

	PhysicsStaticObject physicsStaticObject;
	ModelRender         m_JumpRender;
	Vector3             m_position;
	Quaternion          m_rotation;
	Player *            m_player;
	Game   *            m_game;
};
