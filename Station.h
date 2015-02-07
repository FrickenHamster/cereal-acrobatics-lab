/*
 * Station.h
 *
 *  Created on: Jan 25, 2015
 *      Author: Hamster
 */

#ifndef STATION_H_
#define STATION_H_

class Station
{
public:
	Station(int, int);
	virtual ~Station();
	

	bool isMarked() const
	{
		return marked;
	}

	void setMarked(bool marked)
	{
		Station::marked = marked;
	}

private:
	bool marked;
};

#endif /* STATION_H_ */
