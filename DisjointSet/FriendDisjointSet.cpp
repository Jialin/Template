/**
 * Disjoint set for transitive friend relation.
 *
 * Usage:
 *   init(numberOfNodes);
 *   setFriend(x, y);
 *   isFriend(x, y);
 */
struct FriendDisjointSet {
  int _setCnt;
  vector<int> p;

  void _shrink(int root, int x) {
    while (p[x] >= 0) {
      int y = p[x];
      p[x] = root;
      x = y;
    }
  }

  void init(int n) {
    p = vector<int>(n, -1);
    _setCnt = n;
  }

  int getRoot(int x) {
    int root = x;
    for ( ; p[root] >= 0; root = p[root]) {}
    _shrink(root, x);
    return root;
  }

  bool isFriend(int x, int y) {
    return getRoot(x) == getRoot(y);
  }

  void setFriend(int x, int y) {
    int rootx = getRoot(x), rooty = getRoot(y);
    if (rootx != rooty) {
      _setCnt--;
      p[rootx] += p[rooty];
      p[rooty] = rootx;
    }
  }

  /** Gets # of nodes in <x>'s friend set. */
  int getSetSize(int x) {
    return -p[getRoot(x)];
  }

  /** Gets # of friend sets. */
  int getSetCnt() {
    return _setCnt;
  }
};
