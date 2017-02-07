#pragma once/**
 *  \file file.h
 *  \brief Defines Fsm class.
 */
//////////////////////////////////////////////////////////////////////
// File name : Fsm.h
// Purpose : Defines Fsm class. 
// Author : Boris Zverev (bz) aka Privet
///////////////////////////////////////////////////////////////////////

#include <string>
#include <list>
#include <vector>
#include <map>
//#include <mutex>
//#include <stdexcept>
//# include <cerrno>
#include <pthread.h>


namespace bz
{
	struct Transition
	{
		std::vector<unsigned int> input;  // vector of input statuses
		std::vector<unsigned int> output; // vector of next nodes ids
	};
	
	struct Connect;
	
///////////////////////////////////////////////////////////  Contact
	enum ContactType: unsigned int
	{
		ctNONE,
		ctIN,
		ctOUT,
		ctOUTX,
		ctINOUT,
		ctUNDEFINED
	};
	
	
	struct Contact
	{
		Contact();
		virtual ~Contact();
		
		unsigned int            id;
		pthread_mutex_t        mtx;
		Connect*          pconnect;
		short                 type;
		short              typenow;
	};
	
///////////////////////////////////////////////////////////  Connect
	struct Connect
	{
		Connect();
		Connect(Contact& out);
		virtual ~Connect();
				
		unsigned int              id;
		void*                  pdata;
		unsigned int            size;
		Contact               output;  // От Ноды N
		std::vector<Contact*> inputs;  // К Нодам N+1 и далее...
	};


	class Fsm;

	// Почему Connect? Потому, что он имеет данные и связан с in & out
	typedef int (*Job)(Connect& connect);

///////////////////////////////////////////////////////////  Node
	class Node
	{
	public:
		Node();
		Node(Fsm* _pfsm, const unsigned int _id, const std::string _name);
		//Node(const Node& other) = delete;
		//Node(Node&& other) = delete;
		virtual ~Node();
		
//		Node& operator=(const Node& other) = delete;
//		Node& operator=(Node&& other) = delete;
		
		Node& operator+=(const Transition& transition);
		Node& operator+=(const Contact& contact);
		Node& operator+=(const Job pjob);

		int execute();
		
	private:
		unsigned int   id;
		std::string  name;  // имя ноды -> имя выполняемой функции
		Fsm*         pfsm;
		Job          pjob;
		
		std::map<std::vector<unsigned int>, 
		         std::vector<unsigned int>> transitions;
		
		std::vector <Contact>  contacts;
	};
	
	
///////////////////////////////////////////////////////////  Fsm
	class Fsm
	{
	public:
		Fsm();
		Fsm(const std::string name);
		virtual ~Fsm();

		// StateMachine Method prototype
	//	int(*pExec) (Node& node);

		// returns assigned id to inserted node.
		/// @param[in] : Node to be added into Fsm
		/// @returns added node id that is assigned by this function.
		unsigned int AddNode(const std::string name);
		unsigned int AddNode(const Node* pnode);

		/// @param[in] : 
		/// @returns 
		Node* GetNode(unsigned int id);

		int Start(unsigned int id);

		// returns id of last node whicn completed its own job.
		unsigned int Stop();

	private:
		std::string                   name;
		//         node id     node
		std::map<unsigned int, Node>  nodes;
		unsigned int               id_count;
		unsigned int                id_last;
	};

} // namespase bz

///////////////// End File  : Fsm.h  ///////////////////////////////