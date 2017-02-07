//////////////////////////////////////////////////////////////////////
// File name : fsm.cpp
// Purpose : Реализует Fsm класс
// Author : Boris Zverev (bz) aka Privet
///////////////////////////////////////////////////////////////////////

#include <fsm.h>

using namespace bz;

/* #include <iostream>
#include <system_error>
try
{
	throw std::system_error(EFAULT, std::system_category());
}
catch (std::system_error& error)
{
	std::cout << "Error: " << error.code() << " - " << error.what() << '\n';
}
*/

///////////////////////////////////////////////////////////  Contact

Contact::Contact() :
	id(0),
	type(ctUNDEFINED),
	name(),
	mtx(PTHREAD_MUTEX_INITIALIZER),
	pconnect(NULL)
{
	pthread_mutex_init(&mtx, NULL);
}

Contact::Contact(const ContactType _type, const std::string _name) :
	id(0),
	type(_type),
	name(_name),
	mtx(PTHREAD_MUTEX_INITIALIZER),
	pconnect(NULL)
{
	pthread_mutex_init(&mtx, NULL);
}

Contact::~Contact()
{
	name.clear();
	pthread_mutex_destroy(&mtx);
}


///////////////////////////////////////////////////////////  Connect
Connect::Connect() :
	id(0),
	name(),
	pdata(NULL),
	size(0),
	contacts()
{}

Connect::Connect(const std::string _name) :
	id(0),
	name(_name),
	pdata(NULL),
	size(0),
	contacts()
{}

Connect::~Connect()
{
	name.clear();
	if(pdata)
		free(pdata);
	contacts.clear();
}

Connect& Connect::operator+=(Contact& contact)
{
	contact.id = id_count++;
	contacts.push_back(&contact);
	return *this;
}


///////////////////////////////////////////////////////////  Node
Node::Node() :
	id(0),
	type(nodeUNDEFINED),
	name(),
	pfsm(NULL),
	pjob(NULL),
	cont_count(0),
	transitions(),
	contacts()
{}

Node::Node(Fsm* _pfsm, const NodeType _type, const std::string _name, const Job _pjob) :
	id(0),
	type(_type),
	name(_name),
	pfsm(_pfsm),
	pjob(_pjob),
	cont_count(0),
	transitions(),
	contacts()
{}

Node::~Node()
{
	name.clear();
	transitions.clear();
	contacts.clear();
}


Node& Node::operator+=(Transition& transition)
{
	transitions[transition.input] = transition.output;
	return *this;
}


Node& Node::operator+=(Contact& contact)
{
	contact.id = cont_count++;
	contacts.push_back(contact);
	return *this;
}


Node& Node::operator+=(const Job _pjob)
{
	pjob = _pjob;
	return *this;
}


//            in/out
int Node::execute()
{
//	// ждём возвращения рабочей программы.
//	// результат возвращается в Connect структуре.
//#ifdef THREAD_POOL
//	// ждём, пока будут готовы все статусы.
////	wait(data.mtx);
//
////	queue(data.pjob, &data);
//#else
//	pjob(&data);
//#endif
//	if(++Ncount >= transitions.size())
//	{
//		pjob(&data);
//	}
//	else
//		return 0;
//	
//	// получаем ссылки на следущую ноду
//	size_t              next_id = 0;
//	std::vector<size_t> next_ids;
////		next_ids.clear;
//
//	next_ids = transitions[data.statuses]; // БЕДА может быть несколько одинаковых ключей.
//
//	for (size_t i=0; i<Ncount; i++)
//	{
//		next_id = next_ids[i];
//		Node* pnode = pfsm->GetNode(next_id);
////		pnode->data.size = data.size;
////		pnode->data.pdata = data.pdata;
//		pnode->execute();
//	}
	return 0;
}

///////////////////////////////////////////////////////////  Fsm
Fsm::Fsm() :
	id(0),
	name(),
	nodes(),
	connects(),
	node_count(0),
	conn_count(0),
	id_last(0)
{}

Fsm::Fsm(const size_t _id, const std::string _name):
	id(_id),
	name(_name),
	nodes(),
	connects(),
	node_count(0),
	conn_count(0),
	id_last(0)
{}

Fsm::~Fsm()
{
	name.clear();
	nodes.clear();
}

// returns assigned id.
/// @param[in] : Node to be added into Fsm
/// @returns added node id that is assigned by this function.
size_t Fsm::PutNode(const std::string name)
{
	Node* pnode = new Node(this, nodeUNDEFINED, name);
	nodes[node_count] = *pnode;
	return node_count++;
}

size_t Fsm::PutNode(const Node& node)
{
	nodes[node_count] = node;
	return node_count++;
}

Fsm& Fsm::operator+=(const Node& node)
{
	nodes[node_count++] = node;
	return *this;
}

Fsm& Fsm::operator+=(const Connect& connect)
{
	connects[conn_count++] = connect;
	return *this;
}


/// @param[in] : 
/// @returns 
Node* Fsm::GetNode(const size_t id)
{
	Node* pnode = &nodes[id];
	return pnode;
}

int Fsm::Start(const size_t id)
{
	id_last = id;
// unlock stop
	return nodes[id].execute();
}

// returns id of last node whicn completed its own job.
size_t Fsm::Stop()
{
// lock stop
	return id_last;
}


/////////// End File : fsmT.cpp ////////////////////////////////