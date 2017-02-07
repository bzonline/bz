//////////////////////////////////////////////////////////////////////
// File name : worker.cpp
// Purpose : Реализует worker класс
// Author : Boris Zverev (bz) aka Privet
///////////////////////////////////////////////////////////////////////

#include <worker.h>
//#include <fstream>
//#include <sstream>
//#include <iostream>
//# include <ifsm.h>


using namespace bz;


std::map<NodeType, NodeParams> NodeMap =
{
	{ nodeNONE, { "none", NULL, 0, 0 } },
	{ nodePARSE_COMMAND_LINE,   {"parse_command_line",  Tnode<char*[]>,      1, 1} },
	{ nodeREAD_FILE_CONTENT,    {"read_file_content",   Tnode<char*>,        1, 1} },
	{ nodeCOMPILE_BZ_CODE,      {"compile_bz_code",     Tnode<std::string>,  1, 1} },
	{ nodeUNDEFINED,            { "undefined", NULL, 0, 0 } }
};



Node* create_node(Fsm* pFsm, NodeType type)
{
	const NodeParams& npar = NodeMap[type];

	Node* pnode = new Node(pFsm, type, npar.name);
	
	return pnode;
}


std::string read_file_content(const char *filename)
{
  std::FILE *fp = std::fopen(filename, "rb");
  if (fp)
  {
    std::string contents;
    std::fseek(fp, 0, SEEK_END);
    contents.resize(std::ftell(fp));
    std::rewind(fp);
    std::fread(&contents[0], 1, contents.size(), fp);
    std::fclose(fp);
    return(contents);
  }
  throw(errno);
}

//std::string read_file_content2(const char *filename)
//{
//  std::ifstream in(filename, std::ios::in | std::ios::binary);
//  if (in)
//  {
//    std::ostringstream contents;
//    contents << in.rdbuf();
//    in.close();
//    return(contents.str());
//  }
//  throw(errno);
//}

template<> int Tnode<char*[]>(Connect& pconnect)
{
	return 0;
}

template<> int Tnode<char*>(Connect& pconnect)
{
	return 0;
}

template<> int Tnode<std::string>(Connect& pconnect)
{
	return 0;
}




///////////////// End File  : worker.h  ///////////////////////////////