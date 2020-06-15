#include "VertexArray.h"

#include "glUtils.h"

VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_RendererId));

}
VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1,&m_RendererId));
}
void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	std::vector<VertexBufferLayoutElement> elements = layout.GetElements();
	unsigned int Offset = 0;
	for (unsigned int i = 0; i < elements.size(); ++i)
	{
		auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i,element.count, element.type, element.nomralized, layout.GetStride(), reinterpret_cast<const void*>(Offset)));
		Offset += element.count * VertexBufferLayoutElement::GetSizeOfType(element.type);
		
	}
	
	
}
void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_RendererId));
}
void VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}