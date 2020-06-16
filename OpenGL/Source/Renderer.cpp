#include "Renderer.h"

#include "glUtils.h"

void Renderer::Clear(unsigned int i_Color) const
{
	GLCall(glClear(i_Color));
}
void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
	va.Bind();
	ib.Bind();
	shader.Bind();
	GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
}