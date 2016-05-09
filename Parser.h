/** @file Parser.h 
  *  Copyright (c) 2016 Ozbotics 
  *  Distributed under the MIT license (see LICENSE)
  */ 
#ifndef PARSER_H
  #define PARSER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * Base class of all Parser(s)
 *
 * Provides a means of Parsing char strings
 */
class Parser {
  public:
   /**
    * Constructor
    *
    * @param delimChar The token delimiter char 
    */
    Parser(char delimChar) : delimChar(delimChar) {}

   /**
    * Parse an Intger
    *
    * @param inputBufP The input string cursor
    * @param value Pointer to the parsed value
    *
    * @return true if the string parsed correctly
    */
    bool parseInt(char ** inputBufP, int * value);
    
   /**
    * Parse an Unsigned Intger
    *
    * @param inputBufP The input string cursor
    * @param value Pointer to the parsed value
    *
    * @return true if the string parsed correctly
    */
    bool parseUInt(char ** inputBufP, unsigned int * value);    
    
   /**
    * Parse a Delimiter
    *
    * @param inputBufP The input string cursor
    *
    * @return true if the string parsed correctly
    */
    bool parseDelim(char ** inputBufP);
    
   /**
    * Parse a Delimiter
    *
    * @param inputBufP The input string cursor
    * @param tokenId Pointer to the parsed Token identifier
    * @param tokenArray The array of token strings
    * @param tokenArraySize The size of the tokenArray
    *
    * @return true if the string parsed correctly
    */
    bool parseToken(char ** inputBufP, int * tokenId, const char * tokenArray[]	, int tokenArraySize);
    
   /**
    * Parse a Literal String
    *
    * @param inputBufP The input string cursor
    * @param value The literal char string
    *
    * @return true if the string parsed correctly
    */
    bool parseLiteral(char ** inputBufP, char const * value);
    
   /**
    * Parse an arbitary String
    *
    * @param inputBufP The input string cursor
    * @param value The parsed string
    *
    * @return true if the string parsed correctly
    */
    bool parseString(char ** inputBufP, char * value);
    
    
   /**
    * Parse a Bool (0|1)
    *
    * @param inputBufP The input string cursor
    * @param value The parsed bool
    *
    * @return true if the string parsed correctly
    */
    bool parseBool(char ** inputBufP, bool * value);
    
   /**
    * Parse a Float
    *
    * @param inputBufP The input string cursor
    * @param value The parsed float
    *
    * @return true if the string parsed correctly
    */
    bool parseFloat(char ** inputBufP, float * value);
    
   /**
    * Parse End
    *
    * @param inputBufP The input string cursor
    *
    * @return true if the message is complete (no trailing chars)
    */
    virtual bool parseEnd(char ** inputBufP);
    
   /**
    * Validate that int value is Between min & max
    *
    * @param value the value to be tested
    * @param min the minimum of the value range
    * @param max the maximum of the value range
    *
    * @return true if the value is between min & max
    */
    bool intIsBetween(int value, int min, int max);
    
   /**
    * Validate that string length is Between min & max
    *
    * @param str the string to be tested
    * @param min the minimum of the length range
    * @param max the maximum of the length range
    *
    * @return true if the value is between min & max
    */
    bool stringLengthIsBetween(char * str, int min, int max);
    
   /**
    * Validate that the string contains no spaces
    *
    * @param str the string to be tested
    *
    * @return true if the value is between min & max
    */
    bool stringHasNoSpaces(char * str);

    
  protected:
    char delimChar;                       /**< protected variable  delimChar    the delimiter char used to separate tokens*/
    static const int maxTokenSize = 10;   /**< protected variable  maxTokenSize the maximum Token Size */
    
   /**
    * extract the next token from the input string
    *
    * @param inputBufP The input string cursor
    * @param token The next token string
    */
    void _getNextToken(char ** inputBufP, char * token) { _getNextToken(inputBufP, token, delimChar); }

   /**
    * extract the next token from the input string
    *
    * @param inputBufP The input string cursor
    * @param token The next token string
    * @param sentinel Use sentinel instead of delim to identify end of token
    */
    void _getNextToken(char ** inputBufP, char * token, char sentinel);
    
};
  
#endif
