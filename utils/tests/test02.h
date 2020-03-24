#include <Arduboy2.h>

#include "../progmem.h"

namespace test02
{
	const char test_data[] PROGMEM = "Hello world";

	void test(Arduboy2 & arduboy)
	{
		auto array = progmem::makeProgmemArray(test_data);
		
		for(size_t index = 0; index < array.size(); ++index)
			arduboy.print(array[index]);
		arduboy.println();
		
		for(auto c : array)
			arduboy.print(c);
		arduboy.println();
		
		arduboy.println(F("Hello world"));
	}
}