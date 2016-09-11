#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <array>
#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
#include <iterator>
#include <fstream>
#include <GLES2/gl2.h>
#include <EGL/egl.h>

#include "glm/glm.hpp"
#include "Game.h"
#include "glue.h"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>
#include "GLES2Lesson.h"

GLES2Lesson* gles2Lesson = nullptr;

extern void draw() {
	if ( gles2Lesson != nullptr ) {
		gles2Lesson->tick();
		gles2Lesson->render();
	}
}


/* new window size or exposure */
extern void reshape(int width, int height) {
}


static void
create_shaders(void) {
}

std::string readShaderFrom( std::string path ) {
    std::ifstream file( path );
    std::string toReturn((std::istreambuf_iterator<char>(file)),
                         std::istreambuf_iterator<char>());

    return toReturn;
}
extern void init() {

	std::string gFragmentShader = readShaderFrom( "res/fragment.glsl" );
    std::string gVertexShader = readShaderFrom( "res/vertex.glsl" );

	gles2Lesson = new GLES2Lesson();
	gles2Lesson->init(300, 300, gVertexShader.c_str(), gFragmentShader.c_str());
}
