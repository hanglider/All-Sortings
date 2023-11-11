#include "bits/stdc++.h"
#define pb push_back
#define ll long long

using namespace std;

template <typename T>
void QuickSort(vector<T> &a);
template <typename T>                   //have problems with cmp
void QuickSort(vector<T> &a, T l, T r);
template <typename T>
void QuickSort(vector<T> &a, T l, T r, function<bool(T, T)> &cmp);

template <typename T>
void MergeSort(vector<T> &a);
template <typename T>
void MergeSort(vector<T> &a, T l, T r);
template <typename T>
void MergeSort(vector<T> &a, T l, T r, function<bool(T, T)> &cmp);

template <typename T>
void InsertionSort(vector<T>& a);
template <typename T>                   //have problems with cmp
void InsertionSort(vector<T>& a, T l, T r);
template <typename T>
void InsertionSort(vector<T>& a, T l, T r, function<bool(T, T)> &cmp);

template <typename T>
void MergeInsertionSort(vector<T>& a);
template <typename T>
void MergeInsertionSort(vector<T>& a, T m, T l, T r);
template <typename T>
void MergeInsertionSort(vector<T>& a, T m, T l, T r, function<bool(T, T)> &cmp);

template <typename T>
void RadixSort(vector<T>& a);
/*template <typename T>
void RadixSort(vector<T>& arr, T l, T r);       //don't work
template <typename T>
void RadixSort(vector<T>& arr, T l, T r, function<bool(T, T)> &cmp);*/

template<typename T>
void countSort(vector<T>& arr, T exp, T l, T r);  //for radix
template <typename T>
T G(vector<T>& a, T l, T r);                      //optimization for pick el in Quick
template <typename T>
auto F(vector<T>& a, T l, T r, function<bool(T, T)> &cmp); //sort for Quicksort

template <typename T>
static function<bool(T, T)> cmp = [](T a, T b) {
    return a < b;
};

template <typename T>
T Binpow (T a, T n) {int r = 1;while (n) {if (n & 1) r *= a; a *= a; n >>= 1;} return r;}

template<typename T>
T findMax(vector<T>& arr, T l, T r) {T max = arr[l];
    for (auto i = l + 1; i < r; i++) {if (arr[i] > max) max = arr[i];} return max;}

/*

    ///////////////////////////////////////

*/

template <typename T>
T G(vector<T>& a, T l, T r) {
    auto mid = l + (r - l) / 2;
    if (a[l] > a[mid])
        swap(a[l], a[mid]);
    if (a[l] > a[r])
        swap(a[l], a[r]);
    if (a[mid] > a[r])
        swap(a[mid], a[r]);
    return mid;
}

template <typename T>
auto F(vector<T>& a, T l, T r, function<bool(T, T)> &cmp) {
    auto m = G(a, l, r);
    auto mid = a[m];
    swap(a[m], a[r]);
    auto i = l - 1;
    for (auto j = l; j <= r - 1; j++) {
        if (cmp(a[j], mid)) swap(a[++i], a[j]);
    }
    swap(a[i + 1], a[r]);
    return ++i;
}

template <typename T>
void QuickSort(vector<T> &a, T l, T r, function<bool(T, T)> &cmp) {
    if (l < r){
        auto mid = F(a, l, r, ::cmp<typeof(a[0])>);
        QuickSort(a, l, mid - 1, ::cmp<typeof(a[0])>);
        QuickSort(a, mid + 1, r, ::cmp<typeof(a[0])>);
    }
}

template <typename T>
void QuickSort(vector<T> &a, T l, T r) {
    return QuickSort(a, l, r, cmp<typeof(a[0])>);
}

template <typename T>
void QuickSort(vector<T> &a) {
    return QuickSort(a, (T)0, (T)a.size(), cmp<typeof(a[0])>);
}

/*

    ///////////////////////////////////////

*/

template <typename T>
void merge(vector<T>& a, T l, T mid, T r, function<bool(T, T)> &cmp){
    auto n1 = mid - l + 1;
    auto n2 = r - mid;

    auto i = l, j = mid + 1;
    while (i <= mid && j <= r) {
        if (cmp(a[i], a[j])){//(a[i] > a[j]) {
            j++;
        } else {
            i++;
        }
    }
    vector<T> L(n1);
    vector<T> R(n2);
    for (auto i = 0; i < n1; ++i){ L[i] = a[l + i];}
    for (auto i = 0; i < n2; ++i){ R[i] = a[mid + 1 + i];}
    i = 0; j = 0;
    auto k = l;
    while (i < n1 && j < n2){
        if (!cmp(L[i], R[j])){//(L[i] <= R[j]){
            a[k] = L[i];
            i++;
        } else {
            a[k] = R[j];
            j++;
        }
        k += 1;
    }
    while (i < n1){
        a[k] = L[i];
        i += 1;
        k += 1;
    }
    while (j < n2){
        a[k] = R[j];
        j += 1;
        k += 1;
    }
}

template <typename T>
void MergeSort(vector<T>& a, T l, T r, function<bool(T, T)> &cmp){
    if (l < r){
        auto mid = l + (r - l) / 2;
        MergeSort(a, l, mid, ::cmp<typeof(a[0])>);
        MergeSort(a, mid + 1, r, ::cmp<typeof(a[0])>);
        merge(a, l, mid, r, ::cmp<typeof(a[0])>);
    }
}

