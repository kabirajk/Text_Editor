// Text_Editor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include "User.pb.h"

//for user input 
void promtforuser(userdata::User * person)
{
    std::string name,email;
    std::cout << "enter the name: ";
    std::cin >> name;
    person->set_name(name);
    std::cout << "enter the email: ";
    std::cin >> email;
    person->set_email(email);
    std::string password;
    std::cout << "enter the password: ";
    std::cin >> password;
    person->set_password(password);
    int id;
    std::cout << "enter the id: ";
    std::cin >> id;
    person->set_id(id);
    std::string location;
    std::cout << "enter the location: ";
    std::cin >> location;
    person->set_location(location);
    std::string address;
    std::cout << "enter the Address: ";
    std::cin >> address;
    person->set_address(address);
    std::string phonenumber;
    std::cout << "enter the phonenumber: ";
    std::cin >> phonenumber;
    person->set_phonenumber(phonenumber);


}


//for printing the every serialised value
void print_serialized_object(userdata::Userlist& listobj)
{
    for (int userindex = 0; userindex < listobj.userdatabase_size(); userindex += 1)
    {
       //inline function returns as constant 
        std::cout<< "---------------------------"<<std::endl;
       const userdata::User& indiviudal = listobj.userdatabase(userindex);
       std::cout <<"Name:" << indiviudal.name() << std::endl;
       std::cout << "Email:" << indiviudal.email() << std::endl;
       std::cout << "Id:" << indiviudal.id() << std::endl;
    }
}

int main()
{ //namespace|userdata|obj var
    userdata::Userlist user_list;
    //opening as binary 
    std::fstream file("user.bin",std::ios::in|std::ios::binary);
    if (!file.is_open()) { std::cout << "file not found"; }
    else if (!(user_list.ParseFromIstream(&file))) { std::cout << "cant phrase"; return -1; 
    promtforuser(user_list.add_userdatabase());
    user_list.set_usercount(user_list.usercount() + 1);
    std::cout << user_list.usercount();
    print_serialized_object(user_list);

    std::fstream writefile("user.bin", std::ios::out | std::ios::trunc | std::ios::binary);
    if (writefile.is_open()) { std::cout << "file present"; }
    if (!user_list.SerializeToOstream(&writefile)) { std::cout << "cant write"; return -1; }
    std::cout << "file writed sucessfully"<<std::endl;
    return 0;
}