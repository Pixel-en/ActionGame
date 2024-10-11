#include "RankingsSystem.h"
#include"Engine/CsvReader.h"
#include"CleraLogo.h"
#include"TitleText.h"

RankingsSystem::RankingsSystem(GameObject* parent)
	: GameObject(parent, "RankingsSystem"), width(0), height(0), csv(nullptr), cLogo(nullptr), tText(nullptr), InputHandle(0),SetEnd(false),Name()
{
	
}

RankingsSystem::~RankingsSystem()
{
}

void RankingsSystem::Initialize()
{
	output_csv_file_path_ScoreData = "Assets\\Rankings\\RankingsSystem.csv";
	output_csv_file_path_SortData = "Assets\\Rankings\\RankingsSystemClearSort.csv";
	csv = new CsvReader(output_csv_file_path_ScoreData);
	width = csv->GetColumns(0);
	height = csv->GetLines();

	SetEnd = false;

	cLogo = Instantiate<ClearLogo>(this);
	tText = Instantiate<TitleText>(this);

	// �L�[���̓n���h�������(�L�����Z���Ȃ��S�p�����L�萔�l���͂���Ȃ�)
	InputHandle = MakeKeyInput(10,FALSE,TRUE,FALSE);

	eraseTime = 1.2f;
	eraseTimer = 0.0f;
	flame = 1.0f / 60.0f;
	eraseAlpha = 0;

	x1,y1,x2,y2 = 455, 440, 478, 445;
}

void RankingsSystem::Update()
{
	if (cLogo->GetOutput()) {
		// ���͂��I�����Ă���ꍇ�͏I��
		if (CheckKeyInput(InputHandle) != 0) {
			if (!SetEnd) {
				SetRankings(Name, 500);

				SetEnd = true;
				SortScore();
			}
		}
		// �쐬�����L�[���̓n���h�����A�N�e�B�u�ɂ���
		SetActiveKeyInput(InputHandle);

		//���̓��[�h��`��
		DrawKeyInputModeString(640, 480);

		// ���͓r���̕������`��
		DrawKeyInputString(0, 0, InputHandle);

		// ���͂��ꂽ��������擾
		GetKeyInputString(Name, InputHandle);

	}
}

void RankingsSystem::Draw()
{
	/*if (cLogo->GetOutput()) {*/
		if (eraseTimer > eraseTime) {
			eraseTimer = 0.0f;
			eraseAlpha = 0;
		}
		eraseTimer += flame;
		eraseAlpha = 255 - 255 * eraseTimer / eraseTime;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, eraseAlpha);
		DrawBoxAA(435, 390, 440, 440, GetColor(255, 255, 255), TRUE);//���̓o�[
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

		//for (int i = 0; i < 10; i++) {
		//	int space = 8;
		//	int word = 23;
		//	int n = y2 + space;
		//	if(i > 0)
		//	  DrawBoxAA(n, y1, x2 + word, y2, GetColor(255, 255, 255), TRUE); //�����_
		//	else
		//	  DrawBoxAA(x1, y1, x2, y2 , GetColor(255, 255, 255), TRUE); //�����_
		//}

		DrawBoxAA(519, 440, 542, 445, GetColor(255, 255, 255), TRUE); //�����_
		DrawBoxAA(486, 440, 511, 445, GetColor(255, 255, 255), TRUE); //�����_
		DrawBoxAA(x1,y1,x2,y2, GetColor(255, 255, 255), TRUE); //�����_
		DrawBoxAA(430, 380, 840, 450, GetColor(255, 255, 255), FALSE); //���͘g��
		tText->DrawString(Name, 450, 400);
		/* DrawString(450,400, Name, GetColor(255, 255, 255));*/
		SetFontSize(50);
	/*}*/
}

void RankingsSystem::Release()
{
}

void RankingsSystem::SetRankings(std::string _Pname, float _Pscore)
{
	std::ofstream ofs_csv_file(output_csv_file_path_ScoreData, std::ios::app);
	ofs_csv_file << _Pname << "," << _Pscore;
	ofs_csv_file << std::endl;
	ofs_csv_file.close();
}

void RankingsSystem::SortScore()
{
	csv = new CsvReader(output_csv_file_path_ScoreData);
	height = csv->GetLines();
	if (height > 1) {
		for (int h = 1; h < height; h++) {
			Rankings.insert(std::pair<std::string, float>(csv->GetString(h, 0), csv->GetFloat(h, 1)));
		}

		for (std::map<std::string, float>::iterator it = Rankings.begin(); it != Rankings.end(); it++) {
			r.push_back({ it->second, it->first });
		}

		sort(r.rbegin(), r.rend());
	}

	std::ofstream ofs_csv_file(output_csv_file_path_SortData);
	ofs_csv_file << "PlayerName" << "," << "PlayerScore";
	ofs_csv_file << std::endl;
	for (auto itr = r.begin(); itr != r.end(); ++itr) {
		ofs_csv_file << itr->second << "," << itr->first;
		ofs_csv_file << std::endl;
		ofs_csv_file.close();
	}
}