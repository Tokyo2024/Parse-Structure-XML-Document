#pragma once

#include "ParseXML.h"

int main()
{
	CParseXML::get_mutable_instance().setParseXMLName("configure.xml");
	std::vector<std::vector<int>> IndexSet;
	CParseXML::get_mutable_instance().fetchVideoIndex(1, IndexSet);

	for (auto& e : IndexSet)
	{
		//std::cout << e.size() << std::endl;
		for (std::vector<int>::iterator Iterator = e.begin(); Iterator != e.end(); Iterator++)
		{
			std::cout << (*Iterator) << "   ";
		}
		std::cout << std::endl;
	}
	
	return 0;
}