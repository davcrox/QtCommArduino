// Test of simple serial comms, using Thierry Schneider's
// Tserial class

#include <iostream>
#include <string>
#include <ctime>
#include <stdio.h>      /* printf */
#include <assert.h>     /* assert */
#include <stdlib.h>
#include "TSerial/TSerial.h"


// the com port we use
Tserial *com;

using namespace std;
// Read a string from the serial port if at least one char
// is available, otherwise wait for up to timeout seconds
// for something to show up.
string readSerial(int timeout=1) {
	const int SLEEPTIME = 100;  // milliseconds
	int maxtries = 1000*timeout/SLEEPTIME;
	int ntries = 0;
	int nchars = 0;
	string response;

	while ( !(nchars=com->getNbrOfBytes()) && (ntries<maxtries)) {
		ntries++;
		_sleep(100);
	}

	for(int i=0; i<nchars; i++) {
		response.push_back(com->getChar());
	}
	return response;
}
void OnPV(string serial,int virg)
{
    int Inputs[5];
    int counter=5;
    while(counter>0)
    {
        int input=serial[virg-3]-'0';
        input--;
        //cout<<"SET "<<(serial[virg-3])<<" TURNED TO "<<input<<" TO "<<serial[virg-1]<<endl;
        Inputs[input]=serial[virg-1]-'0';
        virg=virg-4;
        counter--;
    }
    system("cls");
    cout<<"1:"<<Inputs[0]<<endl;
    cout<<"2:"<<Inputs[1]<<endl;
    cout<<"3:"<<Inputs[2]<<endl;
    cout<<"4:"<<Inputs[3]<<endl;
    cout<<"5:"<<Inputs[4]<<endl;
}
void getLastPV(string serial)
{
    //cout << "response was->"<< serial << "<-"<< endl;
    if(serial.size()>20)
    {
        int found=0;
        int serialNumber=serial.size();
        int minor=1;
        while(found==0 && minor<serial.size())
        {
            char compare=serial[serialNumber-minor];
            //cout<<compare<<endl;
            if(compare==';')
            {
                OnPV(serial,serialNumber-minor);
                found=1;
            }
            else
            {
                minor++;
            }
        }
    }
}

// nasty little loop to try it out
int main()
{
	com = new Tserial();
	assert(com);
	com->connect("COM9", 9600, spNONE);
	char buffer[]="+20";
    com->sendArray(buffer, 3);
	string cmd;
	/*for(;;) {
		cout << "command or R to read or Q to quit->" ;
		cin >> cmd;
		cout << endl;

		if (cmd == "R") {
                while(true){
                    cout << "response was->"<< readSerial() << "<-"<< endl;
                    getLastPV(readSerial());
                }

		} else if (cmd == "Q") {
			return 0;
		} else {
			com->sendArray((char*)cmd.c_str(), cmd.size());
			com->sendChar('\n');
			while(true)
            {
                //cout << "response was->"<< readSerial() << "<-"<< endl;
                getLastPV(readSerial());
            }
		}
  	}*/

}
