#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
using namespace std ;

struct student 
  {
    string name ;
    int RollNumber ;
    int year ;
    string department ;
    float GPA ;
  };
vector<student>students;
vector<student>:: iterator it ;
int op , e =0 , del=0 , ROLL , YEAR  , location = 0 , pos=0 ;
float Gpa ;
string NAME , DEP , line ;
ofstream file ;

int TrueInput ();
void AddStudent () ;
void ShowAllStudent() ;
void DeleteStudent();


int main() 
{ 


   
cout << "welcome student recording " << endl ;
while(e==0)
{
   cout << "\n1. add student\n2. delete student\n3. show all studnts\n0. exist"<< endl;

   TrueInput();  

   switch(op)
   {
      case 0 :
         e++;
         break; 
      case 1 :
         AddStudent ();
         break;
      case 2 :
         DeleteStudent();
         break; 
      case 3 :
         ShowAllStudent();
         break;      

      
         
   }     
}
return 0;  
}



int TrueInput () // handle the errors
{
    do  
    {
       cin >> op ;
       if ( cin.fail() )
       {
          cin.clear();
          cin.ignore( 1000 ,'\n');
          cout << " please enter a number : ";

       }
       else if ( cin.peek() != '\n'  )
       {   
          cin.clear();
          cin.ignore( 1000 ,'\n');
          cout<<"please enter an number from 1 to 4 ";

       } 
       else if (  op > 3)
       {
          cout<<"please enter an number from 1 to 4 ";

       }  
       else 
          break;
    }while(true); 
return op;
}

void AddStudent () 
{
   student s ;
  cout << "Enter the student name : ";
  cin >> s.name;
  cout << "Enter the student Roll Number  : ";
  cin >> s.RollNumber;
  cout << "Enter the student year : ";
  cin >> s.year;
  cout << "Enter the student department : ";
  cin >> s.department;
  cout << "Enter the student GPA : ";
  cin >> s.GPA;
  
   
  students.push_back(s);
  file.open("data.csv", ios :: app); 
  
  file<<s.RollNumber<<","<<s.name<<","<<s.year<<","<<s.department<<","<<s.GPA<<'\n';
  file.close();
  cout<< "the student " << s.name << " added\n";
}
void ShowAllStudent()
{
  ifstream file ;
   file.open("data.csv");
   if (file.fail()){
       cout << "error in opening the file ";
   } 
   
   while(getline(file , line ))
   {    

   if (line.empty()) continue ;
   location = line.find(',');
   ROLL = stoi(line.substr(0,location));
   line = line.substr(location+1,line.length());

   location = line.find(',');
   NAME = line.substr(0,location);
   line = line.substr(location+1,line.length());

   location = line.find(',');
   YEAR =stoi( line.substr(0,location));
   line = line.substr(location+1,line.length());

   location = line.find(',');
   DEP = line.substr(0,location);
   line = line.substr(location+1,line.length());

   Gpa = stof(line);
   cout << "--------------------\n"; 
   cout << "name : " << NAME << "\nRoll Number : "<< ROLL <<"\nyear : "<< YEAR << " year \ndepartment : " << DEP <<"\nGPA : "<< Gpa << endl ;
   cout << "--------------------\n"; 
   }
   file.close();
}
void DeleteStudent ()
{
       cout << "Enter RollNumber to delete: ";
       cin >> del;

       
       for (it = students.begin(); it < students.end();  )
       {
           if (del == it->RollNumber)
               it = students.erase(it); 
           else
               ++it;
       }

       
       ifstream file("data.csv");
       ofstream temp("temp.csv");

       string linee;
       bool found = false;

       while (getline(file, linee))
       {
           if (linee.empty()) continue ;
          
          int roll;
            pos = linee.find(',');
           if (pos != string::npos)
           {
              
   roll=stoi(linee.substr(0, pos));
              
               if (roll == del)
               {
                   found = true;
                   continue; 
               }
           }
           temp << linee << '\n'; 
       }

       file.close();
       temp.close();

       
       remove("data.csv");
       rename("temp.csv", "data.csv");

       if (found)
           cout << "Student with RollNumber " << del << " deleted.\n";
       else
           cout << "Student not found.\n";
   }

