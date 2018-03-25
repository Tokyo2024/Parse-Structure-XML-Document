#pragma once

#include <string>
#include <set>
#include <exception>
#include <vector>
#include <iostream>
#include <map>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <boost/format.hpp>  
#include <boost/tokenizer.hpp>  
#include <boost/algorithm/string.hpp>  
#include <boost/lexical_cast.hpp>  
#include <boost/serialization/singleton.hpp> 

#include <glm/glm.hpp>

const std::vector<std::string> StrNodeName = { "HostID", "FrontFaceVideoIndex","BackFaceVideoIndex", "LeftFaceVideoIndex", "RightFaceVideoIndex", "TopFaceVideoIndex", "BottomFaceVideoIndex"};

class CParseXML : public boost::serialization::singleton<CParseXML>
{
public:
	CParseXML();
	~CParseXML();
	
	void setParseXMLName(const std::string &vFileName);
	glm::vec2 getWindowInfo();
	int       getFovX();
	void fetchVideoIndex(int vHostIndex, std::vector<std::vector<int>>& voVideoIndex);
	void fetchFrameChangeInfo(std::pair<int, bool>& voFrameChangeInfo);
	
private:
	void __parseXML();
	void __spliteString(const std::string& vString, std::vector<std::string>& voSegTag);
	int __changeToInterger(const std::string& vString);
	bool __changeToBool(const std::string& vString);

private:
	std::string m_FileName;
	boost::property_tree::ptree m_PTree;
};

