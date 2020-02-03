#include <GL/glew.h>

#include <SDL.h>
#include <SDL_opengl.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

static int window_width  = 500;
static int window_height = 500;

static glm::vec3 triangle_position = glm::vec3(0, 0, 1);
static glm::vec3 triangle_rotation = glm::vec3(0, 0, 0);
static glm::vec3 triangle_scale    = glm::vec3(1, 1, 1);

static const float CAMERA_SPEED = 0.01f;
static const float CAMERA_ROT_SPEED = 0.01f;
static glm::vec3 camera_position = glm::vec3(0, 0, -0.5);
static glm::vec3 camera_rotation = glm::vec3(0, M_PI, 0);
static float camera_aspect_ratio  = 1.0f;
static float camera_field_of_view = 1.13f;
static float camera_near_plane    = 0.01f;
static float camera_far_plane     = 100.0f;

static glm::mat4 triangle_model_matrix;
static glm::mat4 camera_model_matrix;
static glm::mat4 camera_view_matrix;
static glm::mat4 camera_projection_matrix;
static glm::mat4 triangle_model_view_projection_matrix;

int main(int argc, char **argv)
{
    // SDL Setup

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window =
        SDL_CreateWindow(
            "Lab 01",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            window_width, window_height,
            SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI
        );
    SDL_GL_GetDrawableSize(window, &window_width, &window_height);
    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    glewExperimental = GL_TRUE; glewInit();
    SDL_GL_SetSwapInterval(1);

    // OpenGL Shader Compilation

    const char *vertex_shader_source =
        "#version 110\n"                                               \
        "\n"                                                           \
        "attribute vec4 position;\n"                                   \
        "attribute vec4 color;\n"                                      \
        "\n"                                                           \
        "uniform mat4 model_view_projection_matrix;\n"                 \
        "\n"                                                           \
        "varying vec4 fragment_color;\n"                               \
        "\n"                                                           \
        "void main()\n"                                                \
        "{\n"                                                          \
        "    fragment_color = color;\n"                                \
        "\n"                                                           \
        "    gl_Position = model_view_projection_matrix * position;\n" \
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
    GLint status;
    glGetShaderiv(vertex_shader_object, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        GLint info_log_length;
        glGetShaderiv(vertex_shader_object, GL_INFO_LOG_LENGTH, &info_log_length);
        if (info_log_length > 0) {
            GLchar *info_log = (GLchar *) malloc((size_t) info_log_length);
            glGetShaderInfoLog(vertex_shader_object, info_log_length, NULL, info_log);
            fprintf(stderr, "Failed to compile a vertex shader\n");
            fprintf(stderr, "Compilation log:\n%s\n\n", info_log);
            free(info_log);
        }
        return -1;
    }

    GLuint fragment_shader_object = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(
        fragment_shader_object,
        1, (const GLchar**) &fragment_shader_source, NULL
    );
    glCompileShader(fragment_shader_object);
    glGetShaderiv(fragment_shader_object, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        GLint info_log_length;
        glGetShaderiv(fragment_shader_object, GL_INFO_LOG_LENGTH, &info_log_length);
        if (info_log_length > 0) {
            GLchar *info_log = (GLchar *) malloc((size_t) info_log_length);
            glGetShaderInfoLog(fragment_shader_object, info_log_length, NULL, info_log);
            fprintf(stderr, "Failed to compile a fragment shader\n");
            fprintf(stderr, "Compilation log:\n%s\n\n", info_log);
            free(info_log);
        }
        return -1;
    }

    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader_object);
    glAttachShader(shader_program, fragment_shader_object);
    glLinkProgram(shader_program);
    glGetProgramiv(shader_program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        GLint info_log_length;
        glGetProgramiv(shader_program, GL_INFO_LOG_LENGTH, &info_log_length);
        if (info_log_length > 0) {
            GLchar *info_log = (GLchar *) malloc((size_t) info_log_length);
            glGetProgramInfoLog(shader_program, info_log_length, NULL, info_log);
            fprintf(stderr, "Failed to link a GPU program\n");
            fprintf(stderr, "Linker log:\n%s\n\n", info_log);
            free(info_log);
        }

        return -1;
    }
    glDetachShader(shader_program, vertex_shader_object);
    glDetachShader(shader_program, fragment_shader_object);
    glDeleteShader(vertex_shader_object);
    glDeleteShader(fragment_shader_object);

    GLint position_attribute_location =
        glGetAttribLocation(shader_program, "position");
    GLint color_attribute_location =
        glGetAttribLocation(shader_program, "color");
    GLint mvp_matrix_uniform_location =
        glGetUniformLocation(shader_program, "model_view_projection_matrix");

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
    glViewport(0, 0, (GLsizei) window_width, (GLsizei) window_height);

    for (;;) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                goto end;
            } else {
                switch (event.key.keysym.sym) {
                    case SDLK_w:
                        camera_rotation.x -= CAMERA_ROT_SPEED;
                        break;
                    case SDLK_a:
                        camera_rotation.y += CAMERA_ROT_SPEED;
                        break;
                    case SDLK_s:
                        camera_rotation.x += CAMERA_ROT_SPEED;
                        break;
                    case SDLK_d:
                        camera_rotation.y -= CAMERA_ROT_SPEED;
                        break;
                    case SDLK_UP: {
                        glm::vec4 dir = glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);
                        dir = camera_model_matrix * dir;
                        dir *= CAMERA_SPEED;

                        camera_position.x -= dir.x;
                        camera_position.y -= dir.y;
                        camera_position.z -= dir.z;
                        break;
                    }
                    case SDLK_DOWN: {
                        glm::vec4 dir = glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);
                        dir = camera_model_matrix * dir;
                        dir *= CAMERA_SPEED;

                        camera_position.x += dir.x;
                        camera_position.y += dir.y;
                        camera_position.z += dir.z;
                        break;
                    }
                }
            }
        }

        // Transformation

        triangle_rotation.y += 0.01f;

        triangle_model_matrix = glm::translate(glm::mat4(1.0f), triangle_position);
        triangle_model_matrix = glm::rotate(triangle_model_matrix, triangle_rotation.y, glm::vec3(0, 1, 0));
        triangle_model_matrix = glm::rotate(triangle_model_matrix, triangle_rotation.x, glm::vec3(1, 0, 0));
        triangle_model_matrix = glm::rotate(triangle_model_matrix, triangle_rotation.z, glm::vec3(0, 0, 1));
        triangle_model_matrix = glm::scale(triangle_model_matrix, triangle_scale);

        camera_model_matrix = glm::translate(glm::mat4(1.0f), camera_position);
        camera_model_matrix = glm::rotate(camera_model_matrix, camera_rotation.y, glm::vec3(0, 1, 0));
        camera_model_matrix = glm::rotate(camera_model_matrix, camera_rotation.x, glm::vec3(1, 0, 0));
        camera_model_matrix = glm::rotate(camera_model_matrix, camera_rotation.z, glm::vec3(0, 0, 1));
        camera_view_matrix = glm::inverse(camera_model_matrix);

        camera_aspect_ratio = fabsf((float) window_width / (float) window_height);
        camera_projection_matrix =
            glm::perspective<float>(
                camera_field_of_view,
                camera_aspect_ratio,
                camera_near_plane,
                camera_far_plane
            );

        triangle_model_view_projection_matrix = camera_projection_matrix * camera_view_matrix * triangle_model_matrix;
        glUniformMatrix4fv(
            mvp_matrix_uniform_location,
            1, GL_FALSE,
            glm::value_ptr(triangle_model_view_projection_matrix)
        );

        glViewport(
            0, 0,
            (GLsizei) window_width,
            (GLsizei) window_height
        );

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

