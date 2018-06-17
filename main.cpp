#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <algorithm>

using namespace std;

class SerialNumberHelper
{
    /** Self-defined Base System Representation
     *  the Demo here shows a 30-base system.
     *  */
private:
    static const vector<char> r; //{ 'q', 'w', 'e', '8', 's', '2', 'd', 'z',
    //'x', '9', 'c', '7', 'p', '5', 'k', '3', 'm', 'j', 'u', 'f', 'r', '4', 'v', 'y', 't', 'n', '6', 'b', 'g', 'h' };

    /** Separate bit */
    static const char b;

    /** Base */
    static const int binLen;

    /** SerialCode Length */
    static const int s = 10;

    // Generate Code with long type ID

public:

    static string ToSerialCode(long id)
    {
        string sSerialID;
        cout << "b" << binLen << endl;
        try {

            char *buf = new char[35];
            int charPos = 0;

            while ((id / binLen) > 0) {
                int ind = (int) (id % binLen);
                buf[charPos++] = r[ind];
                id /= binLen;
            }
            buf[charPos] = r[(int) (id % binLen)];
            cout << "Buf " << buf << endl;
            string str(buf, charPos + 1);
            reverse(str.begin(), str.end());

            cout << "Temp SerialID "<< str << endl;
            //Make-up bits
            if (str.size() < s) {
                string sCode = "";
                srand(time(NULL));
                sCode.append(&b);

                for (int i = 1; i < s - str.size(); i++) {
                    sCode.append(&r[rand() % binLen], 1);
                }
                str += sCode;
            }
            sSerialID = str;
        }
        catch (std::exception& ex)
        {
           cout  << "ERROR" << ex.what() << endl;
        }
        return sSerialID;
    }

    /// Generate ID with Code

public:

    static long CodeToId(string code)
    {
        long res = 0L;
        for (int i = 0 ; i < code.size(); i++)
        {
            cout << "Number " << i << " " << code[i] << endl;
            int ind = 0;
            for (int j = 0; j < binLen; j++)
            {
                if (code[i] == r[j])
                {
                    ind = j;
                    break;
                }
            }
            if (code[i] == b)
            {
                break;
            }
            if (i > 0)
            {
                cout << "Accu" << i << endl;
                res = res * binLen + ind;
            }
            else
            {
                res = ind;
            }
        }
        return res;
    }
};


const std::vector<char> SerialNumberHelper::r = { 'q', 'w', 'e', '8', 's', '2', 'd', 'z', 'x', '9', 'c', '7', 'p', '5', 'k', '3', 'm', 'j', 'u', 'f', 'r', '4', 'v', 'y', 't', 'n', '6', 'b', 'g', 'h' };

const int SerialNumberHelper::binLen = SerialNumberHelper::r.size();

const char SerialNumberHelper::b     = 'a';

int main()
{
    string myCode = SerialNumberHelper::ToSerialCode(100);
    cout << myCode << endl;
    cout << SerialNumberHelper::CodeToId(myCode) << endl;
}