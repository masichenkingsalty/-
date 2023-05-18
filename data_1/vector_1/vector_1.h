#include <iostream>
using namespace std;
#include<stdlib.h>


#define DEFAULT_CAPACITY  3 

typedef int Rank; //��

template<typename T> class Vector { //����ģ����

protected:
    Rank _size; int _capacity; T* _elem; //��ģ��������������

    void copyFrom(T const* A, Rank lo, Rank hi); //������������[lo, hi)
    void expand(); //�ռ䲻��ʱ����
    void shrink(); //װ�����ӹ�Сʱѹ��
    bool bubble(Rank lo, Rank hi); //ɨ�轻��
    
    Rank max(Rank lo, Rank hi); //ѡȡ���Ԫ��
    
    void merge(Rank lo, Rank mi, Rank hi); //�鲢�㷨
    
    Rank partition(Rank lo, Rank hi); //��㹹���㷨
    
   // void heapSort(Rank lo, Rank hi); //������

public:
    //���캯��
    Vector(int c = 0, int s = 0, T v = 0) //����Ϊc����ģΪs������Ԫ�س�ʼΪv
    {
        _elem = new T[_capacity = c]; for (_size = 0; _size < s; _elem[_size++] = v);
    } //s<=c
    Vector(T const* A, Rank n) { copyFrom(A, 0, n); } //�������帴��
    Vector(T const* A, Rank lo, Rank hi) { copyFrom(A, lo, hi); } //����
    Vector(Vector<T> const& V) { copyFrom(V._elem, 0, V._size); } //�������帴��
    Vector(Vector<T> const& V, Rank lo, Rank hi) { copyFrom(V._elem, lo, hi); } //�������临��

    //��������
    ~Vector() { delete[] _elem; } //�ͷ��ڲ��ռ�

    //ֻ�����ʽӿ�
    Rank size() const { return _size; } //��ģ
    bool empty() const { return !_size; } //�п�
    int disordered() const; //�ж������Ƿ�������
    Rank find(T const& e) const { return find(e, 0, _size); } //���������������
    Rank find(T const& e, Rank lo, Rank hi) const; //���������������
    Rank search(T const& e) const //���������������
    {
        return (0 >= _size) ? -1 : search(e, 0, _size);
    }
    Rank search(T const& e, Rank lo, Rank hi) const; //���������������
    //��д���ʽӿ�
    T& operator[] (Rank r) const; //�����±������������������������ʽ���ø�Ԫ��
    Vector<T>& operator= (Vector<T> const&); //���ظ�ֵ���������Ա�ֱ�ӿ�¡����
    T remove(Rank r); //ɾ����Ϊr��Ԫ��
    int remove(Rank lo, Rank hi); //ɾ����������[lo, hi)֮�ڵ�Ԫ��
    Rank insert(Rank r, T const& e); //����Ԫ��
    Rank insert(T const& e) { return insert(_size, e); } //Ĭ����ΪĩԪ�ز���
    void sort(Rank lo, Rank hi); //��[lo, hi)����
    void sort() { sort(0, _size); } //��������
    void unsort(Rank lo, Rank hi); //��[lo, hi)����
    void unsort() { unsort(0, _size); } //��������
    int deduplicate(); //����ȥ��
    int uniquify(); //����ȥ�أ����ر�ɾ��Ԫ������
    //����
    void quickSort(Rank lo, Rank hi); //���������㷨
    void selectionSort(Rank lo, Rank hi); //ѡ�������㷨
    void mergeSort(Rank lo, Rank hi); //�鲢�����㷨
    void bubbleSort(Rank lo, Rank hi); //���������㷨
    void traverse(void (*visit) (T&)); //������ʹ�ú���ָ�룬ֻ����ֲ����޸ģ�
    template <typename VST> void traverse(VST&); //������ʹ�ú������󣬿�ȫ�����޸ģ�

}; //Vector





// 复制数组区间[lo, hi)
template <typename T>
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi) {
	// 分配空间并复制整个数组A
	_elem = new T[_capacity = 2 * (hi - lo)];
	_size = 0; // 初始规模为0
	while (lo < hi) { // A[lo, hi)内的元素逐一复制到_elem[0, hi-lo)
		_elem[_size++] = A[lo++];
	}
}

