#include <bits/stdc++.h>
#include "CompilersTask_1_Scanner.cpp"

using namespace std;

class Result{
public:
    int lineNumber;
    string actualString;
    string type;
    Result(int lineNumber,string actualString,string type){
        this->lineNumber = lineNumber;
        this->actualString = actualString;
        this->type = type;
    }
};

bool IsSymbolicToken(string &s){
    for (auto i:symbolic_tokens) {
        if(s == i.str){
            return true;
        }
    }
    return false;
}
bool IsReservedWord(string &s){
    for (auto i :reserved_words) {
        if(s == i.str){
            return true;
        }
    }
    return false;
}
string returnTokenTypeReserved(string &s){
    for (auto i:reserved_words) {
        if(s == i.str){
            return TokenTypeStr[i.type];
        }
    }
    return "Not Found";
}

string returnTokenTypeSymbolic(string &s){
    for (auto i:symbolic_tokens) {
        if(s == i.str){
            return TokenTypeStr[i.type];
        }
    }
    return "Not Found";
}

int main() {
    ofstream  out;
    InFile in("input.txt");
    out.open("out.txt");
    vector<Result> res;
    while (in.GetNewLine()){
        string line = in.GetNextTokenStr();
        string token;
        for (int i = 0; i < line.size(); ++i) {
            token += line[i];
            if (IsLetterOrUnderscore(line[i])){
                while (IsLetterOrUnderscore(line[i+1])){
                    token += line[i+1];
                    i++;
                }
                if(IsReservedWord(token)){
                    res.emplace_back(in.cur_line_num, token, returnTokenTypeReserved(token));
                } else{
                    res.emplace_back(in.cur_line_num, token, "ID");
                }
            }else if(IsDigit(line[i])){
                while (IsDigit(line[i+1])){
                    token += line[i+1];
                    i++;
                }
                res.emplace_back(in.cur_line_num, token, "NUM");
            }else if(IsSymbolicToken(token)){
                res.emplace_back(in.cur_line_num, token, returnTokenTypeSymbolic(token));
                if(token == "{"){
                    i++;
                    while (line[i] != '}'){
                        i++;
                        if(i == line.size()){
                            if (in.GetNewLine()){
                                line = in.GetNextTokenStr();
                                i = 0;
                            }
                        }
                    }
                    token = "}";
                    res.emplace_back(in.cur_line_num, token, returnTokenTypeSymbolic(token));
                }
            }else if(token + line[i+1] == ":="){
                token += line[i+1];
                res.emplace_back(in.cur_line_num, token, returnTokenTypeSymbolic(token));
                i++;
            }else if(token != "\n" && token != "\t" && token != "\r" && token != " "){
                res.emplace_back(in.cur_line_num, token, "Error");
            }
            token = "";
        }
    }
    res.emplace_back(in.cur_line_num + 1, "EOF", "EndFile");

    for (auto i:res) {
        out << "[" << i.lineNumber << "] " << i.actualString << " " << i.type << "\n";
    }
    return 0;
}