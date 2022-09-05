#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Shader.h"

#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//float vertices[] =
//{
//    //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
//         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
//         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
//        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
//        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
//};

float vertices[] =
{
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

glm::vec3 cubePositions[] =
{
  glm::vec3(0.0f,  0.0f,  0.0f),
  glm::vec3(2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3(2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3(1.3f, -2.0f, -2.5f),
  glm::vec3(1.5f,  2.0f, -2.5f),
  glm::vec3(1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
};

unsigned int indices[] =
{
    0, 1, 2,
    2, 3, 0
};//opengl默认为逆时针画法为正面，而本index采用顺时针画法，画的实际上是背面，如果开启背面剔除的话，则无法画出该三角面

void ProcessInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

int main()
{
    if (glfwInit() == GLFW_FALSE)
    {
        std::cout << "glfw init error." << std::endl;
        return EXIT_FAILURE;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL window", NULL, NULL);

    glfwMakeContextCurrent(window);

    glewExperimental = true;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "glew init error." << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glViewport(0, 0, 800, 600);
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), 0);
    //glEnableVertexAttribArray(7);
    //glVertexAttribPointer(7, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (const void*)(3 * sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(8);
    glVertexAttribPointer(8, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (const void*)(3 * sizeof(GL_FLOAT)));

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //设置环绕方式
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //设置远近(缩小放大过滤方式)
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);

    unsigned int textureBufferA;
    glGenTextures(1, &textureBufferA);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, textureBufferA);

    //加载图片 container.jpg该图片为三通道，没有alpha通道
    int width, height, nrChannels;
    unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, NULL);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "load image failed." << std::endl;
    }
    stbi_image_free(data);

    unsigned int textureBufferB;
    glGenTextures(1, &textureBufferB);
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, textureBufferB);

    unsigned char* data2 = stbi_load("awesomeface.png", &width, &height, &nrChannels, NULL);
    if (data2)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "load image failed." << std::endl;
    }
    stbi_image_free(data2);

    glm::mat4 trans = glm::mat4(1.0f);

    Shader shader("VertexShader.vs", "FragmentShader.fs");

    shader.Use();
    int location;
    location = glGetUniformLocation(shader.m_ProgramID, "ourTexture");
    glUniform1i(location, 2);
    location = glGetUniformLocation(shader.m_ProgramID, "ourFace");
    glUniform1i(location, 3);
    location = glGetUniformLocation(shader.m_ProgramID, "transform");
    //trans = glm::translate(trans, glm::vec3(-1, 0, 0));
    //trans = glm::rotate(trans, glm::radians(45.0f), glm::vec3(0, 0, 1));
    //trans = glm::scale(trans, glm::vec3(2.0f, 2.0f, 2.0f));
    //因为为列主序 V新=Mt*Mr*Ms*V旧
    //=============================
    //需求:箱子缩放0.5倍,然后顺时针旋转90°(以正z看过去),opengl右手坐标系,以vec3(0,0,1)方向看过去指向屏幕向外
    //我看向屏幕向里,实际看到的是背面,也说明了
    //我们实际贴的图贴在了多边形的背面,以负z看过去,则是逆时针旋转90°
    //trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0, 0, 1));
    //trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));
    //================================
    //glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(trans));

    //躺平
    //trans = glm::rotate(trans, glm::radians(-55.0f), glm::vec3(1, 0, 0));
    //glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(trans));

    glm::mat4 modelMat(glm::mat4(1.0f));
    modelMat = glm::rotate(modelMat, glm::radians(-55.0f), glm::vec3(1.0f, 1.0f, 0.0f));
    glm::mat4 viewMat(glm::mat4(1.0f));
    viewMat = glm::translate(viewMat, glm::vec3(0, 0, -3.0f));
    glm::mat4 projMat(glm::mat4(1.0f));
    projMat = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.f);

    location = glGetUniformLocation(shader.m_ProgramID, "modelMat");
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(modelMat));
    location = glGetUniformLocation(shader.m_ProgramID, "viewMat");
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(viewMat));
    location = glGetUniformLocation(shader.m_ProgramID, "projMat");
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(projMat));

    shader.UnUse();
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window))
    {
        ProcessInput(window);

        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Use();
        glBindVertexArray(VAO);
        //trans = glm::mat4(1.0f);
        //trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0));
        //trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        //glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(trans));

        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
        //glDrawArrays(GL_TRIANGLES, 0, 36);

        for (int i = 0; i < 10; i++)
        {
            glm::mat4 modelMat(glm::mat4(1.0f));
            modelMat = glm::translate(modelMat, cubePositions[i]);
            //modelMat = glm::rotate(modelMat, glm::radians(-55.0f), glm::vec3(1.0f, 1.0f, 0.0f));
            location = glGetUniformLocation(shader.m_ProgramID, "modelMat");
            glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(modelMat));

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}