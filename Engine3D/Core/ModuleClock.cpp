#include "ModuleClock.h"

ModuleClock::ModuleClock(Application* app, bool start_enabled):Module(app, start_enabled)
{
	is_paused = true;
	gameTimer = 0.0f;

	scale = 1.0f;
	dtGame = 0.0f;
}

ModuleClock::~ModuleClock()
{

}
bool ModuleClock::Init()
{
	bool ret = true;

	return ret;
}

bool ModuleClock::Start()
{
	timer.Stop();
	timer.Reset();
	return true;
}

update_status ModuleClock::PreUpdate(float dt)
{
	
	if (is_paused)
	{
		dtGame = dt * scale;
		gameTimer = gameTimer + dtGame;
	}

	return UPDATE_CONTINUE;
}

update_status ModuleClock::Update(float dt)
{
	return UPDATE_CONTINUE;
}

bool ModuleClock::CleanUp()
{
	bool ret = true;

	return ret;
}

void ModuleClock::Play()
{
	is_paused = false;
	timer.Start();
}

void ModuleClock::Pause()
{
	is_paused = true;
	timer.Stop();
}
void ModuleClock::Resume()
{
	is_paused = false;
	timer.Resume();
}
void ModuleClock::Stop()
{
	timer.Stop();
	timer.Reset();
	gameTimer = 0;
	dtGame = 0;
	is_paused = true;
	
}
//float ModuleClock::GetFramesSinceGameStart()
//{
//
//}
float ModuleClock::GetSecondsSinceGameStart()
{
	return gameTimer;
}
float ModuleClock::GetDeltaTimeGame()
{
	return dtGame;
}
float* ModuleClock::GetScale()
{
	return &scale;
}
float ModuleClock::GetRealTimeSeconds()
{
	return timer.ReadSec();
}
//float ModuleClock::GetRealTimeDeltaTime()
//{
//	///
//}
bool ModuleClock::CheckPause()
{
	return is_paused;
}