#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
#include<iomanip>
#include<cstdlib>

using namespace std;

const int EMP_ID_WIDTH = 8;
const int EMP_NAME_WIDTH = 20;
const int EMP_EMAIL_WIDTH = 25;
const int EMP_NUMERIC_WIDTH = 10;
const int TOTAL_WIDTH = 100;

struct Employee
{
    int empId;
    string name;
    double basicSalary;
    double pf;
    double healthInsAmt;
    string email;
};

//FUNCTION PROTOTYPES :
void readFile(vector <Employee> &v_emp);
void printMenu();
void doTask(vector <Employee> &v_emp, int option);
void addEmployee(vector<Employee> &v_emp);
int searchEmployee(vector<Employee> v_emp, int targetEmpId);
void saveToFile(vector<Employee> v_emp);
void printEmployees(vector <Employee> v_emp);
void printEmployee(Employee e);
double getNetSalary(Employee e);
bool deleteEmployee(vector<Employee> &v_emp, int targetEmpId);

//FUNCTIONS :
void readFile(vector <Employee> &v_emp)
{
    ifstream fin("emp.txt");
    if(!fin)
    {
        cout<<"unable to open database file emp.txt"<<endl
            <<"Make sure that the file exist"<<endl;
            exit(1);
    }
    string line;
    int recNo=0;
    while(!fin.eof()) // The loop will run as long as it is not the end of file
    {
        std::getline(fin, line);
        recNo++;
        istringstream iss(line);
        string strEmpId;
        string strName;
        string strBasicSalary;
        string strPf;
        string strStrHealthInsAmt;
        string strEmail;
        std::getline(iss,strEmpId, ',');
        std::getline(iss,strName, ',');
        std::getline(iss,strBasicSalary, ',');
        std::getline(iss,strPf, ',');
        std::getline(iss,strStrHealthInsAmt, ',');
        std::getline(iss,strEmail, ',');
        Employee temp;
        temp.empId = atoi(strEmpId.c_str());
        temp.name = strName;
        temp.basicSalary = atof(strBasicSalary.c_str());
        temp.pf = atof(strPf.c_str());
        temp.healthInsAmt = atof(strStrHealthInsAmt.c_str());
        temp.email=strEmail;

        v_emp.push_back(temp);
    }
    fin.close();
}

void printMenu()
{
    cout << "1. Add Employee " << endl;
    cout << "2. Print Employee Report " << endl;
    cout << "3. Search Employee " << endl;
    cout << "4. Delete Employee " << endl;
    cout << "5. Save " << endl;
    cout << "6. Exit " << endl;
}

void doTask(vector<Employee> &v_emp, int option)
{
    int targetEmpId;
    int index;
    switch(option)
    {
        case 1 : addEmployee(v_emp);
                 break;
        case 2 : printEmployees(v_emp);
                 break;
        case 3 : cout<<"Enter Employee ID to search : ";
                 cin>>targetEmpId;
                 index = searchEmployee(v_emp, targetEmpId);
                 if( index == -1 )
                 {
                     cout<<"Employee with ID : "<<targetEmpId
                         << "doesn't exists. "<<endl;
                 }
                 else
                 {
                     cout<<"Employee with ID : "<<targetEmpId
                         <<" found."<<endl;
                     printEmployee(v_emp[index]);
                 }
                 break;
        case 4 : cout<<"Enter Employee ID to Delete : ";
                 cin>>targetEmpId;
                 if(deleteEmployee(v_emp, targetEmpId))
                 {
                     cout<<"Employee with ID : "<<targetEmpId
                         <<"Deleted Successfully. "<<endl;
                     cout<<"please use option-5 to save the changes permanently."<<endl;
                 }
                 else
                 {
                     cout<<"Employee with ID : "<<targetEmpId
                         <<"could not be deleted. "<<endl;
                 }
                 break;
        case 5 : saveToFile(v_emp);
                 break;
       default : cout<<"Invalid menu option chosen, valid options are from 1-6 "<<endl;
    }
}

void addEmployee(vector <Employee> & v_emp)
{
    Employee temp;
    bool isDuplicate = false;
    do
    {
        cout<<"Emp Id : ";
        cin>>temp.empId;
        isDuplicate = false;
        if(searchEmployee(v_emp, temp.empId)!= -1)
        {
            isDuplicate = true;
            cout<<"Employee ID : "<<temp.empId
                <<" already exists, please input unique ID "<<endl;
        }
    }while (isDuplicate);
    cout<<"Name : ";
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    std::getline(cin, temp.name);
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    cout<<"Basic Salary ($) : ";
    cin>>temp.basicSalary;
    cout << "PF($): ";
    cin >> temp.pf;
    cout<<"Health Ins ($) : ";
    cin>>temp.healthInsAmt;
    cout<<"Email : ";
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    std::getline(cin, temp.email);

    v_emp.push_back(temp);
    cout<<"Employee with ID : "<<temp.empId
        <<" added successfully "<<endl;
    cout<<"Total Employees : "<<v_emp.size()<<endl;
}

