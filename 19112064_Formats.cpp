#include <iostream>
#include <math.h>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;
string tostring(int n, int T)
{
    string out = "";
    for(int i = 0; i < T; i++)
    {
        int x = (n & (1<<(T-i-1)));
        if(x != 0)
            out+='1';
        else
            out+='0';
    }
    return out;
}
void solve(string n, int T, int E, fstream& fout)
{
    char sign_temp = n[0];
        int integer=0;
        int k =0;
        int i;
        for(i=n.length()-1;i>0;i--)
        {
            if(n[i]=='1')
            {
                integer = integer + pow(2,k);
            }
            k++;
        }
        if(sign_temp=='1')
            integer *= -1;
        float fixed_point = 0;
        k =0;
        for(i=E;i>0;i--)
        {
            if(n[i]=='1')
            {
                fixed_point = fixed_point + pow(2,k);
            }
            k++;
        }
        k=1;
         for(i=E+1;i<n.length();i++)
        {
            if(n[i]=='1')
            {
                fixed_point = fixed_point + pow(2,-k);
            }
            k++;
        }
        if(sign_temp=='1' && fixed_point!=0)
            fixed_point *= -1;
        float fraction = 0;
        int exponent=0;
        k=1;
        for(i=E+1;i<n.length();i++)
        {
            if(n[i]=='1')
            {
                fraction = fraction + pow(2,-k);
            }
            k++;
        }
        k=0;
        for(i=E;i>0;i--)
        {
            if(n[i]=='1')
            {
                exponent = exponent + pow(2,k);
            }
            k++;
        }
        int bias = pow(2,E-1)-1;
        float fp;
        string fpstring;
        int stringflag = 0;
        if(exponent==pow(2,E)-1 )
        {
              stringflag = 1;
            if(fraction==0)
            {
                if(sign_temp=='0')
                    fpstring = "+infinity";
                else
                    fpstring = "-infinity";
            }
            else
            {
                fpstring = "NAN";
            }
        }
        else if(exponent == 0)
        {
            if(fraction==0)
                fp=0;
            else
            {
                           stringflag = 2;
            fpstring = "    Denormal number ";
                fp=(0+fraction) * pow(2,1-bias);
                            if(sign_temp=='1')
                                fp *= -1;
            }
        }
        else
        {
            fp = (1+fraction) * pow(2,exponent-bias);
            if(sign_temp=='1')
            fp *= -1;
        }
        if(stringflag == 0)
            fout << n << setw(20) << integer << setw(20) << fixed_point <<setw(20) <<fp;
        else if(stringflag == 1)
            fout << n << setw(20) << integer << setw(20) << fixed_point <<setw(20) <<fpstring;
        else
            fout << n << setw(20) << integer << setw(20) << fixed_point << fpstring <<fp;
        fout << "\n";
}
int main(int argc,char* argv[])
{
    string infile = argv[1];
    string T_temp = argv[1];
    string E_temp = argv[2];
    string option = argv[3];
    string n;
    if(argc == 5)
         n = argv[4];
    int T=0,E=0,i;
    for(i=0;i<T_temp.length();i++)
	{
		char temp = T_temp[i];
		int tempk = int(temp-'0');
		T = T*10 + tempk;
	}
	for(int i=0;i<E_temp.length();i++)
	{
		char temp = E_temp[i];
		int tempk = int(temp-'0');
		E = E*10 + tempk;
	}
	if(option!="All")
    {
         fstream fout;
        string fname =  "19112064_" + T_temp + "_" + E_temp + "_Single_" + n + ".txt";;
        fout.open(fname.data(),ios::out);
        fout << "combinations             integer         fixed point                  FP\n";
        solve(n,T,E,fout);

    }
    else
    {
        fstream fout;
        string fname = "19112064_" + T_temp + "_" + E_temp + "_All.txt";
        fout.open(fname.data(),ios::out);
        fout << "combinations             integer         fixed point                  FP\n";
        int i = 0;
        for(;i < pow(2,T);i++)
        {
             string n = tostring(i,T);
            solve(n,T,E,fout);
        }
    }
    return 0;
}
