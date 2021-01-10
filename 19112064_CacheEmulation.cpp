#include <bits/stdc++.h>
#include <fstream>
#include <string>
using namespace std;
int main(int argc, char* argv[])
{
	string rep_policy = argv[0], infile = argv[1];
	string n_temp = argv[2];
	int n=0;
	/*for(int i=n_temp.length()-1;i>=0;i--)
	{
		char temp = n_temp[i];
		int tempk = int(temp-'0');
		n = n*10 + tempk;
	}*/
	n=18;
	ifstream fin;
	fin.open("infile",ios::in);
	vector<int>cache;
	int comp_miss;
	map<int,int>check;
	int cap_miss;
	vector<bool>out;
	vector<int>LRU;
	if(rep_policy == "LRU")
	{
		string word;
		while(!fin.eof())
		{
			fin >> word;
			int addr = atoi(const_cast<char*>(word.c_str()));
			check[addr]++;
			
			auto it=find(cache.begin(),cache.end(),addr);
			if(it != cache.end())
			{
				LRU.erase(it);
				LRU.insert(LRU.begin(),addr);
				out.push_back(1);
			}
			else 
			{
				out.push_back(0);
				if(check[addr] == 1)
					comp_miss++;
				else
					cap_miss++;
				if(cache.size() < n)
				{
					cache.push_back(addr);
					LRU.insert(LRU.begin(),addr);
				}
				else
				{
					int deladdr = *(LRU.end()-1);
					LRU.pop_back();
					LRU.insert(LRU.begin(),addr);
					auto it2=find(cache.begin(),cache.end(),deladdr);
					cache.erase(it2);
					cache.push_back(addr);
				}
			}
		}
		fin.close();
		ofstream fout;
		//string outfile = "19112064_" + rep_policy + "_" + n_temp + ".out.txt";
		fout.open("output1.txt",ios::out);
		if(fout.is_open())
		cout<<"continue"<<endl;
		fout << "TOTAL_ACCESSES = " << out.size();
		fout << "\nTOTAL_MISSES = " << comp_miss+cap_miss;
		fout << "\nCOMPULSORY_MISSES = " << comp_miss;
		fout << "\nCAPACITY_MISSES = " << cap_miss;
		for(int i=0; i < out.size(); i++)
		{
			if(out[i] == 1)
				fout << "HIT";
			else
				fout << "MISS";
			fout << "\n";
		}
		fout.close();
	}
	
	return 0;
}
