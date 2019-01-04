#include "CostFunction.h"

namespace NeuralNetwork2
{
	networkType CostFunction::evaluate(std::vector<networkType> expectedOutputs, std::vector<networkType> actualOutputs)
	{
		unsigned int batchSize = expectedOutputs.size();

		networkType cost = 0;
		networkType unit;

		for(unsigned int x = 0; x < batchSize; x++)
		{
			unit = (expectedOutputs[x] - actualOutputs[x]);
			cost += unit * unit;
		}

		cost /= 2 * batchSize;

		return cost;
	}

	networkType CostFunction::evaluateDerivative(std::vector<networkType> expectedOutputs, std::vector<networkType> actualOutputs)
	{
		unsigned int batchSize = expectedOutputs.size();
		networkType costDerivative = 0;

		for(unsigned int x = 0; x < batchSize; x++)
		{
			costDerivative -= (expectedOutputs[x] - actualOutputs[x]);
		}

		return costDerivative;
	}

	networkType CostFunction::evaluate(networkType expectedOutput, networkType activation)
	{
		networkType unit = expectedOutput - activation;
		return 0.5 * unit * unit;
	}

	networkType CostFunction::evaluateDerivative(networkType expectedOutput, networkType activation)
	{
		return activation - expectedOutput;
	}
}
