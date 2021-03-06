#ifndef HP_HPP
#define HP_HPP

/*** TYPE Definitions *******/
#include <string.h>
#include <cstring>
#include <time.h>
#include <list>
#include <set>
#include <algorithm>
#include <cstddef>
#include <stdarg.h>
#include <sstream>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

using namespace std;

#define forlist(x) for (iter=x.begin(),end=x.end(); iter!=end; ++iter)

class QI {
public:

	int id;
	int time;

	QI(const int& idx = 0, const int& timex = 0) :
			id(idx), time(timex) {
	}
	virtual ~QI() {
	}
	;
	virtual void unmarshalling(const char* c) {
	}
	;
	long size() const;
	void marshalling(char* c) const;

	virtual void printItem(std::ostream& os) const {
	}
	;

};

void printQI(QI* t);


bool const_check(int& i , int& g);

void deleteStar(QI* star);

std::ostream& operator<<(std::ostream& os, const QI& q);
//std::ostream& operator<<(std::ostream& os, const QI*& q);

/************ Queue *************////START////
template<class T>
class AQueue {
public:
	list<T*> Q;
};

#define forlist(x) for (iter=x.begin(),end=x.end(); iter!=end; ++iter)

template<class T> std::ostream& operator<<(std::ostream& os,
		const AQueue<T>& q);
template<class T> std::ostream& operator<<(std::ostream& os,
		const AQueue<T>& q) {

	//cout<<" size "<<q.Q.size();
	typename list<T*>::const_iterator iter, end;
	os << "[";
	if (q.Q.size() > 0) {
		forlist(q.Q)
		{
			if (iter != q.Q.begin()) {
				os << ",";
			}
			//cout<<" here 1";
			T *qi = (T*) *iter;
			//cout<<" here 2";
			os << *qi;
		}
	}

	os << "]";
	return os;
}
template<class T> void clearQueue(AQueue<T>& q);
template<class T> void clearQueue(AQueue<T>& q) {
	/*typename list<T*>::const_iterator iter, end;
	forlist(q.Q){
		delete *iter;
	}*/
	//cout<<q<<" "<<q.Q.size()<<endl;
	q.Q.clear();
	//cout<<q<<q.Q.size()<<endl;
}

template<class T> T getQueue(const AQueue<T>& q, const int i);
template<class T> T getQueue(const AQueue<T>& q, const int i) {
	typename list<T*>::const_iterator iter = q.Q.begin();
	advance(iter, i);
	return (**iter);
}

template<class T> T* getQueuePtr(const AQueue<T>& q, const int i);
template<class T> T* getQueuePtr(const AQueue<T>& q, const int i) {
	typename list<T*>::const_iterator iter = q.Q.begin();
	advance(iter, i);
	return (*iter);
}


string serialize(string& s, const AQueue<string> q);
string serialize(string& s, const string q);
AQueue<string> deserialize(AQueue<string>& q, string& s);
std::ostream& operator<<(std::ostream& os, const AQueue<QI>& q);

template<class T, class Q> AQueue<T> add(Q* S, AQueue<T>& q);
template<class T, class Q> AQueue<T> add(Q* S, AQueue<T>& q) {
	//T* t = &S;
	q.Q.push_back(S);
	return q;
}

template<class T, class Q> AQueue<T> add(Q& S, AQueue<T>& q);
template<class T, class Q> AQueue<T> add(Q& S, AQueue<T>& q) {
	Q* t = &S;
	q.Q.push_back(t);
	return q;
}
/*
 AQueue<string> addString(string s, AQueue<string>& q);*/

template<class T> T remove(const T& S, AQueue<T>& q);
template<class T> T remove(const T& S, AQueue<T>& q) {
	std::_List_iterator<T> i = std::find(q.Q.begin(), q.Q.end(), S);
	T ret = (*i);
	if (i != q.Q.end())
		q.Q.erase(i);
	return ret;
}

template<class T> T remove(AQueue<T>& q, const int& pos);
template<class T> T remove(AQueue<T>& q, const int& pos) {
 typename list<T*>::iterator iter=q.Q.begin();
	advance(iter,pos);
	q.Q.erase(iter);
}


template<class T> T removeFirst(AQueue<T>& q);
template<class T> T removeFirst(AQueue<T>& q) {
	//T* first=new T();
	T first = *q.Q.front();
	q.Q.pop_front();
	return first;
}

template<class T> bool findInQueue(const T& S, AQueue<T>& q);
template<class T> bool findInQueue(const T& S, AQueue<T>& q) {
	std::_List_iterator<T> i = std::find(q.Q.begin(), q.Q.end(), S);
	if (i != q.Q.end())
		return true;
	return false;
}

