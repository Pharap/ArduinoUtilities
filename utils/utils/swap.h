#pragma once

// For size_t
#include <stddef.h>

#include "move.h"

namespace utils
{
	/// @brief Swaps two objects.
	/// @details Compatible with move semantics.
	/// @param left, right The objects to be swapped.
	template<typename Type>
	void swap(Type & left, Type & right)
	{
		auto object = move(left);
		left = move(right);
		right = move(object);
	}

	/// @brief Swaps two arrays.
	/// @param left, right The arrays to be swapped.
	template<typename Type, size_t size>
	void swap(Type (&left)[size], Type (&right)[size])
	{
		using utils::swap;

		for(size_t index = 0; index < size; ++index)
			swap(left[index], right[index]);
	}
}