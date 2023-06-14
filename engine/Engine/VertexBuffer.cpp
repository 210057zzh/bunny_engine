#include "stdafx.h"
#include "VertexBuffer.h"

#include "Graphics.h"


VertexBuffer::VertexBuffer(
	const void* vertexData, uint32_t vertexCount, uint32_t vertexStride,
	const void* indexData, uint32_t indexCount, uint32_t indexStride
) : mVertStride(vertexStride), mIndexCount(indexCount)
{
	switch (indexStride)
	{
	case 2:
		mIndexBufferFormat = DXGI_FORMAT_R16_UINT;
		break;
	case 4:
		mIndexBufferFormat = DXGI_FORMAT_R32_UINT;
		break;
	default:
		DbgAssert(false, "index stride not recognized");
	}
	mVertexBuffer = Graphics::Get()->CreateGraphicsBuffer(vertexData, vertexCount * vertexStride, D3D11_BIND_VERTEX_BUFFER, D3D11_CPU_ACCESS_WRITE, D3D11_USAGE_DYNAMIC);
	mIndexBuffer = Graphics::Get()->CreateGraphicsBuffer(indexData, indexStride * indexCount, D3D11_BIND_INDEX_BUFFER, D3D11_CPU_ACCESS_WRITE, D3D11_USAGE_DYNAMIC);
}

VertexBuffer::~VertexBuffer()
{
	mVertexBuffer->Release();
	mIndexBuffer->Release();
}

void VertexBuffer::Draw() const
{
	constexpr  UINT zero = 0;
	Graphics::Get()->GetDeviceContext()->IASetVertexBuffers(0, 1, &mVertexBuffer, &mVertStride, &zero);
	Graphics::Get()->GetDeviceContext()->IASetIndexBuffer(mIndexBuffer, mIndexBufferFormat, 0);
	Graphics::Get()->GetDeviceContext()->DrawIndexed(mIndexCount, 0, 0);
}
