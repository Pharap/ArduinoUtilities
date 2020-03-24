#pragma once

#include "EepromReference.h"

namespace eeprom
{
	// Predeclare as a precaution
	template<typename Type>
	class EepromPointer;

	/// @brief
	/// Represents a pointer to an object stored in eeprom.
	///
	/// @details
	/// The intent of this class is twofold:  
	/// * Primarily, the intent of this class is to provide a means of
	/// differentiating between a pointer to an object in eeprom
	/// and a pointer to an obejct stored elsewhere.  
	/// * Secondarily, the intent of this class is to enable the use of
	/// standard pointer syntax with objects stored in eeprom.  
	///
	/// @note
	/// This class may be used as an contiguous iterator for
	/// containers with contiguous elements stored in eeprom.
	template<typename Type>
	class EepromPointer
	{
	public:
		/// @brief
		/// The type of the object referred to by this pointer.
		using value_type = Type;

	private:
		value_type * pointer;

	public:
		/// @brief
		/// Constructs a @ref EepromPointer that refers to the provided object.
		///
		/// @warning
		/// There is no way of verifying that the provided reference refers to an object in eeprom.
		/// It is thus possible to construct an invalid @ref EepromPointer,
		/// which can lead to <strong>undefined behaviour</strong>.
		constexpr EepromPointer(value_type & object) :
			pointer(&object)
		{
		}

		/// @brief
		/// Constructs a @ref EepromPointer that takes on the value of the provided pointer.
		///
		/// @note
		/// This constructor is marked explicit to ensure that the conversion from
		/// a raw pointer to a @ref EepromPointer is clearly visible,
		/// and to prevent confusion between this overload
		/// and @ref EepromPointer(value_type &).
		///
		/// @warning
		/// There is no way of verifying that the provided pointer points to an object in eeprom.
		/// It is thus possible to construct an invalid @ref EepromPointer,
		/// which can lead to <strong>undefined behaviour</strong>.
		constexpr explicit EepromPointer(value_type * pointer) :
			pointer(pointer)
		{
		}

		/// @brief
		/// Converts this pointer to an @ref EepromPointer<const value_type>
		constexpr operator EepromPointer<const value_type>() const
		{
			return EepromPointer<const value_type>(this->pointer);
		}

		/// @brief
		/// Returns the underlying raw pointer.
		///
		/// @details
		/// This operator is marked explicit to prevent accidental usage
		/// and to discourage excessive intentional usage.
		constexpr explicit operator value_type *() const
		{
			return this->pointer;
		}

		/// @brief
		/// Returns the underlying raw pointer.
		///
		/// @details
		/// This operator is marked explicit to prevent accidental usage
		/// and to discourage excessive intentional usage.
		constexpr explicit operator const value_type *() const
		{
			return this->pointer;
		}

		/// @brief
		/// Dereferences the @ref EepromPointer, creating a @ref EepromReference,
		/// which may be implicitly converted to a @ref value_type object.
		EepromReference<value_type> operator *() const
		{
			return EepromReference<value_type>(this->pointer);
		}

		/// @brief
		/// Pre-increments the @ref EepromPointer.
		///
		/// @attention
		/// Prefer to use
		/// @slink{EepromPointer::operator++(),`++pointer`} over
		/// @slink{EepromPointer::operator++(int),`pointer++`} because
		/// @slink{EepromPointer::operator++(int),`pointer++`}
		/// has implicit overhead due to the creation of a temporary object.
		///
		/// @warning
		/// Do not attempt to use this operator unless the pointer points to an object in an array.
		/// Attempting to increment a pointer that does not point to an array element
		/// is likely to invalidate the pointer, which can lead to <strong>undefined behaviour</strong>.
		/// 
		/// @note
		/// The exception to the above warning is the a `EepromPointer<char>`,
		/// `EepromPointer<unsigned char>` or `EepromPointer<std::byte>` that points to a
		/// [trivially copyable](https://en.cppreference.com/w/cpp/named_req/TriviallyCopyable) type,
		/// in which case the pointer may be used to examine the
		/// [object representation](https://en.cppreference.com/w/cpp/language/object#Object_representation_and_value_representation)
		/// of the object in eeprom, as per the rules of
		/// [type aliasing](https://en.cppreference.com/w/cpp/language/reinterpret_cast#Type_aliasing)
		EepromPointer & operator++()
		{
			++this->pointer;
			return *this;
		}

		/// @brief
		/// Post-increments the @ref EepromPointer.
		///
		/// @attention
		/// Prefer to use
		/// @slink{EepromPointer::operator++(),`++pointer`} over
		/// @slink{EepromPointer::operator++(int),`pointer++`} because
		/// @slink{EepromPointer::operator++(int),`pointer++`}
		/// has implicit overhead due to the creation of a temporary object.
		///
		/// @warning
		/// Do not attempt to use this operator unless the pointer points to an object in an array.
		/// Attempting to increment a pointer that does not point to an array element
		/// is likely to invalidate the pointer, which can lead to <strong>undefined behaviour</strong>.
		/// 
		/// @note
		/// The exception to the above warning is the a `EepromPointer<char>`,
		/// `EepromPointer<unsigned char>` or `EepromPointer<std::byte>` that points to a
		/// [trivially copyable](https://en.cppreference.com/w/cpp/named_req/TriviallyCopyable) type,
		/// in which case the pointer may be used to examine the
		/// [object representation](https://en.cppreference.com/w/cpp/language/object#Object_representation_and_value_representation)
		/// of the object in eeprom, as per the rules of
		/// [type aliasing](https://en.cppreference.com/w/cpp/language/reinterpret_cast#Type_aliasing)
		EepromPointer operator++(int)
		{
			const auto result = *this;
			this->operator++();
			return result;
		}

