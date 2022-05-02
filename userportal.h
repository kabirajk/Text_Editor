
class UserPortal{
	//user data base from proto gen header
//	namespace//array of users//object holding the list of array
	userdata::Userlist userListArray;
	int userUniqueCount = 0;

public:
	UserPortal()
	{	//prasing data from bin file using fstream
		std::fstream binObject("UserData.bin", std::ios::in | std::ios::binary);
		if (!binObject.is_open())
		{
			std::cout << "user *.bin file not found creating a new file" << std::endl;
		}
		else if (!(userListArray.ParseFromIstream(&binObject)))
		{
			std::cout << "error while prasing *.bin file" << std::endl;
		}
		userUniqueCount= userListArray.usercount();
		//std::cout << userUniqueCount << userListArray.usercount() << std::endl;
	}
	void logIn()
	{
		std::string username, password;
		std::cout << "Login \n [Username]: ";
		std::cin >> username;
		std::cout << "[Password]: ";
		std::cin >> password;
		password = encryptPassword(password);
		for (int userindex = 0; userindex < userListArray.userdatabase_size(); userindex += 1)
		{
			const userdata::User& currentuser = userListArray.userdatabase(userindex);
			//const userdata::User* userpr = &currentuser;
			//std::cout << userListArray.userdatabase_size() <<(username==currentuser.name())<<( password==currentuser.password())<<std::endl;
			if (currentuser.name() == username)
			{//try to impelent for email
				if (currentuser.password() == password) 
				{
					std::cout << "Matched Welcome" << currentuser.name() << std::endl;;
					//passsfun(currentuser.name());
					auto text=TextEditor(currentuser.name());
					std::cout << "logged out" << std::endl;
					break;
				}
				else { std::cout << "Mismatch " << std::endl; }
			}
			else
			{
				std::cout << "User name not match" << std::endl;
				signUp();
			}
		}
		if (userUniqueCount == 0) signUp();

	}

	void signUp()
	{
		userdata::User* newUser = userListArray.add_userdatabase();
		std::cout << "Sign Up" << std::endl;
		std::string name;
		std::cout << "[Name]: ";
		std::cin >> name;
		newUser->set_name(name);

		std::string  email;
		std::cout << "[Email]: ";
		std::cin >> email;
		newUser->set_email(email);
		
		std::string password;
		std::cout << "[Password]: ";
		std::cin >> password;
		password = encryptPassword(password);
		newUser->set_password(password);
		
		std::string location;
		std::cout << "[Location]: ";
		std::cin >> location;
		newUser->set_location(location);
		
		std::string address;
		std::cout << "[Address]: ";
		std::cin >> address;
		newUser->set_address(address);
		
		std::string phonenumber;
		std::cout << "[Phonenumber]: ";
		std::cin >> phonenumber;
		newUser->set_phonenumber(phonenumber);
		
		newUser->set_id(userUniqueCount += 1);
		//std::cout << name << email << password << location << address << phonenumber << std::endl;
		std::cout << "Unique id is [" << userUniqueCount << "] SignIn Sucessfull" << std::endl;
		userListArray.set_usercount(userListArray.userdatabase_size());
	}

	std::string encryptPassword(std::string password)
	{
		//logic to get encypt
		return password;
	}

	~UserPortal()
	{
		std::fstream boutObject("UserData.bin", std::ios::out| std::ios::trunc | std::ios::binary);
		if (!boutObject.is_open()) { std::cout << "unable to open user *.bin file" << std::endl; }
		else if (!userListArray.SerializePartialToOstream(&boutObject)) { std::cout << "unable to write data !data lost" << std::endl;}
	}


};