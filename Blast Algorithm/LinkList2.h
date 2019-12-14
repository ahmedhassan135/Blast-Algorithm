//For storing matched K-mers and their important information



//For Breaking queries into k-mers and storing in Linklist

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
            //cout<<"\nreceived"<<tempptr->seq<<"."<<seqVal<<" "<<tempptr->name<<"."<<Name<<" "<<tempptr->pname<<"."<<Pname<<"."<<"\n";
		    while (tempptr->seq != seqVal && tempptr->name != Name && tempptr->pname != Pname)
			{
			    cout<<"loop";
				tempptr = tempptr->next;
			}

			if (tempptr == head)
			{
			    head = tempptr->next;
			    head->pre = NULL;
			    delete tempptr;
			    cout<<"\n\n\nDELEATED head\n\n\n";
			}
			else
            {
                tempptr->pre->next = tempptr->next;
                delete tempptr;
                cout<<"\n\n\nDELEATED\n\n\n";
			}

		}

		void generateResults()      //string Seq, string Name, int Start, int Ending, int PStart, int PEnding
		{
            node2 *tempptr = head;

            int p=0,r=0;
            //string concstr = "";
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
                //cout<<endl<<tempptr->seq<<endl;
                if(tempptr->name == conname)
                {
                    if(tempptr->pname == conpname)
                    {
                        if (p == tempptr->pstart && r == tempptr->pending)
                        {
                            cout<<"1 Condition\n";
                            node2 *newTemp = tempptr->next;
                            deleteNode(tempptr->seq, tempptr->name, tempptr->pname);
                            tempptr = newTemp;

                        }
                        else if (p >= tempptr->pstart && r <= tempptr->pending)
                        {
                            cout<<"2 Condition\n";
                            p = tempptr->pstart;
                            r = tempptr->pending;
                            node2 *newTemp = tempptr->next;
                            deleteNode(tempptr->seq, tempptr->name, tempptr->pname);
                            tempptr = newTemp;

                        }
                        else if (p >= tempptr->pstart && r > tempptr->pending)
                        {
                            cout<<"3 Condition\n";
                            p = tempptr->pstart;
                            node2 *newTemp = tempptr->next;
                            deleteNode(tempptr->seq, tempptr->name, tempptr->pname);
                            tempptr = newTemp;

                        }
                        else if (p < tempptr->pstart && r <= tempptr->pending)
                        {
                            cout<<"4 Condition\n";
                            r = tempptr->pending;

                            //cout<<"\ntemptr is "<<tempptr->name<<" "<<tempptr->pname<<endl;

                            node2 *newTemp = tempptr->next;
                            deleteNode(tempptr->seq, tempptr->name, tempptr->pname);
                            tempptr = newTemp;

                        }
                        else if (p < tempptr->pstart && r > tempptr->pending)
                        {
                            cout<<"5 Condition\n";
                            node2 *newTemp = tempptr->next;
                            deleteNode(tempptr->seq, tempptr->name, tempptr->pname);
                            tempptr = newTemp;

                        }
                    }
                    else
                        {
                            cout<<"else Condition\n";
                            cout<<"\ntemptr is "<<tempptr->seq<<endl;
                            system("pause");
                            tempptr = tempptr->next;
                            cout<<"\ntemptr is now "<<tempptr->seq<<endl;

                        }

                        cout<<"\nthe head is "<<head->seq<<" "<< head->name<<" "<<head->pname<<" next "<< head->next->seq<<endl;
                        cout<<"temptr is "<<tempptr->seq<<endl;
                        system("pause");
                    //check incase head is deleted
                }
                else
                {
                    //write to file;
                    cout<<"seq\t"<<p<<" to "<<r<<endl;


                    system("pause");


                    //cout<<"\nthe head is "<<head->seq<<" "<< head->name<<" "<<head->pname<<" pre "<< head->pre->seq<<endl;
                    system("pause");

                    p = head->pstart;
                    r = head->pending;
                    conname = head->name;
                    conpname = head->pname;
                    deleteNode(head->seq, conname, conpname);
                    tempptr = head;

                    continue;
                }
                //if (tempptr->pname != tempptr->pre->pname)//seperate db seq match
                //else    //same db seq match
                //if (tempptr->name != tempptr->pre->name)  //Next sequence starts
                //else

                //if it reaches next match seq q1,q2 then write to file and go back to head readjust p,r etc.
                //if (tempptr->next == NULL)

                //tempptr = tempptr->next;
            }

		}


	};