template <typename T>
void MergeSort(vector<T>& a, T l, T r){
    return MergeSort(a, l, r, cmp<typeof(a[0])>);
}

template <typename T>
void MergeSort(vector<T>& a){
    return MergeSort(a, (T)0, (T)a.size(), cmp<typeof(a[0])>);
}

/*

    ///////////////////////////////////////

*/

template <typename T>
void InsertionSort(vector<T>& a, T l, T r, function<bool(T, T)> &cmp){
    for (auto i = l; i <= r; i++){
        auto j = i - 1, key = a[i];
        while (cmp(a[j], key) && j >= 0){//a[j] > key && j >= 0){
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

template <typename T>
void InsertionSort(vector<T>& a, T l, T r){
    return InsertionSort(a, l, r, cmp<typeof(a[0])>);
}

template <typename T>
void InsertionSort(vector<T>& a){
    return InsertionSort(a, (T)0, (T)a.size(), cmp<typeof(a[0])>);
}

/*

    ///////////////////////////////////////

*/

template <typename T>
void MergeInsertionSort(vector<T>& a, T m, T l, T r, function<bool(T, T)> &cmp){
    if (l < r){
        auto mid = l + (r - l) / 2;
        if (r- l <= m) {
            InsertionSort(a, l, r, ::cmp<typeof(a[0])>);
            return ;
        }
        MergeSort(a, l, mid, ::cmp<typeof(a[0])>);
        MergeSort(a, mid + 1, r, ::cmp<typeof(a[0])>);
        merge(a, l, mid, r, ::cmp<typeof(a[0])>);
    }
}

template <typename T>
void MergeInsertionSort(vector<T>& a, T m, T l, T r){
    return MergeSort(a, l, r, cmp<typeof(a[0])>);
}

template <typename T>
void MergeInsertionSort(vector<T>& a){
    return MergeSort(a, (T)0, (T)a.size(), cmp<typeof(a[0])>);
}

/*

    ///////////////////////////////////////

*/



template<typename T, typename S>
void countSort(vector<T>& arr, S base, T exp, T l, T r) {
    const int n = r - l;
    vector<T> output(n);
    vector<T> count(base, 0);

    for (int i = l; i < r; i++) {
        count[(arr[i] / exp) % base]++;
    }
    for (int i = 1; i < base; i++) {
        count[i] += count[i - 1];
    }
    for (int i = r - 1; i >= l; i--) {
        output[count[(arr[i] / exp) % base] - 1] = arr[i];
        count[(arr[i] / exp) % base]--;
    }
    for (int i = l; i < r; i++) {
        arr[i] = output[i];
    }
}

template <typename T, typename S>
void RadixSort(vector<T>& a, S base) {
    return RadixSort(a, base, (T)0, (T)a.size());
}

template <typename T, typename S>
void RadixSort(vector<T>& a, S base, T l, T r) {
    auto max = findMax(a, l, r);
    for (T exp = l + 1; max / exp > 0; exp *= base) {
        countSort(a, base, exp, l, r);
    }
}

template <typename T, typename S>
void RadixSort(vector<T>& a, S base, T l, T r, function<bool(T, T)> &cmp) {
    auto max = findMax(a, l, r);
    for (T exp = l + 1; max / exp > 0; exp *= base) {
        countSort(a, base, exp, l, r);
    }
}

int main() {
    //ll n = 2642245;
    auto n = 5;
    random_device rd;
    uniform_int_distribution<int> dist(1, Binpow(n, 3) - 1);
    vector<int> a;
    for (int i = 0; i < n; i++){
        a.pb(dist(rd));
    }
    for (auto &x : a){
        printf("%d %s", x, " ");
    }
    cout << endl;
    auto t = clock()/(double)1000;
    //BubbleSort(a);
    //BubbleSort(a, l, r);
    //BubbleSort(a, l, r, cmp<typeof(a[0])>);
    //InsertionSort(a);
    //InsertionSort(a, l, r);
    //InsertionSort(a, l, r, cmp<typeof(a[0])>);
    //QuickSort(a);
    //QuickSort(a, 0, n - 1);
    //QuickSort(a, 0, n - 1, cmp<typeof(a[0])>);
    MergeSort(a);
    //MergeSort(a, 0, n - 1);
    //MergeSort(a, 0, n - 1, cmp<typeof(a[0])>);
    //MergeInsertionSort(a, m);
    //MergeInsertionSort(a, m, 0, n - 1);
    //MergeInsertionSort(a, m, 0, n - 1, cmp<typeof(a[0])>);
    //HeapSort(a);
    //HeapSort(a, 0, n - 1);
    //HeapSort(a, 0, n - 1, cmp<typeof(a[0])>);
    //CoutingSort(a);
    //CoutingSort(a, 0, n - 1);
    //CoutingSort(a, 0, n - 1, cmp<typeof(a[0])>);
    //RadixSort(a, 0, n);
    //RadixSort(a, 0, n);                               //don't work for interval l > 0

    std::cout << "time: " << clock()/(double)1000 - t << std::endl;
    for (auto &x : a){
        printf("%d %s", x, " ");
    }
    return 0;
}