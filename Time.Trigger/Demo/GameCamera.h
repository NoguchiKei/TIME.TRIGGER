#pragma once

class Player;

class GameCamera : public IGameObject
{
public:
    GameCamera();
    ~GameCamera();

    bool Init();
    void Update();


private:
    Player* m_player = nullptr;      // �v���C���[�Q��
    Vector3 m_toCameraPos;           // �����_����J�����ʒu�ւ̃x�N�g���i�I�t�Z�b�g�j

};

