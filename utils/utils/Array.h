#pragma once

/// @file Array.h
/// @author Pharap
/// @version v0.0.1
/// @date 2020/03/05
/// @copyright &copy; Pharap 2020

// For size_t, ptrdiff_t
#include <stddef.h>

// For swap
#include "swap.h"

namespace utils
{
	/// @brief
	/// A template class that behaves almost identically to
	/// [`std::array`](https://en.cppreference.com/w/cpp/container/array).
	template<typename Type, size_t capacity>
	class Array
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
		/// The type that represents a reference to a mutable array element.
		using reference = value_type &;

		/// @brief
		/// The type that represents a reference to a read-only array element.
		using const_reference = const value_type &;

		/// @brief
		/// The type that represents a pointer to a mutable array element.
		using pointer = value_type *;

		/// @brief
		/// The type that represents a pointer to a read-only array element.
		using const_pointer = const value_type *;

		/// @brief
		/// The type used as an iterator to mutable array elements.
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
		value_type elements[capacity];

	public:
		/// @brief
		/// Returns `true` if the array is empty, returns `false` otherwise.
		///
		/// @note
		/// Always returns `false` for
		/// @sref{utils::Array<Type\, capacity>, Array<Type\, capacity>}
		/// when `size` is not `0`.
		constexpr bool empty() const noexcept
		{
			return false;
		}

		/// @brief
		/// Returns the number of elements in the array.
		///
		/// @attention
		/// Prefer to use @slink{utils::size(const Container &),`utils::size(array)`}
		/// rather than @slink{utils::Array::size(),`array.size()`}.
		constexpr size_type size() const noexcept
		{
			return capacity;
		}

		/// @brief
		/// Returns the maximum number of elements in the array.
		///
		/// @note
		/// The expression @slink{utils::Array::max_size(),`array.max_size()`}
		/// returns the same value as @slink{utils::Array::size(),`array.size()`}
		/// because @sref{utils::Array, Array<Type\, capacity>} is a fixed-size container.
		constexpr size_type max_size() const noexcept
		{
			return capacity;
		}

		/// @brief
		/// Returns a mutable reference to the first element of the array.
		reference front()
		{
			return this->elements[first_index];
		}

		/// @brief
		/// Returns a read-only reference to the first element of the array.
		constexpr const_reference front() const
		{
			return this->elements[first_index];
		}

		/// @brief
		/// Returns a mutable reference to the last element of the array.
		reference back()
		{
			return this->elements[last_index];
		}

		/// @brief
		/// Returns a read-only reference to the last element of the array.
		constexpr const_reference back() const
		{
			return this->elements[last_index];
		}

		/// @brief
		/// Returns a pointer to the first element of the underlying array.
		value_type * data() noexcept
		{
			return &this->elements[first_index];
		}

		/// @brief
		/// Returns a pointer to the first element of the underlying array.
		constexpr const value_type * data() const noexcept
		{
			return &this->elements[first_index];
		}

		/// @brief
		/// Returns a mutable reference to the element at the specified index.
		///
		/// @param index
		/// The index of the requested array element.
		///
		/// @pre
		/// `0` &le; `index` &lt; `array.size()`
		///
		/// @warning
		/// This function does no bounds checking.
		/// <em>Providing an `index` that is greater than or equal to
		/// @slink{utils::Array::size(),`array.size()`}
		/// will result in a buffer overrun, which is <strong>undefined behaviour</strong></em>.
		reference operator[](size_type index)
		{
			return this->elements[index];
		}

		/// @brief
		/// Returns a read-only reference to the element at the specified index.
		///
		/// @param index
		/// The index of the requested array element.
		///
		/// @pre
		/// `0` &le; `index` &lt; `array.size()`
		///
		/// @warning
		/// This function does no bounds checking.
		/// <em>Providing an `index` that is greater than or equal to
		/// @slink{utils::Array::size(),`array.size()`}
		/// will result in a buffer overrun, which is <strong>undefined behaviour</strong></em>.
		constexpr const_reference operator[](size_type index) const
		{
			return this->elements[index];
		}

		/// @brief
		/// Returns an iterator pointing to the first element of the array.
		iterator begin() noexcept
		{
			return &this->elements[begin_index];
		}

		/// @brief
		/// Returns a const iterator pointing to the first element of the array.
		constexpr const_iterator begin() const noexcept
		{
			return &this->elements[begin_index];
		}

		/// @brief
		/// Returns a const iterator pointing to the first element of the array.
		constexpr const_iterator cbegin() const noexcept
		{
			return &this->elements[begin_index];
		}

