#ifndef VAL_H
#define VAL_H

#include <string>
using namespace std;

class Val {
    int        i;
    string    s;
    enum ValType { ISINT, ISSTR, ISERR } vt;
    
public:
    Val() : i(0), vt(ISERR) {}
    Val(int i) : i(i), vt(ISINT) {}
    Val(string s) : i(0), s(s), vt(ISSTR) {}
    Val(ValType vt, string errmsg) : i(0), s(errmsg), vt(ISERR) {}
    
    ValType getVt() const { return vt; }
    
    bool isErr() const { return vt == ISERR; }
    bool isInt() const { return vt == ISINT; }
    bool isStr() const { return vt == ISSTR; }
    
    int ValInt() const {
        if( isInt() ) return i;
        throw "This Val is not an Int";
    }
    string ValString() const {
        if( isStr() ) return s;
        throw "This Val is not a Str";
    }
    
    friend ostream& operator<<(ostream& out, const Val& v) {
        // IMPLEMENT
        if(v.isInt()){
            out << v.ValInt();
            
        }
        
        if(v.isStr()){
            out << v.ValString();
            
        }
        return out;
    }
    
    string GetErrMsg() const {
        if( isErr() ) return s;
        throw "This Val is not an Error";
    }
   
    Val operator+(const Val& op) const {
        if( isInt() && op.isInt() )
            return ValInt() + op.ValInt();
        if( isStr() && op.isStr() )
            return ValString() + op.ValString();
        return Val(ISERR, "Type mismatch on operands of +");
    }
    
    Val operator-(const Val& op) const {
        // IMPLEMENT
        if( isInt() && op.isInt() )
            return ValInt() - op.ValInt();
        
        return Val(ISERR, "Type mismatch on operands of -");
    }
    
    Val operator*(const Val& op) const {
        // IMPLEMENT
        if( (isInt() && op.isInt()))
            return ValInt() * op.ValInt();
        if( (isInt() && op.isStr())  || (isStr() && op.isInt())){
            
            string test ="";
            int f;
            string str = "";
            
            if(op.isInt()){
                f = op.ValInt();
                
                str = ValString();
            }
            
            else{
                f = ValInt();
                str = op.ValString();
            
            }
            
            if(f<0){
                    return Val(ISERR, "Cannot multiply string by negative int");
                }
            for(int j = 0; j < f; j++){
                test += str;
            }
            return test;
            
        }
        return Val(ISERR, "Type mismatch on operands of *");
    }
    
    Val operator/(const Val& op) const {
        // IMPLEMENT
        if( isInt() && op.isInt() ){
            if(op.ValInt()==0){
                return Val(ISERR, "Divide by zero error");
            }
            
            
            return ValInt() / op.ValInt();
        
        }
        
        return Val(ISERR, "Type mismatch on operands of *");
    }
    
    Val operator!() const {
         // IMPLEMENT
        if(isInt()){
           int reverse =0;
           int mod;
           int n = ValInt();
            
           while(n){
               mod = n%10;
               reverse = reverse*10 +mod;
               n /= 10;
           }
           return reverse;
        }
        if(isStr()){
            string reverse ="";
            string str = ValString();
            int n = str.length();
            for(int i = 0; i < n; i++){
                reverse += str[n-1-i];
            }
            return reverse;
        
        }
        return Val(ISERR, "Type mismatch on operands of !");
    }
    
};

#endif
