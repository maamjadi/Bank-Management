//
//  account.cpp
//  bank management system
//
//  Created by Amin Amjadi on 3/29/16.
//  Copyright © 2016 AIT. All rights reserved.
//

#include "account.hpp"
#include <string.h>
#include <iostream>
#include <iomanip>

using namespace std;

void account::create_account()
{
    cout<<"\nEnter The account No. (It must be 6 digit) :";
    cin.ignore();
    if (cin>>acno)
    {// the user input a valid integer, process it
        while (!(100000<=acno && acno<1000000) || acno_exits(acno)) {
            
            if (!(100000<=acno && acno<1000000)) { //if the account number is less or more than 6 digits scan it again
                cout<<"\nEnter The account No. with 6 digit! :";
                cin>>acno;
                cin.ignore();
            }
            else if (acno_exits(acno)) { //if the Account number exits
                cout<<"\nThis Account Number exits, Please type different Account number : ";
                cin>>acno;
                cin.ignore();
            }
        }
    }
    else
    {
        // the user didn't enter a valid integer
        // now you probably want to consume the rest of the input until newline and
        // re-prompt the user
        cin.clear(); // clears the fail bit
        cin.ignore();
        cout<<"\nCreating Account Failed! ";
        return;
    }
    

    cout<<"\n\nEnter The Name of The account Holder : ";
    cin.ignore();
    cin.getline(name,50); //get name with the size of 50
    cout<<"\nEnter Currency of The account (€/$) : ";
    cin>>currency;
    cin.ignore();
    currency=toupper(currency); //write this for the case that we get lowercase letter to change it to upper case
    while (currency!='S' && currency!='C') {
        cout<<"\nCurrency has to be Either $ or € !";
        cout<<"\nFor € press C";
        cout<<"\nFor $ press S";
        cout<<"\nPlease try again : ";
        cin>>currency;
        cin.ignore();
        currency=toupper(currency);
    }
    cout<<"\nEnter Type of the account(G:GOLD,S:Silver,B:Bronze) : ";
    cin>>type;
    cin.ignore();
    type=toupper(type); //change to upper case
    while (type!='G' && type!='S' && type!='B') {
        cout<<"\ntype has to be either G:GOLD or S:Silver or B:Bronze!";
        cout<<"\nPlease try again : ";
        cin>>type;
        cin.ignore();
        type=toupper(type);
    }
    if (type=='G') { //condition of G accounts
        cout<<"\nEnter The Initial amount(>=500 for Saving and <=10000 for current ) : ";
        cin>>deposit;
        cin.ignore();
        while (!(500<=deposit && deposit<=10000)) {
            cout<<"\nPlease Enter The amount between 500 and 10000 for current! : ";
            cin>>deposit;
            cin.ignore();
        }
    }
    else if (type=='S') {//condition of S accounts
        cout<<"\nEnter The Initial amount(>=500 for Saving and <=5000 for current ) : ";
        cin>>deposit;
        cin.ignore();
        while (!(500<=deposit && deposit<=5000)) {
            cout<<"\nPlease Enter The amount between 500 and 5000 for current! : ";
            cin>>deposit;
            cin.ignore();
        }
    }
    else if (type=='B'){//condition of B accounts
        cout<<"\nEnter The Initial amount(>=500 for Saving and <=1000 for current ) : ";
        cin>>deposit;
        cin.ignore();
        while (!(500<=deposit && deposit<=1000)) {
            cout<<"\nPlease Enter The amount between 500 and 1000 for current! : ";
            cin>>deposit;
            cin.ignore();
        }
    }

    write_to_file(); //call write to file function from account_fn source
    cout<<"\n\n\nAccount Created...";
}

void account::show_account() const
{
    cout<<"\n====================================";
    cout<<"\nAccount No. : "<<acno;
    cout<<"\nAccount Holder : "<<name;
    cout<<"\nCurrency : "<<currency;
    cout<<"\nBalance amount : "<<deposit;
    cout<<"\nType of Account : "<<type;
    cout<<"\n====================================";
}

void account::setdepos(long int x)
{
    this->deposit+=x;
}

void account::setdrawal(long int x)
{
    this->deposit-=x;
}

void account::report() const
{
    cout<<acno<<setw(14)<<name<<setw(15);
    if (type=='G') {
        cout<<"GOLD"<<setw(12);
    }
    else if (type=='S') {
        cout<<"Silver"<<setw(11);
    }
    else if (type=='B'){
     cout<<"Bronze"<<setw(11);
    }
    cout<<deposit<<setw(11)<<currency<<endl;
}

void account::modify()
{
    cout<<"\nAccount No. : "<<acno;
    cout<<"\nModify Account Holder Name : ";
    cin.clear();
    cin.ignore();
    cin.getline(name,50);
    cout<<"\nModify Type of Account(G:GOLD,S:Silver,B:Bronze) : ";
    cin>>type;
    cin.ignore();
    type=toupper(type);
    while (type!='G' && type!='S' && type!='B') {
        cout<<"\ntype has to be either G:GOLD or S:Silver or B:Bronze!";
        cout<<"\nPlease try again : ";
        cin>>type;
        cin.ignore();
        type=toupper(type);
    }
    if (type=='G') { //condition of G accounts
        cout<<"\nModify Balance amount(>=500 for Saving and <=10000 for current ) : ";
        cin>>deposit;
        cin.ignore();
        while (!(500<=deposit && deposit<=10000)) {
            cout<<"\nPlease Enter The amount between 500 and 10000! : ";
            cin>>deposit;
            cin.ignore();
        }
    }
    else if (type=='S') {//condition of S accounts
        cout<<"\nModify Balance amount(>=500 for Saving and <=5000 for current ) : ";
        cin>>deposit;
        cin.ignore();
        while (!(500<=deposit && deposit<=5000)) {
            cout<<"\nPlease Enter The amount between 500 and 5000! : ";
            cin>>deposit;
            cin.ignore();
        }
    }
    else if (type=='B'){//condition of B accounts
        cout<<"\nModify Balance amount(>=500 for Saving and <=1000 for current ) : ";
        cin>>deposit;
        cin.ignore();
        while (!(500<=deposit && deposit<=1000)) {
            cout<<"\nPlease Enter The amount between 500 and 1000! : ";
            cin>>deposit;
            cin.ignore();
        }
    }
    
    write_to_ftemp();
}

long int account::getacno() const
{
    return this->acno;
}

long int account::getdeposit() const
{
    return this->deposit;
}

char account::gettype() const
{
    return this->type;
}



