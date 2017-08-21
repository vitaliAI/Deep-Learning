//
//  NeuralNetwork.cpp
//  ANN in C++
///Users/vmueller/Documents/Software Projects/Machine Learning/ANN in C++/ANN in C++/NeuralNetwork.hpp
//  Created by Vitali Mueller on 19/08/2017.
//  Copyright © 2017 Vitali M/Users/vmueller/Documents/Software Projects/Machine Learning/ANN in C++/ANN in C++/NeuralNetwork.hppueller. All rights reserved.
//

#include "NeuralNetwork.hpp"
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cmath>


using namespace std;

// --------------- Start Neural Network ------------------


Net::Net(const vector<double> topology)
{
    // We need to know how many total layers
    unsigned numLayers = static_cast<unsigned>(topology.size());
    for(unsigned layerNum = 0; layerNum < numLayers; ++layerNum)
    {
        // Create a new Layer with private Data Type Layer
        // Layer is a Vector of Neuron types
        this->n_layers.push_back(Layer());
        // Number of Outputs Weights/Parameters depends on Next Layer Neurons
        unsigned numberOutputs = layerNum == topology.size() - 1 ? 0 : topology[layerNum + 1];
        
        // Now we need to loop through the layer and add Neurons plus additional Bias Neuron
        for(unsigned neuronNum = 0; neuronNum <= topology[layerNum]; ++neuronNum)
        {
            this->n_layers.back().push_back(Neuron(numberOutputs, neuronNum));
            
            
#ifdef DEBUG_LOG
            if(neuronNum != topology[layerNum])
            {
                cout << "Created a Neuron in Layer " << layerNum + 1 << endl;
            }
            else
            {
                cout << "Created Bias Neuron in Layer " << layerNum + 1 << endl;
            }
#endif
            
        }
    }
}

void Net::feedForward(const vector<double> &inputValues)
{
    // test if number of input values is equal to number of Neurons in first layer
    // subtract one for the Bias Neuron
    assert(inputValues.size() == n_layers[0].size() - 1);
    
    // Input Values of the first layer are becoming directly output values
    // No activation and summation function is required at this point
    for(unsigned i = 0; i < inputValues.size(); ++i)
    {
        n_layers[0][i].setOutputValue(inputValues[i]);
    }
    
    // Forward propagation
    // start looping from the second layer
    for(unsigned layerNumber = 1; layerNumber < n_layers.size(); ++layerNumber)
    {
        Layer &prevLayer = n_layers[layerNumber - 1];
        // loop through all Neurons except Bias Neuron
        for(unsigned n = 0; n < n_layers[layerNumber].size(); ++n)
        {
            // feedForward Method from Neuron class needs to get a reference from the previous Layer
            n_layers[layerNumber][n].feedForward(prevLayer);
        }
    
    }
}

void Net::backPropagation(const vector<double> &targetValues)
{
    // Calculate overall net error - RMS (Root Mean Square) of output neuron errors
    
    Layer &outputLayer = n_layers.back();
    error = 0.0;
    
    for(unsigned n = 0; n < outputLayer.size() - 1; ++n)
    {
        double delta = targetValues[n] - outputLayer[n].getOutputValue();
        error += delta * delta;
    }
    
    // RMS - get average error squared
    error /= outputLayer.size() - 1;
    error = sqrt(error);
    
    
    recentAverageError = (recentAverageError * recentAverageSmoothingFactor +
                          error) / (recentAverageSmoothingFactor + 1.0);
    
    // Calculate output layer gradients
    
    for(unsigned n = 0; n < outputLayer.size() -1; ++n)
    {
        outputLayer[n].calculateOutputGradients(targetValues[n]);
    }
    
    // Calculate gradients on hidden layers
    for(unsigned layerNum = static_cast<unsigned>(n_layers.size()) - 2; layerNum > 0; --layerNum)
    {
        Layer &hiddenLayer = n_layers[layerNum];
        Layer &nextLayer = n_layers[layerNum + 1];
        
        for(unsigned n = 0; n < hiddenLayer.size(); ++n)
        {
            hiddenLayer[n].calculateHiddenGradients(nextLayer);
        }
    }
    
    
    // For all layers from outputs to first hidden layer,
    // update conncetion weights
    for(unsigned layerNum = static_cast<unsigned>(n_layers.size()) - 1; layerNum > 0; --layerNum)
    {
        Layer &layer = n_layers[layerNum];
        Layer &prevLayer = n_layers[layerNum - 1];
        
        for(unsigned n = 0; n < layer.size() - 1; ++n)
        {
            layer[n].updateInputWeights(prevLayer);
        }
    
    }
}

