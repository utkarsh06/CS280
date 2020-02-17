#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <map>
#include "lex.h"
#include <iterator>

using namespace std;

Lex getNextToken(istream& in, int& linenumr){
    
    std:: map<string, Token> :: iterator it;
    
    static std:: map<string, Token> myMap;
     myMap.insert(pair<string,Token>("print", PRINT));
     myMap.insert(pair<string,Token>("let", LET ));
     myMap.insert(pair<string,Token>("if", IF ));
     myMap.insert(pair<string,Token>("begin", BEGIN ));
     myMap.insert(pair<string,Token>("end", END ));
     myMap.insert(pair<string,Token>("+", PLUS ));
     myMap.insert(pair<string,Token>("-", MINUS ));
     myMap.insert(pair<string,Token>("*", STAR));
     myMap.insert(pair<string,Token>("/", SLASH ));
     myMap.insert(pair<string,Token>( "(", LPAREN ));
     myMap.insert(pair<string,Token>(")", RPAREN ));
     myMap.insert(pair<string,Token>(";", SC ));
     myMap.insert(pair<string,Token>("INT", INT ));
     myMap.insert(pair<string,Token>("STR", STR ));
     myMap.insert(pair<string,Token>("!", BANG ));
    char ch;
    std:: string lexeme = "";
    
    enum LexState { START, STID, STSTRING, STINT, STSLASH, STCOMMENT} 
    lexstate = START;
    
    while(in.get(ch)){
        
       // if(in.eof()){}
        
        
           if(ch == '\n'){
                ++linenumr;
                  
                }
        
        switch(lexstate){
            
        case(START):
                
                
                
                if(isspace(ch)){
                continue;
                }
                
                
                if(isalpha(ch)){
                    lexeme = ch;
                    lexstate = STID;
                
                }
                
                if(ch == '/'){
                     
                     if(isspace(in.peek())){
                         //in.putback(ch);
                         lexeme = ch;
                         return Lex(SLASH, lexeme, linenumr);
                     }
                     
                     
                    
                     lexstate = STSLASH;
                }
                
                if(isdigit(ch)){
                    
                    lexeme =ch;
                    lexstate = STINT;
                }
                
                if(ch == '\"'){
                    //lexeme = '\"';
                    lexstate = STSTRING;
                
                }
                
                else{
                    
                    
                    if(ch == '+'){
                        lexeme = ch;
                        return Lex (PLUS, lexeme, linenumr);
                    
                        }
                    
                    if(ch == '-'){
                        lexeme = ch;
                        return Lex (MINUS, lexeme, linenumr);
                    
                        }
                     if(ch == '*'){
                        lexeme = ch;
                        return Lex (STAR, lexeme, linenumr);
                    
                        }
                    
                    
                    
                    if(ch == '!'){
                        lexeme = ch;
                        return Lex (BANG, lexeme, linenumr);
                    
                        }
                    
                    
                    if(ch == '('){
                        lexeme = ch;
                        return Lex (LPAREN, lexeme, linenumr);
                    
                        }
                    
                    if(ch == ')'){
                        lexeme = ch;
                        return Lex (RPAREN, lexeme, linenumr);
                    
                        }
                     if(ch == ';'){
                        lexeme = ch;
                        return Lex (SC, lexeme, linenumr);
                    
                        }
                
                    if(ch == '.'){
                        lexeme = ch;
                        linenumr++;
                        return Lex (ERR, lexeme, linenumr);
                    
                        }
                    if(ch == '$'){
                        lexeme = ch;
                        linenumr++;
                        return Lex (ERR, lexeme, linenumr);
                    
                        }
                     if(ch == '_'){
                        lexeme = ch;
                        linenumr++;
                        return Lex (ERR, lexeme, linenumr);
                    
                        }
                   
                    
                
                }
                
                break;
        
        case(STID):
                
                if( isalnum(ch)){
                 lexeme += ch;
                 continue;
                     
                }
                
                
                else if(!isalnum(ch)){
                    if (ch != '\n'){
                    in.putback(ch);}
                    //cout << "space bw Tokens" << endl
                    it = myMap.find(lexeme);
                    if (it == myMap.end()){
                        return Lex (ID, lexeme, linenumr);
                        lexstate = START;
                    }
                    else{
                        Token tk = it -> second;
                        return Lex (tk, lexeme , linenumr);
                        lexstate = START;
                    }
                }
                    
             
                
                    
                break;
                
       case(STSTRING):
               if( ch == '\"'){
                   //lexeme += '\"';
                   return Lex(STR, lexeme,linenumr);
                   lexstate = START;
               }
               else if(ch == '\\' ){
                   in.get(ch);
                   if(ch == 'n'){
                       
                       lexeme += '\n';
                   }
                   else{
                       lexeme+= ch;
                   }
                   
                   }
                   
               
              
               else if (ch == '\n'){
                   lexeme += ch;
                   //linenumr++;
                   return Lex(ERR,lexeme,linenumr);
               }
               else{
                   lexeme += ch;
               }
               break;    
               
               
         
       
       
                
       case(STINT):
               
                if(isdigit(ch)){
                    
                    lexeme += ch;
                }
                /*
                else if( isalpha(ch)){
                    lexeme += ch;
                    
                    return Lex (ERR, lexeme, linenumr);
                    lexstate = START;
                }*/
                else if(ch =='\n'){
                return Lex (INT, lexeme,linenumr);
                    lexstate = START;
                }
                else {
                    in.putback(ch);
                    return Lex (INT, lexeme,linenumr);
                    lexstate = START;
                }
               break;
                
                
       
       case(STSLASH):
                if(ch == '/'){
                    lexstate = STCOMMENT;
                    
                }
                
                
               
                else{
                    in.putback(ch);
                    return Lex(SLASH,lexeme,linenumr); //Might want to subtract one line
                    
                
                }
               
                break;
                
                
        case(STCOMMENT):
                
               if(ch == '\n'){
                        //runcin.putback(ch);
                        lexstate = START;
                        
                    }
                
               break;
                
        }
            
        
        }
    
    
    if(in.eof()){
        
        return Lex (DONE, lexeme, linenumr);
    
    }
    
    
    return Lex (ERR, lexeme, linenumr);
    
    
}   
      

