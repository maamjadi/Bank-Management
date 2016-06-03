//
//  account_fn.cpp
//  bank management system
//
//  Created by Amin Amjadi on 5/2/16.
//  Copyright © 2016 AIT. All rights reserved.
//

#include <stdio.h>
#include "account.hpp"
#include <iomanip>
#include <iostream>
#include <fstream>

using namespace std;

//all of the functions that are using file for account header

void account::write_to_file()
{
    ofstream out;
    out.open("account.dat", ios::binary | ios::app);
    out.write(reinterpret_cast<char *> (this), sizeof(account));
    out.close();
}

void account::write_to_ftemp()
{
    ofstream out;
    out.open("tmp.dat", ios::binary | ios::app);
    out.write(reinterpret_cast<char *> (this), sizeof(account));
    out.close();
}

bool account::acno_exits(long int x)
{
    account a; //we use "a" because otherwise this function would be open the last file which makes problem
    ifstream in;
    in.open("account.dat", ios::binary);
    while (in.read(reinterpret_cast<char *>(&a), sizeof(account))) {
        if (a.getacno()==x) {
            return true;
        }
    }
    in.close();
    return false;
}


void account::display_all()
{
    ifstream in;
    in.open("account.dat", ios::binary);
    if(!in)
    {
        cout<<"File could not be open !! Press any Key...";
        return;
    }
    cout<<"\n\n\t\t\tACCOUNT HOLDER LIST\n\n";
    cout<<"==========================================================\n";
    cout<<"Acc no."<<setw(14);
    cout<<"NAME"<<setw(15);
    cout<<"Type"<<setw(12);
    cout<<"Balance"<<setw(11);
    cout<<"Currency\n";
    cout<<"==========================================================\n";
    while(in.read(reinterpret_cast<char *> (this), sizeof(account)))
    {
        report();
    }
    in.close();
}


void account::display_acc(long int x)
{
    bool flag=false;
    ifstream in;
    in.open("account.dat", ios::binary);
    if (!in) {
        cout<<"File could not be open !! Press any Key...";
        return;
    }
    while (in.read(reinterpret_cast<char *>(this), sizeof(account))) {
        if (getacno()==x) {
            show_account();
            flag=true;
        }
    }
    in.close();
    if (flag==false) {
        cout<<"\n\n\tThis account doesn't exist";
    }
}


void account::modify_acc(long int x)
{
    ifstream File,tf;
    File.open("account.dat", ios::binary);
    if (!File) {
        cout<<"File could not be open !! Press any Key...";
        return;
    }
    while (File.read(reinterpret_cast<char *>(this), sizeof(account))) {
        if (getacno()==x)
        {
            show_account();
            cout<<"\n\n\tEnter The New Details of account"<<endl;
            modify();
            cout<<"\n\n\tRecord Updated...";
        }
    }
    File.close();
    delete_acc(x);
    tf.open("tmp.dat", ios::binary);
    if (!tf) {
        return;
    }
    while (tf.read(reinterpret_cast<char *>(this), sizeof(account))) {
        write_to_file();
    }
    tf.close();
    remove("tmp.dat");
    
}


bool account::delete_acc(long int x)
{
    bool flag=false;
    ofstream out;
    ifstream in;
    in.open("account.dat", ios::binary);
    if (!in) {
        cout<<"File could not be open !! Press any Key...";
        return false;
    }
    out.open("Temp.dat", ios::binary | ios::app);
    in.clear();
    in.seekg(0, ios::beg);
    while (in.read(reinterpret_cast<char *>(this), sizeof(account))) {
        if(getacno()!=x) {
            out.write(reinterpret_cast<char *>(this), sizeof(account));
        }
        else if (getacno()==x)
        {
            flag=true;
        }
    }
    in.close();
    out.close();
    if (flag==true) {
        remove("account.dat");
        rename("Temp.dat","account.dat");
        return true;
    }
    else{
        cout<<"\n\n\tThis account doesn't exist";
        return false;
    }
    
}


void account::drawal_depos(int i, long int x)
{
    long int amount = 0;
    ifstream File,tf;
    File.open("account.dat", ios::binary);
    if (!File) {
        cout<<"File could not be open !! Press any Key...";
        return;
    }
    while (File.read(reinterpret_cast<char *>(this), sizeof(account))) {
        if (acno==x) {
            if (i==1) {
                cout<<"\n\n\tTO WITHDRAW AMOUNT ";
                show_account();
                if (type=='G') {
                    cout<<"\nEnter The amount(<=10000) : ";
                    cin>>amount;
                    cin.ignore();
                    while (!(amount<=10000) || getdeposit()<amount) {
                        if (!(amount<=10000)) {
                            cout<<"\nEnter The amount Less Than 10000! : ";
                        }
                        else if (getdeposit()<amount){
                            cout<<"\nYour Balance is "<<getdeposit()<<" !\nPlease Enter different amount : ";
                        }
                        cin>>amount;
                        cin.ignore();
                    }
                }
                else if (type=='S') {
                    cout<<"\nEnter The  amount(<=5000) : ";
                    cin>>amount;
                    cin.ignore();
                    while (!(amount<=5000) || getdeposit()<amount) {
                        if (!(amount<=5000)) {
                            cout<<"\nEnter The amount Less Than 5000! : ";
                        }
                        else if (getdeposit()<amount){
                            cout<<"\nYour Balance is "<<getdeposit()<<" !\nPlease Enter different amount : ";
                        }
                        cin>>amount;
                        cin.ignore();
                    }
                }
                else if (type=='B'){
                    cout<<"\nEnter The amount(<=1000) : ";
                    cin>>amount;
                    cin.ignore();
                    while (!(amount<=1000) || getdeposit()<amount) {
                        if (!(amount<=1000)) {
                            cout<<"\nEnter The amount Less Than 1000! : ";
                        }
                        else if (getdeposit()<amount){
                            cout<<"\nYour Balance is "<<getdeposit()<<" !\nPlease Enter different amount : ";
                        }
                        cin>>amount;
                        cin.ignore();
                    }
                }
                setdrawal(amount);
                write_to_ftemp();
            }
            else if (i==2){
                cout<<"\n\n\tTO DEPOSITE AMOUNT ";
                show_account();
                cout<<"\nEnter The amount : ";
                cin>>amount;
                cin.ignore();
                setdepos(amount);
                write_to_ftemp();
            }
            cout<<"\n\n\t Record Updated...";
        }
    }
    File.close();
    delete_acc(x);
    tf.open("tmp.dat", ios::binary);
    if (!tf) {
        return;
    }
    while (tf.read(reinterpret_cast<char *>(this), sizeof(account))) {
        write_to_file();
    }
    tf.close();
    remove("tmp.dat");
}

