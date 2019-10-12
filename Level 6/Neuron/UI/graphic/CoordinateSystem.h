#ifndef _COORDINATESYSTEM_H
#define _COORDINATESYSTEM_H

#include "CompositeGraph.h"
#include <windef.h>

typedef signed long int Long;

class Visitor;
class CoordinateSystem : public CompositeGraph {
public:
	CoordinateSystem();
	CoordinateSystem(Long capacity, double magnificationX, double magnificationY, Long originX, Long originY);
	CoordinateSystem(const CoordinateSystem& source);
	virtual ~CoordinateSystem();
	virtual void Accept(Visitor *visitor);

	CoordinateSystem& operator=(const CoordinateSystem& source);
	Graph* operator[](Long index);
	Graph* GetAt(Long index);
	virtual Graph* Clone();

	double GetMagnificationX() const;
	double GetMagnificationY() const;
	Long GetOriginX() const;
	Long GetOriginY() const;
private:
	double magnificationX;
	double magnificationY;
	Long originX;
	Long originY;
};

inline double CoordinateSystem::GetMagnificationX() const {
	return this->magnificationX;
}

inline double CoordinateSystem::GetMagnificationY() const {
	return this->magnificationY;
}

inline Long CoordinateSystem::GetOriginX() const {
	return this->originX;
}

inline Long CoordinateSystem::GetOriginY() const {
	return this->originY;
}

#endif //_COORDINATESYSTEM_H