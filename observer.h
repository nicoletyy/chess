#ifndef _OBSERVER_H_
#define _OBSERVER_H_
#include <memory>

template <typename InfoType> class Subject;

template <typename InfoType> class Observer {
 public:
  virtual void notifyIn(Subject<InfoType> &whoFrom) = 0; 
  virtual void notifyOut(Subject<InfoType> &whoTo) = 0;  
  virtual ~Observer() = default;
};
#endif
