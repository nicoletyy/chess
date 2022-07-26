#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include "info.h"
#include <memory>


#include <iostream>
using namespace std;

template <typename InfoType> class Observer;

template <typename InfoType> class Subject {
  std::vector<shared_ptr<Observer<InfoType>>> observers;

 public:
  void attach(shared_ptr<Observer<InfoType>> o);  
  void detach(shared_ptr<Observer<InfoType>> o);
//  void detachPiece(shared_ptr<Observer<InfoType>> o);
  void detachAll();
  virtual bool hasObserver()=0;
  void notifyObserversIn() {
    for (auto &ob : observers) ob->notifyIn(*this);
  }
  void notifyObserversOut() {
    for (auto &ob : observers) ob->notifyOut(*this);
  }
  virtual InfoType getInfo() const = 0;
  std::vector<shared_ptr<Observer<InfoType>>> getObserver() {return observers;} 

};




template <typename InfoType>
void Subject<InfoType>::attach(shared_ptr<Observer<InfoType>> o) {
	observers.emplace_back(o);
}



//void detachPiece(shared_ptr<Observer<InfoType>> o);




template <typename InfoType>
void Subject<InfoType>::detach(shared_ptr<Observer<InfoType>> o) {
	if ((int)observers.size() != 0) {
		for (int i = 0; i < (int)observers.size(); ++i) {
			if (observers[i].get() == o.get()) {
				observers.erase(observers.begin()+i);
				return;
			}
		}
	}
} 
        




template <typename InfoType>
void Subject<InfoType>::detachAll() {
	for (int i = 2; i < (int)observers.size(); ++i) {
		observers.erase(observers.begin()+i);
	}
}


#endif





