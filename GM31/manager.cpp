#include "main.h"
#include "manager.h"
#include "renderer.h"
#include<wrl.h>
#include"Scene.h"
#include"Keyboard.h"
#include"Game.h"
#include"Title.h"
#include"audio.h"
std::shared_ptr<Scene> Manager::m_Scene;

void Manager::Init()
{
	Renderer::Init();
	Keyboard::Init();
	Audio::InitMaster();
	//m_Scene = std::make_shared<Title>();
	//m_Scene->Init();
	SetScene<Title>();
}

void Manager::Uninit()
{
	m_Scene->UnInit();
	Keyboard::Uninit();
	Renderer::Uninit();
	Audio::UninitMaster();
	//m_Scene.reset();
}

void Manager::Update()
{
	Keyboard::Update();
	m_Scene->Update();
}

void Manager::Draw()
{
	Renderer::Begin();
	
	m_Scene->Draw();

	Renderer::End();
}
