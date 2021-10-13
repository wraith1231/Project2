#pragma once
#include "Singletons.h"

struct WindowDesc
{
	HINSTANCE hInstance = 0;
	HWND ghMainWnd = 0;
	int x = 150;
	int y = 90;
	int Width = 1600;
	int Height = 900;
	int MaxFPS = 60;
	bool Paused = false;
};

class Window : public Singletons
{
public:
	Window();
	~Window();

	bool Init(int show);
	int Run();
	virtual void Init() override;
	virtual void Update() override;
	virtual void Delete() override;

	WindowDesc GetDesc() { return _desc; }
	void SetDesc(WindowDesc desc);


private:
	WindowDesc _desc;
};

