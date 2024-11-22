#include "ScoreAndTimeAndMap.h"
#include "Engine/CsvReader.h"
#include <vector>

namespace ScoreAndTimeAndMap {

	int Score_;
	float Timer_;
	std::vector<std::string> maplist;
	int number_;
}


void ScoreAndTimeAndMap::Reset(float _score)
{
	 Score_ = 0;
	 Timer_ = _score;
}

void ScoreAndTimeAndMap::MapReset()
{
	CsvReader* csv = new CsvReader("Assets\\Map\\MapList.csv");
	for (int i = 0; i < csv->GetLines(); i++) {
		for (int j = 0; j < csv->GetColumns(0); j++) {
			maplist.push_back(csv->GetString(i, j));
		}
	}
	number_ = -1;
}

void ScoreAndTimeAndMap::AddScore(int _score)
{
	Score_ += _score;
}
void ScoreAndTimeAndMap::SubScore(int _score)
{

	Score_ -= _score;
}

int ScoreAndTimeAndMap::GetScore()
{
	return Score_;
}

void ScoreAndTimeAndMap::AddTimer(float _timer)
{
	Timer_ += _timer;
}

void ScoreAndTimeAndMap::SubTimer(float _timer)
{
	Timer_ -= _timer;
}

float ScoreAndTimeAndMap::GetTimer()
{
	return Timer_;
}

void ScoreAndTimeAndMap::SetTimer(float _timer)
{
	Timer_ = _timer;
}

std::string ScoreAndTimeAndMap::NextMap()
{
	number_++;
	return maplist[number_];
}

bool ScoreAndTimeAndMap::IsLastMap()
{
	if (maplist.size() - 1 == number_)
		return true;
	else
		return false;
}

void ScoreAndTimeAndMap::RetryMap()
{
	number_--;
}
