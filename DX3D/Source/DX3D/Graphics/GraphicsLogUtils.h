#pragma once
//May need in future 
/*#include <winerror.h>d*/
#include <DX3D/Core/Logger.h>

namespace dx3d
{
#define DX3DGraphicsLogErrorThrowOnFail(hr,message) \
	{ \
		auto res = (hr); \
		if (FAILED(res)) \
		{ \
			DX3DLogErrorAndThrow(message); \
		} \
	}
}