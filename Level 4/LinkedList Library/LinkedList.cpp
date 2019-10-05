#include "LinkedList.h"
#include <iostream>

using namespace std;

int Compare(void *one, void *other);

int main(int argc, char *argv[]) {
	//1. 연결리스트를 만든다.
	LinkedList<Long> linkedList;

	LinkedList<Long>::Node *index;

	//2. 100을 맨 뒤에 추가하다.				100
	index = linkedList.AppendFromTail(100);
	cout << index->GetObject() << endl;

	//3. 200을 맨 앞에 추가하다.				200 100
	index = linkedList.AppendFromHead(200);
	cout << index->GetObject() << endl;

	//4. 다음으로 이동하다.						200 100
	index = linkedList.Next();
	cout << index->GetObject() << endl;

	//5. 300을 100앞에 삽입하다.				200 300 100
	index = linkedList.InsertBefore(index, 300);
	cout << index->GetObject() << endl;

	//6. 처음으로 이동하다.						200 300 100
	index = linkedList.First();
	cout << index->GetObject() << endl;
	
	//7. 400을 200뒤에 삽입하다.				200 400 300 100
	index = linkedList.InsertAfter(index, 400);
	cout << index->GetObject() << endl;

	//8. 300을 선형검색하다.					200 400 300 100
	Long key = 300;
	index = linkedList.LinearSearchUnique(&key, Compare);
	cout << index->GetObject() << endl;
	
	//9. 300을 삭제하다.						200 400 100
	index = linkedList.Delete(index);
	if (index == 0) {
		cout << "지워졌습니다." << endl;
	}

	//10. 100의 이전으로 이동하다.				200 400 100
	index = linkedList.Previous();
	cout << index->GetObject() << endl;

	//11. 200을 맨 뒤에 추가하다.				200 400 100 200
	index = linkedList.AppendFromTail(200);
	cout << index->GetObject() << endl;

	//12. 200을 선형검색하다.					200 400 100 200
	LinkedList<Long>::Node* (*indexes);
	Long count;
	Long object;
	key = 200;
	linkedList.LinearSearchDuplicate(&key, &indexes, &count, Compare);
	Long i = 0;
	while (i < count) {
		object = indexes[i]->GetObject();
		cout << object << endl;
		i++;
	}

	//13. 처음 200으로 이동하다.				200 400 100 200
	index = linkedList.Move(indexes[0]);
	cout << index->GetObject() << endl;

	//14. 맨 뒤를 지우다.						200 400 100
	index = linkedList.DeleteFromTail();
	if (index == 0) {
		cout << "지워졌습니다." << endl;
	}

	//15. 맨 앞을 지우다.						400 100
	index = linkedList.DeleteFromHead();
	if (index == 0) {
		cout << "지워졌습니다." << endl;
	}

	//16. 마지막으로 이동하다.					400 100
	index = linkedList.Last();
	cout << index->GetObject() << endl;

	//17. 모두 지우다.
	linkedList.DeleteAllItems();
	if (linkedList.GetLength() == 0) {
		cout << "모두 지워졌습니다." << endl;
	}

	//18. 500을 맨 뒤에 삽입하다.				500
	index = linkedList.AppendFromTail(500);
	cout << index->GetObject() << endl;

	//19. 100을 500 앞에 삽입하다.				100 500
	index = linkedList.InsertBefore(index, 100);
	cout << index->GetObject() << endl;

	//복사하다.									`100 500
	LinkedList<Long> newLinkedList(linkedList);
	i = 0;
	while (i < newLinkedList.GetLength()) {
		cout << newLinkedList[i] << endl;
		i++;
	}

	//치환하다.
	index = newLinkedList.DeleteFromTail();		//`100
	linkedList = newLinkedList;
	i = 0;
	while (i < linkedList.GetLength()) {
		cout << linkedList[i] << endl;
		i++;
	}

	return 0;
}
int Compare(void *one, void *other) {
	Long *one_ = static_cast<Long*>(one);
	Long *other_ = static_cast<Long*>(other);
	int ret;

	if (*one_ < *other_) {
		ret = -1;
	}
	else if (*one_ == *other_) {
		ret = 0;
	}
	else if (*one_ > *other_) {
		ret = -1;
	}

	return ret;
}