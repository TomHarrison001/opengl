#include "TestClearColour.h"

#include "Renderer.h"
#include "imgui/imgui.h"

namespace test {
	TestClearColour::TestClearColour()
		: m_ClearColour { 0.2f, 0.3, 0.8f, 1.f } { }
	
	TestClearColour::~TestClearColour() { }
	
	void TestClearColour::OnUpdate(float deltaTime) { }

	void TestClearColour::OnRender()
	{
		GLCall(glClearColor(m_ClearColour[0], m_ClearColour[1], m_ClearColour[2], m_ClearColour[3]));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}

	void TestClearColour::OnImGuiRender()
	{
		ImGui::ColorEdit4("Clear colour", m_ClearColour);
	}
}
