#include "read_binary.h"

//seekg() -			 move to a specific position in file
//pos = in.tellg() - pos is the position of in’s get pointer

//app -		 Append(i.e., add to the end of the file)
//ate -		 ‘‘At end’’(open and seek to the end)
//binary -	 Binary mode; beware of system - specific behavior
//in -		 For reading
//out -		 For writing
//trunc -	 Truncate the file to 0 length

size_t binfile_size(char* file_name)
{
	fstream file(file_name, ios::in | ios::app | ios::binary);
	if (file.is_open())
	{
		streampos fsize = file.tellg();
		file.seekg(0, ios::end);
		return size_t(file.tellg() - fsize);
	}
	else
		throw runtime_error
		("binfile_size(): was unable to open file:");
}

//-------------------------------------------------------------------------

size_t elems_in_binfile(char* file_name, size_t elem_size)
{
	size_t fsize = binfile_size(file_name);

	if (fsize % elem_size == 0)
		return (fsize / elem_size);
	else
		throw runtime_error
		("elemens_in_binflie(): containts invalid type elements");
}

