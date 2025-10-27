#include <DX3D/Graphics/DeviceContext.h>
#include <DX3D/Graphics/SwapChain.h>

dx3d::DeviceContext::DeviceContext(const GraphicsResourceDesc& gDesc):
	GraphicsResource(gDesc)
{
	DX3DGraphicsLogErrorThrowOnFail(m_device.CreateDeferredContext(0, &m_context),
		"CreateDeferedContext failed"
	);
}

void dx3d::DeviceContext::clearAndSetBackBuffer(const SwapChain& swapChain, Vec4& color)
{
	f32 fColor [4] = { color.x, color.y, color.z, color.w };
	auto rtv = swapChain.m_backBufferRTV.Get();
	m_context->ClearRenderTargetView(
		swapChain.m_backBufferRTV.Get(), fColor);
	m_context->OMSetRenderTargets(1, &rtv, nullptr);
}

