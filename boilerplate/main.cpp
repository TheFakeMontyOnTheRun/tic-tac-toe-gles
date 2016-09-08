#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>

#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include "glue.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>


extern "C" {
  EM_BOOL keydown_callback(int eventType, const EmscriptenKeyboardEvent *e, void *userData) {
	std::cout << "keydown: " << e->keyCode << std::endl;
	return true;
  }
  EM_BOOL keypress_callback(int eventType, const EmscriptenKeyboardEvent *e, void *userData) {
	std::cout << "keypress: " << e->keyCode << std::endl;
    	return true;
  }
  EM_BOOL keyup_callback(int eventType, const EmscriptenKeyboardEvent *e, void *userData) {
	std::cout << "keyUp: " << e->keyCode << std::endl;
	return true;
  }
}
#endif


	const int winWidth = 300, winHeight = 300;

	Display *x_dpy;
	Window win;
	EGLSurface egl_surf;
	EGLContext egl_ctx;
	EGLDisplay egl_dpy;
	EGLint egl_major, egl_minor;
	const char *s;

void gameLoopTick();

int main(int argc, char *argv[]) {


	x_dpy = XOpenDisplay(nullptr);

	if (!x_dpy) {
		printf("Error: couldn't open display");
		return -1;
	}

	egl_dpy = eglGetDisplay((EGLNativeDisplayType)x_dpy);

	if (!egl_dpy) {
		printf("Error: eglGetDisplay() failed\n");
		return -1;
	}

	if (!eglInitialize(egl_dpy, &egl_major, &egl_minor)) {
		printf("Error: eglInitialize() failed\n");
		return -1;
	}

	s = eglQueryString(egl_dpy, EGL_VERSION);
	printf("EGL_VERSION = %s\n", s);

	s = eglQueryString(egl_dpy, EGL_VENDOR);
	printf("EGL_VENDOR = %s\n", s);

	s = eglQueryString(egl_dpy, EGL_EXTENSIONS);
	printf("EGL_EXTENSIONS = %s\n", s);

	s = eglQueryString(egl_dpy, EGL_CLIENT_APIS);
	printf("EGL_CLIENT_APIS = %s\n", s);

	make_x_window(x_dpy, egl_dpy,
	              "OpenGL ES 2.x tri", 0, 0, winWidth, winHeight,
	              &win, &egl_ctx, &egl_surf);

	XMapWindow(x_dpy, win);

	if (!eglMakeCurrent(egl_dpy, egl_surf, egl_surf, egl_ctx)) {
		printf("Error: eglMakeCurrent() failed\n");
		return -1;
	}

	printf("GL_RENDERER   = %s\n", (char *) glGetString(GL_RENDERER));
	printf("GL_VERSION    = %s\n", (char *) glGetString(GL_VERSION));
	printf("GL_VENDOR     = %s\n", (char *) glGetString(GL_VENDOR));
	printf("GL_EXTENSIONS = %s\n", (char *) glGetString(GL_EXTENSIONS));


	init();

	/* Set initial projection/viewing transformation.
	 * We can't be sure we'll get a ConfigureNotify event when the window
	 * first appears.
	 */
	reshape(winWidth, winHeight);

#ifdef __EMSCRIPTEN__


	if ( emscripten_set_keydown_callback("#document", nullptr, true, keydown_callback) == EMSCRIPTEN_RESULT_SUCCESS ) {
		std::cout << "down ok" << std::endl; 
	}else{	
		std::cout << "down not ok" << std::endl;
	}

	if ( emscripten_set_keypress_callback("#document", nullptr, true, keypress_callback) == EMSCRIPTEN_RESULT_SUCCESS ) {
		std::cout << "press ok" << std::endl; 
	}else{	
		std::cout << "press not ok" << std::endl;
	}

	if ( emscripten_set_keyup_callback("#document", nullptr, true, keyup_callback) == EMSCRIPTEN_RESULT_SUCCESS ){
		std::cout << "up ok" << std::endl; 
	}else{	
		std::cout << "up not ok" << std::endl;
	}
      emscripten_set_main_loop( gameLoopTick, 30, 1 );
#else
	event_loop(x_dpy, win, egl_dpy, egl_surf);
#endif


	eglDestroyContext(egl_dpy, egl_ctx);
	eglDestroySurface(egl_dpy, egl_surf);
	eglTerminate(egl_dpy);


	//XDestroyWindow(x_dpy, win);
	//XCloseDisplay(x_dpy);

	return 0;
}


void gameLoopTick() {
	event_loop(x_dpy, win, egl_dpy, egl_surf);
}
