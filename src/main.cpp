#include <iostream>
#include <stdio.h>
#include <GLFW/glfw3.h>


int main(int argc, char *argv[])
{
	GLFWwindow* window;
	// std::cout << "Hello world!" << std::endl;

	if(!glfwInit()){
		printf("couldnnot init ");
		return 1;
	}

	window = glfwCreateWindow(640,480,"hello world",NULL, NULL);
	if (!window)
	{
		printf("couldn't open window\n");
		return 1;
	}

	glfwMakeContextCurrent(window);

	unsigned char* data = new unsigned char[100 * 100 * 3];
	for (int y = 0; y < 100; y++)
	{
		for (int x = 0; x < 100; x++)
		{
			data[y * 100 *3 + x *3] = 0xff;
			data[y * 100 *3 + x *3 +1] = 0x00;
			data[y * 100 *3 + x *3 +2] = 0x00;
		}
		
	}
	

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDrawPixels(100, 100, GL_RGB, GL_UNSIGNED_BYTE, data);
		glfwSwapBuffers(window);

		glfwWaitEvents();
	}
	
	

	system("pause");
	return 0;
}