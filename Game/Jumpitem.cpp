#include "stdafx.h"
#include "Jumpitem.h"
#include "Game.h"
#include "Player.h"

namespace 
{
	const Vector3 FIRST_ITEM_POS = { 250.0f, 0.0f, 250.0f };
	const float PICKUP_DISTANCE  = { 20.0f };
	const float ROTATIONOBJECT   = { 10.0f };
}


Jumpitem::Jumpitem()
{
	m_JumpRender.Init("Assets/modelData/All.tkm");
	m_position = FIRST_ITEM_POS;
	m_JumpRender.SetPosition(m_position);
	m_JumpRender.Update();
	//physicsStaticObject.CreateFromModel(m_JumpRender.GetModel(), m_JumpRender.GetModel().GetWorldMatrix());
}

Jumpitem::~Jumpitem()
{

}

bool Jumpitem::Start()
{
	m_player = FindGO<Player>("player");
	return true;
}

void Jumpitem::Update()
{
	Move();
	Rotation();
	
	if (m_player == nullptr)
	{
		return;
	}
	
	Vector3 diff = m_position - m_player->m_position;
	
	if (diff.Length() <= PICKUP_DISTANCE)
	{
		m_player->getJumpItem = true;
		DeleteGO(this);
	}

	m_JumpRender.Update();
}

void Jumpitem::Move()
{
	m_JumpRender.SetPosition(m_position);
}

void Jumpitem::Rotation()
{
	m_rotation.AddRotationDegY(ROTATIONOBJECT);
	m_JumpRender.SetRotation(m_rotation);
}

void Jumpitem::Render(RenderContext& rc)
{
	m_JumpRender.Draw(rc);
}