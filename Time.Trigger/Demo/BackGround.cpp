#include "stdafx.h"
#include "BackGround.h"


BackGround::BackGround() = default;
BackGround::~BackGround() = default;

bool BackGround::Init()
{
    m_bg.Init("Assets/modelData/BackGround/Demo_Stage03_kansei.tkm");
  

    //m_bg.SetPosition(Vector3(0.0f, 0.0f, 0.0f));
    //m_bg.SetScale(Vector3(-1.0f, 1.0f, 1.0f));

    // Update���ă��[���h�s����m�肳����
    m_bg.Update();

    // �����œ����蔻��쐬
    m_bgObject.CreateFromModel(m_bg.GetModel(),
        m_bg.GetModel().GetWorldMatrix());

   // PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
    return true;
}

void BackGround::Update()
{
	m_bg.Update();
}

void BackGround::Render(RenderContext& renderContext)
{
	m_bg.Draw(renderContext);
}