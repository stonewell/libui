#include "uipriv_windows.hpp"
#include "area.hpp"
#include <GL/gl.h>

void uiAreaOpenGLInit(uiArea * a) {
	PIXELFORMATDESCRIPTOR pfd = {
    	sizeof(PIXELFORMATDESCRIPTOR),   // size of this pfd
    	1,		     // version number
    	PFD_DRAW_TO_WINDOW |   // support window
    		PFD_SUPPORT_OPENGL |   // support OpenGL
    		PFD_DOUBLEBUFFER,      // double buffered
    	PFD_TYPE_RGBA,	 // RGBA type
    	24,		    // 24-bit color depth
    	0, 0, 0, 0, 0, 0,      // color bits ignored
    	0,		     // no alpha buffer
    	0,		     // shift bit ignored
    	0,		     // no accumulation buffer
    	0, 0, 0, 0,	    // accum bits ignored
    	32,		    // 32-bit z-buffer
    	0,		     // no stencil buffer
    	0,		     // no auxiliary buffer
    	PFD_MAIN_PLANE,	// main layer
    	0,		     // reserved
    	0, 0, 0		// layer masks ignored
	};

	int  iPixelFormat;

	a->hDC = GetDC(a->hwnd);

	// get the best available match of pixel format for the device context
	iPixelFormat = ChoosePixelFormat(a->hDC, &pfd);

	// make that the pixel format of the device context
	SetPixelFormat(a->hDC, iPixelFormat, &pfd);

    a->hglrc = wglCreateContext(a->hDC);
    wglMakeCurrent(a->hDC, a->hglrc);
}

void uiAreaOpenGLBeginDraw(uiArea * a, uiAreaDrawParams * dp) {
	RECT rect;
	GetClientRect(a->hwnd,&rect);
	glViewport(0, 0, rect.right, rect.bottom);

    if (a->scrolling) {
        dp->AreaWidth = a->scrollWidth;
        dp->AreaHeight = a->scrollHeight;
    } else {
        dp->AreaWidth = rect.right - rect.left;
        dp->AreaHeight = rect.bottom - rect.top;
    }
}

HRESULT uiAreaOpenGLEndDraw(uiArea * a) {
	SwapBuffers(a->hDC);
	return S_OK;
}

void uiAreaOpenGLUninit(uiArea * a) {
    if (a->hglrc) {
        wglMakeCurrent(NULL, NULL);
        ReleaseDC(a->hwnd, a->hDC);
        wglDeleteContext(a->hglrc);
        a->hDC = NULL;
        a->hglrc = NULL;
    }
}
