#include "Arduino.h"
#include "Parser.h"

void Parser::getNextToken(char ** inputBufP, char * token, char sentinel) {
  char * tokenCursor = token;
  
  while ((**inputBufP != 0) && (**inputBufP != sentinel)) {
    *tokenCursor = **inputBufP;
    tokenCursor++;
    
    *inputBufP += 1;
  }
  
  *tokenCursor = 0;
}

bool Parser::parseDelim(char ** inputBufP) {
  bool ok = false;

  if (**inputBufP == delimChar) {
    ok = true;
    *inputBufP += 1;
  }
  
  return ok;
}

bool Parser::parseToken(char ** inputBufP, int * tokenId, const char * tokenArray[], int tokenArraySize) {
//  char * cursor = *inputBufP;
  bool ok = false;
  char token[maxTokenSize]; 
  
  char * origCursor = *inputBufP;
  getNextToken(inputBufP, token);

  for (int id=0; id<tokenArraySize; id++) {
    if (strcmp(tokenArray[id], token) == 0) {
      *tokenId = id;
      ok = true;
      break;
    }
  }

  if (!ok) {
     //*inputBufP = cursor;
     *inputBufP = origCursor;
  }

  return ok;
}

bool Parser::parseLiteral(char ** inputBufP, char const * literal) {
  char token[maxTokenSize];
  bool ok = false;
  
  char * origCursor = *inputBufP;
  getNextToken(inputBufP, token);

  if (strcmp(literal, token) == 0) {
    ok = true;
  }

  if (!ok) {
     *inputBufP = origCursor;
  }

  return ok;
}


bool Parser::parseString(char ** inputBufP, char * value) {
  bool ok = false;

  char * origCursor = *inputBufP;
  getNextToken(inputBufP, value);
  
  if (strlen(value) > 0) {
    ok = true;
  }
  
  if (!ok) {
     *inputBufP = origCursor;
  }

  return ok;
}

bool Parser::parseBool(char ** inputBufP, bool * value) {
  bool ok = false;
  
  if (**inputBufP == '1') {
    *value = 1;
    ok = true;
    *inputBufP += 1;
  }
  else if (**inputBufP == '0') {
    *value = 0;
    ok = true;
    *inputBufP += 1;
  }
  
  return ok;
}

bool Parser::parseFloat(char ** inputBufP, float * value) {

  bool ok = false;
  float parsedValue = 0.0;
  
  char * origCursor = *inputBufP;
  
  parsedValue = strtod(*inputBufP, inputBufP);
  
  if (*inputBufP != origCursor) {
    *value = parsedValue;
    ok = true;
  }
  else {
    *inputBufP = origCursor;
  }
  
  return ok;
}

bool Parser::parseInt(char ** inputBufP, int * value) {
  bool ok = false;
  long parsedValue = 0;
  
//  char * origCursor = *inputBufP;

  char * origCursor = *inputBufP;
  parsedValue = strtol(*inputBufP, inputBufP, 10);
  
  if (*inputBufP != origCursor) {
    *value = (int) parsedValue;
    ok = true;
  }
  else {
    //*inputBufP = origCursor;
    *inputBufP = origCursor;
  }
  
  return ok;
}

bool Parser::parseUInt(char ** inputBufP, unsigned int * value) {
  bool ok = false;
  long parsedValue = 0;
  
  char * origCursor = *inputBufP;
  parsedValue = strtol(*inputBufP, inputBufP, 10);
  
  if (*inputBufP != origCursor) {
    *value = (unsigned int) parsedValue;
    ok = true;
  }
  else {
    *inputBufP = origCursor;
  }
  
  return ok;
}

bool Parser::parseEnd(char ** inputBufP) {
  return (**inputBufP == 0);
}

bool Parser::intIsBetween(int value, int min, int max) {
  return ((min <= value) && (value <= max));
}

bool Parser::stringLengthIsBetween(char * str, int min, int max) {
  int value = strlen(str);
  return ((min <= value) && (value <= max));
}

bool Parser::stringHasNoSpaces(char * str) {
  int len = strlen(str);
  bool ok = true;
  
  for (int i=0; i<len; i++) {
    if (str[i] == ' ') {
      ok = false;
      break;
    }

    if (str[i] == 0) {
      break;
    }
  }

  return ok;
}
