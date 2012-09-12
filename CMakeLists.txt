CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(NEWBIE)

ADD_DEFINITIONS(-std=c99 -O3 -funsigned-char -freg-struct-return -Wall -W -Wshadow -Wstrict-prototypes -Wpointer-arith -Winline)

FIND_PACKAGE(GLUT)
FIND_PACKAGE(OpenGL)
SET(GL_LIBS ${GLUT_LIBRARY} ${OPENGL_LIBRARY})

SET(SRC main.c)
ADD_EXECUTABLE(main ${SRC})
TARGET_LINK_LIBRARIES(main ${GL_LIBS} m)
