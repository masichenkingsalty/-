#include <iostream>
using namespace std;
#include<stdlib.h>


#define DEFAULT_CAPACITY  3 

typedef int Rank; //ÖÈ

template<typename T> class Vector { //ÏòÁ¿Ä£°åÀà

protected:
    Rank _size; int _capacity; T* _elem; //¹æÄ£¡¢ÈİÁ¿¡¢Êı¾İÇø

    void copyFrom(T const* A, Rank lo, Rank hi); //¸´ÖÆÊı×éÇø¼ä[lo, hi)
    void expand(); //¿Õ¼ä²»×ãÊ±À©Èİ
    void shrink(); //×°ÌîÒò×Ó¹ıĞ¡Ê±Ñ¹Ëõ
    bool bubble(Rank lo, Rank hi); //É¨Ãè½»»»
    
    Rank max(Rank lo, Rank hi); //Ñ¡È¡×î´óÔªËØ
    
    void merge(Rank lo, Rank mi, Rank hi); //¹é²¢Ëã·¨
    
    Rank partition(Rank lo, Rank hi); //Öáµã¹¹ÔìËã·¨
    
   // void heapSort(Rank lo, Rank hi); //¶ÑÅÅĞò

public:
    //¹¹Ôìº¯Êı
    Vector(int c = 0, int s = 0, T v = 0) //ÈİÁ¿Îªc¡¢¹æÄ£Îªs¡¢ËùÓĞÔªËØ³õÊ¼Îªv
    {
        _elem = new T[_capacity = c]; for (_size = 0; _size < s; _elem[_size++] = v);
    } //s<=c
    Vector(T const* A, Rank n) { copyFrom(A, 0, n); } //Êı×éÕûÌå¸´ÖÆ
    Vector(T const* A, Rank lo, Rank hi) { copyFrom(A, lo, hi); } //Çø¼ä
    Vector(Vector<T> const& V) { copyFrom(V._elem, 0, V._size); } //ÏòÁ¿ÕûÌå¸´ÖÆ
    Vector(Vector<T> const& V, Rank lo, Rank hi) { copyFrom(V._elem, lo, hi); } //ÏòÁ¿Çø¼ä¸´ÖÆ

    //Îö¹¹º¯Êı
    ~Vector() { delete[] _elem; } //ÊÍ·ÅÄÚ²¿¿Õ¼ä

    //Ö»¶Á·ÃÎÊ½Ó¿Ú
    Rank size() const { return _size; } //¹æÄ£
    bool empty() const { return !_size; } //ÅĞ¿Õ
    int disordered() const; //ÅĞ¶ÏÏòÁ¿ÊÇ·ñÒÑÅÅĞò
    Rank find(T const& e) const { return find(e, 0, _size); } //ÎŞĞòÏòÁ¿ÕûÌå²éÕÒ
    Rank find(T const& e, Rank lo, Rank hi) const; //ÎŞĞòÏòÁ¿Çø¼ä²éÕÒ
    Rank search(T const& e) const //ÓĞĞòÏòÁ¿ÕûÌå²éÕÒ
    {
        return (0 >= _size) ? -1 : search(e, 0, _size);
    }
    Rank search(T const& e, Rank lo, Rank hi) const; //ÓĞĞòÏòÁ¿Çø¼ä²éÕÒ
    //¿ÉĞ´·ÃÎÊ½Ó¿Ú
    T& operator[] (Rank r) const; //ÖØÔØÏÂ±ê²Ù×÷·û£¬¿ÉÒÔÀàËÆÓÚÊı×éĞÎÊ½ÒıÓÃ¸÷ÔªËØ
    Vector<T>& operator= (Vector<T> const&); //ÖØÔØ¸³Öµ²Ù×÷·û£¬ÒÔ±ãÖ±½Ó¿ËÂ¡ÏòÁ¿
    T remove(Rank r); //É¾³ıÖÈÎªrµÄÔªËØ
    int remove(Rank lo, Rank hi); //É¾³ıÖÈÔÚÇø¼ä[lo, hi)Ö®ÄÚµÄÔªËØ
    Rank insert(Rank r, T const& e); //²åÈëÔªËØ
    Rank insert(T const& e) { return insert(_size, e); } //Ä¬ÈÏ×÷ÎªÄ©ÔªËØ²åÈë
    void sort(Rank lo, Rank hi); //¶Ô[lo, hi)ÅÅĞò
    void sort() { sort(0, _size); } //ÕûÌåÅÅĞò
    void unsort(Rank lo, Rank hi); //¶Ô[lo, hi)ÖÃÂÒ
    void unsort() { unsort(0, _size); } //ÕûÌåÖÃÂÒ
    int deduplicate(); //ÎŞĞòÈ¥ÖØ
    int uniquify(); //ÓĞĞòÈ¥ÖØ£¬·µ»Ø±»É¾³ıÔªËØ×ÜÊı
    //±éÀú
    void quickSort(Rank lo, Rank hi); //¿ìËÙÅÅĞòËã·¨
    void selectionSort(Rank lo, Rank hi); //Ñ¡ÔñÅÅĞòËã·¨
    void mergeSort(Rank lo, Rank hi); //¹é²¢ÅÅĞòËã·¨
    void bubbleSort(Rank lo, Rank hi); //ÆğÅİÅÅĞòËã·¨
    void traverse(void (*visit) (T&)); //±éÀú£¨Ê¹ÓÃº¯ÊıÖ¸Õë£¬Ö»¶Á»ò¾Ö²¿ĞÔĞŞ¸Ä£©
    template <typename VST> void traverse(VST&); //±éÀú£¨Ê¹ÓÃº¯Êı¶ÔÏó£¬¿ÉÈ«¾ÖĞÔĞŞ¸Ä£©

}; //Vector





