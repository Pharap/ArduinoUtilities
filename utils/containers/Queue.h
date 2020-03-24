#pragma once

// For size_t
#include <stddef.h>

#include "Deque.h"
#include "CircularDeque.h"

namespace containers
{
	// Predeclare as a precaution
	template<typename Type, size_t capacity, typename Container>
	class Queue;

	/// @brief
	/// A container adapter class representing a queue (a 'first in first out' container).
	template<typename Type, size_t capacity, typename Container = Deque<Type, capacity>>
	class Queue
	{
	public:
		/// @brief
		/// The type of container adapted by the queue.
		using container_type = Container;
		
		/// @brief
		/// The type of the elements contained by the queue.
		using value_type = typename container_type::value_type;

		/// @brief
		/// The unsigned integer type used for indices.
		using size_type = typename container_type::size_type;

		/// @brief
		/// The type that represents a reference to a mutable queue element.
		using reference = typename container_type::reference;

		/// @brief
		/// The type that represents a reference to a read-only queue element.
		using const_reference = typename container_type::const_reference;

	private:
		container_type container;

	public:
		/// @brief
		/// Returns `true` if the queue is empty, returns `false` otherwise.
		///
		/// @details
		/// Equivalent to <code>@slink{Queue::size(), queue.size()} > 0</code>.
		constexpr bool empty() const noexcept
		{
			return this->container.empty();
		}

		/// @brief
		/// Returns the number of elements in the queue.
		///
		/// @attention
		/// Prefer to use @slink{utils::size(const Container &),`utils::size(queue)`}
		/// rather than @slink{Queue::size(),`queue.size()`}.
		constexpr size_type size() const noexcept
		{
			return this->container.size();
		}

		/// @brief
		/// Returns the maximum number of elements in the queue.
		constexpr size_type max_size() const noexcept
		{
			return this->container.max_size();
		}

		/// @brief
		/// Returns a mutable reference to the first element of the queue.
		///
		/// @pre
		/// <code>@slink{Queue::size, queue.size()} > 0</code> -
		/// The queue must contain at least one element.
		///
		/// @pre
		/// <code>!@slink{Queue::empty, queue.empty()}</code> - The queue must not be empty.
		///
		/// @warning
		/// Do not attempt to call `front()` if the queue is empty.
		/// <em>Doing so will result in <strong>undefined behaviour</strong></em>.
		reference front()
		{
			return this->container.front();
		}

		/// @brief
		/// Returns a read-only reference to the first element of the queue.
		///
		/// @pre
		/// <code>@slink{Queue::size, queue.size()} > 0</code> -
		/// The queue must contain at least one element.
		///
		/// @pre
		/// <code>!@slink{Queue::empty, queue.empty()}</code> - The queue must not be empty.
		///
		/// @warning
		/// Do not attempt to call `front()` if the queue is empty.
		/// <em>Doing so will result in <strong>undefined behaviour</strong></em>.
		constexpr const_reference front() const
		{
			return this->container.front();
		}

		/// @brief
		/// Returns a mutable reference to the last element of the queue.
		///
		/// @pre
		/// <code>@slink{Queue::size, queue.size()} > 0</code> -
		/// The queue must contain at least one element.
		///
		/// @pre
		/// <code>!@slink{Queue::empty, queue.empty()}</code> - The queue must not be empty.
		///
		/// @warning
		/// Do not attempt to call `back()` if the queue is empty.
		/// <em>Doing so will result in <strong>undefined behaviour</strong></em>.
		reference back()
		{
			return this->container.back();
		}

		/// @brief
		/// Returns a read-only reference to the last element of the queue.
		///
		/// @pre
		/// <code>@slink{Queue::size, queue.size()} > 0</code> -
		/// The queue must contain at least one element.
		///
		/// @pre
		/// <code>!@slink{Queue::empty, queue.empty()}</code> - The queue must not be empty.
		///
		/// @warning
		/// Do not attempt to call `back()` if the queue is empty.
		/// <em>Doing so will result in <strong>undefined behaviour</strong></em>.
		constexpr const_reference back() const
		{
			return this->container.back();
		}

