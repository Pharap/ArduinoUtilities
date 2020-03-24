#pragma once

// For size_t, ptrdiff_t
#include <stddef.h>

#include "Deque.h"

namespace containers
{
	// Predeclare as a precaution
	template<typename Type, size_t capacity, typename Container>
	class List;

	/// @brief
	/// A container adapter class representing an indexable list.
	template<typename Type, size_t capacity, typename Container = Deque<Type, capacity>>
	class List
	{
	public:
		/// @brief
		/// The type of container adapted by the list.
		using container_type = Container;
		
		/// @brief
		/// The type of the elements contained by the list.
		using value_type = typename container_type::value_type;

		/// @brief
		/// The unsigned integer type used for indices.
		using size_type = typename container_type::size_type;

		/// @brief
		/// The signed integer type used for measuring the distance between iterators.
		using difference_type = typename container_type::difference_type;

		/// @brief
		/// The type that represents a reference to a mutable list element.
		using reference = typename container_type::reference;

		/// @brief
		/// The type that represents a reference to a read-only list element.
		using const_reference = typename container_type::const_reference;

		/// @brief
		/// The type that represents a pointer to a mutable list element.
		using pointer = typename container_type::pointer;

		/// @brief
		/// The type that represents a pointer to a read-only list element.
		using const_pointer = typename container_type::const_pointer;

		/// @brief
		/// The type used as an iterator to mutable list elements.
		using iterator = typename container_type::iterator;

		/// @brief
		/// The type used as an iterator to read-only list elements.
		using const_iterator = typename container_type::const_iterator;

	private:
		container_type container;

	public:
		/// @brief
		/// Returns `true` if the list is empty, returns `false` otherwise.
		///
		/// @details
		/// Equivalent to <code>@slink{List::size(), list.size()} > 0</code>.
		constexpr bool empty() const noexcept
		{
			return this->container.empty();
		}

		/// @brief
		/// Returns the number of elements in the list.
		///
		/// @attention
		/// Prefer to use @slink{utils::size(const Container &),`utils::size(list)`}
		/// rather than @slink{List::size(),`list.size()`}.
		constexpr size_type size() const noexcept
		{
			return this->container.size();
		}

		/// @brief
		/// Returns the maximum number of elements in the list.
		constexpr size_type max_size() const noexcept
		{
			return this->container.max_size();
		}

		/// @brief
		/// Returns a mutable reference to the first element of the list.
		///
		/// @pre
		/// <code>@slink{List::size, list.size()} > 0</code> -
		/// The list must contain at least one element.
		///
		/// @pre
		/// <code>!@slink{List::empty, list.empty()}</code> - The list must not be empty.
		///
		/// @warning
		/// Do not attempt to call `front()` if the list is empty.
		/// <em>Doing so will result in <strong>undefined behaviour</strong></em>.
		reference front()
		{
			return this->container.front();
		}

		/// @brief
		/// Returns a read-only reference to the first element of the list.
		///
		/// @pre
		/// <code>@slink{List::size, list.size()} > 0</code> -
		/// The list must contain at least one element.
		///
		/// @pre
		/// <code>!@slink{List::empty, list.empty()}</code> - The list must not be empty.
		///
		/// @warning
		/// Do not attempt to call `front()` if the list is empty.
		/// <em>Doing so will result in <strong>undefined behaviour</strong></em>.
		constexpr const_reference front() const
		{
			return this->container.front();
		}

		/// @brief
		/// Returns a mutable reference to the last element of the list.
		///
		/// @pre
		/// <code>@slink{List::size, list.size()} > 0</code> -
		/// The list must contain at least one element.
		///
		/// @pre
		/// <code>!@slink{List::empty, list.empty()}</code> - The list must not be empty.
		///
		/// @warning
		/// Do not attempt to call `back()` if the list is empty.
		/// <em>Doing so will result in <strong>undefined behaviour</strong></em>.
		reference back()
		{
			return this->container.back();
		}

		/// @brief
		/// Returns a read-only reference to the last element of the list.
		///
		/// @pre
		/// <code>@slink{List::size, list.size()} > 0</code> -
		/// The list must contain at least one element.
		///
		/// @pre
		/// <code>!@slink{List::empty, list.empty()}</code> - The list must not be empty.
		///
		/// @warning
		/// Do not attempt to call `back()` if the list is empty.
		/// <em>Doing so will result in <strong>undefined behaviour</strong></em>.
		constexpr const_reference back() const
		{
			return this->container.back();
		}

		/// @brief
		/// Returns a pointer to the first element of the underlying array.
		pointer data() noexcept
		{
			return this->container.data();
		}

