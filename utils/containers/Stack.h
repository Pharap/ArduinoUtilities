#pragma once

// For size_t
#include <stddef.h>

#include "Deque.h"

namespace containers
{
	// Predeclare as a precaution
	template<typename Type, size_t capacity, typename Container>
	class Stack;

	/// @brief
	/// A container adapter class representing a stack (a 'last in first out' container).
	template<typename Type, size_t capacity, typename Container = Deque<Type, capacity>>
	class Stack
	{
	public:
		/// @brief
		/// The type of container adapted by the stack.
		using container_type = Container;
		
		/// @brief
		/// The type of the elements contained by the stack.
		using value_type = typename container_type::value_type;

		/// @brief
		/// The unsigned integer type used for indices.
		using size_type = typename container_type::size_type;

		/// @brief
		/// The type that represents a reference to a mutable stack element.
		using reference = typename container_type::reference;

		/// @brief
		/// The type that represents a reference to a read-only stack element.
		using const_reference = typename container_type::const_reference;

	private:
		container_type container;

	public:
		/// @brief
		/// Returns `true` if the stack is empty, returns `false` otherwise.
		///
		/// @details
		/// Equivalent to <code>@slink{Stack::size(), stack.size()} > 0</code>.
		constexpr bool empty() const noexcept
		{
			return this->container.empty();
		}

		/// @brief
		/// Returns the number of elements in the stack.
		///
		/// @attention
		/// Prefer to use @slink{utils::size(const Container &),`utils::size(stack)`}
		/// rather than @slink{Stack::size(),`stack.size()`}.
		constexpr size_type size() const noexcept
		{
			return this->container.size();
		}

		/// @brief
		/// Returns the maximum number of elements in the stack.
		constexpr size_type max_size() const noexcept
		{
			return this->container.max_size();
		}

		/// @brief
		/// Returns a mutable reference to the last element of the stack.
		///
		/// @pre
		/// <code>@slink{Stack::size, stack.size()} > 0</code> -
		/// The stack must contain at least one element.
		///
		/// @pre
		/// <code>!@slink{Stack::empty, stack.empty()}</code> - The stack must not be empty.
		///
		/// @warning
		/// Do not attempt to call `top()` if the stack is empty.
		/// <em>Doing so will result in <strong>undefined behaviour</strong></em>.
		reference top()
		{
			return this->container.back();
		}

		/// @brief
		/// Returns a read-only reference to the top element of the stack.
		///
		/// @pre
		/// <code>@slink{Stack::size, stack.size()} > 0</code> -
		/// The stack must contain at least one element.
		///
		/// @pre
		/// <code>!@slink{Stack::empty, stack.empty()}</code> - The stack must not be empty.
		///
		/// @warning
		/// Do not attempt to call `top()` if the stack is empty.
		/// <em>Doing so will result in <strong>undefined behaviour</strong></em>.
		constexpr const_reference top() const
		{
			return this->container.back();
		}

		/// @brief
		/// Adds the specified value to the top of the stack.
		///
		/// @details
		/// The specified value is copied.
		///
		/// @param value
		/// A value to be pushed onto the stack.
		///
		/// @complexity
		/// Same as `Container::push_back`.
		///
		/// @pre
		/// <code>@slink{Stack::size, stack.size()} <
		/// @slink{Stack::max_size, stack.max_size()}</code> -
		/// The stack must not be full.
		void push(const value_type & value)
		{
			return this->container.push_back(value);
		}

		/// @brief
		/// Adds the specified value to the top of the stack.
		///
		/// @details
		/// The specified value is moved.
		///
		/// @param value
		/// A value to be pushed onto the stack.
		///
		/// @complexity
		/// Same as `Container::push_back`.
		///
		/// @pre
		/// <code>@slink{Stack::size, stack.size()} <
		/// @slink{Stack::max_size, stack.max_size()}</code> -
		/// The stack must not be full.
		void push(value_type && value)
		{
			return this->container.push_back(utils::move(value));
		}

		/// @brief
		/// Adds a new element to the top of the stack.
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
		/// <code>@slink{Stack::size, stack.size()} <
		/// @slink{Stack::max_size, stack.max_size()}</code> -
		/// The stack must not be full.
		///
		/// @post
		/// Only the past-the-end iterator (`stack.end()`) is invalidated.
		template<typename ... Arguments>
		reference emplace(Arguments && ... arguments)
		{
			return this->container.emplace_back(utils::forward<Arguments>(arguments)...);
		}

		/// @brief
		/// Drops the top element from the stack.
		///
		/// @complexity
		/// Same as `Container::pop_back`.
		///
		/// @pre
		/// <code>@slink{Stack::size, stack.size()} > 0</code> -
		/// The stack must contain at least one element.
		///
		/// @pre
		/// <code>!@slink{Stack::empty, stack.empty()}</code> - The stack must not be empty.
		///
		/// @warning
		/// <em>Calling `pop()` on an empty stack will result in
		/// <strong>undefined behaviour</strong>.</em>
		void pop()
		{
			return this->container.pop_back();
		}

		/// @brief
		/// Swaps the contents of this stack with the contents of another stack
		/// of the same `container_type`.
		///
		/// @param other
		/// The other stack.
		///
		/// @complexity
		/// Linear - `O(n)` where `n` is `capacity`.
		///
		/// @attention
		/// Prefer to use
		/// @slink{containers::swap(Stack &\, Stack &),`containers::swap(stack0\, stack1)`}
		/// rather than
		/// @slink{Stack::swap(Stack &),`stack0.swap(stack1)`}.
		void swap(Stack & other)
		{
			using utils::swap;

			swap(this->container, other.container);
		}
	};

	/// @brief
	/// Swaps the contents of two @sref{Stack, Stack<Type\, capacity\, Container>}
	/// objects with the same `Type`, `capacity` and `Container`.
	///
	/// @param left, right
	/// The stacks to be swapped.
	///
	/// @complexity
	/// Linear - `O(n)` where `n` is `capacity`.
	template<typename Type, size_t capacity, typename Container>
	void swap(Stack<Type, capacity, Container> & left, Stack<Type, capacity, Container> & right)
	{
		left.swap(right);
	}
}