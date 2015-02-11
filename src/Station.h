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
	

	int getX()
	{
		return x;
	}

	int getY()
	{
		return y;
	}
private:
	int x;
	int y;
};

#endif /* STATION_H_ */
