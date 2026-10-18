#ifndef LEXANALYZER
#define LEXANALYZER

#include <iostream>
#include <vector>
#include <fstream>
#include <string> 
using namespace std; 

enum class categoryType
{
    KEYWORD,
    IDENTIFIER,
    STRING_LITERAL,
    NUMERIC_LITERAL,
    ASSIGNMENT_OP,
    ARITH_OP,
    LOGICAL_OP,
    RELATIONAL_OP,
    LEFT_PAREN,
    RIGHT_PAREN,
    COLON,
    COMMA,
    COMMENT,
    INDENT,
    UNKNOWN
};

class lexanalyzer
{
private:
    typedef vector<vector<pair<string, categoryType>>> tokenType;
    typedef vector<pair<string, categoryType>> tokenLineType;
    //tokenLineType name
    //use pushback
    typedef pair<string, categoryType> pairType;
    tokenType tokenInfo;
    tokenLineType lineToken; 
    bool problem = false;



public: 
    //categoryType checker = categoryType::KEYWORD;
    //maybe reinitialize beause I don't know when the memory is overwrited especially when storeing 
    void show(string read)
    {
        lineToken.clear();
        string together = "";
        //make sure to check the togethers are reset in the right places
        int stringLit = 0;
        pairType PT;

        bool isNum = false;
        bool lParen = false;
        bool rParen = false;
        bool isIndent = true;
        int spaceCount = 0;
        char check; 
        bool quote = false; 
        string comments = "";
        //to account for strings that don't end in whitespace 
        bool isString = false; 

        for (int i = 0; i < read.length(); i++)
        {
            //take the value of the current part of the string we are on 
           check = read[i];
           //these are the checks for comment
           if (check == 35)
           {
               //if its a comment take everything after and place it into check 
               
               //cout << " i is " << i; 
               for (int j = i; j < read.length(); j++)
              {
                  comments += read[j];
                  //cout << "The length of the line is " << read.length(); 
                  //cout << "This is comment at increment" << endl;
              }
               PT.first = comments;
               PT.second = categoryType::COMMENT;
               lineToken.push_back(PT);
               i = read.length();

           }        

          

           //whitespace 
           else if (check == 32)
           {  
               //checking for indent
               for (int i = 0; i < 5; i++)
               {
                   if (read[i] != 32)
                   {
                       isIndent = false; 
                   }
               }
               if ( isIndent == true && i == 0)
               {
                   PT.first = "\t";
                   PT.second = categoryType::INDENT;
                   lineToken.push_back(PT);
                   together = "";
               }
               //if theres currently an array being pushed back it is finished
               //use function now to determine what it is 
               //then reset
               together = ""; 
               //use continue to go the next incrament maybe not necessary
               continue;
               

           }
          
           else if (check == 34)
           {
               //checking for string literal 
               together.push_back(check);
               
               int j = i;
               //check for a closing one now
               while(quote == false)
               { 
                   j++;
                   check = read[j];
                   together.push_back(check);
                   if (check == 34)
                   {
                       PT.first = together;
                       PT.second = categoryType::STRING_LITERAL;
                       lineToken.push_back(PT);
                       together = "";
                       quote = true; 

                   }
                   else if (j == read.length())
                   {
                       problem = true;
                       cout << "Syntax error, no ending quote";
                       return;
                   }
                       
                   
               }
               i = j;
               

              
                  
               
              
                /*if (stringLit % 2 == 0)
               {
                   //checking if its a multiple of 2 

                   PT.first = together;
                   PT.second = categoryType::STRING_LITERAL;
                   lineToken.push_back(PT);
                   together = "";

               }*/
               

           }
           else if (isalpha(check))
           {
               isString = true;
               //trying to check if we are looking at a string 
               together.push_back(check);
               //potentially take out 
               if (isalpha(read[i + 1]) == false)
               {
                   checkString(together);
                   together = "";
               }
               else
               {
                   continue; 
                  
               }
           }
           //keep here to account for a string literal
           else if (isdigit(check))
           {
           
               together.push_back(check);
              
               //trying to account for whitespaces
                   if (isdigit(read[i + 1]) == false)
                   {
                       PT.first = together;
                       PT.second = categoryType::NUMERIC_LITERAL;
                       lineToken.push_back(PT);
                       together = "";
                   }
                   else
                   {
                       continue;
                   }
               
           }
           else if (check == 40)
           {
               //and what if they letters in them
               //if there is a left parathesis there should be a right parenthesis 
               //but maybe trouble if there is a left with no right or just a right 
               PT.first = "(";
               PT.second = categoryType::LEFT_PAREN;
               lineToken.push_back(PT);
               together = "";
               //checking if there isn't another right before this 
               //but doesn't really make sense as you can have left parenthesis before having a right 
              /* if (lParen == true)
               {
                   problem = true; 
                   cout << "syntax error, there is a " << endl; 
               }*/
               lParen = true;
               //if there is something in the together string before say error incorrect syntax
               

           }
           else if (check == 41)
           {
               // right parathesis 
               //handle if there is a left parenthasis before this or not 
              if (lParen == false)
               {
                   problem = true; 
                   cout << "syntax error, right parenthesis but no left parenthesis before" << endl;
                   return; 
               }
 
              rParen = true; 
               //if (lParen == true)
               //{
               //    //reseting so another parenthesis can exist 
               //    lParen = false;
               //}
               PT.first = ")";
               PT.second = categoryType::RIGHT_PAREN;
               lineToken.push_back(PT);
               together = "";

           }
           else if (check == '=')
           {
               //assignment operator 
               PT.first = "=";
               //in the case its == not = 
               if (read[i + 1] == '=')
               {
                   i++;
                   PT.first = "==";
                   PT.second = categoryType::RELATIONAL_OP;
               }
               PT.second = categoryType::ASSIGNMENT_OP;
               lineToken.push_back(PT);
               together = "";
        }
           else if (check == '+' || check == '-' || check == '/' || check == '*')
           {
               PT.first = check;
               PT.second = categoryType::ARITH_OP;
               lineToken.push_back(PT);
               together = "";
        }
           else if (check == '|' || check == '&' || check == '!')
           {
               //checking for second one for | and &
               if (check == '|')
               {
                   if (read[i + 1] == '|' )
                   {
                       i++;
                       PT.first = "||";
                       PT.second = categoryType::LOGICAL_OP;
                       
                   }
                   else
                   {
                       problem = true; 
                       cout << "syntax error, no second | "; 
                   }
               }
               else if (check == '&')
               {
                   if (read[i + 1] == '&')
                   {
                       i++;
                       PT.first = "&&";
                       PT.second = categoryType::LOGICAL_OP;
                   }
                   else
                   {
                       problem = true; 
                       cout << "syntax error, no second &";
                   }
               }
               else if (check == '!')
               {
                   if (read[i + 1] == '=')
                   {
                       i++;
                       PT.first = "!=";
                       PT.second = categoryType::RELATIONAL_OP;
                   }
                   else
                   {
                       PT.first = "!";
                       PT.second = categoryType::LOGICAL_OP;
                   }
               }
               
               //check if you need to check for extra operators after !
               //PT.first = check;
               //PT.second = categoryType::LOGICAL_OP;
               lineToken.push_back(PT);
        }
           else if (check == '=' || check == '<' || check == '>' || check == '!')
           {
               //check for 2nd character 
               if (check == '=')
               {
                   if (read[i + 1] == '=')
                   {
                       i++;
                       PT.first = "==";
                       PT.second = categoryType::RELATIONAL_OP;
                   }
                   else
                   {
                       problem = true;
                       cout << "syntax error, no second =";
                   }
               }
               else if (check == '>')
               {
                   if (read[i + 1] == '=')
                   {
                       //to skip an incrament 
                       i++;
                       PT.first = ">=";
                       PT.second = categoryType::RELATIONAL_OP;
                   }
               }
               else if (check == '<')
               {
                   if (read[i + 1] == '=')
                   {
                       i++;
                       PT.first = "<=";
                       PT.second = categoryType::RELATIONAL_OP;
                   }
                   else
                   {
                       cout << "syntax error, no = following <";
                   }
               }
               else if (check == '!')
               {
                   if (read[i + 1] == '=')
                   { 
                       i++;
                       PT.first = "!=";
                       PT.second = categoryType::RELATIONAL_OP;
                   }
                   else
                   {
                       problem = true; 
                       cout << "syntax error, no = following !";
                   }
               }
               PT.first = check;
               PT.second = categoryType::RELATIONAL_OP;
               lineToken.push_back(PT);
        }
           else if (check == ':')
           {
               PT.first = check;
               PT.second = categoryType::COLON;
               lineToken.push_back(PT);
        }
           else if (check == ',')
           {
               PT.first = check;
               PT.second = categoryType::COMMA;
               lineToken.push_back(PT);
        }
           else
           {
               PT.first = check;
               PT.second = categoryType::UNKNOWN;
               lineToken.push_back(PT); 

           }
          
       }


       //checking parenthesis
       if (lParen == true && rParen == false)
       {
           cout << "Syntax error with no right parenthesis for every left parenthesis" << endl;
       }
       //checking quotations
       if (stringLit % 2 != 0)
       {
           cout << "Syntax error no closing parathesis" << endl; 
       }       //after the for loop push the line's token into the tokenType
       tokenInfo.push_back(lineToken); 
       //display();
       return; 
    }

