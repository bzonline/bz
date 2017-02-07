//////////////////////////////////////////////////////////////////////
// File name : BasicFsmTest.cpp
// Purpose : To test implementation of FSM by BasicFsmT Class.
//          This includes BasicFsmT as public base class to implement a
//          sample Telephone state machine.
///////////////////////////////////////////////////////////////////////

#include <compiler.h>
#include <worker.h>

//#include <algorithm> // for std::find( ) etc.
//#include <iostream>
//#include <sstream>
//#include <stdexcept>


using namespace bz;



int main(int argc, char *argv[])
{
	size_t status = 0;
	size_t fsm_id = 0;
	
	Fsm*  pFsm = new Fsm(fsm_id, "read_compile_run");
	
	if (!pFsm)
		return -1;

	std::list<Node*> pnodes;
	Node* pnode = NULL;
	
	pnode = new Node(pFsm, nodePARSE_COMMAND_LINE, "parse_command_line");
	for (size_t i = 0; i < pnode->; i++)
	{
		pnode.
	}
	pnodes.push_back(pnode);
	pnode = new Node(pFsm, nodeREAD_FILE_CONTENT, "read_file_content");
	pnodes.push_back(pnode);
	pnode = new Node(pFsm, nodeCOMPILE_BZ_CODE, "compile_bz_code");
	pnodes.push_back(pnode);
//	pnode = new Node(pFsm, node_id++, "compile_bz_code");
//	pnodes.push_back(pnode);

	delete pFsm;
	return status;
}


/////// End File : fmsui.cpp  /////////////////////////////////////////