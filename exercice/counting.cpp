//
//  counting.cpp
//
//  Created by Olivier Cuisenaire on 10.04.15.
//  Copyright (c) 2015 Olivier Cuisenaire. All rights reserved.
//

#include <iostream>
#include <utility>
#include <climits>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// countingSort
//
// Effectue le tri comptage des éléments entre begin
// et end (non inclus). Les éléments pointés par ces
// itérateurs doivent être de type entier (char, short, int, long).
// Calcule les min et max des éléments pour déterminer
// le tableau de compteurs à allouer. Affiche dans l'ordre
// des éléments croissants et pour chaque élément de
// compte > 0 le nombre d'occurence sous la forme
// E: C
// où E est l'élément et C le compte.
//
// A COMPLETER

template < typename RandomAccessIterator >
void countingSort( RandomAccessIterator begin,
                  RandomAccessIterator end )
{
   RandomAccessIterator min = min_element(begin, end);
   RandomAccessIterator max = max_element(begin, end);
    
   vector<int> result(abs(*min - *max));
   cout << *min << " " << (int)*min << " " << *max << " " << (int)*max << endl;
   
   for(RandomAccessIterator i = begin; i != end; ++i) {
        cout << *i << " " << " " << *i - *min << endl;
        result.at(*i - *min)++;
   }

   for(int i : result)
      cout << i << ";";
   
   

}

// display
//
// Affiche les valeur entre begin et end (non inclus)
// utilisé uniquement par main, pas par vous.
//
// NE RIEN MODIFIER A CETTE FONCTION

template < typename RandomAccessIterator >
void display( const RandomAccessIterator begin,
             const RandomAccessIterator end )
{
    for(auto it = begin; it<end; ++it) cout << *it << " ";
    cout << endl;
}

// main
//
// Programme testant la mise en oeuvre de selectionSort
// appelle cette fonction avec une string, un tableau
// C d'entiers et un std::vector<double>
//
// NE RIEN MODIFIER A CETTE FONCTION

int main() {
    
    // std::string
    
    string s("EXEMPLE_DE_TRI_COMPTAGE");
    display(s.begin(),s.end());
    
    countingSort(s.begin(),s.end());
    
    display(s.begin(),s.end());
    
    // C array
    
    int array[] = { 1, 3, 1, 1, 2, 1, 0, 1, 3, -1 };
    cout << endl;
    display(array,array+10);
    
    countingSort(array,array+10);
    
    display(array,array+10);
    
    // std::vector
    
    vector<int> vd {  7, 3, 6, 1, 9, 7, 3, 3, 3, 6, 1, 2, 0, 10, 12, -3 };
    cout << endl;
    display(vd.begin(),vd.end());
    
    countingSort(vd.begin(),vd.end());
    
    display(vd.begin(),vd.end());
    
    return 0;
    
}
