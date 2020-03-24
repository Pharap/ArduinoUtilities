#pragma once

// For size_t
#include <stddef.h>

// For uint16_t, int16_t, uint32_t, int32_t
#include <stdint.h>

// For eeprom_write_block, eeprom_write_byte, ..., eeprom_write_ptr
#include <avr/eeprom.h>

namespace eeprom
{
	namespace details
	{
		// Default behaviour - a type-safe wrapper for eeprom_write_block
		template<typename Type, size_t size = sizeof(Type)>
		struct write_eeprom_helper
		{
			static void write_eeprom(Type & destination, const Type & source)
			{
				eeprom_write_block(&source, &destination, sizeof(Type));
			}
		};

		// Special behaviour for single-byte types
		template<typename Type>
		struct write_eeprom_helper<Type, 1>
		{
			static void write_eeprom(Type & destination, const Type & source)
			{
				const auto source_pointer = reinterpret_cast<unsigned char *>(&source);
				eeprom_write_byte(&destination, *source_pointer);
			}
		};

		// A type-safe copy function for general objects
		template<typename Type>
		void write_eeprom(Type & destination, const Type & source)
		{
			write_eeprom_helper<Type>::write_eeprom(destination, source);
		}

		// A type-safe copy function for arrays
		template<typename Type, size_t size>
		void write_eeprom(Type (& destination)[size], const Type (& source)[size])
		{
			eeprom_write_block(&source[0], &destination[0], sizeof(Type) * size);
		}

		//
		// Type-safe updeat functions,
		// wrapping all the common 'eeprom_write' functions.
		//

		inline void write_eeprom(char & object, char value)
		{
			// Note: using reinterpret cast to convert to uint8_t ought to
			// be safe as long as uint8_t is an alias for unsigned char.
			eeprom_write_byte(reinterpret_cast<uint8_t *>(&object), value);
		}

		inline void write_eeprom(uint8_t & object, uint8_t value)
		{
			eeprom_write_byte(&object, value);
		}

		inline void write_eeprom(int8_t & object, int8_t value)
		{
			// Note: using reinterpret cast to convert to uint8_t ought to
			// be safe as long as uint8_t is an alias for unsigned char.
			eeprom_write_byte(reinterpret_cast<uint8_t *>(&object), value);
		}

		inline void write_eeprom(uint16_t & object, uint16_t value)
		{
			eeprom_write_word(&object, value);
		}

		inline void write_eeprom(int16_t & object, int16_t value)
		{
			// Note: using reinterpret cast like this is dangerous and likely to cause bugs.
			eeprom_write_word(reinterpret_cast<uint16_t *>(&object), value);
		}

		inline void write_eeprom(uint32_t & object, uint32_t value)
		{
			eeprom_write_dword(&object, value);
		}

		inline void write_eeprom(int32_t & object, int32_t value)
		{
			// Note: using reinterpret cast like this is dangerous and likely to cause bugs.
			eeprom_write_dword(reinterpret_cast<uint32_t *>(&object), value);
		}

		inline void write_eeprom(float & object, float value)
		{
			eeprom_write_float(&object, value);
		}
	}
}