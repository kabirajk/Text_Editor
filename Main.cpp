#include <iostream>
#include <conio.h>
#include <fstream>

#include "User.pb.h"
#include "textfile.pb.h"
#include "filesversion.pb.h"

#include "editor.h"
#include "filepicker.h"
#include "userportal.h"

int main()
{
	UserPortal user;
	while(1)
	{
		int option = -1;
		std::cout << "1 for signup 2 login 3 break" << std::endl;
		std::cin >> option;
		std::cin.ignore();
		if(option == 1) user.signUp();
		if(option ==2) user.logIn();
		if (option == 3) break;
	}
	//todo
	//file deletion
	//version deletion
	//account deletion

	return 0;
};