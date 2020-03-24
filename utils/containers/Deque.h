#pragma once

// For size_t, ptrdiff_t
#include <stddef.h>

// For utils::Array, utils::move
#include "../utils.h"

namespace containers
{
	// Predeclare as a precaution
	template<typename Type, size_t capacity>
	class Deque;

	/// @brief
	/// A simple double-ended queue implemented with an array and a size counter.
	///
	/// @note
	/// This class is simpler and uses less memory than `CircularDeque`,
	/// but has `O(n)` insertion and deletion at the front.
	template<typename Type, size_t capacity>
	class Deque
	{
	public:
		/// @brief
		/// The type of the elements stored in the deque.
		using value_type = Type;

		/// @brief
		/// The unsigned integer type used for measuring the size of the deque.
		/// Also used to represent deque indices.
		using size_type = size_t;

		/// @brief
		/// The signed integer type used for measuring the distance between deque elements.
		using difference_type = ptrdiff_t;

		/// @brief
		/// The type that represents a reference to a mutable deque element.
		using reference = value_type &;

		/// @brief
		/// The type that represents a reference to a read-only deque element.
		using const_reference = const value_type &;

		/// @brief
		/// The type that represents a pointer to a mutable deque element.
		using pointer = value_type *;

		/// @brief
		/// The type that represents a pointer to a read-only deque element.
		using const_pointer = const value_type *;

		/// @brief
		/// The type used as an iterator to mutable deque elements.
		using iterator = pointer;

		/// @brief
		/// The type used as an iterator to read-only deque elements.
		using const_iterator = const_pointer;

	private:
		utils::Array<value_type, capacity> elements;
		size_type element_count = 0;

	private:
		constexpr size_type get_first_index() const
		{
			return 0;
		}

		constexpr size_type get_last_index() const
		{
			return (this->element_count - 1);
		}

		constexpr size_type get_begin_index() const
		{
			return 0;
		}

		constexpr size_type get_end_index()
		{
			return this->element_count;
		}

	public:
		/// @brief
		/// Returns `true` if the deque is empty, returns `false` otherwise.
		///
		/// @details
		/// Equivalent to <code>@slink{Deque::size(), deque.size()} > 0</code>.
		constexpr bool empty() const noexcept
		{
			return (element_count == 0);
		}

		/// @brief
		/// Returns the number of elements in the deque.
		///
		/// @attention
		/// Prefer to use @slink{utils::size(const Container &),`utils::size(deque)`}
		/// rather than @slink{Deque::size(),`deque.size()`}.
		constexpr size_type size() const noexcept
		{
			return element_count;
		}

		/// @brief
		/// Returns the maximum number of elements in the deque.
		constexpr size_type max_size() const noexcept
		{
			return capacity;
		}

		/// @brief
		/// Returns a mutable reference to the first element of the deque.
		///
		/// @pre
		/// <code>@slink{Deque::size, deque.size()} > 0</code> -
		/// The deque must contain at least one element.
		///
		/// @pre
		/// <code>!@slink{Deque::empty, deque.empty()}</code> - The deque must not be empty.
		///
		/// @warning
		/// Do not attempt to call `front()` if the deque is empty.
		/// <em>Doing so will result in <strong>undefined behaviour</strong></em>.
		reference front()
		{
			return this->elements[this->get_first_index()];
		}

		/// @brief
		/// Returns a read-only reference to the first element of the deque.
		///
		/// @pre
		/// <code>@slink{Deque::size, deque.size()} > 0</code> -
		/// The deque must contain at least one element.
		///
		/// @pre
		/// <code>!@slink{Deque::empty, deque.empty()}</code> - The deque must not be empty.
		///
		/// @warning
		/// Do not attempt to call `front()` if the deque is empty.
		/// <em>Doing so will result in <strong>undefined behaviour</strong></em>.
		constexpr const_reference front() const
		{
			return this->elements[this->get_first_index()];
		}

		/// @brief
		/// Returns a mutable reference to the last element of the deque.
		///
		/// @pre
		/// <code>@slink{Deque::size, deque.size()} > 0</code> -
		/// The deque must contain at least one element.
		///
		/// @pre
		/// <code>!@slink{Deque::empty, deque.empty()}</code> - The deque must not be empty.
		///
		/// @warning
		/// Do not attempt to call `back()` if the deque is empty.
		/// <em>Doing so will result in <strong>undefined behaviour</strong></em>.
		reference back()
		{
			return this->elements[this->get_last_index()];
		}

