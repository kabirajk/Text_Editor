
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
		int userindex = 0,notfound=0;
		for (userindex; userindex < userListArray.userdatabase_size(); userindex += 1)
		{
			const userdata::User& currentuser = userListArray.userdatabase(userindex);
			//std::cout << userListArray.userdatabase_size() <<(username==currentuser.name())<<( password==currentuser.password())<<std::endl;
			if (currentuser.name() == username)
			{//try to impelent for email
				if (currentuser.password() == password) 
				{
					std::cout << "Matched Welcome" << currentuser.name() << std::endl;;
					//passsfun(currentuser.name());

					auto text=TextEditor(currentuser.name());
					system("cls");
					std::cout << "logged out" << std::endl;
					notfound = 0;
					break;

				}
				else { std::cout << "Mismatch " << std::endl; notfound = 0; }
			}
			else { notfound = 1; }
			
		}
		if (userListArray.userdatabase_size() == 0) signUp();
		else if(notfound==1)
		{
			std::cout << "User name not match" << std::endl;
			signUp();
		}

	}
	std::string CheckPassword(std::string password)
	{	
		try
		{	
			if (password.length() < 6)
				throw "Password needs more than 6 char";

		}
		catch (char* c)
		{
			std::cout << c << "  " << "Enter [Password]";
			std::cin >> password;
			password=CheckPassword(password);
		}
		return password;
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
		std::cout << "[Password] !more than 6 : ";
		std::cin >> password;
		password = CheckPassword(password);
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
		int start = 0, end = password.length() - 1;
		while (start <= end)
		{
			char temp = password[start];
			password[start] = password[end];
			password[end] = temp;
			start++;
			end--;
		}
		return password;
	}

	~UserPortal()
	{
		std::fstream boutObject("UserData.bin", std::ios::out| std::ios::trunc | std::ios::binary);
		if (!boutObject.is_open()) { std::cout << "unable to open user *.bin file" << std::endl; }
		else if (!userListArray.SerializePartialToOstream(&boutObject)) { std::cout << "unable to write data !data lost" << std::endl;}
	}


};