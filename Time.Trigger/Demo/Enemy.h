#pragma once


class Enemy : public IGameObject
{
public:
    Enemy();
    ~Enemy();
    bool Init();
    void Update();
    void Render(RenderContext& rc);

    void OnHit();   // 撃たれた時に呼ぶ

    void SetInitPos(const Vector3& pos);


private:
    void Move();
    void ManageState();

    ModelRender m_modelRender;
    CharacterController m_characterController;

    Vector3 m_position;

    bool m_isAlive = true;
    float m_respawnTimer = 0.0f;
    Vector3 m_initPos;   // 初期座標を保持
    int m_enemyState = 0;   // 敵のステート
};