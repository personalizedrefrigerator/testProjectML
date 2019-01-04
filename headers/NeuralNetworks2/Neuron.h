#pragma once

#include <vector>
#include "NetworkTypes.h"

namespace NeuralNetwork2
{
	enum class ActivationType { SIGMOID };
	struct NeuronData
	{
		std::vector<networkType> weights;
		std::vector<networkType> velocities;

		ActivationType activationFunction = ActivationType::SIGMOID;
		//networkType learningRate = 0.1;

		networkType error = 0.0;

		NeuronData(NeuronData&& other);
		const NeuronData& operator=(NeuronData&& other);
		const NeuronData& operator=(const NeuronData& other);
		NeuronData() {};
	};

	class Neuron
	{
	public:
		NeuronData data;
		Neuron() {};
		Neuron(const Neuron& other) { data = other.data; };
		Neuron(Neuron&& other);
		Neuron& operator=(Neuron& other) { data = other.data; return *this;};
		~Neuron() {};

		networkType getOutput(const std::vector<networkType>& input);
		networkType getOutputDerivative(const std::vector<networkType>& input);
		networkType getWeightedInput(const std::vector<networkType>& input);
		inline bool fillWeights(int maxWeights);
	};
}