// å¤åˆ¶æ•°ç»„åŒºé—´[lo, hi)
template <typename T>
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi) {
	// åˆ†é…ç©ºé—´å¹¶å¤åˆ¶æ•´ä¸ªæ•°ç»„A
	_elem = new T[_capacity = 2 * (hi - lo)];
	_size = 0; // åˆå§‹è§„æ¨¡ä¸º0
	while (lo < hi) { // A[lo, hi)å†…çš„å…ƒç´ é€ä¸€å¤åˆ¶åˆ°_elem[0, hi-lo)
		_elem[_size++] = A[lo++];
	}
}

// æ‰©å®¹
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

// å‹ç¼©
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

// æ‰«æäº¤æ¢æ³•å†’æ³¡æ’åº
template <typename T>
bool Vector<T>::bubble(Rank lo, Rank hi) {
	bool sorted = true; // åˆ¤æ–­æ˜¯å¦å·²æœ‰åº
	while (++lo < hi) {
		if (_elem[lo - 1] > _elem[lo]) { // è‹¥é€†åºå­˜åœ¨
			sorted = false;
			swap(_elem[lo - 1], _elem[lo]);
		}
	}
	return sorted;
}

// èµ·æ³¡æ’åºç®—æ³•
template <typename T>
void Vector<T>::bubbleSort(Rank lo, Rank hi) {
	while (!bubble(lo, hi--)); // è‡³å°‘éœ€è¦æ‰§è¡Œä¸€æ¬¡
}

// é€‰å–æœ€å¤§å…ƒç´ 
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

// é€‰æ‹©æ’åºç®—æ³•
template <typename T>
void Vector<T>::selectionSort(Rank lo, Rank hi) {
	while (lo < --hi) {
		swap(_elem[max(lo, hi)], _elem[hi]); // å°†æœ€å¤§å…ƒç´ äº¤æ¢åˆ°æœ«å°¾
	}
}

