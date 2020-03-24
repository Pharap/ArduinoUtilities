#pragma once

namespace utils
{
	/// @brief
	/// Returns the past-the-end iterator of the specified array.
	///
	/// @note
	/// @parblock
	/// Using `end(array)` has the benefit of allowing
	/// the array to later be substituted with a different container type.
	/// @endparblock
	template<typename Type, size_t size_value>
	constexpr Type * end(Type (& array)[size_value]) noexcept
	{
		return &array[size_value];
	}

	/// @brief
	/// Returns the past-the-end iterator of the specified container.
	///
	/// @note
	/// @parblock
	/// Using `end(container)` has the benefit of allowing
	/// the container to later be substituted with a different container type.
	/// @endparblock
	///
	/// @note
	/// @parblock
	/// Defers to `container.end()` to retrieve a result.
	/// @endparblock
	template<typename Container>
	constexpr auto end(Container & container)
		-> decltype(container.end())
	{
		return container.end();
	}

	/// @brief
	/// Returns the past-the-end const iterator of the specified container.
	///
	/// @note
	/// @parblock
	/// Using `end(container)` has the benefit of allowing
	/// the container to later be substituted with a different container type.
	/// @endparblock
	///
	/// @note
	/// @parblock
	/// Defers to `container.end()` to retrieve a result.
	/// @endparblock
	template<typename Container>
	constexpr auto end(const Container & container)
		-> decltype(container.end())
	{
		return container.end();
	}

	/// @brief
	/// Returns the past-the-end const iterator of the specified container.
	///
	/// @note
	/// @parblock
	/// Using `cend(container)` has the benefit of allowing
	/// the container to later be substituted with a different container type.
	/// @endparblock
	///
	/// @note
	/// @parblock
	/// Uses `utils::end(container)` to retrieve a result.
	/// @endparblock
	template<typename Container>
	constexpr auto cend(const Container & container)
		-> decltype(utils::end(container))
	{
		return utils::end(container);
	}
}