#pragma once

class reader {

	unsigned int	reader_id;
	char			firstname[15];
	char			lastname[15];
	char			address[35];
	unsigned int	age;
	
	friend class lib_tx;
	friend class Data_center;

public:

	void			add_reader(unsigned int readerid);
	void			show_reader();

	bool			match_by_id(unsigned int readerid) const { return reader_id == readerid; }

};