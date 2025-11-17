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
    ModelRender m_bg2;

    // “–‚½‚è”»’è
    PhysicsStaticObject m_bgObject;
};