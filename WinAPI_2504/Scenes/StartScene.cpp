#include "Framework.h"
#include "StartScene.h"

StartScene::StartScene()
{
	CreateAnimation(); // 애니메이션 관련된거 전부 생성
	AddAudio();
}

StartScene::~StartScene()
{
	delete animation;
}

void StartScene::Update()
{
	if(curStatus == StartPanel1)
		UIManager::Get()->Update();
	else
	{
		animation->Update(curStatus);
		ChangeStatus();
	}
}

void StartScene::Render()
{
	if(curStatus == StartPanel1)
		UIManager::Get()->Render();
	else
	{
		worldBuffer->Set(transform->GetWorld());
		worldBuffer->SetVS(0);
		animation->Render(curStatus);
	}
}

void StartScene::Start()
{
	curStatus = StartAni1;
	animation->Play(curStatus);
}

void StartScene::End()
{
	UIManager::Get()->Reset();
	Audio::Get()->Stop("bg_Start");
}

void StartScene::ChangeStatus()
{
	if (curStatus == StartPanel1) return;

	if (!animation->IsPlay(curStatus))
	{
		curStatus = (StartStatus)((int)curStatus + 1);
		if (curStatus == StartPanel1)
		{
			Audio::Get()->Play("bg_Start");
			UIManager::Get()->AddShowPanel(PanelType::StartPanel);
			return;
		}
		animation->Play(curStatus);
	}
}

void StartScene::CreateAnimation()
{
	animation = new Animation;

	animation->LoadClip("Resources/Textures/CrazyArcade_UI/Start/", "Start1.xml", false,0.4f);
	animation->LoadClip("Resources/Textures/CrazyArcade_UI/Start/", "Start2.xml", false,0.5f);


	transform = new Transform();
	transform->SetLocalPosition(700, 480);
	transform->UpdateWorld();

	worldBuffer = new MatrixBuffer;
}

void StartScene::AddAudio()
{
	string folderPath = "Resources/Sound/";
	string searchPath = folderPath + "*.*";

	WIN32_FIND_DATAA findData;
	HANDLE hFind = FindFirstFileA(searchPath.c_str(), &findData);

	if (hFind == INVALID_HANDLE_VALUE)
		return;

	do {
		if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
			string fileName = findData.cFileName;

			// 확장자 검사
			if (fileName.find(".ogg") != string::npos || fileName.find(".mp3") != string::npos
				|| fileName.find(".wav") != string::npos) {
				string fullPath = folderPath + fileName;
				string key = fileName.substr(0, fileName.find_last_of('.'));

				bool isBgm = key.find("bg") != string::npos;
				bool isLoop = key.find("ef") == string::npos;

				Audio::Get()->Add(key, fullPath, isBgm, isLoop);
			}
		}

	} while (FindNextFileA(hFind, &findData));

	FindClose(hFind);
}
