#pragma once

namespace utils
{
	namespace details
	{
		template<typename Type>
		auto try_get_difference_type(int) -> typename Type::difference_type;

		template<typename Type>
		auto try_get_difference_type(...) -> void;

		template<typename Type>
		auto try_get_value_type(int) -> typename Type::value_type;

		template<typename Type>
		auto try_get_value_type(int) -> void;

		template<typename Type>
		auto try_get_pointer(int) -> typename Type::pointer;

		template<typename Type>
		auto try_get_pointer(int) -> void;

		template<typename Type>
		auto try_get_reference(int) -> typename Type::reference;

		template<typename Type>
		auto try_get_reference(int) -> void;

		template<typename Type>
		auto try_get_iterator_category(int) -> typename Type::iterator_category;

		template<typename Type>
		auto try_get_iterator_category(int) -> void;

		template<typename Type>
		struct IsVoid
		{
			static constexpr bool value = false;
		};

		template<>
		struct IsVoid<void>
		{
			static constexpr bool value = true;
		};

		template<typename Iterator>
		struct IsCompleteIterator
		{
			static constexpr bool value =
				!IsVoid<decltype(try_get_difference_type<Iterator>(0))>::value &&
				!IsVoid<decltype(try_get_value_type<Iterator>(0))>::value &&
				!IsVoid<decltype(try_get_pointer<Iterator>(0))>::value &&
				!IsVoid<decltype(try_get_reference<Iterator>(0))>::value &&
				!IsVoid<decltype(try_get_iterator_category<Iterator>(0))>::value;
		};

		template<typename Iterator, bool isComplete = IsCompleteIterator<Iterator>::value>
		struct IteratorTraits;

		template<typename Iterator>
		struct IteratorTraits<Iterator, false> {};

		template<typename Iterator>
		struct IteratorTraits<Iterator, true>
		{
			using difference_type = typename Iterator::difference_type;
			using value_type = typename Iterator::value_type;
			using pointer = typename Iterator::pointer;
			using reference = typename Iterator::reference;
			using iterator_category = typename Iterator::iterator_category;
		};
	}
}