/*
CS280 Section 1
Utkarsh Gaur
This program does a subsituition encryption
*/



#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include <cstdlib>
using namespace std;

void csr_dict();
char ROT13(char ch1);

int main(int argc, char *argv[]){
  //std::string arg1;
  std::string not_command;
    
  if( argc ==  1){
      cout << "MISSING COMMAND" << endl;
      return 0;
  }
    
  std::string arg1(argv[1]);
  if ((arg1 != "-r") && (arg1 != "-g") && (arg1 != "-e") && (arg1 != "-d")){
      not_command =  arg1 + " NOT A VALID COMMAND";
      cout<< not_command << endl;
      return 0;
  }
    
    
  if (arg1 == "-r"){ 
      
      char ch;
      
      if(argc < 3){
            
          while(!cin.eof()){ // Not print any value after a space <---------------------------------------------------------- here
              cin >> ch;
              cout << ROT13(ch); // 
          }
      }
  
      else{
       
          std:: string arg2, er, r13cryp; 
          arg2 = argv[2];
          
          ifstream infile;
          infile.open(argv[2]);
          
          if( infile.is_open() == false ) {
              er = arg2 + "FILE COULD NOT BE OPENED";
              cerr<< er << endl;
              return -1;
              }
          infile >> r13cryp;
          infile.close();
          
          
          
          for(int i =0; i < r13cryp.length(); i++){ 
              
              ch = r13cryp[i];
              cout << ROT13(ch); // does not print any value after space <-------------------------------------------------------- here
          }
       }
          
      }
      
  if(arg1 == "-g"){ 
      csr_dict();
  }
      
  
 return 0; 
}


void csr_dict(){
     

    //Declaring the variables and arrays
    int r_index, temp, tmp;
    int alpha[26], beta[26];
    char ch1, ch2;
   
  
    // setting the random seed value as time
    srand(time(NULL));
    
    //assigning the values of 0 to 25 to the array
    for( int i = 0; i<26; i++){
        beta[i] = i;
        alpha[i] = i;
        
    }
    //generating a random number between 0 and 25
    for(int i = 0; i <26 ; i++){
        
        r_index = rand()%(26-i)+i ; 
        //Swapping the values of the number at the random index with the number at the ith index
        temp = alpha[i];
        alpha[i] = alpha[r_index];
        alpha[r_index] =temp;
        
    }
    
    
    //printing out random character from a to z
    for(int i=0;i<26; i++){
       if(alpha[i] == beta[i]){
           tmp = alpha[i];
           alpha[i] =alpha[i+1];
           alpha[i+1]  = tmp;
       }
       if(alpha[i] == beta[i] && alpha[i] ==25){
           tmp = alpha[i];
           alpha[i] =alpha[i-1];
           alpha[i-1]  = tmp;
       }
           
       
        ch1 = 'a' +  alpha[i]; //Askii value of a + random number
        ch2 = 'a' + beta[i];
        
        cout << ch2; //printing a random character at one line each
        cout << "";
        cout << ch1 << endl; 
    }
    
   
}


char ROT13(char ch1)
{
int r_ch;
char ch = ch1;
    
    if((int(ch) >= 65) && (int(ch) <= 90)){ 

      if(int(ch) <= 77){
        
        r_ch = ch + 13;
        return char(r_ch);
      }
      else{
        r_ch = ch - 13;
         return char(r_ch);
      }
    }
    
    else if((int(ch) >= 97) && (int(ch) <= 122)){

      if(int(ch) <= 109){
        r_ch = ch + 13;
           return char(r_ch);
      }
      else{
        r_ch = ch - 13;
           return char(r_ch);
      }
    }
    
    else{
      
      return ch;
    }

}
