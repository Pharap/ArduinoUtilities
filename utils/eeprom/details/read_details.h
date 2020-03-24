#pragma once

// For size_t
#include <stddef.h>

// For uint16_t, int16_t, uint32_t, int32_t
#include <stdint.h>

// For eeprom_read_block, eeprom_read_byte, ..., eeprom_read_ptr
#include <avr/eeprom.h>

namespace eeprom
{
	namespace details
	{
		// Default behaviour - a type-safe wrapper for eeprom_read_block
		template<typename Type, size_t size = sizeof(Type)>
		struct read_eeprom_helper
		{
			static Type read_eeprom(const Type & object)
			{
				Type result;
				eeprom_read_block(&result, &object, sizeof(Type));
				return result;
			}
		};

		// Special behaviour for single-byte types
		template<typename Type>
		struct read_eeprom_helper<Type, 1>
		{
			static Type read_eeprom(const Type & object)
			{
				Type result;
				const auto result_pointer = reinterpret_cast<unsigned char *>(&result);
				*result_pointer = eeprom_read_byte(&object);
				return result;
			}
		};

		// A type-safe read function for general objects
		template<typename Type>
		Type read_eeprom(const Type & object)
		{
			return read_eeprom_helper<Type>::read_eeprom(object);
		}

		// A type-safe read function for arrays,
		// intentionally deleted until it's implemented
		template<typename Type, size_t size>
		void read_eeprom(const Type (& array)[size]) = delete;

		// A type-safe read function for pointers
		template<typename Type>
		const Type * read_eeprom(const Type * const & object)
		{
			return static_cast<const Type *>(eeprom_read_ptr(&object));
		}

		//
		// Type-safe read functions,
		// wrapping all the common 'eeprom_read' functions.
		//

		inline char read_eeprom(const char & object)
		{
			// Note: using reinterpret cast to convert to uint8_t ought to
			// be safe as long as uint8_t is an alias for unsigned char.
			return eeprom_read_byte(reinterpret_cast<const uint8_t *>(&object));
		}

		inline uint8_t read_eeprom(const uint8_t & object)
		{
			return eeprom_read_byte(&object);
		}

		inline int8_t read_eeprom(const int8_t & object)
		{
			// Note: using reinterpret cast to convert to uint8_t ought to
			// be safe as long as uint8_t is an alias for unsigned char.
			return eeprom_read_byte(reinterpret_cast<const uint8_t *>(&object));
		}

		inline uint16_t read_eeprom(const uint16_t & object)
		{
			return eeprom_read_word(&object);
		}

		inline int16_t read_eeprom(const int16_t & object)
		{
			// Note: using reinterpret cast like this is dangerous and likely to cause bugs.
			return eeprom_read_word(reinterpret_cast<const uint16_t *>(&object));
		}

		inline uint32_t read_eeprom(const uint32_t & object)
		{
			return eeprom_read_dword(&object);
		}

		inline int32_t read_eeprom(const int32_t & object)
		{
			// Note: using reinterpret cast like this is dangerous and likely to cause bugs.
			return eeprom_read_dword(reinterpret_cast<const uint32_t *>(&object));
		}

		inline float read_eeprom(const float & object)
		{
			return eeprom_read_float(&object);
		}
	}
}