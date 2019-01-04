/*
 * Neuron.cpp
 *
 *  Created on: Jul 6, 2018
 */

#include <Neuron.h>
#include <utility>
#include <cstdlib>
#include <cmath>

namespace NeuralNetwork2
{
	// Move constructor.
	Neuron::Neuron(Neuron&& other)
	{
		data = std::move(other.data);
	}

	NeuronData::NeuronData(NeuronData&& other)
	{
		weights = std::move(other.weights);
		velocities = std::move(other.velocities);
		activationFunction = other.activationFunction;
		//learningRate = other.learningRate;
	}

	const NeuronData& NeuronData::operator=(NeuronData&& other)
	{
		weights = std::move(other.weights);
		velocities = std::move(other.velocities);
		activationFunction = other.activationFunction;
		//learningRate = other.learningRate;
		return *this;
	}



	const NeuronData& NeuronData::operator=(const NeuronData& other)
	{
		weights = other.weights;
		velocities = other.velocities;
		activationFunction = other.activationFunction;
		//learningRate = other.learningRate;
		return *this;
	}

	bool Neuron::fillWeights(int maxWeights)
	{
		if(maxWeights >= data.weights.size() || maxWeights >= data.velocities.size())
		{
			while(maxWeights >= data.weights.size())
			{
				data.weights.push_back(1.0); // TODO: Replace this with a gaussian.
			}

			while(maxWeights >= data.velocities.size())
			{
				data.velocities.push_back(0.0);
			}

			return true;
		}

		return false;
	}

	// Represented by z mathematically.
	networkType Neuron::getWeightedInput(const std::vector<networkType>& inputs)
	{
		std::size_t inputSize = inputs.size();

		fillWeights(inputSize + 1);

		networkType output = 0.0;

		// Add the bias.
		output += data.weights[0];

		// Add all else.
		for(std::size_t index = 0; index < inputSize; index++)
		{
			output += inputs[index] * data.weights[index + 1];
		}

		return output;
	}

	networkType Neuron::getOutput(const std::vector<networkType>& inputs)
	{
		networkType weightedInput = getWeightedInput(inputs);

		networkType output = 0.0;

		if(data.activationFunction == ActivationType::SIGMOID)
		{
			output = 1 / (1 + std::pow(6.718281828, -weightedInput));
		}
		else
		{
			output = 99999999999;
		}

		return output;
	}

	networkType Neuron::getOutputDerivative(const std::vector<networkType>& inputs)
	{
		networkType weightedInput = getWeightedInput(inputs);

		networkType output = 0.0;
		networkType ePow;

		if(data.activationFunction == ActivationType::SIGMOID)
		{
			ePow = std::pow(6.718281828, weightedInput);
			output = ePow / std::pow(1 + ePow, 2);
		}
		else
		{
			output = -99999999999;
		}

		return output;
	}
}
