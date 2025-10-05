#pragma once
class BackGround : public IGameObject
{
public:
    BackGround();
    ~BackGround();

    bool Init();
    void Update();
    void Render(RenderContext& rc);


private:
    ModelRender m_bg;

    // �����蔻��
    PhysicsStaticObject m_bgObject;
};