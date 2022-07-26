#ifndef __GRAPHICSDISPLAY_H__
#define __GRAPHICSDISPLAY_H__
#include <X11/Xlib.h>
#include <iostream>
#include <string>
#include "cell.h"
#include "board.h"
#include "info.h"
#include "observer.h"
#include "subject.h"
#include "window.h"
#include "piece.h"
#include <string>


class Cell;
class Board;
template <typename InfoType> class Subject;

class GraphicsDisplay : public Observer<Info> {
	Xwindow xwindow;
	int gridSize;
public:
	GraphicsDisplay(); 
	void notifyIn(Subject<Info> &whoNotified) override; 
	void notifyOut(Subject<Info> &whoNotified) override;
	~GraphicsDisplay(); 
};
#endif


