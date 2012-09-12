#define GL_GLEXT_PROTOTYPES
#include <error.h>
#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define CHECK_GL_STATUS(T,O,S) { \
  GLint status; \
  glGet##T##iv(O, S, &status); \
  if (GL_FALSE == status) { \
    GLint logLength; \
    glGet##T##iv(O, GL_INFO_LOG_LENGTH, &logLength); \
    char *infoLog = malloc(logLength * sizeof(char)); \
    glGet##T##InfoLog(O, logLength, NULL, infoLog); \
    fprintf(stderr, "%d: %d, %s\n", __LINE__, S, infoLog); \
    free(infoLog); \
  } \
}


#define VERTEX_SHADER " \
  #version 130\n \
  in vec4 position; \
  in vec4 color; \
  noperspective out vec4 vColor; \
  void main() { \
    gl_Position = position; \
    vColor = color; \
  }"

#define FRAGMENT_SHADER " \
  #version 130\n \
  uniform float loop; \
  uniform float time; \
  noperspective in vec4 vColor; \
  void main() { \
    float lerp = mod(time, loop) / loop; \
    vec4 vColor = mix(vColor, vec4(1, 1, 0, 0.2), lerp); \
    gl_FragColor = vColor; \
  }"


const GLfloat sValues[] = {
  0.0f, 0.5f,
  -0.5f, -0.5f,
  0.5f, -0.5f,
  0.7f, 0.0f,
  0.1f, 0.8f,
  0.9f, -0.9f,
  1.0f, 0.0f, 0.0f,
  0.0f, 1.0f, 0.0f,
  0.0f, 0.0f, 1.0f,
  1.0f, 0.0f, 0.0f,
  0.0f, 1.0f, 0.0f,
  0.0f, 0.0f, 1.0f,
};


static GLuint sProgram;
static GLuint sLocLoop;
static GLuint sLocTime;
static GLuint sLocPosition;
static GLuint sLocColor;
static GLuint sValuesBuffer;


GLuint CreateShader(GLenum shaderType, const char* shaderSource)
{
  GLuint shader = glCreateShader(shaderType);
  glShaderSource(shader, 1, (const GLchar **)&shaderSource, NULL);
  glCompileShader(shader);

  CHECK_GL_STATUS(Shader, shader, GL_COMPILE_STATUS);

  return shader;
}

GLuint CreateProgram(GLuint vertexShader, GLuint fragmentShader)
{
  GLuint program = glCreateProgram();
  glAttachShader(program, vertexShader);
  glAttachShader(program, fragmentShader);
  glLinkProgram(program);

  CHECK_GL_STATUS(Program, program, GL_LINK_STATUS);

  glDetachShader(program, vertexShader);
  glDetachShader(program, fragmentShader);
  return program;
}

void Init(void)
{
  GLuint vertexShader = CreateShader(GL_VERTEX_SHADER, VERTEX_SHADER);
  GLuint fragmentShader = CreateShader(GL_FRAGMENT_SHADER, FRAGMENT_SHADER);
  sProgram = CreateProgram(vertexShader, fragmentShader);
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  sLocLoop = glGetUniformLocation(sProgram, "loop");
  sLocTime = glGetUniformLocation(sProgram, "time");
  sLocPosition = glGetAttribLocation(sProgram, "position");
  sLocColor = glGetAttribLocation(sProgram, "color");

  glGenBuffers(1, &sValuesBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, sValuesBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(sValues), sValues, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GL_version(void)
{
  int OpenGLVersion[2];
  glGetIntegerv(GL_MAJOR_VERSION, &OpenGLVersion[0]);
  glGetIntegerv(GL_MINOR_VERSION, &OpenGLVersion[1]);
  printf("OpenGL version: %s, %d, %d\n", glGetString(GL_VERSION), OpenGLVersion[0], OpenGLVersion[1]);
}

void GLUT_display(void)
{
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glUseProgram(sProgram);

  glUniform1f(sLocLoop, 0.5);
  glUniform1f(sLocTime, glutGet(GLUT_ELAPSED_TIME) / 10000.0f);

  glBindBuffer(GL_ARRAY_BUFFER, sValuesBuffer);
  glEnableVertexAttribArray(sLocPosition);
  glVertexAttribPointer(sLocPosition, 2, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(sLocColor);
  glVertexAttribPointer(sLocColor, 3, GL_FLOAT, GL_FALSE, 0, (void *)48);

  glDrawArrays(GL_TRIANGLES, 0, 6);

  for (GLenum err = glGetError(); err != GL_NO_ERROR; err = glGetError()) {
    fprintf(stderr, "%d: %s\n", err, gluErrorString(err));
  }

  glDisableVertexAttribArray(sLocPosition);
  glDisableVertexAttribArray(sLocColor);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glUseProgram(0);

  glutSwapBuffers();
  glutPostRedisplay();
}

void GLUT_reshape(int w, int h)
{
  glViewport(0, 0, w, h);
}

void GLUT_keyboard(unsigned char key, int x, int y)
{
  if (key == 27) {
    printf("keyboard: %d, %d, %d\n", key, x, y);
    exit(0);
  }
}

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH | GLUT_STENCIL);
  glutInitWindowSize(800, 600);
  glutInitWindowPosition(200, 100);
  glutCreateWindow(argv[0]);

  glutDisplayFunc(GLUT_display);
  glutReshapeFunc(GLUT_reshape);
  glutKeyboardFunc(GLUT_keyboard);

  GL_version();
  Init();

  glutMainLoop();
  return 0;
}
