#include <assert.h>

#include "glUtils.h"
#include "IndexBuffer.h"
#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"
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
		texture.Bind(1);

		Shader basicShader("Resources/Shaders/BasicTriangle.shader");
		basicShader.Bind();
		basicShader.SetUniform1i("u_Texture", 1);
		Renderer renderer;

		vb.Unbind();
		ib.Unbind();
		basicShader.Unbind();
		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{			
			renderer.Clear(GL_COLOR_BUFFER_BIT);
			basicShader.Bind();
			basicShader.SetUniform4f("u_Color", GetNCV(RandomInRange(1, 255)), 1.0f, 1.0f, 1.0f);
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