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
    if (left >= right) return; // �ݹ����

    int mid = (left + right) / 2; // �ָ��
    merge_sort(arr, left, mid); // �ֱ�����������ֽ�������
    merge_sort(arr, mid + 1, right);
    Vector<int> tmp(right - left + 1); // ��ʱ����

    int i = left, j = mid + 1, k = 0; // ��ʼ��ָ��

    // �����������ֺϲ�����ʱ������
    while (i <= mid && j <= right) {
        if (arr[i] < arr[j]) tmp[k++] = arr[i++];
        else tmp[k++] = arr[j++];
    }
    while (i <= mid) tmp[k++] = arr[i++];
    while (j <= right) tmp[k++] = arr[j++];

    // ���ź������ʱ���鿽����ԭ����
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
	cout<<"������������ʾ����"<<endl; 
	arr.bubbleSort(0,30001);
	
	//˳�� 
	cout<<"˳������£�"<<endl;
	
	//ð��
	 
	start = clock();
	arr.bubbleSort(0,30001);
	end = clock();
	s = (double)(end - start) / 1000;
	cout << endl;
	cout << "ð������" << s << " s" << endl;
	
	
	//����
	start = clock();
	insertionSort1(arr); 
	end = clock();
	s = (double)(end - start) / 1000;
	cout << endl;
	cout << "��������" << s << " s" << endl;	 
	
	
	//ѡ��
	start = clock();
	arr.selectionSort(0,30001) ;
	end = clock();
	s = (double)(end - start) / 1000;
	cout << endl;
	cout << "ѡ������" << s << " s" << endl;	 
	
	
	//�鲢
	start = clock();
	merge_sort(arr,0,30001);
	end = clock();
	s = (double)(end - start) / 1000;
	cout << endl;
	cout << "�鲢����" << s << " s" << endl;	 
	
	
	//����
	start = clock();
	arr.quickSort(0,30000);
	end = clock();
	s = (double)(end - start) / 1000;
	cout << endl;
	cout << "��������" << s << " s" << endl;	
	
	cout<<endl;

	
	cout<<"--------------------------------------------"<<endl;
	//����
	cout<<"��������£�"<<endl;
	insertionSort2(arr);
	
	
	//ð��
	 
	start = clock();
	arr.bubbleSort(0,30001);
	end = clock();
	s = (double)(end - start) / 1000;
	cout << endl;
	cout << "ð������" << s << " s" << endl;

	
	//����
	start = clock();
	insertionSort2(arr); 
	end = clock();
	s = (double)(end - start) / 1000;
	cout << endl;
	cout << "��������" << s << " s" << endl;
	
	
	//ѡ��
	start = clock();
	arr.selectionSort(0,30001) ;
	end = clock();
	s = (double)(end - start) / 1000;
	cout << endl;
	cout << "ѡ������" << s << " s" << endl;	
	
	
	
	
	//�鲢
	start = clock();
	merge_sort(arr,0,30001);
	end = clock();
	s = (double)(end - start) / 1000;
	cout << endl;
	cout << "�鲢����" << s << " s" << endl;	
	
	
	
	//����
	start = clock();
	arr.quickSort(0,30001);
	end = clock();
	s = (double)(end - start) / 1000;
	cout << endl;
	cout << "��������" << s << " s" << endl;	
	
	cout<<endl;
	
	
	cout<<"--------------------------------------------"<<endl;
	//����
	cout<<"��������£�"<<endl;
	 
	arr.unsort(0,arr.size());   //����
	
	
	//ð��
	 
	start = clock();
	arr.bubbleSort(0,30001);
	end = clock();
	s = (double)(end - start) / 1000;
	cout << endl;
	cout << "ð������" << s << " s" << endl;
	
	
	
	start = clock();
	insertionSort1(arr); 
	end = clock();
	s = (double)(end - start) / 1000;
	cout << endl;
	cout << "��������" << s << " s" << endl;	 
	
	
	
	//ѡ��
	start = clock();
	arr.selectionSort(0,30001) ;
	end = clock();
	s = (double)(end - start) / 1000;
	cout << endl;
	cout << "ѡ������" << s << " s" << endl;	
	
	
	
	//�鲢
	start = clock();
	merge_sort(arr,0,30001);
	end = clock();
	s = (double)(end - start) / 1000;
	cout << endl;
	cout << "�鲢����" << s << " s" << endl;	
	
	
	//����
	start = clock();
	arr.quickSort(0,30001);
	end = clock();
	s = (double)(end - start) / 1000;
	cout << endl;
	cout << "��������" << s << " s" << endl;	
	
	
	return 0;	 
	
}
