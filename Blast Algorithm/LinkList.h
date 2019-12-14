

//For Breaking queries into k-mers and storing in Linklist

#include <iostream>
#include <cstring>

using namespace std;

struct node
		{
			string seq;
			string name;
			int start;
			int ending;
			node *next;
			node *pre;
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
			   /* if ( tempptr->pre != NULL)
                    cout<< tempptr->pre->seq<< "\t";*/
				cout<<tempptr->seq << ", " << tempptr->name <<", "<<tempptr->start<<", "<<tempptr->ending<<endl;
				tempptr = tempptr->next;
			}
			cout<<"length is " << length;
		}



	};
