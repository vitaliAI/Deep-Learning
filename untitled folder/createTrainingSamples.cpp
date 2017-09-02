//
//  createTrainingSamples.cpp
//  ANN in C++
//
//  Created by Vitali Mueller on 23/08/2017.
//  Copyright © 2017 Vitali Mueller. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

int main(void)
{
    // Random training Samples for XOR
    // Two inputs and one output
    
    cout << "topology: 2 4 1" << endl;
    for(int i = 2000; i >= 0; --i)
    {
        int n1 = static_cast<int>(2.0 * rand() / static_cast<double>(RAND_MAX));
        int n2 = static_cast<int>(2.0 * rand() / static_cast<double>(RAND_MAX));
        int t = n1 ^ n2;  // should be 0 or 1
        cout << "in: " << n1 << ".0 " << n2 << ".0 " << endl;
        cout << "out: " << t << ".0" << endl;
    }


    return 0;
}


