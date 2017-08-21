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

struct Connections
{
    double weight;
    double deltaWeight;
};

class Net
{
public:
    // Constructor - ANN Architecture Initialisation
    Net(const vector<double> topology);
    // Read only the input values
    void feedForward(const vector<double> &inputValues);
    void backPropagation(const vector<double> &targetValues);
    void getResults(vector<double> &outputValues)const;
private:
    // n_layers[layerNumber][neuronNumber]
    vector<Layer> n_layers;
    double error;
    double recentAverageError;
    double recentAverageSmoothingFactor;
    
};

class Neuron
{
public:
    Neuron(unsigned numOutputs, unsigned myIndex);
    void setOutputValue(double outputValues) { n_outputValue = outputValues; }
    double getOutputValue(void) const { return n_outputValue; }
    void feedForward(const Layer &prevLayer);
    void calculateOutputGradients(double targetVal);
    void calculateHiddenGradients(const Layer &nextLayer);
    void updateInputWeights(Layer &prevLayer);
    
private:
    static double eta;
    static double alpha;
    static double activationFunction(double);
    static double activationFunctionDerivative(double);
    static double randomWeight(void);
    double sumDOW(const Layer &nextLayer) const;
    double n_outputValue;
    vector<Connections> n_outputWeights;
    unsigned n_myIndex;
    double gradient;
};

#endif /* NeuralNetwork_hpp */
