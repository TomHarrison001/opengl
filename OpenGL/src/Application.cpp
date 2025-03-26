#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"
#include "VAO.h"
#include "VBO.h"
#include "VBOLayout.h"
#include "IBO.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

int main(void)
{
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    // set openGL version to core 4.6
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // save version for imgui initialisation
    const char* glsl_version = "#version 460";

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    /* Enable vsync */
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        std::cout << "Error!" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;

    {
        float positions[16] = {
            100.f, 100.f, 0.f, 0.f,
            200.f, 100.f, 1.f, 0.f,
            200.f, 200.f, 1.f, 1.f,
            100.f, 200.f, 0.f, 1.f
        };

        unsigned int indices[6] = {
            0, 1, 2, 2, 3, 0
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        VAO va;
        VBO vb(positions, 16 * sizeof(float));

        VBOLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);

        IBO ib(indices, 6);

        glm::mat4 proj = glm::ortho(0.f, 640.f, 0.f, 480.f, -1.f, 1.f);
        glm::mat4 view = glm::translate(glm::mat4(1.f), glm::vec3(-100.f, 0.f, 0.f));

        Shader shader("res/shaders/Basic.shader");
        shader.Bind();

        Texture texture("res/textures/rock.png");
        texture.Bind(0);
        shader.SetUniform1i("u_texture", 0);
        shader.SetUniformMat4f("u_projection", proj);
        shader.SetUniformMat4f("u_view", view);

        va.Unbind();
        vb.Unbind();
        ib.Unbind();
        shader.Unbind();

        Renderer m_MainRenderer;

        // initialise imgui
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init(glsl_version);
        glm::vec3 translation(200.f, 200.f, 0.f);

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            m_MainRenderer.Clear();

            // Start the imgui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            glm::mat4 model = glm::translate(glm::mat4(1.f), translation);
            shader.Bind();
            shader.SetUniformMat4f("u_model", model);

            m_MainRenderer.Draw(va, ib, shader);

            {
                ImGui::Begin("Hello, world!");
                ImGui::SliderFloat3("Translation", &translation.x, 0.f, 640.f);
                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
                ImGui::End();
            }

            // Render the imgui frame
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}
