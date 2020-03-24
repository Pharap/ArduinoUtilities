#pragma once

#include "../readEeprom.h"

namespace eeprom
{
	// Predeclare as a precaution
	template<typename Type>
	class EepromReference;

	/// @brief
	/// A specialisation of @sref{eeprom::EepromReference<Type>, EepromReference<Type>}
	/// that represents a reference to a read-only object.
	template<typename Type>
	class EepromReference<const Type>
	{
	public:
		/// @brief
		/// The type of the object referred to by this reference.
		using value_type = Type;

	private:
		const value_type * pointer;

	public:
		/// @brief
		/// Constructs an @ref EepromReference that refers to the provided object.
		///
		/// @warning
		/// There is no way of verifying that the provided reference refers to an object in eeprom.
		/// It is thus possible to construct an invalid @ref EepromReference,
		/// which can lead to <strong>undefined behaviour</strong>.
		constexpr EepromReference(const value_type & object) :
			pointer(&object)
		{
		}

		/// @brief
		/// Constructs a @ref EepromReference that takes on the value of the provided pointer.
		///
		/// @note
		/// This constructor is marked explicit to ensure that the conversion from
		/// a raw pointer to a @ref EepromReference is clearly visible,
		/// and to prevent confusion between this overload
		/// and @ref EepromReference(const value_type &).
		///
		/// @warning
		/// There is no way of verifying that the provided pointer points to an object in eeprom.
		/// It is thus possible to construct an invalid @ref EepromReference,
		/// which can lead to <strong>undefined behaviour</strong>.
		constexpr explicit EepromReference(const value_type * pointer) :
			pointer(pointer)
		{
		}

		/// @brief
		/// Explicitly deleted to indicate that a @ref EepromReference<const Type> can't be used like this.
		EepromReference & operator =(const value_type & value) = delete;

		/// @brief
		/// Returns the underlying raw pointer.
		///
		/// @details
		/// This operator is marked explicit to prevent its accidental use
		/// and to discourage excessive intentional use.
		explicit operator const value_type *() const
		{
			return this->pointer;
		}

		/// @brief
		/// Creates a copy of the object in eeprom referred to by this @ref EepromReference.
		///
		/// @note
		/// In some cases it may be beneficial to cache the result of this function,
		/// e.g. in a variable of suitable type.
		///
		/// @attention
		/// This conversion is implicit for the sake of providing behaviour analogous
		/// to that of ordinary lvalue references.
		/// However, this convinience comes at the cost of making it easier to accidentally
		/// invoke an implicit conversion when one was not intented.
		/// As such it is paramount that @ref EepromReference objects are used cautiously.
		///
		/// @warning
		/// There is no way of verifying that an
		/// @ref EepromReference refers to a valid object in eeprom.
		/// It is thus possible to construct an invalid @ref EepromReference.
		/// <em>Calling @ref operator value_type() on an invalid @ref EepromReference invokes
		/// <strong>undefined behaviour</strong></em>.
		operator value_type() const
		{
			return eeprom::readEeprom(*this->pointer);
		}
	};

	/// @brief
	/// A simpler way to construct a @ref EepromReference. This function allows the type to be inferred.
	///
	/// @warning
	/// There is no way of verifying that the provided reference refers to an object in eeprom.
	/// It is thus possible to construct an invalid @ref EepromReference,
	/// which can lead to <strong>undefined behaviour</strong>.
	template<typename Type>
	constexpr EepromReference<const Type> makeEepromReference(const Type & object)
	{
		return EepromReference<const Type>(object); 
	}
}