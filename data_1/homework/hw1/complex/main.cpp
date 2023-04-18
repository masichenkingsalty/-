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
bool compare(Complex e1, Complex e2) {  // 升序 
	if (e1.value > e2.value) return true;
	else if (e1.value == e2.value) {
		if (e1.real > e2.real) return true;
		else return false;
	}
	else return false;
}
bool compare2(Complex e1, Complex e2) {  // 降序
	if (e1.value < e2.value) return true;
	else if (e1.value == e2.value) {
		if (e1.real < e2.real) return true;
		else return false;
	}
	else return false;
}

int mysearch(Vector<Complex> A, double e, Rank lo, Rank hi) //有序向量区间查找
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
	cout << "第一部分" << endl;
	Complex pre;
	pre.init(1, 2);
	Vector<Complex> a(50, 6, pre);
	cout << "随机复数" << endl;
	for (int i = 0; i < a.size(); i++)
	{
		a[i].random();
		myprint(a[i]);
	}
	cout << endl;
	//删除
	cout << "删除" << endl;
	a.remove(2);
	for (int i = 0; i < a.size(); i++)
	{
		myprint(a[i]);
	}
	cout << endl;
	//插入相同复数
	cout << "插入" << endl;
	
	a.insert(a[0]);
	for (int i = 0; i < a.size(); i++)
	{
		myprint(a[i]);
	}
	cout << endl;
	//置乱
	cout << "置乱" << endl;
	a.unsort(0, a.size());
	for (int i = 0; i < a.size(); i++)
	{
		myprint(a[i]);
	}cout << endl;
	//查找
	cout << "查找" << endl;
	int result = a.find(a[2],0,a.size(),mycmp);
	cout << result;
	cout << endl;

	cout << "唯一前" << endl;
	for (int i = 0; i < a.size(); i++)
	{
		myprint(a[i]);
	}cout << endl;
	//唯一化
	cout << "唯一后" << endl;
	a.deduplicate(mycmp);
	for (int i = 0; i < a.size(); i++)
	{
		myprint(a[i]);
	}cout << endl;



	cout << "第二部分" << endl;
	Vector<Complex> b(a, 0, a.size());
	//排序是否可用
	//冒泡
	printf("冒泡排序前：\n");
	a.traverse(myprint); cout << endl;
	a.bubbleSort(0, a.size(), compare);
	printf("冒泡排序后：\n");
	a.traverse(myprint); cout << endl;

	//选择
	printf("归并排序前：\n");
	b.traverse(myprint); cout << endl;
	b.mergeSort(0, a.size(), compare);
	printf("归并排序后：\n");
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
	//乱序
	printf("乱序情况下：\n");
	start = clock();
	c.bubbleSort(0, c.size(), compare);
	end = clock();
	s = (double)(end - start) / 1000;
	cout << "冒泡排序：" << s << " ms" << endl;

	start = clock();
	d.mergeSort(0, d.size(), compare);
	end = clock();
	s = (double)(end - start) / 1000;
	cout << "归并排序：" << s << " ms" << endl;

	//顺序

	printf("顺序情况下：\n");
	start = clock();
	c.bubbleSort(0, c.size(), compare);
	end = clock();
	s = (double)(end - start) / 1000;
	cout << "冒泡排序：" << s << " ms" << endl;


	start = clock();
	d.mergeSort(0, d.size(), compare);
	end = clock();
	s = (double)(end - start) / 1000;
	cout << "归并排序：" << s << " ms" << endl;


	//逆序
	cout << "逆序" << endl;
	start = clock();
	c.bubbleSort(0, c.size(), compare2);
	end = clock();
	s = (double)(end - start) / 1000;
	cout << "冒泡排序：" << s << " ms" << endl;


	start = clock();
	d.mergeSort(0, d.size(), compare2);
	end = clock();
	s = (double)(end - start) / 1000;
	cout << "归并排序：" << s << " ms" << endl;

	cout << "第三部分" << endl;
	a.mergeSort(0, a.size(), compare);
	for (int i = 0; i < a.size(); i++)
	{
		myprint(a[i]);
	}cout << endl;


	int n1 = 2, n2 = 100;
	cout << "查询结果: " << endl;
	Vector<Complex>result_1 = partqurry(a, n1, n2);
	for (int i = 0; i < result_1.size(); i++)
	{
		myprint(result_1[i]);
	}
	
	cout << endl;

	return 0;
}