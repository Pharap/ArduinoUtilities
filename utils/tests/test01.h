#include <Arduboy2.h>

#include "../progmem.h"

namespace test01
{
	void test(Arduboy2 & arduboy)
	{
		auto string = PROGMEM_STRING("Hello world");

		for(auto c : string)
			arduboy.print(c);

		arduboy.println();

		arduboy.println(string);
		arduboy.println(F("Test 01"));
	}
}