#ifndef GLUE_H
#define GLUE_H

extern void draw(odb::Game &game);

/* new window size or exposure */
extern void reshape();

extern void init();

#ifdef X11_GLUE
/*
 * Create an RGB, double-buffered X window.
 * Return the window and context handles.
 */
extern void make_x_window(Display *x_dpy, EGLDisplay egl_dpy,
						  const char *name,
						  int x, int y, int width, int height,
						  Window *winRet,
						  EGLContext *ctxRet,
						  EGLSurface *surfRet);


extern void event_loop(Display *dpy, Window win,
					   EGLDisplay egl_dpy, EGLSurface egl_surf, odb::Game &game);

#endif

#define  LOGI(...)  printf(__VA_ARGS__)
#define  LOGE(...)  printf(__VA_ARGS__)

#endif
