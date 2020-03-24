#pragma once

// For size_t
#include <stddef.h>

#include "ProgmemReference.h"
#include "ProgmemPointer.h"

namespace progmem
{
	/// @brief
	/// Represents an array of objects stored in progmem.
	///
	/// @details
	/// The intent of this class is:  
	/// * Primarily, to provide a simple way to manipulate
	/// arrays of objects in progmem.  
	/// * Secondarily, to provide a safer alternative to @ref ProgmemPointer
	/// for certain operations.  
	template<typename Type, size_t capacity>
	class ProgmemArray
	{
	public:
		/// @brief
		/// The type of the elements stored in the array.
		using value_type = Type;

		/// @brief
		/// The unsigned integer type used for measuring the size of the array.
		/// Also used to represent array indices.
		using size_type = size_t;

		/// @brief
		/// The signed integer type used for measuring the distance between array elements.
		using difference_type = ptrdiff_t;

		/// @brief
		/// The type that represents a reference to an array element.
		using reference = ProgmemReference<value_type>;

		/// @brief
		/// The type that represents a reference to a read-only array element.
		using const_reference = ProgmemReference<value_type>;

		/// @brief
		/// The type that represents a pointer to an array element.
		using pointer = ProgmemPointer<value_type>;

		/// @brief
		/// The type that represents a pointer to a read-only array element.
		using const_pointer = ProgmemPointer<value_type>;

		/// @brief
		/// The type used as an iterator to array elements.
		using iterator = pointer;

		/// @brief
		/// The type used as an iterator to read-only array elements.
		using const_iterator = const_pointer;

	private:
		static constexpr size_type first_index = 0;
		static constexpr size_type last_index = (capacity - 1);

		static constexpr size_type begin_index = 0;
		static constexpr size_type end_index = capacity;

	private:
		const value_type * elements;

	public:
		/// @brief
		/// Constructs a @slink{progmem::ProgmemArray,ProgmemArray}
		/// that refers to the provided array.
		///
		/// @warning
		/// There is no way of verifying that the provided reference refers to an array in progmem.
		/// It is thus possible to construct an invalid @ref ProgmemArray,
		/// which can lead to <strong>undefined behaviour</strong>.
		constexpr ProgmemArray(const value_type (& array)[capacity]) :
			elements(&array[0])
		{
		}

		/// @brief
		/// Constructs a @slink{progmem::ProgmemArray,ProgmemArray}
		/// that takes on the value of the provided pointer.
		///
		/// @note
		/// This constructor is marked explicit to ensure that the conversion from
		/// a raw pointer to a @slink{progmem::ProgmemArray,ProgmemArray}
		/// is clearly visible, and to prevent confusion between this overload
		/// and @ref ProgmemArray(const value_type (& array)[capacity]).
		///
		/// @warning
		/// There is no way of verifying that the provided pointer points to an array element in progmem.
		/// It is thus possible to construct an invalid @ref ProgmemArray,
		/// which can lead to <strong>undefined behaviour</strong>.
		constexpr explicit ProgmemArray(const value_type * pointer) :
			elements(pointer)
		{
		}

		/// @brief
		/// Returns `true` if the array is empty, returns `false` otherwise.
		///
		/// @note
		/// Always returns `false` for @slink{progmem::ProgmemArray,ProgmemArray} when `size` is not `0`.
		constexpr bool empty() const noexcept
		{
			return (capacity > 0);
		}

		/// @brief
		/// Returns the number of elements in the array.
		///
		/// @attention
		/// Prefer to use @slink{utils::size(const Container &),`utils::size(array)`}
		/// rather than @slink{progmem::ProgmemArray::size(),`array.size()`}.
		constexpr size_type size() const noexcept
		{
			return capacity;
		}

		/// @brief
		/// Returns the maximum number of elements in the array.
		///
		/// @note
		/// The expression @slink{progmem::ProgmemArray::max_size(),`array.max_size()`}
		/// returns the same value as @slink{progmem::ProgmemArray::size(),`array.size()`}
		/// because @sref{progmem::ProgmemArray, ProgmemArray<Type\, capacity>} is a fixed-size container.
		constexpr size_type max_size() const noexcept
		{
			return capacity;
		}

		/// @brief
		/// Returns a read-only reference to the first element of the array.
		constexpr const_reference front() const
		{
			return const_reference(&this->elements[first_index]);
		}

		/// @brief
		/// Returns a read-only reference to the last element of the array.
		constexpr const_reference back() const
		{
			return const_reference(&this->elements[last_index]);
		}

		/// @brief
		/// Returns a pointer to the first element of the underlying array.
		constexpr const_pointer data() const noexcept
		{
			return const_pointer(&this->elements[first_index]);
		}

		/// @brief
		/// Returns a read-only reference to the element at the specified index.
		///
		/// @warning
		/// This function does no bounds checking.
		/// <em>Providing an `index` that is greater than or equal to
		/// @slink{progmem::ProgmemArray::size(),`array.size()`}
		/// will result in a buffer overrun, which is <strong>undefined behaviour</strong></em>.
		constexpr const_reference operator[](size_type index) const
		{
			return const_reference(&this->elements[index]);
		}

		/// @brief
		/// Returns a const iterator pointing to the first element of the array.
		constexpr const_iterator begin() const noexcept
		{
			return const_pointer(&this->elements[begin_index]);
		}

		/// @brief
		/// Returns a const iterator pointing to the first element of the array.
		constexpr const_iterator cbegin() const noexcept
		{
			return const_pointer(&this->elements[begin_index]);
		}

		/// @brief
		/// Returns a past-the-end const iterator pointing beyond the last element of the array.
		///
		/// @warning
		/// Do not attempt to dereference the returned iterator.
		/// <em>Doing so will result in <strong>undefined behaviour</strong></em>.
		constexpr const_iterator end() const noexcept
		{
			return const_pointer(&this->elements[end_index]);
		}

		/// @brief
		/// Returns a past-the-end const iterator pointing beyond the last element of the array.
		///
		/// @warning
		/// Do not attempt to dereference the returned iterator.
		/// <em>Doing so will result in <strong>undefined behaviour</strong></em>.
		constexpr const_iterator cend() const noexcept
		{
			return const_pointer(&this->elements[end_index]);
		}
	};

	/// @brief
	/// @slink{progmem::ProgmemArray<const Type>, ProgmemArray<const Type>}
	/// is specialised to provide the correct behaviour for `const Type`.
	///
	/// @details
	/// @slink{progmem::ProgmemArray<const Type>, ProgmemArray<const Type>}
	/// behaves the same as @slink{progmem::ProgmemArray<Type>, ProgmemArray<Type>}
	/// because progmem is implicitly read-only.
	template<typename Type, size_t capacity>
	class ProgmemArray<const Type, capacity> :
		public ProgmemArray<Type, capacity>
	{
		using ProgmemArray<Type, capacity>::ProgmemArray;
	};

	/// @brief
	/// A simpler way to construct a @ref ProgmemArray.
	/// This function allows the type and size to be inferred.
	///
	/// @warning
	/// There is no way of verifying that the provided reference refers to an array in progmem.
	/// It is thus possible to construct an invalid @ref ProgmemArray,
	/// which can lead to <strong>undefined behaviour</strong>.
	template<typename Type, size_t capacity>
	constexpr ProgmemArray<Type, capacity> makeProgmemArray(const Type (&array)[capacity])
	{
		return array;
	}
}