#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<map>
#include<vector>
#include<algorithm>
#include"Engine/GameObject.h"

class CsvReader;
class ClearLogo;
class TitleText;

class RankingsSystem : public GameObject
{
public:
	RankingsSystem(GameObject* parent);

	~RankingsSystem();

	void Initialize();

	void Update();

	void Draw();

	void Release();

	/// <summary>
	/// �����L���O�̂ɕK�v�ȃf�[�^��csv�ɑ}��
	/// </summary>
	void SetRankings(std::string _name, float _score);

	/// <summary>
	/// csv�ɕۑ����ꂽ�f�[�^���\�[�g
	/// </summary>
	void SortScore();

	

private:

	/// <summary>
	/// ���O���͗pUI�\��(�L�[�}�E�p)
	/// </summary>
	void DrawWriteUI();

	/// <summary>
	/// ���O���͗pUI�\��(�p�b�h�p)
	/// </summary>
	void DrawWriteUICn();

	std::string output_csv_file_path_ScoreData;
	std::string output_csv_file_path_SortData;
	CsvReader* csv;
	int width;
	int height;
	std::map <std::string, float> Rankings;
	std::vector<std::pair<float, std::string>> r;

	ClearLogo* cLogo;
	TitleText* tText;

	bool SetEnd;

	float eraseTime;
	float eraseTimer;
	float flame;
	float eraseAlpha;

	int x1, y1, x2, y2;

	int space;
	int word;
	int n;
	int a;
	int count;
	int MaxWord;

	int cx1, cy1, cx2, cy2;
	bool prevKey;

	int InputHandle;
	char Name[256];
	char cName[256];
	std::string str;

	

	enum DEVICE
	{
		KEY_AND_MOUSE = 0,
		PAD
	};

	int nowDevice;
};

