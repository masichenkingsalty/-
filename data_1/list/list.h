#include<iostream>
#define ListNodePosi(T) ListNode<T>*
typedef int Rank;

template <typename T>
struct ListNode	{
	
	T data;                                                   //数据域 
	ListNodePosi(T) pred;                                     //直接前驱指针 
	ListNodePosi(T) succ;                                     //直接后继指针 
	
	ListNode() {}                                             //默认构造函数 针对header和trailer节点的构造 默认为NULL 
	ListNode(T e, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL):data(e), pred(s), succ(s) {}
	
	ListNodePosi(T) insertAsPred(const T &e);                 //在当前节点前插入新节点 
	ListNodePosi(T) insertAsSucc(const T &e);                 //在当前节点后插入新节点 
	
};



template <typename T> class List { //列表模板类

private:
   Rank _size; ListNodePosi(T) header, trailer; //规模、头哨兵、尾哨兵

protected:
   void init(); //列表创建时的初始化
   Rank clear(); //清除所有节点
   void copyNodes( ListNodePosi(T), Rank ); //复制列表中自位置p起的n项
   ListNodePosi(T) merge( ListNodePosi(T), Rank, List<T>&, ListNodePosi(T), Rank ); //归并
   void mergeSort( ListNodePosi(T)&, Rank ); //对从p开始连续的n个节点归并排序
   void selectionSort( ListNodePosi(T), Rank ); //对从p开始连续的n个节点选择排序
   void insertionSort( ListNodePosi(T), Rank ); //对从p开始连续的n个节点插入排序
   void radixSort( ListNodePosi(T), Rank ); //对从p开始连续的n个节点基数排序

public:
// 构造函数
   List() { init(); } //默认
   List( List<T> const& L ); //整体复制列表L
   List( List<T> const& L, Rank r, Rank n ); //复制列表L中自第r项起的n项
   List( ListNodePosi(T) p, Rank n ); //复制列表中自位置p起的n项
   // 析构函数
   ~List(); //释放（包含头、尾哨兵在内的）所有节点
// 只读访问接口
   Rank size() const { return _size; } //规模
   bool empty() const { return _size <= 0; } //判空
   ListNodePosi(T) operator[]( Rank r ) const; //重载，支持循秩访问（效率低）
   ListNodePosi(T) first() const { return header->succ; } //首节点位置
   ListNodePosi(T) last() const { return trailer->pred; } //末节点位置
   bool valid( ListNodePosi(T) p ) //判断位置p是否对外合法
   { return p && ( trailer != p ) && ( header != p ); } //将头、尾节点等同于NULL
   ListNodePosi(T) find( T const& e ) const //无序列表查找
   { return find( e, _size, trailer ); }
   ListNodePosi(T) find( T const& e, Rank n, ListNodePosi(T) p ) const; //无序区间查找
   ListNodePosi(T) search( T const& e ) const //有序列表查找
   { return search( e, _size, trailer ); }
   ListNodePosi(T) search( T const& e, Rank n, ListNodePosi(T) p ) const; //有序区间查找
   ListNodePosi(T) selectMax( ListNodePosi(T) p, Rank n ); //在p及其n-1个后继中选出最大者
   ListNodePosi(T) selectMax() { return selectMax( header->succ, _size ); } //整体最大者
// 可写访问接口
   ListNodePosi(T) insertAsFirst( T const& e ); //将e当作首节点插入
   ListNodePosi(T) insertAsLast( T const& e ); //将e当作末节点插入
   ListNodePosi(T) insert( ListNodePosi(T) p, T const& e ); //将e当作p的后继插入
   ListNodePosi(T) insert( T const& e, ListNodePosi(T) p ); //将e当作p的前驱插入
   T remove( ListNodePosi(T) p ); //删除合法位置p处的节点,返回被删除节点
   void merge( List<T>& L ) { merge( header->succ, _size, L, L.header->succ, L._size ); } //全列表归并
   void sort( ListNodePosi(T), Rank ); //列表区间排序
   void sort() { sort( first(), _size ); } //列表整体排序
   Rank deduplicate(); //无序去重
   Rank uniquify(); //有序去重
   void reverse(); //前后倒置（习题）
// 遍历
   void traverse( void ( * )( T& ) ); //依次实施visit操作（函数指针）
   template <typename VST> void traverse( VST& ); //依次实施visit操作（函数对象）
}; //List

template <typename T> void List<T>::init() { //列表初始化，在创建列表对象时统一调用
   header = new ListNode<T>; trailer = new ListNode<T>; //创建头、尾哨兵节点
   header->succ = trailer; header->pred = NULL; //向前链接
   trailer->pred = header; trailer->succ = NULL; //向后链接
   _size = 0; //记录规模
}



template <typename T> ListNodePosi(T) List<T>::insertAsFirst( T const& e )
   { _size++; return header->insertAsSucc( e ); } // e当作首节点插入

template <typename T> ListNodePosi(T) List<T>::insertAsLast( T const& e )
   { _size++; return trailer->insertAsPred( e ); } // e当作末节点插入

template <typename T> ListNodePosi(T) List<T>::insert( ListNodePosi(T) p, T const& e )
   { _size++; return p->insertAsSucc( e ); } // e当作p的后继插入

template <typename T> ListNodePosi(T) List<T>::insert( T const& e, ListNodePosi(T) p )
   { _size++; return p->insertAsPred( e ); } // e当作p的前驱插入


template <typename T> T List<T>::remove( ListNodePosi(T) p ) { //删除合法节点p，返回其数值
   T e = p->data; //备份待删除节点的数值（假定T类型可直接赋值）
   p->pred->succ = p->succ; p->succ->pred = p->pred; //后继、前驱
   delete p; _size--; //释放节点，更新规模
   return e; //返回备份的数值
}


