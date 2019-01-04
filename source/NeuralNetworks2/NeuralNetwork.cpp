#include "NeuralNetwork.h"
#include <utility>
#include <iostream>

namespace NeuralNetwork2
{
	NeuralNetwork::NeuralNetwork(std::initializer_list<unsigned int> neuronCounts)
	{
		layers.reserve(neuronCounts.size());

		std::cout << "INIT neural network." << std::endl;

		unsigned int layerIndex = 0;

		for(unsigned int layerCount : neuronCounts)
		{
			layers.push_back(Layer(layerCount));
			layerIndex++;
		}
	}

	// For on-line learning. Use only a single input and output.
	void NeuralNetwork::train(TrainingSet& trainingData) noexcept
	{
		int layerIndex;

		// FEED FORWARD.
		storeOutputs(trainingData.inputs);

		// BACKPROPAGATE THE ERROR.
		unsigned int layersCount = layers.size();

		if(layersCount == 0)
		{
			return;
		}

		// Start in the last layer, and backpropagate the error.
		layers[layersCount - 1].backpropagateError(trainingData.outputs, layers[layersCount - 2].activations);

		for(layerIndex = layersCount - 2; layerIndex >= 0; layerIndex--)
		{
			layers[layerIndex].backpropagateError(layers[layerIndex + 1]);
		}

		// GRADIENT DESCENT.
		if(layersCount > 0)
		{
			layers[0].gradientDescent(trainingData.inputs);
		}

		for(layerIndex = 1; layerIndex < layersCount; layerIndex++)
		{
			layers[layerIndex].gradientDescent(layers[layerIndex - 1].activations);
		}
	}

	// Tell each layer to return its outputs.
	std::vector<networkType> NeuralNetwork::getOutputs(std::vector<networkType> inputs) noexcept
	{
		std::vector<networkType> lastOutputs = std::move(inputs);

		unsigned int numberOfLayers = layers.size();

		for(unsigned int layerIndex = 0; layerIndex < numberOfLayers; layerIndex++)
		{
			lastOutputs = layers[layerIndex].getOutputs(lastOutputs);
		}

		return lastOutputs;
	}

	void NeuralNetwork::storeOutputs(std::vector<networkType>& inputs) noexcept
	{
		// This is a pointer to STACK memory, so should not be deleted.
		std::vector<networkType> * lastOutputs = &inputs;

		unsigned int numberOfLayers = layers.size();

		for(unsigned int layerIndex = 0; layerIndex < numberOfLayers; layerIndex++)
		{
			layers[layerIndex].storeActivations(*lastOutputs);
			lastOutputs = &(layers[layerIndex].activations);
		}
	}

	void NeuralNetwork::setLearningRate(networkType setTo)
	{
		unsigned int numberOfLayers = layers.size();

		for(unsigned int layerIndex = 0; layerIndex < numberOfLayers; layerIndex++)
		{
			layers[layerIndex].learningRate = setTo;
		}
	}


	void NeuralNetwork::multiplyLearningRate(networkType changeBy)
	{
		unsigned int numberOfLayers = layers.size();

		for(unsigned int layerIndex = 0; layerIndex < numberOfLayers; layerIndex++)
		{
			layers[layerIndex].learningRate *= changeBy;
		}
	}
}
