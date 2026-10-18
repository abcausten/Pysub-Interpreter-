#ifndef EXPEVALUATOR
#define EXPEVALUATOR 
#include <iostream>
#include <vector>
#include <fstream>
#include <string> 
#include <map>
#include <stack>
#include <string>

class Expevaluator
{

private:

	//postfix vector for now

public:
	typedef std::map<std::string, std::string> symbolTableType;
	symbolTableType symbolTable;
	std::vector<std::string> postfixVect;
	void inflixConvertorPostfix(std::vector<std::string> reader)
	{
		std::stack<std::string> st1;
		//maybe discard
		std::stack<std::string> st2;
		std::string num = "";
		std::string convertRead = "";
		int j = 0;
		bool condition = false;
		bool lParencheck = false; 
		int tempX = 0;
		string toHold = "";
		bool conditional = false; 
		//( a + b - c ) * d - ( e + f )
		for (int i = 0; i < reader.size(); i++)
		{
			//keep in mind it could be a whitespace 
			convertRead = reader[i];
			//geting the operators that have two because read is a char
			// if (symbolTable.find(reader) != symbolTable.end())
			//{
			//	//means it is in symbolTable 
			//	symbolTable[reader]

			//}
			if (convertRead == "<")
			{
				if (reader[i + 1] == "=")
				{
					//possibly twoEle if needed 
					convertRead = "<=";
					i++;
				}
			}
			else if (convertRead == ">")
			{
				if (reader[i + 1] == "=")
				{
					convertRead = ">=";
					i++;
				}
			}
			else if (convertRead == "!")
			{
				if (reader[i + 1] == "=")
				{
					convertRead = "!=";
					i++;
				}
			}
			else if (convertRead == "=")
			{
				if (reader[i + 1] == "=")
				{
					convertRead = "==";
					i++;
				}
			}
			else if (convertRead == "n")
			{
				//checking for not 
				//added in the 2nd condition later but first condition by itself worked fine 
				if (i != reader.size() - 2 && i != reader.size() - 1)
				{
					
					num = reader[i+1];
					if(num == "o")
					{
						convertRead += reader[i];
						i++;
						/*if (i == reader.size() - 1)
						{
							break;
						}*/
						num = reader[i + 1];
						if (num == "t")
						{
							convertRead += reader[i + 1];
							i++;
							conditional = true; 
						}
						
					}
					
					num = "";
				}
				/*else
				{
					cout << "Misspelled operator likely tyring to spell not";
					return; 
				}*/
			}
			else if (convertRead == "a")
			{
				//checking for and
				if (i != reader.size() - 2 && i != reader.size()-1)
				{
					num = reader[i + 1];
					if (num == "n")
					{
						convertRead += reader[i + 1];
						i++;

						num = reader[i + 1];
						if (num == "d")
						{
							convertRead += reader[i + 1];
							i++;
							conditional = true; 
						}
						
					}
					
					num = "";
				}
				/*else
				{
					cout << "Misspelled operator likely tyring to spell and";
					return;
				}*/
			}
			else if (convertRead == "o")
			{
				//checking for or
				if (i != reader.size() - 1)
				{
					num = reader[i + 1];
					if (num == "r")
					{
						convertRead += reader[i + 1];
						i++;
						conditional = true;
					}
					num = "";
				}
				/*else
				{
					cout << "Misspelled operator likely tyring to spell or";
					return;
				}*/
			}

			if ((isdigit(convertRead[0]) || isalpha(convertRead[0])) && conditional == false)
			{
				//checking if there is a number for the varible
				conditional = false; 
				if (i + 1 != reader.size())
				{
					num = reader[i + 1];
					//if the next element is equal to a digit or a number could be a varaible 
					if (isdigit(num[0]) || isalpha(num[0]))
					{
						convertRead += reader[i + 1];
						tempX = i + 2;
						num = reader[tempX];
						while (isdigit(num[tempX]) || isalpha(num[tempX]))
						{
							convertRead += reader[tempX];
							tempX++;
						}
					}
				}
				//check if its in symbol table
				if (symbolTable.find(convertRead) != symbolTable.end())
				{
					convertRead = symbolTable[convertRead];
					postfixVect.push_back(convertRead);
					//add x to the i count to account for change 
					i = i + tempX;
					tempX = 0;
					//using continue so it skips over everything else
					continue;
				}
				else
				{
					for (auto y : convertRead)
					{
						if (isalpha(y))
						{
							//means it is a variable but not a found one
							conditional = true; 
						}
					}

					if (conditional == true)
					{
						cout << "The varaible given is not assigned one"; 
						return; 
					}
					//else just goes back to default 
					convertRead = reader[i];
					tempX = 0; 
					
				}
			// doesn't recognize this varaible 
				
			}
		
			//potentially change for operands that aren't digits 
			if (isdigit(convertRead[0]))
			{
				//should be convertRead[0] because one element 
				//keep reading to get the rest of the number 
				if (i != reader.size() - 1)
				{

					num = reader[i + 1];
					while (isdigit(num[0]))
					{
						//a string that adds read if its a char 
						convertRead += reader[i + 1];
						i++;
						if (i == reader.size() - 1)
						{
							break;
						}
						num = reader[i + 1];

					}
					postfixVect.push_back(convertRead);
					//put i-- because of the i++ increment
					//resetting num 
					num = "";
				}
				else
				{
					postfixVect.push_back(convertRead);
				}
			}
			else if (convertRead == "(")
			{
				st1.push("(");
			}
			else if (convertRead == ")")
			{
				//maybe check to see if st2 and st1 are empty
				//!!!check for more than one operator inside 
				if (st1.top() == "(")
				{
					cout << "not a valid expression only left parenthesis";
					return;
				}
				//checking if does have a left parenthesis 
				while (!st1.empty())
				{

					st2.push(st1.top());
					st1.pop();
					if (st2.top() == "(")
					{
						//checking if there is two left Parenthesis 
						if (lParencheck == true)
						{
							//cout << "two left parenthesis in the statment so it isn't valid ";
							return;
						}
						lParencheck = true;
					}
					

					
				}
				while (!st2.empty())
				{
					st1.push(st2.top());
						st2.pop();
				}
				
				while (st1.top() != "(")
				{
					postfixVect.push_back(st1.top());
					st1.pop();


				}
				if (st1.top() == "(")
				{
					st1.pop();
				}

			}
			else if (convertRead == "*" || convertRead == "/" || convertRead == "%" || convertRead == "+" || convertRead == "-" || convertRead == "<" || convertRead == ">"
				|| convertRead == "<=" || convertRead == ">=" || convertRead == "!=" || convertRead == "==" || convertRead == "and" || convertRead == "not" || convertRead == "or")
			{
				condition = true;
				while (condition == true)
				{
					if (!st1.empty())
					{

							if (st1.top() != "(")
							{

									if (presedenseCheck(st1, convertRead) == true)
									{
										postfixVect.push_back(st1.top());
										st1.pop();
									}
									else
									{
										condition = false;
										st1.push(convertRead);
									}

							}
							else
							{
								condition = false;
								st1.push(convertRead);
							}

					}
					else
					{
						condition = false;
						st1.push(convertRead);
					}
					
				}
			}
		}
		while (!st1.empty())
		{
			if (st1.top() == "(" || st1.top() == ")")
			{
				st1.pop();
			}
			else
			{
				//add to the vector 
				postfixVect.push_back(st1.top());
				st1.pop();

			}

		}
		/*for (auto x : postfixVect)
		{
			cout << x << " ";
		}*/

	}

