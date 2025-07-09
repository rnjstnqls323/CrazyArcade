#include "Framework.h"
#include "MapEditScene.h"

MapEditScene::MapEditScene()
{
	//CreateEditTiles();
	LoadTextures();
}

MapEditScene::~MapEditScene()
{
	delete backGround;
	DeleteEditTiles();
}

void MapEditScene::Update()
{
	if(backGround != nullptr)
		backGround->UpdateWorld();
	if (ImGui::GetIO().WantCaptureMouse) return;

	EditBgTiles();
}

void MapEditScene::Render()
{
	if (backGround != nullptr)
		backGround->Render();

	for (EditTile* tile : tiles)
	{
		tile->Render();
	}
	
}

void MapEditScene::GUIRender()
{

	ImGui::Text("Map Editor");
	ImGui::NewLine();
	SaveDialog();
	ImGui::SameLine();
	LoadDialog();
	ImGui::NewLine();
	if (ImGui::Button("Create Tiles"))
	{
		CreateEditTiles();
	}

	if (ImGui::Button("Create BackGround"))
	{
		CreateBackGround();
	}

	if (ImGui::Button("Reset Tiless"))
	{
		ResetTiles();
	}

	RenderSampleButtons();
}

void MapEditScene::Start()
{
	CreateEditTiles();
	CreateBackGround();
}

void MapEditScene::End()
{

}

//블록 선택 후 타일 고르면 바뀌게 해주는 코드
//Monster EndNode때문에 블록에 태그 붙여주는 작업도 하고있다. End먼저 깔고 몬스터 올려야됨
void MapEditScene::EditBgTiles()
{
	if (!Input::Get()->IsKeyDown(VK_LBUTTON)&& !Input::Get()->IsKeyPress(VK_RBUTTON))
		return;
	
	for (EditTile* tile : tiles)
	{
		if (tile->IsPointCollision(mousePos))
		{
			tile->GetImage()->GetMaterial()->SetBaseMap(selectTexture);
			
			wstring file = selectTexture->GetFile();
			EditTileType type = EditTileType::NormalTile;

			if (file.find(L"Monster") != wstring::npos)
			{
				type = EditTileType::MonsterTilePos;
				tile->SetTileTag(tag++);
			}
			else if (file.find(L"EndNode") != wstring::npos)
			{
				type = EditTileType::EndNodeTilePos;
				tile->SetTileTag(tag);
			}
			tile->SetEditTileType(type);
		}
	}
}

void MapEditScene::RenderSampleButtons()
{
	if (ImGui::TreeNode("Block Buttons"))
	{
		int count = 0;

		for (Texture* texture : sampleTextures)
		{
			string key = Utility::ToString(texture->GetFile());
			ImTextureID imguiTextureID = (ImTextureID)texture->GetSRV();

			if (ImGui::ImageButton(key.c_str(), imguiTextureID, ImVec2(50, 50)))
			{
				selectTexture = texture;
			}

			count++;

			if (count % COL_BUTTON_NUM)
			{
				ImGui::SameLine();
			}

		}

		ImGui::TreePop();
	}
	ImGui::NewLine();

	if (ImGui::TreeNode("Stage Buttons"))
	{
		int count = 0;

		for (Texture* texture : sampleBackground)
		{
			string key = Utility::ToString(texture->GetFile());
			ImTextureID imguiTextureID = (ImTextureID)texture->GetSRV();

			if (ImGui::ImageButton(key.c_str(), imguiTextureID, ImVec2(50, 50)))
			{
				backGround->GetMaterial()->SetBaseMap(texture->GetFile());
			}

			count++;

			if (count % COL_BUTTON_NUM)
			{
				ImGui::SameLine();
			}

		}

		ImGui::TreePop();
	}
}

void MapEditScene::CreateEditTiles()
{

	DeleteEditTiles();

	Vector2 startPos = Vector2(TILE_SIZE.x * 0.5f + 100, SCREEN_HEIGHT - TILE_SIZE.y * 0.5f - 30);

	for (int y = 0; y < ROW; y++)
	{
		for (int x = 0; x < COL; x++)
		{
			EditTile* tile = new EditTile();
			Vector2 pos = startPos + Vector2(x * tile->Size().x, -y * tile->Size().y);
			tile->SetLocalPosition(pos);
			tile->Update();
			tiles.push_back(tile);
		}
	}
}

