#include <iostream>
using namespace std;


class SuffixArray
{


    int size=0;//size of both arrays
    char *toBeSorted;//the original String
    int *suffixArr;//the sorted suffix array
public:
    SuffixArray() {}


    SuffixArray(char arr[])
    {
        for(int i=0 ; arr[i]!=NULL ; i++)
            size++;


        toBeSorted= new char(size);
        suffixArr= { new int[size]{} };


        for(int i=0 ; i<size ; i++)
            toBeSorted[i]=arr[i];


    }
    ConstructUsingPrefixDoubling()
    {
        char distinct[26]= {'&'}; //contains all distinct elements
        int counter=0;//number of distinct characters
        for(int i=0 ; i<size ; i++)
        {
            for(int j=0 ; j<26 ; j++)
            {
                if(j==counter)
                {
                    distinct[counter]=toBeSorted[i];
                    counter++;
                    break;
                }
                else if(toBeSorted[i]==distinct[j])
                    break;
                else
                    continue;
            }
        }
        int minimum;
        char temp;//sorts the distinct characters ascending
        for(int i=0 ; i<counter-1 ; i++)
        {
            minimum=i;
            for (int j =i+1 ; j<counter ; j++)
            {
                if(distinct[j]<distinct[minimum])
                    minimum=j;
            }
            temp=distinct[i];
            distinct[i]=distinct[minimum];
            distinct[minimum]=temp;
        }


        int k=0;
        bool cond=false;
        int * prev{ new int[size]{} };//stores the last index to every suffix
        int *current{ new int[size]{} };//to store the new index of the suffixes
        int *checkIndex{ new int[size]{} };//has the number of suffixes in each index
        while(!cond) //checks if the array needs more sorting(more than one suffix have the same index)
        {


            int *finishCheck{ new int[size]{} };//array to store the number of suffixes at each index is intialized to zero
            if(k==0)
            {
                for(int i=0 ; i<size ; i++)
                {


                    for(int j=0 ; j<counter ; j++)
                    {
                        if(toBeSorted[i]==distinct[j])
                        {
                            prev[i]=j;
                            finishCheck[j]++;//increment the number of suffixes at that index
                            break;
                        }
                    }
                }


            }
            else
            {
                int c=0;//index counter to see if all the suffixes were given index
                int ind=0;//current index
                int doneCharacters=0;//characters given index
                while(doneCharacters<size)
                {
                    if(checkIndex[ind]==1)//if this index has only 1 suffix we assign this suffix with the current index counter
                    {
                        for(int i=0; i<size ; i++)
                        {
                            if(prev[i]==ind)
                            {
                                current[i]=c;
                                finishCheck[c]++;
                                break;
                            }
                        }
                        c++;
                        doneCharacters++;
                    }
                    else
                    {
                        int leftToAssign=checkIndex[ind];


                        while(leftToAssign>0)
                        {
                            int minimumChar;
                            bool first=true;
                            bool restIsEqual=true;
                            int eq=1;
                            for(int i=0 ; i<size ; i++)
                            {


                                if(prev[i]==ind)
                                {
                                    if(first)
                                    {
                                        minimumChar=i;
                                        first=false;
                                    }
                                    else
                                    {
                                        if(prev[i+k]<prev[minimumChar+k])
                                        {
                                            restIsEqual=false;
                                            minimumChar=i;
                                        }
                                        else if(prev[i+k]==prev[minimumChar+k])
                                            eq++;
                                    }
                                }
                            }
                            if(restIsEqual)
                            {
                                for(int i=0 ; i<size ; i++)
                                {
                                    if(prev[i]==ind&&prev[i+k]==prev[minimumChar+k])
                                    {
                                        current[i]=c;
                                        prev[i]=-1;
                                    }


                                }


                                doneCharacters+=eq;
                                finishCheck[c]+=eq;
                                leftToAssign-=eq;
                            }
                            else
                            {
                                doneCharacters++;
                                finishCheck[c]++;
                                prev[minimumChar]=-1;
                                current[minimumChar]=c;//assigning current index counter to the smallest suffix of this index
                                leftToAssign--;
                            }
                            c++;//incrementing current index counter
                        }
                    }
                    ind++;
                }
                for(int i=0 ; i<size ; i++)
                    prev[i]=current[i];
            }
            k++;
            for(int i=0 ; i<size ; i++) //checks that there is not more than one suffix with the same index
            {
                if(finishCheck[i]!=1)//if this index has more than or less than 1 suffix we break and the cond stays false
                    break;
                else if(i==size-1)
                    cond=true;
            }


            checkIndex=finishCheck;


        }
        for(int i=0; i<size ; i++)
        {
            for(int j=0 ; j<size ; j++)
            {
                if(current[j]==i)
                    suffixArr[i]=j;


            }
        }

    }
    Print()
    {
        for(int i=0 ; i<size ; i++)
            cout<<suffixArr[i]<<" ";
    }
};
int main()
{
    SuffixArray t("ACGACTACGATAAC$");

    t.ConstructUsingPrefixDoubling();

    t.Print(); // Prints:  14 11 12  0  6  3  9 13  1  7  4  2  8 10  5

    return 0;
}
