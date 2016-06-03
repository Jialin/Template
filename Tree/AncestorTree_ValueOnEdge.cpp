/**
 * TODO: verify multi tasks.
 *
 * Ancestor tree.
 * 1. Find the [k]-th ancestor of a node;
 * 2. Aggregate the [k] edges' value above a node.
 *
 * Usage:
 *   init(numberOfNodes);
 *   // add edges
 *   preprocess();
 *   calcAncestor(node, kthAncestor);
 *   calc(node, kEdgesAbove);
 */
template<class VALUE> struct AncestorTreeValueOnEdge {
  struct _Edge {
    int to;
    VALUE value;

    _Edge() {}

    _Edge(int to, VALUE &value) : to(to), value(value) {}
  };

  vector<vector<_Edge> > _edges;
  vector<vector<int> > _ancestor;
  vector<vector<VALUE> > _ancestorValue;

  void _dfs(int u, int parent, int depth, VALUE *value) {
    this->depth[u] = depth;
    _ancestor[0][u] = parent;
    if (value != NULL) _ancestorValue[0][u] = *value;
    for (int bit = 1, last = parent; 1 << bit <= depth; bit++) {
      _ancestor[bit][u] = _ancestor[bit - 1][last];
      _ancestorValue[bit][u] = _ancestorValue[bit - 1][u] + _ancestorValue[bit - 1][last];
      last = _ancestor[bit - 1][last];
    }
    for (auto &edge : _edges[u]) if (edge.to != parent) {
      _dfs(edge.to, u, depth + 1, &edge.value);
    }
  }

  /// Depth of the node (starting from 0)
  vector<int> depth;

  void init(int n) {
    _edges.resize(n);
    for (auto &edges : _edges) edges.clear();
    depth.resize(n);
    int bit;
    for (bit = 1; 1 << bit <= n; bit++) {}
    _ancestor.resize(bit);
    for (auto &ancestor : _ancestor) ancestor.resize(n);
    _ancestorValue.resize(bit);
    for (auto &ancestorValue : _ancestorValue) ancestorValue.resize(n);
  }

  void addDirectedEdge(int x, int y, VALUE value) {
    _edges[x].push_back(_Edge(y, value));
  }

  void addUndirectedEdge(int x, int y, VALUE value) {
    addDirectedEdge(x, y, value);
    addDirectedEdge(y, x, value);
  }

  void preprocess(int root = 0) {
    _dfs(root, -1, 0, NULL);
  }

  /// Gets the [k]th ancestor of node [u]. 0-th is itself, 1-th is parent.
  /// NOTE: Returns -1 if not exist.
  int calcAncestor(int u, int kth) {
    if (depth[u] < kth) return -1;
    for (int bit = 0; kth; bit++, kth >>= 1) if (kth & 1) {
      u = _ancestor[bit][u];
    }
    return u;
  }

  /// Gets the combined [VALUE] of the [k] edges above node [u].
  /// NOTE: 1 <= k <= depth[u]
  VALUE calc(int u, int k) {
    assert(1 <= k && k <= depth[u]);
    bool first = true;
    VALUE res;
    for (int bit = 0; k; bit++, k >>= 1) if (k & 1) {
      if (first) {
        first = false;
        res = _ancestorValue[bit][u];
      } else {
        res = res + _ancestorValue[bit][u];
      }
      u = _ancestor[bit][u];
    }
    return res;
  }
};

struct AncestorTreeMaxValueEdge {
  int maxValue;

  AncestorTreeMaxValueEdge(int maxValue = 0) : maxValue(maxValue) {}

  AncestorTreeMaxValueEdge operator +(const AncestorTreeMaxValueEdge &o) {
    return AncestorTreeMaxValueEdge(max(maxValue, o.maxValue));
  }
};
