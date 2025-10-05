#pragma once


class Player : public IGameObject
{
public:
    Player();
    ~Player();

    bool Init();
    void Update();
    void Move();
    void ManageState();  // �X�e�[�g�Ǘ�
    void Render(RenderContext& rc);

    bool ShotInit();
    void ShotUpdate();   // �V���b�g�X�V


    CharacterController& GetCharacterController()
    {
        return m_characterController;
    }

    Quaternion rotX, rotY;   // ��]�p�i�N�H�[�^�j�I���j
    Quaternion rotation;     // ������]�p

    // --- �����o�ϐ� ---
    Vector3 m_position = Vector3::Zero; // ���W
    Vector3 moveSpeed;                  // �ړ����x
    float m_verticalSpeed = 0.0f;       // ���������̑��x�i�W�����v�E������p�j
    int playerState = 0;                // �v���C���[�̃X�e�[�g

    CharacterController m_characterController; // �L�����N�^�[�R���g���[���[
    ModelRender m_modelRender;                           // �v���C���[���f��
    ModelRender m_bulletModel;                         // �e���f��

private:
    enum EnAnimationClip {		//�A�j���[�V�����B
        enAnimationClip_Idle,
        enAnimationClip_Walk,
        enAnimationClip_Jump,
        enAnimationClip_Num,
    };

    AnimationClip animationClips[enAnimationClip_Num];		//�A�j���[�V�����N���b�v�B

    Vector3 m_shotPos;                 // �V���b�g�ʒu
    Vector3 m_shotDir = Vector3::Zero; // �V���b�g����
    bool m_isShot = false;             // �V���b�g���

    // �e���X�g
    struct Shot {
        Vector3 pos;        // ���݈ʒu
        Vector3 startPos;   // ���˒n�_�i��������p�j
        Vector3 dir;        // �ړ�����
        bool active = false; // �g�p�����ǂ���
    };
    std::vector<Shot> m_shots;

    // ���ˊԊu�Ǘ�
    float m_timer = 0.0f;
    float m_shotInterval = 0.5f;
};