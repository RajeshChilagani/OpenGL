#pragma once
#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"

class Renderer
{
public:
	void Clear(unsigned int i_Color) const;
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
private:
};

