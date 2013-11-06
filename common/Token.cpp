#include "Token.h"

Token::Token(){
    delim = 0;
    content.clear();
}

Token::Token(char value, std::string content){
    delim = value;
    this->content = content;
}

char Token::getMatachedDelim(){
    return delim;
}

std::string Token::getContent(){
    return content;
}

