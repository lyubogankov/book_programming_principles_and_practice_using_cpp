#include <vector>
#include <memory>

using std::allocator;
using std::vector;

template<typename T, typename U>
double dot_product(const vector<T, allocator<T>>& vt, const vector<U, allocator<U>>& vu);