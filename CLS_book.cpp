#include "CLS_book.h"
#include "get_integer.h"
#include <iostream>
#include <cstdio>
#include <iomanip>
using std::cout;
using std::cin;


void book::show_book() const
{
	if (Status::Availabe == _status) cout <<  std::setw(5) << "Av" << " | ";
	if (Status::Loaned == _status) cout << " Unav"  << " | ";

	cout << std::setw(3)  << book_id << " | "
		 << std::setw(15) << author << " | " 
		 << std::setw(25) << title << " | "
		 << std::setw(4)  << year;

	if (Genres::Biography	== genre)	cout << " | Biography";
	if (Genres::Fiction		== genre)	cout << " | Fiction";
	if (Genres::Science		== genre)	cout << " | Science";
	if (Genres::Poetry		== genre)	cout << " | Poetry";

}

//-------------------------------------------------------------------------------

void book::add_book(unsigned int id)
{	
	book_id = id;
	cout << "\tauthor: "; 
	gets_s(author, 25);
	cout << "\ttitle: "; 
	gets_s(title, 35);
	year = 	get_integer_range(1700,2016, "\tprint year ");

	cout << "\tselect genre - Fiction=1, Biography=2, Science=3, Poetry=4: ";
	genre = Genres(get_integer_range(1, 4));

	_status = Status::Availabe;	
}

//-------------------------------------------------------------------------------

const book::Status& book::status()
{
	 return _status; 
}

//-------------------------------------------------------------------------------

bool book::set_loaned_status()
{
	if (_status == Status::Availabe)
	{
		_status = Status::Loaned;
		return true;
	}
	return false;
}

//-------------------------------------------------------------------------------


void book::set_availabe_status()
{
	 _status = Status::Availabe; 
}

//-------------------------------------------------------------------------------

void book::set_removed_status()
{
	_status = Status::Removed;
}

//-------------------------------------------------------------------------------

bool book::match_by_id(unsigned int bookid) const
{
 return book_id == bookid; 
}

//-------------------------------------------------------------------------------

bool book::match_by_genre(Genres g)
{
	return genre == g;
}

//-------------------------------------------------------------------------------

bool book::keyword_in_title(const char * keyword) const
{	
	if (strlen(keyword) > strlen(title))
		return 0;
	
		//start comparsion
	for (unsigned int i = 0; title[i] != '\0' ;	++i)
											
		if (tolower(title[i]) == tolower(keyword[0]))	//look for 1st letters match
			for (unsigned int j = 0; ; ++j)				//compare rest of keyword
			{ 
				if (tolower(title[i + j]) != tolower(keyword[j]))
					break;

				if (keyword[j + 1] == '\0')				//full match
					return true;
			}
	
	return 0;
}

//-------------------------------------------------------------------------------

bool book_by_author(const char* author, const book& book) 
{
	if (strlen(author) > strlen(book.author))
		return 0;

	for (unsigned int i = 0; book.author[i] != '\0'; ++i)

		if (tolower(book.author[i]) == tolower(author[0]))	//look for 1st letters match
			for (unsigned int j = 0; ; ++j)				//compare rest of keyword
			{
				if (tolower(book.author[i + j]) != tolower(author[j]))
					break;

				if (author[j + 1] == '\0')				//full match
					return true;
			}


	return 0;
}