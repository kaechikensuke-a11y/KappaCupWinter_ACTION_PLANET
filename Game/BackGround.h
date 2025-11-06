#pragma once
class BackGround : public IGameObject

{
public:
    BackGround();
    ~BackGround();

    //描画関数。
    void Render(RenderContext& rc);

    //モデルレンダ―。        
    ModelRender m_modelRender;
    ModelRender m_itemModelRender;
    ModelRender m_groundModelRender;
    ModelRender m_sloupModelRender;
    ModelRender m_secondsloupModelRender;
    ModelRender m_tableModelRender;
    ModelRender m_secondtableModelRender;
    ModelRender m_thirdtableModelRender;

    PhysicsStaticObject m_physicsStaticObject;
    PhysicsStaticObject physicsStaticObject;
    PhysicsStaticObject m_groundphysicsStaticObject;
    PhysicsStaticObject m_sloupphysicsStaticObject;
    PhysicsStaticObject m_tablePhysicsStaticObject;
    PhysicsStaticObject m_secondtablePhysicsStaticObject;
    PhysicsStaticObject m_thirdtablePhysicsStaticObject;
    PhysicsStaticObject m_secondsloupphysicsStaticObject;
 

};
