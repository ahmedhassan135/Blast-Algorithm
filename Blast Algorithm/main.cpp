#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

using namespace std;

	class LinkList
	{
	private:
		struct node
		{
			string seq;
			string name;
			int start;
			int ending;
			node *next;
		};


	public:
		node *head = NULL;
		node *tail = NULL;

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
				return newNode;
			}


			tail->next = newNode;
			tail = newNode;
			return newNode;
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
                        for (int j=i; j <= i+k-1; j++)
                        {
                            kmer = kmer + seq[j];
                        }
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
        for (int j=i; j <= i+k-1; j++)
        {
            kmer = kmer + seq[j];
        }
         myfile2 << kmer <<" "<< sname <<" "<<i<<" "<<i+k<< endl;
    }

    myfile2.close();


    cout<<"Finished Part 1...\n";

    seq = "";
    sname = "";
    firstSeq = true;


    LinkList querylist;

    ifstream queryfile ("query.txt");
    ifstream dbfile ("db.txt");


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
                        for (int j=i; j <= i+k-1; j++)
                        {
                            kmer = kmer + seq[j];
                        }
                        querylist.insert_node(kmer, sname, i, i+k);
                        //dbfile << kmer <<" "<< sname <<" "<<i<<" "<<i+k<< endl;
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


    querylist.print_all_records();


    cout<<"\n\n\nExiting...\n";
    return 0;
}
