Preface
-------

I've been struggling to find some tutorials to learn modern OpenGL. By modern, I mean programmable pipeline introduced in OpenGL 3.0, not the deprecated fixed pipeline prior to OpenGL 2.x.

I found the most famous OpenGL tutorials are [NeHe's](http://nehe.gamedev.net/), It's too deprecated to learn from them. Also the 'official red book' is sticking with the old API, while annoucing to support OpenGL 3.0.

Now OpenGL 4.3 has been released, why those tutorials are still in 2.x age? The only available resource I found is [Learning Modern 3D Graphics Programming](http://www.arcsynthesis.org/gltut/index.html), I have to admit it's a great book.

The OpenGL Super Bible targets to OpenGL 3.x, but I don't like the manners it teaches, all details are hidden until the end of the book. After reading through the book for many pages, I found I still can't write a simple triangle programme with public general API, so frustrated.

Anyway, I will try to write my own OpenGL tutorials, I'm a beginner, so I know how to learn as a beginner. Stop talking, show me the Hello world!


System requirements
-------------------

I use **Ubuntu 12.04** installed on a MacBookPro8-1 as my development OS, I choose **CMake** as the building tool, **freeglut** to manage window and OpenGL context.

**Git** is used along all my coding process, it's recommended to use it but not required.

If you're a beginner, you may not understand what's OpenGL context, I don't either think I can explain it clear to you at the very beginning. For now, you just need to remember that it's the window OpenGL will rendering it's content to, e.g. you should create a window to draw something. Freeglut is here to do the window initialization, and it's a defacto window manager for OpenGL in Linux.

    sudo apt-get install freeglut3-dev cmake git

After you succeed to issue the command above, we can proceed to the exciting code.


Setup a skeleton
----------------

As an OpenGL newbie, I'm also a cmake beginner. But I can generate the most simple working cmake structure for all the OpenGL tutorials I will write.

    ├── build
    ├── CMakeLists.txt
    └── main.c

You can use any approach to create above file structures, I choose to issue commands below:

    mkdir build
    touch CMakeLists.txt main.c

After that, add these contents to the only CMakeLists.txt file:

    CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
    PROJECT(NEWBIE)

    ADD_DEFINITIONS(-std=c99 -O3 -funsigned-char -freg-struct-return -Wall -W -Wshadow -Wstrict-prototypes -Wpointer-arith -Winline)

    FIND_PACKAGE(GLUT)
    FIND_PACKAGE(OpenGL)
    SET(GL_LIBS ${GLUT_LIBRARY} ${OPENGL_LIBRARY})

    SET(SRC main.c)
    ADD_EXECUTABLE(main ${SRC})
    TARGET_LINK_LIBRARIES(main ${GL_LIBS} m)

Now enter the build directory, and run command `cmake ..` to test if your environment works. A working runtime will produce a final output similliar to:

    Build files have been written to: /home/vecio/Code/HeadToOpenGL/build

If everything OK, you can walk through the tutorials by git tags.

    git checkout t1
    cd build
    cmake ..
    make && ./main

    git checkout (some tag)
    ...
    ...


Copyright
---------

* root@vec.io
* http://vec.io/posts/head-to-opengl-hello-triangle
