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

    // “–‚½‚è”»’è
    PhysicsStaticObject m_bgObject;
};