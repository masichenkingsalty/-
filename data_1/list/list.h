#include<iostream>
#define ListNodePosi(T) ListNode<T>*
typedef int Rank;

template <typename T>
struct ListNode	{
	
	T data;                                                   //������ 
	ListNodePosi(T) pred;                                     //ֱ��ǰ��ָ�� 
	ListNodePosi(T) succ;                                     //ֱ�Ӻ��ָ�� 
	
	ListNode() {}                                             //Ĭ�Ϲ��캯�� ���header��trailer�ڵ�Ĺ��� Ĭ��ΪNULL 
	ListNode(T e, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL):data(e), pred(s), succ(s) {}
	
	ListNodePosi(T) insertAsPred(const T &e);                 //�ڵ�ǰ�ڵ�ǰ�����½ڵ� 
	ListNodePosi(T) insertAsSucc(const T &e);                 //�ڵ�ǰ�ڵ������½ڵ� 
	
};



template <typename T> class List { //�б�ģ����

private:
   Rank _size; ListNodePosi(T) header, trailer; //��ģ��ͷ�ڱ���β�ڱ�

protected:
   void init(); //�б���ʱ�ĳ�ʼ��
   Rank clear(); //������нڵ�
   void copyNodes( ListNodePosi(T), Rank ); //�����б�����λ��p���n��
   ListNodePosi(T) merge( ListNodePosi(T), Rank, List<T>&, ListNodePosi(T), Rank ); //�鲢
   void mergeSort( ListNodePosi(T)&, Rank ); //�Դ�p��ʼ������n���ڵ�鲢����
   void selectionSort( ListNodePosi(T), Rank ); //�Դ�p��ʼ������n���ڵ�ѡ������
   void insertionSort( ListNodePosi(T), Rank ); //�Դ�p��ʼ������n���ڵ��������
   void radixSort( ListNodePosi(T), Rank ); //�Դ�p��ʼ������n���ڵ��������

public:
// ���캯��
   List() { init(); } //Ĭ��
   List( List<T> const& L ); //���帴���б�L
   List( List<T> const& L, Rank r, Rank n ); //�����б�L���Ե�r�����n��
   List( ListNodePosi(T) p, Rank n ); //�����б�����λ��p���n��
   // ��������
   ~List(); //�ͷţ�����ͷ��β�ڱ����ڵģ����нڵ�
// ֻ�����ʽӿ�
   Rank size() const { return _size; } //��ģ
   bool empty() const { return _size <= 0; } //�п�
   ListNodePosi(T) operator[]( Rank r ) const; //���أ�֧��ѭ�ȷ��ʣ�Ч�ʵͣ�
   ListNodePosi(T) first() const { return header->succ; } //�׽ڵ�λ��
   ListNodePosi(T) last() const { return trailer->pred; } //ĩ�ڵ�λ��
   bool valid( ListNodePosi(T) p ) //�ж�λ��p�Ƿ����Ϸ�
   { return p && ( trailer != p ) && ( header != p ); } //��ͷ��β�ڵ��ͬ��NULL
   ListNodePosi(T) find( T const& e ) const //�����б����
   { return find( e, _size, trailer ); }
   ListNodePosi(T) find( T const& e, Rank n, ListNodePosi(T) p ) const; //�����������
   ListNodePosi(T) search( T const& e ) const //�����б����
   { return search( e, _size, trailer ); }
   ListNodePosi(T) search( T const& e, Rank n, ListNodePosi(T) p ) const; //�����������
   ListNodePosi(T) selectMax( ListNodePosi(T) p, Rank n ); //��p����n-1�������ѡ�������
   ListNodePosi(T) selectMax() { return selectMax( header->succ, _size ); } //���������
// ��д���ʽӿ�
   ListNodePosi(T) insertAsFirst( T const& e ); //��e�����׽ڵ����
   ListNodePosi(T) insertAsLast( T const& e ); //��e����ĩ�ڵ����
   ListNodePosi(T) insert( ListNodePosi(T) p, T const& e ); //��e����p�ĺ�̲���
   ListNodePosi(T) insert( T const& e, ListNodePosi(T) p ); //��e����p��ǰ������
   T remove( ListNodePosi(T) p ); //ɾ���Ϸ�λ��p���Ľڵ�,���ر�ɾ���ڵ�
   void merge( List<T>& L ) { merge( header->succ, _size, L, L.header->succ, L._size ); } //ȫ�б�鲢
   void sort( ListNodePosi(T), Rank ); //�б���������
   void sort() { sort( first(), _size ); } //�б���������
   Rank deduplicate(); //����ȥ��
   Rank uniquify(); //����ȥ��
   void reverse(); //ǰ���ã�ϰ�⣩
// ����
   void traverse( void ( * )( T& ) ); //����ʵʩvisit����������ָ�룩
   template <typename VST> void traverse( VST& ); //����ʵʩvisit��������������
}; //List

template <typename T> void List<T>::init() { //�б��ʼ�����ڴ����б����ʱͳһ����
   header = new ListNode<T>; trailer = new ListNode<T>; //����ͷ��β�ڱ��ڵ�
   header->succ = trailer; header->pred = NULL; //��ǰ����
   trailer->pred = header; trailer->succ = NULL; //�������
   _size = 0; //��¼��ģ
}



template <typename T> ListNodePosi(T) List<T>::insertAsFirst( T const& e )
   { _size++; return header->insertAsSucc( e ); } // e�����׽ڵ����

template <typename T> ListNodePosi(T) List<T>::insertAsLast( T const& e )
   { _size++; return trailer->insertAsPred( e ); } // e����ĩ�ڵ����

template <typename T> ListNodePosi(T) List<T>::insert( ListNodePosi(T) p, T const& e )
   { _size++; return p->insertAsSucc( e ); } // e����p�ĺ�̲���

template <typename T> ListNodePosi(T) List<T>::insert( T const& e, ListNodePosi(T) p )
   { _size++; return p->insertAsPred( e ); } // e����p��ǰ������


template <typename T> T List<T>::remove( ListNodePosi(T) p ) { //ɾ���Ϸ��ڵ�p����������ֵ
   T e = p->data; //���ݴ�ɾ���ڵ����ֵ���ٶ�T���Ϳ�ֱ�Ӹ�ֵ��
   p->pred->succ = p->succ; p->succ->pred = p->pred; //��̡�ǰ��
   delete p; _size--; //�ͷŽڵ㣬���¹�ģ
   return e; //���ر��ݵ���ֵ
}


