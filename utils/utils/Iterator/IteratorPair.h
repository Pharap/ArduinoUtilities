#pragma once

// For forward, begin, end
#include "../utils.h"

namespace utils
{
	/// @brief
	/// Represents a pair of iterators of different types.
	template<typename BeginIterator, typename EndIterator = BeginIterator>
	class IteratorPair
	{
	public:
		using begin_iterator_type = BeginIterator;
		using end_iterator_type = EndIterator;

	private:
		begin_iterator_type begin_iterator;
		end_iterator_type end_iterator;

	public:
		constexpr IteratorPair(begin_iterator_type && begin_iterator, end_iterator_type && end_iterator) :
			begin_iterator(utils::forward<begin_iterator_type>(begin_iterator)),
			end_iterator(utils::forward<end_iterator_type>(end_iterator))
		{
		}

		constexpr begin_iterator_type begin() const
		{
			return this->begin_iterator;
		}

		constexpr end_iterator_type end() const
		{
			return this->end_iterator;
		}
	};

	/// @brief
	/// Represents a pair of iterators of the same type.
	template<typename Iterator>
	class IteratorPair<Iterator, Iterator>
	{
	public:
		using iterator_type = Iterator;
		using begin_iterator_type = Iterator;
		using end_iterator_type = Iterator;

	private:
		iterator_type begin_iterator;
		iterator_type end_iterator;

	public:
		constexpr IteratorPair(iterator_type && begin_iterator, iterator_type && end_iterator) :
			begin_iterator(utils::forward<iterator_type>(begin_iterator)),
			end_iterator(utils::forward<iterator_type>(end_iterator))
		{
		}

		constexpr iterator_type begin() const
		{
			return this->begin_iterator;
		}

		constexpr iterator_type end() const
		{
			return this->end_iterator;
		}
	};

	template<typename BeginIterator, typename EndIterator = BeginIterator>
	constexpr auto makeIteratorPair(BeginIterator && begin_iterator, EndIterator && end_iterator) ->
		IteratorPair<BeginIterator, EndIterator>
	{
		return { begin_iterator, end_iterator };
	}

	/// @brief
	/// Creates an @ref IteratorPair from the provided `Container`.
	///
	/// @details
	/// Effectively calls `utils::begin(container)` and `utils::end(container)`.
	template<typename Container>
	constexpr auto makeIteratorPair(Container & container) ->
		IteratorPair<decltype(utils::begin(container)), decltype(utils::end(container))>
	{
		return { utils::begin(container), utils::end(container) };
	}
}