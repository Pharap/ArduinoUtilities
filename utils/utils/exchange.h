#pragma once

// For move
#include "move.h"

// For forward
#include "forward.h"

namespace utils
{
	/// @brief Replaces the value of `object` with `new_value` whilst returning the old value of `object`.
	/// @param object The object whose value is to be replaced.
	/// @param new_value The value to be assigned to `object`.
	template<typename ObjectType, typename NewValueType = ObjectType>
	ObjectType exchange(ObjectType & object, NewValueType && new_value)
	{
		auto old_value = move(object);
		object = forward<NewValueType>(new_value);
		return old_value;
	}
}