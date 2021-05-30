#include <iostream>
using namespace std;
struct Node
{
    char data;
    Node * children;
    int wordEnd;
    Node *nextNode;
    Node()
    {
        this->data= '*';
        this->children=nullptr;
        this->nextNode=nullptr;
        this->wordEnd=-1;
    }
    Node(char data, Node * child,Node * next,int e)
    {
        this->data= data;
        this->children=child;
        this->nextNode=next;
        this->wordEnd=e;
    }
};
class SuffixNode
{
public:
    Node* nodesList= new Node();
    SuffixNode()
    {
        this->nodesList->children=nullptr;
        this->nodesList->data=' ';
        this->nodesList->nextNode=nullptr;
    }
    SuffixNode(char data, Node * child,Node * next)
    {
        this->nodesList->data= data;
        this->nodesList->children=child;
        this->nodesList->nextNode=next;
    }
};
class SuffixTrie
{
private :
    SuffixNode * root= new SuffixNode();
public:
    SuffixTrie() {}
    SuffixTrie(char word[])
    {
        int size=0;
        for(int i=0 ; word[i]!=NULL ; i++)
        {
            size++;
        }
        for(int i=0 ; i<size ; i++)
        {
            Node * currentNode= this->root->nodesList;
            for(int j=i ; j<size ; j++)
            {
//the root has no node containing the new inserted character
                if(currentNode->nextNode==nullptr)
                {
                    Node *temp= new Node(word[j], nullptr,nullptr,-1); //will be added in currentNode->nextNode
                    if(j==size-1)
                        temp->wordEnd=i;
                    j++;
                    Node *pointer=new Node();
                    Node *temp2= new Node(word[j],nullptr,nullptr,-1);
                    pointer=temp2;
                    j++;
                    temp->children=pointer;
                    while(j<size)
                    {
                        temp2= new Node(word[j],nullptr,nullptr,-1);
                        pointer->children=temp2;
                        if(j==size-1)
                            pointer->wordEnd=i;
                        j++;
                        pointer=pointer->children;
                    }
                    currentNode->nextNode= temp;
                    break;
                }
                else
                {
                    if(currentNode->nextNode->data== word[j])//there exists a node from the root with the inserted char
                    {
                        bool cond=false;
                        Node *pointer= new Node();
                        pointer=currentNode->nextNode;
compare:
                        while(pointer->children!=nullptr)
                        {
                            if(pointer->children->data==word[j+1]&&j+1!=(size-1))
                            {
                                j++;
                                pointer=pointer->children;
                            }
                            else if(j+1==(size-1))
                            {
                                Node *next= new Node('$', nullptr, nullptr,i);
                                pointer->children->nextNode=next;
                                break;
                            }
                            else
                            {
                                if(pointer->children->nextNode!=nullptr)
                                {
                                    if(pointer->children->nextNode->data==word[j+1])//if this child is not equal to the char but its sibling is
                                    {
                                        j++;
                                        pointer=pointer->children->nextNode;
                                        goto compare;
                                    }
                                }
                                Node *next= new Node(word[j+1], nullptr, nullptr,-1);
                                if(pointer->children->nextNode!=nullptr)
                                {
                                    Node *currentNext= new Node();
                                    currentNext=pointer->children;
                                    pointer->children->nextNode=currentNext;
                                    while(currentNext->nextNode!=nullptr)
                                    {
                                        currentNext=currentNext->nextNode;
                                    }
                                    currentNext->nextNode=next;
                                }
                                else
                                    pointer->children->nextNode=next;
                                cond=true;
                                j+=2;
                                pointer=pointer->children->nextNode;
                                break;
                            }
                        }
                        if(cond)
                        {
                            Node *temp= new Node();
                            temp= new Node(word[j],nullptr, nullptr,-1);
                            Node *p= new Node();
                            p=temp;
                            pointer->children=p;
                            j++;
                            while(j<size)
                            {
                                temp= new Node(word[j],nullptr, nullptr,-1);
                                if(j==(size-1))
                                    temp->wordEnd=i;
                                p->children=temp;
                                p=p->children;
                                j++;
                            }
                            break;
                        }
                        break;
                    }
                    else
                    {
                        j--;
                        currentNode=currentNode->nextNode;
                    }
                }
            }
        }
    }
    void Search(char s[])
    {
        Node *current=new Node();
        current=root->nodesList;
        int i=0;
        while(current->nextNode!=nullptr)
        {
            if(current->nextNode->data==s[i])
            {
                Node *pointer=new Node();
                pointer= current->nextNode;
                i++;
                while(s[i]==pointer->children->data)
                {
                    i++;
                    pointer=pointer->children;
                }
                if(pointer->children->nextNode!=nullptr&&pointer->children->nextNode->data==s[i])
                {
                    current=pointer->children;
                    continue;
                }
                while(pointer!=nullptr)
                {
                    if(pointer->wordEnd!=-1)
                        cout<<pointer->wordEnd<<" ";
                    if(pointer->nextNode!=nullptr&&pointer->nextNode->wordEnd!=-1)
                        cout<<pointer->nextNode->wordEnd<<" ";
                    else if (pointer->nextNode!=nullptr)
                    {
                        Node * newPointer=new Node();
                        newPointer=pointer->nextNode;
nextNodeChildren:
                        Node *newChild= new Node();
                        newChild=newPointer->children;
                        while(newChild!=nullptr)
                        {
                            if(newChild->wordEnd!=-1)
                                cout<<newChild->wordEnd<<" ";
                            if((newChild->nextNode!=nullptr)&&newChild->nextNode->wordEnd!=-1)
                                cout<<newChild->nextNode->wordEnd<<" ";
                            newChild=newChild->children;
                        }
                        if(newPointer->nextNode!=nullptr)
                        {
                            newPointer=newPointer->nextNode;
                            goto nextNodeChildren;
                        }
                    }
                    pointer=pointer->children;
                }
                cout<<endl;
                break;
            }
            else
                current=current->nextNode;
        }
    }
};
int main()
{
    SuffixTrie t("bananabanaba$");

    t.Search("ana"); // Prints: 1 3 7
    t.Search("naba"); // Prints: 4 8
    return 0;
}
