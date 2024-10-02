#include <iostream>
#include <fstream>>
#include <iomanip>

using namespace std;

int main()
{
    remove("charset.h");
    const int filesize = 0x800;
    int index = 0;
    ifstream F;
    ofstream outF;
    F.open("savpe.bin");
    outF.open("charset.h");
    outF << "// font 7*5   CP866" << endl;
    outF << "const unsigned char FontTable[256][5] = {" << endl;
    char * buf = new char[filesize];
    F.read(buf, filesize);
    for(int i = 0; i <= 255; i++) {
        outF << "{ ";
        for(int n = 0; n < 5; n++) {
            uint8_t current = buf[index];
            current = ~current;
            outF << "0x" << hex << uppercase << setw(2) << setfill('0') << int(current) << dec;
            if(n != 4) outF << ',';
            outF << ' ';
            index++;
        }
        outF << "}, // ";
        if(i > 0x1F && i != 0x7F) outF << uint8_t(i) << ' ';
        else outF << ' ' << ' ';
        outF << "0x" << hex << uppercase << setw(2) << setfill('0') << i << endl;
        index += 3;
    }
    outF << "};" << endl;
    //cout << "Hello world!" << endl;
    return 0;
}
