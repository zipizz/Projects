package MiniC.Scanner;

import MiniC.Scanner.SourceFile;
import MiniC.Scanner.Token;

public final class Scanner {

  private class Stack {

    int top;
    char[] stack;
    int size;

    private Stack() {
      top = -1;
      this.size = 1000;
      stack = new char[this.size];
    }

    private void push(char value) {
      if (isFull()) {
        char[] temp;
        temp = new char[this.size];

        for (int i = 0; i < this.size; i++) {
          temp[i] = stack[i];
        }

        stack = new char[this.size * 2];

        for (int i = 0; i < this.size; i++) {
          stack[i] = temp[i];
        }
        this.size *= 2;
      }
      stack[++top] = value;
    }

    private char pop() {
      return stack[top--];
    }

    private boolean isEmpty() {
      if (top == -1) {
        return true;
      }
      return false;
    }

    private boolean isFull() {
      if (top == this.size - 1) {
        return true;
      }
      return false;
    }
  }

  private static final int STATE_NONE = 1234;
  private static final int STATE_TOKEN = 2345;
  private static final int STATE_COMMENT = 3456;
  private static final char EOF = '\u0000';
  private static final String ERROR_UNTERMINATED_COMMENTS = "ERROR: unterminated multi-line comment."; 
  private static final String ERROR_UNTERMINATED_STRINGS = "ERROR: unterminated string literal";
  private static final String ERROR_ILLEGAL_SEQUENCES = "ERROR: illegal escape sequence";


  private SourceFile sourceFile;
  private Stack remainStack;
  private char currentChar;
  private boolean verbose;
  private StringBuffer currentLexeme;
  private String commentPart;
  private int state;
  private int currentLineNr;
  private int currentColNr;

  private boolean isDigit(char c) {
    return (c >= '0' && c <= '9');
  }

