#include "Framework.h"

VertexBuffer::VertexBuffer(void* data, UINT stride, UINT count)
    : stride(stride)
{
    D3D11_BUFFER_DESC bufferDesc = {};
    bufferDesc.Usage = D3D11_USAGE_DEFAULT;
    bufferDesc.ByteWidth = stride * count;
    bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA subData = {};
    subData.pSysMem = data;

   // void* testCopy = malloc(bufferDesc.ByteWidth);
   // memcpy(testCopy, subData.pSysMem, bufferDesc.ByteWidth); // 여기서 터지면 범위 문제
   // free(testCopy);
   // 생성할때, 크기는 크게 잡아서 생성했는데 worldBuffer의 크기가 훨씬 작아서 안맞아서 터졌던거다.
   // resize다시 해주니 안터진다.

    DEVICE->CreateBuffer(&bufferDesc, &subData, &buffer);
}

VertexBuffer::~VertexBuffer()
{
    buffer->Release();
}

void VertexBuffer::Set(D3D11_PRIMITIVE_TOPOLOGY type)
{
    DC->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);
    DC->IASetPrimitiveTopology(type);
}

void VertexBuffer::Set(UINT slot, D3D11_PRIMITIVE_TOPOLOGY type)
{
	DC->IASetVertexBuffers(slot, 1, &buffer, &stride, &offset);
	DC->IASetPrimitiveTopology(type);
}

void VertexBuffer::Update(void* data, UINT count)
{
    DC->UpdateSubresource(buffer, 0, nullptr, data, stride, count);
}
