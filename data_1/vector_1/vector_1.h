#include <iostream>
using namespace std;
#include<stdlib.h>


#define DEFAULT_CAPACITY  3 

typedef int Rank; //秩

template<typename T> class Vector { //向量模板类

protected:
    Rank _size; int _capacity; T* _elem; //规模、容量、数据区

    void copyFrom(T const* A, Rank lo, Rank hi); //复制数组区间[lo, hi)
    void expand(); //空间不足时扩容
    void shrink(); //装填因子过小时压缩
    bool bubble(Rank lo, Rank hi); //扫描交换
    
    Rank max(Rank lo, Rank hi); //选取最大元素
    
    void merge(Rank lo, Rank mi, Rank hi); //归并算法
    
    Rank partition(Rank lo, Rank hi); //轴点构造算法
    
   // void heapSort(Rank lo, Rank hi); //堆排序

public:
    //构造函数
    Vector(int c = 0, int s = 0, T v = 0) //容量为c、规模为s、所有元素初始为v
    {
        _elem = new T[_capacity = c]; for (_size = 0; _size < s; _elem[_size++] = v);
    } //s<=c
    Vector(T const* A, Rank n) { copyFrom(A, 0, n); } //数组整体复制
    Vector(T const* A, Rank lo, Rank hi) { copyFrom(A, lo, hi); } //区间
    Vector(Vector<T> const& V) { copyFrom(V._elem, 0, V._size); } //向量整体复制
    Vector(Vector<T> const& V, Rank lo, Rank hi) { copyFrom(V._elem, lo, hi); } //向量区间复制

    //析构函数
    ~Vector() { delete[] _elem; } //释放内部空间

    //只读访问接口
    Rank size() const { return _size; } //规模
    bool empty() const { return !_size; } //判空
    int disordered() const; //判断向量是否已排序
    Rank find(T const& e) const { return find(e, 0, _size); } //无序向量整体查找
    Rank find(T const& e, Rank lo, Rank hi) const; //无序向量区间查找
    Rank search(T const& e) const //有序向量整体查找
    {
        return (0 >= _size) ? -1 : search(e, 0, _size);
    }
    Rank search(T const& e, Rank lo, Rank hi) const; //有序向量区间查找
    //可写访问接口
    T& operator[] (Rank r) const; //重载下标操作符，可以类似于数组形式引用各元素
    Vector<T>& operator= (Vector<T> const&); //重载赋值操作符，以便直接克隆向量
    T remove(Rank r); //删除秩为r的元素
    int remove(Rank lo, Rank hi); //删除秩在区间[lo, hi)之内的元素
    Rank insert(Rank r, T const& e); //插入元素
    Rank insert(T const& e) { return insert(_size, e); } //默认作为末元素插入
    void sort(Rank lo, Rank hi); //对[lo, hi)排序
    void sort() { sort(0, _size); } //整体排序
    void unsort(Rank lo, Rank hi); //对[lo, hi)置乱
    void unsort() { unsort(0, _size); } //整体置乱
    int deduplicate(); //无序去重
    int uniquify(); //有序去重，返回被删除元素总数
    //遍历
    void quickSort(Rank lo, Rank hi); //快速排序算法
    void selectionSort(Rank lo, Rank hi); //选择排序算法
    void mergeSort(Rank lo, Rank hi); //归并排序算法
    void bubbleSort(Rank lo, Rank hi); //起泡排序算法
    void traverse(void (*visit) (T&)); //遍历（使用函数指针，只读或局部性修改）
    template <typename VST> void traverse(VST&); //遍历（使用函数对象，可全局性修改）

}; //Vector





// 澶嶅埗鏁扮粍鍖洪棿[lo, hi)
template <typename T>
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi) {
	// 鍒嗛厤绌洪棿骞跺鍒舵暣涓暟缁凙
	_elem = new T[_capacity = 2 * (hi - lo)];
	_size = 0; // 鍒濆瑙勬ā涓�0
	while (lo < hi) { // A[lo, hi)鍐呯殑鍏冪礌閫愪竴澶嶅埗鍒癬elem[0, hi-lo)
		_elem[_size++] = A[lo++];
	}
}

// 鎵╁
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

// 鍘嬬缉
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

// 鎵弿浜ゆ崲娉曞啋娉℃帓搴�
template <typename T>
bool Vector<T>::bubble(Rank lo, Rank hi) {
	bool sorted = true; // 鍒ゆ柇鏄惁宸叉湁搴�
	while (++lo < hi) {
		if (_elem[lo - 1] > _elem[lo]) { // 鑻ラ�嗗簭瀛樺湪
			sorted = false;
			swap(_elem[lo - 1], _elem[lo]);
		}
	}
	return sorted;
}

// 璧锋场鎺掑簭绠楁硶
template <typename T>
void Vector<T>::bubbleSort(Rank lo, Rank hi) {
	while (!bubble(lo, hi--)); // 鑷冲皯闇�瑕佹墽琛屼竴娆�
}

