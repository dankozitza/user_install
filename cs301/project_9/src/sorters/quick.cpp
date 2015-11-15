//
// quick.cpp
//

template<class T, class SizeT, class CountT>
CountT r_quick(T a[], SizeT low, SizeT high);

template<class T, class SizeT>
void partition(T a[], SizeT low, SizeT high, T pivot, SizeT &i, SizeT &j);

template<class T, class SizeT, class CountT>
CountT sorters::quick(T a[], SizeT a_size) {
   return r_quick<T, SizeT, CountT>(a, 0, a_size - 1);
}

template<class T, class SizeT, class CountT>
CountT r_quick(T a[], SizeT low, SizeT high) {
   CountT count = 0;
   SizeT i, j;
   if (low < high) {
      T pivot = a[(high + low) / 2];
      partition<T, SizeT>(a, low, high, pivot, i, j);
      count += high - low + 1;

      count += r_quick<T, SizeT, CountT>(a, low, i);
      count += r_quick<T, SizeT, CountT>(a, j, high);
   }
   return count;
}

template<class T, class SizeT>
void partition(T a[], SizeT low, SizeT high, T pivot, SizeT &i, SizeT &j) {
   SizeT lasts1 = low, firstU = low, firsts3 = high + 1;
   while (firstU < firsts3) {
      if (a[firstU] < pivot) // s1
         sorters::exchange<T>(a[firstU++], a[lasts1++]);
      else if (a[firstU] == pivot) // s2
         ++firstU;
      else // s3
         sorters::exchange<T>(a[firstU], a[--firsts3]);
   }
   if (lasts1 > 0)
      --lasts1;
   i = lasts1;
   j = firsts3;
}
