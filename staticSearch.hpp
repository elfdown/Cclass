#ifndef STATICSEARCH
#define STATICSEARCH
#include "searchSet.hpp"

// template<class KEY,class VALUE>
// class staticSearch{
// private:
//     searchSet<KEY,VALUE> data;
//     int size;
// public:
//     staticSearch();
//     ~staticSearch();
// };
// template<class KEY,class VALUE>
// staticSearch<KEY,VALUE>::staticSearch(/* args */){
// }

// staticSearch::~staticSearch(){
// };


template<class KEY,class VALUE>
int seqSearch(searchSet<KEY,VALUE> *data,int size,const KEY &x){
    data[0].key = x;
    int i;
    for (i=size;x<data[i].key;--i);
    if (x == data[i].key) return i;
    return 0;
}

template<class KEY,class VALUE>
int binarySearch(searchSet<KEY,VALUE> *data,int size,const KEY &x){
    int low = 1,high = size,mid;
    while (low <= high){
        mid = (low+high) / 2;
        if (x == data[mid].key) return mid;
        if (x < data[mid].key) high = mid-1;
        else low = mid + 1;
    }
    return 0;
}





#endif