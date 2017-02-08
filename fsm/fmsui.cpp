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
	std::string src = "";
	Fsm*  pFsm = new Fsm();
	Compile* pComp = new Compile(pFsm, src);

	pComp->parse_fsm(src);

	delete pComp;
	delete pFsm;
	return status;
}


/////// End File : fmsui.cpp  /////////////////////////////////////////