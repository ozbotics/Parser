#ifndef PARSER_H
  #define PARSER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
  
class Parser {
  public:
    Parser(char delimChar) : delimChar(delimChar) {
      //Serial_printf("Constructed Parser\n");
      //Serial_printf("maxTokenSize is %d\n", maxTokenSize);
    }

    bool parseInt(char ** inputBufP, int * value);    
    bool parseUInt(char ** inputBufP, unsigned int * value);    
    
    
  protected:
    char delimChar;
    static const int maxTokenSize = 10;
    
    void getNextToken(char ** inputBufP, char * token) { getNextToken(inputBufP, token, delimChar); }
    void getNextToken(char ** inputBufP, char * token, char sentinel);

    bool parseDelim(char ** inputBufP);
    bool parseToken(char ** inputBufP, int * tokenId, const char * tokenArray[]	, int tokenArraySize);
    
    bool parseLiteral(char ** inputBufP, char const * value);
    
    bool parseString(char ** inputBufP, char * value);
    bool parseBool(char ** inputBufP, bool * value);
    bool parseFloat(char ** inputBufP, float * value);
    virtual bool parseEnd(char ** inputBufP);
    
    bool intIsBetween(int value, int min, int max);
    bool stringLengthIsBetween(char * str, int min, int max);
    bool stringHasNoSpaces(char * str);
    
};
  
#endif
