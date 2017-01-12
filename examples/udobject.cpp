#include <device.hpp>
#include <user.hpp>

const string    UserRole::typeString[MAX] = {
	"administrator",
	"remote"
};


const string	DeviceType::typeString[MAX] = {
	"server",
	"pc",
	"laptop",
	"vm"
};


User *UserRole::newT() throw (Exception)
{
	if (role.get_value() == ADMINISTRATOR)
		return new Administrator;
	if (role.get_value() == REMOTE)
		return new RemoteUser;

	throw Exception("Undefined user", TracePoint("user"));
}

Device *DeviceType::newT() throw (Exception)
{
	if (machine.get_value() == LAPTOP)
		return new Laptop;
	if (machine.get_value() == SERVER)
		return new Server;
	if (machine.get_value() == VM)
		return new Vm;
	if (machine.get_value() == PC)
		return new Pc;

	throw Exception("Undefined machine", TracePoint("machnie"));
}


int main()
{
	Administrator admin;
	admin.set_name("admin_user");
	admin.set_username("Jafarian");
	admin.set_password("password1");
	admin.set_legalMAC("3f:4e:bc:fd:6a:8f");

	RemoteUser remote;
	remote.set_name("remote_user");
	remote.set_username("Mousavi");
	remote.set_password("password2");
	remote.set_domain("domain1");
	remote.add_legalIPList("192.168.1.1");
	remote.add_legalIPList("fe80::21b:fcff:fe1f:a136");

	Server server;
	server.set_name("server1");
	server.set_ipAddress("2001:cdba:1111:1111:1111:1111:3257:9652");
	server.set_macAddress("3f:4e:bc:fd:6b:8a");
	server.set_upTime(100);
	server.set_cpuUsage(90);
	server.set_ramUsage(80);

	Laptop laptop;
	laptop.set_name("laptop1");
	laptop.set_ipAddress("192.168.1.3");
	laptop.set_macAddress("3f:4e:bc:fd:6a:8a");
	laptop.set_upTime(21);
	laptop.set_cpuUsage(25);
	laptop.set_ramUsage(75);

	Vm vm;
	vm.set_name("PVM2");
	vm.set_ipAddress("192.168.1.4");
	vm.set_macAddress("3f:4e:bc:ad:6a:8a");
	vm.set_upTime(4);
	vm.set_cpuUsage(30);
	vm.set_ramUsage(50);

	XObjectRepository<DeviceType> xoRepMachine("repo_device", "log_device");
	XObjectRepository<DeviceType>::iterator iter1;
	xoRepMachine.regObjList(1, "machine_list");
	iter1 = xoRepMachine.loadObj(1, &server, false);
	laptop.set_iterator(iter1);
	laptop.set_iterator_role(server.get_type_string());
	vm.set_iterator(iter1);
	vm.set_iterator_role(server.get_type_string());
	iter1 = xoRepMachine.add(1, &laptop, false);
	admin.set_iterator(iter1);
	admin.set_iterator_role(laptop.get_type_string());
	iter1 = xoRepMachine.add(1, &vm, false);
	remote.set_iterator(iter1);
	remote.set_iterator_role(vm.get_type_string());

	XObjectRepository<UserRole> xoRepUser("repo_user", "log_user");
	XObjectRepository<UserRole>::iterator iter2;
	xoRepUser.regObjList(1, "admin_list");
	xoRepUser.regObjList(2, "remote_list");
	iter2 = xoRepUser.add(1, &admin, false);
	iter2 = xoRepUser.add(2, &remote, false);
	
	Administrator admin1;
	admin1.set_name("admin1");
	admin1.set_username("HajiMoradi");
	admin1.set_password("password3");
	admin1.set_legalMAC("3f:3e:bc:fd:6a:8f");

	if(admin.mod_prepare()) {
		admin.mod(&admin1);
	}
	remote.del();

	cout << admin.xml_connectionsList() << endl;
	cout << remote.xml_connectionsList() << endl;
	cout << server.xml_connectionsList() << endl;
	cout << laptop.xml_connectionsList() << endl;
	cout << vm.xml_connectionsList() << endl;
		
	return 0;
}
