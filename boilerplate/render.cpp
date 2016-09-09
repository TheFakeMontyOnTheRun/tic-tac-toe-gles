#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <array>
#include <iostream>
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

extern void init() {

	std::string gFragmentShader =
			"precision mediump float;\n"		
					"varying vec4 vColour;\n"			
					"void main() {\n"
					"   gl_FragColor = vColour;\n"
					"}\n";



	std::string gVertexShader =
			"precision mediump float;\n"
					"uniform mat4 uModel;\n"
					"uniform mat4 uProjection;\n"
					"attribute vec4 aPosition;\n"					
					"attribute vec4 aColour;\n"	
					"varying vec4 vColour;\n"	
					"void main() {\n"
					"       gl_Position =  uProjection * uModel * aPosition;\n"
					"       vColour = aColour;\n"
					"}\n";

	gles2Lesson = new GLES2Lesson();
	gles2Lesson->init(300, 300, gVertexShader.c_str(), gFragmentShader.c_str());
}
