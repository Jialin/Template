/**
 * One dimension dancing link.
 *
 * Usage:
 *   DL.init(numberOfNodes);
 *   // cover nodes and uncover nodes
 *   for (int i = DL.start(); i >= 0; i = DL.next(i)) {}
 */
struct DancingLinkOneDimension {
  int n;
  vector<int> _prev, _next;

  int _getNext(int idx) {
    int res = _next[idx];
    return res > n ? -1 : res - 1;
  }

  void init(int n) {
    this->n = n;
    _prev.resize(n + 2);
    _next.resize(n + 2);
    for (int i = 0; i < n + 2; i++) {
      _prev[i] = i - 1;
      _next[i] = i + 1;
    }
  }

  // 0 <= idx && idx < n
  void cover(int idx) {
    idx++;
    _next[_prev[idx]] = _next[idx];
    _prev[_next[idx]] = _prev[idx];
  }

  // 0 <= idx && idx < n
  void uncover(int idx) {
    idx++;
    _next[_prev[idx]] = _prev[_next[idx]] = idx;
  }

  int start() {
    return _getNext(0);
  }

  int next(int idx) {
    return _getNext(idx + 1);
  }
};
