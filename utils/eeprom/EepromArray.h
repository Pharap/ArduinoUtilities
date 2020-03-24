#pragma once

// For size_t, ptrdiff_t
#include <stddef.h>

#include "EepromReference.h"
#include "EepromPointer.h"

namespace eeprom
{
	// Predeclare as a precaution
	template<typename Type, size_t capacity>
	class EepromArray;

	/// @brief
	/// Represents an array of objects stored in eeprom.
	///
	/// @details
	/// The intent of this class is:  
	/// * Primarily, to provide a simple way to manipulate
	/// arrays of objects in eeprom.  
	/// * Secondarily, to provide a safer alternative to @ref EepromPointer
	/// for certain operations.  
	template<typename Type, size_t capacity>
	class EepromArray
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
		using reference = EepromReference<value_type>;

		/// @brief
		/// The type that represents a reference to a read-only array element.
		using const_reference = EepromReference<const value_type>;

		/// @brief
		/// The type that represents a pointer to an array element.
		using pointer = EepromPointer<value_type>;

		/// @brief
		/// The type that represents a pointer to a read-only array element.
		using const_pointer = EepromPointer<const value_type>;

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
		/// Constructs a @slink{eeprom::EepromArray,EepromArray}
		/// that refers to the provided array.
		///
		/// @warning
		/// There is no way of verifying that the provided reference refers to an array in eeprom.
		/// It is thus possible to construct an invalid @ref EepromArray,
		/// which can lead to <strong>undefined behaviour</strong>.
		constexpr EepromArray(const value_type (& array)[capacity]) :
			elements(&array[0])
		{
		}

		/// @brief
		/// Constructs a @slink{eeprom::EepromArray,EepromArray}
		/// that takes on the value of the provided pointer.
		///
		/// @note
		/// This constructor is marked explicit to ensure that the conversion from
		/// a raw pointer to a @slink{eeprom::EepromArray,EepromArray}
		/// is clearly visible, and to prevent confusion between this overload
		/// and @ref EepromArray(const value_type (& array)[capacity]).
		///
		/// @warning
		/// There is no way of verifying that the provided pointer points to an array element in eeprom.
		/// It is thus possible to construct an invalid @ref EepromArray,
		/// which can lead to <strong>undefined behaviour</strong>.
		constexpr explicit EepromArray(const value_type * pointer) :
			elements(pointer)
		{
		}

		/// @brief
		/// Returns `true` if the array is empty, returns `false` otherwise.
		///
		/// @note
		/// Always returns `false` for @slink{eeprom::EepromArray,EepromArray} when `size` is not `0`.
		constexpr bool empty() const noexcept
		{
			return (capacity > 0);
		}

		/// @brief
		/// Returns the number of elements in the array.
		///
		/// @attention
		/// Prefer to use @slink{utils::size(const Container &),`utils::size(array)`}
		/// rather than @slink{eeprom::EepromArray::size(),`array.size()`}.
		constexpr size_type size() const noexcept
		{
			return capacity;
		}

		/// @brief
		/// Returns the maximum number of elements in the array.
		///
		/// @note
		/// The expression @slink{eeprom::EepromArray::max_size(),`array.max_size()`}
		/// returns the same value as @slink{eeprom::EepromArray::size(),`array.size()`}
		/// because @sref{eeprom::EepromArray, EepromArray<Type\, capacity>} is a fixed-size container.
		constexpr size_type max_size() const noexcept
		{
			return capacity;
		}

		/// @brief
		/// Returns a reference to the first element of the array.
		reference front()
		{
			return reference(&this->elements[first_index]);
		}

		/// @brief
		/// Returns a read-only reference to the first element of the array.
		constexpr const_reference front() const
		{
			return const_reference(&this->elements[first_index]);
		}

		/// @brief
		/// Returns a reference to the last element of the array.
		reference back()
		{
			return reference(&this->elements[last_index]);
		}

		/// @brief
		/// Returns a read-only reference to the last element of the array.
		constexpr const_reference back() const
		{
			return const_reference(&this->elements[last_index]);
		}

		/// @brief
		/// Returns a pointer to the first element of the underlying array.
		pointer data() noexcept
		{
			return pointer(&this->elements[first_index]);
		}

		/// @brief
		/// Returns a read-only pointer to the first element of the underlying array.
		constexpr const_pointer data() const noexcept
		{
			return const_pointer(&this->elements[first_index]);
		}

		/// @brief
		/// Returns a reference to the element at the specified index.
		///
		/// @warning
		/// This function does no bounds checking.
		/// _Providing an `index` that is greater than or equal to
		/// @slink{eeprom::EepromArray::size(),`array.size()`}
		/// will result in a buffer overrun, which is <strong>undefined behaviour</strong>_.
		reference operator[](size_type index)
		{
			return reference(&this->elements[index]);
		}

		/// @brief
		/// Returns a read-only reference to the element at the specified index.
		///
		/// @warning
		/// This function does no bounds checking.
		/// <em>Providing an `index` that is greater than or equal to
		/// @slink{eeprom::EepromArray::size(),`array.size()`}
		/// will result in a buffer overrun, which is <strong>undefined behaviour</strong></em>.
		constexpr const_reference operator[](size_type index) const
		{
			return const_reference(&this->elements[index]);
		}

		/// @brief
		/// Returns an iterator pointing to the first element of the array.
		iterator begin() noexcept
		{
			return iterator(&this->elements[begin_index]);
		}

		/// @brief
		/// Returns a const iterator pointing to the first element of the array.
		constexpr const_iterator begin() const noexcept
		{
			return this->cbegin();
		}

		/// @brief
		/// Returns a const iterator pointing to the first element of the array.
		constexpr const_iterator cbegin() const noexcept
		{
			return const_iterator(&this->elements[begin_index]);
		}

		/// @brief
		/// Returns a past-the-end iterator pointing beyond the last element of the array.
		///
		/// @warning
		/// Do not attempt to dereference the returned iterator.
		/// <em>Doing so will result in <strong>undefined behaviour</strong></em>.
		iterator end() noexcept
		{
			return iterator(&this->elements[end_index]);
		}

		/// @brief
		/// Returns a past-the-end const iterator pointing beyond the last element of the array.
		///
		/// @warning
		/// Do not attempt to dereference the returned iterator.
		/// <em>Doing so will result in <strong>undefined behaviour</strong></em>.
		constexpr const_iterator end() const noexcept
		{
			return this->cend();
		}

		/// @brief
		/// Returns a past-the-end const iterator pointing beyond the last element of the array.
		///
		/// @warning
		/// Do not attempt to dereference the returned iterator.
		/// <em>Doing so will result in <strong>undefined behaviour</strong></em>.
		constexpr const_iterator cend() const noexcept
		{
			return const_iterator(&this->elements[end_index]);
		}
	};

	/// @brief
	/// A simpler way to construct a @ref EepromArray.
	/// This function allows the type and size to be inferred.
	///
	/// @warning
	/// There is no way of verifying that the provided reference refers to an array in eeprom.
	/// It is thus possible to construct an invalid @ref EepromArray,
	/// which can lead to <strong>undefined behaviour</strong>.
	template<typename Type, size_t capacity>
	constexpr EepromArray<Type, capacity> makeEepromArray(Type (&array)[capacity])
	{
		return array;
	}
}