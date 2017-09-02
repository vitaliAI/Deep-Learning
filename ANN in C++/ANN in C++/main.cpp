//
//  main.cpp
//  ANN in C++
//
//  Created by Vitali Mueller on 19/08/2017.
//  Copyright © 2017 Vitali Mueller. All rights reserved.
//

#include <iostream>
#include <vector>
#include "NeuralNetwork.hpp"
#include "ReadData.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    
    
    // Topology is Architecture of Artificial Neural Network
    // e.g. {3,2,1}
    // 3 input values + one Bias Neuron, 2 hidden neurons + one Bias  Neuron, 1 output value
    vector<double> topology;
    topology.push_back(3);
    topology.push_back(2);
    topology.push_back(1);
    Net myANNetwork(topology);
    // Feedforward Method
    vector<double> inputValues;
    inputValues.push_back(2);
    inputValues.push_back(3);
    inputValues.push_back(1);
    myANNetwork.feedForward(inputValues);
    // Backpropagation to optimise Parameters/Weights
    vector<double> targetValues;
    myANNetwork.backPropagation(targetValues);
    // Getting Output Values from Input Values
    vector<double>outputValues;
    myANNetwork.getResults(outputValues);
    
    return 0;
}
