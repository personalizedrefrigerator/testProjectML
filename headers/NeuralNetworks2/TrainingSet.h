#pragma once

#include <vector>
#include "NetworkTypes.h"

namespace NeuralNetwork2
{
	struct TrainingSet
	{
		std::vector<networkType> inputs;
		std::vector<networkType> outputs;
	};
}
