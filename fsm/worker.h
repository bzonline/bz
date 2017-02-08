#pragma once
//////////////////////////////////////////////////////////////////////
// File name : worker.h
// Purpose : Реализует Node функциональность.
// Author : Boris Zverev (bz) aka Privet
///////////////////////////////////////////////////////////////////////

#include <fsm.h>
//#include <fstream>
//#include <sstream>
//#include <iostream>


namespace bz
{
	status_t parse_command_line(Connect& connect);
	status_t read_file_content(Connect& connect);
	status_t compile_bz_code(Connect& connect);

	struct NodeParams
	{
		NodeType         type;
		Job              pjob;
		count_t      in_count;
		count_t     out_count;
	};

	extern std::map<std::string, NodeParams> NodeMap;

	std::string get_file_content(const char *filename);
	//std::string get_file_contents2(const char *filename);
}

///////////////// End File  : worker.h  ///////////////////////////////