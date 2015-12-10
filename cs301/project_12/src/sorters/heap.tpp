//
// heap.tpp
//

template<class T, class SizeT, class CountT>
CountT reheap_down(T a[], SizeT parent, SizeT last) {
   CountT cnt = 0;
   SizeT max_child;
   bool done = false;
   while (2 * parent + 1 <= last && !done) {
      cnt++;
      max_child = 2 * parent + 1;

      if (max_child < last && a[max_child + 1] > a[max_child])
         ++max_child;
      
      if (a[parent] < a[max_child]) {
         sorters::exchange<T>(a[parent], a[max_child]);
         parent = max_child;
      }
      else {
         done = true;
      }
   }
   return cnt;
}

template<class T, class SizeT, class CountT>
CountT sorters::heap(T a[], SizeT a_size) {
   CountT cnt = 0;
   for (SizeT i = ((a_size - 2)/2); i >= 1; --i) {
      cnt += reheap_down<T, SizeT, CountT>(a, i, a_size - 1);
   }
   cnt += reheap_down<T, SizeT, CountT>(a, 0, a_size - 1);

   for (SizeT i = a_size - 1; i > 0; --i) {
      exchange<T>(a[0], a[i]);
      cnt += reheap_down<T, SizeT, CountT>(a, 0, i - 1);
   }
   return cnt;
}
