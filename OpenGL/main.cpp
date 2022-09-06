#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "Shader.h"
#include "stb_image.h"
#include "Camera.h"

#pragma region Model Data
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
#pragma endregion

#pragma region Camera Declare
//static Camera camera(glm::vec3(0, 0, 10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
static Camera camera(glm::vec3(0, 0, 10), glm::radians(0.0f), glm::radians(0.0f), glm::vec3(0, 1, 0));
#pragma endregion

#pragma region Input Declare
float gLastX;
float gLastY;
bool gFirstMouse = true;

static void ProcessInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        camera.UpdateCameraZPosition(1.0f);
        camera.Debug();
    }
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera.UpdateCameraZPosition(-1.0f);
        camera.Debug();
    }
    else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        camera.Reset();
        camera.Debug();
    }
}

static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    else if (key == GLFW_KEY_W && action == GLFW_PRESS)
    {
        camera.UpdateCameraZPosition(1.0f);
        camera.Debug();
    }
    else if (key == GLFW_KEY_S && action == GLFW_PRESS)
    {
        camera.UpdateCameraZPosition(-1.0f);
        camera.Debug();
    }
    else if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
    {
        camera.Reset();
        camera.Debug();
    }
}

static void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
    if (gFirstMouse)
    {
        gLastX = (float)xPos;
        gLastY = (float)yPos;
        gFirstMouse = false;
    }
    float xDelta, yDelta;
    xDelta = (float)xPos - gLastX;
    yDelta = (float)yPos - gLastY;
    gLastX = (float)xPos;
    gLastY = (float)yPos;

    camera.ProcessMouseMovement(xDelta, yDelta);
}
#pragma endregion

static unsigned int LoadImageToGPU(const char* imageFullName, unsigned int textureIndex)
{
    unsigned int ID;
    glGenTextures(1, &ID);
    glActiveTexture(textureIndex);
    glBindTexture(GL_TEXTURE_2D, ID);
    int width, height, nrChannels;
    unsigned char* data = stbi_load(imageFullName, &width, &height, &nrChannels, NULL);
    if (data)
    {
        if (nrChannels == 3)
        {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }
        else if (nrChannels == 4)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "load image failed." << std::endl;
    }
    stbi_image_free(data);

    return ID;
}

int main()
{
#pragma region glfw init
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
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, MouseCallback);
    //glfwSetKeyCallback(window, KeyCallback);
#pragma endregion

#pragma region glew init
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
#pragma endregion

#pragma region VAO VBO
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), 0);
    glEnableVertexAttribArray(8);
    glVertexAttribPointer(8, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (const void*)(3 * sizeof(GL_FLOAT)));
#pragma endregion

#pragma region 纹理环绕 纹理过滤
    //设置环绕方式
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //设置远近(缩小放大过滤方式)
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
#pragma endregion

#pragma region load image and set texture
    stbi_set_flip_vertically_on_load(true);

    unsigned int textureBufferA;
    textureBufferA = LoadImageToGPU("container.jpg", GL_TEXTURE2);

    unsigned int textureBufferB;
    textureBufferB = LoadImageToGPU("awesomeface.png", GL_TEXTURE3);

    Shader shader("VertexShader.vert", "FragmentShader.frag");
    shader.Use();
    int location;
    location = glGetUniformLocation(shader.m_ProgramID, "ourTexture");
    glUniform1i(location, 2);
    location = glGetUniformLocation(shader.m_ProgramID, "ourFace");
    glUniform1i(location, 3);
#pragma endregion

#pragma region set Proj
    glm::mat4 modelMat(glm::mat4(1.0f)), viewMat(glm::mat4(1.0f)), projMat(glm::mat4(1.0f));

    projMat = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.f);

    location = glGetUniformLocation(shader.m_ProgramID, "projMat");
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(projMat));
#pragma endregion

#pragma region cancel bind shaderProgram and VAO
    shader.UnUse();
    glBindVertexArray(0);
#pragma endregion

#pragma region while loop
    while (!glfwWindowShouldClose(window))
    {
        ProcessInput(window);

        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Use();
        glBindVertexArray(VAO);

#pragma region set ViewMat
        viewMat = camera.GetViewMatrix();
        location = glGetUniformLocation(shader.m_ProgramID, "viewMat");
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(viewMat));
#pragma endregion

#pragma region DrawCall
        for (int i = 0; i < 10; i++)
        {
            modelMat = glm::mat4(1.0f);
            modelMat = glm::translate(modelMat, cubePositions[i]);
#pragma region set ModelMat
        location = glGetUniformLocation(shader.m_ProgramID, "modelMat");
            glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(modelMat));
#pragma endregion

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
#pragma endregion

        glfwPollEvents();
        glfwSwapBuffers(window);
    }
#pragma endregion

    glfwTerminate();
    return 0;
}