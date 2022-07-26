#ifndef __WINDOW_H__
#define __WINDOW_H__
#include <X11/Xlib.h>
#include <iostream>
#include <string>

class Xwindow {
	Display *d;
	Window w;
	int s;
	GC gc;
	unsigned long colours[10];
	int width, height;

	public:
	Xwindow(int width=500, int height=500);  // Constructor; displays the window.
	~Xwindow();                              // Destructor; destroys the window.

	enum { White = 0, Black, Red, Green, Blue };
		

	void drawString(int x, int y, std::string msg, int colour = Black);
	void drawBigString(int x, int y, std::string msg, int colour = Black);
	void drawStringFont(int x, int y, std::string msg, std::string font, int colour = Black);

	// Draws a rectangle
	void fillRectangle(int x, int y, int width, int height, int colour=Black);

 private:
  void printMessage(int x, int y, const std::string& msg, int colour, XFontStruct& f);
};

#endif
