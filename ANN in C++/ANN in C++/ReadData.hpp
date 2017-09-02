//
//  ReadData.hpp
//  ANN in C++
//
//  Created by Vitali Mueller on 02/09/2017.
//  Copyright © 2017 Vitali Mueller. All rights reserved.
//

#ifndef ReadData_hpp
#define ReadData_hpp

#include <stdio.h>
#include <cstdlib>
#include <fstream>
#include <sstream>

using namespace std;

class TrainingData
{
public:
    TrainingData(const string filename);
    bool isEof(void) { return m_trainingDataFile.eof(); }
    void getTopology(vector<unsigned> &topology);
    
    // Returns the number of input values read from the file:
    unsigned getNextInputs(vector<double> &inputVals);
    unsigned getTargetOutputs(vector<double> &targetOutputVals);
    
private:
    ifstream m_trainingDataFile;
};


#endif /* ReadData_hpp */
