#include "stdafx.h"
#include "BackGround.h"

namespace
{
    const Vector3 SCALE      = Vector3{ 0.1f,0.1f,0.1f };
    const Vector3 SMALL      = Vector3{ 0.1f,0.1f,0.1f };
    const Vector3 SLOUPSCALE = Vector3{ 3.0f,3.0f,5.0f };
    const Vector3 SECONDSLOUPSCALE = Vector3{ 4.0f,8.0f,14.0f };
    const Vector3 TABLESCALE = Vector3{ 50.0f,3.0f,30.0f };
    const Vector3 SECONDTABLE = Vector3{ 10.0f,8.0f,10.0f };
    const Vector3 THIRDTABLE = Vector3{ 10.0f,8.0f,10.0f };

}
BackGround::BackGround()
{
    m_modelRender.Init("Assets/modelData/ground.tkm");
    m_modelRender.SetPosition(Vector3::Zero);
    m_modelRender.Update();
    physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());

    m_itemModelRender.Init("Assets/modelData/ground.tkm");
    m_itemModelRender.SetPosition({ 3800.0f, 100.0f, 1500.0f });
    m_itemModelRender.SetScale(SCALE);
    m_itemModelRender.Update();
    m_physicsStaticObject.CreateFromModel(m_itemModelRender.GetModel(), m_itemModelRender.GetModel().GetWorldMatrix());

    m_groundModelRender.Init("Assets/modelData/ground.tkm");
    m_groundModelRender.SetPosition({ 3800.0f, 100.0f, -1500.0f });
    m_groundModelRender.SetScale(SMALL);
    m_groundModelRender.Update();
    m_groundphysicsStaticObject.CreateFromModel(m_groundModelRender.GetModel(), m_groundModelRender.GetModel().GetWorldMatrix());

    m_sloupModelRender.Init("Assets/modelData/sloup.tkm");
    m_sloupModelRender.SetPosition({ 1000.0f,-10.0f,200.0f });
    m_sloupModelRender.SetScale(SLOUPSCALE);
    m_sloupModelRender.Update();
    m_sloupphysicsStaticObject.CreateFromModel(m_sloupModelRender.GetModel(), m_sloupModelRender.GetModel().GetWorldMatrix());

    m_secondsloupModelRender.Init("Assets/modelData/sloup.tkm");
    m_secondsloupModelRender.SetPosition({ 2300.0f,110.0f,-400.0f });
    m_secondsloupModelRender.SetScale(SECONDSLOUPSCALE);
    m_secondsloupModelRender.Update();
    m_secondsloupphysicsStaticObject.CreateFromModel(m_secondsloupModelRender.GetModel(), m_secondsloupModelRender.GetModel().GetWorldMatrix());


    m_tableModelRender.Init("Assets/modelData/table.tkm");
    m_tableModelRender.SetPosition({ 1500.0f,-10.0f,-465.0f});
    m_tableModelRender.SetScale(TABLESCALE);
    m_tableModelRender.Update();
    m_tablePhysicsStaticObject.CreateFromModel(m_tableModelRender.GetModel(), m_tableModelRender.GetModel().GetWorldMatrix());

    m_secondtableModelRender.Init("Assets/modelData/table.tkm");
    m_secondtableModelRender.SetPosition({ 2500.0f,-10.0f,-465.0f });
    m_secondtableModelRender.SetScale(SECONDTABLE);
    m_secondtableModelRender.Update();
    m_secondtablePhysicsStaticObject.CreateFromModel(m_secondtableModelRender.GetModel(), m_secondtableModelRender.GetModel().GetWorldMatrix());

    m_thirdtableModelRender.Init("Assets/modelData/table.tkm");
    m_thirdtableModelRender.SetPosition({ 1500.0f,-10.0f,-1465.0f });
    m_thirdtableModelRender.SetScale(THIRDTABLE);
    m_thirdtableModelRender.Update();
    m_thirdtablePhysicsStaticObject.CreateFromModel(m_thirdtableModelRender.GetModel(), m_thirdtableModelRender.GetModel().GetWorldMatrix());
}

BackGround::~BackGround()
{

}

void BackGround::Render(RenderContext& rc)
{
    //ÉÇÉfÉãÇï`âÊÇ∑ÇÈÅB
    m_modelRender.Draw(rc);
    m_itemModelRender.Draw(rc);
    m_groundModelRender.Draw(rc);
    m_sloupModelRender.Draw(rc);
    m_secondsloupModelRender.Draw(rc);
    m_tableModelRender.Draw(rc);
    m_secondtableModelRender.Draw(rc);
    m_thirdtableModelRender.Draw(rc);

}
