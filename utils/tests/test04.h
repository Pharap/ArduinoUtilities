#include <Arduboy2.h>

#include "../progmem.h"

namespace test04
{
	const char test_data[] PROGMEM = "Hello world";

	const char * const test_ptr PROGMEM = test_data;

	void test(Arduboy2 & arduboy)
	{
		auto p = progmem::details::read_progmem(test_ptr);
		arduboy.println(reinterpret_cast<const __FlashStringHelper *>(p));
	}
}