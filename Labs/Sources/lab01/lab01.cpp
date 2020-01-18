#include <GL/glew.h>

#include <SDL.h>
#include <SDL_opengl.h>

static const int WINDOW_WIDTH  = 500;
static const int WINDOW_HEIGHT = 500;

int main(int argc, char **argv)
{
    // SDL Setup

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window =
        SDL_CreateWindow(
            "Lab 01",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            WINDOW_WIDTH, WINDOW_HEIGHT,
            SDL_WINDOW_OPENGL
        );
    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    glewExperimental = GL_TRUE; glewInit();
    SDL_GL_SetSwapInterval(1);

    // OpenGL Shader Compilation

    const char *vertex_shader_source =
        "#version 110\n"                 \
        "\n"                             \
        "attribute vec4 position;\n"     \
        "attribute vec4 color;\n"        \
        "\n"                             \
        "varying vec4 fragment_color;\n" \
        "\n"                             \
        "void main()\n"                  \
        "{\n"                            \
        "    fragment_color = color;\n"  \
        "\n"                             \
        "    gl_Position = position;\n"  \
        "}";
    const char *fragment_shader_source =
        "#version 110\n"                       \
        "\n"                                   \
        "varying vec4 fragment_color;\n"       \
        "\n"                                   \
        "void main()\n"                        \
        "{\n"                                  \
        "    gl_FragColor = fragment_color;\n" \
        "}";

    GLuint vertex_shader_object = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(
        vertex_shader_object,
        1, (const GLchar**) &vertex_shader_source, NULL
    );
    glCompileShader(vertex_shader_object);

    GLuint fragment_shader_object = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(
        fragment_shader_object,
        1, (const GLchar**) &fragment_shader_source, NULL
    );
    glCompileShader(fragment_shader_object);

    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader_object);
    glAttachShader(shader_program, fragment_shader_object);
    glLinkProgram(shader_program);
    glDetachShader(shader_program, vertex_shader_object);
    glDetachShader(shader_program, fragment_shader_object);
    glDeleteShader(vertex_shader_object);
    glDeleteShader(fragment_shader_object);

    GLint position_attribute_location =
        glGetAttribLocation(shader_program, "position");
    GLint color_attribute_location =
        glGetAttribLocation(shader_program, "color");

    // OpengGL Geometry Data Transfer

    GLfloat vertex_data[] = {
    //   Position           Color (RGBA)
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
         0.0f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
         0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    };

    GLuint vertex_array_object  = 0;
    GLuint vertex_buffer_object = 0;
    glGenVertexArrays(1, &vertex_array_object);
    glBindVertexArray(vertex_array_object);
    glGenBuffers(1, &vertex_buffer_object);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(vertex_data), vertex_data,
        GL_STATIC_DRAW
    );

    GLsizei stride = sizeof(GLfloat) * 7;
    glEnableVertexAttribArray(position_attribute_location);
    glVertexAttribPointer(
        position_attribute_location,
        3, GL_FLOAT, GL_FALSE, stride, (const GLvoid *) 0
    );
    glEnableVertexAttribArray(color_attribute_location);
    glVertexAttribPointer(
        color_attribute_location,
        4, GL_FLOAT, GL_FALSE, stride, (const GLvoid *) (sizeof(GLfloat) * 3)
    );
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // OpenGL General Setup

    glClearColor(0, 0, 0, 0);
    glViewport(0, 0, (GLsizei) WINDOW_WIDTH, (GLsizei) WINDOW_HEIGHT);

    for (;;) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) { goto end; }
        }

        // OpenGL Rendering

        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shader_program);
        glBindVertexArray(vertex_array_object);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 3);

        SDL_GL_SwapWindow(window);
    }

end:
    // SDL cleanup

    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