		/// @brief
		/// Returns a const pointer to the first element of the underlying array.
		constexpr const_pointer data() const noexcept
		{
			return this->container.data();
		}

		/// @brief
		/// Returns a mutable reference to the element at the specified index.
		///
		/// @param index
		/// The index of the requested list element.
		///
		/// @pre
		/// <code>@slink{List::size, list.size()} > 0</code> -
		/// The list must contain at least one element.
		///
		/// @pre
		/// <code>!@slink{List::empty, list.empty()}</code> -
		/// The list must not be empty.
		///
		/// @pre
		/// <code>index < @slink{List::size(), list.size()}</code> -
		/// `index` must be less than `size()`.
		///
		/// @warning
		/// This function does no bounds checking.
		/// <em>Providing an `index` that is greater than or equal to @slink{List::size(),`list.size()`}
		/// will result in a buffer overrun, which is <strong>undefined behaviour</strong></em>.
		reference operator[](size_type index)
		{
			return this->container[index];
		}

		/// @brief
		/// Returns a read-only reference to the element at the specified index.
		///
		/// @param index
		/// The index of the requested list element.
		///
		/// @pre
		/// <code>@slink{List::size, list.size()} > 0</code> -
		/// The list must contain at least one element.
		///
		/// @pre
		/// <code>!@slink{List::empty, list.empty()}</code> -
		/// The list must not be empty.
		///
		/// @pre
		/// <code>index < @slink{List::size(), list.size()}</code> -
		/// `index` must be less than `size()`.
		///
		/// @warning
		/// This function does no bounds checking.
		/// <em>Providing an `index` that is greater than or equal to
		/// @slink{List::size(),`list.size()`}
		/// will result in a buffer overrun, which is <strong>undefined behaviour</strong></em>.
		constexpr const_reference operator[](size_type index) const
		{
			return this->container[index];
		}

		/// @brief
		/// Returns an iterator pointing to the first element of the list.
		///
		/// @pre
		/// <code>@slink{List::size, list.size()} > 0</code> -
		/// The list must contain at least one element.
		///
		/// @pre
		/// <code>!@slink{List::empty, list.empty()}</code> -
		/// The list must not be empty.
		///
		/// @warning
		/// Do not attempt to dereference the returned iterator if the list is empty.
		/// <em>Doing so will result in <strong>undefined behaviour</strong></em>.
		iterator begin() noexcept
		{
			return this->container.begin();
		}

		/// @brief
		/// Returns a const iterator pointing to the first element of the list.
		///
		/// @pre
		/// <code>@slink{List::size, list.size()} > 0</code> -
		/// The list must contain at least one element.
		///
		/// @pre
		/// <code>!@slink{List::empty, list.empty()}</code> -
		/// The list must not be empty.
		///
		/// @warning
		/// Do not attempt to dereference the returned iterator if the list is empty.
		/// <em>Doing so will result in <strong>undefined behaviour</strong></em>.
		constexpr const_iterator begin() const noexcept
		{
			return this->container.begin();
		}

		/// @brief
		/// Returns a const iterator pointing to the first element of the list.
		///
		/// @pre
		///
		/// @pre
		/// <code>@slink{List::size, list.size()} > 0</code> -
		/// The list must contain at least one element.
		///
		/// @pre
		/// <code>!@slink{List::empty, list.empty()}</code> -
		/// The list must not be empty.
		///
		/// @warning
		/// Do not attempt to dereference the returned iterator if the list is empty.
		/// <em>Doing so will result in <strong>undefined behaviour</strong></em>.
		constexpr const_iterator cbegin() const noexcept
		{
			return this->container.cbegin();
		}

		/// @brief
		/// Returns a past-the-end iterator pointing beyond the last element of the list.
		///
		/// @warning
		/// Do not attempt to dereference the returned iterator.
		/// <em>Doing so will result in <strong>undefined behaviour</strong></em>.
		iterator end() noexcept
		{
			return this->container.end();
		}

		/// @brief
		/// Returns a past-the-end const iterator pointing beyond the last element of the list.
		///
		/// @warning
		/// Do not attempt to dereference the returned iterator.
		/// <em>Doing so will result in <strong>undefined behaviour</strong></em>.
		constexpr const_iterator end() const noexcept
		{
			return this->container.end();
		}

		/// @brief
		/// Returns a past-the-end const iterator pointing beyond the last element of the list.
		///
		/// @warning
		/// Do not attempt to dereference the returned iterator.
		/// <em>Doing so will result in <strong>undefined behaviour</strong></em>.
		constexpr const_iterator cend() const noexcept
		{
			return this->container.cend();
		}

