#pragma once
#include "CLS_book.h"
#include "CLS_reader.h"

class lib_tx {
public:

	enum class Status  {Pending = 1, Returned };	

private:
	
	unsigned int		_book_id;
	unsigned int		_reader_id;
	unsigned int		_loan_date;
	unsigned int		_return_date;
	Status			_status;

	friend class Data_center;

public:

	const			Status & status() const				{ return _status; }	
	unsigned int		debtor_id() const				{ return _reader_id; }
	unsigned int		book_id() const					{ return _book_id; }
	bool			match_bookid(unsigned int id)	{ return _book_id == id; }
	bool			match_debtorid(unsigned int id)	{ return _reader_id == id; }
	
	void			loan_tx(unsigned int book_id, unsigned int reader_id);
	bool			complete_tx(unsigned int book_id);

};