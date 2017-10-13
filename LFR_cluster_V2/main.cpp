#include <cstdio>
#include <fstream>
#include <cassert>
#include <cstring>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <stdlib.h>

using namespace std;

typedef vector<int> IntVec;

/*
void LoadData(map<int, int>& barcode_index, vector<vector<int> >& bar_unikmer_set)
{
	ifstream infile("test_file2");
	//infile.open(file.data());
	assert(infile.is_open());
	long  index = 0;
	const int Line_len = 10000;
	char str[Line_len];
	bar_unikmer_set.clear();
	barcode_index.clear();
	vector<int> unikmer_array;
	while (infile.getline(str, Line_len))
	{
		const char *split = " ,";
		char *p;
		p = strtok(str, split);
		unikmer_array.clear();
		barcode_index[index] = atol(p);
		while (p) {
			//printf("%s ", p);
			p = strtok(NULL, split);
			unikmer_array.push_back(atol(p));
		}
		bar_unikmer_set.push_back(unikmer_array);
		//printf("\n");
		++index;
	}
	infile.close();
}
int FindKmer(string kmerarray[], int x, string kmer)
{

}*/
void SplitString(const string& s, vector<int>& v, const string& c)
{
	string::size_type pos1, pos2;
	pos2 = s.find(c);
	pos1 = 0;
	while (string::npos != pos2)
	{
		v.push_back(atol(s.substr(pos1, pos2 - pos1).c_str()));

		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if (pos1 != s.length())
		v.push_back(atol(s.substr(pos1).c_str()));
}

void LoadIndex(map<int, int>& barcode_index, vector<vector<int> >& bar_unikmer_set)
{
	ifstream infile("test_file3");
	//infile.open(file.data());
	assert(infile.is_open());
	long  index = 0;
	string s;
	bar_unikmer_set.clear();
	barcode_index.clear();
	vector<int> unikmer_array;
	while (getline(infile, s))
	{
		istringstream strm(s);
		string barcode;
		string unikmer;
		string unikmer_string;
		unikmer_array.clear();
		strm >> barcode;
		barcode_index[index] = atol(barcode.c_str());
		strm >> unikmer_string;
		//cout << unikmer_string << endl;
		//if (unikmer_string.c_str())
		SplitString(unikmer_string, unikmer_array,",");
		bar_unikmer_set.push_back(unikmer_array);
		++index;
	}
	infile.close();
}


int main()
{
    printf("hello from LFR_cluster_V2!\n");
	map<int, int> barcode_index;
	vector<vector<int> > bar_unikmer_set;
	map<int, int>::const_iterator bar_ID;
	LoadIndex(barcode_index, bar_unikmer_set);
	cout << bar_unikmer_set[0][0] << " " << bar_unikmer_set[0][1] << endl;
	cout << bar_unikmer_set[1][0] << " " << bar_unikmer_set[1][1] << endl;
	//cout << bar_unikmer_set[2][0] << " " << bar_unikmer_set[2][1] <<endl;
	cout << bar_unikmer_set[3][0] << " " << bar_unikmer_set[3][1] << endl;
	for (bar_ID = barcode_index.begin(); bar_ID != barcode_index.end(); bar_ID++)
		cout << bar_ID->first << "->" << bar_ID->second << endl;
    return 0;
}


