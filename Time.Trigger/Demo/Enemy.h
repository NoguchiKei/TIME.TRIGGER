#pragma once
#include "tkFile/TknFile.h"
#include "AI/PathFinding/NaviMesh.h"
#include "AI/PathFinding/Path.h"
#include "AI/PathFinding/PathFinding.h"

class Player;
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

	Player* m_player = nullptr; // プレイヤーの参照

    bool m_isAlive = true;
    float m_respawnTimer = 0.0f;
    Vector3 m_initPos;   // 初期座標を保持
    int m_enemyState = 0;   // 敵のステート
    Vector3 m_enemyForward = { 0.0f, 0.0f, -1.0f };	// 敵の前方ベクトル
    Quaternion m_rotation;  //クォータニオン。

    //ナビメッシュ
    nsAI::NaviMesh m_nvmMesh;
    nsAI::Path m_path;
    nsAI::PathFinding m_pathFiding;
};