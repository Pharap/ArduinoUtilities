#pragma once

// For size_t
#include <stddef.h>

#include "../utils/Array.h"
#include "details/update_details.h"

namespace eeprom
{
	/// @brief
	/// Writes an object to eeprom, avoiding a write if the old value is identical.
	///
	/// @details
	/// This function avoids writing bytes if the existing value in eeprom
	/// already has the same value, to prevent unnecessary wear on eeprom.
	///
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
	void writeEeprom(Type & destination, const Type & source)
	{
		details::update_eeprom(destination, source);
	}

	/// @brief
	/// Writes an array to eeprom, avoiding a write if the old value is identical.
	///
	/// @details
	/// This function avoids writing bytes if the existing value in eeprom
	/// already has the same value, to prevent unnecessary wear on eeprom.
	///
	/// @note
	/// The object type must be trivially copyable.
	///
	/// @warning
	/// There is no way to verify that the provided reference refers to an array in eeprom.
	/// Calling this function on an object that is not stored in eeprom
	/// will result in <strong>undefined behaviour</strong>.
	template<typename Type, size_t size>
	void writeEeprom(Type (& destination)[size], const Type (& source)[size])
	{
		details::update_eeprom(destination, source);
	}
}