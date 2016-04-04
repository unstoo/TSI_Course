#pragma once
#include <fstream>
#include <string>
using namespace std;

//calculates file size in bytes
size_t binfile_size(char* file_name);

//calculates how many elements are stores in a binary file
size_t elems_in_binfile(char* file_name, size_t elem_size);