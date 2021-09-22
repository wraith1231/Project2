#pragma once

class Singletons;
class Window;
class Time;

class SingletonManager
{
public:
	SingletonManager();
	~SingletonManager();

	void Init();
	void Update();
	void Delete();

	void AddSingleton(string name, Singletons* sin);
	Singletons* GetSingleton(string name);
	//Singletons* operator[](string name) { return GetSingleton(name); }

	static SingletonManager* Singleton();
	Window* GetWindow() { return (Window*)GetSingleton("Window"); }
	Time* GetTime() { return (Time*)GetSingleton("Time"); }

private:
	map<string, Singletons*> _Singletons;
};

static SingletonManager* h_instance = 0;

template <typename T>
T* Singleton(string str)
{
	return (T*)SingletonManager::Singleton()->GetSingleton(str);
}