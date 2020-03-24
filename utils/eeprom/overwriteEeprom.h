#pragma once

// For size_t
#include <stddef.h>

#include "../utils/Array.h"
#include "details/write_details.h"

namespace eeprom
{
	/// @brief
	/// Writes an object to eeprom, even if the old value is identical.
	///
	/// @details
	/// This function always performs a write,
	/// even if the existing value in eeprom already has the same value,
	/// which can cause unnecessary wear on eeprom.
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
	void overwriteEeprom(Type & destination, const Type & source)
	{
		details::write_eeprom(destination, source);
	}

	/// @brief
	/// Writes an array to eeprom, even if the old value is identical.
	///
	/// @details
	/// This function always performs a write,
	/// even if the existing value in eeprom already has the same value,
	/// which can cause unnecessary wear on eeprom.
	///
	/// @note
	/// The object type must be trivially copyable.
	///
	/// @warning
	/// There is no way to verify that the provided reference refers to an array in eeprom.
	/// Calling this function on an object that is not stored in eeprom
	/// will result in <strong>undefined behaviour</strong>.
	template<typename Type, size_t size>
	void overwriteEeprom(Type (& destination)[size], const Type (& source)[size])
	{
		details::write_eeprom(destination, source);
	}
}