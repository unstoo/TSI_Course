#pragma once
#include <fstream>
#include "read_binary.h"

template <typename T>
class Array
{
	size_t			_sz;				 //number of cells
	size_t			_elems_stored;	
	T *				_array;				 //ptr to an array	

	void			increase_storage(size_t n = 10);

public:
		
	size_t			size() const		{ return _sz; }
	size_t			elements() const	{ return _elems_stored; }
	size_t			byte_size() const	{ return sizeof(T) * _sz; }
	bool			isfull() const		{ return _elems_stored == _sz; }

	//----------------------------------------------------------//

	explicit	Array() : _sz(0), _elems_stored(0), _array(nullptr) {}
	explicit	Array(size_t n) : _sz(n), _elems_stored(0), _array(new T[n]) {}
				~Array() { _sz = 0; _elems_stored = 0;  delete[] _array; }

	//-----------------------------------------------------------------//
	
	Array(const Array& arr)				=delete;
	Array& operator=(const Array& arr)	=delete;
	Array(Array&& arr)					=delete;
	Array& operator=(Array&& arr)		=delete;

	//-----------------------------------------------------------------//

	T& operator[](size_t i);
	const T& operator[](size_t i) const; //read-only [] notation

	//-----------------------------------------------------------------//

	void insert(T& instance); //main function to add new elements to Array
	
	//-----------------------------------------------------------------//

	void sort_ascending(); //not implemented yet
	void sort_descending(); //not implemented yet

	//-----------------------------------------------------------------//	
	// for built-in types elements
	// or for objects without virtual methods

	bool array_to_binaryfile(char* file_name) const;
	bool binaryfile_to_array(char* file_name);

	//-----------------------------------------------------------------//
};

//=============================================================================


//allocates new memory, copies values into new place
//add +10 array cells by default
template<typename T>
inline void Array<T>::increase_storage(size_t n) 
{
	T* temp_array = new T[_sz + n];

	for (size_t i = 0; i < _elems_stored; ++i)
			temp_array[i] = _array[i];

	delete[] _array;
	_array = temp_array;
	_sz += n;
}

//=============================================================================
//inserts element, expands its capacity if full 

template<typename T>
inline void Array<T>::insert(T & instance)
{
	if (!(isfull())) //if all OK store element 
	{
		_array[_elems_stored] = instance; //*****switch this two IFs
		++_elems_stored;
	}
	else
	{
		increase_storage();
		_array[_elems_stored] = instance;
		++_elems_stored;
	}
}

//=============================================================================

template<typename T>
inline const T & Array<T>::operator[](size_t i) const
{
	if (i < 0 || size() <= i)
		throw std::out_of_range{ "Array::operator[]" };
	return _array[i];
}

template<typename T>
inline  T & Array<T>::operator[](size_t i) 
{
	if (i < 0 || size() <= i)
		throw std::out_of_range{ "Array::operator[]" };
	return _array[i];
}



//=============================================================================

template<typename T>
inline void Array<T>::sort_ascending()
{
	if (this->size() > 0)
		//sort
}


template<typename T>
inline void Array<T>::sort_descending()
{
	if (this->size() > 0)
		//sort
}

//=============================================================================
//writes data from array down to binary file
template<typename T>
inline bool Array<T>::array_to_binaryfile(char* file_name) const
{	
	std::ofstream fileOut 
		(file_name, ios_base::out | ios_base::trunc | ios_base::binary);

	if (fileOut.is_open())			//write all elements to file at once
		fileOut.write((char *)&_array[0], sizeof(T)*this->elements());

	else {
		string filename = file_name;
		string msg =
			"Array.array_to_binaryfile(): was not able to open file - " + filename;
		throw std::runtime_error(msg);
	}

	return true;
}



//=============================================================================
//reads from binary file
template<typename T>
inline bool Array<T>::binaryfile_to_array(char* file_name)
{	

	size_t file_size = elems_in_binfile(file_name, sizeof(T));

	//make sure current Array has enough space to store whole binary file
	if (file_size > this->size())
	{
		delete[] _array;
		_sz = file_size; 
		_array = new T[_sz];
	}

	std::ifstream fileIn
		(file_name, ios_base::in | ios_base::binary);
	if (!fileIn.is_open())				//throw if couldn't open file
	{
		string filename = file_name;
		string msg = 
			"Array.binaryfile_to_array(): was not able to open file - " + filename;
		throw std::runtime_error(msg);
	}
		
		//insert() one element at a time into Array from file
		for (T element;	fileIn.read((char *)&element, sizeof(T));)
			this->insert(element);		
	
		return true;	
}

//=============================================================================