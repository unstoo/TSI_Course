#include "Array.h"
#include "CLS_book.h"
#include "CLS_reader.h"
#include "CLS_lib_tx.h"
#include "get_integer.h"
#include "Data_center.h"

#include <iostream>
#include <iomanip>

using std::cout;
using std::cin;
using id_t = unsigned int;
void print_menu();

int main() {

	Array<book> b_list;
	Array<reader> r_list;
	Array<lib_tx> tx_list;

	try {
		b_list.binaryfile_to_array("books.bin");
		r_list.binaryfile_to_array("readers.bin");
		tx_list.binaryfile_to_array("libtxs.bin");
	}
	catch (runtime_error& e) 	{ 
		cerr << "runtime_err(): " << e.what(); 
		return 1;
	}

	book tbook;
	reader	treader;
	lib_tx	ttx;

	Data_center session;	

	char ch;

	while (true){
	system("CLS");
	print_menu();
	cin >> ch;
	flush_cin_buffer();

	switch (ch) {

	case '1': {  //[1] - New book (...)

		system("CLS");
		cout << "[1] - Adding new book ";
		id_t unique_book_id = b_list.elements() + 1;
		tbook.add_book(unique_book_id);
		b_list.insert(tbook);
		keep_window_open("\tBook added.");
		break;
	}

//---------------------------------------------------------------------------------

	case '2': { //[2] - Remove book(id)	

		system("CLS");
		cout << "[2] - To remove book, enter its ID: ";
		id_t bookid = get_integer_range(1, b_list.elements());

		for (id_t i = 0; i < b_list.elements(); ++i)
			if (b_list[i].match_by_id(bookid))
			{
				b_list[i].set_removed_status();
				break;
			}
		keep_window_open("\tBook removed.");
		break;
	}

//---------------------------------------------------------------------------------

	case '3': { //[3] - New reader (...)

		system("CLS");
		cout << "[3] - Adding new reader:\n";
		id_t unique_reder_id = r_list.elements() + 1;
		treader.add_reader(unique_reder_id);
		r_list.insert(treader);
		keep_window_open("\tReader added.");
		break;
	}

//----------------------------------------------------------------------------------

	case '4': { //[4] - Library card (reader id)

		system("CLS");
		cout << "[4] - To print library card enter reader's ID: ";
		id_t readerid = get_integer_range(1, r_list.elements());
		session.print_library_card(readerid, b_list, r_list, tx_list);
		keep_window_open();
		break;
	}

//---------------------------------------------------------------------------------

	case '5': { //[5] - Loan book (book id, reader id)

		system("CLS");
		if (r_list.elements() == 0)	
		{
			keep_window_open("There's no one to loan to. Add a reader first.\n");
			break;
		}
		
		cout << "[5] - To loan book, enter its ID: ";		

		//deal with the book first
		bool loanable = false;
		id_t bookid = get_integer_range(1, b_list.elements());

		//find & update the book
		for (id_t i = 0; i < b_list.elements(); ++i)
			if (b_list[i].match_by_id(bookid))
			{
				loanable = b_list[i].set_loaned_status();
				break;
			}

		//move on with tx if book lets us
		if (loanable)
		{
			id_t readerid = get_integer_range(1, r_list.elements(), "\tReader's ID: ");

			ttx.loan_tx(bookid, readerid);		//make correpsonding lib_tx record
			tx_list.insert(ttx);
			keep_window_open("Successfully loaned book. ");
			break;
		}

		else  //cancel request if book != Available
		{
			keep_window_open("Can't loan. Book is unavailable.\n");
			break;
		}
	}

//---------------------------------------------------------------------------------

	case '6': {	//[6] - Return book (book id)
		system("CLS");

		cout << "[6] - To return book, enter its ID ";

		id_t bookid = get_integer_range(1, b_list.elements(), "");

		if (session.Return_book(bookid, tx_list, b_list))
			keep_window_open("Book returned. ");
		else
			keep_window_open("The books is already returned. ");

		break;
	}

//---------------------------------------------------------------------------------

	case '7': {	//[7] - Loaned books list ()
		system("CLS");

		cout << std::setw(8) << "| "
			<< std::setw(6) << "ID | "
			<< std::setw(15) << "Author" << " | "
			<< std::setw(25) << "Title" << " | "
			<< std::setw(4) << "Year"
			<< " | Genre\n";

		int ct = 0;
		for (id_t i = 0; i < b_list.elements(); ++i)
			if (b_list[i].status() == book::Status::Loaned)
			{
				++ct;
				b_list[i].show_book();
				cout << '\n';
			}

		cout << "\nTotal of " << ct << " loaned books found.\n";
		keep_window_open();
		break;
	}

 //---------------------------------------------------------------------------------

	case '8': { //[8] - All books list ()
		system("CLS");

		int ct = 0;
		cout << std::setw(8) << "| "
			<< std::setw(6) << "ID | "
			<< std::setw(15) << "Author" << " | "
			<< std::setw(25) << "Title" << " | "
			<< std::setw(4) << "Year"
			<< " | Genre\n";

		for (id_t i = 0; i < b_list.elements(); ++i)
			if (b_list[i].status() != book::Status::Removed)
			{
				++ct;
				b_list[i].show_book();
				cout << '\n';
			}

		cout << "\nTotal of " << ct << " books found.\n";
		keep_window_open();
		break;
	}

//---------------------------------------------------------------------------------	

	case '9': {	//[9] - Readers list
		system("CLS");

		cout << "[9] - Readers list:\n";
		for (id_t i = 0; i < r_list.elements(); ++i)
		{
			r_list[i].show_reader();
			cout << '\n';
		}
		keep_window_open();
		break;
	}

//---------------------------------------------------------------------------------		
			  
	case 'A':case 'a': { //[A] - Books by author (lastname)
		system("CLS");

		cout << "[A] - Books by author, enter a name: ";
		char author[35];
		gets_s(author);

		size_t ct = 0;
		for (id_t i = 0; i < b_list.elements(); ++i)
			if (book_by_author(author, b_list[i]))
			{
				++ct;
				b_list[i].show_book();
				cout << '\n';
			}

		cout << "Total of " << ct << " author matches found.\n";
		keep_window_open();
		break;
	}
//---------------------------------------------------------------------------------

	case 'K':case 'k': { //[K] - Books by keyword (keyword)
		system("CLS");

		cout << "[K] - Books by keyword, enter one:	";
		char kword[35];
		gets_s(kword);
		
		size_t ct = 0;
		for (id_t i = 0; i < b_list.elements(); ++i)
			if (b_list[i].keyword_in_title(kword)) 
			{	
				++ct;
				b_list[i].show_book();
				cout << '\n';
			}
		cout << "Total of " << ct << " keyword matches found.\n";
		keep_window_open();
		break;
	}

//---------------------------------------------------------------------------------

	case 'G': case 'g': {  //[G] - Books by genre
		system("CLS");

		cout << "[G] - Books by genre, pick one\n"
				"Fiction=1, Biography=2, Science=3, Poetry=4: ";
		auto selection = book::Genres(get_integer_range(1, 4));

		for (id_t i = 0; i < b_list.elements(); ++i)
			if (b_list[i].match_by_genre(selection))
			{
				b_list[i].show_book();
				cout << '\n';
			}
		keep_window_open();
		break;
	}
//---------------------------------------------------------------------------------

	case 'H':case 'h': { //[S] - Book's history (title)
		break; //NOTIMPLEMENTED
	}

//---------------------------------------------------------------------------------

	case 'S':case 's': { //[S] - Generatl statistics
		system("CLS");

		session.load_stats(b_list, r_list, tx_list);
		session.display_stats();
		keep_window_open();
		break;
	}

//---------------------------------------------------------------------------------
	case 'Q':case 'q': {
		b_list.array_to_binaryfile("books.bin");
		r_list.array_to_binaryfile("readers.bin");
		tx_list.array_to_binaryfile("libtxs.bin");
		return 0;
	}

	} //case(ch)
  } //while(true)
}//main()
//--------------------------------------------------------------------------------

void print_menu() {

	cout << "----------------Administration--------------------\n\n";
	cout << "[1] - Add book    (...) \n";
	cout << "[2] - Remove book (ID)  \n";
	cout << "[3] - New reader  (...) \n";
	cout << "[4] - Library card(reader id) \n";
	cout << "\n----------------Books control-----------------------\n\n";
	cout << "[5] - Loan book (book id, reader id) \n";
	cout << "[6] - Return book(book id) \n";
	cout << "[7] - Loaned books list \n";
	cout << "[8] - Books list \n";
	cout << "[9] - Readers list \n";
	cout << "\n----------------Search & info----------------------\n\n";
	cout << "[A] - Books by author (lastname)	\n";
	cout << "[K] - Books by keyword in title (keyword)	\n";
	cout << "[G] - Books by genre \n";
	cout << "[H] - Book's history (id) \n";
	cout << "[S] - Overall stats \n";
	cout << "\n----------------[Q]uit & Save-----------------------\n";
}