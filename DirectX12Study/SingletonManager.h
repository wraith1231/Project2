#pragma once

class Window;
class Time;

class SingletonManager
{
public:
	SingletonManager();
	~SingletonManager();

	static SingletonManager* Singleton();
	Window* GetWindow();
	Time* GetTime();

private:
	Window* _window;
	Time* _time;
};

static SingletonManager* h_instance;