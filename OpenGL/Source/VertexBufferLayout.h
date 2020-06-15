#pragma once
#include <vector>

#include "glUtils.h"
#include <GL/glew.h>
struct VertexBufferLayoutElement
{
	unsigned int type;
	unsigned int count;
	unsigned char nomralized;
	static unsigned int GetSizeOfType(unsigned int i_Type)
	{
		switch (i_Type)
		{
		case GL_FLOAT:
			return 4;
		case GL_UNSIGNED_INT: 
			return 4;
		case GL_UNSIGNED_BYTE:
			return 1;
		default:
			break;
		}
		ASSERT(false);
		return 0;
	}
};
class VertexBufferLayout
{
public:
	VertexBufferLayout() :m_Stride(0){}
		~VertexBufferLayout() {}
	template<typename T>
	void Push(unsigned int count)
	{
		static_assert(false);
	}
	template<>
	void Push<float>(unsigned int count)
	{
		m_LayoutElements.push_back({GL_FLOAT,count,GL_FALSE});
		m_Stride += VertexBufferLayoutElement::GetSizeOfType(GL_FLOAT)* count;
	}
	template<>
	void Push<unsigned int>(unsigned int count)
	{
		m_LayoutElements.push_back({ GL_UNSIGNED_INT,count,GL_FALSE });
		m_Stride += VertexBufferLayoutElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
	}
	template<>
	void Push<unsigned char>(unsigned int count)
	{
		m_LayoutElements.push_back({ GL_UNSIGNED_BYTE,count,GL_TRUE});
		m_Stride += VertexBufferLayoutElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
	}
	inline const std::vector<VertexBufferLayoutElement>& GetElements() const { return m_LayoutElements; }
	inline unsigned int GetStride() const { return m_Stride; }
private:
	unsigned int m_Stride;
	std::vector<VertexBufferLayoutElement> m_LayoutElements;
};
