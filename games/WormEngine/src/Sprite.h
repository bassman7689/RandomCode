#ifndef __MODEL__
#define __MODEL__

#include <string>
#include <vector>

#include <GL/glew.h>

#include <glm/vec2.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>


#include "Shader.h"
#include "stb_image.h"

class Sprite{
public:
    Sprite(float x, float y, std::string texturePath, std::shared_ptr<Shader> shader);
    ~Sprite();

    void SetPosition(glm::vec2 position) { _position = position; }
    void rotate(float rotationDegrees);
    void scale(float x, float y);
    void draw();

private:
    float                    _width;
    float                    _height;
    float                    _rotationDegrees;
    glm::vec3                _scale;
    glm::vec2                _position;
    glm::mat4                _transform;
    std::shared_ptr<Shader>  _shader;
    GLuint                   _vao;
    GLuint                   _vbo;
    GLuint                   _ibo;
    GLuint                   _texture;
};

#endif
