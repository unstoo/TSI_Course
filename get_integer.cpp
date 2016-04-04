#include <string>
#include <iostream>
using std::cin;
using std::cerr;
using std::cout;
using std::string;


//throws away line from cin buffer
void flush_cin_buffer()
{
	std::string _buffer;
	cin.clear();
	std::getline(cin, _buffer);
}

//prompts until proper integer followed by white space provided
//accepts only integers followed by whitespace
//refuses '1.23' or '56fvdf'
int get_integer() 
{
	for (int z;;)
	{
		if (cin >> z)
		{	
			if (isspace(cin.peek()))
			{
				//throws away any tracing characters			
				flush_cin_buffer();
				return z;
			}			
		}
		else if (!cin)
		{
			cerr << "\t not an integer. ";
			flush_cin_buffer();
			cerr << "try again: ";
		}
	}
}

//---------------------------------------------------------------------------


//promts for an integer within given range
int get_integer_range(int min, int max)
{
	//fixes range if needed
	if (min > max)
	{
		int temp = 0;
		temp = max;
		max = min;
		min = temp;
	}

	//returns value only if it's within set range
	while (true) 
	{
		int z = get_integer();

		if (min <= z && z <= max)
			return z;
		else
			cerr << z << " is out of range. Try again: ";
	}
}

//promts for an integer within given range with a specific msg
int get_integer_range(int min, int max, const char* str)
{
	if (min > max)
	{
		int temp = 0;
		temp = max;
		max = min;
		min = temp;
	}

	cout << str << " [" << min << ", " << max << "]: "; 

	//returns value only if it's within set range
	while (true) 
	{
		int z = get_integer();

		if (min <= z && z <= max)
			return z;
		else
			cerr << z << " is out of range.s Try again: ";
	}		
}

//---------------------------------------------------------------------------

void keep_window_open()
{
	cin.clear();
	cout << "\nEnter a character to continue. ";
	char ch;
	cin >> ch;
	flush_cin_buffer();
}

void keep_window_open(const char* msg)
{
	cin.clear();
	cout << msg << "Enter a character to continue. ";
	char ch;
	cin >> ch;
	flush_cin_buffer();
}
