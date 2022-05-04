#include <iostream>
#include <conio.h>
#include <fstream>
#include <ctime>
#include <stdio.h>

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
		std::cout << "1 => SignUp 2 => Login 3 => Exit" << std::endl;
		std::cin >> option;
		std::cin.ignore();
		if(option == 1) user.signUp();
		if(option ==2) user.logIn();
		if (option == 3) break;
	}
	
	return 0;
};