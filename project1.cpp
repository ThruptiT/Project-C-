/* Bank Mnagement system
author:Thrupti T
date  :11/10/2021
*/


#include <iostream>
#include<string.h>
#include<fstream>
using namespace std;

// Class bank to get user details
class bank
{
  public:
  int accountno,record_no=1;
  double balance;
  char name[50];
  char account_type[50];


//getting the data from user
  void get(){
      
      cout << "enter the name:";
      cin>>name;
      cout<<"enter the account number:";
      cin>>accountno;
      cout<<"account type:";
      cin>>account_type;
      cout<<"enter the balance:";
      cin>>balance;
      cout<<"\n";
      update();
      record_no++;
  }
  

//withdraw funtion
void withdraw(int amount){
  
  
  if(amount<=balance){
  balance=balance-amount;
  update();
  }
  else{
    cout<<"invalid";
  }
}

//updating the details in bankdetail file
void update(){
fstream bankdetail;

bankdetail.open("bankdetail.txt",ios::app|ios::binary);
       
bankdetail<<name;
bankdetail<<"              ";
bankdetail<<accountno;
bankdetail<<"              ";
bankdetail<<account_type;
bankdetail<<"              ";
bankdetail<<balance;
bankdetail<<"\n";
bankdetail.close();
}

//member function to deposite money

void deposite(int amount){
  double new_amount=balance+amount;
  balance=new_amount;
  update();
}


// display the data on the console
void display(){
  fstream bankdetail;
  bankdetail.open("bankdetail.txt",ios::in);
  bankdetail.seekg(0,ios::beg);
	char info[100];
	
    while(bankdetail)
    {
        bankdetail.getline(info,100);//read the info from the file
        cout<<info<<endl;// put the info on the console
        
    }
    
	bankdetail.close();
}

////searching the account is it present or not.if it is found it display the acoount detail.
int Search(int a)
{
    if (accountno == a) {
        ShowAccount();
        cout<<"\n";
        return (1);
    }
    return (0);
    
}

//displaying the data
 void ShowAccount()
    {
        cout << "Account Number: " << accountno << endl;
        cout << "Name: " << name << endl;
        cout << "Balance: " << balance << endl;
    }

//to store the details in transaction file
void transaction(int a,int b){
  fstream transaction;

  transaction.open("transaction.txt",ios::app|ios::binary);
  transaction<<a;
  transaction<<"              ";
  transaction<<name;
  transaction<<"              ";
  transaction<<b;
  transaction<<"              ";
  transaction<<balance;
  transaction<<"\n";
 
}

};

//main function
int main() {
    bank ba[50];
    int num,i,found,a;
    int userOption;
    //entering the total number of user input
    cout<<"enter the number of details required";
    cin>>num;

    //getting the details from user
    for(i=0;i<num;i++){
      ba[i].get();
      }

    
    cout<<"............................"<<endl;

     do{
        cout<<"What do you want to do further?";
        
        cout<<"\n1: Do you want to deposite?";
        cout<<"\n2: Do you want to withdraw?";
        cout<<"\n3: Do you want to display?";
        cout<<"\n4: Do you want to search?";
        cout<<"\n5: Do you want to add more?";
        cin>>userOption;
        //switch statement to select the option

        switch(userOption)
        {
            
        case 1:
                cout << "Account Number To Deposit Amount? ";
                cin >> a;
                int amount;
                //searching the account is present or not.if it present deposite operation take place.
                for (i = 0; i < num; i++) {
                found = ba[i].Search(a);
                if (found) {
                  cout<<"enter the amount to deposite";
                  cin>>amount;
                    ba[i].deposite(amount);
                    ba[i].transaction(a,amount);
                    break;
                }
            }
            if (!found)
                cout << "Record Not Found" << endl;
            cout<<"----------------------------"<<endl;
            break;



        case 2:
               cout << "Account Number To withdraw Amount? ";
                cin >> a;
               //searching the account is present or not.if it present withdraw operation take place.
                
                for (i = 0; i <num; i++) {
                found = ba[i].Search(a);
                if (found) {
                  cout<<"enetr the amount to withdraw";
                  cin>>amount;
                    ba[i].withdraw(amount);
                    ba[i].transaction(a,amount);
                    break;
                }
            }
            if (!found)
                cout << "Record Not Found" << endl;
            cout<<"----------------------------"<<endl;
            break;

        case 3:
              
                for (i = 0; i <num; i++) {
                ba[i].display();
            }
            cout<<"----------------------------"<<endl;
            break;

        case 4:
            cout << "Account Number? ";
            cin >> a;
            for (i = 0; i < num; i++) {
                found = ba[i].Search(a);
                if (found)
                    break;
            }
            if (!found)
                cout << "Record Not Found" << endl;
            cout<<"----------------------------"<<endl;
            break;

        case 5:
            int n;
            
            cout<<"enter the number of data to add:";
            cin>>n;
            for(i=0;i<n;i++){
            ba[num+i].get();
            num++;
            }
            
           break;
        default:
           cout<<"invalid";
        }
                
        
        cout<<"Do you want to repeat?(1= yes, 0=no)";
        cin>>userOption;
}while(userOption);

	return 0;
}

 