		/// @brief
		/// Returns a read-only reference to the last element of the deque.
		///
		/// @pre
		/// <code>@slink{Deque::size, deque.size()} > 0</code> -
		/// The deque must contain at least one element.
		///
		/// @pre
		/// <code>!@slink{Deque::empty, deque.empty()}</code> - The deque must not be empty.
		///
		/// @warning
		/// Do not attempt to call `back()` if the deque is empty.
		/// <em>Doing so will result in <strong>undefined behaviour</strong></em>.
		constexpr const_reference back() const
		{
			return this->elements[this->get_last_index()];
		}

		/// @brief
		/// Returns a pointer to the first element of the underlying array.
		pointer data() noexcept
		{
			return &this->elements[this->get_first_index()];
		}

		/// @brief
		/// Returns a const pointer to the first element of the underlying array.
		constexpr const_pointer data() const noexcept
		{
			return &this->elements[this->get_first_index()];
		}

		/// @brief
		/// Returns a mutable reference to the element at the specified index.
		///
		/// @param index
		/// The index of the requested deque element.
		///
		/// @pre
		/// <code>@slink{Deque::size, deque.size()} > 0</code> -
		/// The deque must contain at least one element.
		///
		/// @pre
		/// <code>!@slink{Deque::empty, deque.empty()}</code> -
		/// The deque must not be empty.
		///
		/// @pre
		/// <code>index < @slink{Deque::size(), deque.size()}</code> -
		/// `index` must be less than `size()`.
		///
		/// @warning
		/// This function does no bounds checking.
		/// <em>Providing an `index` that is greater than or equal to @slink{Deque::size(),`deque.size()`}
		/// will result in a buffer overrun, which is <strong>undefined behaviour</strong></em>.
		reference operator[](size_type index)
		{
			return this->elements[index];
		}

		/// @brief
		/// Returns a read-only reference to the element at the specified index.
		///
		/// @param index
		/// The index of the requested deque element.
		///
		/// @pre
		/// <code>@slink{Deque::size, deque.size()} > 0</code> -
		/// The deque must contain at least one element.
		///
		/// @pre
		/// <code>!@slink{Deque::empty, deque.empty()}</code> -
		/// The deque must not be empty.
		///
		/// @pre
		/// <code>index < @slink{Deque::size(), deque.size()}</code> -
		/// `index` must be less than `size()`.
		///
		/// @warning
		/// This function does no bounds checking.
		/// <em>Providing an `index` that is greater than or equal to
		/// @slink{Deque::size(),`deque.size()`}
		/// will result in a buffer overrun, which is <strong>undefined behaviour</strong></em>.
		constexpr const_reference operator[](size_type index) const
		{
			return this->elements[index];
		}

		/// @brief
		/// Returns an iterator pointing to the first element of the deque.
		///
		/// @pre
		/// <code>@slink{Deque::size, deque.size()} > 0</code> -
		/// The deque must contain at least one element.
		///
		/// @pre
		/// <code>!@slink{Deque::empty, deque.empty()}</code> -
		/// The deque must not be empty.
		///
		/// @warning
		/// Do not attempt to dereference the returned iterator if the deque is empty.
		/// <em>Doing so will result in <strong>undefined behaviour</strong></em>.
		iterator begin() noexcept
		{
			return &this->elements[this->get_begin_index()];
		}

		/// @brief
		/// Returns a const iterator pointing to the first element of the deque.
		///
		/// @pre
		/// <code>@slink{Deque::size, deque.size()} > 0</code> -
		/// The deque must contain at least one element.
		///
		/// @pre
		/// <code>!@slink{Deque::empty, deque.empty()}</code> -
		/// The deque must not be empty.
		///
		/// @warning
		/// Do not attempt to dereference the returned iterator if the deque is empty.
		/// <em>Doing so will result in <strong>undefined behaviour</strong></em>.
		constexpr const_iterator begin() const noexcept
		{
			return &this->elements[this->get_begin_index()];
		}

