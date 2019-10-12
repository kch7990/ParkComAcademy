#include "Axis.h"
#include "Array.h"
#include <math.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
Axis::Axis() {

}

Axis::Axis(const Axis& source) {

}

Axis::~Axis() {

}

void Axis::ConvertToHist(Array<double>& weights, Array<double> *axisX, Array<Long> *axisY) {
	double minX = -4.0F;
	double maxX = 4.0F;
	double unit = 0.1F;

	//x축 배열 데이터 넣기 : 어떤 범위의 대푯값
	Long capacity = static_cast<Long>((maxX - minX) / unit);
	axisX->Resize(capacity);
	double delegate = minX + unit / 2;

	Long i = 0;
	while (i < axisX->GetCapacity()) {
		axisX->Store(i, delegate);
		delegate += unit;
		i++;
	}
	
	Long index;
	//가중치가 고정범위(-4 ~ 4)를 벗어날 때 x축배열 앞뒤에 추가하기
	i = 0;
	while (i < weights.GetLength() && weights[i] < minX) {
		delegate = static_cast<double>(floor(weights[i] * 10)) / 10 + unit / 2; //가중치 값에서 소수점 첫째 자리 밑으로 제거한 후 0.05 더하기
		if (i <= 0) {
			index = axisX->AppendFromFront(delegate);
		}
		else {
			index = axisX->Insert(index + 1, delegate);
		}
		i++;
	}

	i = weights.GetLength() - 1;
	while (i >= 0 && weights[i] > maxX) {
		delegate = static_cast<double>(floor(weights[i] * 10))/10 + unit / 2;
		if (i >= weights.GetLength() - 1) {
			index = axisX->AppendFromRear(delegate);
		}
		else {
			index = axisX->Insert(index - 1, delegate);
		}
		i--;
	}
	
	//y축 배열 데이터 넣기 : 어떤 범위에 해당하는 가중치의 개수
	axisY->Resize(axisX->GetLength()); //범위 벗어나는 가중치가 있으면 axisX의 크기가 바뀔 수 있음.
	i = 0;
	while (i < axisY->GetCapacity()) {
		axisY->Store(i, 0);
		i++;
	}

	weights.SelectionSort(CompareFloat);
	Long count;
	Long j = 0;
	i = 0;
	while (i < weights.GetLength()) {
		//현재 x=범위의 대푯값, 범위 = (대푯값 - 단위/2) ~ (대푯값 + 단위/2)
		//현재 가중치가 범위 안에 들어가면 개수를 늘려 y배열에 넣는다.
		while (j < axisX->GetLength() && (axisX->GetAt(j) - unit / 2 >= weights[i] || axisX->GetAt(j) + unit / 2 < weights[i])) {
			j++;
		}
		if (j < axisX->GetLength()) {
			count = axisY->GetAt(j);
			count++;
			axisY->Modify(j, count);
		}
		i++;
	}
}

Axis& Axis::operator =(const Axis& source) {
	return *this;
}

int CompareFloat(void *one, void *other) {
	double *one_ = static_cast<double*>(one);
	double *other_ = static_cast<double*>(other);
	int ret;

	if (*one_ < *other_) {
		ret = -1;
	}
	else if (*one_ == *other_) {
		ret = 0;
	}
	else if ((*one_ > *other_)) {
		ret = 1;
	}

	return ret;
}

#if 0
#include <iostream>
using namespace std;
int main(int argc, char *argv[]) {
	Axis axis;
	Array<double> weights(10);
	weights.Store(0, -0.94f);
	weights.Store(1, -0.74f);
	weights.Store(2, -0.44f);
	weights.Store(3, -0.20f);
	weights.Store(4, -0.11f);
	weights.Store(5, 0.01f);
	weights.Store(6, 0.13f);
	weights.Store(7, 0.23f);
	weights.Store(8, 0.42f);
	weights.Store(9, 0.85f);

	Array<double> axisX;
	Array<Long> axisY;

	axis.ConvertToHist(weights, &axisX, &axisY);
	Long i = 0;
	while (i < axisX.GetLength()) {
		cout << "X축 " << axisX.GetAt(i) << endl;
		cout << axisX.GetAt(i) - 0.05 << " ~ " << axisX.GetAt(i) + 0.05 << endl;
		cout << "Y축 " << axisY.GetAt(i) << endl;
		cout << endl;
		i++;
	}
	return 0;
}
#endif