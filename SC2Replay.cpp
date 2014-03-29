#include "SC2Replay.h"

//Private

void SC2Replay::deepCopy(const SC2Replay &obj)
{
	this->contentSize = obj.contentSize;
	this->title =  obj.title;
	this->mapID = obj.mapID;
	this->nrOfplayers = obj.nrOfplayers;
	this->fullPath = obj.fullPath;
	this->names = obj.names;
	this->races = obj.races;
}


SC2Replay::SC2Replay(string replayTitle,Vector<string> replayContent,string fullPath)
{

	this->title = replayTitle;
	this->fullPath = fullPath;
	contentSize = replayContent.size();
	for(int i = 0; i < contentSize-1; i++)
	{
		if(i % 2 == 0)
		{
			names.addLast(replayContent.getAt(i));
		}
		else
		{
			races.addLast(replayContent.getAt(i));
		}
	}
	this->nrOfplayers = names.size();
	this->mapID = replayContent.getAt(contentSize -1);
}


SC2Replay::SC2Replay()
{
	this->title ="";
}

SC2Replay::SC2Replay(const SC2Replay &obj)
{
	deepCopy(obj);
}

SC2Replay::~SC2Replay(void)
{
}

void SC2Replay::operator=(const SC2Replay &obj)
{
	deepCopy(obj);
}

void SC2Replay::initiate(string replayTitle,Vector<string> replayContent,string fullPath)
{
	names.clear();
	races.clear();

	this->title = replayTitle;
	this->fullPath = fullPath;
	contentSize = replayContent.size();
	for(int i = 0; i < contentSize-1; i++)
	{
		if(i % 2 == 0)
		{
			names.addLast(replayContent.getAt(i));
		}
		else
		{
			races.addLast(replayContent.getAt(i));
		}
	}
	this->mapID = (replayContent.getAt(contentSize-1));
}

bool SC2Replay::operator<(const SC2Replay &obj)
{
	return this->title < obj.title;
}

bool SC2Replay::operator>(const SC2Replay &obj)
{
	return this->title > obj.title;
}

string SC2Replay::getMapTitle() const
{
	return this->mapID;
}

string SC2Replay::getName(int pos) const
{
	return this->names[pos];
}

string SC2Replay::getRace(int pos) const
{
	return this->races[pos];
}

int SC2Replay::getNrOfPlayers() const
{
	return this->nrOfplayers;
}

