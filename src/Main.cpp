#include <iostream>
#include "interface.h"
#include <string>
#include <fstream>


//check for if you need more endlines for the spacing 
int main()
{
    Interface pySubInterpreter;
    string userInput;
    bool stay = true;
    // Start the interface
    pySubInterpreter.startInterface();
    string check;
    string check1;
    string check2;
    string check3;
    string check4; 
    string forSub; 
    bool equation = false;
    bool isEquation = false; 
    vector<string> convert;
    while (stay == true)
    {
        cout << ">>>";
        getline(cin, userInput);
        check = userInput;
        //check copies userInput for substr problems of cuttoff 
        if (userInput.size() >= 2)
            check4 = userInput.substr(0, 2);
        else
            check4 = "";
        if (userInput.size() >= 3)
            check3 = userInput.substr(0, 3);
        else
            check3 = "";
        if (userInput.size() >= 4)
            check2 = userInput.substr(0, 4);
        else
            check2 = "";
        if (userInput.size() >= 5)
            check1 = check.substr(0, 5);
        else
            check1 = "";
        isEquation = false;
            equation = false; 
        //check2 is used for commands with inputs in them
        //create two stings one being the substring and one being the actual string 

        //checking for if theres a number beause then its a expression
        for (int i = 0; i < check.size(); i++)
        {
            forSub = check[i];
            if (forSub == "-" || forSub == "+" || forSub == "%" || forSub == "*" || forSub == "/" || forSub == "<" || forSub == ">"|| forSub == "=" || forSub =="*")
            {
                if (forSub == "=")
                {
                    
                     if (check[i + 1] == '=')
                    {
                        i++;
                        equation = true;
                    }
                     else  if (check[i - 1] == '<' || check[i - 1] == '!' || check[i - 1] == '>')
                         equation = true;
                    else
                        isEquation = true; 
                }
                else
                equation = true;
            }
            

        }
        for (int i = 0; i < check.size(); i++)
        {
             if (check[i] == 'n')
            {
                //checking for not 
                if (i != check.size() - 2 && i != check.size() - 1)
                {
                    if (check[i+1] == 'o')
                    {
                        
                        if (check[i + 2] == 't')
                        {
                            equation = true; 
                        }
                    }
                }
            }
            else if (check[i] == 'a')
            {
                //checking for and
                if (i != check.size() - 2 && i != check.size() - 1)
                {
                    if (check[i + 1] == 'n')
                    {

                        if (check[i + 2] == 'd')
                        {
                            equation = true;
                        }
                    }
                }
            }
            else if (check[i] == 'o')
            {
                //checking for or
                if (i != check.size() - 1)
                {
                    if (check[i+1] == 'r')
                    {
                        equation = true; 
                    }
                }
            }
            else if (check[i] == 'p')
             {
                 //chekcing for print
                 if (i != check.size() - 4)
                 {
                     forSub = check.substr(i + 1, 4);
                     if (forSub == "rint")
                     {
                         isEquation = true; 
                     }
                 }
             }
        }
      
        if (check1 == "while")
        {
            pySubInterpreter.conditionalWhile(check);
            //because equation is executed
            equation = false; 
            //clear runVector
            //pySubInterpreter.runVector.clear();
        }
        else if (check4 == "if" || check2 == "elif" || check2 == "else")
        {
            
            if (check4 == "if")
            {
                //ifConditional to represent the fact that the code has hit an if statement 
                   //ifConditional remains true unless the statement executes 
                pySubInterpreter.ifConditional = true;
                //ifStatement means the first if exists so that we can enter an if loop 
                pySubInterpreter.ifStatement = true;
            }
            pySubInterpreter.conditionalIf(check);
            equation = false; 
        }
        else if (isEquation == true)
        {
          
                convert.push_back(check);

            
            pySubInterpreter.read(convert);
            for (auto x : pySubInterpreter.runVector)
            {
                pySubInterpreter.run(x);
            }
            isEquation = false; 
            //clear the vector 
            convert.clear(); 
            pySubInterpreter.runVector.clear();

        }
        else if (equation == true)
        {
            //change the string into a vector 
            for (int i = 0; i < check.size(); i++)
            {

                check2 = check[i];
                convert.push_back(check2);

            }
            pySubInterpreter.mathEvaluator(convert);
            convert.clear();
            //reseting equation 
            equation = false; 

        }
        
        if (check3 == "run" || check3 == "run()")
        {
           for(int b = 0; b < pySubInterpreter.runVector.size(); b++)
             {
                if (pySubInterpreter.runVector[b].substr(0, 2) == "if")
                {
                    //ifConditional to represent the fact that the code has hit an if statement 
                    //ifConditional remains true unless the statement executes 
                    pySubInterpreter.ifConditional = true;
                    //ifStatement means the first if exists so that we can enter an if loop 
                    pySubInterpreter.ifStatement = true; 
                    //b does this to change the increment it is on 
                    b += pySubInterpreter.runConditional(pySubInterpreter.runVector[b], b);

                }
                else if (pySubInterpreter.runVector[b].substr(0, 4) == "elif" || pySubInterpreter.runVector[b].substr(0, 4) == "else")
                {
                    b += pySubInterpreter.runConditional(pySubInterpreter.runVector[b], b);
                }
                else if (pySubInterpreter.runVector[b].substr(0, 5) == "while")
                {
                    b += pySubInterpreter.runConditional(pySubInterpreter.runVector[b], b);
                }
                else
                pySubInterpreter.run(pySubInterpreter.runVector[b]);
            }
            //then clear the runVector likely here
         pySubInterpreter.runVector.clear();


        }
        else if (check2 == "help")
        {
            //help needs to be check2 to read the function later on
            //keep it in the help loop 
            pySubInterpreter.help(check, true, true);
        }
        else if (check2 == "read")
        {
            //check2 because it checks if its read but doesn't read the function yet
            pySubInterpreter.read(check);
        }
        else if (check2 == "show")
        {

            //while the vector is not empty
            pySubInterpreter.show(check);
        }
        else if (check == "clear" || check == "clear()")
        {
            //no check2 because no info inside
            pySubInterpreter.clear();
        }
       

    }

    return 0;
}

