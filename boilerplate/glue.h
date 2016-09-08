#ifndef GLUE_H
#define GLUE_H

static GLfloat view_rotx = 0.0, view_roty = 0.0;


extern void draw();

/* new window size or exposure */
extern void reshape(int width, int height);

extern void init();


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
           EGLDisplay egl_dpy, EGLSurface egl_surf);



#define  LOGI(...)  printf(__VA_ARGS__)
#define  LOGE(...)  printf(__VA_ARGS__)

#endif
