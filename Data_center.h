#pragma once
#include "Array.h"
#include "CLS_book.h"
#include "CLS_reader.h"
#include "CLS_lib_tx.h"

class Data_center {

	//CPU deals with overall library stats and
	//messy multi-Array composition tasks

	unsigned int books = 0;
	unsigned int loanedbooks = 0;
	unsigned int * loanedb_ids = nullptr;

	unsigned int readers = 0;
	unsigned int activer = 0;
	unsigned int * activer_ids = nullptr;

public:
	
	void load_stats(const Array<book>& blist,
		const Array<reader>& rlist, const Array<lib_tx>& txlist);

	void display_stats() const;

	bool Return_book(unsigned int bookid, Array<lib_tx>& tx_list, Array<book>& b_list);

	void print_library_card(unsigned int readerid, const Array<book>& blist,
		const Array<reader>& rlist, const Array<lib_tx>& txlist);

	void print_book_history(unsigned int bookid, const Array<book>& blist,
		const Array<reader>& rlist, const Array<lib_tx>& txlist) const;
	
};
