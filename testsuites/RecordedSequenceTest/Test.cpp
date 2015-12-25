#include <stdio.h>
#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include "../../src/RecordedSequence.h"


using namespace std;

int main(int argc, const char* argv[])
{
    string filename = "simcrec";
    int startFrame = 0;
    int endFrame = 100;
    RecordedSequence sim(filename, startFrame, endFrame);
    
    cout << "----- I/O Part -----" << endl;
    
    cout << sim.toString() << endl;
    
    cout << "----- Serialization Part -----" << endl;
    
    // save to file
    {
        ofstream ofs("filename.rs");
        boost::archive::text_oarchive oa(ofs);
    	oa << sim;
        // archive and stream closed when destructors are called
    }

    RecordedSequence cloned;
    cout << cloned.toString() << endl;

    // load from file
    {
        ifstream ifs("filename.rs");
        boost::archive::text_iarchive ia(ifs);    
    	ia >> cloned; 
        // archive and stream closed when destructors are called
    }
    
    cout << cloned.toString() << endl;
}
