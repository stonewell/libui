// 18 december 2015

// TODOs
// - things look very wrong on initial draw
// - initial scrolling is not set properly
// - should background be inherited from parent control?

struct uiArea {
	uiWindowsControl c;
	HWND hwnd;
	uiAreaHandler *ah;

	BOOL scrolling;
	int scrollWidth;
	int scrollHeight;
	int hscrollpos;
	int vscrollpos;
	int hwheelCarry;
	int vwheelCarry;

	clickCounter cc;
	BOOL capturing;

	BOOL inside;
	BOOL tracking;

	ID2D1HwndRenderTarget *rt;

	BOOL drawOpenGL;
	HDC hDC;
	HGLRC hglrc;
};

// areadraw.cpp
extern BOOL areaDoDraw(uiArea *a, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT *lResult);
extern void areaDrawOnResize(uiArea *, RECT *);

// areascroll.cpp
extern BOOL areaDoScroll(uiArea *a, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT *lResult);
extern void areaScrollOnResize(uiArea *, RECT *);
extern void areaUpdateScroll(uiArea *a);

// areaevents.cpp
extern BOOL areaDoEvents(uiArea *a, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT *lResult);

// areautil.cpp
extern void loadAreaSize(uiArea *a, ID2D1RenderTarget *rt, double *width, double *height);
extern void pixelsToDIP(uiArea *a, double *x, double *y);
extern void dipToPixels(uiArea *a, double *x, double *y);

//area_opengl.cpp
extern void uiAreaOpenGLInit(uiArea * a);
extern void uiAreaOpenGLUninit(uiArea * a);
extern void uiAreaOpenGLBeginDraw(uiArea * a, uiAreaDrawParams * dp);
extern HRESULT uiAreaOpenGLEndDraw(uiArea * a);
