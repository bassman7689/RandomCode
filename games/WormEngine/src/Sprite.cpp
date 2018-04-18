#include <iostream>
#include <memory>
#include <math.h>
#include <stdlib.h>

#include "stb_image.h"
#include "Sprite.h"

GLushort indices[] = { 0, 1, 2, 2, 1, 3 };

Sprite::Sprite(float x, float y, std::string texturePath, std::shared_ptr<Shader> shader)
    : _shader(shader), _rotationDegrees(0)
{
    _position = glm::vec2(x, y);
    _transform = glm::mat4(1.0f);
    _scale = glm::vec3(1.0f, 1.0f, 1.0f);

    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);

    glGenTextures(1, &_texture);
    glBindTexture(GL_TEXTURE_2D, _texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int tex_width, tex_height, nrChannels;
    unsigned char * data = stbi_load(texturePath.c_str(), &tex_width, &tex_height, &nrChannels, 0);
    if(!data)
    {
        std::cout << "failed to load texture: " << texturePath << std::endl;
        exit(1);
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex_width, tex_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    _width = tex_width;
    _height = tex_height;

    // GLfloat vertices[] = {
    //     x,          y,           0.0f, 0.0f, 0.0f,
    //     x + _width, y,           0.0f, 1.0f, 0.0f,
    //     x,          y + _height, 0.0f, 0.0f, 1.0f,
    //     x + _width, y + _height, 0.0f, 1.0f, 1.0f,
    // };

    GLfloat vertices[] = {
        0.0f,   0.0f,    0.0f, 0.0f, 0.0f,
        _width, 0.0f,    0.0f, 1.0f, 0.0f,
        0.0f,   _height, 0.0f, 0.0f, 1.0f,
        _width, _height, 0.0f, 1.0f, 1.0f,
    };

    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glVertexAttribPointer(_shader->attrib("vert"), 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(_shader->attrib("vert"));

    glVertexAttribPointer(_shader->attrib("texcoord"), 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(_shader->attrib("texcoord"));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _texture);
    glUniform1i(_shader->uniform("tex"), 0);

    glm::mat4 projection = glm::ortho(0.0f, 1024.0f, 768.0f, 0.0f, -1.0f, 1.0f);
    glm::mat4 view(1.0f);
}

Sprite::~Sprite()
{
    glDeleteBuffers(1, &_ibo);
    glDeleteBuffers(1, &_vbo);
    glDeleteVertexArrays(1, &_vao);
}

void Sprite::rotate(float rotationDegrees)
{
    _rotationDegrees = rotationDegrees;
}

void Sprite::scale(float x, float y)
{
    _scale = glm::vec3(x, y, 1.0);
}

void Sprite::draw()
{
    _shader->bind();

    glm::mat4 projection = glm::ortho(0.0f, 1024.0f, 768.0f, 0.0f, -1.0f, 1.0f);
    glm::mat4 view(1.0f);
    _transform = glm::mat4(1.0f);

    _transform = glm::translate(_transform, glm::vec3(_position.x, _position.y, 0));

    if (_scale.x != 1.0f && _scale.y != 1.0f)
    {
        _transform = glm::translate(_transform, glm::vec3(_width/2, _height/2, 0));
        _transform = glm::scale(_transform, _scale);
        _transform = glm::translate(_transform, glm::vec3(-(_width/2), -(_height/2), 0));
    }

    if(_rotationDegrees) {
        _transform = glm::translate(_transform, glm::vec3(_width/2, _height/2, 0));
        _transform = glm::rotate(_transform, glm::radians(_rotationDegrees), glm::vec3(0, 0, 1));
        _transform = glm::translate(_transform, glm::vec3(-(_width/2), -(_height/2), 0));
    }


    glm::mat4 mvp = projection * view * _transform;
    glUniformMatrix4fv(_shader->uniform("MVP"), 1, GL_FALSE, glm::value_ptr(mvp));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

    _shader->unbind();
}
