#include<iostream>
#include<cstdlib>
#define BinNodePosi(T)BinNode<T>*//�ڵ�λ��
#define stature(p)((p)? (p)->height : -1)
typedef int Rank;
typedef enum { RB_RED, RB_BLACK} RBColor; //�ڵ���ɫ

//template <typename T> struct BinNode;
//template <typename T> using BinNodePosi = BinNode<T>*; //�ڵ�λ��

template <typename T> struct BinNode { //�������ڵ�ģ����
// ��Ա��Ϊ���������ͳһ���ţ����߿ɸ�����Ҫ��һ����װ��
   T data; //��ֵ
   BinNodePosi(T) parent, lc, rc; //���ڵ㼰���Һ���
   Rank height; //�߶ȣ�ͨ�ã�
   Rank npl; //Null Path Length����ʽ�ѣ�Ҳ��ֱ����height���棩
   RBColor color; //��ɫ���������
// ���캯��
   BinNode() : parent( NULL ), lc( NULL ), rc( NULL ), height( 0 ), npl( 1 ), color( RB_RED ) {}
   BinNode( T e, BinNodePosi(T) p = NULL, BinNodePosi(T) lc = NULL,
            BinNodePosi(T) rc = NULL, int h = 0, int l = 1, RBColor c = RB_RED )
      : data( e ), parent( p ), lc( lc ), rc( rc ), height( h ), npl( l ), color( c ) {}
// �����ӿ�
   Rank size(); //ͳ�Ƶ�ǰ�ڵ����������༴����Ϊ���������Ĺ�ģ
   BinNodePosi(T) insertAsLC( T const& ); //��Ϊ��ǰ�ڵ�����Ӳ����½ڵ�
   BinNodePosi(T) insertAsRC( T const& ); //��Ϊ��ǰ�ڵ���Һ��Ӳ����½ڵ�
   BinNodePosi(T) succ(); //ȡ��ǰ�ڵ��ֱ�Ӻ��
   template <typename VST> void travLevel( VST& ); //������α���
   template <typename VST> void travPre( VST& ); //�����������
   template <typename VST> void travIn( VST& ); //�����������
   template <typename VST> void travPost( VST& ); //�����������
// �Ƚ������е�����������һ���������в��䣩
   bool operator< ( BinNode const& bn ) { return data < bn.data; } //С��
   bool operator== ( BinNode const& bn ) { return data == bn.data; } //����
};


template <typename T> BinNodePosi(T)BinNode<T>::insertAsLC( T const& e )
   { return lc = new BinNode( e, this ); } //��e��Ϊ��ǰ�ڵ�����Ӳ��������


template <typename T> BinNodePosi(T) BinNode<T>::insertAsRC( T const& e )
   { return rc = new BinNode( e, this ); }


template <typename T> template <typename VST> //Ԫ�����͡�������
void BinNode<T>::travIn ( VST& visit ) { //��������������㷨ͳһ���
   switch ( rand() % 5 ) { //�˴������ѡ���������ԣ�������ѡ��
      case 1 : travIn_I1( this, visit ); break; //������#1
      case 2 : travIn_I2( this, visit ); break; //������#2
      case 3 : travIn_I3( this, visit ); break; //������#3
      case 4 : travIn_I4( this, visit ); break; //������#4
      default : travIn_R( this, visit ); break; //�ݹ��
   }
}

