#include <cctype>
void selectionSort(string& A) {
   for(size_t i = 0; i < A.length() - 1; ++i) {
      size_t iMin = i;
      for(size_t j = i + 1; j < A.length(); ++j){
         if(A[iMin] > A[j]){
            iMin = j;
         }
      }
      swap(A[i], A[iMin]);
      cout << A << endl;
   }
}

// qsort
int compareWithParity(const void * p1, const void * p2) {
   if ( (*(int*)p1 % 2) < (*(int*)p2 % 2) ) return -1;
   if ( (*(int*)p1 % 2) == (*(int*)p2 % 2) ) return 0;
   if ( (*(int*)p1 % 2) > (*(int*)p2 % 2) ) return 1;
}

int compare(char c1, char c2) {
    return tolower(c1) < tolower(c2);
}


