#include<iostream>
#include<vector>
#include<numeric>
#include<fstream>
#include<string>
#include<sstream>
#include<iterator>

using namespace std;

const string A_FILE="A.txt";
const string B_FILE="B.txt";
const string PI_FILE="pi.txt";

double forward(vector<vector<double>> a,vector<vector<double>> b,vector<double> pi,vector<unsigned> seq){
	vector<vector<double>> alphas(seq.size(),vector<double>(a.size(),0.0));
	for(int i=0;i!=seq.size();++i){
		for(int j=0;j!=a.size();++j){
			if(i==0){alphas[i][j]=pi[j]*b[j][seq[i]];}
			else{
				for(int k=0;k!=a.size();++k){alphas[i][j]+=(alphas[i-1][k]*a[k][j]*b[j][seq[i]]);}
			}
		}
	}
	return accumulate((alphas.end()-1)->begin(),(alphas.end()-1)->end(),0.0)/seq.size();
}

vector<double> parse_line(const string& line){
	istringstream iss(line);
	return {istream_iterator<double>(iss),istream_iterator<double>{}};
}

vector<vector<double>> read_a(string a_file=A_FILE){
	ifstream ifs(a_file);
	vector<vector<double>> ret;
	string line;
	while(getline(ifs,line)){ret.push_back(parse_line(line));}
	return ret;
}

vector<vector<double>> read_b(string b_file=B_FILE){
	ifstream ifs(b_file);
	vector<vector<double>> ret;
	string line;
	while(getline(ifs,line)){ret.push_back(parse_line(line));}
	return ret;
}

vector<double> read_pi(string pi_file=PI_FILE){
	ifstream ifs(pi_file);
	vector<double> ret;
	double d;
	while(ifs>>d){ret.push_back(d);}
	return ret;
}

int main(){
	cout<<forward(read_a(),read_b(),read_pi(),{0,13,3})<<endl;
}
