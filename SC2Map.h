#ifndef _SC2MAP_
#define _SC2MAP_


#include "SC2Media.h"
using namespace std;

class SC2Map : public SC2Media
{
private:
	
	string description;
	string imagePath;
	//string size;  will maybe implement this
public:
	SC2Map(string mapTitle = "",string imagePath ="",string description = "",string fullPath = "");
	virtual~SC2Map(void);


	void setMapTitle(string mapTitle);
	void setDescription(string description);
	void setImagePath(string path);

	bool operator<(const SC2Map &obj);
	bool operator>(const SC2Map &obj);

	string getImagePath() const;
	string getDescription() const;
};

#endif