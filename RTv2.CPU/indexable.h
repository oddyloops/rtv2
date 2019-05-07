#ifndef INDEXABLE_H
#define INDEXABLE_H

class indexable
{
protected:
	int _index;
public:
	void set_index(int index)
	{
		_index = index;
	}

	int get_index() const
	{
		return _index;
	}
};

#endif
