/**
 * Hash rooted tree.
 *
 * For each node, its hash value equals to
 *   ((((seed1 * MOD) ^ H1) * MOD) ^ H2 ...) * seed2 % 2^64
 *   where H1, H2, ... are the sorted hash values of its child nodes.
 *
 * Usage:
 *   init(numberOfNodes, whetherDuplicateEdges *OPTIONAL*);
 *   // add edges
 *   calc(rootIdx, seed1, seed2);
 */
template<
    int MOD = 1000000007,
    unsigned long long SEED1 = 100000000000000003ULL,
    unsigned long long SEED2 = 1000000000000000003ULL> struct RootedTreeHash {
  vector<vector<int> > _edges;
  vector<unsigned long long> _hashs;
  unsigned long long _seed1, _seed2;
  bool _duplicateEdges;

  unsigned long long &_dfs(int u, int parent) {
    vector<unsigned long long> childs(_edges[u].size() - (parent >= 0));
    int idx = 0;
    for (auto v : _edges[u]) if (v != parent) {
      childs[idx++] = _dfs(v, u);
    }
    sort(childs.begin(), childs.end());
    unsigned long long &res = _hashs[u];
    res = _seed1;
    for (auto &hash : childs) res = (res * MOD) ^ hash;
    res *= _seed2;
    return res;
  }

  void init(int n, bool duplicateEdges = false) {
    _duplicateEdges = duplicateEdges;
    _edges.resize(n);
    for (auto &edges : _edges) edges.clear();
    _hashs.resize(n);
  }

  void addDirectedEdge(int x, int y) {
    _edges[x].push_back(y);
  }

  void addUndirectedEdge(int x, int y) {
    addDirectedEdge(x, y);
    addDirectedEdge(y, x);
  }

  unsigned long long &calc(
      int root = 0,
      unsigned long long _seed1 = SEED1,
      unsigned long long _seed2 = SEED2) {

    if (_duplicateEdges) {
      for (auto &edges : _edges) {
        sort(edges.begin(), edges.end());
        edges.erase(unique(edges.begin(), edges.end()), edges.end());
      }
      _duplicateEdges = false;
    }
    this->_seed1 = _seed1;
    this->_seed2 = _seed2;
    return _dfs(root, -1);
  }
};