template<class T> void printSize(AQueue<T>& q);
template<class T> void printSize(AQueue<T>& q) {
	std::cout << q.Q.size() << '\n';
}

template<class T> int const_size(const AQueue<T>& q);
template<class T> int const_size(const AQueue<T>& q) {
	//cout<<'\n'<<q;
	int i = q.Q.size();
	//cout<< " const_size "<<i;
	return i;
}

void addToAddress(string& address, const int& id);
/************ ObQueue *****************/

class QQueue: public AQueue<QI> {
public:
	void marshalling(char* c);
	long size() const;
	void printItem(std::ostream& os) const;

};
std::ostream& operator<<(std::ostream& os, const QQueue& q);
QI* removePosition(QQueue& q, const int& next);
void printQQueue(const QQueue &q);
string int2string(const int& e);
int string2int(const string& s);

/************ Replica *************/ ///START////
typedef AQueue<string> Queue;
typedef AQueue<int> ChkpointQueue;
typedef QQueue ConnQueue;
typedef AQueue<string> StringQueue;
typedef string* StringStar;
typedef StringStar StringSStar;
typedef QQueue Sess2ReplQueue;

class Sess2Repl: public QI {
public:
	string replicaAddress;

	Sess2Repl(const int id = -1, const string& replicaAddress = "") :
			QI(id), replicaAddress(replicaAddress) {
	}
	//long size() const;
	void printItem(std::ostream& os) const;
	void unmarshalling(const char* c);
	//void marshalling(char* c) const;

};

typedef Sess2Repl* Sess2ReplStar;
typedef Sess2Repl* Sess2ReplSStar;
void Sess2Repl_unmarshalling(Sess2Repl* t, const char* c);
long Sess2Repl_sizeof(const Sess2Repl& t);
void Sess2Repl_marshalling(char* c, const Sess2Repl* t);
void printSess2Repl(Sess2Repl *t);
void Sess2ReplStar_unmarshalling(Sess2ReplStar* t, const char* c);
long Sess2ReplStar_sizeof(const Sess2ReplStar& t);
void Sess2ReplStar_marshalling(char* c, const Sess2ReplStar* t);
void Sess2ReplSStar_unmarshalling(Sess2ReplSStar* t, const char* c);
long Sess2ReplSStar_sizeof(const Sess2ReplSStar& t);
void Sess2ReplSStar_marshalling(char* c, const Sess2ReplSStar* t);

Sess2Repl* sess2ReplStar(const int id=-1, const string& replicaAddress = "");
Sess2Repl* sess2ReplSStar(const int id=-1, const string& replicaAddress = "");
bool const_isSess2Repl(const Sess2Repl* r, const int& id, const int& time,
		const string& addr);
list<QI*>::const_iterator getFirstSess2ReplIter(const QQueue& q, const int& c,
		const int& s, const string& addr);
bool const_hasSess2Repl(const QQueue& q, const int id = -1, const int time = -1,
		const string replicaAddress = "");
long Sess2ReplQueue_sizeof(const QQueue& q);
void id2address(const int& id, string& address);
void addRequestedOperationToParameters(StringStar& operReq, StringQueue& parametersIn);
void addListnAddresses(const int& id, StringStar& address, StringQueue& addrQueue);
void addMsgBusCtrlAddresses(const int& id, StringStar& address,
		StringQueue& addresses);
void copyStringQueue(const StringQueue& from, StringQueue& to);
void copyQQueue(const QQueue& from, QQueue& to);
void copyParameters(const StringQueue& from, StringQueue& to);
//long Sess2Repl::size() const;
string assignTarget(const string& sessionId, Sess2ReplQueue& sess2repl);
string abstractMatchTask(string& inputMsg);
void getSessionIdFromData(string& sessionId, const StringQueue& sessionData);
void getSessionCreateTimeFromData(string& create_time, const StringQueue& sessionData);
string chooseReplcaLessSessions(StringQueue replicas,
		Sess2ReplQueue& sess2repl);
string chooseReplica(StringQueue replicas,
		Sess2ReplQueue& sess2repl);
void addToReplcaSessions(Sess2Repl* sr, const string sessionId,
		const string replica, Sess2ReplQueue& sess2repl);
void updateReplcaSession(const string sessionId, Sess2ReplQueue& sess2repl);
int stringToInt(string s);
void isNewSession(const string& sessionId, Sess2ReplQueue& sess2repl, int newSes);


class Replc: public QI {
public:
	string address;
	Replc(const string& s1 = "") :
			QI(), address(s1) {
	}
	Replc(const char* c);

