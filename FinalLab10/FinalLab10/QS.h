#ifndef QS_H
#define QS_H
#include <iostream>
#include <string>
#include <algorithm>
#include "QSInterface.h"
using namespace std;

template<typename T>
class QS : public QSInterface<T>
{
private:
	size_t quickCapacity;
	int itemsNum;
	T* myArray;
	size_t compare;
	size_t exchange;

	void reallocate() 
	{
		T* numberNew = new T[2 * quickCapacity];
		for (int i = 0; i < (2 * quickCapacity); ++i) 
		{ 
			numberNew[i] = 0; 
		}
		for (size_t i = 0; i < itemsNum; ++i) 
		{ 
			numberNew[i] = myArray[i]; 
		}
		swap(myArray, numberNew);
		quickCapacity = 2 * quickCapacity;
		delete[] numberNew;
	}
public:
	QS() 
	{
		quickCapacity = 0;
		itemsNum = 0;
		myArray = new T[0];
		compare = 0;
		exchange = 0;
	}
	~QS() 
	{
		delete[] myArray;
	}

	bool checkNoPivot(int left, int right) 
	{
		if (right <= left || itemsNum == 0 || right > itemsNum || left > itemsNum || right < 0 || left < 0) { return false; }
		else { return true; }
	}
	bool checkWithPivot(int left, int right, int pivot) 
	{
		if (right <= left || pivot <= left || right <= pivot || itemsNum == 0 || right > itemsNum || left > itemsNum || pivot > itemsNum || right < 0 || left < 0 || pivot < 0) { return false; }
		else { return true; }
	}

	void setFlags() 
	{
		compare = 0;
		exchange = 0;
	}

	void setSize(size_t sizeOfArray) 
	{
		delete[] myArray;
		myArray = new T[sizeOfArray];
		for (int i = 0; i < sizeOfArray; ++i) 
		{									
			myArray[i] = 0;					
		}
		quickCapacity = sizeOfArray;
		itemsNum = 0;
	}

	bool addElement(T element) 
	{
		int copyItemsNum = itemsNum;
		if (itemsNum == quickCapacity && quickCapacity != 0) reallocate(); 
		myArray[itemsNum] = element; 
		++itemsNum;					
		if (itemsNum == copyItemsNum + 1) { return true; }
		else { return false; }
	}

	bool sort(size_t left, size_t right) 
	{
		if (!checkNoPivot(static_cast<int>(left), static_cast<int>(right))) { return false; }
		if (left - right > 1) 
		{
			size_t pivot = partition(left, right, medianOfThree(left, right)); 
			sort(left, pivot); 
			sort(pivot + 1, right); 
		}
		return true;
	}

	bool sortAll() 
	{
		sort(0, itemsNum);
		return true;
	}

	bool clear() 
	{
		itemsNum = 0;
		return true;
	}

	size_t capacity() const
	{
		return quickCapacity;
	}

	size_t size() const 
	{
		return itemsNum;
	}

	int medianOfThree(size_t left, size_t right) 
	{
		size_t median = (left + right) / 2; 
		if (myArray[median] < myArray[left]) { swap(myArray[left], myArray[median]); }
		if (myArray[right - 1] < myArray[median]) 
		{
			swap(myArray[median], myArray[right - 1]);
			if (myArray[median] < myArray[left]) { swap(myArray[median], myArray[left]); }
		}
		return static_cast<int>(median); 
	}

	int partition(size_t left, size_t right, size_t pivotIndex) 
	{
		size_t up = left + 1;
		size_t down = right - 1;
		swap(myArray[left], myArray[pivotIndex]); 
		pivotIndex = left; 
		do
		{
			while (myArray[up] <= myArray[pivotIndex] && up < right - 1) { ++up; }
			while (myArray[down] > myArray[pivotIndex] && down > left) { --down; }
			if (up < down && myArray[up] > myArray[down]) { swap(myArray[up], myArray[down]); }								
		} while (up < down);
		swap(myArray[left], myArray[down]);
		pivotIndex = down;						
		return static_cast<int>(pivotIndex);
	}

	string toString() const 
	{
		stringstream out;
		for (int i = 0; i < itemsNum; ++i)
		{
			out << myArray[i];
			if (i < itemsNum - 1) { out << ","; }
		}
		return out.str();
	}

	friend ostream& operator<<(ostream& out, QS& other) 
	{
		return out << other.toString();
	}
};



#endif