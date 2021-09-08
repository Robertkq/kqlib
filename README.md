This library is my take at recreating fundamental data structures and functions to help modify them as we like, I have tried to keep everythin as smilliar as std as I could.

# The main kqlib.h header includes:
1. kqvector.h
2. kqlinkedlist.h
3. kqdeque.h
4. kqpair.h
5. kqalgorithm.h
6. kqother

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
      std::cout << *it;
  }
  std::cout << "\n";
  v[0] = v[1] + 1;
  std::cout << v.front();
  
  return 0;
}
```
