#include "stdafx.h"
#include "Title.h"
#include "Game.h"

Title::Title() {}
Title::~Title() {}

bool Title::Start()
{
	spriteRender.Init("Assets/Sprite/game_title.DDS", 1917.0f, 1069.0f);
	return true;
}

void Title::Update()
{
	
	
	if (g_pad[0]->IsTrigger(enButtonA)) {
		NewGO<Game>(0, "game");  
		DeleteGO(this);         
		return;
	}
}

void Title::Render(RenderContext& rc)
{
	
	spriteRender.Draw(rc);
}