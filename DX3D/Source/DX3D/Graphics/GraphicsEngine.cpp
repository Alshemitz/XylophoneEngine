#include <DX3D/Graphics/GraphicsEngine.h>
#include <DX3D/Graphics/GraphicsDevice.h>
#include <DX3D/Graphics/DeviceContext.h>
#include <DX3D/Graphics/SwapChain.h>

using namespace dx3d;

dx3d::GraphicsEngine::GraphicsEngine(const GraphicsEngineDesc& desc):
	Base(desc.Base)
{
	m_graphicsDevice = std::make_shared<GraphicsDevice>(GraphicsDeviceDesc{m_logger});

	auto& device = *m_graphicsDevice;
	m_deviceContext = device.createDeviceContext();
}

dx3d::GraphicsEngine::~GraphicsEngine()
{
}

dx3d::GraphicsDevice& dx3d::GraphicsEngine::getGraphicsDevice() noexcept
{
	return *m_graphicsDevice;
}

void dx3d::GraphicsEngine::render(SwapChain& swapChain)
{
	auto& context = *m_deviceContext;
	Vec4 clearColor{0.667f, 0.0f, 1.0f, 1.0f};
	context.clearAndSetBackBuffer(swapChain, clearColor);

	auto& device = *m_graphicsDevice;
	device.executeCommandList(context);
	swapChain.present();
}
