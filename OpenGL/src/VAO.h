#pragma once

#include "VBO.h"

class VBOLayout;

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
