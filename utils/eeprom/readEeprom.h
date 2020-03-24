#pragma once

// For size_t
#include <stddef.h>

#include "../utils/Array.h"
#include "details/read_details.h"

namespace eeprom
{
	/// @brief
	/// Reads an object from eeprom.
	///
	/// @details
	/// The underlying implementation uses templates to attempt to reduce progmem usage.
	///
	/// @note
	/// The object type must be trivially copyable.
	///
	/// @warning
	/// There is no way to verify that the provided reference refers to an object in eeprom.
	/// Calling this function on an object that is not stored in eeprom
	/// will result in <strong>undefined behaviour</strong>.
	template<typename Type>
	Type readEeprom(const Type & object)
	{
		return details::read_eeprom(object);
	}

	/// @brief
	/// Reads an array from eeprom.
	///
	/// @note
	/// The object type must be trivially copyable.
	///
	/// @warning
	/// There is no way to verify that the provided reference refers to an array in eeprom.
	/// Calling this function on an object that is not stored in eeprom
	/// will result in <strong>undefined behaviour</strong>.
	///
	/// @todo
	/// This function is presently unimplemented.
	template<typename Type, size_t size>
	utils::Array<Type, size> readEeprom(const Type (& array)[size]) = delete;
}