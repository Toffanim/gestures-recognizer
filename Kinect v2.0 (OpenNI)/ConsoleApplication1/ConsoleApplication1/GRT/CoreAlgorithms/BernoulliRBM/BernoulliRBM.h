
/**
 @file
 @author  Nicholas Gillian <ngillian@media.mit.edu>
 @version 1.0
 
 @brief This class implements a Bernoulli Restricted Boltzmann machine.
 
 */

/**
 GRT MIT License
 Copyright (c) <2012> <Nicholas Gillian, Media Lab, MIT>
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 and associated documentation files (the "Software"), to deal in the Software without restriction,
 including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
 subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all copies or substantial
 portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
 LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef GRT_BERNOULLI_RBM_HEADER
#define GRT_BERNOULLI_RBM_HEADER

#include "../../Util/MatrixDouble.h"
#include "../../CoreModules/MLBase.h"

namespace GRT{

class BernoulliRBM : public MLBase{

public:
    BernoulliRBM(const UINT numHiddenUnits = 100,const UINT maxNumEpochs = 1000,const double learningRate = 1,const double learningRateUpdate = 1,const double momentum = 0.5,const bool useScaling = true,const bool randomiseTrainingOrder = true);
  
    virtual ~BernoulliRBM();
    
    /**
     This is the main prediction interface for referenced VectorDouble data.  It propagates the input data up through the RBM.  
     The RBM should be trained first before you use this function.  
     The size of the input data must match the number of visible units.
     
     @param VectorDouble &inputData: a reference to the input data that will be used to train the RBM model
     @param VectorDouble &outputData: a reference to the output data that will be used to train the RBM model
     @return returns true if the prediction was successful, false otherwise
     */
    bool predict_(VectorDouble &inputData,VectorDouble &outputData);
    
    /**
     This is the main prediction interface for referenced VectorDouble data.  It propagates the input data up through the RBM.
     The RBM should be trained first before you use this function.
     The size of the input data must match the number of visible units.
     
     @param VectorDouble &inputData: a reference to the input data that will be used to train the RBM model
     @param VectorDouble &outputData: a reference to the output data that will be used to train the RBM model
     @return returns true if the prediction was successful, false otherwise
     */
    bool predict_(MatrixDouble &inputData,MatrixDouble &outputData,const UINT rowIndex);
    
    /**
     This is the main training interface for referenced MatrixDouble data.
     
     @param MatrixDouble &trainingData: a reference to the training data that will be used to train the RBM model
     @return returns true if the model was successfully trained, false otherwise
     */
    virtual bool train_(MatrixDouble &data);
    
    /**
     This function will reset the model (i.e. set all values back to default settings). If you want to completely clear the model
     (i.e. clear any learned weights or values) then you should use the clear function.
     
     @return returns true if the instance was reset succesfully, false otherwise
     */
    virtual bool reset();
    
    /**
     This function will completely clear the RBM instance, removing any trained model and setting all the base variables to their default values.
     
     @return returns true if the instance was cleared succesfully, false otherwise
     */
    virtual bool clear();
    
    /**
     This saves the trained model to a file.
     
     @param string filename: the name of the file to save the model to
     @return returns true if the model was saved successfully, false otherwise
     */
    virtual bool saveModelToFile(string filename) const;
    
    /**
     This saves the trained model to a file.
     
     @param fstream &file: a reference to the file the model will be saved to
     @return returns true if the model was saved successfully, false otherwise
     */
    virtual bool saveModelToFile(fstream &file) const;
    
    /**
     This loads a trained model from a file.
     
     @param string filename: the name of the file to load the model from
     @return returns true if the model was loaded successfully, false otherwise
     */
    virtual bool loadModelFromFile(string filename);
    
    /**
     This loads a trained model from a file.
     
     @param fstream &file: a reference to the file the model will be loaded from
     @return returns true if the model was loaded successfully, false otherwise
     */
    virtual bool loadModelFromFile(fstream &file);
    
    bool reconstruct(const VectorDouble &input,VectorDouble &output);
    
    virtual bool print() const;
    
    bool getRandomizeWeightsForTraining() const;
    UINT getNumVisibleUnits() const;
    UINT getNumHiddenUnits() const;
    const MatrixDouble& getWeights() const;
    bool setNumHiddenUnits(const UINT numHiddenUnits);
    bool setMomentum(const double momentum);
    bool setLearningRateUpdate(const double learningRateUpdate);
    bool setRandomizeWeightsForTraining(const bool randomizeWeightsForTraining);
    bool setBatchSize(const UINT batchSize);
    bool setBatchStepSize(const UINT batchStepSize);
    
protected:
    bool loadLegacyModelFromFile(fstream &file);
    
    inline double sigmoid(const double &x) {
        return 1.0 / (1.0 + exp(-x));
    }
    
    inline double sigmoidRandom(const double &x){
        return (1.0 / (1.0 + exp(-x)) > rand.getRandomNumberUniform(0.0,1.0)) ? 1.0 : 0.0;
    }
    
    UINT binomial(const UINT n,const double p);

    bool randomizeWeightsForTraining;
    UINT numVisibleUnits;
    UINT numHiddenUnits;
    UINT batchSize;
    UINT batchStepSize;
    double momentum;
    double learningRateUpdate;
    MatrixDouble weightsMatrix;
    VectorDouble visibleLayerBias;
    VectorDouble hiddenLayerBias;
    VectorDouble ph_mean;
    VectorDouble ph_sample;
    VectorDouble nv_means;
    VectorDouble nv_samples;
    VectorDouble nh_means;
    VectorDouble nh_samples;
    vector<MinMax> ranges;
    Random rand;
    
    struct BatchIndexs{
        UINT startIndex;
        UINT endIndex;
        UINT batchSize;
    };
    typedef struct BatchIndexs BatchIndexs;
    
};
    
} //End of namespace GRT

#endif //GRT_BERNOULLI_RBM_HEADER

