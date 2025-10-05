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
	//�v���C���[�̃I�u�W�F�N�g�����B
	m_player = NewGO<Player>(0, "player");
	m_player->Init();
	m_player->ShotInit();

	//�G�̃I�u�W�F�N�g�����B
	m_enemy = NewGO<EnemyManager>(0, "enemy");
	m_enemy->Init();


	//�w�i�̃I�u�W�F�N�g�����B
	m_backGround = NewGO<BackGround>(0, "backGround");
	m_backGround->Init();

	//�J�����̃I�u�W�F�N�g�����B
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