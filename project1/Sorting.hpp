#ifndef __SORTING_H
#define __SORTING_H

#include <iostream>
#include "Helper.hpp"

using namespace std;

template <class T> void selectionsort(T* data, int size)
{
	int m;
	for (int i = 0; i < size; i++)
	{
		m = i;
		// this for loop is try to find the min of the rest array.
		// it means find the min except when program already swap
		for (int j = i + 1; j < size; j++)
		{
			if (data[j] <= data[m])
				m = j;
		}
		Swap(data[m], data[i]);

	}
}
template <class T> void insertionsort(T* data, int size)
{
	int i, j, temp;
	for (i = 0; i < size; i++)
	{
		j = i;
		
		//moves element forward try to shift the data
		// and insert the data
		while ((data[j]<data[j-1]) && (j > 0))
		{
			temp = data[j-1];      
			data[j-1] = data[j];
			data[j] = temp;
			j= j-1;
		}

	}
}

template <class T> void mergesort(T* data, int size, T* temp)
{
	T  *left, *right;
		int i =0 , j = 0, l = 0, r = 0, s = 0;
		int mid;

	if (size > 1)
	{
		mid = (size + 1) / 2;
		left = data;
		right = &data[mid];
		mergesort(left, mid, temp);
		mergesort(right, size - mid, &temp[mid]); // the & means start at this postion

		// the following code is translate from the project 1 PDF
		while ((l < mid) && (r < size - mid))
		{
			if (left[l] < right[r])
			{
				temp[s] = left[l];
				l = l + 1;
			}
			else
			{
				temp[s] = right[r];
				r = r + 1;
			}
			s = s + 1;
		}
		for (i = s, j = l; i < s + mid - l, j < mid; i++, j++)
		{
			temp[i] = left[j];
		}
		s = s + mid - l;
		for (i = r, j = s; i < size - mid; i++, j++)
		{
			temp[j] = right[i];
		}
		for (i = 0; i < size; i++)
		{
			data[i] = temp[i];
		}
	}
}

template <class T> void quicksort(T* data, int size)
{
	int pivot, left = 0, right = size -1;
	if (size <= 1)
		return;
	int mid = (size + 1) / 2;
	pivot = medianof3(data[0], data[mid], data[size - 1]);  // check median and assign it to pivot
	if (pivot ==1)
		pivot = 0;
	else if (pivot ==2)
		pivot = mid;
	else
		pivot = size - 1;
	Swap(data[pivot], data[0]);
	// the following code is from the project 1 PDF

	do
	{
		while ((left<right) &&(data[left] <= data[0]))
			left = left + 1;
		while((left < right) && (data[right] > data[0]))
			right = right - 1;
		Swap(data[left], data[right]);

	} while (left < right);

	if (data[left] > data[0])
		left = left - 1;
	Swap(data[0], data[left]);

	quicksort(data, left);
	quicksort(&data[left + 1], size - left-1);


}


#endif
