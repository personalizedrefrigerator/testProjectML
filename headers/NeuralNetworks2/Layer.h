#pragma once

#include "Neuron.h"
#include "NetworkTypes.h"
#include "CostFunction.h"

namespace NeuralNetwork2
{
	class Layer
	{
	private:
		CostFunction cost;
	public:
		double friction = 0.4;
		double learningRate = 0.7;
		double normalizeK = 0.99;
		unsigned int neuronsSize;
		std::vector<Neuron> neurons;


		// For backpropagation.
		std::vector<networkType> error;
		std::vector<networkType> activations;

		Layer(unsigned int numberOfNeurons);
		Layer(unsigned int neuronsCount, CostFunction costFunction) : cost(costFunction) { neuronsSize = neuronsCount; neurons.resize(neuronsCount); };
		Layer() { neuronsSize = 0; };

		std::vector<networkType> getOutputs(const std::vector<networkType>& inputs);
		void storeActivations(const std::vector<networkType>& inputs);
		void backpropagateError(Layer& nextLayer);
		void backpropagateError(const std::vector<networkType>& expectedOutputs, const std::vector<networkType>& inputs);
		void gradientDescent(const std::vector<networkType>& previousLayerActivations);
	};
}
