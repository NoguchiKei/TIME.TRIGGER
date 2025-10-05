#pragma once


class Player : public IGameObject
{
public:
    Player();
    ~Player();

    bool Init();
    void Update();
    void Move();
    void ManageState();  // ステート管理
    void Render(RenderContext& rc);

    bool ShotInit();
    void ShotUpdate();   // ショット更新


    CharacterController& GetCharacterController()
    {
        return m_characterController;
    }

    Quaternion rotX, rotY;   // 回転用（クォータニオン）
    Quaternion rotation;     // 合成回転用

    // --- メンバ変数 ---
    Vector3 m_position = Vector3::Zero; // 座標
    Vector3 moveSpeed;                  // 移動速度
    float m_verticalSpeed = 0.0f;       // 垂直方向の速度（ジャンプ・落下専用）
    int playerState = 0;                // プレイヤーのステート

    CharacterController m_characterController; // キャラクターコントローラー
    ModelRender m_modelRender;                           // プレイヤーモデル
    ModelRender m_bulletModel;                         // 弾モデル

private:
    enum EnAnimationClip {		//アニメーション。
        enAnimationClip_Idle,
        enAnimationClip_Walk,
        enAnimationClip_Jump,
        enAnimationClip_Num,
    };

    AnimationClip animationClips[enAnimationClip_Num];		//アニメーションクリップ。

    Vector3 m_shotPos;                 // ショット位置
    Vector3 m_shotDir = Vector3::Zero; // ショット方向
    bool m_isShot = false;             // ショット状態

    // 弾リスト
    struct Shot {
        Vector3 pos;        // 現在位置
        Vector3 startPos;   // 発射地点（寿命判定用）
        Vector3 dir;        // 移動方向
        bool active = false; // 使用中かどうか
    };
    std::vector<Shot> m_shots;

    // 発射間隔管理
    float m_timer = 0.0f;
    float m_shotInterval = 0.5f;
};