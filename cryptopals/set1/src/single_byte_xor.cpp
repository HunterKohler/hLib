#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using std::vector;
using std::string;
using std::cout;
using std::ifstream;


string xor_decode(const string& s, char c) {
    string r;
    for(int i = 0; i < s.length(); i += 2) {
        r += (char) (std::stoi(s.substr(i,2),nullptr,16) ^ (int)c);
    }
    return r;
}

bool valid(const string& s) {
    return s.find("Now that the party is jumping") != string::npos;
    // int letters = 0;
    // for(char c: s) {
    //     if(('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'))
    //         letters++;
    // }
    // return letters > 20;
}

int main(int argc, char const *argv[]) {
    ifstream fin("challengedata.txt");

    string s;
    while(fin >> s) {
        for(int i = 0; i < 256; i++) {
            string encoded = xor_decode(s,(char) i);

            if(valid(encoded)) {
                cout << s << "\n" << i << "\n" << encoded;
            }
        }
    }
}
