#include "Shader.h"

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

#include <GL/glew.h>

Shader::Shader(const char* vertexPath, const char* fragmentPath) :m_ProgramID(0)
{
    std::ifstream vertexFileStream;
    std::ifstream fragmentFileStream;

    vertexFileStream.open(vertexPath);
    fragmentFileStream.open(fragmentPath);

    vertexFileStream.exceptions(std::ifstream::failbit || std::ifstream::badbit);
    fragmentFileStream.exceptions(std::ifstream::failbit || std::ifstream::badbit);
   
    try
    {
        if (!vertexFileStream.is_open() || !fragmentFileStream.is_open())
        {
            throw std::exception("open file error");
        }

        std::stringstream vertexStringStream, fragmentStringStream;
        vertexStringStream << vertexFileStream.rdbuf();
        fragmentStringStream << fragmentFileStream.rdbuf();
        vertexFileStream.close();
        fragmentFileStream.close();

        std::string vertexString, fragmentString;
        vertexString = vertexStringStream.str();
        fragmentString = fragmentStringStream.str();

        const char* vertexSource, * fragmentSource;
        vertexSource = vertexString.c_str();
        fragmentSource = fragmentString.c_str();

        std::cout << vertexSource << std::endl;
        std::cout << fragmentSource << std::endl;

        unsigned int vertexShader;
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexSource, NULL);
        glCompileShader(vertexShader);
        CheckCompileErrors(vertexShader, "VERTEX");

        unsigned int fragmentShader;
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
        glCompileShader(fragmentShader);
        CheckCompileErrors(fragmentShader, "FRAGMENT");

        m_ProgramID = glCreateProgram();
        glAttachShader(m_ProgramID, vertexShader);
        glAttachShader(m_ProgramID, fragmentShader);
        glLinkProgram(m_ProgramID);
        CheckCompileErrors(m_ProgramID, "PROGRAM");

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }
    catch (const std::exception& ex)
    {
        std::cout << ex.what() << std::endl;
    }
}

void Shader::Use()
{
    glUseProgram(m_ProgramID);
}

void Shader::UnUse()
{
    glUseProgram(0);
}

void Shader::CheckCompileErrors(unsigned int ID, const std::string& type)
{
    int success;
    char infoLog[512];
    if (type != "PROGRAM")
    {
        glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(ID, 512, NULL, infoLog);
            std::cout << "shader compile error: " << infoLog << std::endl;
        }
    }
    else
    {
        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(ID, 512, NULL, infoLog);
            std::cout << "program link error: " << infoLog << std::endl;
        }
    }
}
