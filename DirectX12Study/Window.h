#pragma once

struct WindowDesc
{
	HINSTANCE hInstance;
	HWND ghMainWnd;
	int Width = 1080;
	int Height = 720;
	int MaxFPS = 60;
};

class Window
{
public:
	Window();
	~Window();

	bool Init(int show);
	int Update();
	void Delete();

	WindowDesc GetDesc() { return _desc; }
	void SetDesc(WindowDesc desc);


private:
	WindowDesc _desc;
};

