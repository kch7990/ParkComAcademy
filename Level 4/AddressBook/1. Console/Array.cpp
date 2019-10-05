#if 0
#include "Array.h"
#include <iostream>

using namespace std;

int Compare(void *one, void *other);

int main(int argc, char* argv[]) {
	//1. 배열을 3만큼 생성하다.
	Array<Long> array(3);
	//2. 숫자 30을 위치 1에 저장하다.
	Long index = array.Store(0, 30);
	cout << array[index] << endl;
	//3. 숫자 10을 위치 2에 저장하다.
	index = array.Store(1, 10);
	cout << array[index] << endl;
	//4. 숫자 20을 위치 3에 저장하다.
	index = array.Store(2, 20);
	cout << array[index] << endl;
	//5. 숫자 20을 위치 2에 삽입하다.
	index = array.Insert(2, 20);
	cout << array[index] << endl;
	//6. 숫자 20을 선형검색하다.
	Long key = 20;
	Long(*indexes);
	Long count;
	array.LinearSearchDuplicate(&key, &indexes, &count, Compare);
	Long i = 0;
	while (i < count) {
		cout << array[indexes[i]] << endl;
		i++;
	}
	if (indexes != 0) {
		delete[] indexes;
	}
	//7. 맨 뒤의 배열요소를 삭제하다.
	index = array.DeleteFromRear();
	if (index == -1) {
		cout << "지워졌습니다." << endl;
	}
	//8. 맨 앞에 숫자 50을 추가하다.
	index = array.AppendFromFront(50);
	cout << array[index] << endl;
	//9. 숫자 10을 선형검색하다.
	key = 10;
	index = array.LinearSearchUnique(&key, Compare);
	if (index != -1) {
		cout << array[index] << endl;
	}
	//10. 거품정렬하다.
	array.BubbleSort(Compare);
	i = 0;
	while (i < array.GetLength()) {
		cout << array[i] << endl;
		i++;
	}
	//11. 클리어하다.
	array.Clear();
	if (array.GetLength() == 0) {
		cout << "클리어" << endl;
	}
	//12. one 배열을 2만큼 생성하다.
	Array<Long> one(2);
	//13. 숫자 50을 one의 위치 1에 저장하다.
	index = one.Store(0, 50);
	cout << one[index] << endl;
	//14. 숫자 90을 one의 위치 2에 저장하다.
	index = one.Store(1, 90);
	cout << one[index] << endl;
	//15. other 배열을 3만큼 생성하다.
	Array<Long> other(3);
	//16. 숫자 60을 other의 위치 1에 저장하다.
	index = other.Store(0, 60);
	cout << other[index] << endl;
	//17. 숫자 70을 other의 위치 2에 저장하다.
	index = other.Store(1, 70);
	cout << other[index] << endl;
	//18. 숫자 80을 other의 위치 3에 저장하다.
	index = other.Store(2, 80);
	cout << other[index] << endl;
	//19. one과 other를 병합하다.
	array.Merge(one, other, Compare);
	i = 0;
	while (i < array.GetLength()) {
		cout << array[i] << endl;
		i++;
	}
	//20. 위치 4의 배열요소를 삭제하다.
	index = array.Delete(3);
	if (index == -1) {
		cout << "지워졌습니다." << endl;
	}
	//21. 숫자 70을 이분검색하다.
	key = 70;
	index = array.BinarySearchUnique(&key, Compare);
	if (index != -1) {
		cout << array[index] << endl;
	}
	//22. 맨 뒤에 숫자 40을 추가하다.
	index = array.AppendFromRear(40);
	cout << array[index] << endl;
	//23. 선택정렬하다.
	array.SelectionSort(Compare);
	i = 0;
	while (i < array.GetLength()) {
		cout << array[i] << endl;
		i++;
	}
	//24. 맨 앞의 배열요소를 삭제하다.
	index = array.DeleteFromFront();
	if (index == -1) {
		cout << "지워졌습니다." << endl;
	}
	//25. 위치 1의 배열요소를 숫자 90으로 수정하다.
	index = array.Modify(0, 90);
	cout << array[index] << endl;
	//26. 삽입정렬하다.
	array.InsertionSort(Compare);
	Long object;
	i = 0;
	while (i < array.GetLength()) {
		object = array.GetAt(i);
		cout << object << endl;
		i++;
	}
	//27. 숫자 90을 이분검색하다.
	key = 90;
	array.BinarySearchDuplicate(&key, &indexes, &count, Compare);
	i = 0;
	while (i < count) {
		object = array.GetAt(indexes[i]);
		cout << object << endl;
		i++;
	}
	if (indexes != 0) {
		delete[] indexes;
	}
	//주소 구하는 + 연산자 검증
	Long *ret;
	i = 0;
	while (i < array.GetLength()) {
		ret = array + i;
		cout << *ret << endl;
		i++;
	}
	//28. 배열을 없애다.

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
		ret = 1;
	}

	return ret;
}
#endif