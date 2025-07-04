#pragma once

enum class ShaShakType 
{
	Basic, Shine, Clover,Heart
};
enum class ShaShakStatus
{
	Idle, MoveUp, MoveDown,MoveLeft,MoveRight
};
class ShaShak : public Transform
{
public:
	ShaShak();
	~ShaShak();

	static ShaShakType GetShaShakType() { return shaShak; }
	static void SetShaShakType(ShaShakType type) { shaShak = type; }
	static wstring GetShaShakTypeToWString(ShaShakType type);

	ShaShakStatus GetCurStatus() { return curStatus; }
	void SetCurStatus(ShaShakStatus status) { curStatus = status; }

	void Update();
	void Render();

private:
	string ShaShakTypeToString(ShaShakType type);
	void CreateAnimation();
	void CreateTransform();

private:
	static ShaShakType shaShak;

	ShaShakStatus curStatus;
	unordered_map<ShaShakType, Animation*> animation;
	unordered_map<ShaShakStatus, Transform*> transform;
	MatrixBuffer* worldBuffer;
};