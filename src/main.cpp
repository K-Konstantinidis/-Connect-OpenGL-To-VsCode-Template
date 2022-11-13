#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
int openWindow();

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// Vertex Shader source code
const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";
// Fragment Shader source code
const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
                                   "}\n\0";

int main()
{
    openWindow();

    return 0;
}

int openWindow()
{
    // glfw: initialize and configure the library
    glfwInit();

    // Tell glfw which version of opeGL we are using
    // In our case it is OpenGL 3.3 so both major/minor version are version 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Tell glfw which OpenGL profile we want to use
    // openGL profile is like a package of functions
    // GLFW_OPENGL_CORE_PROFILE: Contains all the modern functions
    // GLFW_OPENGL_COMPAT_PROFILE: Contains modern & outdated functions
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Coordinates to make a triangle:
    // lower left corner | lower right corner | upper corner
    GLfloat vertices[] = {
        -0.5f,                         // x
        -0.5f * float(sqrt(3)) / 3,    // y
        0.0f,                          // z
        0.5f,                          // x
        -0.5f * float(sqrt(3)) / 3,    // y
        0.0f,                          // z
        0.0f,                          // x
        0.5f * float(sqrt(3)) * 2 / 3, // y
        0.0f,                          // z
    };

    // If something went wrong in the initialization
    if (!glfwInit())
    {
        std::cout << "Something went wrong in the glfw initialization" << std::endl;
        return -1;
    }

    // Create a window
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Window", NULL, NULL);
    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window part of the current context
    glfwMakeContextCurrent(window);

    // Load GLAD so it configures OpenGL
    gladLoadGL();

    // Which area of the window we want OpenGL to render in
    // In our case it is: from bottom left (0,0) to top right (width/height)
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    // Create Vertex Shader Object & get reference
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Attach Vertex Shader source to the Vertex Shader Object
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    // Compile the Vertex Shader to machine code
    glCompileShader(vertexShader);

    // Create Fragment Shader Object & get reference
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // Attach Fragment Shader source to the Vertex Shader Object
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    // Compile the Fragment Shader to machine code
    glCompileShader(fragmentShader);

    // Create Shader Program Object & get reference
    GLuint shaderProgram = glCreateProgram();
    // Attach the Vertex & Fragment Shaders to the Shader Program
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    // Wrap-up/Link all the shaders together into the Shader Program
    glLinkProgram(shaderProgram);

    // Delete the now useless Vertex & Fragment Shader objects
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Create reference containers(Arrays) for the:
    // Vertex Array Object: VAO
    // Vertex Buffer Object: VBO
    GLuint VAO, VBO;

    // Generate the VAO & VBO with only 1 object each
    glGenVertexArrays(1, &VAO); // Stores pointers to 1 or more VBOs and tells OpenGL how to interpret them
    glGenBuffers(1, &VBO);

    // Make the VAO the current Vertex Array Object by binding it
    glBindVertexArray(VAO);

    // Bind the VBO specifying it's a GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Introduce the vertices into the VBO
    //  GL_STREAM_DRAW: Vertices will be modified once and used a few times
    //  GL_STATIC_DRAW: Vertices will be modified once and used many times
    //  GL_DYNAMIC_DRAW: Vertices will be modified multiple times and used many times
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Configure the Vertex Attribute so that OpenGL knows how to read the VBO
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    // Enable the Vertex Attribute so that OpenGL knows to use it
    glEnableVertexAttribArray(0);

    // Bind both the VBO & VAO to 0 so that we do not
    // accidentally modify them
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Swap the back buffer with the front one, to see the color we chose
    glfwSwapBuffers(window);

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        // If users presses the ESC key escape close window
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        // Render here
        // Change background color
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        // Clean the back buffer and assign the new color to it
        glClear(GL_COLOR_BUFFER_BIT);

        // Tell OpenGL which Shader Program we want to use
        glUseProgram(shaderProgram);
        // Bind the VAO so OpenGL know to use it
        glBindVertexArray(VAO);
        // Draw the triangle using the GL_TRIANGLES primitive
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);

        /* Process all glfw events e.g. window appearence, resize etc*/
        glfwPollEvents();
    }

    // Delete the now all the objects we have created
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    // Delete window before ending the program
    glfwDestroyWindow(window);
    // Terminate glfw clearing all previously allocated GLFW resources
    glfwTerminate();
    return 0;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays
    glViewport(0, 0, width, height);
}
