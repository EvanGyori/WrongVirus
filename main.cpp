#define GLEW_BUILD GLEW_STATIC
#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <Windows.h>

const GLfloat vertexData[] = {
	0.0f, 0.1f, 0.0f,
	-0.1f, -0.1f, 0.0f,
	0.1f, -0.1f, 0.0f
};

const GLfloat colorData[] = {
	1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f
};

const char* vertShader = 
"#version 330 core\n"
"layout(location = 0) in vec3 vertexPos_modelspace;"
"layout(location = 1) in vec3 vertexColor;"
"uniform mat4 mvp;"
"out vec3 fragmentColor;"
"void main() {"
"gl_Position = mvp * vec4(vertexPos_modelspace, 1);"
"fragmentColor = vertexColor;"
"}";

const char* fragShader =
"#version 330 core\n"
"in vec3 fragmentColor;"
"layout(location = 0) out vec4 color;"
"void main() {"
"color = vec4(fragmentColor, 1);"
"}";

// Has no error checking
int main()
{
	FreeConsole();

	glfwInit();

	//glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
	glfwWindowHint(GLFW_SAMPLES, 4);
	//glfwWindowHint(GLFW_MOUSE_, GLFW_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
	glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "wrong v1rus", nullptr, nullptr);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	glfwMakeContextCurrent(window);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glewExperimental = true;
	glewInit();

	GLuint vertShaderId = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	
	glShaderSource(vertShaderId, 1, &vertShader, NULL);
	glShaderSource(fragShaderId, 1, &fragShader, NULL);
	glCompileShader(vertShaderId);
	glCompileShader(fragShaderId);

	GLuint programId = glCreateProgram();
	glAttachShader(programId, vertShaderId);
	glAttachShader(programId, fragShaderId);
	glLinkProgram(programId);

	// error check program
	int infoLogLength;
	glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0) {
		std::vector<char> errorMsg(infoLogLength + 1);
		glGetProgramInfoLog(programId, infoLogLength, NULL, &errorMsg[0]);
		std::cout << errorMsg.data() << std::endl;
	}

	glDetachShader(programId, vertShaderId);
	glDetachShader(programId, fragShaderId);
	glDeleteShader(vertShaderId);
	glDeleteShader(fragShaderId);

	glUseProgram(programId);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	GLuint vbo;
	glGenBuffers(1, &vbo);
	GLuint cbo;
	glGenBuffers(1, &cbo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glEnableVertexArrayAttrib(vao, 0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	glBindBuffer(GL_ARRAY_BUFFER, cbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colorData), colorData, GL_STATIC_DRAW);
	glEnableVertexArrayAttrib(vao, 1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	GLuint mvpUniform = glGetUniformLocation(programId, "mvp");
	float rotation = 0.0f;
	float lastTimeStamp = 0.0f;

	int x = mode->width/2;
	int y = mode->height/2;

	// !glfwWindowShouldClose(window)
	while (!(glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS &&
			glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS &&
			glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS &&
			glfwGetKey(window, GLFW_KEY_V) == GLFW_RELEASE &&
			glfwGetKey(window, GLFW_KEY_N) == GLFW_RELEASE))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSetWindowPos(window, 0, 0);
		glfwSetWindowSize(window, mode->width, mode->height);
		glfwFocusWindow(window);
		glfwMaximizeWindow(window);
		x += rand() % 3 - 1;
		y += rand() % 3 - 1;
		glfwSetCursorPos(window, x, y);

		float currentTime = glfwGetTime();
		float deltaTime = float(currentTime - lastTimeStamp);
		lastTimeStamp = currentTime;

		rotation += deltaTime/5.0f;
		if (rotation > 2.0f) rotation = 0.0f;

		glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 100.0f);
		glm::mat4 view = glm::lookAt(
			glm::vec3(0, 0, 1),
			glm::vec3(0, 0, 0),
			glm::vec3(rotation-1.0f, 1, 0)
		);
		glm::mat4 model(1.0f);
		glm::mat4 mvp = projection * view * model;
		glUniformMatrix4fv(mvpUniform, 1, GL_FALSE, &mvp[0][0]);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);

	return 0;
}
