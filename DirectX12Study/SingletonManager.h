#pragma once

class Singletons;

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
	
	static SingletonManager* Singleton();

private:
	map<string, Singletons*> _Singletons;
};

static SingletonManager* h_instance = 0;

template <typename T>
T* Singleton()//string str)
{
	string str = typeid(T).name();
	size_t count = str.find(' ');
	str = str.substr(count + 1, str.length() - count);
	return (T*)SingletonManager::Singleton()->GetSingleton(str);
}