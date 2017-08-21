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
}


// --------------- End Neuron ------------------
