#ifndef __SHADER__
#define __SHADER__

#include <string>
#include <GL/glew.h>

class Shader{
public:
    Shader(const char* vertPath, const char* fragPath);
    ~Shader();

    bool valid() { return _isValid == GL_TRUE; }

    void bind();
    void unbind();

    GLint attrib(const GLchar* attribName) const;
    GLint uniform(const GLchar* uniformName) const;

private:
    GLuint createShader(GLenum eShaderType, std::string& shaderSource);
    GLuint createProgram(GLuint vertexShader, GLuint programShader);
    GLuint _programHandle;
    GLint _isValid;
};

#endif
