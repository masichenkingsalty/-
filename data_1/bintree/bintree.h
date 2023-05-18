#include"binnode.h"
#include"../queue/queue.h"
template <typename T> class BinTree { //������ģ����
protected:
   Rank _size; BinNodePosi(T) _root; //��ģ�����ڵ�
   virtual Rank updateHeight( BinNodePosi(T) x ); //���½ڵ�x�ĸ߶�
   void updateHeightAbove( BinNodePosi(T) x ); //���½ڵ�x�������ȵĸ߶�
public:
   BinTree() : _size( 0 ), _root( NULL ) {} //���캯��
   ~BinTree() { if ( 0 < _size ) remove( _root ); } //��������
   Rank size() const { return _size; } //��ģ
   bool empty() const { return !_root; } //�п�
   BinNodePosi(T) root() const { return _root; } //����
   BinNodePosi(T) insert( T const& ); //������ڵ�
   BinNodePosi(T) insert( T const&, BinNodePosi(T) ); //��������
   BinNodePosi(T) insert( BinNodePosi(T), T const& ); //�����Һ���
   BinNodePosi(T) attach( BinTree<T>*&, BinNodePosi(T) ); //����������
   BinNodePosi(T) attach( BinNodePosi(T), BinTree<T>*& ); //����������
   Rank remove ( BinNodePosi(T) ); //����ɾ��
   BinTree<T>* secede ( BinNodePosi(T) ); //��������
   template <typename VST> //������
   void travLevel( VST& visit ) { if ( _root ) _root->travLevel( visit ); } //��α���
   template <typename VST> //������
   void travPre( VST& visit ) { if ( _root ) _root->travPre( visit ); } //�������
   template <typename VST> //������
   void travIn( VST& visit ) { if ( _root ) _root->travIn( visit ); } //�������
   template <typename VST> //������
   void travPost( VST& visit ) { if ( _root ) _root->travPost( visit ); } //�������
   bool operator<( BinTree<T> const& t ) //�Ƚ������������в��䣩
      { return _root && t._root && lt( _root, t._root ); }
   bool operator==( BinTree<T> const& t ) //�е���
      { return _root && t._root && ( _root == t._root ); }
}; //BinTree



template <typename T> Rank BinTree<T>::updateHeight( BinNodePosi(T) x ) //���½ڵ�x�߶�
   { return x->height = 1 + max( stature( x->lc ), stature( x->rc ) ); } //���������������

template <typename T> void BinTree<T>::updateHeightAbove( BinNodePosi(T) x ) //���¸߶�
   { while ( x ) { updateHeight( x ); x = x->parent; } } //��x�����������������ȡ����Ż�



template <typename T> BinNodePosi(T) BinTree<T>::insert( T const& e )
   { _size = 1; return _root = new BinNode<T>( e ); } //��e�������ڵ����յĶ�����

template <typename T> BinNodePosi(T) BinTree<T>::insert( T const& e, BinNodePosi(T) x )
   { _size++; x->insertAsLC( e ); updateHeightAbove( x ); return x->lc; } // e����Ϊx������

template <typename T> BinNodePosi(T) BinTree<T>::insert( BinNodePosi(T) x, T const& e )
   { _size++; x->insertAsRC( e ); updateHeightAbove( x ); return x->rc; } // e����Ϊx���Һ���
   


template <typename T> //��S�����ڵ�x�������������������S�����ÿ�
BinNodePosi(T) BinTree<T>::attach( BinTree<T>*& S, BinNodePosi(T) x ) { // x->lc == NULL
   if ( x->lc = S->_root ) x->lc->parent = x; //����
   _size += S->_size; updateHeightAbove( x ); //����ȫ����ģ��x�������ȵĸ߶�
   S->_root = NULL; S->_size = 0; release( S ); S = NULL; return x; //�ͷ�ԭ�������ؽ���λ��
}

template <typename T> //��S�����ڵ�x�������������������S�����ÿ�
BinNodePosi(T) BinTree<T>::attach( BinNodePosi(T) x, BinTree<T>*& S ) { // x->rc == NULL
   if ( x->rc = S->_root ) x->rc->parent = x; //����
   _size += S->_size; updateHeightAbove( x ); //����ȫ����ģ��x�������ȵĸ߶�
   S->_root = NULL; S->_size = 0; release( S ); S = NULL; return x; //�ͷ�ԭ�������ؽ���λ��
}

template <typename T> //ɾ����������λ��x���Ľڵ㼰���������ر�ɾ���ڵ����ֵ
Rank BinTree<T>::remove( BinNodePosi(T) x ) { // assert: xΪ�������еĺϷ�λ��
   FromParentTo( *x ) = NULL; //�ж����Ը��ڵ��ָ��
   updateHeightAbove( x->parent ); //�������ȸ߶�
   Rank n = removeAt( x ); _size -= n; return n; //ɾ������x�����¹�ģ������ɾ���ڵ�����
}
template <typename T> //ɾ����������λ��x���Ľڵ㼰���������ر�ɾ���ڵ����ֵ
static Rank removeAt( BinNodePosi(T) x ) { // assert: xΪ�������еĺϷ�λ��
   if ( !x ) return 0; //�ݹ��������
   Rank n = 1 + removeAt( x->lc ) + removeAt( x->rc ); //�ݹ��ͷ���������
   release( x->data ); release( x ); return n; //�ͷű�ժ���ڵ㣬������ɾ���ڵ�����
} // release()�����ͷŸ��ӽṹ�����㷨��ֱ�ӹ�ϵ������ʵ����������



template <typename T> //���������������㷨��������x�ӵ�ǰ����ժ���������װΪһ�ö�����������
BinTree<T>* BinTree<T>::secede( BinNodePosi(T) x ) { // assert: xΪ�������еĺϷ�λ��
   FromParentTo( *x ) = NULL; //�ж����Ը��ڵ��ָ��
   updateHeightAbove( x->parent ); //����ԭ�����������ȵĸ߶�
   BinTree<T>* S = new BinTree<T>; S->_root = x; x->parent = NULL; //������xΪ��
   S->_size = x->size(); _size -= S->_size; return S; //���¹�ģ�����ط������������
}


template <typename T, typename VST> //Ԫ�����͡�������
void travPre( BinNodePosi(T) x, VST& visit ) { //��������������㷨���ݹ�棩
   if ( !x ) return;
   visit( x->data );
   travPre_R( x->lc, visit );
   travPre_R( x->rc, visit );
}


template <typename T, typename VST> //Ԫ�����͡�������
void travPost( BinNodePosi(T) x, VST& visit ) { //��������������㷨���ݹ�棩
   if ( !x ) return;
   visit( x->data );
   travPre_R( x->lc, visit );
   travPre_R( x->rc, visit );
}


template <typename T, typename VST> //Ԫ�����͡�������
void travin ( BinNodePosi(T) x, VST& visit ) { //��������������㷨���ݹ�棩
   if ( !x ) return;
   travIn_R ( x->lc, visit );
   visit ( x->data );
   travIn_R ( x->rc, visit );
}


template <typename T> template <typename VST> //Ԫ�����͡�������
void BinNode <T>::travLevel( VST& visit ) { //��������α����㷨
	Queue<BinNodePosi(T)> Q;
	Q.enqueue(this);
	while(!Q.empty()){
		BinNodePosi(T) x=Q.dequeue(); visit(x->data);
		if (HasLChild(*x)) Q.enqueue (x->lc);
		if (HasLChild(*x)) Q.enqueue (x->rc);
	}
}



