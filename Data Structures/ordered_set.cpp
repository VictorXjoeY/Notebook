#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

/* ordered_set<int> s - Declaration
   s.order_of_key(x) - Returns the number of elements lesser than x in s. If x is in s then this corresponds to its 0-based index k.
   s.find_by_order(k) - Returns the k-th element in s. Use k such that 0 <= k < s.size(). */
template <class TKey, class TValue>
using ordered_map = __gnu_pbds::tree<TKey, TValue, less<TKey>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;
template <class TKey>
using ordered_set = ordered_map<TKey, __gnu_pbds::null_type>;
