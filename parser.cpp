#include<iostream>
#include<vector>
#include<string>
#include<cctype>
#include<map>

using namespace std;

enum TokenType{
    T_INT, T_ID, T_NUM, T_IF, T_ELSE, T_RETURN, T_ASSIGN, T_PLUS, T_MINUS, T_MUL, T_DIV, 
    T_LPAREN, T_RPAREN, T_LBRACE, T_RBRACE, T_SEMICOLON, T_COLON, T_COMMA, T_GT, T_LT, T_EOF, 
    T_FOR, T_WHILE, T_EQ, T_LE, T_AND, T_OR, T_NOT, T_FLOAT, T_STRING, T_DOUBLE, T_BOOL, T_CHAR, 
    T_NEQ, T_LOGICAL_AND, T_LOGICAL_OR
};

struct Token{
    TokenType type;
    string value;
    int line;
};

class Lexer{
    private:
        string src;
        size_t pos;
        int line;
        
    public:
        Lexer(const string &src){
            this->src = src;
            this->pos = 0;
            this->line = 1;
        }

        string consumeNumber() {
            size_t start = pos;
            while(pos < src.size() && isdigit(src[pos])){
                pos++;
            }
            return src.substr(start, pos - start);
        }

        string consumeWord() {
            size_t start = pos;
            while(pos < src.size() && isalnum(src[pos])){
                pos++;
            }
            return src.substr(start, pos - start);
        }

        vector<Token> tokenize(){
            vector<Token> tokens;
            while(pos < src.size()){
                char current = src[pos];

                if(isspace(current)){
                    pos++;
                    continue;
                }
                if(isdigit(current)){
                    tokens.push_back(Token{T_NUM , consumeNumber()});
                    continue;
                }
                if(isalpha(current)){
                    string word = consumeWord();
                    if (word == "int") tokens.push_back(Token{T_INT , word, line});
                    else if (word == "float") tokens.push_back(Token{T_FLOAT , word, line});
                    else if (word == "double") tokens.push_back(Token{T_DOUBLE , word, line});
                    else if (word == "bool") tokens.push_back(Token{T_BOOL , word, line});
                    else if (word == "char") tokens.push_back(Token{T_CHAR , word, line});
                    else if (word == "string") tokens.push_back(Token{T_STRING , word, line});
                    else if (word == "IF") tokens.push_back(Token{T_IF , word, line});
                    else if (word == "else") tokens.push_back(Token{T_ELSE , word, line});
                    else if (word == "return") tokens.push_back(Token{T_RETURN , word, line});
                    else if (word == "while") tokens.push_back(Token{T_WHILE , word, line});
                    else tokens.push_back(Token{T_ID , word, line});
                    continue;
                }

                switch(current){
                    case '=' : 
                        if (src[pos+1] == '=') { tokens.push_back(Token{T_EQ, "==", line}); pos++; }
                        else { tokens.push_back(Token{T_ASSIGN , "=", line}); } 
                        break;
                    case '!' :
                        if (src[pos+1] == '=') { tokens.push_back(Token{T_NEQ, "!=", line}); pos++; }
                        break;
                    case '&' :
                        if (src[pos+1] == '&') { tokens.push_back(Token{T_LOGICAL_AND, "&&", line}); pos++; }
                        break;
                    case '|' :
                        if (src[pos+1] == '|') { tokens.push_back(Token{T_LOGICAL_OR, "||", line}); pos++; }
                        break;
                    case '+' : tokens.push_back(Token{T_PLUS , "+", line}); break;
                    case '-' : tokens.push_back(Token{T_MINUS , "-", line}); break;
                    case '*' : tokens.push_back(Token{T_MUL , "*", line}); break;
                    case '/' : tokens.push_back(Token{T_DIV , "/", line}); break;
                    case '(' : tokens.push_back(Token{T_LPAREN , "(", line}); break;
                    case ')' : tokens.push_back(Token{T_RPAREN , ")", line}); break;
                    case '{' : tokens.push_back(Token{T_LBRACE , "{", line}); break;
                    case '}' : tokens.push_back(Token{T_RBRACE , "}", line}); break;
                    case ';' : tokens.push_back(Token{T_SEMICOLON , ";", line}); break;
                    case ',' : tokens.push_back(Token{T_COMMA , ",", line}); break;
                    case '<' : tokens.push_back(Token{T_LT , "<", line}); break;
                    case '>' : tokens.push_back(Token{T_GT , ">", line}); break;
                    default: cout << "Unexpected character: " << current << endl; exit(1);
                }
                pos++;
            }
            tokens.push_back(Token{T_EOF , ""});
            return tokens;
        }

};

