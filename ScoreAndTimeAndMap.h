#pragma once
#include <string>

namespace ScoreAndTimeAndMap {
	
	void Reset(float _time);
	void MapReset();
	void AddScore(int _score);
	void SubScore(int _score);
	int GetScore();
	void SetScore(int _score);

	void AddTimer(float _timer);
	void SubTimer(float _timer);
	float GetTimer();
	void SetTimer(float _timer);

	std::string NextMap();
	bool IsLastMap();
	void RetryMap();

}
