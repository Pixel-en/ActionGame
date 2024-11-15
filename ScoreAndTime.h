#pragma once

namespace ScoreAndTime {
	
	void Reset(float _time);
	void AddScore(int _score);
	void SubScore(int _score);
	int GetScore();

	void AddTimer(float _timer);
	void SubTimer(float _timer);
	float GetTimer();
	void SetTimer(float _timer);
}
