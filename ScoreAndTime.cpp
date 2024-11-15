#include "ScoreAndTime.h"
namespace Score {

	int Score_;
	float Time_;
}


void Score::Reset(float _time)
{
	 Score_ = 0;
	 Time_ = _time;
}

void Score::AddScore(int _score)
{
	Score_ += _score; 
}
void Score::SubScore(int _score)
{

	Score_ -= _score;
}

int Score::GetScore()
{
	return Score_;
}

void Score::AddTime(float _time)
{
	Time_ += _time;
}

void Score::SubTime(float _time)
{
	Time_ -= _time;
}

float Score::GetTime()
{
	return Time_;
}

void Score::SetTime(int _time)
{
	Time_ = _time;
}
