#include"../list/list.h"

template <typename T> class Queue : public List<T> {
    public:
        void enqueue(T const& e){
            this->insertAsLast(e);
        }//��� β������ 
        T dequeue(){
            return this->remove(this->first());
        }//���� �ײ�ɾ�� 
        T& front(){
            return this->first()->data;
        }//���� 
};