		/// @brief
		/// Appends the specified value to the end of the queue.
		///
		/// @details
		/// The specified value is copied.
		///
		/// @param value
		/// A value to be appended to the queue.
		///
		/// @complexity
		/// Same as `Container::push_back`.
		///
		/// @pre
		/// <code>@slink{Queue::size, queue.size()} <
		/// @slink{Queue::max_size, queue.max_size()}</code> -
		/// The queue must not be full.
		void push(const value_type & value)
		{
			return this->container.push_back(value);
		}

		/// @brief
		/// Appends the specified value to the end of the queue.
		///
		/// @details
		/// The specified value is moved.
		///
		/// @param value
		/// A value to be appended to the queue.
		///
		/// @complexity
		/// Same as `Container::push_back`.
		///
		/// @pre
		/// <code>@slink{Queue::size, queue.size()} <
		/// @slink{Queue::max_size, queue.max_size()}</code> -
		/// The queue must not be full.
		void push(value_type && value)
		{
			return this->container.push_back(utils::move(value));
		}

		/// @brief
		/// Appends a new element to the end of the queue.
		///
		/// @details
		/// The new element is constructed in-place with placement new.
		///
		/// @param arguments
		/// Arguments to be passed to `value_type`'s constructor.
		///
		/// @complexity
		/// Same as `Container::emplace_back`.
		///
		/// @pre
		/// <code>@slink{Queue::size, queue.size()} <
		/// @slink{Queue::max_size, queue.max_size()}</code> -
		/// The queue must not be full.
		template<typename ... Arguments>
		reference emplace(Arguments && ... arguments)
		{
			return this->container.emplace_back(utils::forward<Arguments>(arguments)...);
		}

		/// @brief
		/// Erases the first element from the queue.
		///
		/// @complexity
		/// Same as `Container::pop_front`.
		///
		/// @pre
		/// <code>@slink{Queue::size, queue.size()} > 0</code> -
		/// The queue must contain at least one element.
		///
		/// @pre
		/// <code>!@slink{Queue::empty, queue.empty()}</code> - The queue must not be empty.
		///
		/// @warning
		/// <em>Calling `pop()` on an empty queue will result in
		/// <strong>undefined behaviour</strong>.</em>
		void pop()
		{
			return this->container.pop_front();
		}

		/// @brief
		/// Swaps the contents of this queue with the contents of another queue
		/// of the same `container_type`.
		///
		/// @param other
		/// The other queue.
		///
		/// @complexity
		/// Linear - `O(n)` where `n` is `capacity`.
		///
		/// @attention
		/// Prefer to use
		/// @slink{containers::swap(Queue &\, Queue &),`containers::swap(queue0\, queue1)`}
		/// rather than
		/// @slink{Queue::swap(Queue &),`queue0.swap(queue1)`}.
		void swap(Queue & other)
		{
			using utils::swap;

			swap(this->container, other.container);
		}
	};

	/// @brief
	/// Swaps the contents of two @sref{Queue, Queue<Type\, capacity\, Container>}
	/// objects with the same `Type`, `capacity` and `Container`.
	///
	/// @param left, right
	/// The queues to be swapped.
	///
	/// @complexity
	/// Linear - `O(n)` where `n` is `capacity`.
	template<typename Type, size_t capacity, typename Container>
	void swap(Queue<Type, capacity, Container> & left, Queue<Type, capacity, Container> & right)
	{
		left.swap(right);
	}

	/// @brief
	/// An alias for a `Queue` that uses `CircularDeque` as its container.
	template<typename Type, size_t capacity>
	using FastQueue = Queue<Type, capacity, CircularDeque<Type, capacity>>;
}