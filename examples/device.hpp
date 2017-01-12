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

class Device;

class DeviceType : public XMixParam
{
public:
	enum Machine{
		SERVER,
		PC,
		LAPTOP,
		VM,
		MAX
	};
	typedef XInt Literal;
	DeviceType(const string &pname):
		XMixParam(pname),
		machine("machine_type", SERVER)
	{
		addParam(&machine);
	}
	DeviceType():
		XMixParam("name"),
		machine("machine_type", SERVER)
	{
		addParam(&machine);
	}

	void set_type(Literal _machine)
	{
		machine = _machine;
	}
	Literal get_type() const
	{
		return machine.get_value();
	}
	XParam *getTypeParam()
	{
		return (XParam*) (this);
	}
	string value() const
	{
		return machine.value();
	}
	void set_machine(const int _machine) 	
	{ 
        	machine = _machine; 
        }
	Device *newT() throw (Exception);
public:
	static const string	typeString[MAX];
private:
	XEnumParam<DeviceType>	machine;
};

class Device : public XObject<DeviceType>
{
public:
	typedef DeviceType 			Type;
	typedef XObjectList<Type>::iterator	iterator;
	Device():
		_XObject("machine"),
		ip("IP_Address"),
		legalMAC("MAC_Address"),
		upTime("up_time", 0, -1),
		cpuUsage("cpu_usage", 0, 100),
		ramUsage("ram_usage", 0, 100)
	{
		addParam(&ip);
		addParam(&legalMAC);
		addParam(&upTime);
		addParam(&cpuUsage);
		addParam(&ramUsage);
	}
	Device(const string &pname):
		_XObject(pname),
		ip("IP_Address"),
		legalMAC("MAC_Address"),
		upTime("up_time", 0, -1),
		cpuUsage("cpu_usage", 0, 100),
		ramUsage("ram_usage", 0, 100)
	{
		addParam(&ip);
		addParam(&legalMAC);
		addParam(&upTime);
		addParam(&cpuUsage);
		addParam(&ramUsage);
	}

	virtual void type(Type &_type) const
	{ }
	bool key(string &_key)
	{
		_key = legalMAC.value();
                return true;
        }
	void set_ipAddress(const string _ip)
	{
		ip.setAddress(_ip);
	}
	string get_ipAddress() const
	{
		return ip.getAddress();
	}
	void set_macAddress(const string _mac)
	{
		legalMAC = _mac;
	}
	string get_macAddress() const
	{
		return legalMAC.value();
	}
	void set_upTime(const XULong _time)
	{
		upTime.set_value(_time);
	}
	XULong get_upTime() const
	{
		return upTime.get_value();
	}
	void set_cpuUsage(const XFloat _cpu)
	{
		cpuUsage.set_value(_cpu);
	}
	XFloat get_cpuUsage() const
	{
		return cpuUsage.get_value();
	}
	void set_ramUsage(const XFloat _ram)
	{
		ramUsage.set_value(_ram);
	}
	XFloat get_ramUsage() const
	{
		return ramUsage.get_value();
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
	void assignHelper(const XParam &xp)
	{
		this->iter = ((Device*) &xp)->iter;
        }
	bool operator==(const _XObject &lvalue) const
	{
		const Device* _device = 
			dynamic_cast<const Device*>(&lvalue);
		if(get_ipAddress() == _device->get_ipAddress() &&
				get_macAddress() == 
					_device->get_macAddress() &&
				get_upTime() ==	_device->get_upTime() &&
				get_cpuUsage() == _device->get_cpuUsage() &&
				get_ramUsage() == _device->get_ramUsage()) {
			return true;
		} else {
			return false;
		}

	}
protected:
	iterator		iter;
private:
	IPxParam		ip;
	MACAddressParam 	legalMAC;
	XIntParam<XULong>	upTime;
	XIntParam<XFloat>	cpuUsage;
	XIntParam<XFloat>	ramUsage;
	string			role;
};

class Server : public Device
{
public:
	Server()
	{
		set_type(DeviceType::SERVER);
	}
	void type(Type &_type) const
	{
		_type.set_machine(DeviceType::SERVER);
        }
	void _add()
	{
		_XObjectConnection fromc;
		_XObjectConnection toc;
		fromc.name = toc.name = "device";
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
		Server* _server = (Server*)(xo);
		this->set_ipAddress(_server->get_ipAddress());
		this->set_macAddress(_server->get_macAddress());
		this->set_upTime(_server->get_upTime());
		this->set_cpuUsage(_server->get_cpuUsage());
		this->set_ramUsage(_server->get_ramUsage());
	}
};

class Pc : public Device
{
public:
	Pc()
	{
		set_type(DeviceType::PC);
	}
	void type(Type &_type) const
	{
		_type.set_machine(DeviceType::PC);
        }
	void _add()
	{
		_XObjectConnection fromc;
		_XObjectConnection toc;
		fromc.name = toc.name = "device";
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
		Pc* _pc = (Pc*)(xo);
		this->set_ipAddress(_pc->get_ipAddress());
		this->set_macAddress(_pc->get_macAddress());
		this->set_upTime(_pc->get_upTime());
		this->set_cpuUsage(_pc->get_cpuUsage());
		this->set_ramUsage(_pc->get_ramUsage());
	}
};

class Laptop : public Device
{
public:
	Laptop()
	{
		set_type(DeviceType::LAPTOP);
	}
	void type(Type &_type) const
	{
		_type.set_machine(DeviceType::LAPTOP);
        }
	void _add()
	{
		_XObjectConnection fromc;
		_XObjectConnection toc;
		fromc.name = toc.name = "device";
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
		Laptop* _laptop = (Laptop*)(xo);
		this->set_ipAddress(_laptop->get_ipAddress());
		this->set_macAddress(_laptop->get_macAddress());
		this->set_upTime(_laptop->get_upTime());
		this->set_cpuUsage(_laptop->get_cpuUsage());
		this->set_ramUsage(_laptop->get_ramUsage());
	}
};

class Vm : public Device
{
public:
	Vm()
	{
		set_type(DeviceType::VM);
	}
	void type(Type &_type) const
	{
		_type.set_machine(DeviceType::VM);
        }
	void _add()
	{
		_XObjectConnection fromc;
		_XObjectConnection toc;
		fromc.name = toc.name = "device";
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
		Vm* _vm = (Vm*)(xo);
		this->set_ipAddress(_vm->get_ipAddress());
		this->set_macAddress(_vm->get_macAddress());
		this->set_upTime(_vm->get_upTime());
		this->set_cpuUsage(_vm->get_cpuUsage());
		this->set_ramUsage(_vm->get_ramUsage());
	}
};
