#include <sstream>
#include "list.hpp"
#include "iostream"

int main() {
    //testing list pushFront/popFront/pushBack/clear
    {
        int length=0;
        list<int, int> Seq(-1,-1);
        std::string sequenceString = "Default: -1\t-1\n";
        std::stringstream testStream;
        testStream << Seq;

        if (!Seq.isEmpty())std::cout << "Error in isEmpty sequence function! list is not empty!"<< std::endl;
        if (Seq.getLength() != length)std::cout << "Error in sequence length. Length is not "<<length<<". Length: "<<Seq.getLength() << std::endl;
        if (sequenceString != testStream.str()) std::cout << "Error in list to string conversion! String should be " << sequenceString<<" instead of "<<testStream.str() << std::endl;


        Seq.pushFront(1, 3);
        sequenceString = "Default: -1\t-1\n1\t3\n";
        length++;
        testStream.str(std::string());
        testStream << Seq;

        if (sequenceString != testStream.str()) std::cout << "Error in list to string conversion! String should be " << sequenceString<<" instead of "<<testStream.str() << std::endl;
        if (Seq.isEmpty())std::cout << "Error in isEmpty sequence function! list is empty!" << std::endl;
        if (Seq.getLength() != length)std::cout << "Error in sequence length. Length is not "<<length<<". Length: "<<Seq.getLength() << std::endl;


        Seq.popFront();
        length--;

        if (!Seq.isEmpty())std::cout << "Error in isEmpty sequence function! list is not empty!" << std::endl;
        if (Seq.getLength() != length)std::cout << "Error in sequence length. Length is not "<<length<<". Length: "<<Seq.getLength() << std::endl;


        sequenceString = "Default: -1\t-1\n";
        testStream.str(std::string());
        testStream << Seq;

        if (sequenceString != testStream.str()) std::cout << "Error in list to string conversion! String should be " << sequenceString<<" instead of "<<testStream.str() << std::endl;


        Seq.pushBack(1, 3);
        length++;
        sequenceString = "Default: -1\t-1\n1\t3\n";
        testStream.str(std::string());
        testStream << Seq;

        if (sequenceString != testStream.str()) std::cout << "Error in list to string conversion! String should be " << sequenceString<<" instead of "<<testStream.str() << std::endl;
        if (Seq.isEmpty())std::cout << "Error in isEmpty sequence function! list is empty!" << std::endl;
        if (Seq.getLength() != length)std::cout << "Error in sequence length. Length is not "<<length<<". Length: "<<Seq.getLength() << std::endl;


        Seq.clear();

        if (!Seq.isEmpty())std::cout << "Error in isEmpty sequence function! list is not empty!" << std::endl;
        if (Seq.getLength() != 0)std::cout << "Error in sequence length. Length is not 0. Length: "<<Seq.getLength() << std::endl;


        sequenceString = "Default: -1\t-1\n";
        testStream.str(std::string());
        testStream << Seq;

        if (sequenceString != testStream.str()) std::cout << "Error in list to string conversion! String should be " << sequenceString<<" instead of "<<testStream.str() << std::endl;
    }

    //testing list getIndexOccurrence/pop/popAll
    {
        int length;
        list<int, int> Seq(-1,-1);
        std::string sequenceString = "Default: -1\t-1\n2\t3\n1\t3\n";
        std::stringstream testStream;
        Seq.insert(1,3, Seq.begin());
        Seq.insert(2,3, Seq.begin());
        Seq.insert(1,3, Seq.begin());
        length=Seq.getLength();

        if(2!=Seq.getNumberOfOccurrences(1)) std::cout<<"Error in getNumberOfOccurrences! Should be 2 instead of "<<Seq.getNumberOfOccurrences(1)<<std::endl;
        Seq.popFront();
        length--;
        testStream << Seq;
        if (Seq.getLength() != length) std::cout << "Error in pop function! Wrong number of nodes. Should be "<<length<<" instead of "<<Seq.getLength()<<std::endl;
        if (sequenceString != testStream.str()) std::cout << "Error in pop function! Wrong node order. Should be "<<sequenceString<<" instead of "<<testStream.str()<<std::endl;



        Seq.pop(Seq.find(1));
        Seq.pop(Seq.find(2));

        length-=2;
        sequenceString="Default: -1\t-1\n";
        testStream.str(std::string());
        testStream<<Seq;

        if (Seq.getLength() != length) std::cout << "Error in pop function! Wrong number of nodes. Should be "<<length<<" instead of "<<Seq.getLength()<<std::endl;
        if (sequenceString != testStream.str()) std::cout << "Error in pop function! Wrong node order. Should be "<<sequenceString<<" instead of "<<testStream.str()<<std::endl;


        Seq.pushFront(1, 3);
        Seq.pushFront(2, 3);
        Seq.pushFront(1, 3);
        Seq.pop(Seq.find(1,1));
        length+=2;
        sequenceString="Default: -1\t-1\n1\t3\n2\t3\n";
        testStream.str(std::string());
        testStream<<Seq;

        if (Seq.getLength() != length) std::cout << "Error in pop function! Wrong number of nodes. Should be "<<length<<" instead of "<<Seq.getLength()<<std::endl;
        if (sequenceString != testStream.str()) std::cout << "Error in pop function! Wrong node order. Should be "<<sequenceString<<" instead of "<<testStream.str()<<std::endl;

        Seq.pushBack(1,3);
    }

    std::cout<<"All tests passed!"<<std::endl;
    getchar();
}