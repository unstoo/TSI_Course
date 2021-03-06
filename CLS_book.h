#pragma once

class book {
public:

	enum class Status { Availabe = 1, Loaned, Removed };
	enum class Genres { Fiction = 1, Biography, Science, Poetry };

private:

	unsigned int	 	book_id;
	char			author[20];
	char			title[35];
	unsigned int		year;
	Genres			genre;
	Status			_status;

	friend class	lib_tx;
	friend class	Data_center;
	
public:
	
	void			show_book() const;
	void			add_book(unsigned int bookid);
	
	const Status&		status();

	bool			set_loaned_status();	
	void			set_availabe_status();
	void			set_removed_status();
	
	bool			match_by_genre(Genres g);
	bool			match_by_id(unsigned int bookid) const;	
	
	bool			keyword_in_title(const char* keyword) const;
	friend bool		book_by_author(const char* author, const book& book);

};