		/// @brief
		/// Returns a const iterator pointing to the first element of the deque.
		///
		/// @pre
		///
		/// @pre
		/// <code>@slink{Deque::size, deque.size()} > 0</code> -
		/// The deque must contain at least one element.
		///
		/// @pre
		/// <code>!@slink{Deque::empty, deque.empty()}</code> -
		/// The deque must not be empty.
		///
		/// @warning
		/// Do not attempt to dereference the returned iterator if the deque is empty.
		/// <em>Doing so will result in <strong>undefined behaviour</strong></em>.
		constexpr const_iterator cbegin() const noexcept
		{
			return &this->elements[this->get_begin_index()];
		}

		/// @brief
		/// Returns a past-the-end iterator pointing beyond the last element of the deque.
		///
		/// @warning
		/// Do not attempt to dereference the returned iterator.
		/// <em>Doing so will result in <strong>undefined behaviour</strong></em>.
		iterator end() noexcept
		{
			return &this->elements[this->get_end_index()];
		}

		/// @brief
		/// Returns a past-the-end const iterator pointing beyond the last element of the deque.
		///
		/// @warning
		/// Do not attempt to dereference the returned iterator.
		/// <em>Doing so will result in <strong>undefined behaviour</strong></em>.
		constexpr const_iterator end() const noexcept
		{
			return &this->elements[this->get_end_index()];
		}

		/// @brief
		/// Returns a past-the-end const iterator pointing beyond the last element of the deque.
		///
		/// @warning
		/// Do not attempt to dereference the returned iterator.
		/// <em>Doing so will result in <strong>undefined behaviour</strong></em>.
		constexpr const_iterator cend() const noexcept
		{
			return &this->elements[this->get_end_index()];
		}

		/// @brief
		/// Appends the specified value to the end of the deque.
		///
		/// @details
		/// The specified value is copied.
		///
		/// @param value
		/// A value to be appended to the deque.
		///
		/// @complexity
		/// Constant - `O(1)`
		///
		/// @pre
		/// <code>@slink{Deque::size, deque.size()} <
		/// @slink{Deque::max_size, deque.max_size()}</code> -
		/// The deque must not be full.
		///
		/// @post
		/// Only the past-the-end iterator (`deque.end()`) is invalidated.
		void push_back(const value_type & value)
		{
			#if defined(CONTAINER_SAFETY)
			// If there's no room, exit
			if(this->size() >= this->max_size())
				return;
			#endif

			// Copy the value
			this->elements[this->element_count] = value;

			// Increase the element count
			++this->element_count;
		}

		/// @brief
		/// Appends the specified value to the end of the deque.
		///
		/// @details
		/// The specified value is moved.
		///
		/// @param value
		/// A value to be appended to the deque.
		///
		/// @complexity
		/// Constant - `O(1)`
		///
		/// @pre
		/// <code>@slink{Deque::size, deque.size()} <
		/// @slink{Deque::max_size, deque.max_size()}</code> -
		/// The deque must not be full.
		///
		/// @post
		/// Only the past-the-end iterator (`deque.end()`) is invalidated.
		void push_back(value_type && value)
		{
			#if defined(CONTAINER_SAFETY)
			// If there's no room, exit
			if(this->size() >= this->max_size())
				return;
			#endif

			// Move the value
			this->elements[this->element_count] = utils::move(value);

			// Increase the element count
			++this->element_count;
		}

		/// @brief
		/// Appends a new element to the end of the deque.
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
		/// <code>@slink{Deque::size, deque.size()} <
		/// @slink{Deque::max_size, deque.max_size()}</code> -
		/// The deque must not be full.
		///
		/// @post
		/// Only the past-the-end iterator (`deque.end()`) is invalidated.
		template<typename ... Arguments>
		reference emplace_back(Arguments && ... arguments)
		{
			#if defined(CONTAINER_SAFETY)
			// If there's no room, exit
			if(this->size() >= this->max_size())
				return;
			#endif

			// Cache the element index
			const size_type element_index = this->element_count;

			// Construct the value with placement new
			new (&this->elements[element_index]) value_type(utils::forward<Arguments>(arguments)...);

			// Increase the element count
			++this->element_count;

			// Return a reference to the created element
			return this->elements[element_index];
		}

