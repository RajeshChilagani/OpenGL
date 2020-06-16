#include <assert.h>

#include "glUtils.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Renderer.h"
#include "Utils.h"
#include "VertexBuffer.h"
#include "VertexArray.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main(void)
{
	srand((unsigned int)time(0));
	GLFWwindow* window;
	/* Initialize the library */
	if (!glfwInit())
		return -1;
	window = glfwCreateWindow(1280, 720, "OPEN GL", NULL, NULL);  //Create Window
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);                                 //Make the window's context current
	glfwSwapInterval(0);
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Error" << std::endl;
	}
	{
		float vertexPositions[] =
		{ -0.5f,-0.5f,
			0.0f,-0.5f,
			0.0f, 0.5f,
			-0.5f,  0.5f

		};
		unsigned int indices[] =
		{
			0,1,2,
			2,3,0
		};
		std::cout << glGetString(GL_VERSION) << std::endl;
		VertexArray va;
		VertexBuffer vb(vertexPositions,8*sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(2);
		va.AddBuffer(vb, layout);
		IndexBuffer ib(indices,6);
		Shader basicShader("Resources/Shaders/BasicTriangle.shader");
		basicShader.Bind();
		Renderer renderer;
		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{			
			renderer.Clear(GL_COLOR_BUFFER_BIT);
						
			basicShader.SetUniform4f("u_Color", GetNCV(RandomInRange(1, 255)), GetNCV(RandomInRange(1, 255)), GetNCV(RandomInRange(1, 255)), 1.0f);
			renderer.Draw(va,ib,basicShader);

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}

	}
	
	glfwTerminate();
	return 0;
}