// 閫夊彇鏈�澶у厓绱�
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

// 閫夋嫨鎺掑簭绠楁硶
template <typename T>
void Vector<T>::selectionSort(Rank lo, Rank hi) {
	while (lo < --hi) {
		swap(_elem[max(lo, hi)], _elem[hi]); // 灏嗘渶澶у厓绱犱氦鎹㈠埌鏈熬
	}
}

// 褰掑苟绠楁硶
template <typename T>
void Vector<T>::merge(Rank lo, Rank mi, Rank hi) {
	T* A = _elem + lo; // 瀛愬悜閲廇[0, mi - lo) = _elem[lo, mi)
	int lb = mi - lo; // A鐨勯暱搴�
	T* B = new T[lb]; // 澶嶅埗宸﹀崐閮ㄥ垎
	for (Rank i = 0; i < lb; ++i) {
		B[i] = A[i];
	}
	int lc = hi - mi; // l盲ngd B
	T* C = _elem + mi; // 鎸囧悜鍙冲崐閮ㄥ垎C = _elem[mi, hi)
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

// 褰掑苟鎺掑簭绠楁硶锛堣凯浠ｇ増锛�
template <typename T>
void Vector<T>::mergeSort(Rank lo, Rank hi) {
	if (hi - lo < 2) return; // 骞冲嚒鎯呭喌
	Rank mi = (lo + hi) >> 1; // 鍒嗚
	mergeSort(lo, mi); // 閫掑綊宸﹀崐杈�
	mergeSort(mi, hi); // 閫掑綊鍙冲崐杈�
	merge(lo, mi, hi); // 褰掑苟
}

// 杞寸偣鏋勯�犵畻娉�
template <typename T>
Rank Vector<T>::partition(Rank lo, Rank hi) {
	swap(_elem[lo], _elem[lo + rand() % (hi - lo + 1)]); // 闅忔満閫夊彇杞寸偣骞朵氦鎹㈣嚦lo
	T pivot = _elem[lo]; // 澶囦唤杞寸偣鍏冪礌
	while (lo < hi) {
		while ((lo < hi) && (pivot <= _elem[hi])) {
			--hi;
		}
		_elem[lo] = _elem[hi]; // 灏唄i鍏冪礌褰掑叆宸︿晶
		while ((lo < hi) && (_elem[lo] <= pivot)) {
			++lo;
		}
		_elem[hi] = _elem[lo]; // 灏唋o鍏冪礌褰掑叆鍙充晶
	}
	_elem[lo] = pivot; // 褰掍綅杞寸偣鍏冪礌
	return lo; // 杩斿洖杞寸偣绉�
}

// 蹇�熸帓搴忕畻娉�
template <typename T>
void Vector<T>::quickSort(Rank lo, Rank hi) {
	if (hi - lo < 2) return; // 鍩烘湰鎯呭喌
	Rank mi = partition(lo, hi - 1); // 鏋勯�犺酱鐐�
	quickSort(lo, mi); // 瀵瑰乏鍗婅竟鎺掑簭
	quickSort(mi + 1, hi); // 瀵瑰彸鍗婅竟鎺掑簭
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

// 鏌ユ壘鍏冪礌e鍦ㄦ棤搴忓悜閲忓唴鐨勭З
template <typename T>
Rank Vector<T>::find(T const& e, Rank lo, Rank hi) const {
	while ((lo < hi--) && (_elem[hi] != e)); // 浠庡悗寰�鍓嶉『搴忔煡鎵�
	return hi; // 鑻i < lo锛屽垯鎰忓懗鐫�澶辫触锛涘惁鍒檋i鍗冲懡涓厓绱犵殑绉�
}

//鏈夊簭鍚戦噺鍖洪棿鏌ユ壘
template<typename T>
Rank Vector<T>::search(T const& e, Rank lo, Rank hi) const {
	return (rand() % 2) ?
		binSearch(_elem, e, lo, hi) :
		fibSearch(_elem, e, lo, hi);
}

// 閲嶈浇涓嬫爣鎿嶄綔绗�
template <typename T>
T& Vector<T>::operator[] (Rank r) const {
	return _elem[r];
}

// 閲嶈浇璧嬪�兼搷浣滅
template <typename T>
Vector<T>& Vector<T>::operator= (Vector<T> const& V) {
	if (_elem) delete[] _elem; // 閲婃斁鍘熸湁鍐呭
	copyFrom(V._elem, 0, V._size); // 澶嶅埗
	return *this;
}

// 鍒犻櫎绉╀负r鐨勫厓绱�
template <typename T>
T Vector<T>::remove(Rank r) {
	T e = _elem[r]; // 澶囦唤琚垹闄ゅ厓绱�
	remove(r, r + 1); // 璋冪敤鍖洪棿鍒犻櫎绠楁硶鍒犻櫎鍗曞厓绱犲尯闂碵r, r+1)锛屽叿浣撳疄鐜拌涓嬮潰
	return e; // 杩斿洖琚垹闄ゅ厓绱�
}

// 鍒犻櫎绉╁湪鍖洪棿[lo, hi)涔嬪唴鐨勫厓绱�
template <typename T>
int Vector<T>::remove(Rank lo, Rank hi) {
	if (lo == hi) return 0; // 绌哄尯闂翠笉闇�瑕佸垹闄�
	while (hi < _size) { // 灏哰_hi, _size)鍐呯殑鍏冪礌渚濇鍓嶇Щ
		_elem[lo++] = _elem[hi++];
	}
	_size = lo; // 鏇存柊瑙勬ā锛岀洿鎺ヨ垗鍘诲熬閮╗lo, _size - (hi - lo)) = [lo, hi)
	shrink(); // 鑻ヨ妯¤繃灏忥紝鍒欏帇缂╃┖闂�
	return hi - lo; // 杩斿洖琚垹闄ゅ厓绱犳�绘暟
}

// 鎻掑叆鍏冪礌
template <typename T>
Rank Vector<T>::insert(Rank r, T const& e) {
	expand(); // 鑻ラ渶鎵╁锛屽垯鎵╁
	for (int i = _size; i > r; --i) { // 鑷悗鍚戝墠锛屽悗缁у厓绱犻『娆″悗绉讳竴涓崟鍏�
		_elem[i] = _elem[i - 1];
	}
	_elem[r] = e; // 鎻掑叆鏂板厓绱�
	++_size; // 鏇存柊瑙勬ā
	return r; // 杩斿洖绉�
}

// 瀵筟lo, hi)鎺掑簭
template <typename T>
void Vector<T>::sort(Rank lo, Rank hi) {
	switch (rand() % 5) { // 闅忔満閫夊彇鎺掑簭绠楁硶
	case 1: bubbleSort(lo, hi); break;
	case 2: selectionSort(lo, hi); break;
	case 3: mergeSort(lo, hi); break;
	case 4: quickSort(lo, hi); break;
	//default: heapSort(lo, hi); break;
	}
}
//瀵筟lo, hi)缃贡
template<typename T>
void Vector<T>::unsort(Rank lo, Rank hi) {
	T* V = _elem + lo;
	for (Rank i = hi - lo; i > 0; i--) {
		swap(V[i - 1], V[rand() % i]);
	}
}
// 鏃犲簭鍘婚噸
template <typename T>
int Vector<T>::deduplicate() {
	int oldSize = _size; // 璁板綍鍘熸湁瑙勬ā
	Rank i = 1; // 浠巁elem[1]寮�濮嬩緷娆¤�冨療鍚勫厓绱燺e[i]
	while (i < _size) { // 鑷墠鍚戝悗鎵弿鍏朵綑鍏冪礌
		(find(_elem[i], 0, i) < 0) ? // 鍦ㄥ叾鍓嶇紑涓鎵句笌涔嬮浄鍚岃�咃紙鑷冲涓�涓級
			++i : remove(i); // 鑻ユ棤锛屽垯缁х画鑰冨療鍚庣户锛涘惁鍒欏垹闄ら浄鍚岃��
	}
	return oldSize - _size; // 杩斿洖琚垹闄ゅ厓绱犳�绘暟
}

// 鏈夊簭鍘婚噸
template <typename T>
int Vector<T>::uniquify() {
	int oldSize = _size; // 璁板綍鍘熸湁瑙勬ā
	Rank i = 1; // 浠巁elem[1]寮�濮嬩緷娆℃壂鎻忓悇鍏冪礌_e[i]
	while (i < _size) { // 鑷墠鍚戝悗鑰冨療锛岀洿鑷虫湯鍏冪礌
		(_elem[i - 1] == _elem[i]) ? // 鑻ュ彂鐜伴噸澶嶏紝鍒犻櫎鍚庤��
			remove(i) : // 涓嬫爣i瀵瑰簲鐨勫厓绱犺鍒犻櫎锛屽悗缁у厓绱犺嚜鍔ㄥ墠绉�
			++i;
	}
	return oldSize - _size; // 杩斿洖琚垹闄ゅ厓绱犳�绘暟
}

//閬嶅巻锛堜娇鐢ㄥ嚱鏁版寚閽堬紝鍙鎴栧眬閮ㄦ�т慨鏀癸級
template<typename T>
void Vector<T>::traverse(void (*visit) (T&)) {
	for (int i = 0; i < _size; i++) {
		visit(_elem[i]);
	}
}

// 閬嶅巻锛堜娇鐢ㄥ嚱鏁板璞★紝鍙叏灞�鎬т慨鏀癸級
template <typename T> template <typename VST>
void Vector<T>::traverse(VST& visit) {
	for (int i = 0; i < _size; ++i) {
		visit(_elem[i]);
	}
}

