#ifndef SHADER_HPP
#define SHADER_HPP

#include <iostream>

using namespace std;

class Shader {
	public:
		Shader(string _filePath, int _shaderType);
		~Shader();
		string getFilePath();
		int getShaderType();
	private:
		string filePath;
		int shaderType;
};

#endif
