#pragma once


class XMMatrixTest
{
public:
	//static XMMatrixTest* Matrix() { return h_instance; }

	XMMatrixTest();
	~XMMatrixTest();

	static XMMatrixTest* Matrix();
	static void Init();

	void Test();

private:
};


static XMMatrixTest* h_instance;