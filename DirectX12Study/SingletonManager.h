#pragma once

class Window;

class SingletonManager
{
public:
	SingletonManager();
	~SingletonManager();

	void Init();

	static SingletonManager* Singleton();
	Window* GetWindow();

private:
	Window* _window;

};

static SingletonManager* h_instance;