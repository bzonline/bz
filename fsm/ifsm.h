#pragma once
//////////////////////////////////////////////////////////////////////
// File name : Fsm.h
// Purpose : To define simple FSM implementation base class. 
//            This class to be inherited
///////////////////////////////////////////////////////////////////////

#include <string>
#include <list>
#include <map>
#include <mutex>
#include <exception>
//#include <iostream>

namespace bz
{

	class iNode
	{
		virtual unsigned int PutTransunsigned int PutTrans(const Transition& transition) = 0;
		virtual int execute() = 0;
	};
	
	
	class ifsm
	{
		virtual unsigned int PutNode(iNode& node) = 0;
		virtual iNode* GetNode(unsigned int id) = 0;
		virtual int Start(unsigned int id) = 0;
		virtual unsigned int Stop() = 0;
	};

} // namespase bz
///////////////// End File  : Fsm.h  ///////////////////////////////