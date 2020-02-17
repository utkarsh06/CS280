//CS 280 Section 01 
//Utkarsh Gaur
//Lexical analyzer
#include <stdio.h>
#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include <cstdlib>
#include <map>
#include <iterator>
#include <stdlib.h>
#include "lex.h"
#include <vector>
#include <algorithm>

using namespace std;
int main( int argc , char *argv[]){
    
    int linenum = 0;
    int& linenumr = linenum;
    int tok_num = 0;
    int num_of_files =0;
    
    vector<string> lxm_id;
    vector<string> lxm_str;
    vector<string> lxm_int;
    vector<string> :: iterator itr;
    vector<string> :: iterator it1;
    vector<string> :: iterator it2;
    vector<Token> lxm;
    it1 = std::unique(lxm_id.begin(), lxm_id.end());
    
    bool v = false;
    bool id = false;
    bool c = false;
 
    
    for(int i = 1; i < argc; i++){ 
        
        if(argv[i][0] == '-'){ //if flagged
            string arg = argv[i];
            if(arg != "-v" && arg != "-consts"  && arg != "-ids" ){
                cerr << "UNRECOGNIZED FLAG " << argv[i] << endl;
                return -1;
            }
        }
        
       else { //It is a file
            
            
            num_of_files += 1;
            
            }
        
    }
    
    
   std:: string arg1;
   for(int i = 1; i < argc; i++){
        
        arg1 = argv[i];
        
        if(arg1 ==  "-v"){
            
            v = true;
            
      }
      
        if(arg1 == "-consts"){
            c = true;
        } 
   
        if(arg1 == "-ids"){
            id = true;
        }
      
    }
    
    
 
     if(num_of_files > 1){
                 cerr << "ONLY ONE FILE NAME ALLOWED" << endl;
                 return -1;
             }
    
     else if (num_of_files == 1){ 
                 // there is one file
                 ifstream infile;
                 infile.open(argv[argc-1]);

                 if( infile.is_open() == false ) {
                      cerr << "CANNOT OPEN " << argv[argc-1] << endl;
                      return -1;
                  }
         
                 Lex tok;
                 ifstream& in = infile;

                 tok = getNextToken( in ,linenumr);
                 
                 while(tok != DONE && tok!= ERR){
                      
                      lxm.push_back(tok.GetToken());
                      if(tok.GetToken() == ID){
                          lxm_id.push_back(tok.GetLexeme());
                      }
                      if(tok.GetToken() == STR){
                          lxm_str.push_back(tok.GetLexeme());
                      }
                     
                      if(tok.GetToken() == INT){
                          lxm_int.push_back(tok.GetLexeme());
                      
                      }
                     
                      
                      //cout << tok <<endl;
                     
                      if(v){
                       
                       cout << tok <<endl;
                
                     }
                      
                      
                      
                      tok = getNextToken(in, linenumr);
                      tok_num++;
                      if(tok == ERR){
                      if(lxm[lxm.size() -1] == STR){
                      cout<< "Error on line " << linenumr << " " << "(\"" <<  tok.GetLexeme() << ")" <<endl;
                      return -1;
                      }
                         
                      cout<< "Error on line " << linenumr << " " << "(" <<  tok.GetLexeme() << ")" <<endl;
                      return -1;
                      }
                 }
                  
                  
                  infile.close();
         
                   if(id){
                       
                       
                        
                       if(lxm_id.size() > 0 ){
                        sort(lxm_id.begin(), lxm_id.end());
                        cout << "IDENTIFIERS: " ;
                        for (itr = lxm_id.begin(); itr != lxm_id.end(); ++itr) {
                                    cout << *itr; 
                             if(itr != lxm_id.end() -1){
                                    cout << ", " ;
                             }
                             else{
                                 cout << "";
                             }
                                    
                        }
                       
                       cout <<endl;
                        }  
                     } 
         
         
                  if(c){ 
                      
                      
                      if (lxm_str.size()>0){
                          sort(lxm_str.begin(), lxm_str.end());
                          cout << "STRINGS:" <<endl;
                          for(itr = lxm_str.begin(); itr != lxm_str.end(); ++itr )
                              cout << *itr <<endl;
                      }
                       
                  
                  } 
                 

                if(linenum>=1){
                    
                    cout<< "Lines: " << linenum << endl;
                    cout<< "Tokens: " <<tok_num <<endl;
                }
                else{
                    cout<< "Lines: " << linenumr << endl;
                }                  

                


              


        }
     
    else{        Lex tok;
                 istream& in = cin;

                 tok = getNextToken( in ,linenumr);
                 
                 while(tok != DONE && tok!= ERR){
                      
                      lxm.push_back(tok.GetToken());
                      if(tok.GetToken() == ID){
                          lxm_id.push_back(tok.GetLexeme());
                      }
                      if(tok.GetToken() == STR){
                          lxm_str.push_back(tok.GetLexeme());
                      }
                     
                      if(tok.GetToken() == INT){
                          lxm_int.push_back(tok.GetLexeme());
                      
                      }
                     
                      
                      //cout << tok <<endl;
                     
                      if(v){
                       
                       cout << tok <<endl;
                
                     }
                      
                      
                      
                      tok = getNextToken(in, linenumr);
                      tok_num++;
                      if(tok == ERR){
                      if(lxm[lxm.size() -1] == STR){
                      cout<< "Error on line " << linenumr << " " << "(\"" <<  tok.GetLexeme() << ")" <<endl;
                      return -1;
                      }
                         
                      cout<< "Error on line " << linenumr << " " << "(" <<  tok.GetLexeme() << ")" <<endl;
                      return -1;
                      }
                 }
                  
                  
                  
         
                   if(id){
                       
                       
                        
                       if(lxm_id.size() > 0 ){
                        lxm_id.erase(
                        std::unique(lxm_id.begin(), lxm_id.end()),
                        lxm_id.end());
                        sort(lxm_id.begin(), lxm_id.end());
                        cout << "IDENTIFIERS: " ;
                        for (itr = lxm_id.begin(); itr != lxm_id.end(); ++itr) {
                                    cout << *itr; 
                             if(itr != lxm_id.end() -1){
                                    cout << ", " ;
                             }
                             else{
                                 cout << "";
                             }
                                    
                        }
                       
                       cout <<endl;
                        }  
                     } 
         
         
                  if(c){ 
                      
                      
                      if (lxm_str.size()>0){
                          sort(lxm_str.begin(), lxm_str.end());
                          cout << "STRINGS:" <<endl;
                          for(itr = lxm_str.begin(); itr != lxm_str.end(); ++itr )
                              cout << *itr <<endl;
                      }
                      
                      if (lxm_int.size() >0){
                          sort(lxm_int.begin(), lxm_int.end(),greater<string>());
                          cout << "INTEGERS:" <<endl;
                          for(it2 = lxm_int.begin(); it2 != lxm_int.end(); ++it2 )
                              cout << *it2 <<endl;
                      
                      }
                  
                  } 
                 

                if(linenum>=1){
                    
                    cout<< "Lines: " << linenum << endl;
                    cout<< "Tokens: " <<tok_num <<endl;
                }
                else{
                    cout<< "Lines: " << linenumr << endl;
                }                  

                


              


        }
    
    
     return 0;
}
