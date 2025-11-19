#include "stdafx.h"
#include "Game.h"
#include "BackGround.h"
#include "Player.h"
#include "GameCamera.h"
#include "EnemyManager.h"
#include "GameClear.h"

Game::Game() {}

Game::~Game()
{
	DeleteGO(m_backGround);
	DeleteGO(m_player);
	DeleteGO(m_gameCamera);
	DeleteGO(m_enemyMgr);

}



bool Game::Start()
{
	//プレイヤーのオブジェクトを作る。
	m_player = NewGO<Player>(0, "player");
	m_player->Init();
	m_player->ShotInit();

	//敵のオブジェクトを作る。
	m_enemyMgr = NewGO<EnemyManager>(0, "enemy");
	m_enemyMgr->Init();
	m_enemyMgr->SetPlayer(m_player);


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
	// 敵が全滅したらゲームクリア画面へ遷移
	if (m_enemyMgr->IsAllDead()) {
		NewGO<GameClear>(0, "gameClear");  // ← GameClear シーンを作る想定
		DeleteGO(this);                   // 今のゲームシーンを削除
		return;
	}

}

void Game::Render(RenderContext& rc)
{

}