#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

float vertices[] = 
{
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
     0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
     0.8f,  0.8f, 0.0f, 1.0f, 0.0f, 1.0f
};

unsigned int indices[] =
{
    0, 1, 2,
    2, 1, 3
};

const char* vertexShaderSource = 
"#version 330 core                                   \n"
"layout(location = 6) in vec3 aPos;                  \n"
"layout(location = 7) in vec3 vertexColor;           \n"
"out vec3 outVertexColor;                            \n"
"                                                    \n"
"void main()                                         \n"
"{                                                   \n"
"    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"    outVertexColor = vertexColor;                   \n"
"}                                                   \n"
;

const char* fragmentShaderSource =
"#version 330 core                                                             \n"
"out vec4 FragColor;                                                           \n"
"in vec3 outVertexColor;                                                       \n"
"                                                                              \n"
"void main()                                                                   \n"
"{                                                                             \n"
"    FragColor = vec4(outVertexColor.x, outVertexColor.y, outVertexColor.z, 1);\n"                  
"}                                                                             \n"
;

void ProcessInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

int main()
{
    if(glfwInit() == GLFW_FALSE)
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
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), 0);
    glEnableVertexAttribArray(7);
    glVertexAttribPointer(7, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (const void*)(3 * sizeof(GL_FLOAT)));

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glUseProgram(0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window))
    {
        ProcessInput(window);

        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VAO);
        glUseProgram(shaderProgram);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}