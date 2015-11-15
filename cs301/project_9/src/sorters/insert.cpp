//
// insert.cpp
//

template<class T>
void sorters::exchange(T &v1, T &v2) {
   T tmp = v2;
   v2 = v1;
   v1 = tmp;
}

// insert
//
//
//
template<class T, class SizeT, class CountT>
CountT sorters::insert(T a[], SizeT a_size) {
   SizeT k, j;
   CountT cnt = 0;
   for(k = 1; k < a_size; ++k) {
      j = k;
      while (++cnt != 0 && j > 0 && a[j] < a[j-1]) {
         exchange<T>(a[j], a[j - 1]);
         --j;
      }
   }
   return cnt;
}
