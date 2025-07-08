#include "Framework.h"

#include "Scenes/MapEditScene.h"
//#include "Scenes/TestScene.h"
#include "Scenes/LobyScene.h"
#include "Scenes/StoreScene.h"
#include "Scenes/StartScene.h"
#include "Scenes/Stage1Scene.h"
#include "Scenes/Stage2Scene.h"
#include "Scenes/BossStageScene.h"
GameManager::GameManager()
{
	Create();
		
	SCENE->AddScene("Edit", new MapEditScene());
	//SCENE->AddScene("Game", new TestScene());
	SCENE->AddScene("Store", new StoreScene());
	SCENE->AddScene("Loby", new LobyScene());
	SCENE->AddScene("Start", new StartScene());
	SCENE->AddScene("Stage1", new Stage1Scene());
	SCENE->AddScene("Stage2", new Stage2Scene());
	SCENE->AddScene("BossStage", new BossStageScene());

	SCENE->ChangeScene("Start");
}

GameManager::~GameManager()
{
	Release();
}

void GameManager::Update()
{
	Timer::Get()->Update();
	Input::Get()->Update();
	Audio::Get()->Update();

	Environment::Get()->Update();

	SCENE->Update();

	InvalidateRect(hWnd, nullptr, false);
}

void GameManager::Render()
{
	SCENE->PreRender();
	
	Environment::Get()->SetViewport();
	Device::Get()->Clear();	

	SCENE->Render();

	Environment::Get()->SetUIViewBuffer();
	SCENE->PostRender();

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	string fps = "FPS : " + to_string(Timer::Get()->GetFPS());
	ImGui::Text(fps.c_str());

	SCENE->GUIRender();	

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	Device::Get()->Present();
}

void GameManager::Create()
{
	Timer::Get();
	Input::Get();
	Audio::Get();

	Device::Get();

	SceneManager::Get();

	Environment::Get();

	BlockFactory::Get();
	BubbleManager::Get();
	MonsterManager::Get();
	ItemManager::Get();
	UIManager::Get();

	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX11_Init(DEVICE, DC);
}

void GameManager::Release()
{
	Timer::Delete();
	Input::Delete();

	Device::Delete();
	Shader::Delete();
	Texture::Delete();
	Audio::Delete();

	SceneManager::Delete();

	Environment::Delete();

	BlockFactory::Delete();
	BubbleManager::Delete();
	MonsterManager::Delete();
	ItemManager::Delete();
	UIManager::Delete();

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();

	ImGui::DestroyContext();
}
