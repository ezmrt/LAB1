#define GLFW_DLL
#define GLEW_DLL
#include "glew-2.1.0/include/GL/glew.h"
#include "glfw-3.4.bin.WIN64/include/GLFW/glfw3.h"
#include <iostream>
#include <cmath>
#include <vector>

#include "Shader.h" 

int main()
{
    if (!glfwInit()) {
        fprintf(stderr, "ERROR GLFW Init\n");
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* Okno = glfwCreateWindow(512, 512, "Star with Shader Library", NULL, NULL);
    if (!Okno) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(Okno);

    if (glewInit() != GLEW_OK) {
        return -2;
    }

    Shader ourShader("vertex.glsl", "fragment.glsl");

  
    float vertices[] = {

         0.0f,  0.0f, 0.0f,  -0.2f,  0.2f, 0.0f,   0.0f,  0.7f, 0.0f,
         0.0f,  0.0f, 0.0f,   0.2f,  0.2f, 0.0f,   0.0f,  0.7f, 0.0f,

          0.0f,  0.0f, 0.0f,   0.2f,  0.2f, 0.0f,   0.7f,  0.0f, 0.0f,
          0.0f,  0.0f, 0.0f,   0.2f, -0.2f, 0.0f,   0.7f,  0.0f, 0.0f,

           0.0f,  0.0f, 0.0f,   0.2f, -0.2f, 0.0f,   0.0f, -0.7f, 0.0f,
           0.0f,  0.0f, 0.0f,  -0.2f, -0.2f, 0.0f,   0.0f, -0.7f, 0.0f,

            0.0f,  0.0f, 0.0f,  -0.2f, -0.2f, 0.0f,  -0.7f,  0.0f, 0.0f,
            0.0f,  0.0f, 0.0f,  -0.2f,  0.2f, 0.0f,  -0.7f,  0.0f, 0.0f
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    while (!glfwWindowShouldClose(Okno)) {

        glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ourShader.use();

        // смена цвета
        float timeValue = (float)glfwGetTime();
        float red = (sin(timeValue) + 1.0f) / 2.0f;
        float green = (sin(timeValue + 2.0f) + 1.0f) / 2.0f;
        float blue = (sin(timeValue + 4.0f) + 1.0f) / 2.0f;


        ourShader.setFloat("red", red);

        int vertexColorLocation = glGetUniformLocation(ourShader.ID, "ourColor");
        glUniform4f(vertexColorLocation, red, green, blue, 1.0f);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 24);

        glfwSwapBuffers(Okno);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    return 0;
}