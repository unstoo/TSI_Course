#include "Data_center.h"
#include <iostream>
#include <cstdio>
#include <iomanip>
using std::cout;
using std::cin;

void Data_center::load_stats(const Array<book>& blist, 
	const Array<reader>& rlist, const Array<lib_tx>& txlist)
{
	
	books = blist.elements(); //number of books
	
	readers = rlist.elements(); //numer of readers
	
	
	//number of loaned books, their IDs, IDs of active readers
	loanedbooks = 0;
	unsigned int * temp_arr = new unsigned int[blist.size()];
	unsigned int * temp_arr2 = new unsigned int[blist.size()];

		for (int i = 0; i < txlist.elements(); ++i)
		{			
			if (txlist[i].status() == lib_tx::Status::Pending)
			{
				++loanedbooks;
				temp_arr[i] = txlist[i]._book_id;
				temp_arr2[i] = txlist[i]._reader_id;
			}
		}

		loanedb_ids = temp_arr;
		activer_ids= temp_arr2;
	
}

//------------------------------------------------------------------------------

void Data_center::display_stats() const
{
	
	cout << "\n  Books in labriry: " << books
		 << ", loaned books: " << loanedbooks << '\n';
	cout << "  Readers in library: " << readers
		 << ", active readers " << activer << '\n';
}

//------------------------------------------------------------------------------

bool Data_center::Return_book(unsigned int bookid,
	Array<lib_tx>& tx_list, Array<book>& b_list)
{
	using id_t = unsigned int;

	//complete lib_tx
	for (id_t i = 0; i < tx_list.elements(); ++i)
		if (tx_list[i].complete_tx(bookid))
			//find book set == Available				 
			for (id_t i = 0; i < b_list.elements(); ++i)
			{
				if (b_list[i].match_by_id(bookid)) 
				{
					b_list[i]._status = book::Status::Availabe;
					return true;
				}
			}

	return false;
}


//------------------------------------------------------------------------------

void Data_center::print_library_card
(unsigned int readerid, 
	const Array<book>& blist, const Array<reader>& rlist, const Array<lib_tx>& txlist)
{
	//composes library card using 3 Arrays
	using id_t = unsigned int;
	id_t ct = 0;
	//find & print details of the reader
	for (id_t i = 0; i < rlist.elements(); ++i)
		if (rlist[i].match_by_id(readerid))
		{
			cout << "Library card of:";
			cout << setw(14) << rlist[i].firstname << " ";
			cout << rlist[i].lastname << ", ";
			cout << setw(3) << rlist[i].age << '\n';
			cout << rlist[i].address << '\n';
			std::cout << std::string(50, '-') << '\n';
			break;
		}


	//look for txs related to the reader	
	for (id_t i = 0; i < txlist.elements(); ++i)
		if (txlist[i].debtor_id() == readerid) //tx by book id found
		{  
			for (id_t j = 0; j < blist.elements(); ++j)
			{	
				if (blist[j].match_by_id(txlist[i].book_id())) //book by book id found
				{ 
					//compose details from book list & tx list
					++ct;
					if (txlist[i]._status == lib_tx::Status::Returned)
						cout << "Returned ";
					if (txlist[i]._status == lib_tx::Status::Pending)
						cout << "Debt ";
					cout << txlist[i]._loan_date << "-";
					cout << txlist[i]._return_date << " ";
					cout << blist[j].title << " by ";
					cout << blist[j].author << " ";								
					cout << '\n';
				}
			}
		}

	std::cout << std::string(50, '-') << '\n';
	cout << "Total of " << ct << " records in library card found.\n";
}

//------------------------------------------------------------------------------

