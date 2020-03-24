#pragma once

// For size_t
#include <stddef.h>

// For uint16_t, int16_t, uint32_t, int32_t
#include <stdint.h>

// For memcpy_P, pgm_read_byte, ..., pgm_read_ptr
#include <avr/pgmspace.h>

namespace progmem
{
	namespace details
	{
		// Default behaviour - a type-safe wrapper for memcpy_P
		template<typename Type, size_t size = sizeof(Type)>
		struct read_progmem_helper
		{
			static Type read_progmem(const Type & object)
			{
				Type result;
				static_cast<void>(memcpy_P(&result, &object, sizeof(Type)));
				return result;
			}
		};

		// Special behaviour for single-byte types
		template<typename Type>
		struct read_progmem_helper<Type, 1>
		{
			static Type read_progmem(const Type & object)
			{
				Type result;
				const auto result_pointer = reinterpret_cast<unsigned char *>(&result);
				*result_pointer = pgm_read_byte(&object);
				return result;
			}
		};

		// A type-safe read function for general objects
		template<typename Type>
		Type read_progmem(const Type & object)
		{
			return read_progmem_helper<Type>::read_progmem(object);
		}

		// A type-safe read function for arrays,
		// intentionally deleted until it's implemented
		template<typename Type, size_t size>
		void read_progmem(const Type (& array)[size]) = delete;

		// A type-safe read function for pointers
		template<typename Type>
		const Type * read_progmem(const Type * const & object)
		{
			return static_cast<const Type *>(pgm_read_ptr(&object));
		}

		//
		// Type-safe read functions,
		// wrapping all the common 'pgm_read' functions.
		//

		inline char read_progmem(const char & object)
		{
			return pgm_read_byte(&object);
		}

		inline uint8_t read_progmem(const uint8_t & object)
		{
			return pgm_read_byte(&object);
		}

		inline int8_t read_progmem(const int8_t & object)
		{
			return pgm_read_byte(&object);
		}

		inline uint16_t read_progmem(const uint16_t & object)
		{
			return pgm_read_word(&object);
		}

		inline int16_t read_progmem(const int16_t & object)
		{
			return pgm_read_word(&object);
		}

		inline uint32_t read_progmem(const uint32_t & object)
		{
			return pgm_read_dword(&object);
		}

		inline int32_t read_progmem(const int32_t & object)
		{
			return pgm_read_dword(&object);
		}

		inline float read_progmem(const float & object)
		{
			return pgm_read_float(&object);
		}
	}
}