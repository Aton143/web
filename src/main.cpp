#include <stdint.h>
#include <stdio.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
#include <SDL.h>
#include <SDL_opengles2.h>
#else
#include "SDL2/SDL.h"
#include "SDL2/SDL_video.h"
#ifdef _WIN32
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "SDL2/SDL_opengl.h"
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "opengl32.lib")
#undef main
#endif

#ifdef __APPLE__
  #define GL_SILENCE_DEPRECATION
  #include <OpenGL/gl3.h>
  #include <OpenGL/gl3ext.h>
#endif
#endif

static float lerp(float min, float t, float max)
{
  return((min * (1 - t)) + (max * t));
}

static void main_loop(void *arg);
int main(int argc, char *argv[]);

GLfloat vertices[512] = {};
uint32_t vertex_index = 0;

#if __EMSCRIPTEN__
static EM_BOOL mouse_callback(int32_t, EmscriptenMouseEvent *, void *);

EM_BOOL
mouse_callback(int                         event_type,
               const EmscriptenMouseEvent *mouse_event,
               void                       *user_data)
{
  SDL_Log("screen: (%d,%d), client: (%d,%d),%s%s%s%s button: %hu, "
         "buttons: %hu, movement: (%d,%d), canvas: (%d,%d), timestamp: %lf\n",
         mouse_event->screenX,
         mouse_event->screenY,
         mouse_event->clientX,
         mouse_event->clientY,
         mouse_event->ctrlKey ? " CTRL" : "",
         mouse_event->shiftKey ? " SHIFT" : "",
         mouse_event->altKey ? " ALT" : "",
         mouse_event->metaKey ? " META" : "",
         mouse_event->button,
         mouse_event->buttons,
         mouse_event->movementX,
         mouse_event->movementY,
         mouse_event->canvasX,
         mouse_event->canvasY,
         mouse_event->timestamp);

  float radius = 5.0f;
  float x = mouse_event->clientX;
  float y = 512 - mouse_event->clientY;

  // 0 - x, 1 - y, 2 - z, 3 - c_x, 4 - c_y, 5 - radius
  // top left
  vertices[vertex_index + 0] = lerp(-1.0f, (x - radius) / 512.0f, 1.0f);
  vertices[vertex_index + 1] = lerp(-1.0f, (y + radius) / 512.0f, 1.0f);
  vertices[vertex_index + 2] = 0.0f;

  vertices[vertex_index + 3] = lerp(-1.0f, x / 512.0f, 1.0f);
  vertices[vertex_index + 4] = lerp(-1.0f, y / 512.0f, 1.0f);

  vertices[vertex_index + 5] = radius;

  SDL_Log("%d, (%2f, %2f)\n", vertex_index, vertices[vertex_index + 0],  vertices[vertex_index + 1]);
  vertex_index += 1;

  // bottom left
  vertices[vertex_index + 0] = lerp(-1.0f, (x - radius) / 512.0f, 1.0f);
  vertices[vertex_index + 1] = lerp(-1.0f, (y - radius) / 512.0f, 1.0f);
  vertices[vertex_index + 2] = 0.0f;

  vertices[vertex_index + 3] = lerp(-1.0f, x / 512.0f, 1.0f);
  vertices[vertex_index + 4] = lerp(-1.0f, y / 512.0f, 1.0f);

  vertices[vertex_index + 5] = radius;

  SDL_Log("%d, (%2f, %2f)\n", vertex_index, vertices[vertex_index + 0],  vertices[vertex_index + 1]);
  vertex_index += 1;

  // bottom right
  vertices[vertex_index + 0] = lerp(-1.0f, (x + radius) / 512.0f, 1.0f);
  vertices[vertex_index + 1] = lerp(-1.0f, (y - radius) / 512.0f, 1.0f);
  vertices[vertex_index + 2] = 0.0f;

  vertices[vertex_index + 3] = lerp(-1.0f, x / 512.0f, 1.0f);
  vertices[vertex_index + 4] = lerp(-1.0f, y / 512.0f, 1.0f);

  vertices[vertex_index + 5] = radius;

  SDL_Log("%d, (%2f, %2f)\n", vertex_index, vertices[vertex_index + 0],  vertices[vertex_index + 1]);
  vertex_index += 1;

  // bottom right
  vertices[vertex_index + 0] = lerp(-1.0f, (x + radius) / 512.0f, 1.0f);
  vertices[vertex_index + 1] = lerp(-1.0f, (y - radius) / 512.0f, 1.0f);
  vertices[vertex_index + 2] = 0.0f;

  vertices[vertex_index + 3] = lerp(-1.0f, x / 512.0f, 1.0f);
  vertices[vertex_index + 4] = lerp(-1.0f, y / 512.0f, 1.0f);

  vertices[vertex_index + 5] = radius;

  SDL_Log("%d, (%2f, %2f)\n", vertex_index, vertices[vertex_index + 0],  vertices[vertex_index + 1]);
  vertex_index += 1;

  // top right
  vertices[vertex_index + 0] = lerp(-1.0f, (x + radius) / 512.0f, 1.0f);
  vertices[vertex_index + 1] = lerp(-1.0f, (y + radius) / 512.0f, 1.0f);
  vertices[vertex_index + 2] = 0.0f;

  vertices[vertex_index + 3] = lerp(-1.0f, x / 512.0f, 1.0f);
  vertices[vertex_index + 4] = lerp(-1.0f, y / 512.0f, 1.0f);

  vertices[vertex_index + 5] = radius;

  SDL_Log("%d, (%2f, %2f)\n", vertex_index, vertices[vertex_index + 0],  vertices[vertex_index + 1]);
  vertex_index += 1;

  // top left
  vertices[vertex_index + 0] = lerp(-1.0f, (x - radius) / 512.0f, 1.0f);
  vertices[vertex_index + 1] = lerp(-1.0f, (y + radius) / 512.0f, 1.0f);
  vertices[vertex_index + 2] = 0.0f;

  vertices[vertex_index + 3] = lerp(-1.0f, x / 512.0f, 1.0f);
  vertices[vertex_index + 4] = lerp(-1.0f, y / 512.0f, 1.0f);

  vertices[vertex_index + 5] = radius;

  SDL_Log("%d, (%2f, %2f)\n", vertex_index, vertices[vertex_index + 0],  vertices[vertex_index + 1]);
  vertex_index += 1;

  return(0);
}
#endif

