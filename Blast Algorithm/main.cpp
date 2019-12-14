#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include "LinkList.h"
#include "LinkList2.h"

using namespace std;

struct store
{
    string name;
    string sequence;
};


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
                        kmer = seq.substr(i, k);
                        myfile2 << kmer <<" "<< sname <<" "<<i<<" "<<i+k<< endl;

                    }

                }

                else
                    firstSeq = false;

                sname = line.substr(1, line.length()-1);



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
        kmer = seq.substr(i, k);
         myfile2 << kmer <<" "<< sname <<" "<<i<<" "<<i+k<< endl;
    }

    myfile2.close();




    ///////////////

    string strtemp;

    store array[50];
    int arrindex = -1;

    ifstream myfile3 ("fastadb.txt");
     if (myfile3.is_open())
    {
        while (getline (myfile3,line))
        {
            if (line[0] == '>')
            {
                arrindex++;
                array[arrindex].name = line.substr(1, line.length()-1);
            }
            else
            {
                array[arrindex].sequence = array[arrindex].sequence + line;
            }

        }
    }

    arrindex++;
    myfile3.close();


    for (int i = 0; i < arrindex; i++)
    {
        cout<< array[i].name<<": "<<array[i].sequence<<endl;
    }



////////////////////////////////////
    cout<<"Finished Part 1...\n";

    system("pause");

    seq = "";
    sname = "";
    firstSeq = true;



    LinkList querylist;


    ifstream queryfile ("query.txt");



    if (queryfile.is_open())
    {
        while ( getline (queryfile,line) )
        {
            if (line[0] == '>')
            {
                if (!firstSeq)
                {
                    for (int i=0; i < (seq.length()-k+1); i++)
                    {
                        string kmer = "";
                        kmer = seq.substr(i, k);
                        querylist.insert_node(kmer, sname, i, i+k);

                    }

                }

                else
                    firstSeq = false;

                sname = line.substr(1, line.length()-1);
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
        kmer = seq.substr(i, k);
        querylist.insert_node(kmer, sname, i, i+k);
    }




    cout<<"Checking for match\n\n\n";


    cout<<"\n\n\nChecking for match\n\n\n";

    LinkList2 matchlist;

    int kmer_count = 0;//number of matching k-mers

    cout<<"seq\tname\tpname\tps\tpe\ts\te\n";
    for (int i=0; i<querylist.length; i++)
    {
        ifstream dbfile ("db.txt");
        if (dbfile.is_open())
        {
            while (!dbfile.eof())
            {
                string tempseq;
                string tempname;
                int tempstart;
                int tempend;

                dbfile>>tempseq;
                dbfile>>tempname;
                dbfile>>tempstart;
                dbfile>>tempend;

                node returnedNode = querylist.gotonode(i);
                if (tempseq == returnedNode.seq)       //push all the found k-mers in a linklist.
                {
                    matchlist.insert_node(tempseq, returnedNode.name, tempname, returnedNode.start, returnedNode.ending, tempstart, tempend);
                    cout<<tempseq<<"\t"<<returnedNode.name<<"\t"<<tempname<<"\t"<<tempstart<<"\t"<<tempend<<"\t"<<returnedNode.start<<"\t"<<returnedNode.ending<<endl;
                }


            }
    }
    dbfile.close();
    }



    //querylist.print_all_records();



    matchlist.print_all_records();
    cout<<endl<<endl<<endl;



    matchlist.generateResults();


    ifstream matchfile ("matches.txt");
    ofstream resultfile ("results.txt");

    resultfile <<"Query seq ID"<<"\t\t"<< "Start point query" <<"\t\t"<< "End point query" <<"\t\t"<< "length"<<"\t\t"
                        <<"DB seq ID"<<"\t\t"<<"Start(Letter) DB seq"<<"\t\t"<<"End(Letter) DB seq"<< endl;

    if (matchfile.is_open())
    {
        while (!matchfile.eof())
            {
                string tpname;
                string tname;
                int tempstart;
                int tempend;
                int tempsize;

                matchfile>>tpname;
                matchfile>>tname;
                matchfile>>tempstart;
                matchfile>>tempend;
                matchfile>>tempsize;

                for (int i = 0; i < arrindex; i++)
                {
                    if (array[i].name == tpname)
                    {
                        resultfile <<tname<<"\t\t\t"<< tempstart <<"\t\t\t\t"<< tempend <<"\t\t\t"<< tempend-tempstart<<"\t\t"
                        <<tpname<<"\t\t\t"<<(array[i].sequence)[0]<<"\t\t\t\t"<<(array[i].sequence)[array[i].sequence.length()-1]<< endl;
                    }
                }


            }
    }


    cout<<"\n\n\nExiting...\n";
    return 0;
}
