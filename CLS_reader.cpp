#include "CLS_reader.h"
#include "get_integer.h"
#include <iostream>
#include <cstdio>
#include <iomanip>

using std::cout;
using std::cin;

void reader::add_reader(unsigned int readerid)
{
	reader_id = readerid;
	cout << "\tfirstname: ";
	gets_s(firstname, 15);
	cout << "\tlastname: ";
	gets_s(lastname, 15);
	cout << "\taddress: ";
	gets_s(address, 35);
	age = get_integer_range(7, 125, "/tage ");
}

//-------------------------------------------------------------------------------

void reader::show_reader()
{
	cout << std::setw(4)	 << reader_id << " | "
		 << std::setw(12)	 << firstname << ' ' 
							 << lastname << ", " 
							 << age << " | " 
							 << address	<< '\n';	
}
