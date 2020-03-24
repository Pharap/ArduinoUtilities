#pragma once

// For size_t, ptrdiff_t
#include <stddef.h>

// For utils::size
#include "../utils.h"

#include "ProgmemReference.h"
#include "ProgmemPointer.h"

// Used by Arduino
// Redeclaring here shouldn't cause an issue,
// and ought to be less hassle than requiring <WString.h>
class __FlashStringHelper;

namespace progmem
{
	/// @brief
	/// Represents a null-terminated string stored in progmem.
	/// Behaves similarly to a @slink{progmem::ProgmemPointer<char>, ProgmemPointer<char>},
	/// but with added enhancements.
	///
	/// @warning
	/// Experimental class, may be removed.
	/// Use only to test and provide feedback.
	class ProgmemNullString
	{
	public:
		/// @brief
		/// The character type used by this string.
		using value_type = char;

		/// @brief
		/// The unsigned integer type used for measuring the size of the array.
		/// Also used to represent array indices.
		using size_type = size_t;

		/// @brief
		/// The signed integer type used for measuring the distance between characters.
		using difference_type = ptrdiff_t;

		/// @brief
		/// The type that represents a reference to a character.
		using reference = ProgmemReference<value_type>;

		/// @brief
		/// The type that represents a reference to a read-only character.
		using const_reference = ProgmemReference<const value_type>;

		/// @brief
		/// The type that represents a pointer to a character.
		using pointer = ProgmemPointer<value_type>;

		/// @brief
		/// The type that represents a pointer to a read-only character.
		using const_pointer = ProgmemPointer<const value_type>;

	private:
		const value_type * string;

	public:
		/// @brief
		/// Constructs a @ref ProgmemNullString from a null pointer.
		constexpr ProgmemNullString(decltype(nullptr)) :
			string(nullptr)
		{
		}

		/// @brief
		/// Constructs a @ref ProgmemNullString with the provided pointer.
		///
		/// @note
		/// This constructor is marked explicit to ensure that the conversion from
		/// a raw pointer to a @ref ProgmemNullString is clearly visible.
		///
		/// @warning
		/// There is no way of verifying that the provided pointer points to an object in progmem.
		/// It is thus possible to construct an invalid @ref ProgmemNullString,
		/// which can lead to <strong>undefined behaviour</strong>.
		constexpr explicit ProgmemNullString(const value_type * pointer) :
			string(pointer)
		{
		}

		/// @brief
		/// Constructs a @ref ProgmemNullString from the result of an Arduino `F` macro.
		///
		/// @warning
		/// There is no way of verifying that the provided pointer points to an object in progmem.
		/// It is thus possible to construct an invalid @ref ProgmemNullString,
		/// which can lead to <strong>undefined behaviour</strong>.
		explicit ProgmemNullString(const __FlashStringHelper * pointer) :
			string(reinterpret_cast<const value_type *>(pointer))
		{
		}

		/// @brief
		/// Constructs a @slink{progmem::ProgmemNullString,ProgmemNullString}
		/// that refers to the provided array.
		///
		/// @warning
		/// There is no way of verifying that the provided reference refers to an array in progmem.
		/// It is thus possible to construct an invalid @ref ProgmemNullString,
		/// which can lead to <strong>undefined behaviour</strong>.
		template<size_t capacity>
		constexpr ProgmemNullString(const value_type (& array)[capacity]) :
			string(&array[0])
		{
		}

		/// @brief
		/// Returns the number of characters in the string, excluding the null terminator.
		///
		/// @warning
		/// This function has `O(n)` complexity.
		/// Use it sparingly, and cache the result.
		size_type size() const noexcept
		{
			size_type result = 0;

			for(auto current = this->string; pgm_read_byte(current) != '\0'; ++current)
				++result;

			return result;
		}

		/// @brief
		/// Returns a read-only reference to the character at the specified index.
		///
		/// @warning
		/// This function does no bounds checking.
		/// <em>Providing an `index` that is greater than or equal to
		/// @slink{progmem::ProgmemNullString::size(),`string.size()`}
		/// will result in a buffer overrun, which is <strong>undefined behaviour</strong></em>.
		constexpr const_reference operator[](size_type index) const
		{
			return const_reference(&this->string[index]);
		}

		/// @brief
		/// Returns the underlying raw pointer.
		///
		/// @details
		/// This operator is marked explicit to prevent accidental usage
		/// and to discourage excessive intentional usage.
		constexpr explicit operator const value_type *() const
		{
			return this->string;
		}

		/// @brief
		/// Creates an equivalent
		/// @slink{progmem::ProgmemPointer<char>, ProgmemPointer<char>}
		///
		/// @details
		/// This operator is marked explicit to prevent accidental usage
		/// and to discourage excessive intentional usage.
		constexpr explicit operator pointer() const
		{
			return pointer(this->string);
		}

		/// @brief
		/// Creates an equivalent
		/// @slink{progmem::ProgmemPointer<const char>, ProgmemPointer<const char>}
		///
		/// @details
		/// This operator is marked explicit to prevent accidental usage
		/// and to discourage excessive intentional usage.
		constexpr explicit operator const_pointer() const
		{
			return const_pointer(this->string);
		}

		/// @brief
		/// Returns the underlying raw pointer as an Arduino flash string helper.
		///
		/// @details
		/// This operator is permitted to be implicit specifically to allow
		/// @ref ProgmemNullString to be used with Arduino's `Print` class without
		/// any extra boilerplate.
		/// E.g. `Serial.print(string)` where `string` is an
		/// object of type @ref ProgmemNullString.
		operator const __FlashStringHelper *() const
		{
			return reinterpret_cast<const __FlashStringHelper*>(this->string);
		}
	};

	/// @brief
	/// Tests whether two @sref{progmem::ProgmemNullString,ProgmemNullStrings} are equal.
	///
	/// @details
	/// Returns `true` if the pointers are equal, otherwise returns `false`.
	constexpr bool operator ==(const ProgmemNullString & left, const ProgmemNullString & right)
	{
		return ((static_cast<const char *>(left) == static_cast<const char *>(right)) && (left.size() == right.size()));
	}

	/// @brief
	/// Tests whether a @ref ProgmemNullString is null.
	///
	/// @details
	/// Returns `true` if the pointer is null, otherwise returns `false`.
	constexpr bool operator ==(const ProgmemNullString & left, decltype(nullptr))
	{
		return (static_cast<const char *>(left) == nullptr);
	}

	/// @brief
	/// Tests whether two @sref{progmem::ProgmemNullString,ProgmemNullStrings} are not equal.
	///
	/// @details
	/// Returns `true` if the pointers are not equal, otherwise returns `false`.
	constexpr bool operator !=(const ProgmemNullString & left, const ProgmemNullString & right)
	{
		return ((static_cast<const char *>(left) != static_cast<const char *>(right)) || (left.size() != right.size()));
	}

	/// @brief
	/// Tests whether a @ref ProgmemNullString is not null.
	///
	/// @details
	/// Returns `true` if the pointer is not null, otherwise returns `false`.
	constexpr bool operator !=(const ProgmemNullString & left, decltype(nullptr))
	{
		return (static_cast<const char *>(left) != nullptr);
	}
}