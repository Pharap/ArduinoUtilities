#include <Arduboy2.h>

#include "../containers.h"

namespace test06
{
	containers::CircularDeque<char, 16> deque;

	void test(Arduboy2 & arduboy)
	{
		deque.push_back('w');
		deque.push_back('o');
		deque.push_back('r');
		deque.push_back('l');
		deque.push_back('d');
		
		deque.push_front(' ');
		deque.push_front('o');
		deque.push_front('l');
		deque.push_front('l');
		deque.push_front('e');
		deque.push_front('h');

		for(char c : deque)
			arduboy.print(c);

		arduboy.println();
	}
}