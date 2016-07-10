/**
 * Longest increasing sequence.
 */
template<class T = int, class Compare = less<T> > struct LongestIncreasingSequence {
  // Indexes of LIS
  vector<int> lis;
  // Length of LIS ended at i-th element.
  vector<int> length;

  Compare _compare;
  vector<int> _tmp, _from;

  template<class RandomAccessIterator> int calc(
      RandomAccessIterator first, RandomAccessIterator last) {
    int n = last - first;
    length.resize(n);
    _tmp.resize(n + 1);
    _from.resize(n);
    int res = 0;
    for (int i = 0; i < n; i++) {
      int head = 1, tail = res;
      while (head <= tail) {
        int medium = (head + tail) >> 1;
        if (_compare(first[_tmp[medium]], first[i])) head = medium + 1;
        else tail = medium - 1;
      }
      _tmp[head] = i;
      length[i] = head;
      _from[i] = _tmp[head - 1];
      if (head > res) res++;
    }
    lis.resize(res);
    int tmp = _tmp[res];
    for (int i = res - 1; i >= 0; i--) {
      lis[i] = tmp;
      tmp = _from[tmp];
    }
    return res;
  }
};

