
#include "bits/stdc++.h"
#define pb push_back
#define ll long long

using namespace std;

template <typename T>
void BubbleSort(vector<T> &a);
template <typename T>
void BubbleSort(vector<T> &a, T l, T r);
template <typename T>
void BubbleSort(vector<T> &a, T l, T r, function<bool(T, T)> &cmp);


template <typename T>
static function<bool(T, T)> cmp = [](T a, T b) {
    return a > b;
};

template<typename T>
T findMax(vector<T>& arr, T l, T r) {T max = arr[l];
    for (auto i = l + 1; i < r; i++) {if (arr[i] > max) max = arr[i];} return max;}

/*

    ///////////////////////////////////////

*/

template <typename T>
void BubbleSort(vector<T>& a, T l, T r, function<bool(T, T)> &cmp){
    for (auto i = l; i < r; i++){
        for (auto j = i + 1; j < r; j++){
            if (cmp(a[i], a[j])) swap(a[i], a[j]);
        }
    }
}

template <typename T>
void BubbleSort(vector<T>& a, T l, T r){
    return BubbleSort(a, l, r, ::cmp<typeof(a[l])>);
}

template <typename T>
void BubbleSort(vector<T>& a, function<bool(T, T)> &cmp){
    return BubbleSort(a, (T)0, (T)a.size(), ::cmp<typeof(a[(T)0])>);
}

template <typename T>
void BubbleSort(vector<T>& a){
    return BubbleSort(a, (T)0, (T)a.size(), ::cmp<typeof(a[(T)0])>);
}

int main() {
    auto n = 5; //2642245
    random_device rd;
    uniform_int_distribution<int> dist(1, pow(n, 3) - 1);
    vector<int> a;
    for (int i = 0; i < n; i++) a.pb(dist(rd));
    for (auto &x : a) printf("%d %s", x, " "); cout << endl;
    auto t = clock()/(double)1000;

    //BubbleSort(a);
    //BubbleSort(a, cmp<typeof(a[0])>);
    //BubbleSort(a, 2, 5);
    //BubbleSort(a, 1, 5, cmp<typeof(a[0])>);

    std::cout << "time: " << clock()/(double)1000 - t << std::endl;
    for (auto &x : a) printf("%d %s", x, " ");
    return 0;
}