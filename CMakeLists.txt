# To build makefiles, cd to build and cmake ../ -DCMAKE_LINKER=nvcc -DCMAKE_BUILD_TYPE=Release

cmake_minimum_required(VERSION 3.1) # Minimum CMake version
project(TestProjectML) # Set the project name
set(CMAKE_CXX_STANDARD 11)

#find_package(CUDA REQUIRED) # Find CUDA
find_package(X11 REQUIRED)

# Where header files are.
include_directories(./headers)
include_directories(./headers/NeuralNetworks2)
include_directories(${X11_INCLUDE_DIR})

# Set compilation flags.
#set(CUDA_NVCC_FLAGS "${CUDA_NVCC_FLAGS}; -G -g -O0 -gencode arch=compute_61,code=compute_61")

# A list of all source file names in the root dierctory.
set(SOURCE_FILE_NAMES "BaseRenderer.cpp;Color.cpp;EmptyRenderer.cpp;Grapher.cpp;InvertedPixelSetter.cpp;Matrix.cpp;NeuralNetworkRenderer.cpp;PixelSetter.cpp;PixelSetterWrapper.cpp;PixelWindow.cpp;TextDrawer.cpp;TextEditor.cpp;TransformedPixelSetter.cpp;X11PixelSetter.cpp;NeuralNetworks2/CostFunction.cpp;NeuralNetworks2/Layer.cpp;NeuralNetworks2/NeuralNetwork.cpp;NeuralNetworks2/Neuron.cpp;NeuralNetworks2/Neuron_test.cpp;NeuralNetworks2/TrainingSet.cpp")

# Set the starting source directory
set(SOURCE_DIR "source")
set(SOURCES "main.cpp")

foreach(CURRENT ${SOURCE_FILE_NAMES})
    set(SOURCES "${SOURCES};${SOURCE_DIR}/${CURRENT}")
endforeach()


# Add the sources
add_executable(TestProjectML main.cpp ${SOURCES})

target_link_libraries(TestProjectML ${X11_LIBRARIES})
#target_link_libraries(TestProjectML ${CUDA_LIBRARIES})
#target_link_libraries(TestProjectML "--cudart static --relocatable-device-code=false -gencode arch=compute_61,code=compute_61 -gencode arch=compute_61,code=sm_61")
