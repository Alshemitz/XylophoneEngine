#include <DX3D/Graphics/GraphicsDevice.h>
#include <DX3D/Graphics/GraphicsLogUtils.h>
#include <DX3D/Graphics/SwapChain.h>
#include <DX3D/Graphics/DeviceContext.h>

using namespace dx3d;

dx3d::GraphicsDevice::GraphicsDevice(const GraphicsDeviceDesc& desc) :
	Base(desc.Base)
{
	D3D_FEATURE_LEVEL featureLevel{};
	UINT createDeviceFlags{};

#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	DX3DGraphicsLogErrorThrowOnFail(D3D11CreateDevice(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		createDeviceFlags,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&m_d3dDevice,
		&featureLevel,
		&m_d3dDeviceContext
	), "D3D11CreateDevice FAILED");

	DX3DGraphicsLogErrorThrowOnFail(m_d3dDevice.As(&m_dxgiDevice),
		"Failed to get IDXGIDevice from ID3D11Device");

	DX3DGraphicsLogErrorThrowOnFail(m_dxgiDevice->GetParent(IID_PPV_ARGS(&m_dxgiAdapter)),
		"GetParent failed to get IDXGIAdapter");

	DX3DGraphicsLogErrorThrowOnFail(m_dxgiAdapter->GetParent(IID_PPV_ARGS(&m_dxgiFactory)),
		"GetParent failed to get IDXGIFactory");
}

dx3d::GraphicsDevice::~GraphicsDevice()
{
}

SwapChainPtr dx3d::GraphicsDevice::createSwapChain(const SwapChainDesc& desc) const
{
	return std::make_shared<SwapChain>(desc, getGraphicsResourceDesc());
}

DeviceContextPtr dx3d::GraphicsDevice::createDeviceContext()
{
	return std::make_shared<DeviceContext>(getGraphicsResourceDesc());
}

void dx3d::GraphicsDevice::executeCommandList(DeviceContext& context)
{
	Microsoft::WRL::ComPtr<ID3D11CommandList> list{};
	DX3DGraphicsLogErrorThrowOnFail(context.m_context->FinishCommandList(false, &list),
	"FinishCommandList Failed"
	);

	m_d3dDeviceContext->ExecuteCommandList(list.Get(), false);
}

GraphicsResourceDesc dx3d::GraphicsDevice::getGraphicsResourceDesc() const noexcept
{
	return { 
		{ m_logger }, 
		shared_from_this(), 
		*m_d3dDevice.Get(), 
		*m_dxgiFactory.Get(), 
		*m_dxgiAdapter.Get() 
	};
}