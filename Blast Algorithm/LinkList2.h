//For storing matched K-mers and their important information


#include <iostream>
#include <cstring>

using namespace std;

struct node2
		{
			string seq;
			string name;
			string pname;
			int start;
			int ending;
			int pstart;
			int pending;
			node2 *next;
			node2 *pre;
		};


class LinkList2
	{
	    public:


		node2 *head = NULL;
		node2 *tail = NULL;


		int length = 0;

		node2 *insert_node(string Seq, string Name, string Pname, int Start, int Ending, int PStart, int PEnding)
		{
			node2 *newNode = new node2;

			newNode->seq = Seq;
			newNode->name = Name;
			newNode->pname = Pname;
			newNode->start = Start;
			newNode->ending = Ending;
			newNode->pstart = PStart;
			newNode->pending = PEnding;
			newNode->next = NULL;
			newNode->pre = tail;


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

        node2 gotonode(int index)
        {
            node2 *tempptr = head;
            for (int i=1; i<=index;i++)
            tempptr = tempptr->next;

            return *tempptr;

        }

		void print_all_records()
		{
		    cout<<"\n\nprinting all matched records\n\n";
			node2 *tempptr = head;
			while (tempptr)
			{
				cout<<tempptr->seq << ", " << tempptr->name <<", "<<tempptr->pname<<", "<<tempptr->start<<", "<<tempptr->ending <<", "<<tempptr->pstart<<", "<<tempptr->pending<<endl;
				tempptr = tempptr->next;
			}
			cout<<"length is " << length;
		}

		void deleteNode(string seqVal, string Name, string Pname)
		{
		    node2 *tempptr = head;
            while (true)
			{
			    if (tempptr == NULL)
                    return;
			    if (tempptr->seq == seqVal)
                {
                    if(tempptr->name == Name)
                    {
                        if(tempptr->pname == Pname)
                        {
                            break;
                        }
                    }
                }
                if (tempptr->next)
                    tempptr = tempptr->next;
			}

			if (tempptr == head)
			{
			    if (tempptr->next)
                {
                    head = tempptr->next;
                    head->pre = NULL;
                }
                else
                {
                    head = NULL;
                    tempptr = NULL;
                }

			}
			else
            {
                tempptr->pre->next = tempptr->next;
                delete tempptr;
			}

		}

		void generateResults()
		{
		    ofstream resultsfile ("matches.txt");

		    //resultsfile << "Start of Query" <<"\t"<< "End of Query" <<"\t"<< "Total Length Query" <<"\t"<< endl;

            node2 *tempptr = head;

            int p=0,r=0;
            string conname;
            string conpname;

            p = tempptr->pstart;
            r = tempptr->pending;
            conname = tempptr->name;
            conpname = tempptr->pname;

            tempptr = head->next;

            deleteNode(head->seq, head->name, head->pname);

            while (head != NULL)
            {

                if(tempptr->name == conname && tempptr->next)
                {
                    if(tempptr->pname == conpname)
                    {
                        if (p == tempptr->pstart && r == tempptr->pending)
                        {
                            node2 *newTemp = tempptr->next;
                            deleteNode(tempptr->seq, tempptr->name, tempptr->pname);
                            tempptr = newTemp;

                        }
                        else if (p >= tempptr->pstart && r <= tempptr->pending)
                        {
                            p = tempptr->pstart;
                            r = tempptr->pending;
                            node2 *newTemp = tempptr->next;
                            deleteNode(tempptr->seq, tempptr->name, tempptr->pname);
                            tempptr = newTemp;

                        }
                        else if (p >= tempptr->pstart && r > tempptr->pending)
                        {
                            p = tempptr->pstart;
                            node2 *newTemp = tempptr->next;
                            deleteNode(tempptr->seq, tempptr->name, tempptr->pname);
                            tempptr = newTemp;

                        }
                        else if (p < tempptr->pstart && r <= tempptr->pending)
                        {
                            r = tempptr->pending;

                            node2 *newTemp = tempptr->next;
                            deleteNode(tempptr->seq, tempptr->name, tempptr->pname);
                            tempptr = newTemp;

                        }
                        else if (p < tempptr->pstart && r > tempptr->pending)
                        {
                            node2 *newTemp = tempptr->next;
                            deleteNode(tempptr->seq, tempptr->name, tempptr->pname);
                            tempptr = newTemp;

                        }
                    }
                    else
                        {
                            if (tempptr->next)
                            tempptr = tempptr->next;

                        }
                }
                else
                {
                    //write to file;

                    resultsfile <<conpname<<"\t\t"<<conname<<"\t\t"<< p <<"\t\t"<< r <<"\t\t"<< r-p <<"\t\t"<< endl;
                    cout<<"MATCHED seq\t"<<p<<" to "<<r<<endl;

                    p = head->pstart;
                    r = head->pending;
                    conname = head->name;
                    conpname = head->pname;



                    deleteNode(head->seq, conname, conpname);


                    tempptr = head;

                    if (!head)
                    {
                        resultsfile << p <<"\t\t"<< r <<"\t\t"<< r-p <<"\t\t"<< endl;
                    }


                    continue;
                }
            }
            resultsfile.close();
		}


	};











