#include "SC2Map.h"


SC2Map::SC2Map(string mapTitle,string imagePath, string description,string fullPath)
{
	this->title = mapTitle;
	this->description = description;
	this->imagePath = imagePath;
	this->fullPath = fullPath;
}


SC2Map::~SC2Map(void)
{

}

	
void SC2Map::setMapTitle(string mapTitle)
{
	this->title = mapTitle;
}

void SC2Map::setDescription(string description)
{
	this->description = description;
}

void SC2Map::setImagePath(string imagePath)
{
	this->imagePath = imagePath;
}

bool SC2Map::operator<(const SC2Map &obj)
{
	return this->title < obj.title; 
}

bool SC2Map::operator>(const SC2Map &obj)
{
	return this->title > obj.title;
}

string SC2Map::getImagePath() const
{
	return this->imagePath;
}

string SC2Map::getDescription() const
{
	return this->description;
}
