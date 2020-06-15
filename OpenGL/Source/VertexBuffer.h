#pragma once
class VertexBuffer
{
public:
	VertexBuffer(const void* Data, unsigned int size);
	~VertexBuffer();
	void Bind() const;
	void Unbind() const;
private:
	unsigned int m_RendererID;
};