		/// @brief
		/// Appends the specified value to the end of the list.
		///
		/// @details
		/// The specified value is copied.
		///
		/// @param value
		/// A value to be appended to the list.
		///
		/// @complexity
		/// Constant - `O(1)`
		///
		/// @pre
		/// <code>@slink{List::size, list.size()} <
		/// @slink{List::max_size, list.max_size()}</code> -
		/// The list must not be full.
		///
		/// @post
		/// Only the past-the-end iterator (`list.end()`) is invalidated.
		void push_back(const value_type & value)
		{
			return this->container.push_back(value);
		}

		/// @brief
		/// Appends the specified value to the end of the list.
		///
		/// @details
		/// The specified value is moved.
		///
		/// @param value
		/// A value to be appended to the list.
		///
		/// @complexity
		/// Constant - `O(1)`
		///
		/// @pre
		/// <code>@slink{List::size, list.size()} <
		/// @slink{List::max_size, list.max_size()}</code> -
		/// The list must not be full.
		///
		/// @post
		/// Only the past-the-end iterator (`list.end()`) is invalidated.
		void push_back(value_type && value)
		{
			return this->container.push_back(utils::move(value));
		}

		/// @brief
		/// Appends a new element to the end of the list.
		///
		/// @details
		/// The new element is constructed in-place with placement new.
		///
		/// @param arguments
		/// Arguments to be passed to `value_type`'s constructor.
		///
		/// @complexity
		/// Constant - `O(1)`
		///
		/// @pre
		/// <code>@slink{List::size, list.size()} <
		/// @slink{List::max_size, list.max_size()}</code> -
		/// The list must not be full.
		///
		/// @post
		/// Only the past-the-end iterator (`list.end()`) is invalidated.
		template<typename ... Arguments>
		reference emplace_back(Arguments && ... arguments)
		{
			return this->container.emplace_back(utils::forward<Arguments>(arguments)...);
		}

		/// @brief
		/// Erases the last element from the list.
		///
		/// @complexity
		/// Constant - `O(1)`
		///
		/// @pre
		/// <code>@slink{List::size, list.size()} > 0</code> -
		/// The list must contain at least one element.
		///
		/// @pre
		/// <code>!@slink{List::empty, list.empty()}</code> - The list must not be empty.
		///
		/// @post
		/// Only the past-the-end iterator (`list.end()`) is invalidated.
		///
		/// @warning
		/// <em>Calling `pop_back()` on an empty list will result in
		/// <strong>undefined behaviour</strong>.</em>
		void pop_back()
		{
			return this->container.pop_back();
		}

		/// @brief
		/// Erases the specified element from the list.
		///
		/// @param element_iterator
		/// An iterator pointing to a valid element of this list.
		///
		/// @complexity
		/// Linear - `O(n)`, where `n` is the distance between
		/// @clink{List::end, list.end()} and `element_iterator`.
		///
		/// @note
		/// `element_iterator` must be dereferenceable,
		/// thus `erase()` cannot be used on the past-the-end iterator
		/// (@clink{List::end, list.end()}).
		iterator erase(iterator element_iterator)
		{
			return this->container.erase(element_iterator);
		}

		/// @brief
		/// Erases all elements from the list.
		///
		/// @post
		/// <code>@slink{List::empty, list.empty()}</code> - The list is empty.
		///
		/// @post
		/// <code>@slink{List::size, list.size()} == 0</code> - Size is equal to zero.
		void clear() noexcept
		{
			return this->container.clear();
		}

		/// @brief
		/// Swaps the contents of this list with the contents of another list
		/// of the same `container_type`.
		///
		/// @param other
		/// The other list.
		///
		/// @complexity
		/// Linear - `O(n)` where `n` is `capacity`.
		///
		/// @attention
		/// Prefer to use
		/// @slink{containers::swap(List &\, List &),`containers::swap(list0\, list1)`}
		/// rather than
		/// @slink{List::swap(List &),`list0.swap(list1)`}.
		void swap(List & other)
		{
			using utils::swap;

			swap(this->elements, other.elements);
		}
	};

	/// @brief
	/// Swaps the contents of two @sref{List, List<Type\, capacity\, Container>}
	/// objects with the same `Type`, `capacity` and `Container`.
	///
	/// @param left, right
	/// The lists to be swapped.
	///
	/// @complexity
	/// Linear - `O(n)` where `n` is `capacity`.
	///
	/// @note
	/// Iterators will remain valid,
	/// and will still point to the list they were created with,
	/// but the values they point to may have changed.
	template<typename Type, size_t capacity, typename Container>
	void swap(List<Type, capacity, Container> & left, List<Type, capacity, Container> & right)
	{
		left.swap(right);
	}
}