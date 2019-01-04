#pragma once

#include <vector>

#include "NetworkTypes.h"
#include "TrainingSet.h"

namespace NeuralNetwork2
{
	enum class CostFunctionTypes { QUADRATIC_COST, CROSS_ENTROPY_COST };

	class CostFunction
	{
	private:
		CostFunctionTypes type = CostFunctionTypes::QUADRATIC_COST;
	public:
		CostFunction() {};
		CostFunction(const CostFunction& other) : type(other.type) {};
		CostFunction(CostFunction&& other) { type = other.type; };

		networkType evaluate(std::vector<networkType> expectedOutputs, std::vector<networkType> actualOutputs);
		networkType evaluateDerivative(std::vector<networkType> expectedOutputs, std::vector<networkType> actualOutputs);

		networkType evaluate(networkType expectedOutput, networkType actualOutput);
		networkType evaluateDerivative(networkType expectedOutput, networkType actualOutput);
	};
}
