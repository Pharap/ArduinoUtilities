#pragma once

#include "ProgmemReference.h"

namespace progmem
{
	/// @brief
	/// Represents a pointer to an object stored in progmem.
	///
	/// @details
	/// The intent of this class is twofold:  
	/// * Primarily, the intent of this class is to provide a means of
	/// differentiating between a pointer to an object in progmem
	/// and a pointer to an obejct stored elsewhere.  
	/// * Secondarily, the intent of this class is to enable the use of
	/// standard pointer syntax with objects stored in progmem.  
	///
	/// @note
	/// This class may be used as an contiguous iterator for
	/// containers with contiguous elements stored in progmem.
	template<typename Type>
	class ProgmemPointer
	{
	public:
		/// @brief
		/// The type of the object referred to by this pointer.
		using value_type = Type;

	private:
		const value_type * pointer;

	public:
		/// @brief
		/// Constructs a @ref ProgmemPointer that refers to the provided object.
		///
		/// @warning
		/// There is no way of verifying that the provided reference refers to an object in progmem.
		/// It is thus possible to construct an invalid @ref ProgmemPointer,
		/// which can lead to <strong>undefined behaviour</strong>.
		constexpr ProgmemPointer(const value_type & object) :
			pointer(&object)
		{
		}

		/// @brief
		/// Constructs a @ref ProgmemPointer that takes on the value of the provided pointer.
		///
		/// @note
		/// This constructor is marked explicit to ensure that the conversion from
		/// a raw pointer to a @ref ProgmemPointer is clearly visible,
		/// and to prevent confusion between this overload
		/// and @ref ProgmemPointer(const value_type &).
		///
		/// @warning
		/// There is no way of verifying that the provided pointer points to an object in progmem.
		/// It is thus possible to construct an invalid @ref ProgmemPointer,
		/// which can lead to <strong>undefined behaviour</strong>.
		constexpr explicit ProgmemPointer(const value_type * pointer) :
			pointer(pointer)
		{
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
		/// Dereferences the @ref ProgmemPointer, creating a @ref ProgmemReference,
		/// which may be implicitly converted to a @ref value_type object.
		ProgmemReference<value_type> operator *() const
		{
			return ProgmemReference<value_type>(this->pointer);
		}

		/// @brief
		/// Pre-increments the @ref ProgmemPointer.
		///
		/// @attention
		/// Prefer to use
		/// @slink{ProgmemPointer::operator++(),`++pointer`} over
		/// @slink{ProgmemPointer::operator++(int),`pointer++`} because
		/// @slink{ProgmemPointer::operator++(int),`pointer++`}
		/// has implicit overhead due to the creation of a temporary object.
		///
		/// @warning
		/// Do not attempt to use this operator unless the pointer points to an object in an array.
		/// Attempting to increment a pointer that does not point to an array element
		/// is likely to invalidate the pointer, which can lead to <strong>undefined behaviour</strong>.
		/// 
		/// @note
		/// The exception to the above warning is the a `ProgmemPointer<char>`,
		/// `ProgmemPointer<unsigned char>` or `ProgmemPointer<std::byte>` that points to a
		/// [trivially copyable](https://en.cppreference.com/w/cpp/named_req/TriviallyCopyable) type,
		/// in which case the pointer may be used to examine the
		/// [object representation](https://en.cppreference.com/w/cpp/language/object#Object_representation_and_value_representation)
		/// of the object in progmem, as per the rules of
		/// [type aliasing](https://en.cppreference.com/w/cpp/language/reinterpret_cast#Type_aliasing)
		ProgmemPointer & operator++()
		{
			++this->pointer;
			return *this;
		}

		/// @brief
		/// Post-increments the @ref ProgmemPointer.
		///
		/// @attention
		/// Prefer to use
		/// @slink{ProgmemPointer::operator++(),`++pointer`} over
		/// @slink{ProgmemPointer::operator++(int),`pointer++`} because
		/// @slink{ProgmemPointer::operator++(int),`pointer++`}
		/// has implicit overhead due to the creation of a temporary object.
		///
		/// @warning
		/// Do not attempt to use this operator unless the pointer points to an object in an array.
		/// Attempting to increment a pointer that does not point to an array element
		/// is likely to invalidate the pointer, which can lead to <strong>undefined behaviour</strong>.
		/// 
		/// @note
		/// The exception to the above warning is the a `ProgmemPointer<char>`,
		/// `ProgmemPointer<unsigned char>` or `ProgmemPointer<std::byte>` that points to a
		/// [trivially copyable](https://en.cppreference.com/w/cpp/named_req/TriviallyCopyable) type,
		/// in which case the pointer may be used to examine the
		/// [object representation](https://en.cppreference.com/w/cpp/language/object#Object_representation_and_value_representation)
		/// of the object in progmem, as per the rules of
		/// [type aliasing](https://en.cppreference.com/w/cpp/language/reinterpret_cast#Type_aliasing)
		ProgmemPointer operator++(int)
		{
			const auto result = *this;
			this->operator++();
			return result;
		}

		/// @brief
		/// Pre-decrements the @ref ProgmemPointer.
		///
		/// @attention
		/// Prefer to use
		/// @slink{ProgmemPointer::operator--(),`--pointer`} over
		/// @slink{ProgmemPointer::operator--(int),`pointer--`} because
		/// @slink{ProgmemPointer::operator--(int),`pointer--`}
		/// has implicit overhead due to the creation of a temporary object.
		///
		/// @warning
		/// Do not attempt to use this operator unless the pointer points to an object in an array.
		/// Attempting to increment a pointer that does not point to an array element
		/// is likely to invalidate the pointer, which can lead to <strong>undefined behaviour</strong>.
		/// 
		/// @note
		/// The exception to the above warning is the a `ProgmemPointer<char>`,
		/// `ProgmemPointer<unsigned char>` or `ProgmemPointer<std::byte>` that points to a
		/// [trivially copyable](https://en.cppreference.com/w/cpp/named_req/TriviallyCopyable) type,
		/// in which case the pointer may be used to examine the
		/// [object representation](https://en.cppreference.com/w/cpp/language/object#Object_representation_and_value_representation)
		/// of the object in progmem, as per the rules of
		/// [type aliasing](https://en.cppreference.com/w/cpp/language/reinterpret_cast#Type_aliasing)
		ProgmemPointer & operator--()
		{
			--this->pointer;
			return *this;
		}

		/// @brief
		/// Post-decrements the @ref ProgmemPointer.
		///
		/// @attention
		/// Prefer to use
		/// @slink{ProgmemPointer::operator--(),`--pointer`} over
		/// @slink{ProgmemPointer::operator--(int),`pointer--`} because
		/// @slink{ProgmemPointer::operator--(int),`pointer--`}
		/// has implicit overhead due to the creation of a temporary object.
		///
		/// @warning
		/// Do not attempt to use this operator unless the pointer points to an object in an array.
		/// Attempting to increment a pointer that does not point to an array element
		/// is likely to invalidate the pointer, which can lead to <strong>undefined behaviour</strong>.
		/// 
		/// @note
		/// The exception to the above warning is the a `ProgmemPointer<char>`,
		/// `ProgmemPointer<unsigned char>` or `ProgmemPointer<std::byte>` that points to a
		/// [trivially copyable](https://en.cppreference.com/w/cpp/named_req/TriviallyCopyable) type,
		/// in which case the pointer may be used to examine the
		/// [object representation](https://en.cppreference.com/w/cpp/language/object#Object_representation_and_value_representation)
		/// of the object in progmem, as per the rules of
		/// [type aliasing](https://en.cppreference.com/w/cpp/language/reinterpret_cast#Type_aliasing)
		ProgmemPointer operator--(int)
		{
			const auto result = *this;
			this->operator--();
			return result;
		}
	};

