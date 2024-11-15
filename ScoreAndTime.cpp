#include "ScoreAndTime.h"
namespace ScoreAndTime {

	int Score_;
	float Time_;
}


void ScoreAndTime::Reset(float _time)
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

void ScoreAndTime::AddTime(float _time)
{
	Time_ += _time;
}

void ScoreAndTime::SubTime(float _time)
{
	Time_ -= _time;
}

float ScoreAndTime::GetTime()
{
	return Time_;
}

void ScoreAndTime::SetTime(int _time)
{
	Time_ = _time;
}
