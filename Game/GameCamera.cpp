#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"

bool GameCamera::Start()
{
	m_toCameraPos.Set(0.0f, 125.0f, -250.0f);

	m_player = FindGO<Player>("player");

	//ばねカメラの初期化
	//1000.0fはカメラの速度
	//trueは地形と当たり判定を有効化
	//5.0fはカメラの球体コリジョンの半径(地形との衝突判定に使う)
	m_springCamera.Init(*g_camera3D, 1000.0f, true, 5.0f);	

	//g_camera3D->SetNear(1.0f);
	//g_camera3D->SetFar(15000.0f);

	return true;
}
void GameCamera::Update()
{
	Vector3 target = m_player->m_position;

	target.y += 80.0f;

	//カメラの向いている方向に20.0f分進んだ位置を計算
	target += g_camera3D->GetForward() * 20.0f;

	Vector3 toCameraPosOld = m_toCameraPos;

	float x = g_pad[0]->GetRStickXF();
	float y = g_pad[0]->GetRStickYF();

	Quaternion qRot;
	qRot.SetRotationDeg(Vector3::AxisY, 1.3f * x);
	qRot.Apply(m_toCameraPos);

	Vector3 axisX;
	axisX.Cross(Vector3::AxisY, m_toCameraPos);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX, 1.3f * y);
	qRot.Apply(m_toCameraPos);

	Vector3 toPosDir = m_toCameraPos;
	toPosDir.Normalize();
	if (toPosDir.y < -0.5f)
	{
		m_toCameraPos = toCameraPosOld;
	}
	else if (toPosDir.y > 0.8f)
	{
		m_toCameraPos = toCameraPosOld;
	}

	Vector3 pos = target + m_toCameraPos;

	g_camera3D->SetTarget(target);
	g_camera3D->SetPosition(pos);

	//カメラの更新
	//これがないとそもそもカメラの機能がなくなる
	m_springCamera.Update();
}
