#include<iostream>
#include"complex.h"
#include"../../../vector/vector.h"
#include<ctime>
using namespace std;
bool mycmp(Complex e1,Complex e2) {
	if (e1.real == e2.real && e1.imag == e2.imag)
		return true;
	return false;
}
void myprint(Complex x) {
	printf("%.2f+%.2fi ", x.real, x.imag);
}
bool compare(Complex e1, Complex e2) {  // ���� 
	if (e1.value > e2.value) return true;
	else if (e1.value == e2.value) {
		if (e1.real > e2.real) return true;
		else return false;
	}
	else return false;
}
bool compare2(Complex e1, Complex e2) {  // ����
	if (e1.value < e2.value) return true;
	else if (e1.value == e2.value) {
		if (e1.real < e2.real) return true;
		else return false;
	}
	else return false;
}

int mysearch(Vector<Complex> A, double e, Rank lo, Rank hi) //���������������
{
	while (lo < hi) {
		Rank mi = (lo + hi) >> 1;
		((e <= A[mi].value)) ? hi = mi : lo = mi + 1;
	}
	return lo;
}
Vector<Complex> partqurry(Vector<Complex> A, int lo, int hi)
{
	int i = mysearch(A, lo, 0, A.size());
	int j = mysearch(A, hi, 0, A.size());
	Vector<Complex> vresult(A, i, j);
	return vresult;
}



int main() {
	cout << "��һ����" << endl;
	Complex pre;
	pre.init(1, 2);
	Vector<Complex> a(50, 6, pre);
	cout << "�������" << endl;
	for (int i = 0; i < a.size(); i++)
	{
		a[i].random();
		myprint(a[i]);
	}
	cout << endl;
	//ɾ��
	cout << "ɾ��" << endl;
	a.remove(2);
	for (int i = 0; i < a.size(); i++)
	{
		myprint(a[i]);
	}
	cout << endl;
	//������ͬ����
	cout << "����" << endl;
	
	a.insert(a[0]);
	for (int i = 0; i < a.size(); i++)
	{
		myprint(a[i]);
	}
	cout << endl;
	//����
	cout << "����" << endl;
	a.unsort(0, a.size());
	for (int i = 0; i < a.size(); i++)
	{
		myprint(a[i]);
	}cout << endl;
	//����
	cout << "����" << endl;
	int result = a.find(a[2],0,a.size(),mycmp);
	cout << result;
	cout << endl;

	cout << "Ψһǰ" << endl;
	for (int i = 0; i < a.size(); i++)
	{
		myprint(a[i]);
	}cout << endl;
	//Ψһ��
	cout << "Ψһ��" << endl;
	a.deduplicate(mycmp);
	for (int i = 0; i < a.size(); i++)
	{
		myprint(a[i]);
	}cout << endl;



	cout << "�ڶ�����" << endl;
	Vector<Complex> b(a, 0, a.size());
	//�����Ƿ����
	//ð��
	printf("ð������ǰ��\n");
	a.traverse(myprint); cout << endl;
	a.bubbleSort(0, a.size(), compare);
	printf("ð�������\n");
	a.traverse(myprint); cout << endl;

	//ѡ��
	printf("�鲢����ǰ��\n");
	b.traverse(myprint); cout << endl;
	b.mergeSort(0, a.size(), compare);
	printf("�鲢�����\n");
	b.traverse(myprint); cout << endl;




	Vector<Complex> c(20000, 7000, pre);
	for (int i = 0; i < c.size(); i++)
	{
		c[i].random();
		c[i].abscomplex();
	}
	Vector<Complex>d(c, 0, c.size());

	clock_t start, end;
	double s;
	//����
	printf("��������£�\n");
	start = clock();
	c.bubbleSort(0, c.size(), compare);
	end = clock();
	s = (double)(end - start) / 1000;
	cout << "ð������" << s << " ms" << endl;

	start = clock();
	d.mergeSort(0, d.size(), compare);
	end = clock();
	s = (double)(end - start) / 1000;
	cout << "�鲢����" << s << " ms" << endl;

	//˳��

	printf("˳������£�\n");
	start = clock();
	c.bubbleSort(0, c.size(), compare);
	end = clock();
	s = (double)(end - start) / 1000;
	cout << "ð������" << s << " ms" << endl;


	start = clock();
	d.mergeSort(0, d.size(), compare);
	end = clock();
	s = (double)(end - start) / 1000;
	cout << "�鲢����" << s << " ms" << endl;


	//����
	cout << "����" << endl;
	start = clock();
	c.bubbleSort(0, c.size(), compare2);
	end = clock();
	s = (double)(end - start) / 1000;
	cout << "ð������" << s << " ms" << endl;


	start = clock();
	d.mergeSort(0, d.size(), compare2);
	end = clock();
	s = (double)(end - start) / 1000;
	cout << "�鲢����" << s << " ms" << endl;

	cout << "��������" << endl;
	a.mergeSort(0, a.size(), compare);
	for (int i = 0; i < a.size(); i++)
	{
		myprint(a[i]);
	}cout << endl;


	int n1 = 2, n2 = 100;
	cout << "��ѯ���: " << endl;
	Vector<Complex>result_1 = partqurry(a, n1, n2);
	for (int i = 0; i < result_1.size(); i++)
	{
		myprint(result_1[i]);
	}
	
	cout << endl;

	return 0;
}