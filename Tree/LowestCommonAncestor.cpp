/**
 * Lowest Common Ancestor.
 *
 * Usage:
 *   init(numberOfNodes);
 *   // add edges
 *   preprocess();
 *   calc(node1, node2);
 */
template<int MAXN, int MAXBIT> struct LowestCommonAncestor {
  int _m;
  vector<int> _height, _idx, _in, _out, _LOG2;
  vector<vector<int> > _edges;
  vector<vector<pair<int, int> > > _rmq;

  void _dfs(int u, int parent, int depth) {
    this->parent[u] = parent;
    this->depth[u] = depth;
    _height[_m] = depth;
    _idx[_m] = u;
    _in[u] = _m++;
    for (int v : _edges[u]) if (v != parent) {
      _dfs(v, u, depth + 1);
      _height[_m] = depth;
      _idx[_m] = u;
      _m++;
    }
    _height[_m] = depth;
    _idx[_m] = u;
    _out[u] = _m++;
  }

  void _initRMQ() {
    int bit;
    for (bit = 1; 1 << bit <= _m; bit++) {}
    _rmq.resize(bit);
    _rmq[0].resize(_m);
    for (int i = 0; i < _m; i++) _rmq[0][i] = make_pair(_height[i], _idx[i]);
    for (int bit = 1; 1 << bit <= _m; bit++) {
      _rmq[bit].resize(_m - (1 << bit) + 1);
      for (int i = _m - (1 << bit); i >= 0; i--) {
        _rmq[bit][i] = min(_rmq[bit - 1][i], _rmq[bit - 1][i + (1 << (bit - 1))]);
      }
    }
    for (int i = 1; i <= _m; i++) {
      _LOG2[i] = __builtin_popcount(i) == 1 ? __builtin_ctz(i) : _LOG2[i - 1];
    }
  }

  int _queryRMQ(int x, int y) {
    if (x > y) return -1;
    int bit = _LOG2[y - x + 1];
    return min(_rmq[bit][x], _rmq[bit][y - (1 << bit) + 1]).second;
  }

  /// Parent node index
  vector<int> parent;
  /// Depth of the node (starting from 0)
  vector<int> depth;

  void init(int n) {
    int n3 = n * 3;
    _edges.resize(n);
    _height.resize(n3);
    _idx.resize(n3);
    _in.resize(n);
    _out.resize(n);
    _LOG2.resize(n3);
    parent.resize(n);
    depth.resize(n);
  }

  void addDirectedEdge(int u, int v) {
    _edges[u].push_back(v);
  }

  void addUndirectedEdge(int u, int v) {
    addDirectedEdge(u, v);
    addDirectedEdge(v, u);
  }

  void preprocess(int root = 0) {
    _m = 0;
    _dfs(root, -1, 0);
    _initRMQ();
  }

  int calc(int x, int y) {
    return _queryRMQ(min(_in[x], _in[y]), max(_out[x], _out[y]));
  }
};
