#include "stdafx.h"
#include "Game.h"
#include "BackGround.h"
#include "Player.h"
#include "GameCamera.h"
#include "EnemyManager.h"

Game::Game() {}

Game::~Game()
{
	DeleteGO(m_backGround);
	DeleteGO(m_player);
	DeleteGO(m_gameCamera);
	DeleteGO(m_enemy);

}



bool Game::Start()
{
	//プレイヤーのオブジェクトを作る。
	m_player = NewGO<Player>(0, "player");
	m_player->Init();
	m_player->ShotInit();

	//敵のオブジェクトを作る。
	m_enemy = NewGO<EnemyManager>(0, "enemy");
	m_enemy->Init();


	//背景のオブジェクトを作る。
	m_backGround = NewGO<BackGround>(0, "backGround");
	m_backGround->Init();

	//カメラのオブジェクトを作る。
	m_gameCamera = NewGO<GameCamera>(0, "gameCamera");
	m_gameCamera->Init();

	return true;
}

void Game::Update()
{


}

void Game::Render(RenderContext& rc)
{

}