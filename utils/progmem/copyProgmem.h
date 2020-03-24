#pragma once

// For size_t
#include <stddef.h>

#include "../utils/Array.h"
#include "details/copy_details.h"

namespace progmem
{
	/// @brief
	/// Copies an object from progmem into an object in RAM.
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
	void copyProgmem(Type & destination, const Type & source)
	{
		static_cast<void>(details::copy_progmem(destination, source));
	}

	/// @brief
	/// Copies an array from progmem into an array in RAM.
	///
	/// @note
	/// The object type must be trivially copyable.
	///
	/// @warning
	/// There is no way to verify that the provided reference refers to an object in progmem.
	/// Calling this function on an object that is not stored in progmem
	/// will result in <strong>undefined behaviour</strong>.
	template<typename Type, size_t size>
	void copyProgmem(Type (& destination)[size], const Type (& source)[size])
	{
		static_cast<void>(details::copy_progmem(destination, source));
	}
}