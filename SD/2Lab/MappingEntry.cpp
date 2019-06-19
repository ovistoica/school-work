#include <fstream>
#include <iostream>

#include "MappingEntry.h"

int main() {

#ifdef DEBUG
	std::ostream& out = std::cout;
#else
	std::ofstream file;
	file.open("Out/Lab2/task3.out");
	std::ostream& out = file;
#endif

	char value[] = "MappingEntryValue";

	/* TODO: Create a MappingEntry object (key should be 1 and value - given
		value from above) using new operator */
	
	/* TODO: Print entry's value in output */

	/* TODO: Delete the entry */

#ifndef DEBUG
	file.close();
#endif

	return 0;
}