const GLchar *vertex_shader_source =
"attribute vec3 position;                             \n"
"attribute vec2  circle_center;                       \n"
"attribute float circle_radius;                       \n"
"varying vec2 center;                                 \n"
"varying float radius;                                \n"
"varying vec3 color;                                  \n"
"void main()                                          \n"
"{                                                    \n"
"  gl_Position = vec4(position.xyz, 1.0);             \n"
"  color = gl_Position.xyz + vec3(0.5);               \n"
"  radius = circle_radius;                            \n"
"  vec2 scale = (circle_center + vec2(1.0, 1.0)) / 2.0; \n"
"  center = mix(vec2(0, 0), vec2(512, 512), scale);   \n"
"}                                                    \n";

const GLchar *fragment_shader_source =
"precision mediump float;                            \n"
"varying vec2 center;                                \n"
"varying float radius;                               \n"
"varying vec3 color;                                 \n"
"float lengthv2f(vec2 u, vec2 v) \n"
"{ \n"
  "return sqrt(dot(u - v, u - v)); \n"
"} \n"
"void main()                                         \n"
"{                                                   \n"
"  vec4 final_color = vec4(0.0, 0.0, 0.0, 1.0);      \n"
// "  if (lengthv2f(gl_FragCoord.xy, center) < radius)  \n"
// "  {                                                 \n"
"    final_color = vec4(color, 1.0);                 \n"
// "  }                                                 \n"
"  gl_FragColor = final_color;                       \n"
"                                                    \n"
"}                                                   \n";

void main_loop(void *arg)
{
  SDL_Window* window = (SDL_Window*) arg;

  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

  // NOTE(antoniom): Clear screen
  glClear(GL_COLOR_BUFFER_BIT);

  // NOTE(antoniom): Draw the vertex buffer
  glDrawArrays(GL_TRIANGLES, 0, vertex_index);

  // NOTE(antoniom): Swap front/back framebuffers
  SDL_GL_SwapWindow(window);
}

