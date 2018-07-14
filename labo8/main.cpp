#include <iostream>
#include "IteratedList.h"

using namespace std;

int main() {
  ForwardList<int> list;

  for(int i = 0; i < 20; ++i) {
    list.push_front(rand() % 100);
  }
  cout << list << endl; 
  
  ForwardList<int>::iterator prec;
  ForwardList<int>::iterator it = list.before_begin();
  
  while( prec = it++, it != list.end() )
    if (*it % 2 == 0)
      list.erase_after(it = prec);
  
  cout << list << endl;

  for( it = list.begin(); it != list.end(); ++it )
    if (*it % 3 == 0) {
      list.insert_after(it,-3);
      ++it;
    }
  
  cout << list << endl;
}
