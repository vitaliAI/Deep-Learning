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
#include "Config.hpp"



using namespace std;

// Forward Reference to class Neuron
class Neuron;

typedef vector<Neuron> Layer;

class Net
{
public:
    // Constructor - ANN Architecture Initialisation
    Net(const vector<double> topology);
    // Read only the input values
    void feedForward(const vector<double> &inputValues){}
    void backPropagation(const vector<double> &targetValues){}
    void getResults(vector<double> outputValues)const{}
private:
    // n_layers[layerNumber][neuronNumber]
    vector<Layer> n_layers;
};

class Neuron
{

};

#endif /* NeuralNetwork_hpp */
