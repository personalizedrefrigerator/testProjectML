/*
 * NeuralNetworkRenderer.cpp
 *
 *  Created on: Jul 6, 2018
 */

#include "NeuralNetworkRenderer.h"
#include <sstream>
#include <chrono>
#include <cmath>
#include <cstring>

NeuralNetworkRenderer::NeuralNetworkRenderer()
{
	textEdit.setTextSize(1, 3);
	textEdit.getContent() = "Test a value in the network: ";
	/*textEdit.setNewLineCallback([&](std::string& text)
			{
				std::size_t separator = text.find(": ", 0);
				std::size_t firstLine = text.find('\n');

				if(firstLine == -1)
				{
					firstLine = text.size();
					text += '\n';
				}

				if(separator >= 0)
				{
					std::string endSection = text.substr(separator + 2, firstLine);
					text = text.substr(0, separator + 1);

					NeuralNetwork2::networkType input = std::stod(endSection);
					text += "\nOutput is " + std::to_string(network.getOutputs(std::vector<NeuralNetwork2::networkType>(input))[0]);
				}
			});*/

	progressGraph.setMaxY(6);
	progressGraph2.setMaxY(1.0);
	progressGraph3.setColors(Color(0, 100, 100), Color(0, 0, 0));
}

void NeuralNetworkRenderer::render(PixelSetter* pixelSetter, int width, int height)
{
	count++;

	pixelSetter->setColor(255, 0, 255);

	if(scaledPixelSetter == nullptr)
	{
		scaledPixelSetter = new TransformedPixelSetter(pixelSetter);
		scaledPixelSetter->transformMatrix.setAt(0.25, 0, 1);
		scaledPixelSetter->transformMatrix.setAt(0.5, 1, 1);
	}
	scaledPixelSetter->setPixelSetter(pixelSetter);

	double theta = 0.0;

	std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
	unsigned long currentTime = (std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch())).count();

	theta = std::sin(currentTime/1000.0) * 3.14159 / 20;

	scaledPixelSetter->transformMatrix.toIdentity();

	Matrix<double, 2, 2> rotateMatrix;
	MatrixControl::toRotationMatrix(theta, rotateMatrix);

	Matrix<double, 2, 2> scaleMatrix;
	scaleMatrix.toIdentity();
	scaleMatrix.setAt((sin(currentTime / 400.0) + 1) / 10, 1, 0);
	scaleMatrix.setAt(0.05, 0, 1);


	scaledPixelSetter->transformMatrix *= rotateMatrix;
	scaledPixelSetter->transformMatrix *= scaleMatrix;

	std::stringstream stringStream;
	stringStream << "Neural network renderer...\n";
	stringStream << "Theta: " << theta << '\n';
	stringStream << "Time (s): " << currentTime << '\n';

	if(!keyData.handledKey)
	{
		keyData.handledKey = true;
		textEdit.handleKeyChange(keyData.lastKey);
	}

	stringStream << std::endl << keyData.lastKey;

	NeuralNetwork2::networkType output, expected;
	std::vector<NeuralNetwork2::networkType> inputs;
	inputs.resize(3);

	std::vector<double>& data = progressGraph2.getData();
	std::vector<double>& dataExpected = progressGraph3.getData();

	double error = 0.0;
	double errorCount = 0.0;

	for(unsigned int i = 0; i < 100; i++)
	{
		NeuralNetwork2::networkType a = ((i % 100) * 0.9);


		inputs[0] = (a / 100.0);
		inputs[1] = (i / 300.0 - 0.1);
		inputs[2] = (theta + 0.3);

		NeuralNetwork2::networkType b = a / 100.0;


		expected = ((sin(b * 6.28) + 1.0) / 2.0 - (theta - 0.3));

		NeuralNetwork2::TrainingSet set;
		set.inputs = inputs;
		set.outputs.push_back(expected);

		network.train(set);


		output = network.getOutputs(inputs)[0];




		data[i % 100] = output;
		dataExpected[i % 100] = expected;

		if(expected != 0)
		{
			error += output / expected;
		}
		else
		{
			error += (output + 0.001) / (expected + 0.001);
		}

		errorCount++;
	}

	error /= errorCount;

	stringStream << std::endl << "Error: " << static_cast<int>((error - 1.0) * 100) << "%\n -- " << output << "/" << expected << "\nCount: " << count;


	for(unsigned int i = 0; i < 400; i++)
	{
		NeuralNetwork2::networkType a = ((i % 100) * 0.9);


		inputs[0] = (a / 100.0);
		inputs[1] = (i / 300.0 - 0.1);
		inputs[2] = (theta + 0.3);

		NeuralNetwork2::networkType b = a / 100.0;

		expected = ((sin(b * 6.28) + 1.0) / 2.0 - (theta - 0.3));

		NeuralNetwork2::TrainingSet set;
		set.inputs = inputs;
		set.outputs.push_back(expected);

		network.train(set);
	}

	progressGraph.addPoint(error - 1);



	scaledPixelSetter->clear(250);

	//subRenderer.render(pixelSetter, width, 20);
	scaledPixelSetter->setColor(0, 0, 255);

	textRenderer.drawWrapped(stringStream.str(), 0, 20, *scaledPixelSetter, 2, 3, width);


	scaledPixelSetter->setColor(150, 150, 0);
	textEdit.render(*scaledPixelSetter, 3, height*2/3, width * 9 / 10);

	progressGraph.render(*pixelSetter, 0, height * 2/3, width, height/8);
	progressGraph2.render(*pixelSetter, 0, height * 1/3, width, height/8);
	progressGraph3.render(*pixelSetter, 0, height * 1/3, width, height/8);

}
