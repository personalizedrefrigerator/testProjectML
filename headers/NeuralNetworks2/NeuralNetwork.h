#pragma once

#include <vector>
#include "Neuron.h"
#include "TrainingSet.h"
#include "Layer.h"
#include "NetworkTypes.h"

namespace NeuralNetwork2
{
	class NeuralNetwork
	{
	public:
		std::vector<Layer> layers;

		NeuralNetwork(std::initializer_list<unsigned int> neuronCounts);

		void train(TrainingSet& trainingData) noexcept;
		void train(std::vector<TrainingSet>& trainingData) noexcept;
		std::vector<networkType> getOutputs(std::vector<networkType> inputs) noexcept;
		void storeOutputs(std::vector<networkType>& inputs) noexcept;

		void setLearningRate(networkType learningRate);
		void multiplyLearningRate(networkType multiplyBy);
	};
}
