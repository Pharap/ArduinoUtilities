#pragma once

// For size_t, ptrdiff_t
#include <stddef.h>

#include "tags.h"
#include "traits.h"

namespace utils
{
	namespace details
	{
		template<typename InputIterator>
		auto distance(InputIterator fromIterator, InputIterator toIterator, input_iterator_tag)
			-> details::iterator_difference_type<InputIterator>
		{
			using diference_type = details::iterator_difference_type<InputIterator>;

			diference_type difference = 0;

			while(toIterator != fromIterator)
			{
				++toIterator;
				++difference;
			}

			return difference;
		}

		template<typename InputIterator>
		auto distance(InputIterator fromIterator, InputIterator toIterator, random_access_iterator_tag)
			-> details::iterator_difference_type<InputIterator>
		{
			return (toIterator - fromIterator);
		}
	}

	template<typename InputIterator>
	auto distance(InputIterator fromIterator, InputIterator toIterator)
		-> details::iterator_difference_type<InputIterator>
	{
		return details::distance(fromIterator, toIterator, details::iterator_category<InputIterator>{});
	}
}