// 扩容
template <typename T>
void Vector<T>::expand() {
	if (_size < _capacity) return;
	if (_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;
	T* oldElem = _elem;
	_elem = new T[_capacity <<= 1];
	for (int i = 0; i < _size; ++i) {
		_elem[i] = oldElem[i];
	}
	delete[] oldElem;
}

// 压缩
template <typename T>
void Vector<T>::shrink() {
	if (_capacity < DEFAULT_CAPACITY << 1) return;
	if (_size << 2 > _capacity) return;
	T* oldElem = _elem;
	_elem = new T[_capacity >>= 1];
	for (int i = 0; i < _size; ++i) {
		_elem[i] = oldElem[i];
	}
	delete[] oldElem;
}

// 扫描交换法冒泡排序
template <typename T>
bool Vector<T>::bubble(Rank lo, Rank hi) {
	bool sorted = true; // 判断是否已有序
	while (++lo < hi) {
		if (_elem[lo - 1] > _elem[lo]) { // 若逆序存在
			sorted = false;
			swap(_elem[lo - 1], _elem[lo]);
		}
	}
	return sorted;
}

// 起泡排序算法
template <typename T>
void Vector<T>::bubbleSort(Rank lo, Rank hi) {
	while (!bubble(lo, hi--)); // 至少需要执行一次
}

// 选取最大元素
template <typename T>
Rank Vector<T>::max(Rank lo, Rank hi) {
	Rank maxIdx = hi - 1;
	while (lo < hi--) {
		if (_elem[maxIdx] < _elem[hi]) {
			maxIdx = hi;
		}
	}
	return maxIdx;
}

// 选择排序算法
template <typename T>
void Vector<T>::selectionSort(Rank lo, Rank hi) {
	while (lo < --hi) {
		swap(_elem[max(lo, hi)], _elem[hi]); // 将最大元素交换到末尾
	}
}

// 归并算法
template <typename T>
void Vector<T>::merge(Rank lo, Rank mi, Rank hi) {
	T* A = _elem + lo; // 子向量A[0, mi - lo) = _elem[lo, mi)
	int lb = mi - lo; // A的长度
	T* B = new T[lb]; // 复制左半部分
	for (Rank i = 0; i < lb; ++i) {
		B[i] = A[i];
	}
	int lc = hi - mi; // längd B
	T* C = _elem + mi; // 指向右半部分C = _elem[mi, hi)
	for (Rank i = 0, j = 0, k = 0; (j < lb) || (k < lc); ) {
		if ((j < lb) && (!(lc <= k) || (B[j] <= C[k]))) {
			A[i++] = B[j++];
		}
		if ((k < lc) && (!(lb <= j) || (C[k] < B[j]))) {
			A[i++] = C[k++];
		}
	}
	delete[] B;
}

// 归并排序算法（迭代版）
template <typename T>
void Vector<T>::mergeSort(Rank lo, Rank hi) {
	if (hi - lo < 2) return; // 平凡情况
	Rank mi = (lo + hi) >> 1; // 分裂
	mergeSort(lo, mi); // 递归左半边
	mergeSort(mi, hi); // 递归右半边
	merge(lo, mi, hi); // 归并
}

// 轴点构造算法
template <typename T>
Rank Vector<T>::partition(Rank lo, Rank hi) {
	swap(_elem[lo], _elem[lo + rand() % (hi - lo + 1)]); // 随机选取轴点并交换至lo
	T pivot = _elem[lo]; // 备份轴点元素
	while (lo < hi) {
		while ((lo < hi) && (pivot <= _elem[hi])) {
			--hi;
		}
		_elem[lo] = _elem[hi]; // 将hi元素归入左侧
		while ((lo < hi) && (_elem[lo] <= pivot)) {
			++lo;
		}
		_elem[hi] = _elem[lo]; // 将lo元素归入右侧
	}
	_elem[lo] = pivot; // 归位轴点元素
	return lo; // 返回轴点秩
}

// 快速排序算法
template <typename T>
void Vector<T>::quickSort(Rank lo, Rank hi) {
	if (hi - lo < 2) return; // 基本情况
	Rank mi = partition(lo, hi - 1); // 构造轴点
	quickSort(lo, mi); // 对左半边排序
	quickSort(mi + 1, hi); // 对右半边排序
}

template<typename T>
int Vector<T>::disordered() const {
	int count = 0;
	for (int i = 1; i < _size; i++) {
		if (_elem[i - 1] > _elem[i]) {
			count++;
		}
	}
	return count;
}

// 查找元素e在无序向量内的秩
template <typename T>
Rank Vector<T>::find(T const& e, Rank lo, Rank hi) const {
	while ((lo < hi--) && (_elem[hi] != e)); // 从后往前顺序查找
	return hi; // 若hi < lo，则意味着失败；否则hi即命中元素的秩
}

//有序向量区间查找
template<typename T>
Rank Vector<T>::search(T const& e, Rank lo, Rank hi) const {
	return (rand() % 2) ?
		binSearch(_elem, e, lo, hi) :
		fibSearch(_elem, e, lo, hi);
}

// 重载下标操作符
template <typename T>
T& Vector<T>::operator[] (Rank r) const {
	return _elem[r];
}

// 重载赋值操作符
template <typename T>
Vector<T>& Vector<T>::operator= (Vector<T> const& V) {
	if (_elem) delete[] _elem; // 释放原有内容
	copyFrom(V._elem, 0, V._size); // 复制
	return *this;
}

// 删除秩为r的元素
template <typename T>
T Vector<T>::remove(Rank r) {
	T e = _elem[r]; // 备份被删除元素
	remove(r, r + 1); // 调用区间删除算法删除单元素区间[r, r+1)，具体实现见下面
	return e; // 返回被删除元素
}

// 删除秩在区间[lo, hi)之内的元素
template <typename T>
int Vector<T>::remove(Rank lo, Rank hi) {
	if (lo == hi) return 0; // 空区间不需要删除
	while (hi < _size) { // 将[_hi, _size)内的元素依次前移
		_elem[lo++] = _elem[hi++];
	}
	_size = lo; // 更新规模，直接舍去尾部[lo, _size - (hi - lo)) = [lo, hi)
	shrink(); // 若规模过小，则压缩空间
	return hi - lo; // 返回被删除元素总数
}

// 插入元素
template <typename T>
Rank Vector<T>::insert(Rank r, T const& e) {
	expand(); // 若需扩容，则扩容
	for (int i = _size; i > r; --i) { // 自后向前，后继元素顺次后移一个单元
		_elem[i] = _elem[i - 1];
	}
	_elem[r] = e; // 插入新元素
	++_size; // 更新规模
	return r; // 返回秩
}

// 对[lo, hi)排序
template <typename T>
void Vector<T>::sort(Rank lo, Rank hi) {
	switch (rand() % 5) { // 随机选取排序算法
	case 1: bubbleSort(lo, hi); break;
	case 2: selectionSort(lo, hi); break;
	case 3: mergeSort(lo, hi); break;
	case 4: quickSort(lo, hi); break;
	//default: heapSort(lo, hi); break;
	}
}
//对[lo, hi)置乱
template<typename T>
void Vector<T>::unsort(Rank lo, Rank hi) {
	T* V = _elem + lo;
	for (Rank i = hi - lo; i > 0; i--) {
		swap(V[i - 1], V[rand() % i]);
	}
}
// 无序去重
template <typename T>
int Vector<T>::deduplicate() {
	int oldSize = _size; // 记录原有规模
	Rank i = 1; // 从_elem[1]开始依次考察各元素_e[i]
	while (i < _size) { // 自前向后扫描其余元素
		(find(_elem[i], 0, i) < 0) ? // 在其前缀中寻找与之雷同者（至多一个）
			++i : remove(i); // 若无，则继续考察后继；否则删除雷同者
	}
	return oldSize - _size; // 返回被删除元素总数
}

// 有序去重
template <typename T>
int Vector<T>::uniquify() {
	int oldSize = _size; // 记录原有规模
	Rank i = 1; // 从_elem[1]开始依次扫描各元素_e[i]
	while (i < _size) { // 自前向后考察，直至末元素
		(_elem[i - 1] == _elem[i]) ? // 若发现重复，删除后者
			remove(i) : // 下标i对应的元素被删除，后继元素自动前移
			++i;
	}
	return oldSize - _size; // 返回被删除元素总数
}

//遍历（使用函数指针，只读或局部性修改）
template<typename T>
void Vector<T>::traverse(void (*visit) (T&)) {
	for (int i = 0; i < _size; i++) {
		visit(_elem[i]);
	}
}

// 遍历（使用函数对象，可全局性修改）
template <typename T> template <typename VST>
void Vector<T>::traverse(VST& visit) {
	for (int i = 0; i < _size; ++i) {
		visit(_elem[i]);
	}
}