  private boolean isLetter(char c) {
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_')) {
      return true;
    }
    return false;
  }

  private boolean isIdentifier(char c) {
    if (isDigit(c) || isLetter(c)) {
      return true;
    }
    return false;
  }

  private boolean isOperator(char c) {
    if (c == '=' || c == '|' || c == '&' || c == '!' || c == '<' || c == '>' || c == '+' || c == '-' || c == '*'
        || c == '/') {
      return true;
    }
    return false;
  }

  private boolean isFractionPoint(char c) {
    if (c == '.' || c == 'e' || c == 'E') {
      return true;
    }
    return false;
  }

  private boolean isExponentPoint(char c) {
    if (c == 'e' || c == 'E') {
      return true;
    }
    return false;
  }

  private boolean isSign(char c) {
    if (c == '+' || c == '-') {
      return true;
    }
    return false;
  }

  private boolean isPunctuation(char c) {
    if (c == '{' || c == '}' || c == '[' || c == ']' || c == '(' || c == ')' || c == ',' || c == ';') {
      return true;
    }
    return false;
  }

  private boolean isWhiteSpace(char c) {
    if (c == '\t' || c == '\n' || c == ' ' || c == '\r' || c == '\f') {
      return true;
    }
    return false;
  }

  private boolean isDot(char c) {
    if (c == '.') {
      return true;
    }
    return false;
  }

  private boolean isDoubleQuotes(char c) {
    if (c == '"') {
      return true;
    }
    return false;
  }

  private boolean isEOF(char c) {
    if (c == EOF) {
      return true;
    }
    return false;
  }
  ///////////////////////////////////////////////////////////////////////////////

  public Scanner(SourceFile source) {
    sourceFile = source;
    remainStack = new Stack();
    state = STATE_NONE;
    currentChar = sourceFile.readChar();
    verbose = false;
    currentLineNr = 1;
    currentColNr = 1;
  }

  public void enableDebugging() {
    verbose = true;
  }

  // takeIt appends the current character to the current token, and gets
  // the next character from the source program (or the to-be-implemented
  // "untake" buffer in case of look-ahead characters that got 'pushed back'
  // into the input stream).

  private void takeIt() {
    switch (state) {
    case STATE_TOKEN:
      currentLexeme.append(currentChar);
      break;
    case STATE_COMMENT:
      commentPart += currentChar;
      break;
    default:
      break;
    }

    if (remainStack.isEmpty()) {
      currentChar = sourceFile.readChar();
    } else {
      currentChar = remainStack.pop();
    }
  }

  private void untake() {
    remainStack.push(currentChar);
    switch (state) {
    case STATE_TOKEN:
      currentChar = currentLexeme.charAt(currentLexeme.length() - 1);
      currentLexeme.deleteCharAt(currentLexeme.length() - 1);
      break;
    case STATE_COMMENT:
      currentChar = commentPart.charAt(commentPart.length() - 1);
      commentPart = commentPart.substring(0, commentPart.length() - 1);
      break;
    default:
      break;
    }
  }

  private int scanOperation() {
    switch (currentChar) {
    case '=':
      takeIt();
      if (currentChar == '=') {
        takeIt();
        return Token.EQ;
      }
      return Token.ASSIGN;
    case '|':
      takeIt();
      if (currentChar == '|') {
        takeIt();
        return Token.OR;
      }
      return Token.ERROR;
    case '&':
      takeIt();
      if (currentChar == '&') {
        takeIt();
        return Token.AND;
      }
      return Token.ERROR;
    case '!':
      takeIt();
      if (currentChar == '=') {
        takeIt();
        return Token.NOTEQ;
      }
      return Token.NOT;
    case '<':
      takeIt();
      if (currentChar == '=') {
        takeIt();
        return Token.LESSEQ;
      }
      return Token.LESS;
    case '>':
      takeIt();
      if (currentChar == '=') {
        takeIt();
        return Token.GREATEREQ;
      }
      return Token.GREATER;
    case '+':
      takeIt();
      return Token.PLUS;
    case '-':
      takeIt();
      return Token.MINUS;
    case '*':
      takeIt();
      return Token.TIMES;
    case '/':
      takeIt();
      return Token.DIV;
    default:
      takeIt();
      return Token.ERROR;
    }
  }

  private boolean isSameSpell(char tokenC, int tokenKind) {
    if (tokenC == Token.spell(tokenKind).charAt(0)) {
      return true;
    }
    return false;
  }

  private boolean isSameSpell(String tokenString, int tokenKind) {
    return tokenString.equals(Token.spell(tokenKind));
  }

  private int scanPunctuation() {
    char charBeforeTake = currentChar;
    takeIt();
    if (isSameSpell(charBeforeTake, Token.LEFTBRACE))
      return Token.LEFTBRACE;
    else if (isSameSpell(charBeforeTake, Token.RIGHTBRACE))
      return Token.RIGHTBRACE;
    else if (isSameSpell(charBeforeTake, Token.LEFTBRACKET))
      return Token.LEFTBRACKET;
    else if (isSameSpell(charBeforeTake, Token.RIGHTBRACKET))
      return Token.RIGHTBRACKET;
    else if (isSameSpell(charBeforeTake, Token.LEFTPAREN))
      return Token.LEFTPAREN;
    else if (isSameSpell(charBeforeTake, Token.RIGHTPAREN))
      return Token.RIGHTPAREN;
    else if (isSameSpell(charBeforeTake, Token.COMMA))
      return Token.COMMA;
    else if (isSameSpell(charBeforeTake, Token.SEMICOLON))
      return Token.SEMICOLON;
    else
      return Token.ERROR;
  }

  private int getIdKeyBoolLiterToken(String currentString) {
    if (isSameSpell(currentString, Token.BOOL))
      return Token.BOOL;
    else if (isSameSpell(currentString, Token.ELSE))
      return Token.ELSE;
    else if (isSameSpell(currentString, Token.FOR))
      return Token.FOR;
    else if (isSameSpell(currentString, Token.FLOAT))
      return Token.FLOAT;
    else if (isSameSpell(currentString, Token.IF))
      return Token.IF;
    else if (isSameSpell(currentString, Token.INT))
      return Token.INT;
    else if (isSameSpell(currentString, Token.RETURN))
      return Token.RETURN;
    else if (isSameSpell(currentString, Token.VOID))
      return Token.VOID;
    else if (isSameSpell(currentString, Token.WHILE))
      return Token.WHILE;
    else if (currentString.equals("true") || currentString.equals("false"))
      return Token.BOOLLITERAL;
    else
      return Token.ID;
  }

  private int scanIdKeyBoolLiter() {
    takeIt();
    while (isIdentifier(currentChar)) {
      takeIt();
    }
    return getIdKeyBoolLiterToken(currentLexeme.toString());
  }

  private int scanPointFirstFloatLiter() {
    takeIt();
    if (isDigit(currentChar)) {
      takeIt();
      while (isDigit(currentChar)) {
        takeIt();
      }
      if (isExponentPoint(currentChar)) {
        scanExponent();
      }
      return Token.FLOATLITERAL;
    }
    return Token.ERROR;
  }

  private int scanExponent() {
    if (!isExponentPoint(currentChar)) {
      return Token.ERROR;
    }
    takeIt();
    if (isSign(currentChar)) {
      takeIt();
    }
    if (isDigit(currentChar)) {
      takeIt();
      while (isDigit(currentChar)) {
        takeIt();
      }
      return Token.FLOATLITERAL;
    }
    while (!isExponentPoint(currentChar)) {
      untake();
    }
    return Token.ERROR;
  }

  private int scanFraction() {
    if (currentChar == '.') {
      takeIt();
      if (isDigit(currentChar)) {
        takeIt();
        while (isDigit(currentChar)) {
          takeIt();
        }
        if (isExponentPoint(currentChar)) {
          scanExponent();
        }
        return Token.FLOATLITERAL;
      } else if (isExponentPoint(currentChar)) {
        scanExponent();
        return Token.FLOATLITERAL;
      } else {
        return Token.FLOATLITERAL;
      }
    } else if (isExponentPoint(currentChar)) {
      if (scanExponent() == Token.ERROR) {
        return Token.INTLITERAL;
      }
      return Token.FLOATLITERAL;
    }
    return Token.ERROR;
  }

  private int scanIntFloatLiter() {
    takeIt();
    while (isDigit(currentChar)) {
      takeIt();
    }
    if (!isFractionPoint(currentChar)) {
      return Token.INTLITERAL;
    }
    return scanFraction();
  }

  private int scanStringLiter() {
    if (currentChar != '"') {
      return Token.ERROR;
    }

    state = STATE_NONE;
    takeIt();
    currentColNr++;
    state = STATE_TOKEN;

    while (currentChar != '"') {
      if (currentChar == '\\') {
        takeIt();
        if (currentChar != 'n') {
          takeIt();
          System.out.println(ERROR_ILLEGAL_SEQUENCES);
          continue;
        } else {
          takeIt();
          continue;
        }
      }
      if (currentChar == '\n') {
        System.out.println(ERROR_UNTERMINATED_STRINGS);
        return Token.STRINGLITERAL;
      }
      if (currentChar == '\r') {
        takeIt();
        if (currentChar == '\n') {
          untake();
          System.out.println(ERROR_UNTERMINATED_STRINGS);
          return Token.STRINGLITERAL;
        }
      }
      takeIt();
    }
    state = STATE_NONE;
    takeIt();
    currentColNr++;
    state = STATE_TOKEN;
    return Token.STRINGLITERAL;
  }

  private int scanToken() {
    if (isOperator(currentChar)) {
      return scanOperation();
    } else if (isPunctuation(currentChar)) {
      return scanPunctuation();
    } else if (isLetter(currentChar)) {
      return scanIdKeyBoolLiter();
    } else if (isDot(currentChar)) {
      return scanPointFirstFloatLiter();
    } else if (isDigit(currentChar)) {
      return scanIntFloatLiter();
    } else if (isDoubleQuotes(currentChar)) {
      return scanStringLiter();
    } else if (isEOF(currentChar)) {
      currentLexeme.append('$');
      return Token.EOF;
    } else {
      takeIt();
      return Token.ERROR;
    }
  }

  private void jumpDoubleComment() { // case of "//"
    while (true) {
      if (currentChar == '\n') {
        takeIt();
        currentColNr = 1;
        currentLineNr++;
        return;
      }
      if (currentChar == '\r') {
        takeIt();
        if (currentChar == '\n') {
          takeIt();
          currentColNr = 1;
          currentLineNr++;
          return;
        }
        continue;
      }
      takeIt();
    }
  }

  private void jumpStarComment() { // case of "/* */"
    while (true) {
      if (currentChar == EOF) {
        System.out.println(ERROR_UNTERMINATED_COMMENTS);
        return;
      }
      if (currentChar == '*') {
        takeIt();
        currentColNr++;
        if (currentChar == '/') {
          takeIt();
          currentColNr++;
          return;
        }
        continue;
      }
      if (currentChar == '\n') {
        takeIt();
        currentColNr = 1;
        currentLineNr++;
        continue;
      }
      if (currentChar == '\r') {
        takeIt();
        currentColNr++;
        if (currentChar == '\n') {
          takeIt();
          currentColNr = 1;
          currentLineNr++;
          continue;
        }
        continue;
      }
      takeIt();
      currentColNr++;
    }
  }

  private void jumpComment() {
    commentPart = new String("");
    while (currentChar == '/' && currentChar != EOF) {
      takeIt();
      currentColNr++;
      if (currentChar == '/') {
        takeIt();
        currentColNr++;
        jumpDoubleComment();
      } else if (currentChar == '*') {
        takeIt();
        currentColNr++;
        jumpStarComment();
      } else {
        untake();
        currentColNr--;
        break;
      }
      jumpWhiteSpace();
    }
  }

  private void jumpWhiteSpace() {
    while (isWhiteSpace(currentChar)) {
      if (currentChar == '\n') {
        takeIt();
        currentColNr = 1;
        currentLineNr++;
        continue;
      }
      if (currentChar == '\r') {
        takeIt();
        if (currentChar == '\n') {
          takeIt();
          currentColNr = 1;
          currentLineNr++;
          continue;
        }
        currentColNr++;
        continue;
      }
      takeIt();
      currentColNr++;
    }
  }

  public Token scan() {
    Token currentToken;
    SourcePos pos;
    int kind;

    state = STATE_NONE;
    jumpWhiteSpace();

    state = STATE_COMMENT;
    jumpComment();

    state = STATE_TOKEN;
    currentLexeme = new StringBuffer("");
    pos = new SourcePos();
    pos.StartLine = currentLineNr;
    pos.EndLine = currentLineNr;
    pos.StartCol = currentColNr;
    kind = scanToken();
    currentToken = new Token(kind, currentLexeme.toString(), pos);
    currentColNr += currentLexeme.toString().length();
    pos.EndCol = currentColNr - 1;
    if (verbose)
      currentToken.print();
    return currentToken;
  }
}