#pragma once
class Player : public IGameObject
{
public:
	Player();
	~Player();

	void Update();
	void Render(RenderContext& rc);
	void Move();
	void ManagerState();
	void Animation();
	void Rotation();

	enum EnAnimationClip
	{
		enAnimationClip_Idle,
		enAnimationClip_Walk,
		enAnimationClip_Jump,
		enAnimationClip_Num,
	};

	//プレイヤーのポジションをエネミーが取得する
	const Vector3& GetPosition() const
	{
		return m_position;
	}

	ModelRender         m_playerRender;
	Vector3             m_position;
	Vector3             m_moveSpeed;
	Quaternion          m_rotation;
	AnimationClip       animationClips[enAnimationClip_Num];
	CharacterController characterController;
	Vector3 moveSpeed;

	int playerState = 0;
	int jumpCount   = 0;
	bool getJumpItem = false;
	
};

