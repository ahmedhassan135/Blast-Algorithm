#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

using namespace std;


struct node
		{
			string seq;
			string name;
			int start;
			int ending;
			node *next;
		};

	class LinkList
	{
	    public:


		node *head = NULL;
		node *tail = NULL;

		int length = 0;

		node *insert_node(string Seq, string Name, int Start, int Ending)
		{
			node *newNode = new node;

			newNode->seq = Seq;
			newNode->name = Name;
			newNode->start = Start;
			newNode->ending = Ending;
			newNode->next = NULL;


			if (head == NULL)
			{
				head = newNode;
				tail = newNode;
				length = 1;
				return newNode;
			}


			tail->next = newNode;
			tail = newNode;
			length++;
			return newNode;
		}

        node gotonode(int index)
        {
            node *tempptr = head;
            for (int i=1; i<=index;i++)
            tempptr = tempptr->next;

            return *tempptr;

        }

		void print_all_records()
		{
		    cout<<"\nprinting all records\n\n";
			node *tempptr = head;
			while (tempptr)
			{
				cout << tempptr->seq << ", " << tempptr->name <<", "<<tempptr->start<<", "<<tempptr->ending<<endl;
				tempptr = tempptr->next;
			}
			cout<<"length is " << length;
		}


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
        kmer = seq.substr(i, k);
        querylist.insert_node(kmer, sname, i, i+k);
    }


    //Start and end point of query sequence
    //Seq ID using the start and end of matched k-mers



    //Testing Phase

    cout<<"Checking for match\n\n\n";


    cout<<"\n\n\nChecking for match\n\n\n";


    //

    int kmer_count = 0;//number of matching k-mers


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

                //cout<<i<<": "<<tempseq<<" with "<<querylist.gotonode(i).seq<<endl;
                if (tempseq == querylist.gotonode(i).seq)
                {
                    cout<<tempseq<<" "<<tempname<<" "<<tempstart<<" "<<tempend<<endl;
                }


            }
        cout<<"i is "<<i<<endl;
    }
    dbfile.close();
    }




    querylist.print_all_records();


    cout<<"\n\n\nExiting...\n";
    return 0;
}
