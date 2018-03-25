#include "ParseXML.h"

CParseXML::CParseXML()
{
}

CParseXML::~CParseXML()
{

}

//******************************************************
//Function:
glm::vec2 CParseXML::getWindowInfo()
{
	std::string WindowInfo = m_PTree.get<std::string>("ConfigureInformation.WindInfo");
	std::vector<std::string> WindowInfoSet;
	__spliteString(WindowInfo, WindowInfoSet);
	return glm::vec2(__changeToInterger(WindowInfoSet[0]), __changeToInterger(WindowInfoSet[1]));
}

//******************************************************
//Function:
void CParseXML::fetchFrameChangeInfo(std::pair<int, bool>& voFrameChangeInfo)
{
	std::string FrameNum = m_PTree.get<std::string>("ConfigureInformation.ChangeFrame.FrameNum");
	std::string IsChange = m_PTree.get<std::string>("ConfigureInformation.ChangeFrame.Change");
	voFrameChangeInfo = std::make_pair(__changeToInterger(FrameNum), __changeToBool(IsChange));
}

//******************************************************
//Function:
int CParseXML::getFovX()
{
	std::string FovX = m_PTree.get<std::string>("ConfigureInformation.FOVX");
	return __changeToInterger(FovX);
}

//******************************************************
//Function:
void CParseXML::__parseXML()
{
	_ASSERT(m_FileName.size() != 0);
	read_xml(m_FileName, m_PTree);
}

//******************************************************
//Function:
void CParseXML::__spliteString(const std::string& vString, std::vector<std::string>& voSegTag)
{
	std::string String = vString;
	boost::char_separator<char> sep(" ,£¬");
	typedef boost::tokenizer<boost::char_separator<char> > CustonTokenizer;
	CustonTokenizer Token(String, sep);
	for (CustonTokenizer::iterator Beg = Token.begin(); Beg != Token.end(); ++Beg)
	{
		voSegTag.push_back(*Beg);
	}
}

//******************************************************
//Function:
int CParseXML::__changeToInterger(const std::string& vString)
{
	return boost::lexical_cast<int>(vString);
}

//******************************************************
//Function:
bool CParseXML::__changeToBool(const std::string& vString)
{
	if (vString == "TRUE")
	{
		return true;
	}
	else
	{
		return false;
	}
}

//******************************************************
//Function:
void CParseXML::setParseXMLName(const std::string &vFileName)
{
	m_FileName = vFileName;
	__parseXML();
}


//******************************************************
//Function:
void CParseXML::fetchVideoIndex(int vHostIndex, std::vector<std::vector<int>>& voVideoIndex)
{
	voVideoIndex.resize(StrNodeName.size() - 1);

	boost::property_tree::ptree Root;
	try
	{
		Root = m_PTree.get_child("ConfigureInformation.LoadVideoIndex");
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		_ASSERT(false);
	}

	for (auto Iterator = Root.begin(); Iterator != Root.end(); Iterator++)
	{
		boost::property_tree::ptree Strage = Iterator->second;
		std::string Index;
		std::string Value;

		boost::property_tree::ptree TemplePTree;
		std::string StrValue;
		try
		{
			TemplePTree = Strage.get_child(StrNodeName[0]);
			StrValue = TemplePTree.data();
		}
		catch (std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
		
		std::vector<std::string> StringSecSet;
		__spliteString(StrValue, StringSecSet);
		int PCID = __changeToInterger(StringSecSet[0]);
		//std::cout << StrIntergerValue << std::endl;
		int A = 0;
		if (vHostIndex == PCID)
		{
			for (unsigned i = 1; i < StrNodeName.size(); i++)
			{

				try
				{
					TemplePTree = Strage.get_child(StrNodeName[i]);
					StrValue = TemplePTree.data();
				}

				catch (std::exception& e)
				{
					std::cout << e.what() << std::endl;
				}

				std::vector<std::string> TempleSectionSet;
				__spliteString(StrValue, TempleSectionSet);
				for (unsigned int k = 0; k < TempleSectionSet.size(); k++)
				{
					voVideoIndex[i - 1].push_back(__changeToInterger(TempleSectionSet[k]));
				}
			}

			break;
		}
	}
}