	/// @brief
	/// @slink{progmem::ProgmemPointer<const Type>, ProgmemPointer<const Type>}
	/// is specialised to provide the correct behaviour for `const Type`.
	///
	/// @details
	/// @slink{progmem::ProgmemPointer<const Type>, ProgmemPointer<const Type>}
	/// behaves the same as @slink{progmem::ProgmemPointer<Type>, ProgmemPointer<Type>}
	/// because progmem is implicitly read-only.
	template<typename Type>
	class ProgmemPointer<const Type> :
		public ProgmemPointer<Type>
	{
		using ProgmemPointer<Type>::ProgmemPointer;
	};

	/// @brief
	/// A simpler way to construct a @ref ProgmemPointer. This function allows the type to be inferred.
	///
	/// @warning
	/// There is no way of verifying that the provided reference refers to an object in progmem.
	/// It is thus possible to construct an invalid @ref ProgmemPointer,
	/// which can lead to <strong>undefined behaviour</strong>.
	template<typename Type>
	constexpr ProgmemPointer<Type> makeProgmemPointer(const Type & object)
	{
		return ProgmemPointer<Type>(object); 
	}

	/// @brief
	/// Tests whether two @sref{progmem::ProgmemPointer,ProgmemPointers} are equal.
	///
	/// @details
	/// Returns `true` if the pointers are equal, otherwise returns `false`.
	template<typename Type>
	constexpr bool operator ==(const ProgmemPointer<Type> & left, const ProgmemPointer<Type> & right)
	{
		return (static_cast<const Type *>(left) == static_cast<const Type *>(right));
	}

	/// @brief
	/// Tests whether a @ref ProgmemPointer is null.
	///
	/// @details
	/// Returns `true` if the pointer is null, otherwise returns `false`.
	template<typename Type>
	constexpr bool operator ==(const ProgmemPointer<Type> & left, decltype(nullptr))
	{
		return (static_cast<const Type *>(left) == nullptr);
	}

	/// @brief
	/// Tests whether two @sref{progmem::ProgmemPointer,ProgmemPointers} are not equal.
	///
	/// @details
	/// Returns `true` if the pointers are not equal, otherwise returns `false`.
	template<typename Type>
	constexpr bool operator !=(const ProgmemPointer<Type> & left, const ProgmemPointer<Type> & right)
	{
		return (static_cast<const Type *>(left) != static_cast<const Type *>(right));
	}

	/// @brief
	/// Tests whether a @ref ProgmemPointer is not null.
	///
	/// @details
	/// Returns `true` if the pointer is not null, otherwise returns `false`.
	template<typename Type>
	constexpr bool operator !=(const ProgmemPointer<Type> & left, decltype(nullptr))
	{
		return (static_cast<const Type *>(left) != nullptr);
	}

	/// @brief
	/// Subtracts two @sref{progmem::ProgmemPointer,ProgmemPointers},
	/// returning the difference between them as a signed integer.
	template<typename Type>
	constexpr ptrdiff_t operator -(const ProgmemPointer<Type> & left, const ProgmemPointer<Type> & right)
	{
		return static_cast<ptrdiff_t>(static_cast<const Type *>(left) - static_cast<const Type *>(right));
	}

	/// @brief
	/// Adds an offset to a @sref{progmem::ProgmemPointer,ProgmemPointer},
	/// and returns the resulting offset pointer.
	template<typename Type>
	constexpr ProgmemPointer<Type> operator +(const ProgmemPointer<Type> & pointer, ptrdiff_t offset)
	{
		return ProgmemPointer<Type>(static_cast<const Type *>(pointer) + offset);
	}
}