		/// @brief
		/// Erases the last element from the deque.
		///
		/// @complexity
		/// Constant - `O(1)`
		///
		/// @pre
		/// <code>@slink{Deque::size, deque.size()} > 0</code> -
		/// The deque must contain at least one element.
		///
		/// @pre
		/// <code>!@slink{Deque::empty, deque.empty()}</code> - The deque must not be empty.
		///
		/// @post
		/// Only the past-the-end iterator (`deque.end()`) is invalidated.
		///
		/// @warning
		/// <em>Calling `pop_back()` on an empty deque will result in
		/// <strong>undefined behaviour</strong>.</em>
		void pop_back()
		{
			#if defined(CONTAINER_SAFETY)
			// If the deque is empty, exit
			if(this->empty())
				return;
			#endif

			// Decrease the element count
			--this->element_count;

			// And destroy the last value
			this->elements[this->element_count].~value_type();
		}

		/// @brief
		/// Prepends the specified value to the beginning of the deque.
		///
		/// @details
		/// The specified value is copied.
		///
		/// @param value
		/// A value to be prepended to the deque.
		///
		/// @complexity
		/// Linear - `O(n)`, where `n` is `deque.size()`.
		///
		/// @pre
		/// <code>@slink{Deque::size, deque.size()} <
		/// @slink{Deque::max_size, deque.max_size()}</code> -
		/// The deque must not be full.
		///
		/// @post
		/// <em>All</em> iterators are invalidated.
		///
		/// @warning
		/// <em>Calling `push_front()` on a full deque will result in
		/// <strong>undefined behaviour</strong>.</em>
		void push_front(const value_type & value)
		{
			#if defined(CONTAINER_SAFETY)
			// If there's no room, exit
			if(this->size() >= this->max_size())
				return;
			#endif

			// Move the array elements back to make room
			for(size_type index = this->element_count; index > 0; --index)
				this->elements[index] = utils::move(this->elements[index - 1]);

			// Copy the value
			this->elements[0] = value;

			// Increase the element count
			++this->element_count;
		}

		/// @brief
		/// Prepends the specified value to the beginning of the deque.
		///
		/// @details
		/// The specified value is moved.
		///
		/// @param value
		/// A value to be prepended to the deque.
		///
		/// @complexity
		/// Linear - `O(n)`, where `n` is `deque.size()`.
		///
		/// @pre
		/// <code>@slink{Deque::size, deque.size()} <
		/// @slink{Deque::max_size, deque.max_size()}</code> -
		/// The deque must not be full.
		///
		/// @post
		/// <em>All</em> iterators are invalidated.
		///
		/// @warning
		/// <em>Calling `push_front()` on a full deque will result in
		/// <strong>undefined behaviour</strong>.</em>
		void push_front(value_type && value)
		{
			#if defined(CONTAINER_SAFETY)
			// If there's no room, exit
			if(this->size() >= this->max_size())
				return;
			#endif

			// Move the array elements back to make room
			for(size_type index = this->element_count; index > 0; --index)
				this->elements[index] = utils::move(this->elements[index - 1]);

			// Move the value
			this->elements[0] = utils::move(value);

			// Increase the element count
			++this->element_count;
		}

		/// @brief
		/// Prepends a new element at the beginning of the deque.
		///
		/// @details
		/// The new element is constructed in-place with placement new.
		///
		/// @param arguments
		/// Arguments to be passed to `value_type`'s constructor.
		///
		/// @complexity
		/// Linear - `O(n)`, where `n` is `deque.size()`.
		///
		/// @pre
		/// <code>@slink{Deque::size, deque.size()} <
		/// @slink{Deque::max_size, deque.max_size()}</code> -
		/// The deque must not be full.
		///
		/// @post
		/// <em>All</em> iterators are invalidated.
		///
		/// @warning
		/// <em>Calling `emplace_front()` on a full deque will result in
		/// <strong>undefined behaviour</strong>.</em>
		template<typename ... Arguments>
		reference emplace_front(Arguments && ... arguments)
		{
			#if defined(CONTAINER_SAFETY)
			// If there's no room, exit
			if(this->size() >= this->max_size())
				return;
			#endif

			// Move the array elements back to make room
			for(size_type index = this->element_count; index > 0; --index)
				this->elements[index] = utils::move(this->elements[index - 1]);

			// Construct the value with placement new
			new (&this->elements[0]) value_type(utils::forward<Arguments>(arguments)...);

			// Increase the element count
			++this->element_count;

			// Return a reference to the created element
			return this->elements[0];
		}

