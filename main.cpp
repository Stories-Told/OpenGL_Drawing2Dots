#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

#define numVAOs 2

GLuint renderingProgram;
GLuint renderingProgram2;
GLuint vao[numVAOs];

// Create the shader program (vertex and fragment)
// Use this shader for following the book
GLuint createShaderProgram()
{
	// Vertex shader for position
	const char *vshaderSource =
		"#version 430   \n"
		"void main(void) \n"
		"{ gl_Position = vec4(0.0, 0.0, 0.0, 1.0); }";

	// Fragment shader to color
	const char *fshaderSource =
		"#version 430   \n"
		"out vec4 color; \n"
		"void main(void) \n"
		"{ color = vec4(0.0, 0.0, 1.0, 1.0); }";

	// Create the vertex and fragment shaders
	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Load and Complie the vertex and fragment shader
	glShaderSource(vShader, 1, &vshaderSource, NULL);
	glShaderSource(fShader, 1, &fshaderSource, NULL);
	glCompileShader(vShader);
	glCompileShader(fShader);

	// Create a program and then attach and link the vertex and fragment shader
	GLuint vfProgram = glCreateProgram();
	glAttachShader(vfProgram, vShader);
	glAttachShader(vfProgram, fShader);
	glLinkProgram(vfProgram);

	return vfProgram;
}

// Use this shader for practice
GLuint createShaderProgram2()
{
	// Vertex shader
	const char *vshaderSource =
		"#version 430  \n"
		"void main(void) \n"
		"{ gl_Position = vec4(0.5, 0.0, 0.0, 1.0); }";

	// Fragment shader
	const char *fshaderSource =
		"#version 430  \n"
		"out vec4 color; \n"
		"void main(void) \n"
		"{ color = vec4(1.0, 1.0, 0.0, 1.0); }";

	// Create the vertex and fragment shaders
	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Load and compile the shaders
	glShaderSource(vShader, 1, &vshaderSource, NULL);
	glShaderSource(fShader, 1, &fshaderSource, NULL);
	glCompileShader(vShader);
	glCompileShader(fShader);

	// Create a program and link the shaders
	GLuint vfProgram = glCreateProgram();
	glAttachShader(vfProgram, vShader);
	glAttachShader(vfProgram, fShader);
	glLinkProgram(vfProgram);

	return vfProgram;
}


void init(GLFWwindow* window) 
{
	// First square
	renderingProgram = createShaderProgram();
	// Generate and bind the first vertex shader
	glGenVertexArrays(numVAOs, vao);
	glBindVertexArray(vao[0]);

	// Second square
	renderingProgram2 = createShaderProgram2();
	// Generate and bind the second vertex shader
	glGenVertexArrays(numVAOs, vao);
	glBindVertexArray(vao[1]);
}

// Displays the window
void display(GLFWwindow* window, double currentTime)
{
	// First square
	glUseProgram(renderingProgram); // Just loads the shaders onto the hardware
	glPointSize(30.0f);
	glDrawArrays(GL_POINTS, 0, 1);

	// Second square
	glUseProgram(renderingProgram2);
	glPointSize(30.0f);
	glDrawArrays(GL_POINTS, 0, 1);
}

int main(void)
{
	// Check to make sure glfw initilized
	if (!glfwInit()) { exit(EXIT_FAILURE); }
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Create the window
	GLFWwindow* window = glfwCreateWindow(800, 800, "CGP_00", NULL, NULL);
	glfwMakeContextCurrent(window);
	// Check to make sure glew initilized
	if (glewInit() != GLEW_OK) { exit(EXIT_FAILURE); }
	glfwSwapInterval(1); // Enables v-sync

	// Initilize the window
	init(window);

	// While loop to keep the window open
	while (!glfwWindowShouldClose(window))
	{
		display(window, glfwGetTime());
		glfwSwapBuffers(window); // Paints the screen
		glfwPollEvents(); // Handles key events like key presses
	}

	// Close the window
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
