//
//  login.cpp
//  bank management system
//
//  Created by Amin Amjadi on 3/29/16.
//  Copyright © 2016 AIT. All rights reserved.
//

#include <string.h>
#include <iostream>
#include <fstream>
#include "log.hpp"
#include <iomanip>

using namespace std;

int log::ct=0;

bool log::isAcc(log *acc[], char* usern)
{
    user us;
    for (int i=0; i<6; ++i) {
        if (strcmp(acc[i]->username,usern)==0) {
            return true;
        }
    }
    if (ID>6) {
        ifstream in;
        in.open("log.dat", ios::binary);
        if (!in) {
            return false;
        }
        while (in.read(reinterpret_cast<char *>(&us), sizeof(user))) {
            if (strcmp(us.username,usern)==0) {
                in.close();
                return true;
            }
        }
    }
    
    return false;
}

void admin::add_user(log *acc[])
{
    char name[50],usern[30],pass[20];
    cin.ignore();
    cout<<"\nPlease enter the name of the user: ";
    cin.getline(name, 50);
    cout<<"\nPlease enter the username(In capital letters): ";
    cin.getline(usern, 30);
    if ((isAcc(acc,usern))) {
        cout<<"\nAccount with this username has already been registered\n Please press enter two times"<<std::endl;
    }
    else{
        cout<<"\nPlease enter your password:";
        cin.getline(pass, 20);
        user(name,usern,pass);
        cout<<"\n\n\nAccount Created...";
    }
}

void log::set_user_pass( char* name,  char* usern, char* pass)
{
    ID=++ct;
    if (ID<=6) {
        strcpy(this->name,name);
        strcpy(this->username,usern);
        strcpy(this->pass,pass);
    }
    else if (ID>6) {
        user us;
        strcpy(us.name,name);
        strcpy(us.username,usern);
        strcpy(us.pass,pass);
        us.ID=ID;
        ofstream out;
        out.open("log.dat", ios::binary | ios::app);
        out.write(reinterpret_cast<char *>(&us), sizeof(user));
        out.close();
    }
}

void admin::remove_user(log *acc[])
{
    user us;
    char usern[50];
    cin.ignore();
    cout<<"\nPlease enter the username of the account you want to remove(In capital letters):";
    cin.getline(usern, 50);
    if (!(isAcc(acc,usern))) {
        cout<<"\nAccount with this username doesn't exist\n  Please press enter two times"<<std::endl;
    }
    else{
        int a= getID(acc, usern);
        ofstream out;
        ifstream in;
        in.open("log.dat", ios::binary);
        if (!in) {
            cout<<"File could not be open !! Press any Key...";
            return;
        }
        out.open("Templ.dat", ios::binary | ios::app);
        in.clear();
        in.seekg(0, ios::beg);
        while (in.read(reinterpret_cast<char *>(&us), sizeof(user))) {
            if(strcmp(us.username,usern)==0) {
                if (getID(acc, us.username)<a) {
                    out.write(reinterpret_cast<char *>(&us), sizeof(user));
                }
                else if (getID(acc, us.username)>a) {
                    us.setID(us, (getID(acc, us.username)-1));
                    out.write(reinterpret_cast<char *>(&us), sizeof(user));
                }
                
            }
        }
        in.close();
        out.close();
        
        remove("log.dat");
        rename("Templ.dat","account.dat");
        cout<<"\n\n\tAccount Deleted ..";
    }
}

void admin::show_all()
{
    user us;
    ifstream in;
    in.open("log.dat", ios::binary);
    if(!in)
    {
        cout<<"File could not be open !! Press any Key...";
        return;
    }
    cout<<"\n\n\t\t\tACCOUNT HOLDER LIST\n\n";
    cout<<"===========================================\n";
    cout<<"NAME"<<setw(15);
    cout<<"USERNAME"<<setw(12);
    cout<<"PASSWORD"<<endl;
    cout<<"============================================\n";
    while(in.read(reinterpret_cast<char *> (&us), sizeof(user)))
    {
        cout<<us.name<<setw(15);
        cout<<us.username<<setw(12);
        cout<<us.pass<<endl;
    }
    in.close();
}

bool log::login(log *acc[], char* usern, char* pass)
{
    user us;
    for (int j=0; j<6; ++j) {
        if (strcmp(acc[j]->username,usern)==0 && strcmp(acc[j]->pass,pass)==0) {
            return true;
        }
    }
    
    ifstream in;
    if (ID>6) {
        if (!in) {
            return false;
        }
        in.open("log.dat", ios::binary);
        while (in.read(reinterpret_cast<char *>(&us), sizeof(user))) {
            if (strcmp(us.username,usern)==0 && strcmp(us.pass,pass)==0) {
                in.close();
                return true;
            }
        }
    }
    return false;
}

char* log::getname(log *acc[], char* usern)
{
    user us;
    for (int j=0; j<6; ++j) {
        if (strcmp(acc[j]->username,usern)==0) {
            return acc[j]->name;
        }
    }
    ifstream in;
    in.open("log.dat", ios::binary);
    if (!in) {
        return NULL;
    }
    while (in.read(reinterpret_cast<char *>(&us), sizeof(user))) {
        if (strcmp(us.username,usern)==0) {
            in.close();
            return us.name;
        }
    }
    return NULL;
}

int log::getID(log *acc[],char* usern)
{
    user us;
    for (int j=0; j<6; ++j) {
        if (strcmp(acc[j]->username,usern)==0) {
            return acc[j]->ID;
        }
    }
    ifstream in;
    in.open("log.dat", ios::binary);
    if (!in) {
        cout<<"File could not be open !! Press any Key...";
        return false;
    }
    while (in.read(reinterpret_cast<char *>(&us), sizeof(user))) {
        if (strcmp(us.username,usern)==0) {
            in.close();
            return us.ID;
        }
    }
    return NULL;
}

int log::setID(log a,int i)
{
    return a.ID=i;
}

bool log::access(log *acc[],int id)
{
    if (id<6) {
        return acc[id]->type();
    }
    else{
        return false;
    }
}

