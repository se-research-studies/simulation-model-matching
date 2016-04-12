#include <stdio.h>
#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include "../../src/RecordedSequence.h"
#include "../../src/Correspondence.h"

using namespace std;

int main(int argc, const char* argv[])
{
    RecordedSequence sim("simcrec", 0, 100);
    RecordedSequence r0("realrec0", 1, 2);
    RecordedSequence r1("realrec1", 2, 3);
    list<RecordedSequence> realRecordings;
    realRecordings.push_back(r0);
    realRecordings.push_back(r1);

    cout << "----- I/O Part -----" << endl;

    Correspondence corr(sim, realRecordings);
    cout << "toString(): " << corr.toString() << endl;
    cout << "getSimRecording().toString(): " << corr.getSimRecording().toString() << endl;
    
    list<RecordedSequence> copiedRecordings;
    corr.getRealRecordings(copiedRecordings);
    for (RecordedSequence rs : copiedRecordings) 
    {
        cout << "copiedRecording: " << rs.toString() << endl;
    }
    
    cout << "----- Serialization Part -----" << endl;
    
    // save to file
    {
        ofstream ofs("filename.corr");
        boost::archive::text_oarchive oa(ofs);
    	oa << corr;
        // archive and stream closed when destructors are called
    }


    Correspondence cloned;
    cout << "cloned: " << cloned.toString() << endl;

    // load from file
    {
        ifstream ifs("filename.corr");
        boost::archive::text_iarchive ia(ifs);    
    	ia >> cloned; 
        // archive and stream closed when destructors are called
    }
    
    cout << "restored: " << cloned.toString() << endl;
    
}
