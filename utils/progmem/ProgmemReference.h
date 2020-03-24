#pragma once

#include "readProgmem.h"

namespace progmem
{
	/// @brief
	/// Represents a reference to an object stored in progmem.
	///
	/// @details
	/// The intent of this class is twofold:  
	/// * Primarily, the intent of this class is to provide a
	/// safer alternative to @ref ProgmemPointer when a simple
	/// reference-like object will suffice.  
	/// * Secondarily, the intent of this class is to provide
	/// a functional analogue to references for objects in progmem,
	/// as regular references don't work for objects stored in progmem.  
	template<typename Type>
	class ProgmemReference
	{
	public:
		/// @brief The type of the object referred to by this reference.
		using value_type = Type;

	private:
		const value_type * pointer;

	public:
		/// @brief
		/// Constructs a @ref ProgmemReference that refers to the provided object.
		///
		/// @warning
		/// There is no way of verifying that the provided reference refers to an object in progmem.
		/// It is thus possible to construct an invalid @ref ProgmemReference,
		/// which can lead to <strong>undefined behaviour</strong>.
		constexpr ProgmemReference(const value_type & object) :
			pointer(&object)
		{
		}

		/// @brief
		/// Constructs a @ref ProgmemReference that takes on the value of the provided pointer.
		///
		/// @note
		/// This constructor is marked explicit to ensure that the conversion from
		/// a raw pointer to a @ref ProgmemReference is clearly visible,
		/// and to prevent confusion between this overload
		/// and @ref ProgmemReference(const value_type &).
		///
		/// @warning
		/// There is no way of verifying that the provided pointer points to an object in progmem.
		/// It is thus possible to construct an invalid @ref ProgmemReference,
		/// which can lead to <strong>undefined behaviour</strong>.
		constexpr explicit ProgmemReference(const value_type * pointer) :
			pointer(pointer)
		{
		}

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
		/// Creates a copy of the object in progmem referred to by this @ref ProgmemReference.
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
		/// As such it is paramount that @ref ProgmemReference objects are used cautiously.
		///
		/// @warning
		/// There is no way of verifying that the @ref ProgmemReference refers to an object in progmem.
		/// It is thus possible to construct an invalid @ref ProgmemReference.
		/// <em>Calling @ref operator value_type() on an invalid reference invokes <strong>undefined behaviour</strong></em>.
		operator value_type() const
		{
			return progmem::readProgmem(*this->pointer);
		}
	};

	/// @brief
	/// @slink{progmem::ProgmemReference<const Type>, ProgmemReference<const Type>}
	/// is specialised to provide the correct behaviour for `const Type`.
	///
	/// @details
	/// @slink{progmem::ProgmemReference<const Type>, ProgmemReference<const Type>}
	/// behaves the same as @slink{progmem::ProgmemReference<Type>, ProgmemReference<Type>}
	/// because progmem is implicitly read-only.
	template<typename Type>
	class ProgmemReference<const Type> :
		public ProgmemReference<Type>
	{
		using ProgmemReference<Type>::ProgmemReference;
	};

	/// @brief
	/// A simpler way to construct a @ref ProgmemReference. This function allows the type to be inferred.
	///
	/// @warning
	/// There is no way of verifying that the provided reference refers to an object in progmem.
	/// It is thus possible to construct an invalid @ref ProgmemReference,
	/// which can lead to <strong>undefined behaviour</strong>.
	template<typename Type>
	constexpr ProgmemReference<Type> makeProgmemReference(const Type & object)
	{
		return ProgmemReference<Type>(object); 
	}
}