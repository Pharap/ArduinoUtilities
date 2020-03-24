#include <Arduboy2.h>

#include "../containers.h"
#include "../utils/Iterator/ReverseIterator.h"
#include "../utils/Iterator/IteratorPair.h"

namespace test07
{
	containers::Deque<char, 16> deque;

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

		auto r = utils::makeReverseIterator(deque.end());
		auto e = utils::makeReverseIterator(deque.begin());

		auto pair = utils::makeIteratorPair(r, e);

		for(char c : pair)
			arduboy.print(c);

		arduboy.println();
	}
}