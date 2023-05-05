#include"../list/list.h"

template <typename T> class Queue : public List<T> {
    public:
        void enqueue(T const& e){
            this->insertAsLast(e);
        }//入队 尾部插入 
        T dequeue(){
            return this->remove(this->first());
        }//出队 首部删除 
        T& front(){
            return this->first()->data;
        }//队首 
};

