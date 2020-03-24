#pragma once

#include "IteratorTraits.h"

namespace utils
{
	/// @brief
	///
	template<typename Iterator>
	class ReverseIterator
	{
	public:
		using iterator_type = Iterator;

		using difference_type = typename IteratorTraits<Iterator>::difference_type;

		using value_type = typename IteratorTraits<Iterator>::value_type;

		using pointer = typename IteratorTraits<Iterator>::pointer;

		using reference = typename IteratorTraits<Iterator>::reference;

		using iterator_category = typename IteratorTraits<Iterator>::iterator_category;

	private:
		iterator_type iterator;

	public:
		constexpr explicit ReverseIterator(iterator_type iterator) :
			iterator(iterator)
		{
		}

		constexpr iterator_type base() const
		{
			return this->iterator;
		}

		reference operator *() const
		{
			auto temporary = this->iterator;
			--temporary;
			return *temporary;
		}

		pointer operator ->() const
		{
			return &(this->operator*());
		}

		reference operator[](difference_type offset) const
		{
			return *(this->iterator - (offset - 1));
		}

		ReverseIterator & operator ++()
		{
			--this->iterator;
			return *this;
		}

		ReverseIterator operator ++(int)
		{
			auto result = *this;
			this->operator++();
			return result;
		}

		ReverseIterator & operator --()
		{
			++this->iterator;
			return *this;
		}

		ReverseIterator operator --(int)
		{
			auto result = *this;
			this->operator--();
			return result;
		}

		ReverseIterator operator +(difference_type offset) const
		{
			return ReverseIterator(this->iterator - offset);
		}

		ReverseIterator operator -(difference_type offset) const
		{
			return ReverseIterator(this->iterator - offset);
		}

		ReverseIterator & operator +=(difference_type offset)
		{
			this->iterator -= offset;
			return *this;
		}

		ReverseIterator & operator -=(difference_type offset)
		{
			this->iterator += offset;
			return *this;
		}
	};

	template<typename Iterator>
	constexpr ReverseIterator<Iterator> makeReverseIterator(Iterator iterator)
	{
		return ReverseIterator<Iterator>(iterator);
	}

	template<typename Iterator>
	constexpr bool operator ==(const ReverseIterator<Iterator> & left, const ReverseIterator<Iterator> & right)
	{
		return (left.base() == right.base());
	}

	template<typename Iterator>
	constexpr bool operator !=(const ReverseIterator<Iterator> & left, const ReverseIterator<Iterator> & right)
	{
		return (left.base() != right.base());
	}

	template<typename Iterator>
	constexpr bool operator <(const ReverseIterator<Iterator> & left, const ReverseIterator<Iterator> & right)
	{
		return (left.base() > right.base());
	}

	template<typename Iterator>
	constexpr bool operator >(const ReverseIterator<Iterator> & left, const ReverseIterator<Iterator> & right)
	{
		return (left.base() < right.base());
	}

	template<typename Iterator>
	constexpr bool operator <=(const ReverseIterator<Iterator> & left, const ReverseIterator<Iterator> & right)
	{
		return (left.base() >= right.base());
	}

	template<typename Iterator>
	constexpr bool operator >=(const ReverseIterator<Iterator> & left, const ReverseIterator<Iterator> & right)
	{
		return (left.base() <= right.base());
	}
}