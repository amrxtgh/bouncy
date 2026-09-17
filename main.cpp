#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <print>

int main() {
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW\n";
		return 1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Bouncy", nullptr, nullptr);
	if (!window) {
		std::cerr << "Failed to create window\n";
		glfwTerminate();
		return 1;
	}

	glfwMakeContextCurrent(window);
	if (!gladLoadGL(glfwGetProcAddress)) {
		std::print(stderr, "Opengl is not loaded\n");
		glfwDestroyWindow(window);
		glfwTerminate();
		return 1;
	}

	glViewport(0, 0, 800, 600);

	// traingle vertex data
	float vertices[] = {
		0.0f,  0.5f,   0.0f,
        -0.5f, -0.5f,   0.0f,
        0.5f, -0.5f,   0.0f
	};

	unsigned int VAO;
	unsigned int VBO;


	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Bind VAO
    glBindVertexArray(VAO);

    // Bind VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Copy vertex data from CPU -> GPU
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(vertices),
        vertices,
        GL_STATIC_DRAW
    );

    // Tell OpenGL how to interpret each vertex.
    glVertexAttribPointer(
        0,                  // attribute location
        3,                  // 3 floats
        GL_FLOAT,
        GL_FALSE,
        3 * sizeof(float),  // distance between vertices
        (void*)0
    );

    // Enable vertex attribute 0
    glEnableVertexAttribArray(0);

    const char* vertexShaderSource = R"(
        #version 330 core

        layout (location = 0) in vec3 aPos;

        void main()
        {
            gl_Position = vec4(aPos, 1.0);
        }
    )";

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(
        vertexShader,
        1,
        &vertexShaderSource,
        nullptr
    );

    glCompileShader(vertexShader);

    const char* fragmentShaderSource = R"(
        #version 330 core

        out vec4 FragColor;

        void main()
        {
            FragColor = vec4(1.0, 0.5, 0.2, 1.0);
        }
    )";

    unsigned int fragmentShader =
        glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(
        fragmentShader,
        1,
        &fragmentShaderSource,
        nullptr
    );

    glCompileShader(fragmentShader);

    unsigned int shaderProgram =
        glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);

    // Shaders are now inside the program.
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    while (!glfwWindowShouldClose(window))
    {
        // Clear framebuffer
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Tell OpenGL which shader program to use
        glUseProgram(shaderProgram);

        // Tell OpenGL which VAO contains our triangle
        glBindVertexArray(VAO);

        // Draw 3 vertices
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Show what we rendered
        glfwSwapBuffers(window);

        // Process keyboard/window events
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
