#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Shader.hpp>

using namespace std;

#define CTS(constant) #constant

static const GLfloat g_vertex_buffer_data[] = {
	-1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
};

const map<int, string> shaderTypeToString = {
	{GL_VERTEX_SHADER, CTS(GL_VERTEX_SHADER)}, 
	{GL_FRAGMENT_SHADER, CTS(GL_FRAGMENT_SHADER)}
};

string shaderTypeString(int shaderType) {
	auto shaderTypeVal = shaderTypeToString.find(shaderType);
	if(shaderTypeVal != shaderTypeToString.end()) {
		return shaderTypeVal->second;
	} else {
		return "Unknown Shader";
	}
}

ostream& operator<< (ostream& stream, Shader &s)
{
	return stream << "Shader(filePath: " << s.getFilePath() << ", shaderType: " << shaderTypeString(s.getShaderType()) << ")";
}

GLuint LoadShaders(vector<Shader> shaders) {
	vector<GLuint> shaderIds = vector<GLuint>();
	GLint Result = GL_FALSE;
	int InfoLogLength;

	for(auto shader : shaders) {
		GLuint ShaderID = glCreateShader(shader.getShaderType());
		shaderIds.push_back(ShaderID);

		string ShaderCode;
		ifstream ShaderCodeStream(shader.getFilePath().c_str(), ios::in);
		if(ShaderCodeStream.is_open())
		{
			stringstream sstr;
			sstr << ShaderCodeStream.rdbuf();
			ShaderCode = sstr.str();
			ShaderCodeStream.close();
		}

		else
		{
			cout << "Impossible to open " << shader.getFilePath() << "." << endl;
			return 0;
		}


		cout << "Compiling shader : " << shader << endl;
		const char *ShaderPointer = ShaderCode.c_str();
		glShaderSource(ShaderID, 1, &ShaderPointer, NULL);
		glCompileShader(ShaderID);

		glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &Result);
		glGetShaderiv(ShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if(InfoLogLength > 0)
		{
			vector<char> ErrorMessage(InfoLogLength+1);
			glGetShaderInfoLog(ShaderID, InfoLogLength, NULL, &ErrorMessage[0]);
			cout << shader << " had error: " << &ErrorMessage[0] << endl;
		}
	}

	cout << "Linking program..." << endl;
	GLuint ProgramID = glCreateProgram();

	for (auto shaderId: shaderIds) {
		glAttachShader(ProgramID, shaderId);
		glLinkProgram(ProgramID);

		glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
		glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if(InfoLogLength > 0)
		{
			vector<char> ProgramErrorMessage(InfoLogLength+1);
			glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
			cout << &ProgramErrorMessage[0] << endl;
		}
	}

	for(auto shaderId: shaderIds) {
		glDetachShader(ProgramID, shaderId);
		glDeleteShader(shaderId);
	}

	return ProgramID;
}

int main(int argc, char **argv)
{
	if(!glfwInit())
	{
		cout << "Failed to initialize GLFW" << endl;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window;
	window = glfwCreateWindow(1024, 768, "Game", NULL, NULL);
	if(window == NULL)
	{
		cout << "Failed to open GLFW window." << endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	glewExperimental=true;
	if(glewInit() != GLEW_OK)
	{
		cout << "Failed to initialize GLEW" << endl;
		return -1;
	}

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	vector<Shader> shaders = vector<Shader>();
	shaders.push_back(Shader("src/VertexShader.glsl", GL_VERTEX_SHADER));
	shaders.push_back(Shader("src/FragmentShader.glsl", GL_FRAGMENT_SHADER));
	GLuint programID = LoadShaders(shaders);

	bool running = true;
	while(running)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(programID);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glVertexAttribPointer(
				0,
				3,
				GL_FLOAT,
				GL_FALSE,
				0,
				NULL
		);

		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexAttribArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
		running = glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0;
	}

	glDeleteProgram(programID);

}
