#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:

    unsigned int ID;

    // читает файлы и строит шейдер
    Shader(const char* vertexPath, const char* fragmentPath);

    // функция для активации шейдера
    void use();

    // для работы с uniform-переменными
    // данные "в одну строку"
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;

};

#endif