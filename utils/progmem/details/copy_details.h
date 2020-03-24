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
		struct copy_progmem_helper
		{
			static Type * copy_progmem(Type & destination, const Type & source)
			{
				return static_cast<Type *>(memcpy_P(&destination, &source, sizeof(Type)));
			}
		};

		// Special behaviour for single-byte types
		template<typename Type>
		struct copy_progmem_helper<Type, 1>
		{
			static Type * copy_progmem(Type & destination, const Type & source)
			{
				const auto result_pointer = reinterpret_cast<unsigned char *>(&destination);
				*result_pointer = pgm_read_byte(&source);
				return &destination;
			}
		};

		// Special behaviour for pointer types
		// Note: sizeof(Type *) is 2 on AVR, but may be larger on other systems
		template<typename Type, size_t size>
		struct copy_progmem_helper<Type *, size>
		{
			static Type * copy_progmem(Type * & destination, const Type * const & source)
			{
				destination = reinterpret_cast<Type *>(pgm_read_ptr(&source));
				return &destination;
			}
		};

		// A type-safe copy function for general objects
		template<typename Type>
		Type * copy_progmem(Type & destination, const Type & source)
		{
			return copy_progmem_helper<Type>::copy_progmem(destination, source);
		}

		// A type-safe copy function for arrays
		template<typename Type, size_t size>
		Type * copy_progmem(Type (& destination)[size], const Type (& source)[size])
		{
			return static_cast<Type *>(memcpy_P(&destination[0], &source[0], sizeof(Type) * size));
		}
	}
}