    //checkLetter is for checking when there is a string from toegether varaible 
    void checkString(string check)
    { 
        pairType Pt;
        //checking keyword 
         if (check == "print" || check == "if" || check == "elif" || check == "else" || check == "while" || check == "int" || check == "input")
        { 
             Pt.first = check;
            Pt.second = categoryType::KEYWORD;
            lineToken.push_back(Pt);

            
        }
        else
        {
             Pt.first = check;
             Pt.second = categoryType::IDENTIFIER;
             lineToken.push_back(Pt);
            
        }
      
 
    }

    void display()
    {
        if (problem == true)
        {
            exit(0);
        }
        string theEnum = "";
        cout << "***** TOKEN INFORMATION *****" << endl; 
        for (int i = 0; i < tokenInfo.size(); i++)
        {
            cout << "Line #" << i << ":" << endl;
            //don't endline 

            for (int j = 0; j < tokenInfo[i].size(); j++)
            {
                cout << "Token[" << j << "]:    "; 
                cout << tokenInfo[i][j].first << "  -  ";
                if (tokenInfo[i][j].second == categoryType::KEYWORD)
                {
                    theEnum = "KEYWORD";
                    
                }
                else if (tokenInfo[i][j].second == categoryType::IDENTIFIER)
                {
                    theEnum ="IDENTIFIER";
                }
                else if (tokenInfo[i][j].second == categoryType::STRING_LITERAL)
                {
                    theEnum = "STRING_LITERAL";

                }
                else if (tokenInfo[i][j].second == categoryType::NUMERIC_LITERAL)
                {
                    theEnum = "NUMERIC_LITERAL";

                }
                else if (tokenInfo[i][j].second == categoryType::ASSIGNMENT_OP)
                {
                    theEnum = "ASSIGNMENT_OP";

                }
                else if (tokenInfo[i][j].second == categoryType::ARITH_OP)
                {
                    theEnum = "ARITH_OP";

                }
                else if (tokenInfo[i][j].second == categoryType::LOGICAL_OP)
                {
                    theEnum = "LOGICAL_OP";

                }
                else if (tokenInfo[i][j].second == categoryType::RELATIONAL_OP)
                {
                    theEnum = "RELATIONAL_OP";
                    
                }
                else if (tokenInfo[i][j].second == categoryType::LEFT_PAREN)
                {
                    theEnum = "LEFT_PAREN";
                    
                }
                else if (tokenInfo[i][j].second == categoryType::RIGHT_PAREN)
                {
                    theEnum = "RIGHT_PAREN";

                }
                else if (tokenInfo[i][j].second == categoryType::COLON)
                {
                    theEnum = "COLON";

                }
                else if (tokenInfo[i][j].second == categoryType::COMMA)
                {
                    theEnum = "COMMA";
                }
                else if (tokenInfo[i][j].second == categoryType::COMMENT)
                {
                    theEnum = "COMMENT";
                }
                else if (tokenInfo[i][j].second == categoryType::INDENT)
                {
                    theEnum = "INDENT";
                }
                else if (tokenInfo[i][j].second == categoryType::UNKNOWN)
                {
                    theEnum = "UNKNOWN";
                }
                cout << theEnum << endl;
            }

        }
    }
};


#endif 