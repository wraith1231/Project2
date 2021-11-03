#pragma once
#include "stdafx.h"

namespace D3DUtil
{
	UINT CalcConstantCBufferByteSize(UINT byteSize)
	{
		return (byteSize + 255) & ~255;
	}
}