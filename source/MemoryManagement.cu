/*
 * MemoryManagement.cpp
 *
 *  Created on: Jul 1, 2018
 */

#include <MemoryManagement.h>
#include <unistd.h>

namespace MemoryManagement
{
	template<typename T>
	void safeFree(T* pointer)
	{
		if(pointer != nullptr && pointer != 0)
		{
			pointer->~T();
			free(pointer);
		}
	}

	template<typename T>
	void safeCUDAFree(T* pointer)
	{
		if(pointer != nullptr && pointer != 0)
		{
			pointer->~T();
			cudaFree(pointer);
		}
	}


	template<typename T>
	__host__ __device__
	void copyArrays(T* source, T* destination, sizeType arrayLengths)
	{
		sizeType index;

		for(index = 0; index < arrayLengths; index++)
		{
			destination[index] = source[index];
		}
	}

	template<typename T>
	void transferMemoryToCUDA(T* source, T* destination, sizeType sizeOfTransfer)
	{
		cudaMemcpy(destination, source, sizeOfTransfer, cudaMemcpyHostToDevice);
	}

	template<typename T>
	void transferMemoryFromCUDA(T* source, T* destination, sizeType sizeOfTransfer)
	{
		cudaMemcpy(destination, source, sizeOfTransfer, cudaMemcpyDeviceToHost);
	}

	void allocateMemory(void** pointer, unsigned int size, bool isCUDA)
	{
		if(isCUDA)
		{
			cudaMalloc(pointer, size);
		}
		else
		{
			(*pointer) = malloc(size);
		}
	}

	template void safeFree<float>(float*);
	template void safeFree<unsigned int>(unsigned int*);

	template void safeCUDAFree<float>(float*);
	template void safeCUDAFree<unsigned int>(unsigned int*);

	template void copyArrays<unsigned int>(unsigned int*, unsigned int*, sizeType);
	template void copyArrays<float>(float*, float*, sizeType);

	template void transferMemoryToCUDA<unsigned int>(unsigned int*, unsigned int*, sizeType);
	template void transferMemoryToCUDA<float>(float*, float*, sizeType);
}
