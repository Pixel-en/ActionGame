#include "ScoreAndTime.h"
namespace Score {
namespace ScoreAndTime {

	int Score_;
	float Timer_;
}


void Score::Reset(float _time)
{
	 Score_ = 0;
	 Time_ = _time;
}

void ScoreAndTime::AddScore(int _score)
{
	Score_ += _score; 
}
void ScoreAndTime::SubScore(int _score)
{

	Score_ -= _score;
}

int ScoreAndTime::GetScore()
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
