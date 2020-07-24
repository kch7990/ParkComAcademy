#include "Stack.h"

#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
	Long object;
	Long top;
	Long ret;
	bool isEmpty;

	//1. 스택을 만들다.
	Stack<Long> stack(2);
	//2. 100을 넣다.
	object = 100;
	top = stack.Push(object);
	cout << "top : " << top << " obj : " << stack.Top() << endl;
	//3. 200을 넣다.
	object = 200;
	top = stack.Push(object);
	cout << "top : " << top << " obj : " << stack.Top() << endl;
	//4. 50을 넣다.
	object = 50;
	top = stack.Push(object);
	cout << "top : " << top << " obj : " << stack.Top() << endl;
	//5. 꺼내다.
	ret = stack.Pop();
	if (ret == -1) {
		cout << "지웠다." << endl;
	}
	cout << "top : " << stack.GetTop() << " obj : " << stack.Top() << endl;
	//비어있는지 확인한다.
	isEmpty = stack.IsEmpty();
	if (isEmpty == true) {
		cout << "비어있다." << endl;
	}
	else {
		cout << "비어있지 않다." << endl;
	}
	//6. 비우다.
	stack.Empty();
	if (stack.GetTop() == 0) {
		cout << "모두 지웠다." << endl;
	}
	//비어있는지 확인한다.
	isEmpty = stack.IsEmpty();
	if (isEmpty == true) {
		cout << "비어있다." << endl;
	}
	else {
		cout << "비어있지 않다." << endl;
	}
	//7. 20을 넣다.
	object = 20;
	top = stack.Push(object);
	cout << "top : " << top << " obj : " << stack.Top() << endl;

	//8. 스택을 지우다.

	return 0;
}