// å½’å¹¶ç®—æ³•
template <typename T>
void Vector<T>::merge(Rank lo, Rank mi, Rank hi) {
	T* A = _elem + lo; // å­å‘é‡A[0, mi - lo) = _elem[lo, mi)
	int lb = mi - lo; // Açš„é•¿åº¦
	T* B = new T[lb]; // å¤åˆ¶å·¦åŠéƒ¨åˆ†
	for (Rank i = 0; i < lb; ++i) {
		B[i] = A[i];
	}
	int lc = hi - mi; // lÃ¤ngd B
	T* C = _elem + mi; // æŒ‡å‘å³åŠéƒ¨åˆ†C = _elem[mi, hi)
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

// å½’å¹¶æ’åºç®—æ³•ï¼ˆè¿­ä»£ç‰ˆï¼‰
template <typename T>
void Vector<T>::mergeSort(Rank lo, Rank hi) {
	if (hi - lo < 2) return; // å¹³å‡¡æƒ…å†µ
	Rank mi = (lo + hi) >> 1; // åˆ†è£‚
	mergeSort(lo, mi); // é€’å½’å·¦åŠè¾¹
	mergeSort(mi, hi); // é€’å½’å³åŠè¾¹
	merge(lo, mi, hi); // å½’å¹¶
}

// è½´ç‚¹æ„é€ ç®—æ³•
template <typename T>
Rank Vector<T>::partition(Rank lo, Rank hi) {
	swap(_elem[lo], _elem[lo + rand() % (hi - lo + 1)]); // éšæœºé€‰å–è½´ç‚¹å¹¶äº¤æ¢è‡³lo
	T pivot = _elem[lo]; // å¤‡ä»½è½´ç‚¹å…ƒç´ 
	while (lo < hi) {
		while ((lo < hi) && (pivot <= _elem[hi])) {
			--hi;
		}
		_elem[lo] = _elem[hi]; // å°†hiå…ƒç´ å½’å…¥å·¦ä¾§
		while ((lo < hi) && (_elem[lo] <= pivot)) {
			++lo;
		}
		_elem[hi] = _elem[lo]; // å°†loå…ƒç´ å½’å…¥å³ä¾§
	}
	_elem[lo] = pivot; // å½’ä½è½´ç‚¹å…ƒç´ 
	return lo; // è¿”å›è½´ç‚¹ç§©
}

// å¿«é€Ÿæ’åºç®—æ³•
template <typename T>
void Vector<T>::quickSort(Rank lo, Rank hi) {
	if (hi - lo < 2) return; // åŸºæœ¬æƒ…å†µ
	Rank mi = partition(lo, hi - 1); // æ„é€ è½´ç‚¹
	quickSort(lo, mi); // å¯¹å·¦åŠè¾¹æ’åº
	quickSort(mi + 1, hi); // å¯¹å³åŠè¾¹æ’åº
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

// æŸ¥æ‰¾å…ƒç´ eåœ¨æ— åºå‘é‡å†…çš„ç§©
template <typename T>
Rank Vector<T>::find(T const& e, Rank lo, Rank hi) const {
	while ((lo < hi--) && (_elem[hi] != e)); // ä»åå¾€å‰é¡ºåºæŸ¥æ‰¾
	return hi; // è‹¥hi < loï¼Œåˆ™æ„å‘³ç€å¤±è´¥ï¼›å¦åˆ™hiå³å‘½ä¸­å…ƒç´ çš„ç§©
}

//æœ‰åºå‘é‡åŒºé—´æŸ¥æ‰¾
template<typename T>
Rank Vector<T>::search(T const& e, Rank lo, Rank hi) const {
	return (rand() % 2) ?
		binSearch(_elem, e, lo, hi) :
		fibSearch(_elem, e, lo, hi);
}

// é‡è½½ä¸‹æ ‡æ“ä½œç¬¦
template <typename T>
T& Vector<T>::operator[] (Rank r) const {
	return _elem[r];
}

// é‡è½½èµ‹å€¼æ“ä½œç¬¦
template <typename T>
Vector<T>& Vector<T>::operator= (Vector<T> const& V) {
	if (_elem) delete[] _elem; // é‡Šæ”¾åŸæœ‰å†…å®¹
	copyFrom(V._elem, 0, V._size); // å¤åˆ¶
	return *this;
}

// åˆ é™¤ç§©ä¸ºrçš„å…ƒç´ 
template <typename T>
T Vector<T>::remove(Rank r) {
	T e = _elem[r]; // å¤‡ä»½è¢«åˆ é™¤å…ƒç´ 
	remove(r, r + 1); // è°ƒç”¨åŒºé—´åˆ é™¤ç®—æ³•åˆ é™¤å•å…ƒç´ åŒºé—´[r, r+1)ï¼Œå…·ä½“å®ç°è§ä¸‹é¢
	return e; // è¿”å›è¢«åˆ é™¤å…ƒç´ 
}

// åˆ é™¤ç§©åœ¨åŒºé—´[lo, hi)ä¹‹å†…çš„å…ƒç´ 
template <typename T>
int Vector<T>::remove(Rank lo, Rank hi) {
	if (lo == hi) return 0; // ç©ºåŒºé—´ä¸éœ€è¦åˆ é™¤
	while (hi < _size) { // å°†[_hi, _size)å†…çš„å…ƒç´ ä¾æ¬¡å‰ç§»
		_elem[lo++] = _elem[hi++];
	}
	_size = lo; // æ›´æ–°è§„æ¨¡ï¼Œç›´æ¥èˆå»å°¾éƒ¨[lo, _size - (hi - lo)) = [lo, hi)
	shrink(); // è‹¥è§„æ¨¡è¿‡å°ï¼Œåˆ™å‹ç¼©ç©ºé—´
	return hi - lo; // è¿”å›è¢«åˆ é™¤å…ƒç´ æ€»æ•°
}

// æ’å…¥å…ƒç´ 
template <typename T>
Rank Vector<T>::insert(Rank r, T const& e) {
	expand(); // è‹¥éœ€æ‰©å®¹ï¼Œåˆ™æ‰©å®¹
	for (int i = _size; i > r; --i) { // è‡ªåå‘å‰ï¼Œåç»§å…ƒç´ é¡ºæ¬¡åç§»ä¸€ä¸ªå•å…ƒ
		_elem[i] = _elem[i - 1];
	}
	_elem[r] = e; // æ’å…¥æ–°å…ƒç´ 
	++_size; // æ›´æ–°è§„æ¨¡
	return r; // è¿”å›ç§©
}

// å¯¹[lo, hi)æ’åº
template <typename T>
void Vector<T>::sort(Rank lo, Rank hi) {
	switch (rand() % 5) { // éšæœºé€‰å–æ’åºç®—æ³•
	case 1: bubbleSort(lo, hi); break;
	case 2: selectionSort(lo, hi); break;
	case 3: mergeSort(lo, hi); break;
	case 4: quickSort(lo, hi); break;
	//default: heapSort(lo, hi); break;
	}
}
//å¯¹[lo, hi)ç½®ä¹±
template<typename T>
void Vector<T>::unsort(Rank lo, Rank hi) {
	T* V = _elem + lo;
	for (Rank i = hi - lo; i > 0; i--) {
		swap(V[i - 1], V[rand() % i]);
	}
}
// æ— åºå»é‡
template <typename T>
int Vector<T>::deduplicate() {
	int oldSize = _size; // è®°å½•åŸæœ‰è§„æ¨¡
	Rank i = 1; // ä»_elem[1]å¼€å§‹ä¾æ¬¡è€ƒå¯Ÿå„å…ƒç´ _e[i]
	while (i < _size) { // è‡ªå‰å‘åæ‰«æå…¶ä½™å…ƒç´ 
		(find(_elem[i], 0, i) < 0) ? // åœ¨å…¶å‰ç¼€ä¸­å¯»æ‰¾ä¸ä¹‹é›·åŒè€…ï¼ˆè‡³å¤šä¸€ä¸ªï¼‰
			++i : remove(i); // è‹¥æ— ï¼Œåˆ™ç»§ç»­è€ƒå¯Ÿåç»§ï¼›å¦åˆ™åˆ é™¤é›·åŒè€…
	}
	return oldSize - _size; // è¿”å›è¢«åˆ é™¤å…ƒç´ æ€»æ•°
}

// æœ‰åºå»é‡
template <typename T>
int Vector<T>::uniquify() {
	int oldSize = _size; // è®°å½•åŸæœ‰è§„æ¨¡
	Rank i = 1; // ä»_elem[1]å¼€å§‹ä¾æ¬¡æ‰«æå„å…ƒç´ _e[i]
	while (i < _size) { // è‡ªå‰å‘åè€ƒå¯Ÿï¼Œç›´è‡³æœ«å…ƒç´ 
		(_elem[i - 1] == _elem[i]) ? // è‹¥å‘ç°é‡å¤ï¼Œåˆ é™¤åè€…
			remove(i) : // ä¸‹æ ‡iå¯¹åº”çš„å…ƒç´ è¢«åˆ é™¤ï¼Œåç»§å…ƒç´ è‡ªåŠ¨å‰ç§»
			++i;
	}
	return oldSize - _size; // è¿”å›è¢«åˆ é™¤å…ƒç´ æ€»æ•°
}

//éå†ï¼ˆä½¿ç”¨å‡½æ•°æŒ‡é’ˆï¼Œåªè¯»æˆ–å±€éƒ¨æ€§ä¿®æ”¹ï¼‰
template<typename T>
void Vector<T>::traverse(void (*visit) (T&)) {
	for (int i = 0; i < _size; i++) {
		visit(_elem[i]);
	}
}

// éå†ï¼ˆä½¿ç”¨å‡½æ•°å¯¹è±¡ï¼Œå¯å…¨å±€æ€§ä¿®æ”¹ï¼‰
template <typename T> template <typename VST>
void Vector<T>::traverse(VST& visit) {
	for (int i = 0; i < _size; ++i) {
		visit(_elem[i]);
	}
}