int searchEmployee(vector <Employee> v_emp, int targetEmpId)
{
    for(int i=0; i<v_emp.size(); i++)
    {
        if(v_emp[i].empId == targetEmpId)
        {
            return i;
        }
    }
    return -1;
}

void saveToFile(vector<Employee> v_emp)
{
    ofstream fout("emp.txt");
    if(!fout)
    {
        cout<<"unable to open the data file emp.txt"<<endl;
        return;
    }
    int recCount =0;
    for(vector<Employee>::iterator it =v_emp.begin(); it!= v_emp.end();++it)
    {
        fout<<it->empId<<","<<it->name<<","
            <<it->basicSalary<<","<<it->pf<<","
            <<it->healthInsAmt<<","<<it->email;
        recCount++;
        if(recCount != v_emp.size())
        {
            fout<<endl;
        }
    }
    fout.close();
    cout<<"Total of "<<recCount<<" records saved successfully into the file. "<<endl;
}

void printEmployees(vector <Employee> v_emp)
{
    cout<<endl;
    // First we need to print the headings
    cout<<setw(EMP_ID_WIDTH)<<left<<"EmpID"
        <<setw(EMP_NAME_WIDTH)<<left<<"Name"
        <<setw(EMP_EMAIL_WIDTH)<<left<<"Email"
        <<setw(EMP_NUMERIC_WIDTH)<<right<<"Basic ($)"
        <<setw(EMP_NUMERIC_WIDTH)<<right<<"PF ($)"
        <<setw(EMP_NUMERIC_WIDTH)<<right<<"HltIns ($)"
        <<setw(EMP_NUMERIC_WIDTH)<<right<<"Net ($)"
        <<endl;
    cout<<setw(TOTAL_WIDTH)<<setfill('-')<<" "<<endl;
    cout<<setfill(' ');
    double totalBasic = 0.0;
    double totalpfDeduction = 0.0;
    double totalHealthIns = 0.0;
    double totalNetSalary = 0.0;

    for(vector<Employee>::iterator it = v_emp.begin(); it!=v_emp.end();it++)
    {
        printEmployee(*it);
        totalBasic += it->basicSalary;
        totalpfDeduction += it->pf;
        totalHealthIns += it->healthInsAmt;
        totalNetSalary += getNetSalary(*it);
    }
    cout<<setw(TOTAL_WIDTH)<<setfill('-')<<" "<<endl;
    cout<<setfill(' ');
    cout<<setw(EMP_ID_WIDTH)<<left<<"Total"
        <<setw(EMP_NAME_WIDTH)<<left<<"In($)"
        <<setw(EMP_EMAIL_WIDTH)<<left<<" "
        <<setw(EMP_NUMERIC_WIDTH)<<setprecision(2)<<right<<fixed<<totalBasic
        <<setw(EMP_NUMERIC_WIDTH)<<setprecision(2)<<right<<fixed<<totalpfDeduction
        <<setw(EMP_NUMERIC_WIDTH)<<setprecision(2)<<right<<fixed<<totalHealthIns
        <<setw(EMP_NUMERIC_WIDTH)<<setprecision(2)<<right<<fixed<<totalNetSalary
        <<endl;
}

void printEmployee(Employee e)
{
    cout<<setw(EMP_ID_WIDTH)<<left<<e.empId
        <<setw(EMP_NAME_WIDTH)<<left<<e.name
        <<setw(EMP_EMAIL_WIDTH)<<left<<e.email
        <<setw(EMP_NUMERIC_WIDTH)<<setprecision(2)<<fixed<<right<<e.basicSalary
        <<setw(EMP_NUMERIC_WIDTH)<<setprecision(2)<<fixed<<right<<e.pf
        <<setw(EMP_NUMERIC_WIDTH)<<setprecision(2)<<fixed<<right<<e.healthInsAmt
        <<setw(EMP_NUMERIC_WIDTH)<<setprecision(2)<<fixed<<right<<getNetSalary(e)
        <<endl;
}

double getNetSalary(Employee e)
{
    return e.basicSalary-(e.pf+e.healthInsAmt);
}

bool deleteEmployee(vector<Employee> &v_emp, int targetEmpId)
{
  int index = searchEmployee(v_emp, targetEmpId);
  if(index == -1)
  {
      return false;
  }
  cout<<"Target Employee with ID : "<<targetEmpId<<" found : "<<endl;
  printEmployee(v_emp[index]);
  cout<<"Are you sure to delete? Input '1' to delete OR '0' to exit. "<<endl;
  int option;
  cin>>option;
  if(option==1)
  {
      v_emp.erase(v_emp.begin()+index);
      return true;
  }
  return false;
}

int main()
{
    vector<Employee> v_emp;
    readFile(v_emp);
    cout<<"Total "<<v_emp.size()<<" records read from the data file "<<endl;
    printMenu();
    bool quit=false;
    while( !quit )
    {
        cout<<"Input your option : ";
        int option;
        cin>>option;
        if(option==6)
        {
            quit=true;
        }
        else
        {
            doTask(v_emp,option);
        }
    }
    return 0;
}
