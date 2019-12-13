#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

using namespace std;

int main()
{

    cout<<"Starting Part 1...\n";

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
            if (line[0] == '>')
            {
                if (!firstSeq)
                {
                    for (int i=0; i < (seq.length()-k+1); i++)
                    {
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


    cout<<"Finished Part 1...\n";


    cout<<"\n\n\nExiting...\n";
    return 0;
}
