#pragma once

namespace utils
{
	/// @brief
	/// Returns an iterator to the first element of the specified array.
	///
	/// @note
	/// @parblock
	/// Using `begin(array)` has the benefit of allowing
	/// the array to later be substituted with a different container type.
	/// @endparblock
	template<typename Type, size_t size_value>
	constexpr Type * begin(Type (& array)[size_value]) noexcept
	{
		return &array[0];
	}

	/// @brief
	/// Returns an iterator to the first element of the specified container.
	///
	/// @note
	/// @parblock
	/// Using `begin(container)` has the benefit of allowing
	/// the container to later be substituted with a different container type.
	/// @endparblock
	///
	/// @note
	/// @parblock
	/// Defers to `container.begin()` to retrieve a result.
	/// @endparblock
	template<typename Container>
	constexpr auto begin(Container & container)
		-> decltype(container.begin())
	{
		return container.begin();
	}

	/// @brief
	/// Returns a const iterator to the first element of the specified container.
	///
	/// @note
	/// @parblock
	/// Using `begin(container)` has the benefit of allowing
	/// the container to later be substituted with a different container type.
	/// @endparblock
	///
	/// @note
	/// @parblock
	/// Defers to `container.begin()` to retrieve a result.
	/// @endparblock
	template<typename Container>
	constexpr auto begin(const Container & container)
		-> decltype(container.begin())
	{
		return container.begin();
	}

	/// @brief
	/// Returns a const iterator to the first element of the specified container.
	///
	/// @note
	/// @parblock
	/// Using `cbegin(container)` has the benefit of allowing
	/// the container to later be substituted with a different container type.
	/// @endparblock
	///
	/// @note
	/// @parblock
	/// Uses `utils::begin(container)` to retrieve a result.
	/// @endparblock
	template<typename Container>
	constexpr auto cbegin(const Container & container)
		-> decltype(utils::begin(container))
	{
		return utils::begin(container);
	}
}