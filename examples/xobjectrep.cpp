#include <user.hpp>
#include <device.hpp>

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

int main()
{
	XObjectRepository<UserRole> xoRep("repo_name", "repo_log");
	xoRep.regObjList(1, "list1");
	xoRep.regObjList(2, "list2");
	cout << xoRep.xml() << endl;

	return 0;
}
