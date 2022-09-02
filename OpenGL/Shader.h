#pragma once

#include <iostream>

class Shader
{
public:
    Shader(const char* vertexPath, const char* fragmentPath);
    int m_ProgramID;

    void Use();
    void UnUse();

private:
    void CheckCompileErrors(unsigned int ID, const std::string& type);
};