class Parser{
    private:
        vector<Token> tokens;
        size_t pos;

        void parseStatement(){
            if(tokens[pos].type == T_INT || tokens[pos].type == T_FLOAT || tokens[pos].type == T_DOUBLE ||
               tokens[pos].type == T_BOOL || tokens[pos].type == T_CHAR || tokens[pos].type == T_STRING){
                parseDeclaration();
            } else if(tokens[pos].type == T_ID){
                parseAssignment();
            } else if(tokens[pos].type == T_IF){
                parseIfStatement();
            } else if(tokens[pos].type == T_WHILE){
                parseWhileStatement();
            } else if(tokens[pos].type == T_RETURN){
                parseReturnStatement();
            } else if(tokens[pos].type == T_LBRACE){
                parseBlock();
            } else{
                cout << "Syntax error on line " << tokens[pos].line << ": Unexpected Token " << tokens[pos].value << endl;
                exit(1);
            }
        }

        void parseBlock(){
            expect(T_LBRACE);
            while(tokens[pos].type != T_LBRACE && tokens[pos].type != T_EOF){
                parseStatement();
            }
            expect(T_RBRACE);
        }

        void parseDeclaration(){
            expect(T_INT);
            expect(T_ID);
            expect(T_SEMICOLON);
        }

        void parseAssignment(){
            expect(T_ID);
            expect(T_ASSIGN);
            parseExpression();
            expect(T_SEMICOLON);
        }

        void parseIfStatement(){
            expect(T_IF);
            expect(T_LPAREN);
            parseExpression();
            expect(T_RPAREN);
            parseStatement();
            if(tokens[pos].type == T_ELSE){
                expect(T_ELSE);
                parseStatement();
            }
        }
        
        void parseWhileStatement(){
            expect(T_WHILE);
            expect(T_LPAREN);
            parseExpression();
            expect(T_RPAREN);
            parseStatement();
        }

        void parseReturnStatement(){
            expect(T_RETURN);
            parseExpression();
            expect(T_SEMICOLON);
        }

        void parseExpression(){
            parseTerm();
            while(tokens[pos].type == T_PLUS || tokens[pos].type == T_MINUS){
                pos++;
                parseTerm();   
            }
            if(tokens[pos].type == T_GT){
                pos++;
                parseExpression();
            }

        }

        void parseTerm(){
            parseFactor();
            while(tokens[pos].type == T_MUL || tokens[pos].type == T_DIV){
                pos++;
                parseFactor();   
            }
        }

        void parseFactor(){
            if(tokens[pos].type == T_NUM || tokens[pos].type == T_ID){
                pos++;
            } else if(tokens[pos].type == T_LPAREN){
                expect(T_LPAREN);
                parseExpression();
                expect(T_RPAREN);
            } else{
                cout << "Syntax error: unexpected token." << tokens[pos].value << endl ;
                exit(1);
            }
        }

        void expect(TokenType type){
            if(tokens[pos].type == type){
                pos++;
            } else{
                cout << "Syntax error: expected." << " but found " << tokens[pos].value << endl ;
                exit(1);
            }
        }

    public:
        Parser(const vector<Token> &tokens){
            this->tokens = tokens;
            this->pos = 0;
        }

        void ParseProgram(){
            while(tokens[pos].type != T_EOF){
                parseStatement();
            }
            cout << "Parsing completed successfully. No Syntax error." << endl ;
        }
    
};

int main(){
    string input = R"(
        int a;
        a = 5;
        int b;
        b = a + 10;
        if(b > 10){
            return b;
        } else{
            return 0;
        }
    )";

    Lexer lexer(input);
    vector<Token> tokens = lexer.tokenize();

    Parser parser(tokens);
    parser.ParseProgram();

    return 0;
}



