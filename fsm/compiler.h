#pragma once
//////////////////////////////////////////////////////////////////////
// File name : compiler.h
// Purpose : формирует Fsm из текста программы на языке bz.
// Author : Boris Zverev (bz) aka Privet
///////////////////////////////////////////////////////////////////////

#include <worker.h>

namespace bz
{
	class Compile
	{
	public:
		Compile(Fsm* pFsm, const std::string& _src);
		virtual ~Compile();

		Fsm* parse_fsm(const std::string src);
		Node* parse_node(Fsm* pFsm, const std::string name);

	private:
		Fsm* pFsm;
		std::string   src;
	};
}

///////////////// End File  : compiler.h  ///////////////////////////////