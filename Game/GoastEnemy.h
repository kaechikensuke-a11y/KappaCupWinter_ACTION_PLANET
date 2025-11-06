#pragma once
class Player;

class GoastEnemy : public IGameObject
{
public:
	GoastEnemy() {}
	~GoastEnemy() {}

	void Update();
	void Render(RenderContext& rc);
	bool Start();
	void Move();
	void Findplayer();//プレイヤーを追いかける関数
private:
	void Rotation();
	void SearchPlayer();
	//ポジションをせっていする。
	Vector3        m_position = Vector3(100.0f, 0.0f, 100.0f);
	Vector3        m_forward; //前に進むコード(Z方向のこと)
	Vector3        m_moveSpeed;
	ModelRender    m_enemyModelRender;
	Quaternion     m_rotation;
	Player*        m_player = nullptr;
	SphereCollider m_spherCollider; //当たり判定
	RigidBody      m_rigidBody; //物理演算を行うもの
	FontRender     m_fontRender;
	//SphereCollider m_sphereCollider;
	CharacterController m_characterController;
	bool           m_isSearchPlayer = false; //プレイヤーを見つけたかどうか

};

