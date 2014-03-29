#ifndef _SC2REPLAY_
#define _SC2REPLAY_

#include"SC2Map.h"
#include "SC2Media.h"
#include <Vector.h>




class SC2Replay : public SC2Media
{
private:
	int contentSize;
	
	string mapID;
	//SC2Map *map; make connection to map in the handler
	
	int nrOfplayers;
	Vector<string> names;
	Vector<string> races;

	void deepCopy(const SC2Replay &obj);
public:
	
	SC2Replay(string replayTitle,Vector<string> replayContent,string fullPath);
	SC2Replay(const SC2Replay &obj);
	SC2Replay();
	virtual ~SC2Replay(void);

	
	void operator=(const SC2Replay &obj);
	void initiate(string replayTitle,Vector<string> replayContent,string fullPath);

	bool operator<(const SC2Replay &obj);
	bool operator>(const SC2Replay &obj);

	int getNrOfPlayers() const;

	string getName(int pos) const;
	string getRace(int pos) const;
	string getMapTitle() const;
	
};

#endif