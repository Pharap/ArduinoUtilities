#include <Arduboy2.h>

#include "../eeprom.h"

namespace test05
{
	void test(Arduboy2 & arduboy)
	{
		char * destination = reinterpret_cast<char *>(900);

		char c = eeprom::readEeprom<char>(*destination);
		arduboy.print(c);
		eeprom::writeEeprom<char>(*destination, 'H');

		char c2 = eeprom::readEeprom<char>(*destination);
		arduboy.print(c2);
	}
}