#include <Shader.hpp>

Shader::Shader(string _filePath, int _shaderType) : filePath(_filePath), shaderType(_shaderType) {}

Shader::~Shader() {};

string Shader::getFilePath() { return filePath; }

int Shader::getShaderType() { return shaderType; }
