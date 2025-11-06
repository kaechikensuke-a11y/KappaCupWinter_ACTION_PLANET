#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "BackGround.h"
#include "GameCamera.h"
#include "Jumpitem.h"
#include "GoastEnemy.h"
#include "nature/SkyCube.h";


bool Game::Start()
{
	player = NewGO<Player>(0, "player");

	gamecamera = NewGO<GameCamera>(0, "gamecamera");

	background = NewGO<BackGround>(0, "background");

	jumpitem = NewGO<Jumpitem>(0, "jumpitem");

	goastenemy = NewGO<GoastEnemy>(0, "goastenemy");

	InitSky();

	return true;
}

void Game::Update()
{
	//当たり判定を可視化する。
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

	// g_renderingEngine->DisableRaytracing();

	m_timer -= g_gameTime->GetFrameDeltaTime();
	int minute = (int)m_timer / 60; //秒数から60引いて分数の計算をする
	int sec = (int)m_timer % 60;//その余りが秒数になる

	wchar_t text[256];//wchar_tはUnicode対応の文字型
	swprintf_s(text, 256, L"残り時間 : %02d:%02d", minute, sec);//日本語を扱うためのswprintf_s
	m_timerRender.SetText(text);
	m_timerRender.SetPosition({ 0.0f, 480.0f, 0.0f });
	m_timerRender.SetScale(1.5f);
	m_timerRender.SetColor(g_vec4White);
}

void Game::Render(RenderContext& rc)
{
	m_timerRender.Draw(rc);
}

void Game::InitSky()
{
	//現在の空を破棄。
	DeleteGO(m_skyCube);

	m_skyCube = NewGO<SkyCube>(0, "skycube");
	m_skyCube->SetType((EnSkyCubeType)m_skyCubeType);

	//環境光の計算のためのIBLテクスチャをセットする。
	g_renderingEngine->SetAmbientByIBLTexture(m_skyCube->GetTextureFilePath(), 0.1f);
}