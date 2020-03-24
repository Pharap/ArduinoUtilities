#pragma once

// For size_t, ptrdiff_t
#include <stddef.h>

// For utils::size
#include "../utils.h"

namespace containers
{
	// Predeclare as a precaution
	template<typename Container>
	class IndexIterator;

	/// @brief
	/// A simple iterator that refers to the contents of a container
	/// by tracking an index and passing it to the container's `operator[]`.
	///
	/// @details
	/// By using indices as a means of representing the iterator,
	/// this iterator can represent the end iterator by using
	/// @clink{utils::size(const Container &), size(container)}
	/// as the underlying index.
	template<typename Container>
	class IndexIterator
	{
	public:
		/// @brief
		/// The type of container referred to by the iterator.
		using container_type = Container;
		
		/// @brief
		/// The type of the elements pointed to by the iterator.
		using value_type = typename container_type::value_type;

		/// @brief
		/// The unsigned integer type used for indices.
		using size_type = typename container_type::size_type;

		/// @brief
		/// The signed integer type used for measuring the distance between iterators.
		using difference_type = typename container_type::difference_type;

		/// @brief
		/// The type that represents a reference to a mutable container element.
		using reference = typename container_type::reference;

		/// @brief
		/// The type that represents a reference to a read-only container element.
		using const_reference = typename container_type::const_reference;

		/// @brief
		/// The type that represents a pointer to a mutable container element.
		using pointer = typename container_type::pointer;

		/// @brief
		/// The type that represents a pointer to a read-only container element.
		using const_pointer = typename container_type::const_pointer;

	private:
		container_type * container;
		size_type index;

	public:
		/// @brief
		/// Creates a `begin()` iterator for the specified container.
		static constexpr IndexIterator make_begin(container_type & container)
		{
			return IndexIterator(container, 0);
		}

		/// @brief
		/// Creates an `end()` iterator for the specified container.
		static constexpr IndexIterator make_end(container_type & container)
		{
			// This use of `size` is explicitly permitted
			return IndexIterator(container, utils::size(container));
		}

	public:
		/// @brief
		/// Default constructs an invalid iterator.
		///
		/// @note
		/// Exists solely to meet the 
		/// [`DefaultConstructible`](https://en.cppreference.com/w/cpp/named_req/DefaultConstructible)
		/// requirement of
		/// [`LegacyForwardIterator`](https://en.cppreference.com/w/cpp/named_req/ForwardIterator)
		IndexIterator() = default;

		/// @brief
		/// Constructs an iterator from a container and an index.
		///
		/// @pre
		/// `index < utils::size(container)`
		///
		/// @warning
		/// This function is unchecked.
		/// Creating an iterator where `index >= utils::size(container)` will create
		/// an invalid iterator that must not be derefrenced.
		/// <em>Dereferencing such an interator would result in
		/// <strong>undefined behaviour</strong></em>
		constexpr IndexIterator(container_type & container, size_type index) :
			container(&container), index(index)
		{
		}

		/// @brief
		/// Returns a reference to the mutable element referred to by this iterator.
		reference operator *()
		{
			return (*this->container)[this->index];
		}

		/// @brief
		/// Returns a reference to the read-only element referred to by this iterator.
		constexpr const_reference operator *() const
		{
			return (*this->container)[this->index];
		}

		/// @brief
		/// Accesses a member of the mutable element referred to by this iterator.
		pointer operator ->()
		{
			return &(*this->container)[this->index];
		}

		/// @brief
		/// Accesses a member of the read-only element referred to by this iterator.
		constexpr const_pointer operator ->() const
		{
			return &(*this->container)[this->index];
		}

		/// @brief
		/// Increment this iterator so that it points to the next element.
		IndexIterator & operator ++()
		{
			++this->index;
			return *this;
		}

		/// @brief
		/// Increment this iterator as if by `operator ++()`,
		/// returning a cached copy of the iterator's previous value.
		///
		/// @attention
		/// Prefer to use `operator ++()` whenever possible.
		IndexIterator operator ++(int)
		{
			auto result = *this;
			this->operator++();
			return result;
		}

		/// @brief
		/// Decrement this iterator so that it points to the next element.
		IndexIterator & operator --()
		{
			--this->index;
			return *this;
		}

		/// @brief
		/// Decrement this iterator as if by `operator --()`,
		/// returning a cached copy of the iterator's previous value.
		///
		/// @attention
		/// Prefer to use `operator --()` whenever possible.
		IndexIterator operator --(int)
		{
			auto result = *this;
			this->operator--();
			return result;
		}

		/// @brief
		/// Positively offset this iterator by the specified number of elements.
		IndexIterator & operator +=(difference_type offset)
		{
			this->index += offset;
			return *this;
		}

		/// @brief
		/// Negatively offset this iterator by the specified number of elements.
		IndexIterator & operator -=(difference_type offset)
		{
			this->index -= offset;
			return *this;
		}

		/// @brief
		/// Returns the absolute difference between two iterators.
		friend constexpr difference_type operator -(const IndexIterator & left, const IndexIterator & right)
		{
			return (left.index - right.index);
		}

		/// @brief
		/// Creates a new iterator that is negatively offset from `iterator` by `offset` elements.
		friend constexpr IndexIterator operator -(const IndexIterator & iterator, difference_type offset)
		{
			return IndexIterator(iterator.container, iterator.index - offset);
		}

