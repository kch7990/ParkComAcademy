#include "Visitor.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
Visitor::Visitor() {

}

Visitor::Visitor(const Visitor& source) {

}

Visitor::~Visitor() {

}

Visitor& Visitor::operator=(const Visitor& source) {
	return *this;
}