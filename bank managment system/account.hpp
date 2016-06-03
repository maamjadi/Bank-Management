//
//  account.hpp
//  bank management system
//
//  Created by Amin Amjadi on 3/29/16.
//  Copyright © 2016 AIT. All rights reserved.
//

#ifndef account_hpp
#define account_hpp

#include <stdio.h>

class account
{
    long int acno;
    char name[50];
    long int deposit;
    char currency;
    char type;
public:
    void create_account();	//function to get data from user
    bool acno_exits(long x); //to check that  whether we have the given acno or not
    void show_account() const;	//function to display data on screen
    void modify();	//function to change data
    void setdepos(long int);	//function to get amount then add it to balance amount
    void setdrawal(long int);	//function to get amount then subtract it from balance amount
    void report() const;	//function to show data in one line
    long int getacno() const;	//function to return account number
    long int getdeposit() const;	//function to return balance amount
    char gettype() const;	//function to return type of account
    void write_to_file();  //function to save the data to the file
    void write_to_ftemp(); //write to temporary file
    void display_all();  //function to show data from file
    bool delete_acc(long int);  //function to delete data from file
    void display_acc(long int);  //function to show specific account from file
    void modify_acc(long int);  //function to change specific account from file
    void drawal_depos(int, long int);  //function to 
};



#endif /* account_hpp */
