#include "stdafx.h"
#include "XMMatrixTest.h"

//#ifndef __XMVECTOR_OUTPUT__
//
//#define __XMVECTOR_OUTPUT__
//
//ostream& XM_CALLCONV operator<<(ostream& os, FXMVECTOR v)
//{
//	//XMFLOAT3 dest;
//	//XMStoreFloat3(&dest, v);
//	XMFLOAT4 dest2;
//	XMStoreFloat4(&dest2, v);
//
//	//os << "(" << dest.x << ", " << dest.y << ", " << dest.z << "), ";
//	os << "(" << dest2.x << ", " << dest2.y << ", " << dest2.z << ", " << dest2.w << ")";
//	return os;
//}
//
//#endif // !__XMVECTOR_OUTPUT__
//
//
//#ifndef __XMMATRIX_OUTPUT__
//
//#define __XMMATRIX_OUTPUT__
//ostream& XM_CALLCONV operator<<(ostream& os, FXMMATRIX m)
//{
//	for (int i = 0; i < 4; i++)
//	{
//		os << XMVectorGetX(m.r[i]) << "	";
//		os << XMVectorGetY(m.r[i]) << "	";
//		os << XMVectorGetZ(m.r[i]) << "	";
//		os << XMVectorGetW(m.r[i]);
//		os << endl;
//	}
//
//	return os;
//}
//
//#endif // !__XMMATRIX_OUTPUT__


XMMatrixTest::XMMatrixTest()
{
	//Init();
}

XMMatrixTest::~XMMatrixTest()
{
}

XMMatrixTest* XMMatrixTest::Matrix()
{
	Init();

	return h_instance;
}

void XMMatrixTest::Init()
{
	if (h_instance == nullptr)
	{
		h_instance = new XMMatrixTest();
	}
}

void XMMatrixTest::Test()
{
	XMMATRIX A(	1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 2.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 4.0f, 0.0f,
				1.0f, 2.0f, 3.0f, 1.0f);

	XMMATRIX B = XMMatrixIdentity();

	XMMATRIX C = A * B;
	XMMATRIX D = XMMatrixTranspose(A);
	XMVECTOR det = XMMatrixDeterminant(A);
	XMMATRIX E = XMMatrixInverse(&det, A);
	XMMATRIX F = A * E;


	cout << "A = " << endl << A << endl;
	cout << "B = " << endl << B << endl;
	cout << "C = A*B = " << endl << C << endl;
	cout << "D = transpose A = " << endl << D << endl;
	//cout << "det = determinant A = " << endl << det << endl;
	cout << "E = inverse A = " << endl << E << endl;
	cout << "F = A*E = " << endl << F << endl;
}
