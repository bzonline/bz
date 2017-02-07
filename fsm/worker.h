//////////////////////////////////////////////////////////////////////
// File name : worker.h
// Purpose : Реализует Node функциональность.
// Author : Boris Zverev (bz) aka Privet
///////////////////////////////////////////////////////////////////////

#include <fsm.h>
//#include <fstream>
//#include <sstream>
//#include <iostream>


using namespace bz;


template<typename T>
int Tnode(Connect& pconnect);
//	{
//		T* pbuff = NULL;
//
//		Tbuff = reinterpret_cast<T>(&pconnect.pdata);
//
//		return TWork(Tbuff);
//	}
	
	
template<> int Tnode<char*[]>(Connect& pconnect);
template<> int Tnode<char*>(Connect& pconnect);
template<> int Tnode<std::string>(Connect& pconnect);


enum NodeType: unsigned int
{
	nodeNONE,
	nodePARSE_COMMAND_LINE,
	nodeREAD_FILE_CONTENT,
    nodeCOMPILE_BZ_CODE,
    nodeUNDEFINED
};


struct NodeParams
{
	std::string      name;
	Job              pjob;
	unsigned int   numins;
	unsigned int  numouts;
};



Node* create_node(Fsm* pFsm, const NodeType id);


std::string get_file_contents(const char *filename);
//std::string get_file_contents2(const char *filename);

///////////////// End File  : worker.h  ///////////////////////////////