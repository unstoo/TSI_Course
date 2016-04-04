#include "CLS_lib_tx.h"

void lib_tx::loan_tx(unsigned int book_id, unsigned int reader_id)
{
		_book_id = book_id;
		_reader_id = reader_id;
		_loan_date = 1; //= todays date();
		_return_date = 0;
		_status = Status::Pending;
}

//-------------------------------------------------------------------------------

bool lib_tx::complete_tx(unsigned int book_id)
{
	if (_book_id == book_id &&
		_status == Status::Pending)
	{
		_status = Status::Returned;
		_return_date = 28611132; //=todays date();
		return true;
	}
	else
		return false;
}

//-------------------------------------------------------------------------------
