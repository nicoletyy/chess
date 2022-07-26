#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include <cmath>
#include "window.h"

using namespace std;

const double pi = std::acos(-1);

Xwindow::Xwindow(int width, int height): width{width}, height{height} {

	d = XOpenDisplay(NULL);
	if (d == NULL) {
		cerr << "Cannot open display" << endl;
		exit(1);
	}
	s = DefaultScreen(d);
	w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, width, height, 1,
			BlackPixel(d, s), WhitePixel(d, s));
	XSelectInput(d, w, ExposureMask | KeyPressMask);
	XMapRaised(d, w);

	Pixmap pix = XCreatePixmap(d,w,width,
			height,DefaultDepth(d,DefaultScreen(d)));
	gc = XCreateGC(d, pix, 0,(XGCValues *)0);

	XFlush(d);
	XFlush(d);


	// Set up colours.
	XColor xcolour;
	Colormap cmap;
    const int numColours = 5;
	char color_vals[numColours][10] = {"white", "black", "red",
		"green", "blue"};

	cmap=DefaultColormap(d,DefaultScreen(d));

	for(int i=0; i < numColours; ++i) {
		XParseColor(d,cmap,color_vals[i],&xcolour);
		XAllocColor(d,cmap,&xcolour);
		colours[i]=xcolour.pixel;
	}

	XSetForeground(d,gc,colours[Black]);

	// Make window non-resizeable.
	XSizeHints hints;
	hints.flags = (USPosition | PSize | PMinSize | PMaxSize );
	hints.height = hints.base_height = hints.min_height = hints.max_height = height;
	hints.width = hints.base_width = hints.min_width = hints.max_width = width;
	XSetNormalHints(d, w, &hints);

	XSynchronize(d, True);

	XSelectInput(d, w, ExposureMask);
	XFlush(d);
	XEvent event;
	XNextEvent(d, &event); // Hang until the window is ready.
	XSelectInput(d, w, 0);

}

Xwindow::~Xwindow() {
	XFreeGC(d, gc);
	XCloseDisplay(d);
}

void Xwindow::fillRectangle(int x, int y, int width, int height, int colour) {
	XSetForeground(d, gc, colours[colour]);
	XFillRectangle(d, w, gc, x, y, width, height);
	XSetForeground(d, gc, colours[Black]);
}


void Xwindow::drawString(int x, int y, string msg, int colour) {
  XFontStruct * f = XLoadQueryFont(d, "6x13");
	
	printMessage(x, y, msg, colour, *f); 

	delete f;
}


void Xwindow::drawStringFont(int x, int y, string msg, string font, int colour) {
  XFontStruct * f = XLoadQueryFont(d, font.c_str());
  
	if ( f == nullptr ){
		f = XLoadQueryFont(d, "6x13");
	}

	printMessage(x, y, msg, colour, *f);
	delete f;
}

void Xwindow::drawBigString(int x, int y, string msg, int colour) {
  // Font f = XLoadFont(d, "-*-helvetica-bold-r-normal--*-240-*-*-*-*-*");
  ostringstream name;
  name << "-*-helvetica-bold-r-*-*-*-240-" << width/5 << "-" << height/5 << "-*-*-*-*";

	drawStringFont(x, y, msg, name.str(), colour);
}

void Xwindow::printMessage(int x, int y, const string& msg, int colour, XFontStruct& f){
  XSetForeground(d, gc, colours[colour]);
  XTextItem ti;
  ti.chars = const_cast<char*>(msg.c_str());
  ti.nchars = msg.length();
  ti.delta = 0;
  ti.font = f.fid;
  XDrawText(d, w, gc, x, y, &ti, 1);
  XSetForeground(d, gc, colours[Black]);
  XFlush(d);
}