void Net::getResults(vector<double> &outputValues)const
{
    outputValues.clear();
    
    for(unsigned n = 0; n < n_layers.back().size() - 1; ++n)
    {
        outputValues.push_back(n_layers.back()[n].getOutputValue());
    }
}

// --------------- End Neural Network ------------------


// --------------- Start Neuron ------------------

Neuron::Neuron(unsigned numOutputs, unsigned myIndex)
{
    // initialize random number generator
    srand(static_cast<unsigned>(time(NULL)));
    
    for(unsigned c = 0; c < numOutputs; ++c)
    {
        // Each Neuron will have Connections Structure
        this->n_outputWeights.push_back(Connections());
        
        // Each Parameter/Weight will initialized with random value between 0 - 1
        this->n_outputWeights.back().weight = randomWeight();
    }
    
    n_myIndex = myIndex;
}

double Neuron::randomWeight(void)
{
    return rand() / static_cast<double>(RAND_MAX);
}

void Neuron::feedForward(const Layer &prevLayer)
{
    // output value = activationFunction(sum(xi*wi))
    double sum  = 0.0;
    
    // sum the previous layers outputs (which are our inouts)
    // Include the Bias Neuron from the previous Layer
    
    for(unsigned n = 0; n < prevLayer.size(); ++n)
    {
        sum += prevLayer[n].getOutputValue() *
        prevLayer[n].n_outputWeights[n_myIndex].weight;
        
    }
    n_outputValue = activationFunction(sum);
}

double Neuron::activationFunction(double sum)
{
    // tanh - Hyberbolic tangent Function  -1 ... 1
    return tanh(sum);
}

double Neuron::activationFunctionDerivative(double x)
{
    // tanh derivative approximation
    return 1.0 - x * x;
}


void Neuron::calculateOutputGradients(double targetVal)
{
    double delta = targetVal - n_outputValue;
    gradient = delta * activationFunction(n_outputValue);
}

void Neuron::calculateHiddenGradients(const Layer &nextLayer)
{
    double dow = sumDOW(nextLayer);
    gradient = dow * activationFunctionDerivative(n_outputValue);
}

double Neuron::sumDOW(const Layer &nextLayer) const
{
    double sum = 0.0;
    // Sum our contributions of the errors at the nodes we feed
    for(unsigned n = 0; n < nextLayer.size() - 1; ++n)
    {
        sum += n_outputWeights[n].weight * nextLayer[n].gradient;
    }
    
    return sum;
}

double Neuron::eta = 0.15;
double Neuron::alpha = 0.5;

void Neuron::updateInputWeights(Layer &prevLayer)
{
    // The weights to be updated are in the Connection container
    // in the neurons in the preceding layer
    for(unsigned n = 0; n < prevLayer.size(); ++n)
    {
        Neuron &neuron = prevLayer[n];
        double oldDeltaWeight = neuron.n_outputWeights[n_myIndex].deltaWeight;
        
        double newDeltaWeight =
        // Individual input magnified by the gradient and train rate
        eta
        * neuron.getOutputValue()
        * gradient
        * alpha
        * oldDeltaWeight;
        
        neuron.n_outputWeights[n_myIndex].deltaWeight = newDeltaWeight;
        neuron.n_outputWeights[n_myIndex].weight += newDeltaWeight;
    }
}

// --------------- End Neuron ------------------