		/// @brief
		/// Creates a new iterator that is positively offset from `iterator` by `offset` elements.
		friend constexpr IndexIterator operator +(const IndexIterator & iterator, difference_type offset)
		{
			return IndexIterator(iterator.container, iterator.index + offset);
		}

		/// @brief
		/// Creates a new iterator that is positively offset from `iterator` by `offset` elements.
		friend constexpr IndexIterator operator +(difference_type offset, const IndexIterator & iterator)
		{
			return IndexIterator(iterator.container, offset + iterator.index);
		}

		/// @brief
		/// Tests whether two iterators represent the same element in the same container.
		friend constexpr bool operator ==(const IndexIterator & left, const IndexIterator & right)
		{
			return ((left.container == right.container) && (left.index == right.index));
		}

		/// @brief
		/// Tests whether two iterators represent different elements or refer to different containers.
		friend constexpr bool operator !=(const IndexIterator & left, const IndexIterator & right)
		{
			return ((left.container != right.container) || (left.index != right.index));
		}

		/// @brief
		/// Tests if `left` is less than `right`,
		/// and both iterators refer to the same container
		///
		/// @details
		/// @parblock
		/// Specifically, returns `true` if:
		/// * Both iterators refer to the same container
		/// * `left` represents an index less than the index represented by `right`
		/// @endparblock
		///
		/// @todo
		/// Consider making comparing iterators from different containers 'undefined',
		/// rather than sanctioning it by performing a specific test.
		friend constexpr bool operator <(const IndexIterator & left, const IndexIterator & right)
		{
			return ((left.container == right.container) && (left.index < right.index));
		}

		/// @brief
		/// Tests if `left` is greater than `right`,
		/// and both iterators refer to the same container
		///
		/// @details
		/// @parblock
		/// Specifically, returns `true` if:
		/// * Both iterators refer to the same container
		/// * `left` represents an index greater than the index represented by `right`
		/// @endparblock
		///
		/// @todo
		/// Consider making comparing iterators from different containers 'undefined',
		/// rather than sanctioning it by performing a specific test.
		friend constexpr bool operator >(const IndexIterator & left, const IndexIterator & right)
		{
			return ((left.container == right.container) && (left.index > right.index));
		}

		/// @brief
		/// Tests if `left` is less than or equal to `right`,
		/// and both iterators refer to the same container
		///
		/// @details
		/// @parblock
		/// Specifically, returns `true` if:
		/// * Both iterators refer to the same container
		/// * `left` represents an index less than or equal to the index represented by `right`
		/// @endparblock
		///
		/// @todo
		/// Consider making comparing iterators from different containers 'undefined',
		/// rather than sanctioning it by performing a specific test.
		friend constexpr bool operator <=(const IndexIterator & left, const IndexIterator & right)
		{
			return ((left.container == right.container) && (left.index <= right.index));
		}

		/// @brief
		/// Tests if `left` is greater than or equal to `right`,
		/// and both iterators refer to the same container
		///
		/// @details
		/// @parblock
		/// Specifically, returns `true` if:
		/// * Both iterators refer to the same container
		/// * `left` represents an index greater than or equal to the index represented by `right`
		/// @endparblock
		///
		/// @todo
		/// Consider making comparing iterators from different containers 'undefined',
		/// rather than sanctioning it by performing a specific test.
		friend constexpr bool operator >=(const IndexIterator & left, const IndexIterator & right)
		{
			return ((left.container == right.container) && (left.index >= right.index));
		}

		/// @brief
		/// Swaps the state of this iterator with the state of another iterator.
		///
		/// @details
		/// Whilst the _type_ of container must remain the same,
		/// the container that each iterator refers to need not be the same.
		/// Which is to say,
		/// two iterators referring to different containers of the same type may be swapped.
		///
		/// @param other
		/// The other iterator.
		///
		/// @complexity
		/// Constant - `O(1)`
		///
		/// @note
		/// While (for example) two `IndexIterator<Deque<int, 10>>`s may be swapped with each other,
		/// an `IndexIterator<Deque<int, 10>>` may not be swapped with an `IndexIterator<Deque<int, 8>>`.
		/// It is theoretically possible, but is not presently a priority.
		///
		/// @attention
		/// Prefer to use
		/// @slink{containers::swap(IndexIterator &\, IndexIterator &),`containers::swap(iterator0\, iterator1)`}
		/// rather than
		/// @slink{IndexIterator::swap(IndexIterator &),`iterator0.swap(iterator1)`}.
		///
		/// @todo
		/// Permit swapping of `IndexIterator<Container<Type, capacity0>>`
		/// with `IndexIterator<Container<Type, capacity1>>`,
		/// where `Container` is a `<Type, capacity>`-style container like
		/// `containers::Deque`, `containers::CircularDeque` and `utils::Array`.
		void swap(IndexIterator & other)
		{
			using utils::swap;

			swap(this->container, other.container);
			swap(this->index, other.index);
		}
	};	

	/// @brief
	/// Swaps the contents of two @sref{IndexIterator, IndexIterator<Container>}
	/// objects with the same `Container` type.
	///
	/// @param left, right
	/// The iterators to be swapped.
	///
	/// @complexity
	/// Constant - `O(1)`
	template<typename Container>
	void swap(IndexIterator<Container> & left, IndexIterator<Container> & right)
	{
		left.swap(right);
	}
}