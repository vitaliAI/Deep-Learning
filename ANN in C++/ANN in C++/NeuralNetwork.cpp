//
//  NeuralNetwork.cpp
//  ANN in C++
///Users/vmueller/Documents/Software Projects/Machine Learning/ANN in C++/ANN in C++/NeuralNetwork.hpp
//  Created by Vitali Mueller on 19/08/2017.
//  Copyright © 2017 Vitali M/Users/vmueller/Documents/Software Projects/Machine Learning/ANN in C++/ANN in C++/NeuralNetwork.hppueller. All rights reserved.
//

#include "NeuralNetwork.hpp"

Net::Net(const vector<double> topology)
{
    // We need to know how many total layers
    unsigned numLayers = static_cast<unsigned>(topology.size());
    for(unsigned layerNum = 0; layerNum < numLayers; ++layerNum)
    {
        // Create a new Layer with private Data Type Layer
        // Layer is a Vector of Neuron types
        this->n_layers.push_back(Layer());
        
        // Now we need to loop through the layer and add Neurons plus additional Bias Neuron
        for(unsigned neuronNum = 0; neuronNum <= topology[layerNum]; ++neuronNum)
        {
            this->n_layers.back().push_back(Neuron());
        }
    }
}
