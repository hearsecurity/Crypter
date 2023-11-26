/*
*  Simple Crypter created in c++
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

void write_output(string out_file, string encrypted) {

    ofstream fh;
    fh.open (out_file.c_str());
    fh << encrypted;
    fh.close();
}


string decrypt_file(string encrypted, string password) {

    string wrong = "Wrong password"; 

    unsigned first = encrypted.find("#");
    unsigned last = encrypted.find_last_of("#");
    string strNew = encrypted.substr (first,last-first);
    strNew.erase(remove(strNew.begin(), strNew.end(), '#'), strNew.end());

    unsigned first1 = encrypted.find("@");
    unsigned last2 = encrypted.find_last_of("@");
    string s = encrypted.substr (first1,last2-first1);
    s.erase(remove(s.begin(), s.end(), '@'), s.end());
    
    for(int i = 0; i < s.size(); i++) {

      s[i] = s[i] - 3; 
    }

    string pass = strNew; 

    for(int i = 0; i < s.size(); i++) {

      pass[i] = pass[i] - 5; 
    }

    if(password != pass) {

        return wrong; 
    }else{
        return s;
    }  
}

string encrypt_file(string plaintext, string password) {
    
    for(int i = 0; i < plaintext.size(); i++) {

        plaintext[i] = plaintext[i] + 3; 
    }

    for(int i = 0; i < password.size(); i++) {

        password[i] = password[i] + 5; 
    }

     
    string result = "@" + plaintext + "@" + "#" + password + "#"; 

    return result;
}

string remove_spaces(string input)
{
  int length = input.length();
  for (int i = 0; i < length; i++) {
     if(input[i] == ' ')
     {
        input.erase(i, 1);
         length--;
         i--;
     }
  }
  return input;
}

string read_plaintext(string plaintext) {

   ifstream f(plaintext.c_str()); 
   string str;

   if(f) {
      ostringstream ss;
      ss << f.rdbuf(); 
      str = ss.str();
   }

return str; 
}
int main(int argc, char **argv) {

     short int op; 
     string file; 
     string output; 
     string password;
     
     cout << "\n--------------------------------" << endl; 
     cout << "  SIMPLE ENCRYPTION ALGORITHM   " << endl; 
     cout << "--------------------------------" << endl;
     cout << "\nOperation 1: Encrypt" << endl; 
     cout << "Operation 2: Decrypt" << endl;  

     cout << "Type the operation: "; 
     cin >> op; 

     cout << "Type file name: "; 
     cin >> file; 

     cout << "Type ouput file name: "; 
     cin >> output;     

    cout << "Type the password: "; 
    cin >> password; 
    
    string plain = read_plaintext(file);
    string plaintext = remove_spaces(plain); 

    if(op == 1) {

        string encrypted = encrypt_file(plaintext, password);
        write_output(output, encrypted); 
    }else if(op == 2) {
        string decrypted = decrypt_file(plaintext, password); 
        write_output(output, decrypted);
    }

    

return 0; 
}