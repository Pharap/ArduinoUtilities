#include <Arduboy2.h>

#include "../progmem.h"

namespace test03
{
	enum class State : uint8_t
	{
		A, B, C,
	};

	constexpr State state PROGMEM = State::B;

	void test(Arduboy2 & arduboy)
	{
		State a;// = progmem::readProgmem(state);
		progmem::copyProgmem(a, state);

		switch (a)
		{
		case State::A:
			arduboy.print('A');
			break;
			
		case State::B:
			arduboy.print('B');
			break;
			
		case State::C:
			arduboy.print('C');
			break;
		
		default:
			break;
		}
	}
}