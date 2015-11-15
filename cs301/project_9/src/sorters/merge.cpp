//
// merge.cpp
//

template<class T, class SizeT, class CountT>
CountT r_merge(T a[], SizeT low, SizeT high);

template<class T, class SizeT>
void merge_segments(T a[], SizeT low, SizeT mid, SizeT high);

// merge
//
//
//
template<class T, class SizeT, class CountT>
CountT sorters::merge(T a[], SizeT a_size) {
   return r_merge<T, SizeT, CountT>(a, 0, a_size - 1);
}

template<class T, class SizeT, class CountT>
CountT r_merge(T a[], SizeT low, SizeT high) {
   SizeT mid = (low + high) / 2;
   CountT count = 0;
   if (low < high) {
      count += r_merge<T, SizeT, CountT>(a, low, mid);
      count += r_merge<T, SizeT, CountT>(a, mid + 1, high);
      merge_segments<T, SizeT>(a, low, mid, high);
      count += 2 * (high - low + 1);
   }
   return count;
}

template<class T, class SizeT>
void merge_segments(T a[], SizeT low, SizeT mid, SizeT high) {
   SizeT j = low, k = mid + 1;
   SizeT tmp_size = high - low + 1;
   SizeT tmp_index = 0;
   T *tmp;

   tmp = new T[tmp_size];
   while(j < mid + 1 && k < high + 1) {
      if (a[j] < a[k])
         tmp[tmp_index++] = a[j++];
      else
         tmp[tmp_index++] = a[k++];
   }

   while(j < mid + 1)
      tmp[tmp_index++] = a[j++];
   while(k < high + 1)
      tmp[tmp_index++] = a[k++];

   assert(tmp_index == tmp_size);
   tmp_index = 0;
   for (int i = low; i <= high; ++i)
      a[i] = tmp[tmp_index++];

   delete []tmp;
}