		/// @brief
		/// Returns a past-the-end iterator pointing beyond the last element of the array.
		///
		/// @warning
		/// Do not attempt to dereference the returned iterator.
		/// <em>Doing so will result in <strong>undefined behaviour</strong></em>.
		iterator end() noexcept
		{
			return &this->elements[end_index];
		}

		/// @brief
		/// Returns a past-the-end const iterator pointing beyond the last element of the array.
		///
		/// @warning
		/// Do not attempt to dereference the returned iterator.
		/// <em>Doing so will result in <strong>undefined behaviour</strong></em>.
		constexpr const_iterator end() const noexcept
		{
			return &this->elements[end_index];
		}

		/// @brief
		/// Returns a past-the-end const iterator pointing beyond the last element of the array.
		///
		/// @warning
		/// Do not attempt to dereference the returned iterator.
		/// <em>Doing so will result in <strong>undefined behaviour</strong></em>.
		constexpr const_iterator cend() const noexcept
		{
			return &this->elements[end_index];
		}

		/// @brief
		/// Fills the array with copies of the specified value.
		///
		/// @complexity
		/// Linear - `O(n)` where `n` is `capacity`.
		///
		/// @param value
		/// The value to fill the array with.
		void fill(const value_type & value)
		{
			for(size_type index = begin_index; index < end_index; ++index)
				this->elements[index] = value;
		}

