#include "ScoreAndTime.h"

namespace ScoreAndTime {

	int Score_;
	float Timer_;
}


void ScoreAndTime::Reset(float _time)
{
	 Score_ = 0;
	 Timer_ = _time;
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

void ScoreAndTime::SetScore(int _score)
{
	Score_ = _score;
}

void ScoreAndTime::AddTimer(float _timer)
{
	Timer_ += _timer;
}

void ScoreAndTime::SubTimer(float _timer)
{
	Timer_ -= _timer;
}

float ScoreAndTime::GetTimer()
{
	return Timer_;
}

void ScoreAndTime::SetTimer(float _timer)
{
	Timer_ = _timer;
}
