#include "Layer.h"
#include <iostream>

namespace NeuralNetwork2
{
	Layer::Layer(unsigned int numberOfNeurons)
	{
		neurons.resize(numberOfNeurons);
		neuronsSize = numberOfNeurons;
	}

	std::vector<networkType> Layer::getOutputs(const std::vector<networkType>& inputs)
	{
		std::vector<networkType> result;
		result.resize(neuronsSize);
		unsigned int neuronsSize = neurons.size();

		for(unsigned int neuronIndex = 0; neuronIndex < neuronsSize; neuronIndex++)
		{
			result[neuronIndex] = neurons[neuronIndex].getOutput(inputs);
		}

		return result;
	}

	void Layer::storeActivations(const std::vector<networkType>& inputs)
	{
		activations = getOutputs(inputs);
	}

	// Assumes the error in previousLayer has been calculated.
	void Layer::backpropagateError(Layer& previousLayer)
	{
		unsigned int previousLayerNeuronsSize = previousLayer.neurons.size();
		unsigned int otherIndex;
		networkType currentError;

		error.resize(neuronsSize);

		for(unsigned int neuronIndex = 0; neuronIndex < neuronsSize; neuronIndex++)
		{
			currentError = 0;
			// For every weight/error in the next layer,
			for(otherIndex = 0; otherIndex < previousLayerNeuronsSize; otherIndex++)
			{
				Neuron& otherNeuron = previousLayer.neurons[otherIndex];

				currentError += otherNeuron.data.weights[neuronIndex + 1] // The weight connecting to this neuron from the other
				                            * previousLayer.error[otherIndex] * otherNeuron.getOutputDerivative(activations);
			}

			error[neuronIndex] = currentError;
		}
	}

	void Layer::backpropagateError(const std::vector<networkType>& expectedOutputs, const std::vector<networkType>& inputs)
	{
		unsigned int outputsCount = expectedOutputs.size();

		error.resize(outputsCount);

		// Store the last layer's error.
		for(unsigned int neuronIndex = 0; neuronIndex < outputsCount; neuronIndex++)
		{
			error.at(neuronIndex) = cost.evaluateDerivative(expectedOutputs[neuronIndex], activations[neuronIndex])
									* neurons[neuronIndex].getOutputDerivative(inputs);
		}
	}

	void Layer::gradientDescent(const std::vector<networkType>& previousLayerActivations)
	{
		unsigned int neuronCount = neuronsSize;//n.size()eurons.size();
		unsigned int velocitiesCount, velocitiesIndex;
		networkType currentError, currentDerivative;
		//networkType * velocity;
		//networkType * weight;

		for(unsigned int neuronIndex = 0; neuronIndex < neuronCount; neuronIndex ++)
		{
			velocitiesCount = neurons[neuronIndex].data.velocities.size();
			currentError = error[neuronIndex];

			for(velocitiesIndex = 0; velocitiesIndex < velocitiesCount; velocitiesIndex++)
			{
				// If not a bias,
				if(velocitiesIndex > 0)
				{
					currentDerivative = previousLayerActivations[velocitiesIndex - 1] * currentError;
				} // If the bias,
				else
				{
					currentDerivative = currentError;
				}

				// Update the velocities,
				networkType& velocity = neurons[neuronIndex].data.velocities[velocitiesIndex];

				velocity = friction * (velocity) - learningRate * currentDerivative;

				// Update the weights,
				networkType& weight = neurons[neuronIndex].data.weights[velocitiesIndex];
				weight = (weight) * normalizeK + (velocity);
			}
		}
	}
}