int main(int argc, char *argv[])
{
#if __EMSCRIPTEN__
  EMSCRIPTEN_RESULT ret = EMSCRIPTEN_RESULT_FAILED;

  ret = emscripten_set_click_callback("#canvas", 0, 1, mouse_callback);
#if 0
  ret = emscripten_set_mousedown_callback("#canvas", 0, 1, mouse_callback);
  ret = emscripten_set_mouseup_callback("#canvas", 0, 1, mouse_callback);
  ret = emscripten_set_dblclick_callback("#canvas", 0, 1, mouse_callback);
  ret = emscripten_set_mousemove_callback("#canvas", 0, 1, mouse_callback);
  ret = emscripten_set_mouseenter_callback("#canvas", 0, 1, mouse_callback);
  ret = emscripten_set_mouseleave_callback("#canvas", 0, 1, mouse_callback);
  ret = emscripten_set_mouseover_callback("#canvas", 0, 1, mouse_callback);
  ret = emscripten_set_mouseout_callback("#canvas", 0, 1, mouse_callback);
#endif
#endif

  int32_t win_width  = 512;
  int32_t win_height = 512;

  SDL_Window *window = SDL_CreateWindow("Hello Triangle Minimal", 
                                        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                        win_width, win_height,
                                        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);

#if __EMSCRIPTEN__
  // NOTE(antoniom): Create OpenGLES 2 context on SDL window
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#else
  SDL_Init(SDL_INIT_VIDEO);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
#endif
  SDL_GL_SetSwapInterval(1);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GLContext glc = SDL_GL_CreateContext(window);
  SDL_Log("INFO: GL version: %s\n", glGetString(GL_VERSION));
  
  glewInit();

  // NOTE(antoniom): Set clear color to black
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  // NOTE(antoniom): Get actual GL window size in pixels, in case of high dpi scaling
  SDL_GL_GetDrawableSize(window, &win_width, &win_height);
  SDL_Log("INFO: GL window size = %dx%d\n", win_width, win_height);
  glViewport(0, 0, win_width, win_height);   

  // NOTE(antoniom): Create and compile vertex shader
  GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
  glCompileShader(vertex_shader);

  // NOTE(antoniom): Create and compile fragment shader
  GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
  glCompileShader(fragment_shader);

  // NOTE(antoniom): Link vertex and fragment shader into shader program and use it
  GLuint shader_program = glCreateProgram();
  glAttachShader(shader_program, vertex_shader);
  glAttachShader(shader_program, fragment_shader);
  glLinkProgram(shader_program);
  glUseProgram(shader_program);

  // NOTE(antoniom): Create vertex buffer object and copy vertex data into it
  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

#if 1
  // NOTE(antoniom): Specify the layout of the shader vertex data (positions only, 3 floats)
  GLint position_attributes = glGetAttribLocation(shader_program, "position");
  GLint center_attributes = glGetAttribLocation(shader_program, "circle_center");
  GLint radius_attributes = glGetAttribLocation(shader_program, "circle_radius");

  glEnableVertexAttribArray(position_attributes);
  glVertexAttribPointer(position_attributes,
                        3,
                        GL_FLOAT,
                        GL_FALSE,
                        6 * sizeof(float),
                        (void *) (0));

  glEnableVertexAttribArray(center_attributes);
  glVertexAttribPointer(center_attributes,
                        2,
                        GL_FLOAT,
                        GL_FALSE,
                        6 * sizeof(float),
                        (void *) (3 * sizeof(float)));

  glEnableVertexAttribArray(radius_attributes);
  glVertexAttribPointer(radius_attributes,
                        1,
                        GL_FLOAT,
                        GL_FALSE,
                        6 * sizeof(float),
                        (void *) (5 * sizeof(float)));

#ifdef __EMSCRIPTEN__
  // NOTE(antoniom): Use browser's requestAnimationFrame
  int32_t fps = 0;
  emscripten_set_main_loop_arg(main_loop, window, fps, true);
#endif
  bool quit = false;
  while (!quit)
  {
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
        quit = true;
    }
    main_loop(window);
  }
#endif

  return 0;
}