	std::string postFixEvaluator(std::vector<std::string> theVector)
	{

		std::stack<std::string> st2;
		std::string reader;
		std::string num;
		int operand1 = 0;
		int operand2 = 0;
		std::string str;
		//for storing the stack of bools 
		std::stack<bool> stBool;
		for (int i = 0; i < theVector.size(); i++)
		{

			reader = theVector[i];
			if (isdigit(reader[0]))
			{
				st2.push(reader);
			}
			
	
			
			////testing for unary operators 
			//if (reader == "+")
			//{
			//	if (theVector.size() > i + 1)
			//	{
			//		if (theVector[i + 1] == "+")
			//		{
			//			//increasing the i
			//			i++;
			//			operand2 = stoi(st2.top());
			//			st2.pop();
			//			operand2++;
			//			str = std::to_string(operand2);
			//			st2.push(str);
			//		}
			//	}

			//}
			//else if (reader == "-")
			//{
			//	if (theVector.size() > i + 1)
			//	{
			//		if (theVector[i + 1] == "-")
			//		{
			//			i++;
			//			operand2 = stoi(st2.top());
			//			st2.pop();
			//			operand2--;
			//			str = std::to_string(operand2);
			//			st2.push(str);
			//		}
			//	}
			//}

			if (reader == "not")
			{
				if (stBool.size() == 0)
				{
					operand2 = stoi(st2.top());
					st2.pop();
					stBool.push(operand2);
				}
				operand2 = stBool.top();
				stBool.pop();
				stBool.push(!operand2);

			}
			// 1 and 1 
			// 1 1 and 

			else if (reader == "and" || reader == "or") {

				if (stBool.size() == 0)
				{
					operand2 = stoi(st2.top());
					st2.pop();
					operand1 = stoi(st2.top());
					st2.pop();
					stBool.push(operand1);
					stBool.push(operand2); 
				}

				operand2 = stBool.top();
				stBool.pop();
				operand1 = stBool.top();
				stBool.pop();
				//evaluating
				if (reader == "and")
				{
					stBool.push(operand1 && operand2);
				}
				else if (reader == "or")
				{
					stBool.push(operand1 || operand2);
				}
			}
			//binary operators - + % * /
			if (reader == "-" || reader == "+" || reader == "%" || reader == "*" || reader == "/"|| reader == "<" || reader == ">"
				|| reader == "<=" || reader == ">=" || reader == "!=" || reader == "==")
			{
				
				//should automatically convert operands to int
				operand2 = stoi(st2.top());
				st2.pop();
				operand1 = stoi(st2.top());
				st2.pop();

				 if (reader == "-")
				{
					//converts the result to a string then pushes into the stack
					st2.push(std::to_string(operand1 - operand2));
				}
				else if (reader == "+")
				{
					//converts the result to a string then pushes into the stack
					st2.push(std::to_string(operand1 + operand2));

				}
				else if (reader == "%")
				{
					//converts the result to a string then pushes into the stack
					st2.push(std::to_string(operand1 % operand2));

				}
				else if (reader == "*")
				{
					//converts the result to a string then pushes into the stack
					st2.push(std::to_string(operand1 * operand2));
					

				}
				else if (reader == "/")
				{
					//converts the result to a string then pushes into the stack
					st2.push(std::to_string(operand1 / operand2));

				}
				else if (reader == "<")
				{
					stBool.push(operand1 < operand2);
				}
				else if (reader == "!=")
				{
					stBool.push(operand1 != operand2);
					
				}
				else if (reader == ">")
				{
					stBool.push(operand1 > operand2);
				}
				else if (reader == "<=")
				{
					stBool.push(operand1 <= operand2);
				}
				else if (reader == ">=")
				{
					stBool.push(operand1 >= operand2);
				}

				else if (reader == "==")
				{
					stBool.push(operand1 == operand2);
				}
				
				
			}

			

		}

		//clear postfixVect 
		postfixVect.clear();
		if (stBool.size() != 0)
		{
			if (stBool.top() == true)
			{
				//cout << "true" << endl;
				return "true";
			}
			else if (stBool.top() == false)
			{
				//cout << "false" << endl;
				return "false";
			}
		}

		//cout<< st2.top() << endl;
		return st2.top();
	}
	bool presedenseCheck(std::stack<std::string> a, std::string b)
	{

		std::string top = a.top();
		//these store their presedence num 
		int val1 = 0;
		int val2 = 0;


		//check if its string or char you want 
		//geting the value for a 
		if (top == "*" || top == "/" || top == "%")
		{
			val1 = 5;
		}
		else if (top == "+" || top == "-")
		{
			val1 = 4;
		}
		else if (top == "<" || top == "<=" || top == ">" || top == ">=" || top == "!=" || top == "==")
		{
			val1 = 3;
		}
		else if (top == "not")
		{
			val1 = 2;
		}
		else if (top == "and")
		{
			val1 = 1;
		}
		else if (top == "or")
		{
			val1 = 0;
		}

		//geting the value for b
		if (b == "*" || b == "/" || b == "%")
		{
			val2 = 5;
		}
		else if (b == "+" || b == "-")
		{
			val2 = 4;
		}
		else if (b == "<" || b == "<=" || b == ">" || b == ">=" || b == "!=" || b == "==")
		{
			val2 = 3;
		}
		else if (b == "not")
		{
			val2 = 2;
		}
		else if (b == "and")
		{
			val2 = 1;
		}
		else if (b == "or")
		{
			val2 = 0;
		}

		//compare the values 
		if (val1 >= val2)
		{
			//if what is just got added to the stack is >= what was alreadly on the stack return true 
			return true;
		}
		return false; 


	}
	void storeSymbolTable(std::string varaible, int value)
	{
		symbolTable[varaible] = to_string(value);

	}
	int findSymbolTable(std::string var)
	{
		return stoi(symbolTable[var]);
	}
	void clearSymbolTable()
	{
		symbolTable.clear();
	}
	int presedenceReturn(std::string oper)
	{
		int val = 0;

		if (oper == "*" || oper == "/" || oper == "%")
		{
			val = 5;
		}
		else if (oper == "+" || oper == "-")
		{
			val = 4;
		}
		else if (oper == "<" || oper == "<=" || oper == ">" || oper == ">=" || oper == "!=" || oper == "==")
		{
			val = 3;
		}
		else if (oper == "not")
		{
			val = 2;
		}
		else if (oper == "and")
		{
			val = 1;
		}
		else if (oper == "or")
		{
			val = 0;
		}
		return val;




	}
	

}
;
#endif