#include<iostream>
#include<math.h>
#include<algorithm>
using namespace std;
typedef int Rank; //��
#define DEFAULT_CAPACITY  3 //Ĭ�ϵĳ�ʼ������ʵ��Ӧ���п�����Ϊ����

template <typename T> class Stack { //ջģ���� 
protected:
    Rank _size; Rank _capacity;  T* _elem; //��ģ��������������
    void copyFrom(T const* A, Rank lo, Rank hi) //������������A[lo, hi) A�Ѿ���һ����ַ���� 
    {
        _elem = new T[_capacity = 2 * (hi - lo)]; _size = 0;
        while (lo < hi)
            _elem[_size++] = A[lo++];
    }
    void expand() //�ռ䲻��ʱ����
    {
        if (_size < _capacity) return;
        if (_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;
        T* oldelem = _elem; _elem = new T[_capacity <<= 1];
        for (int i = 0; i < _size; i++)
            _elem[i] = oldelem[i];
        delete[] oldelem;
    }
    void shrink() //װ�����ӹ�Сʱѹ��
    {
        if (_capacity < DEFAULT_CAPACITY << 1) return;
        if (_size << 2 > _capacity) return;  // ��25%Ϊ���ޣ�
        T* oldelem = _elem; _elem = new T[_capacity >>= 1];
        for (int i = 0; i < _size; i++)
            _elem[i] = oldelem[i];
        delete[] oldelem;

    }
    
    Rank maxItem(Rank lo, Rank hi) //ѡȡ���Ԫ��
    {
        int max = _elem[0];
        for (int i = 1; i < _size; i++)
            if (_elem[i] > max) {
                max = _elem[i];
            }
        return max;
    }
public:
    // ���캯��
    Stack(Rank c = DEFAULT_CAPACITY, Rank s = 0, T v = 0) //����Ϊc����ģΪs������Ԫ�س�ʼΪ v
    {
        _elem = new T[_capacity = c]; for (_size = 0; _size < s; _elem[_size++] = v);
    } //s<=c
    
    Stack(T const* A, Rank n) { copyFrom(A, 0, n); } //�������帴�� 
    Stack(T const* A, Rank lo, Rank hi) { copyFrom(A, lo, hi); } //���� 
    Stack(Stack<T> const& V) { copyFrom(V._elem, 0, V._size); } //�������帴��  
    Stack(Stack<T> const& V, Rank lo, Rank hi) { copyFrom(V._elem, lo, hi); } //����  
 // ��������
    ~Stack() { delete[] _elem; } //�ͷ��ڲ��ռ�
 // ֻ�����ʽӿ�
    Rank size() const { return _size; } //��ģ  
    bool empty() const { return !_size; } //�п�  
    
    // ��д���ʽӿ�
    T& operator[] (Rank r)
    {
        //�����±������������������������ʽ���ø�Ԫ��
        return _elem[r];
    }
    //  const T& operator[] (Rank r) const; //����������ֵ�����ذ汾
    Stack<T>& operator= (Stack<T> const& V) //���ظ�ֵ���������Ա�ֱ�ӿ�¡����
    {
        if (_elem)
            delete[]_elem;
        copyFrom(V._elem, 0, V.size());
        return *this;
    }
    T remove(Rank r) //ɾ����Ϊr��Ԫ��
    {
        T e = _elem[r];
        remove(r, r + 1);
        return e;
    }
    Rank remove(Rank lo, Rank hi) //ɾ����������[lo, hi)֮�ڵ�Ԫ��
    {
        //����³���� 
        if (lo<0 || hi>_size) { printf("Խ��\n"); return 0; }
        if (lo == hi) return 0;
        while (hi < _size) _elem[lo++] = _elem[hi++];
        _size = lo;
        shrink();
        return hi - lo;
    }
    Rank insert(Rank r, T const& e) //����Ԫ��
    {
        // ����³���� 
        if (r > _size) { printf("Խ��\n"); return -1; }
        expand();
        for (int i = _size; i > r; i--)
            _elem[i] = _elem[i - 1];
        _elem[r] = e; _size++;
        return r;
    }
    Rank insert(T const& e) { return insert(_size, e); } //Ĭ����ΪĩԪ�ز���
    
    
    
    void push( T const& e) { insert ( size(), e );}
	T pop() { return remove(size() - 1); }
	T& top(){ return (*this) [size() - 1]; }
    
    
    
    
    
    
    // ����
    void traverse(void ( *visit ) ( T& )) //������ʹ�ú���ָ�룬ֻ����ֲ����޸ģ�
    {
        for (int i = 0; i < _size; i++) visit(_elem[i]);
    }
    template <typename VST> void traverse(VST& visit) //������ʹ�ú������󣬿�ȫ�����޸ģ�
    {
        for (int i = 0; i < _size; i++) visit(_elem[i]);
    }
}; //Stack