void MapEditScene::DeleteEditTiles()
{

	for (EditTile* tile : tiles)
	{
		delete tile;
	}
	tiles.clear();
}

void MapEditScene::CreateBackGround()
{
	delete backGround;

	backGround = new Quad(L"Resources/Textures/CrazyArcade_BG/NoneStage.png");

	backGround->SetLocalPosition({ 600,480 }); //이쁜 위치
	backGround->UpdateWorld();
}

void MapEditScene::LoadTextures()
{
	WIN32_FIND_DATA findData;

	HANDLE handle = FindFirstFile(L"Resources/Textures/CrazyArcade_BG_Texture/*.png", &findData);

	bool result = true;
	wstring path = L"Resources/Textures/CrazyArcade_BG_Texture/";

	while (result)
	{
		Texture* texture = Texture::Add(path + findData.cFileName);
		sampleTextures.push_back(texture);

		result = FindNextFile(handle, &findData);
	}
	FindClose(handle);


	handle = FindFirstFile(L"Resources/Textures/CrazyArcade_BG/*.png", &findData);
	path = L"Resources/Textures/CrazyArcade_BG/";

	result = true;
	while (result)
	{
		Texture* texture = Texture::Add(path + findData.cFileName);
		sampleBackground.push_back(texture);

		result = FindNextFile(handle, &findData);
	}
	FindClose(handle);
}

void MapEditScene::Save(string file)
{
	BinaryWriter* writer = new BinaryWriter(file);
	writer->UInt(tag);
	writer->UInt(tiles.size());

	writer->WString(backGround->GetMaterial()->GetBaseMap()->GetFile());

	for (EditTile* tile : tiles)
	{
		writer->WString(tile->GetImage()->GetMaterial()->GetBaseMap()->GetFile());
		writer->Int((int)tile->GetEditTileType());
		writer->Int(tile->GetTileTag());
	}

	delete writer;
}

//세이브 파일에 있는 타일 정보들 로딩해주는 함수
void MapEditScene::Load(string file)
{
	BinaryReader* reader = new BinaryReader(file);
	if (reader->IsFailed())
	{
		delete reader;
		return;
	}
	this->tag = reader->UInt();
	UINT tileCount = reader->UInt();
	wstring filePath = reader->WString();

	CreateBackGround();
	backGround->GetMaterial()->SetBaseMap(filePath);
	CreateEditTiles();

	for (EditTile* tile : tiles)
	{
		filePath = reader->WString();
		int type = reader->Int();
		int tileTag = reader->Int();

		tile->GetImage()->GetMaterial()->SetBaseMap(filePath); 
		tile->SetEditTileType((EditTileType)type);
		tile->SetTileTag(tileTag);
	}
}

//맵 파일 저장하는 함수
void MapEditScene::SaveDialog()
{
	string key = "Save";

	if (ImGui::Button(key.c_str()))
	{
		DIALOG->OpenDialog(key, key, ".map");
	}

	if (DIALOG->Display(key))
	{
		if (DIALOG->IsOk())
		{
			char temp[256] = {};
			GetCurrentDirectoryA(256, temp);
			string path = temp;
			string file = DIALOG->GetFilePathName();
			file = file.substr(path.size() + 1);
			Save(file);
		}

		DIALOG->Close();
	}
}

//맵 파일 로드하는 함수
void MapEditScene::LoadDialog()
{
	string key = "Load";

	if (ImGui::Button(key.c_str()))
	{
		DIALOG->OpenDialog(key, key, ".map");
	}

	if (DIALOG->Display(key))
	{
		if (DIALOG->IsOk())
		{
			char temp[256] = {};
			GetCurrentDirectoryA(256, temp);
			string path = temp;
			string file = DIALOG->GetFilePathName();
			file = file.substr(path.size() + 1);
			Load(file);
		}

		DIALOG->Close();
	}
}

void MapEditScene::ResetTiles()
{
	for (Texture* texture : sampleTextures)
	{
		if (texture->GetFile() == L"Resources/Textures/CrazyArcade_BG_Texture/NoneBlock.png")
		{
			selectTexture = texture;
			break;
		}
	}

	for (EditTile* tile : tiles)
	{
		tile->GetImage()->GetMaterial()->SetBaseMap(selectTexture);
	}
}
