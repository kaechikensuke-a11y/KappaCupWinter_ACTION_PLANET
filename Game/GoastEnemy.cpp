#include "stdafx.h"
#include "GoastEnemy.h"
#include "Player.h"
namespace
{
	const Vector3 SCALE{ 0.5f,0.5f,0.5f };
}

bool GoastEnemy::Start()
{
	m_enemyModelRender.Init("Assets/modelData/unityChan.tkm");
	m_enemyModelRender.SetScale(SCALE);
	m_player = FindGO<Player>("player"); //プレイヤーを見つける

	m_spherCollider.Create(0.5f); //スフィアコライダーを初期化
	
	m_characterController.Init(25.0f, 75.0f, m_position);
	return true;
}

void GoastEnemy::Update()
{
	Rotation();
	SearchPlayer();
	Findplayer();
	m_enemyModelRender.Update();
	PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
}



void GoastEnemy::Rotation()
{
	//m_rotation.AddRotationDegY(1.0f);
	m_enemyModelRender.SetRotation(m_rotation);
	//現在のプレイヤーの位置からエネミーのポジションをマイナスする。
	Vector3 diff = m_player->GetPosition() - m_position;
}

void GoastEnemy::Findplayer()
{
	m_moveSpeed = Vector3{ 0.0f,0.0f,0.0f };
	if (m_player == nullptr)
	{
		return;
	}

	if (m_isSearchPlayer == true)
	{
		Vector3 playerPos = m_player->GetPosition();//プレイヤーの座標をエネミーに渡す処理

		Vector3 diff = playerPos - m_position;//プレイヤーの座標からエネミーの座標を引く

		diff.y = 0.0f;//これを行うことでプレイヤーが上にいても追いかけてこない

		float distance = diff.Length();//ベクトルの距離計算

		diff.Normalize();//ベクトルを性器化

		float playerTarget = 100.0f;//追跡速度

		m_moveSpeed = diff * playerTarget;//方向＊速さ＝移動ベクトル

	}
	m_position = m_characterController.Execute(m_moveSpeed, 1.0f / 60.0f);//敵がプレイヤーを見つけたら追いかける動きが滑らかになる
	m_enemyModelRender.SetPosition(m_position);
}

//新しい構造体を定義して継承している。 btCollisionWorldは衝突判定を行う ConvexResultCallbackはぶつかったときの処理。
struct SweepResultWall : public btCollisionWorld::ConvexResultCallback
{
	bool isHit = false; //オブジェクトが衝突したかどうかを判定する。

	//virtualとは仮想関数を定義するもの
	virtual btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
	{
		//ぶつかったオブジェクトが壁じゃなかったら処理を終了する
		if (convexResult.m_hitCollisionObject->getUserIndex() != enCollisionAttr_Wall)
		{
			return 0.0f;
		}

		//壁とぶつかったらフラグをtrueにする。
		isHit = true;
		return 0.0f;
	}
};

void GoastEnemy::SearchPlayer()
{
	m_isSearchPlayer = false;

	m_forward = Vector3::AxisZ; //Axisとは軸のこと
	m_rotation.Apply(m_forward);//回転を適用して新しい方向を得る

	Vector3 playerPosition = m_player->GetPosition(); //プレイヤーのポジションを定義する
	Vector3 diff = playerPosition - m_position; //プレイヤーのポジションと敵のポジションを比較する。

	diff.Normalize();//Normalizeを使ってどんな方向でも移動速度が一定になる
	float angle = acosf(diff.Dot(m_forward));//acosfを使って敵がどこを見ているか判定する
	if (Math::PI * 0.25f <= fabsf(angle))//プレイヤーが視界外だったら。　ここでのPIは円周率のことを示しており、Mathは数学関数で主に使われる
	{
		return;//プレイヤーはみつかっていない
	}

	btTransform start, end; //位置と回転を表す変数startとend
	start.setIdentity();
	end.setIdentity();

	start.setOrigin(btVector3(m_position.x, m_position.y + 60.0f, m_position.z));//敵の視点が目と同じ視線になってプレイヤーを探す
	end.setOrigin(btVector3(playerPosition.x, playerPosition.y + 70.0f, playerPosition.z));//プレイヤーも目の高さに設定する

	SweepResultWall callback;//エネミーとプレイヤーの間に壁があるかどうか調べる

	//敵がプレイヤーを視認できるかどうかを判定する。
	PhysicsWorld::GetInstance()->ConvexSweepTest((const btConvexShape*)m_spherCollider.GetBody(), start, end, callback);

	//壁と衝突した。
	if (callback.isHit == true)
	{
		return;//プレイヤーは見つかっていない。
	}

	m_isSearchPlayer = true; //壁にぶつからずプレイヤーを見つけたらフラグをtrueにする。
}
void GoastEnemy::Render(RenderContext& rc)
{
	m_enemyModelRender.Draw(rc);

	if (m_isSearchPlayer == false)
	{
		m_fontRender.SetText(L"みつからん");
	}
	if(m_isSearchPlayer==true)
	{
		m_fontRender.SetText(L"見つけたよ!!!!!!!!");
	}
	m_fontRender.Draw(rc);
}
