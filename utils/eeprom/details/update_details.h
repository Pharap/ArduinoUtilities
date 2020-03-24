#pragma once

// For size_t
#include <stddef.h>

// For uint16_t, int16_t, uint32_t, int32_t
#include <stdint.h>

// For eeprom_update_block, eeprom_update_byte, ..., eeprom_update_ptr
#include <avr/eeprom.h>

namespace eeprom
{
	namespace details
	{
		// Default behaviour - a type-safe wrapper for eeprom_update_block
		template<typename Type, size_t size = sizeof(Type)>
		struct update_eeprom_helper
		{
			static void update_eeprom(Type & destination, const Type & source)
			{
				eeprom_update_block(&source, &destination, sizeof(Type));
			}
		};

		// Special behaviour for single-byte types
		template<typename Type>
		struct update_eeprom_helper<Type, 1>
		{
			static void update_eeprom(Type & destination, const Type & source)
			{
				const auto source_pointer = reinterpret_cast<unsigned char *>(&source);
				eeprom_update_byte(&destination, *source_pointer);
			}
		};

		// A type-safe copy function for general objects
		template<typename Type>
		void update_eeprom(Type & destination, const Type & source)
		{
			update_eeprom_helper<Type>::update_eeprom(destination, source);
		}

		// A type-safe copy function for arrays
		template<typename Type, size_t size>
		void update_eeprom(Type (& destination)[size], const Type (& source)[size])
		{
			eeprom_update_block(&source[0], &destination[0], sizeof(Type) * size);
		}

		//
		// Type-safe updeat functions,
		// wrapping all the common 'eeprom_update' functions.
		//

		inline void update_eeprom(char & object, char value)
		{
			// Note: using reinterpret cast to convert to uint8_t ought to
			// be safe as long as uint8_t is an alias for unsigned char.
			eeprom_update_byte(reinterpret_cast<uint8_t *>(&object), value);
		}

		inline void update_eeprom(uint8_t & object, uint8_t value)
		{
			eeprom_update_byte(&object, value);
		}

		inline void update_eeprom(int8_t & object, int8_t value)
		{
			// Note: using reinterpret cast to convert to uint8_t ought to
			// be safe as long as uint8_t is an alias for unsigned char.
			eeprom_update_byte(reinterpret_cast<uint8_t *>(&object), value);
		}

		inline void update_eeprom(uint16_t & object, uint16_t value)
		{
			eeprom_update_word(&object, value);
		}

		inline void update_eeprom(int16_t & object, int16_t value)
		{
			// Note: using reinterpret cast like this is dangerous and likely to cause bugs.
			eeprom_update_word(reinterpret_cast<uint16_t *>(&object), value);
		}

		inline void update_eeprom(uint32_t & object, uint32_t value)
		{
			eeprom_update_dword(&object, value);
		}

		inline void update_eeprom(int32_t & object, int32_t value)
		{
			// Note: using reinterpret cast like this is dangerous and likely to cause bugs.
			eeprom_update_dword(reinterpret_cast<uint32_t *>(&object), value);
		}

		inline void update_eeprom(float & object, float value)
		{
			eeprom_update_float(&object, value);
		}
	}
}