		/// @brief
		/// Pre-decrements the @ref EepromPointer.
		///
		/// @attention
		/// Prefer to use
		/// @slink{EepromPointer::operator--(),`--pointer`} over
		/// @slink{EepromPointer::operator--(int),`pointer--`} because
		/// @slink{EepromPointer::operator--(int),`pointer--`}
		/// has implicit overhead due to the creation of a temporary object.
		///
		/// @warning
		/// Do not attempt to use this operator unless the pointer points to an object in an array.
		/// Attempting to increment a pointer that does not point to an array element
		/// is likely to invalidate the pointer, which can lead to <strong>undefined behaviour</strong>.
		/// 
		/// @note
		/// The exception to the above warning is the a `EepromPointer<char>`,
		/// `EepromPointer<unsigned char>` or `EepromPointer<std::byte>` that points to a
		/// [trivially copyable](https://en.cppreference.com/w/cpp/named_req/TriviallyCopyable) type,
		/// in which case the pointer may be used to examine the
		/// [object representation](https://en.cppreference.com/w/cpp/language/object#Object_representation_and_value_representation)
		/// of the object in eeprom, as per the rules of
		/// [type aliasing](https://en.cppreference.com/w/cpp/language/reinterpret_cast#Type_aliasing)
		EepromPointer & operator--()
		{
			--this->pointer;
			return *this;
		}

		/// @brief
		/// Post-decrements the @ref EepromPointer.
		///
		/// @attention
		/// Prefer to use
		/// @slink{EepromPointer::operator--(),`--pointer`} over
		/// @slink{EepromPointer::operator--(int),`pointer--`} because
		/// @slink{EepromPointer::operator--(int),`pointer--`}
		/// has implicit overhead due to the creation of a temporary object.
		///
		/// @warning
		/// Do not attempt to use this operator unless the pointer points to an object in an array.
		/// Attempting to increment a pointer that does not point to an array element
		/// is likely to invalidate the pointer, which can lead to <strong>undefined behaviour</strong>.
		/// 
		/// @note
		/// The exception to the above warning is the a `EepromPointer<char>`,
		/// `EepromPointer<unsigned char>` or `EepromPointer<std::byte>` that points to a
		/// [trivially copyable](https://en.cppreference.com/w/cpp/named_req/TriviallyCopyable) type,
		/// in which case the pointer may be used to examine the
		/// [object representation](https://en.cppreference.com/w/cpp/language/object#Object_representation_and_value_representation)
		/// of the object in eeprom, as per the rules of
		/// [type aliasing](https://en.cppreference.com/w/cpp/language/reinterpret_cast#Type_aliasing)
		EepromPointer operator--(int)
		{
			const auto result = *this;
			this->operator--();
			return result;
		}
	};

	/// @brief
	/// A simpler way to construct a @ref EepromPointer. This function allows the type to be inferred.
	///
	/// @warning
	/// There is no way of verifying that the provided reference refers to an object in eeprom.
	/// It is thus possible to construct an invalid @ref EepromPointer,
	/// which can lead to <strong>undefined behaviour</strong>.
	template<typename Type>
	constexpr EepromPointer<Type> makeEepromPointer(Type & object)
	{
		return EepromPointer<Type>(object); 
	}

	/// @brief
	/// Tests whether two @sref{eeprom::EepromPointer,EepromPointers} are equal.
	///
	/// @details
	/// Returns `true` if the pointers are equal, otherwise returns `false`.
	template<typename Type>
	constexpr bool operator ==(const EepromPointer<Type> & left, const EepromPointer<Type> & right)
	{
		return (static_cast<const Type *>(left) == static_cast<const Type *>(right));
	}

	/// @brief
	/// Tests whether a @ref EepromPointer is null.
	///
	/// @details
	/// Returns `true` if the pointer is null, otherwise returns `false`.
	template<typename Type>
	constexpr bool operator ==(const EepromPointer<Type> & left, decltype(nullptr))
	{
		return (static_cast<const Type *>(left) == nullptr);
	}

	/// @brief
	/// Tests whether two @sref{eeprom::EepromPointer,EepromPointers} are not equal.
	///
	/// @details
	/// Returns `true` if the pointers are not equal, otherwise returns `false`.
	template<typename Type>
	constexpr bool operator !=(const EepromPointer<Type> & left, const EepromPointer<Type> & right)
	{
		return (static_cast<const Type *>(left) != static_cast<const Type *>(right));
	}

	/// @brief
	/// Tests whether a @ref EepromPointer is not null.
	///
	/// @details
	/// Returns `true` if the pointer is not null, otherwise returns `false`.
	template<typename Type>
	constexpr bool operator !=(const EepromPointer<Type> & left, decltype(nullptr))
	{
		return (static_cast<const Type *>(left) != nullptr);
	}

	/// @brief
	/// Subtracts two @sref{eeprom::EepromPointer,EepromPointers},
	/// returning the difference between them as a signed integer.
	template<typename Type>
	constexpr ptrdiff_t operator -(const EepromPointer<Type> & left, const EepromPointer<Type> & right)
	{
		return static_cast<ptrdiff_t>(static_cast<const Type *>(left) - static_cast<const Type *>(right));
	}

	/// @brief
	/// Adds an offset to a @sref{eeprom::EepromPointer,EepromPointer},
	/// and returns the resulting offset pointer.
	template<typename Type>
	constexpr EepromPointer<const Type> operator +(const EepromPointer<Type> & pointer, ptrdiff_t offset)
	{
		return EepromPointer<const Type>(static_cast<const Type *>(pointer) + offset);
	}
}