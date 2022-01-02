This library is my take at recreating fundamental data structures and functions to help modify them as we like, I have tried to keep everything as similar to std as I could.

*Special thanks to @PetrFlajsingr for helping with logic, design and solution clarifications.

# The main kqlib.h header includes:

1. kqlib\algorithm.h
2. kqlib\deque.h
3. kqlib\linkedlist.h
4. kqlib\other.h
5. kqlib\string.h
6. kqlib\vector.h

# Examples
```cpp
#include <iostream>
#include "kqvector.h"

using namespace kq;

int main()
{
  vector<int> v({1, 6, 2002, 19, 100});
  for(vector<int>::iterator it = v.begin(); it != v.end(); ++it)
  {
      std::cout << *it << " ";
  }
  std::cout << "\n";
  v[0] = v[1] + 1;
  std::cout << v.front();
  
  return 0;
}
```
