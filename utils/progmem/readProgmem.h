#pragma once

// For size_t
#include <stddef.h>

#include "../utils/Array.h"
#include "details/read_details.h"

namespace progmem
{
	/// @brief
	/// Reads an object from progmem.
	/// The underlying implementation uses templates to attempt to reduce progmem usage.
	///
	/// @note
	/// The object type must be trivially copyable.
	///
	/// @warning
	/// There is no way to verify that the provided reference refers to an object in progmem.
	/// Calling this function on an object that is not stored in progmem
	/// will result in <strong>undefined behaviour</strong>.
	template<typename Type>
	Type readProgmem(const Type & object)
	{
		return details::read_progmem(object);
	}

	/// @brief
	/// Reads an array from progmem.
	///
	/// @note
	/// The object type must be trivially copyable.
	///
	/// @warning
	/// There is no way to verify that the provided reference refers to an array in progmem.
	/// Calling this function on an object that is not stored in progmem
	/// will result in <strong>undefined behaviour</strong>.
	///
	/// @todo
	/// This function is presently unimplemented.
	template<typename Type, size_t size>
	utils::Array<Type, size> readProgmem(const Type (& array)[size]) = delete;
}