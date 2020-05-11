#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <assert.h>

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);  //Create Window
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);                                 //Make the window's context current
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Error" << std::endl;
	}
	std::cout << glGetString(GL_VERSION) << std::endl;
	unsigned int buffer;
	glGenBuffers(1,&buffer);
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);
		glBegin(GL_TRIANGLES);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(0.0f, 0.5f);
		glVertex2f(0.5f, -0.5f);
		glEnd();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}