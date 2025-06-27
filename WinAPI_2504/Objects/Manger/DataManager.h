#pragma once

enum class CharacterName {
	Bazzi, Cappi, Dao, Hook, Marid, EndCharacter// 우니 고민하기
};
struct CharacterData
{
	int key;
	CharacterName name;
	float speed = 200.0f;
	int bubbleCount;
	int waterJetCount;
};

class DataManager : public Singleton<DataManager>
{
	friend class Singleton;

private:
	DataManager();
	~DataManager();

public:
	void LoadData(const string& fileName);
	
	CharacterData GetCharacterData(int key) { return characterDatas[key]; }
	int GetCharacterDataCount() { return characterDatas.size(); }

private:
	string filePath;
	unordered_map<int, CharacterData> characterDatas;

};