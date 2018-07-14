#include <stdlib.h>
#include <string>
#include <iostream>
#include <cmath>


using namespace std;

int fractale(unsigned int n, unsigned int i) {
    if(n) {
            unsigned nbEtoille = fractale(n-1, i);
            
            cout << string(i,' ') << endl;


            for(unsigned int j = 0; j < nbEtoille; ++j) {
                cout << " *";
                cout << endl;
                
                fractale(n-1, nbEtoille + i);

                return nbEtoille << 1;
            }
    }

    return 1;
}
