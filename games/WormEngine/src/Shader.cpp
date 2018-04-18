#include "Shader.h"
#include "FileUtils.h"

Shader::Shader(const char *vertPath, const char *fragPath)
{
    std::string vertexSource = FileUtils::readFile(vertPath);
    GLuint vertexShader = createShader(GL_VERTEX_SHADER, vertexSource);

    std::string fragmentSource = FileUtils::readFile(fragPath);
    GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentSource);
    
    _programHandle = createProgram(vertexShader, fragmentShader);
}

Shader::~Shader()
{
    glDeleteProgram(_programHandle);
}

GLuint Shader::createShader(GLenum eShaderType, std::string &strShaderFile)
{
    GLuint shader = glCreateShader(eShaderType);
    const char *strFileData = strShaderFile.c_str();
    glShaderSource(shader, 1, &strFileData, NULL);

    glCompileShader(shader);

    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

        GLchar *strInfoLog = new GLchar[infoLogLength + 1];
        glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);

        const char *strShaderType = NULL;
        switch(eShaderType)
        {
            case GL_VERTEX_SHADER: strShaderType = "vertex"; break;
            case GL_GEOMETRY_SHADER: strShaderType = "geometry"; break;
            case GL_FRAGMENT_SHADER: strShaderType = "fragment"; break;
        }

        fprintf(stderr, "Compile failure in %s shader:\n%s\n", strShaderType, strInfoLog);
        delete[] strInfoLog;
    }

    return shader;
}

GLuint Shader::createProgram(GLuint vertexShader, GLuint fragmentShader)
{
	GLuint program = glCreateProgram();

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

	glLinkProgram(program);

	GLint status;
	glGetProgramiv (program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}

    glDetachShader(program, fragmentShader);
    glDetachShader(program, vertexShader);

    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);

    _isValid = status;

	return program;
}

void Shader::bind() {
    glUseProgram(_programHandle);
}

void Shader::unbind() {
    glUseProgram(0);
}

GLint Shader::attrib(const GLchar* attribName) const {
    if(!attribName)
    {
        throw std::runtime_error("attribName was NULL");
    }

    GLint attribHandle = glGetAttribLocation(_programHandle, attribName);
    if(attribHandle == -1)
    {
        throw std::runtime_error(std::string("Shader attribute not found: ") + attribName);
    }

    return attribHandle;
}

GLint Shader::uniform(const GLchar* uniformName) const {
    if(!uniformName)
    {
        throw std::runtime_error("uniformName was null");
    }

    GLint uniformHandle = glGetUniformLocation(_programHandle, uniformName);
    if(uniformHandle == -1)
    {
        throw std::runtime_error(std::string("Shader uniform not found: ") + uniformName);
    }

    return uniformHandle;
}