	bool operator==(const Replc& m2) {
		if ((*this).address == m2.address) {
			return true;
		}
		return false;
	}
	void unmarshalling(const char* c);
	//long size() const;
	//void marshalling(char* c) const;
	void printItem(std::ostream& os) const;

};


typedef QQueue ReplcQueue;
typedef Replc* ReplcStar;
typedef ReplcStar ReplcSStar;
void printReplcStar(std::ostream& os, Replc* r);
void printReplc(ReplcSStar r);
Replc* replcStar(const string s1 = "");
list<QI*>::iterator getFirstReplcIter(QQueue& q, const int& c, const int& s,
		const string& addr);
list<QI*>::const_iterator getFirstReplcIter(const QQueue& q, const int& c,
		const int& s, const string& addr);
bool hasReplcaAddress(const string& addr, const ReplcQueue& q);

void Replc_unmarshalling(Replc* t, const char* c);
long Replc_sizeof(const Replc& t);
void Replc_marshalling(char* c, const Replc* t);

void ReplcStar_unmarshalling(ReplcStar* t, const char* c);
long ReplcStar_sizeof(const ReplcStar& t);
void ReplcStar_marshalling(char* c, const ReplcStar* t);
void ReplcSStar_unmarshalling(ReplcStar* t, const char* c);
long ReplcSStar_sizeof(const ReplcStar& t);
void ReplcSStar_marshalling(char* c, const ReplcStar* t);
std::ostream& operator<<(std::ostream& os, const Replc& q);
StringQueue listReplcas(const ReplcQueue& q);
void renewAlive(const StringQueue& address, ReplcQueue& q);

//const Replc NullReplc = Replc();

int const_compareStrings(const string& message1, const string& message2);
void my_print(const std::string message1, const std::string message2 = "");
void my_print(const int message1, const std::string message2);

string getReplcAddress(Replc* r);

Replc* removeReplcPosition(QQueue& q, const int& next);

/************ Connections *************/ ///START////
class Conn: public QI {
public:
	string address1;
	string address2;
	int status;
	string create_time;
	AQueue<string> reqMsg;
	AQueue<string> respMsg;

	Conn(const string& address1 = "", const string& address2 = "",
			const int& id = -1, const int& status = 1,
			const string& create_time = "", const int& time = 0) :
			QI(id, time), address1(address1), address2(address2), status(
					status), create_time(create_time) {

	}
	Conn(const char* c);
	bool operator==(const Conn& m2) {
		if ((*this).address1 == m2.address1 && (*this).address2 == m2.address2
				&& (*this).id == m2.id
				&& (*this).create_time == m2.create_time) {
			return true;
		}
		return false;
	}
//	void toString(char* c);
	void unmarshalling(const char* c);
	//long size() const;
	//void marshalling(char* c) const;
	void printItem(std::ostream& os) const;
};
void Conn_marshalling(char* c, const Conn* s);
void Conn_unmarshalling(Conn* t, const char* c);
long Conn_sizeof(const Conn& c);

int getId(const QI* conn);
string getCreateTime(const Conn* conn);

typedef Conn* ConnStar;
typedef ConnStar ConnSStar;

string* stringStar(string s="");
void setStringStar(string*& sptr, const string s="");
string* setNewStringStar(string*& sptr, const string s);
void printStringQueue(const StringQueue &q);
void deleteConnStar(ConnStar& conn);
void deleteStringStar(StringStar& conn);
Conn* makeConnCopy(Conn*& conn);
void printConn(const ConnStar& conn);
void setConnStatus(ConnStar& conn1, const int& s);
Conn* connStar(const string& s1 = "", const string& s2 = "", const int& c = -1,
		const int& s = -1, const string& t = "");
void ConnStar_marshalling(char* c, const ConnStar* ss);
void ConnStar_unmarshalling(ConnStar* tt, const char* c);
long ConnStar_sizeof(const ConnStar& cc);
void ConnSStar_marshalling(char* c, const ConnStar* ss);
void ConnSStar_unmarshalling(ConnStar* tt, const char* c);
long ConnSStar_sizeof(const ConnStar& cc);
std::ostream& operator<<(std::ostream& os, const Conn& q);
std::ostream& operator<<(std::ostream& os, const ConnStar& q);
void addMsgConn(ConnStar& conn, const string& address, string& msg);
void addMsgConn(ConnStar& conn, const string& address, StringQueue& msgParams);
bool hasFirstMsgConn(ConnStar& conn, const string& address, const string& msg);
string rmvMsgConn(ConnStar& conn, const string& address);

