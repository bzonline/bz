#pragma once
/**
 *  \file file.h
 *  \brief Defines Fsm class.
 */
//////////////////////////////////////////////////////////////////////
// File name : fsm.h
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
#include <nodetypes.h>


namespace bz
{
	typedef   unsigned int      id_t;
	typedef   unsigned int   count_t;
	typedef            int  status_t;

	struct Transition
	{
		std::vector<id_t>    input; // vector of input statuses
		std::vector<id_t>   output; // vector of next nodes ids
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
		Contact(const ContactType _type, const std::string _name = "");
		virtual ~Contact();
		
		id_t                            id;
		ContactType                   type;
		std::string                   name;
		pthread_mutex_t                mtx;
		Connect*                  pconnect;

		friend class Fsm;
	};
	
///////////////////////////////////////////////////////////  Connect
	struct Connect
	{
		Connect();
		Connect(const Connect& other);
		Connect(Connect&& other);
		Connect(const std::string _name);
		virtual ~Connect();
		
		Connect& operator=(const Connect& other);
		Connect& operator=(Connect&& other);

		Connect& operator+=(Contact& contact);

		id_t                            id;
		std::string                   name;
		void*                        pdata;
		size_t                        size;
		std::vector<Contact*>    pcontacts;
		count_t                   id_count;
	};


	class Fsm;
	class Compile;

	// Почему Connect? Потому, что он имеет данные и связан с in & out
	typedef status_t(*Job)(Connect& connect);

///////////////////////////////////////////////////////////  Node
	class Node
	{
	public:
		Node();
		Node(const Node& other);
		Node(Node&& other);
		Node(Fsm* _pfsm, const NodeType _type, const std::string _name="", const Job _pjob=NULL);
		virtual ~Node();
		
		Node& operator=(const Node& other);
		Node& operator=(Node&& other);
		
		Node& operator+=(Transition& transition);
		Node& operator+=(Contact& contact);
		Node& operator+=(const Job pjob);

		int execute();
		
	private:
		id_t                            id;
		NodeType                      type;
		std::string                   name;  // имя ноды -> имя выполняемой функции
		Fsm*                          pfsm;
		Job                           pjob;
		count_t                 cont_count;
		std::map<std::vector<id_t>, std::vector<id_t>>  transitions;
		std::vector<Contact>      contacts;

		friend class Fsm;
	};
	
	
///////////////////////////////////////////////////////////  Fsm
	class Fsm
	{
	public:
		Fsm();
		Fsm(const id_t _id, const std::string _name = "");
		virtual ~Fsm();

		// StateMachine Method prototype
	//	int(*pExec) (Node& node);

		// returns assigned id to inserted node.
		/// @param[in] : Node to be added into Fsm
		/// @returns added node id that is assigned by this function.
		id_t PutNode(const Node& pnode);

		Fsm& operator+=(const Node& node);
		Fsm& operator+=(const Connect& connect);

		/// @param[in] : 
		/// @returns 
		Node& GetNode(const id_t id);

		status_t Start(id_t id);

		// returns id of last node whicn completed its own job.
		unsigned int Stop();

	private:
		id_t                                     id;
		std::string                            name;
		//         node id     node
		std::map<id_t, Node>                  nodes;
		std::map<id_t, Connect>            connects;
		count_t                          node_count;
		count_t                          conn_count;
		id_t                                id_last;

		friend class Compile;
	};

} // namespase bz

///////////////// End File  : fsm.h  ///////////////////////////////