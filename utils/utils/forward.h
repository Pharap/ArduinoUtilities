#pragma once

// For move
#include "move.h"

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
		struct forward_parameter
		{
			using type = Type;
		};

		template<typename Type>
		struct forward_parameter<Type &>
		{
			using type = Type;
		};

		template<typename Type>
		struct forward_parameter<Type &&>
		{
			using type = Type;
		};

		template<typename Type>
		using forward_parameter_t = typename forward_parameter<Type>::type;
	}

	/// @brief Implements perfect forwarding.
	/// @details Forwards lvalues as either lvalues or rvalues.
	/// @param object The object to be forwarded.
	template<typename Type>
	constexpr Type && forward(details::forward_parameter_t<Type> & object)
	{
		return static_cast<Type &&>(object);
	}

	/// @brief Implements perfect forwarding.
	/// @details Forwards lvalues as either lvalues or rvalues.
	/// @param object The object to be forwarded.
	template<typename Type>
	constexpr Type && forward(details::forward_parameter_t<Type> && object)
	{
		return static_cast<Type &&>(object);
	}
}