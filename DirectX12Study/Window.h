#pragma once

//typedef HINSTNACE_* HINSTANCE;

struct WindowDesc
{
	HINSTANCE hInstance;
	HWND ghMainWnd;
	int Width = 1080;
	int Height = 720;
};

class Window
{
public:
	Window();
	~Window();

	bool Init(int show);//HINSTANCE instanceHandle, int show);
	int Update();
	void Delete();

	//LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	//HWND GetGHMainWnd() { return ghMainWnd; }
	//HINSTANCE GetHInstance() { return hInstance; }

	WindowDesc GetDesc() { return _desc; }
	void SetDesc(WindowDesc desc);


private:
	WindowDesc _desc;
	//HWND ghMainWnd;
	//HINSTANCE hInstance;
};

