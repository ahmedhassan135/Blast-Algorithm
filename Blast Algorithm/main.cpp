#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

int main()
{
    string line;
    string sname;
    string seq;

    int k = 5;

    bool firstSeq = true;

    ifstream myfile ("fastadb.txt");
    ofstream myfile2 ("db.txt");
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            //cout << line << '\n';
            if (line[0] == '>')
            {
                if (!firstSeq)
                {
                    for (int i=0; i < (seq.length()-k+1); i++)
                    {
                        //cout<<"."<<seq[i]<<"and"<<seq[i+k-1]<<seq[i+k]<<" for "<<seq<<endl;
                        string kmer = "";
                        for (int j=i; j <= i+k-1; j++)
                        {
                            kmer = kmer + seq[j];
                        }
                        myfile2 << kmer <<" "<< sname << endl;
                    }

                }

                else
                    firstSeq = false;

                sname = line.substr(1, line.length());
                seq = "";
            }
            else
            {
                seq = seq + line;
            }
            //cout << sname << '\n';
        }
    myfile.close();
    }
    else cout << "Unable to open file";

    for (int i=0; i < (seq.length()-k+1); i++)
    {
        string kmer = "";
        for (int j=i; j <= i+k-1; j++)
        {
            kmer = kmer + seq[j];
        }
        myfile2 << kmer <<" "<< sname << endl;
    }

    myfile2.close();


    cout<<"\n\n\nExiting...\n";
    return 0;
}
