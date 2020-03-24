#pragma once

// For size_t, ptrdiff_t
#include <stddef.h>

// For PSTR
#include <avr/pgmspace.h>

// For utils::size
#include "../utils.h"

#include "ProgmemReference.h"
#include "ProgmemPointer.h"
#include "ProgmemNullString.h"

// Used by Arduino
// Redeclaring here shouldn't cause an issue,
// and ought to be less hassle than requiring <WString.h>
class __FlashStringHelper;

/// @brief
/// A macro for creating an inline @ref ProgmemString, similar to the Arduino `F` macro
#define PROGMEM_STRING(string_literal) \
	::progmem::ProgmemString(PSTR(string_literal), ::utils::size(string_literal))

namespace progmem
{
	/// @brief
	/// Represents a length-prefixed, possibly null-terminated string stored in progmem.
	/// Behaves similarly to a @slink{progmem::ProgmemArray<char>, ProgmemArray<char>},
	/// but with added enhancements.
	///
	/// @warning
	/// Experimental class, may be removed.
	/// Use only to test and provide feedback.
	class ProgmemString
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

		/// @brief
		/// The type used as an iterator to character.
		using iterator = pointer;

		/// @brief
		/// The type used as an iterator to read-only character.
		using const_iterator = const_pointer;

	private:
		const value_type * string;
		size_type string_size;

	public:
		/// @brief
		/// Constructs a @slink{progmem::ProgmemString,ProgmemString}
		/// that refers to the provided array.
		///
		/// @warning
		/// There is no way of verifying that the provided reference refers to an array in progmem.
		/// It is thus possible to construct an invalid @ref ProgmemString,
		/// which can lead to <strong>undefined behaviour</strong>.
		template<size_t capacity>
		constexpr ProgmemString(const value_type (& array)[capacity]) :
			string(&array[0]), string_size(capacity)
		{
		}

		/// @brief
		/// Constructs a @ref ProgmemString from a null pointer.
		constexpr ProgmemString(decltype(nullptr)) :
			string(nullptr), string_size(0)
		{
		}

		/// @brief
		/// Constructs a @ref ProgmemString with the provided pointer and size.
		///
		/// @note
		/// This constructor is marked explicit to ensure that the conversion from
		/// a raw pointer to a @ref ProgmemString is clearly visible.
		///
		/// @warning
		/// There is no way of verifying that the provided pointer points to an object in progmem.
		/// It is thus possible to construct an invalid @ref ProgmemString,
		/// which can lead to <strong>undefined behaviour</strong>.
		constexpr explicit ProgmemString(const value_type * pointer, size_type size) :
			string(pointer), string_size(size)
		{
		}

		/// @brief
		/// Constructs a @ref ProgmemString from the result of an Arduino `F` macro and a size.
		///
		/// @warning
		/// There is no way of verifying that the provided pointer points to an object in progmem.
		/// It is thus possible to construct an invalid @ref ProgmemString,
		/// which can lead to <strong>undefined behaviour</strong>.
		explicit ProgmemString(const __FlashStringHelper * pointer, size_type size) :
			string(reinterpret_cast<const value_type *>(pointer)), string_size(size)
		{
		}

		/// @brief
		/// Returns `true` if the string is empty, returns `false` otherwise.
		constexpr bool empty() const noexcept
		{
			return ((this->string == nullptr) || (this->string_size == 0));
		}

		/// @brief
		/// Returns the number of characters in the string.
		/// This includes the null character if present.
		///
		/// @attention
		/// Prefer to use @slink{utils::size(const Container &),`utils::size(string)`}
		/// rather than @slink{progmem::ProgmemString::size(),`string.size()`}.
		constexpr size_type size() const noexcept
		{
			return this->string_size;
		}

		/// @brief
		/// Returns a read-only reference to the first character of the string.
		constexpr const_reference front() const
		{
			return const_reference(&this->string[0]);
		}

		/// @brief
		/// Returns a read-only reference to the last character of the string.
		constexpr const_reference back() const
		{
			return const_reference(&this->string[this->size() - 1]);
		}

		/// @brief
		/// Returns a pointer to the first character of the underlying null-terminated string.
		constexpr const_pointer data() const noexcept
		{
			return const_pointer(&this->string[0]);
		}

