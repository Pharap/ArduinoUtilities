#pragma once

namespace utils
{
	/// @brief
	/// Returns the size of the specified array.
	///
	/// @note
	/// @parblock
	/// Using `size(array)` has the benefit of allowing
	/// the array to later be substituted with a different container type.
	/// @endparblock
	///
	/// @note
	/// @parblock
	/// Does not attempt to read from the array.
	/// This means it can be used in unevaluated contexts.
	/// @endparblock
	template<typename Type, size_t size_value>
	constexpr size_t size(const Type (&)[size_value]) noexcept
	{
		return size_value;
	}

	/// @brief
	/// Returns the size of the specified container.
	///
	/// @note
	/// @parblock
	/// Using `size(container)` has the benefit of allowing
	/// the container to later be substituted with a different container type.
	/// @endparblock
	///
	/// @note
	/// @parblock
	/// Defers to `container.size()` to retrieve a result.
	/// @endparblock
	template<typename Container>
	constexpr auto size(const Container & container)
		-> decltype(container.size())
	{
		return container.size();
	}
}