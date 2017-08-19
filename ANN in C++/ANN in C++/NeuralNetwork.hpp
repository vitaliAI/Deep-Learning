//
//  NeuralNetwork.hpp
//  ANN in C++
//
//  Created by Vitali Mueller on 19/08/2017.
//  Copyright © 2017 Vitali Mueller. All rights reserved.
///Users/vmueller/Documents/Software Projects/Machine Learning/ANN in C++/ANN in C++/NeuralNetwork.hpp

#ifndef NeuralNetwork_hpp
#define NeuralNetwork_hpp

#include <stdio.h>
#include <vector>

using namespace std;

class Net
{
public:
    Net(vector<double> topology){}
    // Read only the input values
    void feedForward(const vector<double> &inputValues){}
    void backPropagation(const vector<double> &targetValues){}
    void getResults(vector<double> outputValues)const{}
private:
};

#endif /* NeuralNetwork_hpp */
