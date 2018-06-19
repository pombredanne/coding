#include<iostream>
#include<string>
#include<iomanip>
#include<vector>
#include<algorithm>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::sort;
using std::string;
using std::istream; 
using std::setw;
struct Stdudent_info{
    string name;
    double middle,finall;
    vector<double> homework;
};
void read_hw(vector<double>& hw){
    double x;
    while(cin>>x){
        hw.push_back(x);
    }
}
istream& read_hw2(istream& in,vector<double>& hw){
    if(in){
        hw.clear();
    double x;
    while(in >> x){
        hw.push_back(x);
    }
    in.clear();
    }
    return in;
}
istream& read(istream& in,Stdudent_info& s){
    cout<<"please input name middle finall"<<endl;
    in>>s.name>>s.middle>>s.finall;
    read_hw2(in,s.homework);
    return in;
}

bool compare(const Stdudent_info& x,const Stdudent_info& y){
    return x.name<y.name;
}
double grade(Stdudent_info & s){
    return s.middle+s.finall;
}
int main(){
	vector<Stdudent_info> students;
    Stdudent_info record;
    int maxlen =0;
    // double x;
    // vector<double> homework;
    // read_hw2(cin,homework);
    // while(cin>>x){
    //     homework.push_back(x);
    // }
    // read
    while(read(cin,record)){
        // maxlen=max(maxlen,record.name.size());
        students.push_back(record);
        cout<<"input anthoer student"<<endl;
    }
    //sort students
    sort(students.begin(),students.end(),compare);
    for (int i=0;i<students.size();i++){
        cout<<setw(maxlen+1)<<students[i].name;
        double finall_grade = grade(students[i]);
        cout<<finall_grade<<endl;
        cout<<endl;
    }

    return 0;
}
