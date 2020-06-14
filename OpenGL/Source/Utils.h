#pragma once
#include <stdlib.h>

#include <ctime>
#include <type_traits>

inline float GetNCV(int i_Value)
{
	return static_cast<float>(i_Value)/ 255.0f;
}
template<typename T>
T RandomInRange(T i_MinValue, T i_MaxValue)
{
	T randValue;
	if (std::is_same<T, int>::value)
	{
		randValue = rand() % i_MaxValue + i_MinValue;
	}
	return randValue;
}
