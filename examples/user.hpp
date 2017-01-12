#include <iostream>

#ifdef  HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef  EXAMPLE_CODE
#include <xobject.hpp>
#else
#include <pobject/xobject.hpp>
#endif

using namespace pobject;
using namespace std;

class User;

class UserRole : public XMixParam
{
public:
	enum Role {
		ADMINISTRATOR,
		REMOTE,
		MAX
	};
	typedef XInt Literal;

	UserRole() :
		XMixParam("name"),
		role("role", ADMINISTRATOR)
	{
		addParam(&role);
	}

	UserRole(const string &pname) :
		XMixParam(pname),
		role("role", ADMINISTRATOR)
	{
		addParam(&role);
	}
	void set_type(Literal _role)
	{
		role = _role;
	}
	Literal get_type() const
	{
		return role.get_value();
	}
	XParam *getTypeParam()
	{
		return (XParam*) (&role);
	}
	string value() const
	{
		return role.value();
	}
	void set_role(const int _role)
	{
		role = _role;
	}
	User *newT() throw (Exception);
public:
	static const string	typeString[MAX];
private:
	XEnumParam<UserRole>	role;
};

class User : public XObject<UserRole>
{
public:
	typedef	UserRole 			Type;
	typedef XObjectList<Type>::iterator 	iterator;
	User() :
		_XObject("user"),
		username("username"),
		password("password")
	{
		addParam(&username);
		addParam(&password);

		password.set_runtime();
	}
	User(const string &pname) :
		_XObject(pname),
		username("username"),
		password("password")
	{
		addParam(&username);
		addParam(&password);

		password.set_runtime();
	}
	virtual void type(Type &_type) const
	{ } 

	string get_username() const
	{
		return username.value();
	}
	void set_username(const string _username)
	{
		username = _username;
	}
	void set_password(const string _password)
	{
		password = _password;
		password.encrypt_md5();
	}
	string get_password() const
	{
		return password.value();
	}
	void set_iterator(iterator _iter)
	{	
		iter = _iter;
	}
	void set_iterator_role(string _role)
	{
		role = _role;
	}
	string get_iterator_role()
	{
		return role;
	}
	virtual void _add()
	{ }
	virtual void _mod(_XObject *xo)
	{ }
	void _del()
	{
		for (c_iterator iter = cList.begin(); 
				iter != cList.end(); ++iter) {
			if (iter->oside == get_this_iter()){
				disconnect(iter);
			}
		}
	}
	void assignHelper(const XParam &xp) 
	{
		this->iter = ((User*) &xp)->iter;
	}
	virtual bool operator==(const _XObject &lvalue) const
	{
		return false;
       	}
	XObjectNotify notify(XObjectNotify nt, const _XObject *xo)
	{
		return OBJ_NOTIFY_NONE;
	}
	void disconnectNotice(const _XObjectConnection &c)
	{
		XObjectNotifier xoNotify((_XObject *)(*c.oside), OBJ_NOTIFY_NONE);
	}
	void connectNotice(const _XObjectConnection &c)
	{
		notify(OBJ_NOTIFY_NONE,(_XObject *)(*c.oside));
       	}
	bool mayConnect(_XObjectConnection &c)
	{
		if(c.type == _XObjectConnection::STRONG) {
			return false;
		} else {
			return true;
		}
	}
protected:
	iterator	iter;
private:
	XTextParam	username;
	CryptoParam	password;
	string		role;
};

class Administrator : public User
{
public:
	Administrator() :
		legalMAC("legal_mac")
	{
		addParam(&legalMAC);

		set_type(UserRole::ADMINISTRATOR);
	}
	void type(Type &_type) const
	{
		_type.set_role(UserRole::ADMINISTRATOR);
	}
	void set_legalMAC(const string mac)
	{
		legalMAC = mac;
	}
	string get_legalMAC() const
	{
		return legalMAC.value();
	}
	void _add()
	{
		_XObjectConnection fromc;
		_XObjectConnection toc;

		fromc.name = toc.name = "admin_user";
		toc.role = get_iterator_role();
		fromc.role = get_type_string();
		fromc.type = _XObjectConnection::WEAK;
		fromc.oside = iter;
		if(! connect(fromc, toc)){
			cout << "can not connect" << endl;
		} else {
			cout << fromc.xml() << endl;
			cout << toc.xml() << endl;
		}
	}
	void _mod(_XObject *xo)
	{
		Administrator* _admin = (Administrator*)(xo);
		this->set_username(_admin->get_username());
		this->set_password(_admin->get_password());
		this->set_legalMAC(_admin->get_legalMAC());
	}
	bool operator==(const _XObject &lvalue) const
	{
		const Administrator* _admin = 
			dynamic_cast<const Administrator*>(&lvalue);
		if(get_username() == _admin->get_username() &&
				get_password() == _admin->get_password() &&
				get_legalMAC() == _admin->get_legalMAC()) {
			return true;
		} else {
			return false;
		}
	}

private:
	MACAddressParam	legalMAC;
};

class RemoteUser : public User
{
public:
	RemoteUser() :
		domain("domain"),
		legalIPList("legal_ip_list")
	{
		addParam(&domain);
		addParam(&legalIPList);

		set_type(UserRole::REMOTE);
	}
	void type(Type &_type) const
	{
		_type.set_role(UserRole::REMOTE);
	}
	void set_domain(const string _domain)
	{
		domain = _domain;
	}
	string get_domain() const
	{
		return domain.value();
	}
	void add_legalIPList(const string ip)
	{
		IPxParam	ipx("ip");

		ipx = ip;
		legalIPList.addT(ipx);
	}
	string get_legalIPList()
	{
		return legalIPList.value();
	}
	void _add()
	{
		_XObjectConnection fromc;
		_XObjectConnection toc;

		fromc.name = toc.name = "remote_user";
		toc.role = get_iterator_role();
		fromc.role = get_type_string();
		fromc.type = _XObjectConnection::WEAK;
		fromc.oside = iter;
		if(! connect(fromc, toc)){
			cout << "can not connect" << endl;
		} else {
			cout << fromc.xml() << endl;
			cout << toc.xml() << endl;
		}
	}
	void _mod(_XObject *xo)
	{
		RemoteUser* _remote = (RemoteUser*)(xo);
		this->set_username(_remote->get_username());
		this->set_password(_remote->get_password());
		this->set_domain(_remote->get_domain());
		this->add_legalIPList(_remote->get_legalIPList());
	}
	bool operator==(const _XObject &lvalue) const
	{
		const RemoteUser* _remote = 
			dynamic_cast<const RemoteUser*>(&lvalue);
		if(get_username() == _remote->get_username() &&
				get_password() == _remote->get_password() &&
				get_domain() == _remote->get_domain()){
			return true;
		} else {
			return false;
		}
	}
private:
	XTextParam	domain;
	IPxList		legalIPList;
};
