#include "stdafx.h"
#include "XMVectorTest.h"


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

void XMVectorTest::test()
{
	cout.setf(ios_base::boolalpha);

	XMVECTOR p = XMVectorSet(2.0f, 2.0f, 1.0f, 0.0f);
	XMVECTOR q = XMVectorSet(2.0f, -0.5f, 0.5f, 0.1f);
	XMVECTOR u = XMVectorSet(1.0f, 2.0f, 4.0f, 9.0f);
	XMVECTOR v = XMVectorSet(-2.0f, 1.0f, -3.0f, 2.5f);
	XMVECTOR w = XMVectorSet(0.0f, XM_PIDIV4, XM_PIDIV2, XM_PI);

	cout << "p : " << p << endl;
	cout << "q : " << q << endl;
	cout << "u : " << u << endl;
	cout << "v : " << v << endl;
	cout << "w : " << w << endl << endl;

	cout << "ABS(V) : " << XMVectorAbs(v) << endl;
	cout << "COS(W) : " << XMVectorCos(w) << endl;
	cout << "LOG(U) : " << XMVectorLog(u) << endl;
	cout << "EXP(W) : " << XMVectorExp(w) << endl << endl;

	cout << "POW(U, P) : " << XMVectorPow(u, p) << endl;
	cout << "SQRT(U) : " << XMVectorSqrt(u) << endl << endl;

	cout << "SWIZZLE(U, 2, 2, 1, 3) : " << XMVectorSwizzle(u, 1, 2, 3, 0) << endl;
	cout << "SWIZZLE(U, 2, 1, 0, 3) : " << XMVectorSwizzle(u, 2, 1, 0, 3) << endl << endl;

	cout << "MUL(U, V) : " << XMVectorMultiply(u, v) << endl;
	cout << "SAT(p) : " << XMVectorSaturate(p) << endl;
	cout << "SAT(Q) : " << XMVectorSaturate(q) << endl;
	cout << "SAT(u) : " << XMVectorSaturate(u) << endl;
	cout << "SAT(v) : " << XMVectorSaturate(v) << endl;
	cout << "SAT(w) : " << XMVectorSaturate(w) << endl;
	cout << "MIN(P, V) : " << XMVectorMin(p, v) << endl;
	cout << "MAX(P, V) : " << XMVectorMax(p, v) << endl;
}
