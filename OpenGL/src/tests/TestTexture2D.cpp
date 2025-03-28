#include "TestTexture2D.h"

#include "Renderer.h"
#include "imgui/imgui.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace test {
	TestTexture2D::TestTexture2D()
        : m_proj(glm::ortho(0.f, 640.f, 0.f, 480.f, -1.f, 1.f)), m_view(glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, 0.f))),
        m_translationA(200.f, 200.f, 0.f), m_translationB(400.f, 400.f, 0.f)
	{
        float positions[16] = {
            -50.f, -50.f, 0.f, 0.f,
             50.f, -50.f, 1.f, 0.f,
             50.f,  50.f, 1.f, 1.f,
            -50.f,  50.f, 0.f, 1.f
        };

        unsigned int indices[6] = {
            0, 1, 2, 2, 3, 0
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        m_VAO = std::make_unique<VAO>();
        m_VBO = std::make_unique<VBO>(positions, 16 * sizeof(float));
        VBOLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);

        m_VAO->AddBuffer(*m_VBO, layout);
        m_IBO = std::make_unique<IBO>(indices, 6);

        m_shader = std::make_unique<Shader>("res/shaders/Basic.shader");
        m_shader->Bind();

        m_texture = std::make_unique<Texture>("res/textures/rock.png");
        m_shader->SetUniform1i("u_texture", 0);
        m_shader->SetUniformMat4f("u_projection", m_proj);
        m_shader->SetUniformMat4f("u_view", m_view);
	}
	
	TestTexture2D::~TestTexture2D() { }
	
	void TestTexture2D::OnUpdate(float deltaTime) { }

	void TestTexture2D::OnRender()
	{
		GLCall(glClearColor(0.f, 0.f, 0.f, 1.f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

        Renderer m_MainRenderer;

        m_texture->Bind(0);

        glm::mat4 modelA = glm::translate(glm::mat4(1.f), m_translationA);
        glm::mat4 modelB = glm::translate(glm::mat4(1.f), m_translationB);

        m_shader->Bind();
        m_shader->SetUniformMat4f("u_model", modelA);
        m_MainRenderer.Draw(*m_VAO, *m_IBO, *m_shader);
        m_shader->SetUniformMat4f("u_model", modelB);
        m_MainRenderer.Draw(*m_VAO, *m_IBO, *m_shader);
	}

	void TestTexture2D::OnImGuiRender()
	{
        ImGui::SliderFloat3("Translation A", &m_translationA.x, 0.f, 640.f);
        ImGui::SliderFloat3("Translation B", &m_translationB.x, 0.f, 640.f);
	}
}
