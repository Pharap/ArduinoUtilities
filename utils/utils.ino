#include <Arduboy2.h>

Arduboy2 arduboy;

#include "progmem.h"
#include "eeprom.h"
#include "containers.h"

#include "tests/tests.h"

void setup()
{
	arduboy.begin();
	arduboy.clear();

	//test01::test(arduboy);
	//test02::test(arduboy);
	//test03::test(arduboy);
	//test04::test(arduboy);
	//test05::test(arduboy);
	//test06::test(arduboy);
	test07::test(arduboy);

	arduboy.display();

	while(true);
}

void loop()
{
	/*
	if (!(arduboy.nextFrame()))
		return;

	arduboy.clear();

	test01::test(arduboy);

	arduboy.display();
	*/
}
