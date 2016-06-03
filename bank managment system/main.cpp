//
//  main.cpp
//  bank management system
//
//  Created by Amin Amjadi on 3/29/16.
//  Copyright © 2016 AIT. All rights reserved.
//

#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include<fstream>
#include "log.hpp"
#include "account.hpp"

using namespace std;

void login(log *[]); //function to call Login switch case

void start()
{
    cout<<"\n\n\t   BANK";
    cout<<"\n\tMANAGEMENT";
    cout<<"\n\t  SYSTEM\n\n";
    cin.get();
}

int main()
{
    //remove("log.dat");
    //remove("account.dat");
    start();
    log call; //this null object is to just able us to call functions of header log
    log* acc[6]; //array of accounts with default usernames and passwords
    acc[0]=new admin("Amin","AMIN","123");
    acc[1]=new admin("Amjadi","AIT","0000");
    acc[2]=new user("HotsonHor","1","001");
    acc[3]=new user("Ali","2","002");
    acc[4]=new user("Pinki","3","003");
    acc[5]=new user("Amra","4","004");
    
    
    char *user,*pass;
    char a,b;
    int i(1),id,x=0,y=0;
    
    while (i) {
        i=0;
        char *tempu=NULL;
        delete tempu;
        tempu=new char[50];
        cout<<"Please enter your username(In capital letters):";
        y=0;
        a='\0';
        while (a!='\n') {
            scanf("%c",&a);
            y++;
            if (a!='\n') {  //scanning until the new line
                tempu[y-1]=a;
            }
        }
        user=new char[y];  //give user size as much character as we have untill new line
        strcpy(user, tempu);
        
        char *tempp=NULL;
        delete tempp;
        tempp=new char[50];
        cout<<"Please enter your password:";
        y=0;
        b='\0';
        while (b!='\n') {
            scanf("%c",&b);
            y++;
            if (b!='\n') {
                tempp[y-1]=b;
            }
        }
        pass=new char[y];
        strcpy(pass, tempp);  //same for pass
        if (call.login(acc,user,pass)) {  // checking if the username & password that we got from user is in log or not
            x=0;
            cout<<"\n\nWelcome, "<<call.getname(acc, user)<<endl; //call the name of the user
            id=(call.getID(acc, user))-1; //makes id equal to ID of the user minus one
            account a; //to be able to call the funtions of header account
            char ch;
            long int num;
            do
            {
                
                cout<<"\n\n\tMAIN MENU";
                cout<<"\n\n\tA. NEW ACCOUNT";
                cout<<"\n\n\tB. DEPOSIT AMOUNT";
                cout<<"\n\n\tC. WITHDRAW AMOUNT";
                cout<<"\n\n\tD. BALANCE ENQUIRY";
                cout<<"\n\n\tE. ALL ACCOUNT HOLDER LIST";
                cout<<"\n\n\tF. CLOSE AN ACCOUNT";
                cout<<"\n\n\tG. MODIFY AN ACCOUNT";
                cout<<"\n\n\tH. LOGIN MENU";
                cout<<"\n\n\tI. SIGN OUT";
                cout<<"\n\n\tJ. EXIT";
                cout<<"\n\n\ttype Your Option (A-K) ";
                cin>>ch;
                ch=toupper(ch); //makes ch uppercase form
                
                switch(ch)
                {
                    case 'A':
                        a.create_account();
                        break;
                    case 'B':
                        cout<<"\n\n\tEnter The account No. : "; cin>>num;
                        a.drawal_depos(2, num);
                        break;
                    case 'C':
                        cout<<"\n\n\tEnter The account No. : "; cin>>num;
                        a.drawal_depos(1, num);
                        break;
                    case 'D':
                        cout<<"\n\n\tEnter The account No. : "; cin>>num;
                        a.display_acc(num);
                        break;
                    case 'E':
                        if (call.access(acc, id)) {  //check the type of acc
                            cout<<"\nPlease enter your password:";
                            cin>>pass;
                            if (call.login(acc,user,pass)) { //check the new password with the previous username
                                a.display_all();
                            }
                        }
                        else
                            cout<< "\nUser can't have access to this part\n"<<endl;
                        break;
                    case 'F':
                        if (call.access(acc, id)) {  //same
                            cout<<"\nPlease enter your password:";
                            cin>>pass;
                            if (call.login(acc,user,pass)) {
                            cout<<"\n\n\tEnter The account No. : "; cin>>num;
                                if (a.delete_acc(num)) {
                                    cout<<"\n\n\tRecord Deleted...";
                                }
                            }
                        }
                        else
                            cout<< "\nUser can't have access to this part\n"<<endl;
                        break;
                    case 'G':
                        if (call.access(acc, id)) {
                            cout<<"\n\n\tEnter The account No. : "; cin>>num;
                            a.modify_acc(num);
                        }
                        else
                            cout<< "\nUser can't have access to this part\n"<<endl;
                        break;
                    case 'H':
                        if (call.access(acc, id)) {
                            cout<<"\nPlease enter your password:";
                            cin>>pass;
                            if (call.login(acc,user,pass)) {
                            login(acc);
                            }
                        }
                        else
                            cout<< "\nUser can't have access to this part\n"<<endl;
                        break;
                    case 'I':
                        cout<<"\n\n\tYou have been signed out.\n\n\n";
                        i=1;
                        break;
                    case 'J':
                        cout<<"\n\n\tThanks for using bank management system";
                        break;
                    default :cout<<"\n\tCommand not found!";
                }
                cin.ignore();  //delete the garbage that stays in buffer from cin
                cin.get();  //wait for pressing any button
            }while(ch!='I' && ch!='J');
        }
        
        else if(x<3) {  //we can enter the wrong user or pass for just 3 times
            ++x;
            cout<<"\n\n\tYour username or password was incorrect\n \t\t\t\t"<<(4-x)<<" attempt(s) left\n\n\n"<<endl;
            i=1;
        }
    }
    
    return 0;
}

void login(log *ac[])
{
    admin call;
    char c;
    do
    {
        cout<<"\n\n\n\tLOGIN MENU";
        cout<<"\n\n\tA. ADD TEMP USER";
        cout<<"\n\n\tB. REMOVE  TEMP USER";
        cout<<"\n\n\tC. SHOW ALL TEMP USERS";
        cout<<"\n\n\tD. GO BACK TO MAIN MENU";
        cout<<"\n\n\tType Your Option (A-D) ";
        cin>>c;
        c=toupper(c);
        
        switch (c) {
            case 'A':
                call.add_user(ac);
                break;
            case 'B':
                call.remove_user(ac);
                break;
            case 'C':
                call.show_all();
                break;
            case 'D':
                break;
                
            default:cout<<"\n\tCommand not found!";
        }
        cin.ignore();
    }while(c!='D');
}





