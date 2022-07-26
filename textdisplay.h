#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <vector>
#include "observer.h"
#include "info.h"
#include "subject.h"

class Cell;
class Board;

class TextDisplay: public Observer<Info> {
  std::vector<std::vector<char>> textDisplay;

 public:
  TextDisplay();
  void notifyIn(Subject<Info> &whoNotified) override;
  void notifyOut(Subject<Info> &whoNotified) override;
  friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
#endif



