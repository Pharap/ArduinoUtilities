#pragma once

namespace utils
{
	// Entities within the `details` namespace are
	// not considered part of the API and should not
	// be referenced from user code as anything within
	// the `details` namespace may be removed or renamed
	// without warning or deprecation.
	namespace details
	{
		template<typename Type>
		struct move_result
		{
			using type = Type &&;
		};

		template<typename Type>
		struct move_result<Type &>
		{
			using type = Type &&;
		};

		template<typename Type>
		struct move_result<Type &&>
		{
			using type = Type &&;
		};

		template<typename Type>
		using move_result_t = typename move_result<Type>::type;
	}

	/// @brief Move objects as per the rules of move semantics.
	/// @details Useful for moving objects that represent a resource,
	/// such as an object that uses dynamically allocated memory, or a file handle.
	/// @warning The result of attempting to move an object to itself (e.g. `v = move(v)`) is unspecified.
	template<typename Type>
	constexpr auto move(Type && object) noexcept
		-> details::move_result_t<Type>
	{
		return static_cast<details::move_result_t<Type>>(object);
	}
}