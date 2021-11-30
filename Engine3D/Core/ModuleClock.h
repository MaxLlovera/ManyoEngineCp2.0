#pragma once
#include "Module.h"
#include "Timer.h"
#include "Globals.h"


class ModuleClock : public Module
{
public:
	ModuleClock(Application* app, bool start_enabled = true);
	~ModuleClock();

	bool Init() override;
	bool Start() override;
	update_status PreUpdate(float dt) override;
	update_status Update(float dt)override;
	bool CleanUp() override;
	void Play();
	void Pause();
	void Resume();
	void Stop();

	float GetFramesSinceGameStart();
	float GetSecondsSinceGameStart();
	float GetDeltaTimeGame();

	float* GetScale();

	float GetRealTimeSeconds();
	float GetRealTimeDeltaTime();

	bool CheckPause();

private:
	Timer timer;
	bool is_paused;

	float scale;
	float dtGame;
	float gameTimer;
	
};