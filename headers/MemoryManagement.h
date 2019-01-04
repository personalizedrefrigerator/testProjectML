#pragma once

namespace MemoryManagement
{
	typedef unsigned int sizeType;

	template <typename T>
	void safeFree(T* pointer);

	template <typename T>
	void safeCUDAFree(T* pointer);

	template<typename T>
	void copyArrays(T* sourceArray, T* destinationArray, sizeType arrayLengths);

	template<typename T>
	void transferMemoryToCUDA(T* source, T* destination, sizeType sizeOfTransfer);

	template<typename T>
	void transferMemoryFromCUDA(T* source, T* destination, sizeType sizeOfTransfer);

	void allocateMemory(void** pointer, unsigned int size, bool isCUDAMemory);
}
