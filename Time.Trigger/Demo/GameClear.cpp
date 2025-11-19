#include "stdafx.h"
#include "GameClear.h"
#include "Title.h"

GameClear::GameClear() {}
GameClear::~GameClear() {}

bool GameClear::Start()
{
	// ゲームクリア画面の初期化処理をここに記述
	spriteRender.Init("Assets/Sprite/game_clear.DDS", 1917.0f, 1069.0f);

	return true;
}

void GameClear::Update()
{
	// ゲームクリア画面の更新処理をここに記述
	//Aボタンが押されたら。
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		
		//タイトルのオブジェクトを作る
		NewGO<Title>(0, "title");
		//自身を削除する。
		DeleteGO(this);
	}
}

void GameClear::Render(RenderContext& rc)
{
	spriteRender.Draw(rc);
}
