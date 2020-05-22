#include <vector>
#include <iostream>
using namespace std;
/**
 * Performs mergesort on the provided vector using
 * the Compare object, comp, to peform ALL comparisons
 *
 * Must run in O(n*log(n))
 */
template <class T, class Compare>
void mergeSort(std::vector<T>& list, Compare comp);

template <class T, class Compare>
void mergeSort(std::vector<T>& list, Compare comp){
    msort(list, 0, list.size()-1, comp);
}

template <class T, class Compare>
void msort(std::vector<T>& mylist, int start, int end, Compare comp){
    if (start < end){
        int m = (start + end)/2;
        msort(mylist, start, m, comp);
        msort(mylist, m+1, end, comp);
        merge(mylist, start, end, m, comp);
    }
}

template <class T, class Compare>
void merge(std::vector<T>& mylist, int l, int r, int m, Compare comp){
    
    vector<T> temp;
    temp.resize(r+1-l);
    
    int i = l, j =m+1, k=0;
    while (i <=m || j <=r){
        if (i <=m && (j > r || comp(mylist[j],mylist[i]))){
            /* smallest is on left */
            temp[k] = mylist[i];
            i++;
            k++;
        }else{
            /*smallest is in the right half*/
            temp[k] = mylist[j];
            j++;
            k++;
        }
    }
    for (k=0; k < r+1-l; k++) mylist[k+l] = temp[k];
}



template <typename T>
struct lessThan{
    bool operator()(const T value1, const T value2){
        return value1 < value2;
    }
};
           
//ascending comparator
template <typename T>
struct CompObj{
    bool operator()(const T value1, const T value2){
        return value1 >= value2;
    }
};

//Pagerank comparator
template <typename T>
struct PRObj{
    bool operator()(const T value1, const T value2){
        return value1.second <= value2.second;
    }
};

//page name comparator
template <typename T>
struct NObj{
    bool operator()(const T value1, const T value2){
        return value1.first->filename() >= value2.first->filename();
    }
};
//webpage sort comparator
template <typename T>
struct WebObj{
    bool operator()(const T value1, const T value2){
        return value1->filename() >= value2->filename();
    }
};
