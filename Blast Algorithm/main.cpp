#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include "LinkList.h"
#include "LinkList2.h"

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


    cout<<"Finished Part 1...\n";

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


    //Start and end point of query sequence
    //Seq ID using the start and end of matched k-mers



    //Testing Phase

    cout<<"Checking for match\n\n\n";


    cout<<"\n\n\nChecking for match\n\n\n";

    LinkList2 matchlist;
    //matchlist.print_all_records();
    //

    int kmer_count = 0;//number of matching k-mers

    cout<<"seq\tname\tpname\tps\tpe\ts\te\n";
    for (int i=0; i<querylist.length; i++)
    //cout<<"index is "<<querylist.gotonode(2).seq;
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
                //cout<<i<<": "<<tempseq<<" with "<<querylist.gotonode(i).seq<<endl;
                if (tempseq == returnedNode.seq)       //push all the found k-mers in a linklist.
                {
                    matchlist.insert_node(tempseq, returnedNode.name, tempname, returnedNode.start, returnedNode.ending, tempstart, tempend);
                    cout<<tempseq<<"\t"<<returnedNode.name<<"\t"<<tempname<<"\t"<<tempstart<<"\t"<<tempend<<"\t"<<returnedNode.start<<"\t"<<returnedNode.ending<<endl;
                }


            }
        //cout<<"i is "<<i<<endl;
    }
    dbfile.close();                 //At the end of a query sequence being found write it into a table.
    }



    //querylist.print_all_records();



    matchlist.print_all_records();
    cout<<endl<<endl<<endl;



    matchlist.generateResults();


    cout<<"\n\n\nExiting...\n";
    return 0;
}
