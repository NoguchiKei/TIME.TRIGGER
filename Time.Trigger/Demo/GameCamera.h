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
    Player* m_player = nullptr;      // プレイヤー参照
    Vector3 m_toCameraPos;           // 注視点からカメラ位置へのベクトル（オフセット）

};