		/// @brief
		/// Swaps the contents of this array with the contents of another array of the same type and size.
		///
		/// @param other
		/// The other array.
		///
		/// @complexity
		/// Linear - `O(n)` where `n` is `capacity`.
		///
		/// @attention
		/// Prefer to use
		/// @slink{utils::swap(utils::Array &\, utils::Array &),`utils::swap(array0\, array1)`}
		/// rather than
		/// @slink{utils::Array::swap(utils::Array &),`array0.swap(array1)`}.
		void swap(Array & other)
		{
			using utils::swap;

			swap(this->elements, other.elements);
		}
	};

	/// @brief
	/// Swaps the contents of two @sref{utils::Array<Type\, capacity>, Array<Type\, capacity>}
	/// objects with the same type and size.
	///
	/// @param left, right
	/// The arrays to be swapped.
	///
	/// @complexity
	/// Linear - `O(n)` where `n` is `capacity`.
	///
	/// @note
	/// Iterators will remain valid,
	/// and will still point to the array they were created with,
	/// but the values they point to may have changed.
	template<typename Type, size_t capacity>
	void swap(Array<Type, capacity> & left, Array<Type, capacity> & right)
	{
		left.swap(right);
	}
	
	/// @brief
	/// A specialisation of @sref{utils::Array<Type\, capacity>, Array<Type\, capacity>}
	/// that represents an empty array.
	template<typename Type>
	class Array<Type, 0>
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
		/// The type that represents a reference to a mutable array element.
		using reference = value_type &;

		/// @brief The type that represents a reference to a read-only array element.
		using const_reference = const value_type &;

		/// @brief
		/// The type that represents a pointer to a mutable array element.
		using pointer = value_type *;

		/// @brief
		/// The type that represents a pointer to a read-only array element.
		using const_pointer = const value_type *;

		/// @brief
		/// The type used as an iterator to mutable array elements.
		using iterator = pointer;

		/// @brief
		/// The type used as an iterator to read-only array elements.
		using const_iterator = const_pointer;

	public:
		/// @brief
		/// Returns `true` if the array is empty, returns `false` otherwise.
		///
		/// @note
		/// Always returns `true` for the @sref{utils::Array<Type\, 0>, Array<Type\, 0>}
		/// specialisation.
		constexpr bool empty() const noexcept
		{
			return true;
		}

		/// @brief
		/// Returns the number of elements in the array.
		///
		/// @attention
		/// Prefer to use @slink{utils::size(const Container &),`utils::size(array)`}
		/// rather than @slink{utils::Array<Type\, 0>::size(),`array.size()`}.
		///
		/// @note
		/// Always returns `0` for the @sref{utils::Array<Type\, 0>, Array<Type\, 0>}
		/// specialisation.
		constexpr size_type size() const noexcept
		{
			return 0;
		}

		/// @brief
		/// Returns the maximum number of elements in the array.
		///
		/// @note
		/// @parblock
		/// The expression @slink{utils::Array<Type\, 0>::max_size(),`array.max_size()`}
		/// returns the same value as @slink{utils::Array<Type\, 0>::size(),`array.size()`}
		/// because @sref{utils::Array<Type\, 0>, Array<Type\, 0>} is a fixed-size container.
		/// @endparblock
		///
		/// @note
		/// @parblock
		/// Always returns `0` for the @sref{utils::Array<Type\, 0>, Array<Type\, 0>}
		/// specialisation.
		/// @endparblock
		constexpr size_type max_size() const noexcept
		{
			return 0;
		}

		/// @brief
		/// Returns a read-only reference to the first element of the array.
		///
		/// @note
		/// Intentionally deleted for the @sref{utils::Array<Type\, 0>, Array<Type\, 0>}
		/// specialisation.
		constexpr const_reference front() const = delete;

		/// @brief
		/// Returns a read-only reference to the last element of the array.
		///
		/// @note
		/// Intentionally deleted for the the @sref{utils::Array<Type\, 0>, Array<Type\, 0>}
		/// specialisation.
		constexpr const_reference back() const = delete;

		/// @brief
		/// Returns a pointer to the first element of the underlying array.
		///
		/// @warning
		/// Returns `nullptr` for the the @sref{utils::Array<Type\, 0>, Array<Type\, 0>}
		/// specialisation.
		/// <em>Dereferencing a null pointer is <strong>undefined behaviour</strong>.</em>
		constexpr const value_type * data()
		{
			return nullptr;
		}

		/// @brief
		/// Returns a read-only reference to the element at the specified index.
		///
		/// @attention
		/// This function is intentionally deleted for the @sref{utils::Array<Type\, 0>, Array<Type\, 0>}
		/// specialisation.
		constexpr const_reference operator[](size_type index) const = delete;

		/// @brief
		/// Returns a const iterator pointing to the first element of the array.
		///
		/// @warning
		/// Returns `nullptr` for the @sref{utils::Array<Type\, 0>, Array<Type\, 0>} specialisation.
		/// <em>Dereferencing a null pointer is <strong>undefined behaviour</strong>.</em>
		constexpr const_iterator begin() const noexcept
		{
			return nullptr;
		}

		/// @brief
		/// Returns a const iterator pointing to the first element of the array.
		///
		/// @warning
		/// Returns `nullptr` for the @sref{utils::Array<Type\, 0>, Array<Type\, 0>} specialisation.
		/// <em>Dereferencing a null pointer is <strong>undefined behaviour</strong>.</em>
		constexpr const_iterator cbegin() const noexcept
		{
			return nullptr;
		}

		/// @brief
		/// Returns a past-the-end const iterator pointing beyond the last element of the array.
		///
		/// @warning
		/// Returns `nullptr` for the @sref{utils::Array<Type\, 0>, Array<Type\, 0>} specialisation.
		/// <em>Dereferencing a null pointer is <strong>undefined behaviour</strong>.</em>
		constexpr const_iterator end() const noexcept
		{
			return nullptr;
		}

		/// @brief
		/// Returns a past-the-end const iterator pointing beyond the last element of the array.
		///
		/// @warning
		/// Returns `nullptr` for the @sref{utils::Array<Type\, 0>, Array<Type\, 0>} specialisation.
		/// <em>Dereferencing a null pointer is <strong>undefined behaviour</strong>.</em>
		constexpr const_iterator cend() const noexcept
		{
			return nullptr;
		}

		/// @brief
		/// Fills the array with copies of the specified value.
		///
		/// @param value
		/// The value to fill the array with.
		///
		/// @note
		/// This function intentionally does nothing for the
		/// @sref{utils::Array<Type\, 0>, Array<Type\, 0>} specialisation.
		void fill(const value_type & value)
		{
			// Note: `static_cast<void>` silences 'unused variable' warnings.
			static_cast<void>(value);
		}

		/// @brief
		/// Swaps the contents of this array with the contents of another array of the same type and size.
		///
		/// @param other
		/// The other array.
		///
		/// @attention
		/// Prefer to use
		/// @slink{utils::swap(utils::Array &\, utils::Array &),`utils::swap(array0\, array1)`}
		/// rather than
		/// @slink{utils::Array<Type\, 0>::swap,`array0.swap(array1)`}.
		///
		/// @note
		/// This function intentionally does nothing for the
		/// @sref{utils::Array<Type\, 0>, Array<Type\, 0>} specialisation.
		void swap(Array & other)
		{
			// Note: `static_cast<void>` silences 'unused variable' warnings.
			static_cast<void>(other);
		}
	};
}