		/// @brief
		/// Returns a read-only reference to the character at the specified index.
		///
		/// @warning
		/// This function does no bounds checking.
		/// <em>Providing an `index` that is greater than or equal to
		/// @slink{progmem::ProgmemString::size(),`string.size()`}
		/// will result in a buffer overrun, which is <strong>undefined behaviour</strong></em>.
		constexpr const_reference operator[](size_type index) const
		{
			return const_reference(&this->string[index]);
		}

		/// @brief
		/// Returns a const iterator pointing to the first character of the string.
		constexpr const_iterator begin() const noexcept
		{
			return const_pointer(&this->string[0]);
		}

		/// @brief
		/// Returns a const iterator pointing to the first character of the string.
		constexpr const_iterator cbegin() const noexcept
		{
			return const_pointer(&this->string[0]);
		}

		/// @brief
		/// Returns a past-the-end const iterator pointing beyond the last character of the string.
		///
		/// @warning
		/// Do not attempt to dereference the returned iterator.
		/// _Doing so will result in <strong>undefined behaviour</strong>_.
		constexpr const_iterator end() const noexcept
		{
			return const_pointer(&this->string[this->string_size]);
		}

		/// @brief
		/// Returns a past-the-end const iterator pointing beyond the last character of the string.
		///
		/// @warning
		/// Do not attempt to dereference the returned iterator.
		/// _Doing so will result in <strong>undefined behaviour</strong>_.
		constexpr const_iterator cend() const noexcept
		{
			return const_pointer(&this->string[this->string_size]);
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
		/// Returns the underlying raw pointer as an Arduino flash string helper.
		///
		/// @details
		/// This operator is permitted to be implicit specifically to allow
		/// @ref ProgmemString to be used with Arduino's `Print` class without
		/// any extra boilerplate.
		/// E.g. `Serial.print(string)` where `string` is an
		/// object of type @ref ProgmemString.
		operator const __FlashStringHelper *() const
		{
			return reinterpret_cast<const __FlashStringHelper*>(this->string);
		}

		/// @brief
		/// Creates an equivalent @ref ProgmemNullString.
		///
		/// @details
		/// This operator is marked explicit to prevent accidental usage
		/// and to discourage excessive intentional usage.
		///
		/// @note
		/// Converting to a @ref ProgmemNullString discards the precomputed size.
		/// (I.e. this is a _narrowing_ operation.)
		/// Computing the size of a @ref ProgmemNullString is an `O(n)` operation,
		/// hence converting @ref ProgmemNullString is discouraged.
		constexpr explicit operator ProgmemNullString() const
		{
			return ProgmemNullString(this->string);
		}
	};

	/// @brief
	/// Tests whether two @sref{progmem::ProgmemString,ProgmemStrings} are equal.
	///
	/// @details
	/// Returns `true` if the pointers are equal, otherwise returns `false`.
	constexpr bool operator ==(const ProgmemString & left, const ProgmemString & right)
	{
		return ((static_cast<const char *>(left) == static_cast<const char *>(right)) && (left.size() == right.size()));
	}

	/// @brief
	/// Tests whether a @ref ProgmemString is null.
	///
	/// @details
	/// Returns `true` if the pointer is null, otherwise returns `false`.
	constexpr bool operator ==(const ProgmemString & left, decltype(nullptr))
	{
		return (static_cast<const char *>(left) == nullptr);
	}

	/// @brief
	/// Tests whether two @sref{progmem::ProgmemString,ProgmemStrings} are not equal.
	///
	/// @details
	/// Returns `true` if the pointers are not equal, otherwise returns `false`.
	constexpr bool operator !=(const ProgmemString & left, const ProgmemString & right)
	{
		return ((static_cast<const char *>(left) != static_cast<const char *>(right)) || (left.size() != right.size()));
	}

	/// @brief
	/// Tests whether a @ref ProgmemString is not null.
	///
	/// @details
	/// Returns `true` if the pointer is not null, otherwise returns `false`.
	constexpr bool operator !=(const ProgmemString & left, decltype(nullptr))
	{
		return (static_cast<const char *>(left) != nullptr);
	}
}