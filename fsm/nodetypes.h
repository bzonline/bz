#pragma once
//////////////////////////////////////////////////////////////////////
// File name : nodetypes.h
// Purpose : Реализует Node функциональность.
// Author : Boris Zverev (bz) aka Privet
///////////////////////////////////////////////////////////////////////


namespace bz
{
	typedef enum _NodeType : unsigned int
	{
		nodeNONE,
		nodePARSE_COMMAND_LINE,
		nodeREAD_FILE_CONTENT,
		nodeCOMPILE_BZ_CODE,
#ifdef NODETYPES_EXT
#include <nodetypes_ext.h>
#endif
		nodeUNDEFINED
	} NodeType;
}

///////////////// End File  : nodetypes.h  ///////////////////////////////