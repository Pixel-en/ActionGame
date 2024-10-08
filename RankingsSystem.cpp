#include "RankingsSystem.h"
#include"Engine/CsvReader.h"
#include"CleraLogo.h"

#if 0
namespace {
	/*std::string input_csv_file_path = "Assets\\Rankings\\RankingsSystem.csv";*/
	std::string output_csv_file_path_ScoreData = "Assets\\Rankings\\RankingsSystem.csv";
	std::string output_csv_file_path_SortData = "Assets\\Rankings\\RankingsSystemClearSort.csv";
	CsvReader* csv = new CsvReader(output_csv_file_path_ScoreData);
	int width = csv->GetColumns(0);
	int height = csv->GetLines();
	std::map <std::string, float> Rankings;
	std::vector<std::pair<float,std::string>> r;
}



void RankingsSystem::SetRankings(std::string _Pname, float _Pscore)
{
	std::ofstream ofs_csv_file(output_csv_file_path_ScoreData,std::ios::app);
	ofs_csv_file << _Pname << ","<< _Pscore;
	ofs_csv_file << std::endl;
}

void RankingsSystem::SortScore()
{
	if (csv->GetLines() > 1) {
		for (int h = 1; h < height; h++) {
			Rankings.insert(std::pair<std::string, float>(csv->GetString(h, 0), csv->GetFloat(h, 1)));
		}

		for (std::map<std::string, float>::iterator it = Rankings.begin(); it != Rankings.end(); it++) {
			r.push_back({ it->second, it->first });
		}
		sort(r.rbegin(), r.rend());


		std::ofstream ofs_csv_file(output_csv_file_path_SortData);
		ofs_csv_file << "PlayerName" << "," << "PlayerScore";
		ofs_csv_file << std::endl;
		for (auto itr = r.begin(); itr != r.end(); ++itr) {
			ofs_csv_file << itr->second << "," << itr->first;
			ofs_csv_file << std::endl;
		}
	}
}
#endif

RankingsSystem::RankingsSystem(GameObject* parent)
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

	// �L�[���̓n���h�������(�L�����Z���Ȃ��S�p�����L�萔�l���͂���Ȃ�)
	InputHandle = MakeKeyInput(50, FALSE, FALSE, FALSE);

	// �쐬�����L�[���̓n���h�����A�N�e�B�u�ɂ���
	SetActiveKeyInput(InputHandle);

}

void RankingsSystem::Update()
{
        // ���͂��I�����Ă���ꍇ�͏I��
	/*if (CheckKeyInput(InputHandle) != 0) ;*/

        // ��ʂ̏�����
    ClearDrawScreen();

        // ���̓��[�h��`��
    DrawKeyInputModeString(640,480);

    //    // ���͓r���̕������`��
    //DrawKeyInputString(0,0, InputHandle);

    // ���͂��ꂽ��������擾
    GetKeyInputString(Name, InputHandle);
}

void RankingsSystem::Draw()
{
    // ���͂��ꂽ���������ʂɕ\������
   /* DrawString(0, 0, "���Ȃ������͂����������", GetColor(255, 255, 255));*/
    DrawString(300,300, Name, GetColor(255, 255, 255));
	SetFontSize(30);
}

void RankingsSystem::Release()
{
}
