#pragma once

#include "VBO.h"
#include "VBOLayout.h"

class VAO
{
private:
	unsigned int m_RendererID;
public:
	VAO();
	~VAO();

	void AddBuffer(const VBO& vb, const VBOLayout& layout);
	void Bind() const;
	void Unbind() const;
};
