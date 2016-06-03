//
//  login.hpp
//  bank management system
//
//  Created by Amin Amjadi on 3/29/16.
//  Copyright © 2016 AIT. All rights reserved.
//

#ifndef login_hpp
#define login_hpp

#include <stdio.h>
#include <string.h>

class log //polymorphism
{
private:
    int ID;
    static int ct; //counter for counting the new ID for new acc
    char username[50];
    char pass[30];
    char name[50];
public:
    log():ID(0){}; //default constructor
    bool isAcc(log*[], char*); //this funtion is just for checking if the account with the specific username exists or not
    bool login(log*[], char*, char*); //check user and pass
    void set_user_pass( char*, char*, char*); //funtion to make object... by receiving name,user,pass
    char* getname(log*[], char*); //funtion to return the name of the acc by getting username
    int getID(log*[], char*);  //returning the ID of user
    virtual bool type(){return 0;};  //virtual function (because we need to have object of this class to call the functions)
    friend class admin; //admin has access to everything in log because has access to do everything
    bool access(log*[],int); //for checking and returning the type of the acc
    int setID(log,int);  //for set the ID of acc to the number that we receive
};

class user: public log
{
public:
    user() //default constructor
    {
        log();
    }
    
    user( char* a, char* b, char* c) //constructor
    {
        set_user_pass(a, b, c);
    };
    bool type() //type of objects of user are false
    {
        return false;
    }
};

class admin: public log
{
public:
    admin() //default constructor
    {
        log();
    }
    
    admin( char* a, char* b, char* c) //constructor
    {
        set_user_pass(a, b, c);
    }
    bool type() //type of objects of admin are true
    {
        return true;
    }
    void remove_user(log*[]); //function for removing user
    void add_user(log*[]); //function for adding user
    void show_all(); //for showing all of the accounts
};

#endif /* login_hpp */
