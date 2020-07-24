#include "Stack.h"

#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
	Long object;
	Long top;
	Long ret;
	bool isEmpty;

	//1. ������ �����.
	Stack<Long> stack(2);
	//2. 100�� �ִ�.
	object = 100;
	top = stack.Push(object);
	cout << "top : " << top << " obj : " << stack.Top() << endl;
	//3. 200�� �ִ�.
	object = 200;
	top = stack.Push(object);
	cout << "top : " << top << " obj : " << stack.Top() << endl;
	//4. 50�� �ִ�.
	object = 50;
	top = stack.Push(object);
	cout << "top : " << top << " obj : " << stack.Top() << endl;
	//5. ������.
	ret = stack.Pop();
	if (ret == -1) {
		cout << "������." << endl;
	}
	cout << "top : " << stack.GetTop() << " obj : " << stack.Top() << endl;
	//����ִ��� Ȯ���Ѵ�.
	isEmpty = stack.IsEmpty();
	if (isEmpty == true) {
		cout << "����ִ�." << endl;
	}
	else {
		cout << "������� �ʴ�." << endl;
	}
	//6. ����.
	stack.Empty();
	if (stack.GetTop() == 0) {
		cout << "��� ������." << endl;
	}
	//����ִ��� Ȯ���Ѵ�.
	isEmpty = stack.IsEmpty();
	if (isEmpty == true) {
		cout << "����ִ�." << endl;
	}
	else {
		cout << "������� �ʴ�." << endl;
	}
	//7. 20�� �ִ�.
	object = 20;
	top = stack.Push(object);
	cout << "top : " << top << " obj : " << stack.Top() << endl;

	//8. ������ �����.

	return 0;
}