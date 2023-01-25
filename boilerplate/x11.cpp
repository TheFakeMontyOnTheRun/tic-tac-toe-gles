#include <cassert>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <memory>
#include <array>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>

#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include "glm/glm.hpp"
#include "CAnimation.h"
#include "GameRenderListener.h"
#include "Game.h"
#include "glue.h"
#include <iostream>
#include <emscripten.h>
#include <emscripten/html5.h>


/*
 * Create an RGB, double-buffered X window.
 * Return the window and context handles.
 */
extern void make_x_window(Display *x_dpy, EGLDisplay egl_dpy,
						  const char *name,
						  int x, int y, int width, int height,
						  Window *winRet,
						  EGLContext *ctxRet,
						  EGLSurface *surfRet) {
	static const EGLint attribs[] = {
			EGL_RED_SIZE, 1,
			EGL_GREEN_SIZE, 1,
			EGL_BLUE_SIZE, 1,
			EGL_DEPTH_SIZE, 1,
			EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
			EGL_NONE
	};
	static const EGLint ctx_attribs[] = {
			EGL_CONTEXT_CLIENT_VERSION, 2,
			EGL_NONE
	};


	int scrnum;
	XSetWindowAttributes attr;
	unsigned long mask;
	Window root;
	Window win;
	//   XVisualInfo *visInfo, visTemplate;
	int num_visuals;
	EGLContext ctx;
	EGLConfig config;
	EGLint num_configs;
	EGLint vid;

	scrnum = DefaultScreen(x_dpy);
	root = DefaultRootWindow(x_dpy);

	if (!eglChooseConfig(egl_dpy, attribs, &config, 1, &num_configs)) {
		printf("Error: couldn't get an EGL visual config\n");
		exit(1);
	}

	assert(config);
	assert(num_configs > 0);

	if (!eglGetConfigAttrib(egl_dpy, config, EGL_NATIVE_VISUAL_ID, &vid)) {
		printf("Error: eglGetConfigAttrib() failed\n");
		exit(1);
	}

	/* window attributes */
	attr.background_pixel = 0;
	attr.border_pixel = 0;
	// attr.colormap = XCreateColormap( x_dpy, root, visInfo->visual, AllocNone);
	attr.event_mask = StructureNotifyMask | ExposureMask | KeyPressMask;
	mask = CWBackPixel | CWBorderPixel | CWColormap | CWEventMask;

	win = XCreateWindow(x_dpy, root, 0, 0, width, height,
						0, CopyFromParent, InputOutput,
						CopyFromParent, mask, &attr);

	/* set hints and properties */
	{
		XSizeHints sizehints;
		sizehints.x = x;
		sizehints.y = y;
		sizehints.width = width;
		sizehints.height = height;
		sizehints.flags = USSize | USPosition;
	}

	eglBindAPI(EGL_OPENGL_ES_API);

	ctx = eglCreateContext(egl_dpy, config, EGL_NO_CONTEXT, ctx_attribs);
	if (!ctx) {
		printf("Error: eglCreateContext failed\n");
		exit(1);
	}


	/* test eglQueryContext() */
	{
		EGLint val;
		eglQueryContext(egl_dpy, ctx, EGL_CONTEXT_CLIENT_VERSION, &val);
		assert(val == 2);
	}


	*surfRet = eglCreateWindowSurface(egl_dpy, config, win, NULL);
	if (!*surfRet) {
		printf("Error: eglCreateWindowSurface failed\n");
		exit(1);
	}

	/* sanity checks */
	{
		EGLint val;
		eglQuerySurface(egl_dpy, *surfRet, EGL_WIDTH, &val);
		assert(val == width);
		eglQuerySurface(egl_dpy, *surfRet, EGL_HEIGHT, &val);
		assert(val == height);
		assert(eglGetConfigAttrib(egl_dpy, config, EGL_SURFACE_TYPE, &val));
		assert(val & EGL_WINDOW_BIT);
	}

	*winRet = win;
	*ctxRet = ctx;
}

extern void
event_loop(Display *dpy, Window win,
		   EGLDisplay egl_dpy, EGLSurface egl_surf, odb::Game &game) {
	draw(game);
	eglSwapBuffers(egl_dpy, egl_surf);
}

