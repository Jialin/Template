/**
 * TODO: verify multi tasks.
 *
 * Interval tree.
 *
 * Usage:
 *   init(size, initialValues);
 *   update(lowerBound, upperBound, updateInterval);
 *   calc(lowerBound, upperBound);
 */
template<class INTERVAL> struct IntervalTree {
  int _n;
  vector<INTERVAL> _intervals;

  static int _LEFT(int idx) { return idx << 1; }
  static int _RIGHT(int idx) { return (idx << 1) | 1; }

  INTERVAL *_initialValues;

  void _build(int idx, int lower, int upper) {
    if (lower == upper) {
      _intervals[idx] = _initialValues[lower];
      return;
    }
    int medium = (lower + upper) >> 1;
    _build(_LEFT(idx), lower, medium);
    _build(_RIGHT(idx), medium + 1, upper);
    _intervals[idx].merge(_intervals[_LEFT(idx)], _intervals[_RIGHT(idx)]);
  }

  int _l, _r;
  INTERVAL _updateInterval;

  void _update(int idx, int lower, int upper) {
    if (_l <= lower && upper <= _r) {
      _intervals[idx].update(_updateInterval);
      return;
    }
    _intervals[idx].pushTo(_intervals[_LEFT(idx)], _intervals[_RIGHT(idx)]);
    int medium = (lower + upper) >> 1;
    if (_r <= medium) {
      _update(_LEFT(idx), lower, medium);
    } else if (medium < _l) {
      _update(_RIGHT(idx), medium + 1, upper);
    } else {
      _update(_LEFT(idx), lower, medium);
      _update(_RIGHT(idx), medium + 1, upper);
    }
    _intervals[idx].merge(_intervals[_LEFT(idx)], _intervals[_RIGHT(idx)]);
  }

  INTERVAL _calc(int idx, int lower, int upper) {
    if (_l <= lower && upper <= _r) return _intervals[idx];
    _intervals[idx].pushTo(_intervals[_LEFT(idx)], _intervals[_RIGHT(idx)]);
    INTERVAL res;
    int medium = (lower + upper) >> 1;
    if (_r <= medium) {
      res = _calc(_LEFT(idx), lower, medium);
    } else if (medium < _l) {
      res = _calc(_RIGHT(idx), medium + 1, upper);
    } else {
      res.merge(_calc(_LEFT(idx), lower, medium), _calc(_RIGHT(idx), medium + 1, upper));
    }
    _intervals[idx].merge(_intervals[_LEFT(idx)], _intervals[_RIGHT(idx)]);
    return res;
  }

  void init(int n, INTERVAL *initialValues) {
    _intervals.resize(n << 2);
    _n = n;
    _initialValues = initialValues;
    _build(1, 0, _n - 1);
  }

  void update(int l, int r, INTERVAL updateInterval) {
    _l = l;
    _r = r;
    _updateInterval = updateInterval;
    _update(1, 0, _n - 1);
  }

  INTERVAL calc(int l, int r) {
    _l = l;
    _r = r;
    return _calc(1, 0, _n - 1);
  }
};

struct Interval {
  int value, deltaValue;

  Interval(int value = 0, int deltaValue = 0) : value(value), deltaValue(deltaValue) {}

  void init() {
    value = deltaValue = 0;
  }

  int getValue() const {
    return value + deltaValue;
  }

  void update(const Interval &o) {
    deltaValue += o.deltaValue;
  }

  void merge(const Interval &lhs, const Interval &rhs) {
    value = lhs.getValue() + rhs.getValue();
    deltaValue = 0;
  }

  void pushTo(Interval &lhs, Interval &rhs) {
    lhs.update(*this);
    rhs.update(*this);
    deltaValue = 0;
  }
};