ostream& operator<<(ostream& out, const Lex& tok){
    
       
    std:: map<string, Token> :: iterator itr;
    
     static std:: map<Token, string> myMap1;
     myMap1.insert(pair<Token, string>(PRINT, "PRINT"));
     myMap1.insert(pair<Token, string>(LET, "LET" ));
     myMap1.insert(pair<Token, string>(IF, "IF" ));
     myMap1.insert(pair<Token, string>(BEGIN, "BEGIN" ));
     myMap1.insert(pair<Token, string>( END, "END" ));
     myMap1.insert(pair<Token, string>(PLUS, "PLUS" ));
     myMap1.insert(pair<Token, string>(MINUS, "MINUS" ));
     myMap1.insert(pair<Token, string>( STAR, "STAR"));
     myMap1.insert(pair<Token, string>(SLASH, "SLASH" ));
     myMap1.insert(pair<Token, string>( LPAREN, "LPAREN" ));
     myMap1.insert(pair<Token, string>(RPAREN , "RPAREN" ));
     myMap1.insert(pair<Token, string>(BANG , "BANG" ));
     myMap1.insert(pair<Token, string>( SC, "SC" ));
     myMap1.insert(pair<Token, string>( INT, "INT" ));
     myMap1.insert(pair<Token, string>( STR, "STR" ));
     myMap1.insert(pair<Token, string>( ERR, "ERR" ));
     myMap1.insert(pair<Token, string>( ID, "ID" ));
    
     
     out << myMap1[tok.GetToken()];
     if(tok.GetToken() == STR || tok.GetToken() == INT ||  tok.GetToken() == ID ){
     
     out << "(" << tok.GetLexeme() << ")";
     
     }
    return out;
     
    
   
 
}



    
