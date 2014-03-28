#include "ReplayDetailsReader.h"
#include <iostream>

ReplayDetailsReader::ReplayDetailsReader(void)
{
	for(int i = 0; i < CHECK_SIZE; i++)
	{
		checkN_R[i] = ' ';
	}
	this->headerInfo = new char[HEADER_SIZE];
}


ReplayDetailsReader::~ReplayDetailsReader(void)
{
	delete[] headerInfo;
}

char ReplayDetailsReader::readString(ifstream &details, char check[])
{
	char* c = new char;
	for(int j = CHECK_SIZE-1; j > 0; j--)
	{
		check[j] = check[j-1];
	}
	details.read(c,1);
	check[0] = *c;
	delete c;
	return check[0];

}


bool ReplayDetailsReader::checkScrap(char check[])
{
	bool noMatch = true;

	char protossID[CHECK_SIZE];
	protossID[0] = 0x0E;
	protossID[1] = 0x02;
	protossID[2] = 0x04;
	char zergID[CHECK_SIZE];
	zergID[0] = 0x08;
	zergID[1] = 0x02;
	zergID[2] = 0x04;
	char terranID[CHECK_SIZE];
	terranID[0] = 0x0C;
	terranID[1] = 0x02;
	terranID[2] = 0x04;
	char beginOfNextName[CHECK_SIZE];
	char beginOfMap[CHECK_SIZE];
	beginOfMap[0] = 0x40; // random value
	beginOfMap[1] = 0x02;
	beginOfMap[2] = 0x02;
	beginOfNextName[0] = 0x40; // random value
	beginOfNextName[1] = 0x02;
	beginOfNextName[2] = 0x00;

	if(checkIndividual(check,protossID))
	{
		noMatch = false;
	}
	else if(checkIndividual(check,zergID))
	{
		noMatch = false;
	}
	else if(checkIndividual(check,terranID))
	{
		noMatch = false;
	}
	else if(checkIndividual(check,beginOfNextName,2))
	{
		noMatch = false;
	}
	else if(checkIndividual(check,beginOfMap,2))
	{
		noMatch =  false;
	}
	
	return noMatch;
}

bool ReplayDetailsReader::checkIndividual(char check[], char id[],int checkSize)
{
	bool foundMatch = false;
	int nrOfEqual  = 0;

	for(int i = 0; i < CHECK_SIZE; i++)
	{
		//cout<<static_cast<int>(check[i]) <<" "<<static_cast<int>(id[i])<<endl;
		cout<<check[i] << id[i]<<endl;
		if(check[i] == id[i])
		{
			nrOfEqual++;
		}
	}
	
	if(nrOfEqual == checkSize)
	{
		foundMatch = true;
	}
	return foundMatch;
}

string ReplayDetailsReader::readName(ifstream &details)
{
	char *name = new char[NAME_SIZE+3];
	char check[] = {' ',' ',' '};
	int length = 0;
	string stringName = "";
	while (check[0] != 0x08 && check[1] != 0x05 && check[2] != 0x02) // end sequence
	{		
		name[length++] = readString(details,check);
		//readString(nameFirst,nameLength,read,checkN_R);		
	}
			
	for(int i = 0; i < CHECK_SIZE; i++)
	{
		name[--length] = NULL;
	}
	
	stringName = name;
	try
	{
		stringName.replace(stringName.find("<sp/>"),5," ");
	}
	catch(exception e)
	{

	}

	
	delete[] name;
	return stringName;
}


void ReplayDetailsReader::disposeScrap(ifstream &details)
{
	char checkN_R[] = {0x00,0x00,0x00};

	while(checkScrap(checkN_R))
	{
		readString(details,checkN_R); 
	}
}

string ReplayDetailsReader::readRace(ifstream &details)
{
	char *race = new char[RACE_SIZE+3];
	char check[] = {' ',' ',' '};

	int length = 0;

	string stringRace;

	while(check[0] != 0x08 && check[1] != 0x05 && check[2] != 0x06) // end sequence
	{
		race[length++] = readString(details,check);		
	}

	for(int i = 0; i < CHECK_SIZE; i++)
	{
		race[--length] = NULL;
	}
			
	stringRace = race;
	delete[] race;
	return stringRace;
}

string ReplayDetailsReader::readMap(ifstream &details,char replayType)
{
	char *map = new char[MAP_SIZE];
	char check[] = {'?','?','?'};

	int length = 0;

	string stringMap;

	while(check[0] != 0x00 && check[1] != 0x02 && check[2] != 0x04) // end sequence
	{
		map[length++] = readString(details,check);
	}

	for(int i = 0; i < CHECK_SIZE; i++) // removes check bytes
	{
		map[--length] = NULL;
	}

	if(replayType == 0x04)
	{
		for(int i = 0; i < length; i++) // reposition
		{
			map[i] = map[i+1];
		}
	}

	stringMap = map;
	delete map;
	return stringMap;

}


Vector<string> ReplayDetailsReader::returnElements()
{
		ifstream read("dump.txt",ios::binary); // have to be opened as binary
		Vector<string> theArray;
		int nrOfElements = 0;
		/*	start of "get first name"						*/

		if(read.is_open())
		{
			read.read(headerInfo,HEADER_SIZE); // in here we find checkers for non-corrupt file and such, wont need it, (replay type!!! (1v1,2v2))
			
			if(headerInfo[6] == 0x04)
			{
				nrOfElements = ONE_VERSUS_ONE;
			}
			else if(headerInfo[6] == 0x08)
			{
				nrOfElements = TWO_VERSUS_TWO;
			}
			else if(headerInfo[6] == 0x0C)
			{
				nrOfElements = THREE_VERSUS_THREE;
			}
			
			for(int i = 0; i < nrOfElements-1; i++) 
			{
				if(i % 2 == 0)
				{
					theArray.addLast(readName(read));
				}
				else
				{
					theArray.addLast(readRace(read));
				}
				disposeScrap(read);
			}
		

			theArray.addLast(readMap(read,headerInfo[6])); // byte position 6 holds replay type
		}
		else throw "Error reading file";
		
		read.close();
		remove("dump.txt");
		return theArray;
}
