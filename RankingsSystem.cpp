#include "RankingsSystem.h"
#include<string>
#include<fstream>
#include<sstream>

namespace {
	/*std::string input_csv_file_path = "Assets\\Rankings\\RankingsSystem.csv";*/
	std::string output_csv_file_path = "Assets\\Rankings\\RankingsSystem.csv";
}

void RankingsSystem::SetRankings(std::string _Pname, float _Pscore)
{
	std::ofstream ofs_csv_file(output_csv_file_path,std::ios::app);
	ofs_csv_file << _Pname << ",,"<< _Pscore;
	ofs_csv_file << std::endl;
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
