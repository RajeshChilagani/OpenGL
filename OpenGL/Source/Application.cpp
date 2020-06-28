#include <assert.h>

#include "glUtils.h"
#include "IndexBuffer.h"
#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"
#include "Utils.h"
#include "VertexBuffer.h"
#include "VertexArray.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main(void)
{
	srand((unsigned int)time(0));
	GLFWwindow* window;
	/* Initialize the library */
	if (!glfwInit())
		return -1;
	window = glfwCreateWindow(1920, 1080, "OPEN GL", NULL, NULL);  //Create Window
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);                                 //Make the window's context current
	glfwSwapInterval(1);
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Error" << std::endl;
	}
	std::cout << glGetString(GL_VERSION) << std::endl;
	{
		float vertexPositions[] =
		{  -0.5f, -0.5f, 0.0f, 0.0f,
			0.5f, -0.5f, 1.0f, 0.0f,
			0.5f,  0.5f, 1.0f, 1.0f,
		   -0.5f,  0.5f, 0.0f, 1.0f
		};
		unsigned int indices[] =
		{
			0,1,2,
			2,3,0
		};
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA));

		VertexBuffer vb(vertexPositions, 4 * 4 * sizeof(float));

		VertexArray va;
		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
		va.AddBuffer(vb, layout);

		IndexBuffer ib(indices,6);
		
		Texture texture("Resources/Textures/VegetaSSG.png");
		
		Texture texture2("Resources/Textures/GokuSSb.png");
		
		glm::mat4 proj = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-0.1f,0.0f,0.0f));
		
		
		Shader basicShader("Resources/Shaders/BasicTriangle.shader");
		basicShader.Bind();
		basicShader.SetUniform1i("u_Texture", 1);
		
		Renderer renderer;

		ImGui::CreateContext();
		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 330");

		vb.Unbind();
		ib.Unbind();
		basicShader.Unbind();
		
		glm::vec3 GokuT(0.5f, 0.0f, 0.0f);
		glm::vec3 GokuS(1.0f, 1.0f, 1.0f);
		glm::vec3 VegetaT(0.5f, 0.0f, 0.0f);
		glm::vec3 VegetaS(1.0f, 1.0f, 1.0f);
		ImVec4 clear_color = ImVec4(GetNCV(237), GetNCV(237), GetNCV(237), 1.00f);
		ImVec4 filter_color = ImVec4(GetNCV(237), GetNCV(237), GetNCV(237), 1.00f);
		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{			
			renderer.Clear(GL_COLOR_BUFFER_BIT);

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			

			basicShader.Bind();
			basicShader.SetUniform4f("u_Color", filter_color.x, filter_color.y, filter_color.z, filter_color.z);
			{
				texture.Bind();
				basicShader.SetUniform1i("u_Texture", 0);
				glm::mat4 model = glm::translate(glm::mat4(1.0f), VegetaT) * glm::scale(glm::mat4(1.0f), VegetaS);
				glm::mat4 mvp = proj * view * model;
				basicShader.SetUniformMat4f("u_MVP", mvp);
				renderer.Draw(va, ib, basicShader);
			}
			{
				texture2.Bind();
				basicShader.SetUniform1i("u_Texture", 0);
				glm::mat4 model = glm::translate(glm::mat4(1.0f), GokuT) * glm::scale(glm::mat4(1.0f),GokuS);
				glm::mat4 mvp = proj * view * model;
				basicShader.SetUniformMat4f("u_MVP", mvp);
				renderer.Draw(va, ib, basicShader);
			}
			
			/*ImGUi Window*/
			{
				ImGui::Begin("Vegeta");                               // Create a window called "Hello, world!" and append into it.

				ImGui::SliderFloat3("Translate", &VegetaT.x, -1.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
				ImGui::SliderFloat3("Scale", &VegetaS.x, -1.0f, 1.0f);
				ImGui::ColorEdit3("Background Color", (float*)&clear_color); // Edit 3 floats representing a color
				ImGui::ColorEdit3("Filter Color", (float*)&filter_color);
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

				ImGui::End();
			}
			/**/
			{
				ImGui::Begin("Goku");

				ImGui::SliderFloat3("Translate", &GokuT.x, -1.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
				ImGui::SliderFloat3("Sacle", &GokuS.x, -1.0f, 1.0f);
				ImGui::ColorEdit3("Background Color", (float*)&clear_color); // Edit 3 floats representing a color
				ImGui::ColorEdit3("Filter Color", (float*)&filter_color);

				ImGui::End();
			}

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			GLCall(glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w));
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