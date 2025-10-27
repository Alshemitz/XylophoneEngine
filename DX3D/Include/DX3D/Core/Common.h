#pragma once
#include <DX3D/Core/Core.h>
#include <DX3D/Core/Logger.h>
#include <DX3D/Math/Rect.h>

namespace dx3d
{
	struct BaseDesc
	{
		Logger& Logger;
	};

	struct WindowDesc
	{
		BaseDesc Base;
		Rect Size{};
	};

	struct DisplayDesc
	{
		WindowDesc Window;
		GraphicsDevice& graphicsDevice;
	};
	
	struct GraphicsEngineDesc
	{
		BaseDesc Base;
	};

	struct GraphicsDeviceDesc
	{
		BaseDesc Base;
	};

	struct SwapChainDesc
	{
		void* winHandle{};
		Rect winSize{};
	};

	struct GameDesc
	{
		Rect windowSize{ 1280, 720 };
		Logger::LogLevel LogLevel = Logger::LogLevel::Error;
	};
}