		/// @brief
		/// Erases the first element from the deque.
		///
		/// @complexity
		/// Linear - `O(n)`, where `n` is `size()`.
		///
		/// @pre
		/// <code>@slink{Deque::size, deque.size()} > 0</code> -
		/// The deque must contain at least one element.
		///
		/// @pre
		/// <code>!@slink{Deque::empty, deque.empty()}</code> - The deque must not be empty.
		///
		/// @post
		/// <em>All</em> iterators are invalidated.
		///
		/// @warning
		/// <em>Calling `pop_front()` on an empty deque will result in
		/// <strong>undefined behaviour</strong>.</em>
		void pop_front()
		{
			#if defined(CONTAINER_SAFETY)
			// If the deque is empty, exit
			if(this->empty())
				return;
			#endif

			// Move the array elements forward
			for(size_type index = 0; index < this->element_count; ++index)
				this->elements[index] = utils::move(this->elements[index + 1]);

			// Decrease the element count
			--this->element_count;
		}

		/// @brief
		/// Erases the specified element from the deque.
		///
		/// @param element_iterator
		/// An iterator pointing to a valid element of this deque.
		///
		/// @complexity
		/// Linear - `O(n)`, where `n` is the distance between
		/// @clink{Deque::end, deque.end()} and `element_iterator`.
		///
		/// @note
		/// `element_iterator` must be dereferenceable,
		/// thus `erase()` cannot be used on the past-the-end iterator
		/// (@clink{Deque::end, deque.end()}).
		iterator erase(iterator element_iterator)
		{
			#if defined(CONTAINER_SAFETY)
			// If the deque is empty, exit
			if(this->empty())
				return;

			// If the element_iterator is the end iterator, exit
			if(element_iterator == this->end())
				return;
			#endif

			// Cache the end iterator
			iterator end_iterator = this->end();

			// Track the current and next elements
			iterator current = element_iterator;
			iterator next = element_iterator;
			++next;

			// Move elements forward
			// until the next element is the end element
			while(next != end_iterator)
			{
				*current = utils::move(*next);
				++current;
				++next;
			}

			// Decrease the element count
			--this->element_count;
		}

		/// @brief
		/// Erases all elements from the deque.
		///
		/// @post
		/// <code>@slink{Deque::empty, deque.empty()}</code> - The deque is empty.
		///
		/// @post
		/// <code>@slink{Deque::size, deque.size()} == 0</code> - Size is equal to zero.
		void clear() noexcept
		{
			// Destroy all elements
			for(size_type index = get_begin_index(); index < get_end_index(); ++index)
				this->elements[index].~value_type();

			// Set the element count to zero
			this->element_count = 0;
		}

		/// @brief
		/// Swaps the contents of this deque with the contents of
		/// another deque of the same `Type` and `capacity`.
		///
		/// @param other
		/// The other deque.
		///
		/// @complexity
		/// Linear - `O(n)` where `n` is `capacity`.
		///
		/// @attention
		/// Prefer to use
		/// @slink{containers::swap(Deque &\, Deque &),`containers::swap(deque0\, deque1)`}
		/// rather than
		/// @slink{Deque::swap(Deque &),`deque0.swap(deque1)`}.
		void swap(Deque & other)
		{
			using utils::swap;

			swap(this->elements, other.elements);
		}
	};

	/// @brief
	/// Swaps the contents of two @sref{Deque, Deque<Type\, capacity>}
	/// objects with the same `Type` and `capacity`.
	///
	/// @param left, right
	/// The deques to be swapped.
	///
	/// @complexity
	/// Linear - `O(n)` where `n` is `capacity`.
	///
	/// @note
	/// Iterators will remain valid,
	/// and will still point to the deque they were created with,
	/// but the values they point to may have changed.
	template<typename Type, size_t capacity>
	void swap(Deque<Type, capacity> & left, Deque<Type, capacity> & right)
	{
		left.swap(right);
	}
}