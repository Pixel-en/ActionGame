#include "RankingsSystem.h"
#include"Engine/CsvReader.h"
#include<string>
#include<fstream>
#include<sstream>
#include<map>

#define INFTY 1000000001

namespace {
	/*std::string input_csv_file_path = "Assets\\Rankings\\RankingsSystem.csv";*/
	std::string output_csv_file_path = "Assets\\Rankings\\RankingsSystem.csv";
	CsvReader* csv = new CsvReader(output_csv_file_path);
	int width = csv->GetColumns(0);
	int height = csv->GetLines();
	std::map <std::string, float> Rankings;
}



void RankingsSystem::SetRankings(std::string _Pname, float _Pscore)
{
	std::ofstream ofs_csv_file(output_csv_file_path,std::ios::app);
	ofs_csv_file << _Pname << ","<< _Pscore;
	ofs_csv_file << std::endl;
}

void RankingsSystem::SortScore()
{
	if (csv->GetLines() > 1) {
		for (int h = 1; h < height; h++) {
			Rankings.insert(std::pair<std::string, float>(csv->GetString(h, 0), csv->GetFloat(h, 1)));
		}
	}

	
}

void RankingsSystem::DrawRankings()
{
	
}

//void RankingsSystem::SetRankings()
//{
//	/*std::ofstream ifs_csv_file(input_csv_file_path);*/
//	std::ofstream ofs_csv_file(output_csv_file_path,std::ios::app);
//    /*std::ifstream file(input_csv_file_path);
//
//    int lineCount = 0;
//    std::string line;
//
//    while (std::getline(file, line)) {
//		
//        lineCount++;
//    }
//
//    file.close();*/
//
//	ofs_csv_file << "tanaka" << ",," << 700;
//	ofs_csv_file << std::endl;
//}
