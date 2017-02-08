//////////////////////////////////////////////////////////////////////
// File name : compiler.cpp
// Purpose : Реализует worker класс
// Author : Boris Zverev (bz) aka Privet
///////////////////////////////////////////////////////////////////////

#include <compiler.h>

using namespace bz;


Compile::Compile(Fsm* _pFsm, const std::string& _src) :
	pFsm(_pFsm),
	src(_src)
{}

Compile::~Compile()
{
	src.clear();
}


Node* Compile::parse_node(Fsm* pFsm, const std::string name)
{
	const NodeParams& node_param = NodeMap[name];

	Node* pnode = new Node(pFsm, node_param.type, name);

	// Парсим контакты
	Contact* pcontact = NULL;
	for (size_t i = 0; i < node_param.in_count; i++)
	{
		Connect* pconn = NULL;
		std::string cont_name = "";
		std::string conn_name = "";
		// TODO Находим тип и имя контакта
		pcontact = new Contact(ctIN, cont_name);
		*pnode += *pcontact;
		// TODO Проверь и создай если надо все соединения, куда подключен этот контакт.
		pconn = new Connect(conn_name);
		pconn->pcontacts.push_back(pcontact);
	}

	return pnode;
}

Fsm* Compile::parse_fsm(const std::string src)
{
	// TODO Парсим Fsm. Находим id и bvz.
	pFsm->id = 1;

	// TODO Парсим узлы
	do
	{
		Node* pnode = NULL;
		std::string name = "";

		// Есть узел!
		pnode = parse_node(pFsm, name);

		*pFsm += *pnode;
	} 
	while (1);  // Крутимся до конца программы. Ищем узлы.

	return pFsm;
}

///////////////// End File  : compiler.h  ///////////////////////////////