#pragma once

#include "Test.h"

#include "VBOLayout.h"
#include "Shader.h"
#include "Texture.h"

#include <memory>

namespace test {

	class TestTexture2D : public Test
	{
	public:
		TestTexture2D();
		~TestTexture2D();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		std::unique_ptr<Shader> m_shader;
		std::unique_ptr<VAO> m_VAO;
		std::unique_ptr<VBO> m_VBO;
		std::unique_ptr<IBO> m_IBO;
		std::unique_ptr<Texture> m_texture;
		glm::mat4 m_proj;
		glm::mat4 m_view;
		glm::vec3 m_translationA;
		glm::vec3 m_translationB;
	};
}
