#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"

GameCamera::GameCamera() = default;
GameCamera::~GameCamera() = default;

bool GameCamera::Init()
{
    // �����J�����I�t�Z�b�g�i�����_����J�����܂ł̋����j
    m_toCameraPos = Vector3(0.0f, 150.0f, 10.0f);

    // �v���C���[�I�u�W�F�N�g������
    m_player = FindGO<Player>("player");

    // �J�����̃j�A�E�t�@�[�N���b�v�ݒ�
    g_camera3D->SetNear(1.0f);
    g_camera3D->SetFar(10000.0f);

    return true;
}

void GameCamera::Update()
{
    if (!m_player) {
        return; // �v���C���[��������Ȃ��ꍇ�͏������I��
    }

    // �v���C���[�̈ʒu���擾
    Vector3 playerPosition = m_player->m_position;

    // �J�����̏��������_�ƈʒu
    Vector3 target = playerPosition;
    target.y += 200.0f; // �v���C���[�̎����̍������������
    Vector3 cameraPosition = target + m_toCameraPos;

    // �E�X�e�B�b�N�̓��́i�J������]�p�j
    float x = g_pad[0]->GetRStickXF(); // ������] (Y��)
    float y = g_pad[0]->GetRStickYF(); // ������] (X��)

    // ���������̉�]���v�Z
    Quaternion horizontalRotation;
    horizontalRotation.SetRotationDeg(Vector3::AxisY, 3.0f * x); // �E�X�e�B�b�NX���ŉ�]

    // �J�����̉�]�𔽉f
    horizontalRotation.Apply(m_toCameraPos);

    // ���������̉�]�𐧌��i�㉺���_�����j
    Vector3 toPosDir = m_toCameraPos;
    toPosDir.Normalize();
    if (toPosDir.y < -0.5f) {
        m_toCameraPos.y = -0.5f;
    }
    else if (toPosDir.y > 0.5f) {
        m_toCameraPos.y = 0.5f;
    }

    // ���X�e�B�b�N�̓��͂ňړ�
    Vector3 stickL;
    stickL.x = g_pad[0]->GetLStickXF();
    stickL.y = g_pad[0]->GetLStickYF();
    if (fabsf(stickL.x) > 0.001f || fabsf(stickL.y) > 0.001f) {
        // ���X�e�B�b�N�̓��͂ɂ��O�i�E��ށE���E�ړ�
        Vector3 forward = g_camera3D->GetForward();
        Vector3 right = g_camera3D->GetRight();
        forward.y = 0.0f; // Y�������͈ړ������Ȃ�
        right.y = 0.0f; // Y�������͈ړ������Ȃ�

        forward.Normalize();
        right.Normalize();

        forward *= stickL.y * 240.0f;
        right *= stickL.x * 240.0f;

        Vector3 moveSpeed = forward + right;
        m_player->m_position = m_player->m_characterController.Execute(moveSpeed, 1.0f / 60.0f);
    }

    // �v���C���[�̃��f�����E�X�e�B�b�N�̉�]�𔽉f
    Quaternion playerRotation = m_player->rotation;
    playerRotation = horizontalRotation * playerRotation;
    m_player->rotation = playerRotation;

    // ���f�������_���[�ɉ�]�𔽉f
    m_player->m_modelRender.SetRotation(playerRotation);

    // �J�����̈ʒu���v�Z
    cameraPosition = target + m_toCameraPos;

    // ���C���J�����ɒ����_�Ǝ��_��ݒ�
    g_camera3D->SetTarget(target);
    g_camera3D->SetPosition(cameraPosition);

    // �J�������X�V
    g_camera3D->Update();
}