int const_ConnStringQueueSize(ConnStar& connInNetwork, QQueue& connQueueInMB);
bool const_hasConn(const QQueue& q, const string a1 = "", const string a2 = "",
		const int& c = -1, const int s = -1, const string create_time = "-1");
list<QI*>::const_iterator getFirstConnIter(const QQueue& q,
		const string a1 = "", const string a2 = "", const int& c = -1,
		const int s = -1, const string create_time = "-1");
Conn* getFirstConn(const QQueue& q, const string a1 = "", const string a2 = "",
		const int& c = -1, const int s = -1, const string create_time = "-1");
bool const_hasConnBPELInstanceMatch(const QQueue& q, const string& a1,
		const string& a2, const int& c, const int& s, const string& create_time,
		const StringQueue& propert);
bool connEquals(const ConnStar conn1, const ConnStar conn2);
int getConnId(const Conn* c);
void copyConnParameters(Conn* conn, const string a, StringQueue& parameters,
		const int mode);

string getRequestedOperation(StringQueue& parametersReqIn);
int getRequestedBinding(StringQueue& parametersReqIn);


/*************** CONNQUEUE **************/
void rmvTimedOut(QQueue& q, const int& timeout);
string getTime();

typedef QQueue DataQueue;
typedef Conn Data;
typedef Conn* DataStar;
typedef Data* DataSStar;

/******************** carts - start  **************************/
DataStar makeDataCopy(const DataStar& data);
DataQueue makeDataCopy(const DataQueue data);
Data* dataStar(const string& s1 = "", const string& s2 = "", const int& c = -1,
		const int& s = -1, const string& t = "");
void DataStar_marshalling(char* c, const DataStar* ss);
void DataStar_unmarshalling(DataStar* tt, const char* c);
long DataStar_sizeof(const DataStar& cc);
void DataSStar_marshalling(char* c, const DataStar* ss);
void DataSStar_unmarshalling(DataStar* tt, const char* c);
long DataSStar_sizeof(const DataStar& cc);
void DataQueue_marshalling(char* c, const DataQueue* ss);
void DataQueue_unmarshalling(DataQueue* tt, const char* c);
long DataQueue_sizeof(const DataQueue& cc);
DataStar makeDataCopy(const DataStar& conn);
string getFromDataResultItem(QI* conn, const int pos);
/******************** carts - end **************************/

//void readCartItem(int cartId);
void addData(DataQueue dataQueue, DataStar data, int dataId);
void readData(const DataQueue dataQueue, const int dataId, DataStar result);
void updateData(DataQueue dataQueue, const int dataId, const int itemId);
void addData(DataQueue dataQueue, DataStar data, int dataId);
void updateGetDataId(const StringQueue& q, int& dataId);
ConnQueue selectDataQuery(QQueue& q, string id);
ConnQueue executeDataQueryCartItems(const string& query, QQueue& dataItems, QQueue& dataCarts);
ConnQueue executeDataQueryCartItems2(const string& query, QQueue& dataItems, QQueue& dataCarts);
ConnQueue executeDataQueryCartItems3(const string& query, QQueue& availItems,
		QQueue& cartItems);
/************ Connections *************/ ///END////
/************ Replica *************////END////
int addiTime(QQueue& q, const int& next);
int getSesTime(QQueue& q, const int& next);
Sess2Repl* getSess2ReplcPos(QQueue& q, const int& next);
Conn* removeDataQuery(QQueue& q, string value);
string appendToString(string& to, const string& from);
Conn* insertDataQuery(QQueue& q, string id, string value2="");
Conn* insertDataIncQuery(QQueue& q, string value2="");
///*****************************************/
//************* ConnQueue *************//START///
ConnStar getFirstStatus(const QQueue& q, const int& s);
list<QI*>::const_iterator getFirstStatusIter(const QQueue& q, const int& s);
bool const_hasConnStatus(const QQueue& q, const int& a, const int& s,
		const string& create_time = "-1");
bool const_hasConnMsg(const QQueue& q, const int& c, const int& s,
		const string& create_time, const string& address, const string& msg);
bool const_isConnTarget(const ConnStar& conn, const AQueue<string>& addrQueue);
bool const_hasToRead(const QQueue& q, const string& a, const int&c,
		const string& create_time = "");
ConnStar getFirstConnStatus(const QQueue& q, const int& c = -1, const int& s =
		-1, const string& create_time = "");
int giveNextId(QQueue& q);
bool const_isConn(Conn* conn, const string& address1 = "",
		const string& address2 = "", const int& id = -1, const int status = -1,
		const string& create_time = "-1");
