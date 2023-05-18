#include"../../vector_1/vector_1.h"
#include<iostream>
#include<ctime>
#include<stdlib.h>
using namespace std;

void myprint(int x) {
	printf("%d ",x );
}

void insertionSort1(Vector<int>& arr) {
  int n = arr.size();
  for (int i = 1; i < n; i++) {
    int j = i - 1;
    int key = arr[i];
    while (j >= 0 && arr[j] > key) {
      arr[j + 1] = arr[j];
      j--;
    }
    arr[j + 1] = key;
  }
}


void insertionSort2(Vector<int>& arr) {
  int n = arr.size();
  for (int i = 1; i < n; i++) {
    int j = i - 1;
    int key = arr[i];
    while (j >= 0 && arr[j] < key) {
      arr[j + 1] = arr[j];
      j--;
    }
    arr[j + 1] = key;
  }
}

void merge_sort(Vector<int>& arr, int left, int right) {
    if (left >= right) return; // 递归出口

    int mid = (left + right) / 2; // 分割点
    merge_sort(arr, left, mid); // 分别对左右两部分进行排序
    merge_sort(arr, mid + 1, right);
    Vector<int> tmp(right - left + 1); // 临时数组

    int i = left, j = mid + 1, k = 0; // 初始化指针

    // 将左右两部分合并到临时数组中
    while (i <= mid && j <= right) {
        if (arr[i] < arr[j]) tmp[k++] = arr[i++];
        else tmp[k++] = arr[j++];
    }
    while (i <= mid) tmp[k++] = arr[i++];
    while (j <= right) tmp[k++] = arr[j++];

    // 将排好序的临时数组拷贝回原序列
    for (int i = 0; i < k; ++i) {
        arr[left + i] = tmp[i];
    }
}


int main() {
	clock_t start, end;
	double s;
	
	
	Vector<int> arr(10);
	
	
	for (int i = 0; i < 30000; i++) {
		arr.insert(i,rand()%1000 + 1);
	}
	cout<<"数据量过大不显示数据"<<endl; 
	arr.bubbleSort(0,30001);
	
	//顺序 
	cout<<"顺序情况下："<<endl;
	
	//冒泡
	 
	start = clock();
	arr.bubbleSort(0,30001);
	end = clock();
	s = (double)(end - start) / 1000;
	cout << endl;
	cout << "冒泡排序：" << s << " s" << endl;
	
	
	//插入
	start = clock();
	insertionSort1(arr); 
	end = clock();
	s = (double)(end - start) / 1000;
	cout << endl;
	cout << "插入排序：" << s << " s" << endl;	 
	
	
	//选择
	start = clock();
	arr.selectionSort(0,30001) ;
	end = clock();
	s = (double)(end - start) / 1000;
	cout << endl;
	cout << "选择排序：" << s << " s" << endl;	 
	
	
	//归并
	start = clock();
	merge_sort(arr,0,30001);
	end = clock();
	s = (double)(end - start) / 1000;
	cout << endl;
	cout << "归并排序：" << s << " s" << endl;	 
	
	
	//快速
	start = clock();
	arr.quickSort(0,30000);
	end = clock();
	s = (double)(end - start) / 1000;
	cout << endl;
	cout << "快速排序：" << s << " s" << endl;	
	
	cout<<endl;

	
	cout<<"--------------------------------------------"<<endl;
	//逆序
	cout<<"逆序情况下："<<endl;
	insertionSort2(arr);
	
	
	//冒泡
	 
	start = clock();
	arr.bubbleSort(0,30001);
	end = clock();
	s = (double)(end - start) / 1000;
	cout << endl;
	cout << "冒泡排序：" << s << " s" << endl;

	
	//插入
	start = clock();
	insertionSort2(arr); 
	end = clock();
	s = (double)(end - start) / 1000;
	cout << endl;
	cout << "插入排序：" << s << " s" << endl;
	
	
	//选择
	start = clock();
	arr.selectionSort(0,30001) ;
	end = clock();
	s = (double)(end - start) / 1000;
	cout << endl;
	cout << "选择排序：" << s << " s" << endl;	
	
	
	
	
	//归并
	start = clock();
	merge_sort(arr,0,30001);
	end = clock();
	s = (double)(end - start) / 1000;
	cout << endl;
	cout << "归并排序：" << s << " s" << endl;	
	
	
	
	//快速
	start = clock();
	arr.quickSort(0,30001);
	end = clock();
	s = (double)(end - start) / 1000;
	cout << endl;
	cout << "快速排序：" << s << " s" << endl;	
	
	cout<<endl;
	
	
	cout<<"--------------------------------------------"<<endl;
	//乱序
	cout<<"乱序情况下："<<endl;
	 
	arr.unsort(0,arr.size());   //置乱
	
	
	//冒泡
	 
	start = clock();
	arr.bubbleSort(0,30001);
	end = clock();
	s = (double)(end - start) / 1000;
	cout << endl;
	cout << "冒泡排序：" << s << " s" << endl;
	
	
	
	start = clock();
	insertionSort1(arr); 
	end = clock();
	s = (double)(end - start) / 1000;
	cout << endl;
	cout << "插入排序：" << s << " s" << endl;	 
	
	
	
	//选择
	start = clock();
	arr.selectionSort(0,30001) ;
	end = clock();
	s = (double)(end - start) / 1000;
	cout << endl;
	cout << "选择排序：" << s << " s" << endl;	
	
	
	
	//归并
	start = clock();
	merge_sort(arr,0,30001);
	end = clock();
	s = (double)(end - start) / 1000;
	cout << endl;
	cout << "归并排序：" << s << " s" << endl;	
	
	
	//快速
	start = clock();
	arr.quickSort(0,30001);
	end = clock();
	s = (double)(end - start) / 1000;
	cout << endl;
	cout << "快速排序：" << s << " s" << endl;	
	
	
	return 0;	 
	
}
