#pragma once

// For ptrdiff_t
#include <stddef.h>

#include "IteratorTags.h"

#include "details/IteratorTraitsUtils.h"

namespace utils
{
	template<typename Iterator>
	struct IteratorTraits :
		details::IteratorTraits<Iterator>
	{
	};

	template<typename Type>
	struct IteratorTraits<Type *>
	{
		using difference_type = ptrdiff_t;
		using value_type = Type;
		using pointer = value_type *;
		using reference = value_type &;
		using iterator_category = RandomAccessIteratorTag;
	};

	template<typename Type>
	struct IteratorTraits<const Type *> :
		IteratorTraits<Type *>
	{
	};

	template<typename Type>
	struct IteratorTraits<volatile Type *> :
		IteratorTraits<Type *>
	{
	};

	template<typename Type>
	struct IteratorTraits<const volatile Type *> :
		IteratorTraits<Type *>
	{
	};
}