void onePartyClosed(QQueue& q, const int& c, const string& create_time);
list<QI*>::const_iterator getFirstConnStatusIter(const QQueue& q, const int& c =
		-1, const int& s = -1, const string& create_time = "-1");
Conn* removeFirstConn(QQueue& q, const int& a, const int& s,
		const string& createTime);
bool const_hasStatus(const QQueue& q, const int& s);
bool const_hasConnAddress(const QQueue& q, const string& a);
Conn* removeFirstConnToAddress(QQueue& q, const string& a);
void removeConn(QQueue& q, const int& c, const string& createTime);
QQueue& setConnInQueueStatus(QQueue& connQueue, const ConnStar& conn1,
		const int& s);
int getNextId(const QQueue& connQueue, const int& maxId);
bool const_BPELmatch(const StringQueue& params, const StringQueue& propert);
//************* ConnQueue *************//END///
///*********** Replica Discovery - Registry ********************/

/***************  STRING ********************/

long string_sizeof(const string& s);
void string_marshalling(char* c, const string* s);
void string_unmarshalling(string* t, const char* c);

void StringStar_marshalling(char* c, const StringStar* ss);
void StringStar_unmarshalling(StringStar* tt, const char* c);
long StringStar_sizeof(const StringStar& cc);
void StringSStar_marshalling(char* c, const StringStar* ss);
void StringSStar_unmarshalling(StringStar* tt, const char* c);
long StringSStar_sizeof(const StringStar& cc);


/***************  ADDRQUEUE ********************/

long StringQueue_sizeof(const AQueue<string>& q);
void StringQueue_marshalling(char* c, const AQueue<string>* q);
void StringQueue_unmarshalling(AQueue<string>* t, const char* c);

/***************  CONNQUEUE ********************/

void ConnQueue_marshalling(char* c, const QQueue* q);
void ConnQueue_unmarshalling(QQueue* t, const char* c);
long ConnQueue_sizeof(const QQueue& q);


/***************  SESS2REPL_QUEUE ********************/

void Sess2ReplQueue_marshalling(char* c, const QQueue* q);
void Sess2ReplQueue_unmarshalling(QQueue* t, const char* c);
long Sess2ReplQueue_sizeof(const QQueue& q);

/***************  RESTQUEUE ********************/
long ReplcQueue_sizeof(const QQueue& q);
void ReplcQueue_unmarshalling(QQueue* t, const char* c);
void ReplcQueue_marshalling(char* c, const QQueue* q);

//long ChkpointQueue_sizeof(const QQueue<int>& q);

//void ChkpointQueue_unmarshalling(QQueue<int>* t, const char* c);
//void ChkpointQueue_marshalling(char* c, const QQueue<int>* q);
bool const_hasReplcaAddress(const string& addr, const ReplcQueue& q);

long IntQueue_sizeof(const AQueue<int>& q);
void IntQueue_unmarshalling(AQueue<int>* t, const char* c);
void IntQueue_marshalling(char* c, const AQueue<int>* q);

void testStringQueue_marshalling();
void testConn_marshalling();
void testConnStar_marshalling();
void testReplcQueue_marshalling();
void testConnQueue_marshalling();
void testReplcStar_marshalling();
void testSess2Repl_marshalling() ;
void testSess2ReplStar_marshalling();
void testStringStar_marshalling();
void testSess2ReplQueue_marshalling();
void testString_marshalling();

#endif



//REST functions

string ResourcesId2Url(const int& id);
void updateCache(ConnQueue& cachedItems, const string& url, string& item, int& eTag);
void getFromCache(const ConnQueue& cachedItems, const string& url, string& item, int& eTag, int& exists, int& eTagOK);
void addToResource(ConnQueue& resourceItems, string& parameters, const string& url, string& item);
void deleteResource(ConnQueue& resourceItems, string& parameters, const string& url, string& item);
void updateResource(ConnQueue& resourceItems, string& parameters, const string& url, string& item);
void getFromResource(const ConnQueue& resourceItems, const string& url, string& item, int& exists);
void isGet(string url,int& foundGet);
void joinStringsWithParameters(string action,string resourceId, string parameters, string& actionIDParam);
void breakTokens(string url,string& controller, string& action, string& resourceId);
void breakTokensWithParameters(string url,string& controller, string& action, string& resourceId, string& parameters);
void splitUrl(string url,string& action,string& path, string& protocol, int& eTag);
void findPathInParams(const StringQueue& queue, string& path);
void joinStrings(string action,string path,string& actionPath);
void splittoken(string dataMsg,string& action,string& path);
void result2Items (ConnQueue result, StringQueue dataOut);
void splitPath(const string& path, StringQueue& q);
