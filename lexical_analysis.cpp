#include <iostream>
#include <regex>
#include <string>
#include <vector>

enum TokenType{
    IDENTIFIER,
    KEYWORD,
    OPERATOR,
    LITERAL
};

struct Token{
    TokenType type;
    std::string value;

};

std::vector<Token> tokenize(const std::string& sourceCode){
    std::vector<Token> tokens;

    // Define regular expressions for different token types
    std::regex identifierRegex("[a\-zA\-Z_][a\-zA\-Z0\-9_]*");
    std::regex keywordRegex("if|else|while|for|return");
    std::regex operatorRegex("[+\\-*/=]");
    std::regex literalRegex("[0\-9]+");
    
    //Tokenize the source code
    std::smatch match;
    size_t position = 0;
    while (position < sourceCode.size()){
        std::string remaining = sourceCode.substr(position);

        if (std::regex_search(remaining, match, identifierRegex)){
            Token token;
            token.type = IDENTIFIER;
            token.value = match.str();
            tokens.push_back(token);
            position +=match.length();

        }
        else if(std::regex_search(remaining,match, keywordRegex)){
            Token token;
            token.type =KEYWORD;
            token.value=match.str();
            tokens.push_back(token);
            position += match.length();

        }
        else if(std::regex_search(remaining,match, operatorRegex)){
            Token token;
            token.type=OPERATOR;
            token.value=match.str();
            tokens.push_back(token);
            position += match.length();
        }

         else if(std::regex_search(remaining,match, literalRegex)){
            Token token;
            token.type=LITERAL;
            token.value=match.str();
            tokens.push_back(token);
            position += match.length();
         }
         else{
            //Invalid token
            position++;
         }

         return tokens;
    }
}

int main() {
    std:: string sourceCode = "int main() {int x=42; return x; }";
    std::vector<Token> tokens = tokenize(sourceCode);

    //Print the tokens
    for (const Token& token: tokens){
        std::cout <<"Type: "<< token.type <<", value: "<< token.value <<std::endl;

    }

    return 0;
}