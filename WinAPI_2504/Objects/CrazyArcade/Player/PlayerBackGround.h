#pragma once

enum class PlayerBackGroundType
{
	Basic, Clover, Cute, Dragon, Gold, Green, Hopi
};
class PlayerBackGround : public GameObject
{
public:
	PlayerBackGround(Vector2 pos);
	~PlayerBackGround();

	void Render() override;
	static PlayerBackGroundType GetBackGroundType() { return curType; }
	static void SetBackGroundType(PlayerBackGroundType type) { curType = type; }
private:
	void MakeMesh() override {}
	void CreateQuad();
	wstring ChangeTypeToWstring(PlayerBackGroundType name);

private:
	static PlayerBackGroundType curType;
	unordered_map<PlayerBackGroundType,Quad*> quads;

};