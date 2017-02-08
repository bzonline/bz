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


std::map<std::string, NodeParams> NodeMap =
{
	{ "none",{ nodeNONE,                               NULL,                0,  0 } },
	{ "parse_command_line",{ nodePARSE_COMMAND_LINE,  parse_command_line,  1,  1 } },
	{ "read_file_content",{ nodeREAD_FILE_CONTENT,   read_file_content,   1,  1 } },
	{ "compile_bz_code",{ nodeCOMPILE_BZ_CODE,     compile_bz_code,     1,  1 } },
	{ "undefined",{ nodeUNDEFINED,           NULL,                0,  0 } }
};



std::string get_file_content(const char *filename)
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

///////////////// End File  : worker.h  ///////////////////////////////