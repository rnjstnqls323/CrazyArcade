#include "Framework.h"

DataManager::DataManager()
{
}

DataManager::~DataManager()
{
}

void DataManager::LoadData(const string& fileName)
{
	filePath = "Resources/Tables/"+fileName;
	
	ifstream file(filePath);
	if (!file.is_open())
	{
		MessageBox(nullptr, L"Failed to open file", L"Error", MB_OK);
		return;
	}

	string line;

	bool isFirstLine = true;

	while (getline(file, line))
	{
		if (isFirstLine)
		{
			isFirstLine = false;
			continue;
		}

		vector<string> data = Utility::SplitString(line, ",");

		CharacterData characterData;
		characterData.key = stoi(data[0]);
		characterData.name = (CharacterName)stoi(data[1]);
		characterData.speed = stof(data[2]);
		characterData.bubbleCount = stoi(data[3]);
		characterData.waterJetCount = stoi(data[4]);

		characterDatas[characterData.key] = characterData;
	}
	file.close();
}
