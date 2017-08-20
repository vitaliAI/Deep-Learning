//
//  NeuralNetwork.cpp
//  ANN in C++
///Users/vmueller/Documents/Software Projects/Machine Learning/ANN in C++/ANN in C++/NeuralNetwork.hpp
//  Created by Vitali Mueller on 19/08/2017.
//  Copyright © 2017 Vitali M/Users/vmueller/Documents/Software Projects/Machine Learning/ANN in C++/ANN in C++/NeuralNetwork.hppueller. All rights reserved.
//

#include "NeuralNetwork.hpp"
#include <iostream>
#include <stdlib.h>
#include <random>


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
            this->n_layers.back().push_back(Neuron(numberOutputs));
            
            
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

// --------------- End Neural Network ------------------


// --------------- Start Neuron ------------------

Neuron::Neuron(unsigned numOutputs)
{
    // initialize random number generator
    srand(time(NULL));
    
    for(unsigned c = 0; c < numOutputs; ++c)
    {
        // Each Neuron will have Connections Structure
        this->n_outputWeights.push_back(Connections());
        
        // Each Parameter/Weight will initialized with random value between 0 - 1
        this->n_outputWeights.back().weight = randomWeight();
    }
}

double Neuron::randomWeight(void)
{
    return rand() / static_cast<double>(RAND_MAX);
}


// --------------- End Neuron ------------------
