#ifndef INTERFACE
#define INTERFACE

#include <iostream>
#include <vector>
#include <fstream>
#include <string> 
#include <algorithm>
#include <cctype>
#include "lexanalyzer.h"
#include "expevaluator.h"



class Interface {
private: 
	typedef vector<string> programType;
	string input; 
	bool keep;
	lexanalyzer lexAnalysis;
	Expevaluator expEvaluation; 
	
	


public: 
	bool ifConditional;
	bool ifStatement = false;
	programType programCode;
	vector <string> runVector;
	vector<string> stackVec; 
	
	void startInterface() 
	{
		string word; 
		cout << "Enter program lines or read(<filename>.py) at command line interface" << endl;
		cout << "Type help for more information or quit to exit" << endl;
		// help or quit need to have quotations 


	}

	void help(string com, bool util, bool paramter)
	{
		
		//write in the substring commands here
		//do a length check to see if it needs to do this or just do an equal to check
		//bool if something is in the parameter 
		if (com != "help" && com != "help()" && paramter == true)
		{
			
			string hCom;
			int aLength = com.length() - 6;
			//measures how many characters to get in substr
			//cout << aLength  << " this is the length" << endl; 
			//initialization might mess things up here
			hCom = com.substr(5, aLength);
			//put the result back into the help so that it goes through the if statements above
			//cout << "HCom is " << hCom << endl; 
			//make keep != true so it can break out
			//keep != true; 
			if (hCom == "quit" || hCom == "quit()")
			{
				cout << "Exits the interpreter interface" << endl;
				cout << "To exit the help utility and return to the interpreter, enter 'exit'" << endl;
				util = false;

			}
			else if (hCom == "help" || hCom == "help()")
			{
				cout << "Enters the help utility mode.";
				cout << "To exit the help utility and return to the interpreter, enter 'exit'" << endl;
				util = false;
			}
			else if (hCom == "read" || hCom == "read()")
			{
				cout << " Reads a PySub program file, <filename>.py parameter has to be provided." << endl;
				cout << "To exit the help utility and return to the interpreter, enter 'exit'" << endl;
				util = false;
			}
			else if (hCom == "show" || hCom == "show()")
			{
				cout << "Shows the lines of the program that are stored in program data structure." << endl;
				cout << "Include line number when displaying each line of code in the program" << endl;
				cout << "To exit the help utility and return to the interpreter, enter 'exit'" << endl;
				util = false;


			}
			else if (hCom == "commands")
			{
				commandDisplay();
				util = false;
			}
			//	help(hCom, false,false ); self call maybe 
			//Intro false likely but check
			//shouldn't enter help utility after
			return; 

		}

		//only intros if a command isn't used
		if (util == true)
		{
			cout << "Welcome to the help utility" << endl;
			cout << "* To exit and return to the interpreter type 'exit'" << endl;
			cout << "* To get a list of commands, type 'commands'" << endl;
			cout << "* To get a description of any command just type the command at the help> prompt" << endl;
		}



		keep = true; 
		while (keep == true)
		{
			if (input == "exit" || input == "exit()")
			{
				return;
			}
			if (com == "quit" || com == "quit()")
			{
				cout << "Exits the interpreter interface" << endl;
				cout << "To exit the help utility and return to the interpreter, enter 'exit'" << endl;
				util = false;
				
			}
			else if (com == "help" || com == "help()")
			{
				cout << "Enters the help utility mode.";
				cout << "To exit the help utility and return to the interpreter, enter 'exit'" << endl;
				util = false;
			}
			else if (com == "read" || com == "read()")
			{
				cout << " Reads a PySub program file, <filename>.py parameter has to be provided." << endl;
				cout << "To exit the help utility and return to the interpreter, enter 'exit'" << endl;
				util = false;
			}
			else if (com == "show" || com == "show()")
			{
				cout << "Shows the lines of the program that are stored in program data structure." << endl;
				cout << "Include line number when displaying each line of code in the program" << endl;
				cout << "To exit the help utility and return to the interpreter, enter 'exit'" << endl;
				util = false;
				

			}
			else if (com == "commands")
			{
				commandDisplay();
				util = false;
			}
				cout << "help>";
				cin >> input;
			//should it self call itself because of all the text before 
			//can put a bool in the paramter to not have an intro 
			
			help(input, false,false);

		}


			return;
	}

	void commandDisplay()
	{
		cout << "clear   help   quit" << endl; 
		cout << "read    show" << endl; 
		return;
	}

	void quit()
	{
		
		abort();
	}
	
	void read(vector<string> use)
	{
		//if isIF is = true don't push into runVector
		
		//check is sent here
		//substring it 
		string subString;
		for (auto text : use)
		{
			string multiuse;
			string helper;
			bool quotes = false;
			string mapFirst;
			bool is;
			string mapSecond;
			bool pushIntoRun = true;
			vector <string> forConvert;
			bool isCondition = false;
			bool keepWhitespace = false;

			if (text.substr(0, 5) == "     ")
			{
				keepWhitespace = true;
			}
			//run the comment, print, and assignment varaibles 
			for (int i = 0; i < text.length(); i++)
			{
				//x should function as the letters 
				//these are the checks for comment

				if (text[i] == 35)
				{
					//if its a comment take everything after and place it into check 

					//cout << " i is " << i; 
					//for (int j = i; j < text.length(); j++)
					//{
					//	multiuse+= text[j];
					//	//cout << "The length of the line is " << read.length(); 
					//	//cout << "This is comment at increment" << endl;
					//}
					//to break out 
					i = text.length() - 1;

				}
				else if (text[i] == 'p')
				{
					//checking for print statement
					if (i + 6 < text.length())
					{
						//cout << text.length() << endl; 
						multiuse = text.substr(i, 6);
						//cout << text.length() << endl;
						if (multiuse == "print(")
						{
							//cout << "called print(" << endl;
							//reset multiuse 
							multiuse = "";
							//in the case we want to indicate it is part of an if statment
							if (keepWhitespace == true)
							{
								multiuse += "     ";
							}



							//text.length() - 7 to try and get the ) at the end 

							for (int x = i + 6; x < text.length() - 1; x++)
							{


								if (text[x] == '\"' || text[x] == '\'')
								{
									//quotes starts on false 
									if (quotes == false)
									{
										//quotes true means that there is one quote up 
										quotes = true;

									}
									else if (quotes == true)
									{
										//quotes false means that quotes have been enclosed or doesn't exist
										quotes = false;
									}


								}

								if (text[x] == ',')
								{
									if (multiuse == "")
									{
										cout << "there is nothing in the print statement or one side of it";
										return;
									}
									if (quotes == true)
									{
										cout << "beginning quotation but no ending";
										return;
									}

								}

								if (text[x] == ')')
								{
									quotes = false;
								}
								else
									multiuse += text[x];

							}
							//quote check
							if (quotes == true)
							{
								cout << "beginning quotation but no ending for an expression";
								return;
							}
							//checking for the last parenthesis 
							if (quotes == false)
							{

								runVector.push_back(multiuse);
								i = text.length() - 1;
							}
							else
							{
								cout << "no closing parenthesis so it is invalid syntax for print()";
								return;
							}
							//cout << "pushed " + multiuse + " into the runVector" << endl; 

						}
					}
				}
				else if (text[i] == '=')
				{
					for (int z = 0; z < multiuse.size(); z++)
					{
						if (multiuse[z] == 'i')
						{
							//get up to int(input( in helper 
							helper = multiuse.substr(z, 11);
							if (helper == "int(input(\"")
							{
								helper = multiuse.substr(multiuse.length() - 3, 3);
								if (helper == "\"))")
								{
									//still would hvae the ")) we can take out later
									//quotations alrealdy checked in both if statementsread 
									//14 so that we don't have the ")) at the end
									//add the mapFirst to it and the = to show that we will do assignement later
									if (isCondition)
									{
										helper = "     " + mapFirst + "=";
									}
									else
										helper = mapFirst + "=";
									helper += multiuse.substr(11, multiuse.length() - 13);
									runVector.push_back(helper);
									pushIntoRun = false;
									break;

								}
								else
								{
									cout << "doesn't have either closing parenthesis and quotation or both";
									return;
								}


							}
						}
					}
					runVector.push_back(text);





				}
				else if (text[i] == 'i')
				{
					if (text[i + 1] == 'f')
					{
						if (text[text.size() - 1] == ':')
						{

							runVector.push_back(text);

						}
						else
						{
							cout << "incorrect use of if, no colon at the end, try removing space at the end";
							
						}
					}



				}
				else if (text[i] == 'e')
				{

					helper = text.substr(i + 1, 3);
					if (helper == "lif")
					{
						if (text[text.size() - 1] == ':')
						{

							runVector.push_back(text);
							//because if can trigger
							i = text.length();
						}
						else
						{
							cout << "incorrect use of elif, no colon at the end, try removing space at the end";
						}
					}

					if (helper == "lse")
					{
						if (text[text.size() - 1] == ':')
						{

							runVector.push_back(text);
						}
						else
						{
							cout << "incorrect use of else, no colon at the end, try removing space at the end";
						}
					}


					//reset helper 
					helper = "";
				}
				else if (text[i] == 'w')
				{
					helper = text.substr(i + 1, 4);
					if (helper == "hile")
					{
						if (text[text.size() - 1] == ':')
						{

							runVector.push_back(text);
						}
						else
						{
							cout << "incorrect use of else, no colon at the end, try removing space at the end";
						}
					}

				}

			}

		}
	}
	
	void read(string theText)
	{
		//check is sent here
		//substring it 
		string subString;
		string text;
		int tLength = theText.length() - 6;
		//check if you can intialize here or will it keep initializing
		subString = theText.substr(5, tLength);
		//cout << " substr is " << subString << endl; 
		ifstream readFile(subString);
		//for comemnts , print, and assignment 
		string multiuse; 
		string helper;
		bool quotes = false; 
		string mapFirst;
		bool is;
		string mapSecond; 
		vector<string> forConvert; 
		bool pushIntoRun = true; 
		bool isCondition = false; 
		bool keepWhitespace = false; 

		while (getline(readFile, text))
		{
			if (text.substr(0, 5) == "     ")
			{
				keepWhitespace = true;
			}
			//run the comment, print, and assignment varaibles 
			for (int i = 0; i < text.length(); i++)
			{
				//x should function as the letters 
				//these are the checks for comment
				
				if (text[i] == 35)
				{
					//if its a comment take everything after and place it into check 

					//cout << " i is " << i; 
					//for (int j = i; j < text.length(); j++)
					//{
					//	multiuse+= text[j];
					//	//cout << "The length of the line is " << read.length(); 
					//	//cout << "This is comment at increment" << endl;
					//}
					//to break out 
					i = text.length()-1 ;

				}
				else if (text[i] == 'p')
				{
					//checking for print statement
					if (i + 6 < text.length())
					{
						//cout << text.length() << endl; 
						multiuse = text.substr(i, 6);
						//cout << text.length() << endl;
						if (multiuse == "print(")
						{
							//cout << "called print(" << endl;
							//reset multiuse 
							multiuse = "";
							//in the case we want to indicate it is part of an if statment
							if (keepWhitespace == true)
							{
								multiuse += "     ";
							}

							
							
							//text.length() - 7 to try and get the ) at the end 
						
								for (int x = i + 6; x < text.length()-1; x++)
								{

									
								 if (text[x] == '\"' || text[x] == '\'')
								  {
									 //quotes starts on false 
									 if (quotes == false)
									 {
										 //quotes true means that there is one quote up 
										 quotes = true;

									 }
									 else if (quotes == true)
									 {
										 //quotes false means that quotes have been enclosed or doesn't exist
										 quotes = false;
									 }
						

								  }
									
										if (text[x] == ',')
										{
										if (multiuse == "")
										{
											cout << "there is nothing in the print statement or one side of it";
											return; 
										}
										if (quotes == true)
										{
											cout << "beginning quotation but no ending";
											return; 
										}
										
										}
										
										if (text[x] == ')')
										{
											quotes = false; 
										}
										else
										multiuse += text[x];
							
								}
								//quote check
								if (quotes == true)
								{
									cout << "beginning quotation but no ending for an expression";
										return; 
								}
								//checking for the last parenthesis 
								if (quotes == false)
								{
									
									runVector.push_back(multiuse);
									i = text.length() - 1;
								}
								else
								{
									cout << "no closing parenthesis so it is invalid syntax for print()";
									return;
								}
								//cout << "pushed " + multiuse + " into the runVector" << endl; 
						
						}
					}
				}
				else if (text[i] == '=')
				{
					for (int z = 0; z < multiuse.size(); z++)
					{
						if (multiuse[z] == 'i')
						{
							//get up to int(input( in helper 
							helper = multiuse.substr(z, 11);
							if (helper == "int(input(\"")
							{
								helper = multiuse.substr(multiuse.length() - 3, 3);
								if (helper == "\"))")
								{
									//still would hvae the ")) we can take out later
									//quotations alrealdy checked in both if statementsread 
									//14 so that we don't have the ")) at the end
									//add the mapFirst to it and the = to show that we will do assignement later
									if (isCondition)
									{
										helper = "     " + mapFirst + "=";
									}
									else
										helper = mapFirst + "=";
									helper += multiuse.substr(11, multiuse.length() - 13);
									runVector.push_back(helper);
									pushIntoRun = false;
									break;

								}
								else
								{
									cout << "doesn't have either closing parenthesis and quotation or both";
									return;
								}


							}
						}
					}
					runVector.push_back(text); 
							
							
						
									
				
				}
				else if (text[i] == 'i')
				{
					if (text[i + 1] == 'f')
					{
						if (text[text.size() - 1] == ':')
						{

							runVector.push_back(text); 

						}
						else
						{
							cout << "incorrect use of if, no colon at the end"; 
						}
					}

					

				}
				else if (text[i] == 'e')
				{
				
						helper = text.substr(i + 1, 3);
						if (helper == "lif")
						{
							if (text[text.size() - 1] == ':')
							{

								runVector.push_back(text);
								//because if can trigger
								i = text.length();
							}
							else
							{
								cout << "incorrect use of elif, no colon at the end"; 
							}
						}

						if (helper == "lse")
						{
							if (text[text.size() - 1] == ':')
							{

								runVector.push_back(text);
							}
							else
							{
								cout << "incorrect use of else, no colon at the end";
							}
						}
				

					//reset helper 
					helper = "";
				}
				else if (text[i] == 'w')
				{
					helper = text.substr(i + 1, 4);
					if (helper == "hile")
					{
						if (text[text.size() - 1] == ':')
						{

							runVector.push_back(text);
						}
						else
						{
							cout << "incorrect use of else, no colon at the end";
						}
					}
					
				}
				

			}
			//still maintains orignial function of pushing it back into programCode 
			programCode.push_back(text);


		}
	}

	void show(string tok)
	{
		string subString;
		string text;
		int tLength = 0;
		if (tok.length() > 6)
		{
			 
			tLength = tok.length() - 6;		//check if you can intialize here or will it keep initializing
			subString = tok.substr(5, tLength);
			if (subString == "token"|| subString == "Token")
			{
				for (int i = 0; i < programCode.size(); i++)
				{
				
					lexAnalysis.show(programCode[i]);
				}
				lexAnalysis.display();
			}
			/*else
			{
				cout << "Incorrect syntax try again";
			}*/

		}
		if (tok.length() > 8)
		{
		
		    tLength = tok.length() - 6;		//check if you can intialize here or will it keep initializing
			subString = tok.substr(5, tLength);
			if (subString == "variables")
			{
				cout << "Showing all the vararibles and their values" << endl;
				for (auto i = expEvaluation.symbolTable.begin(); i != expEvaluation.symbolTable.end(); i++)
				{

					cout << "Variable: " << i->first << " Value: " << i->second << endl;
				}
				
			}
			/*else
			{
				cout << "Incorrect syntax try again";
			}*/
		}

		if (tok == "show" || tok == "show()")
		{
			for (int i = 0; i < programCode.size(); i++)
			{
				cout << "[" << i << "]";
				cout << programCode[i] << endl;
				
			}
		}
		
	}
	int runConditional(string theVector, int position)
	{
		vector<string> convert;
		//so that we can change it in the loop 
		string change = theVector;
		string check = "";
		string check2 = "";
		string userInput;
		int keeper = 0;
		vector<string> run1;
		bool stay = true;
		if (theVector.substr(0, 2) == "if")
		{
			
			//take the substr from 2 because you don't want the if statement and colon
			check = theVector.substr(2, theVector.size() - 3);
			//send the text to the expression evaluator 
			//mathEvaluator(check);
			//converting the string into a vector
			for (int i = 0; i < check.size(); i++)
			{

				check2 = check[i];
				convert.push_back(check2);

			}
			check2 = mathEvaluator(convert);
			if (check2 == "false")
			{
				
				//get all of the lines that would of been executed and skip over them
				position++;
				keeper++;
				check = runVector[position];
				//get the lines that are to be executed and run them
				//this checks if the next line has an indent
				while (check.substr(0, 5) == "     ")
				{

					position++;
					keeper++;
					if (position < runVector.size())
					{
						check = runVector[position];
					}
					else if (position == runVector.size())
					{
						break;
					}
				}
				position--;
				keeper--;

				///////do a position -- for positioning 

				//using the read function that has a vector parameter to execute 
				//returning how many in the run vector have alrealdy been run
				return keeper;
			}

			else if (check2 == "true")
			{
				ifConditional = false;
				position++;
				keeper++;
				check = runVector[position];
				//get the lines that are to be executed and run them
				//this checks if the next line has an indent
				while (check.substr(0, 5) == "     ")
				{
					
						run(check);
						position++;
						keeper++;
						if (position < runVector.size())
						{
							check = runVector[position];
						}
						else if (position == runVector.size())
						{
							break; 
						}
				}
				position--;
				keeper--; 

				///////do a position -- for positioning 

				//using the read function that has a vector parameter to execute 
				//returning how many in the run vector have alrealdy been run
				return keeper; 
			
			}
			else
			{
				cout << "The expression wasn't valid";
				return 0;
				//in the case it is a number or another expressino but not t/f
			}
		}
		else if (theVector.substr(0, 4) == "elif")
		{
			//take the substr from 2 because you don't want the elif statement and colon
			check = theVector.substr(4, theVector.size() - 5);
			//send the text to the expression evaluator 
			//mathEvaluator(check);
			//converting the string into a vector
			for (int i = 0; i < check.size(); i++)
			{

				check2 = check[i];
				convert.push_back(check2);

			}
			check2 = mathEvaluator(convert);

			if ((check2 == "false" || ifConditional == false)|| ifStatement == false)
			{
				//get all of the lines that would of been executed and skip over them
				position++;
				keeper++;
				check = runVector[position];
				//get the lines that are to be executed and run them
				//this checks if the next line has an indent
				while (check.substr(0, 5) == "     ")
				{

					position++;
					keeper++;
					if (position < runVector.size())
					{
						check = runVector[position];
					}
					else if (position == runVector.size())
					{
						break;
					}
				}
				position--;
				keeper--;

				///////do a position -- for positioning 

				//using the read function that has a vector parameter to execute 
				//returning how many in the run vector have alrealdy been run
				return keeper;
			}
			else if ((check2 == "true" && ifConditional == true) && ifStatement == true)
			{
				ifConditional = false;
				position++;
				keeper++;
				check = runVector[position];
				//get the lines that are to be executed and run them
				//this checks if the next line has an indent
				while (check.substr(0, 5) == "     ")
				{

					run(check);
					position++;
					keeper++;
					if (position < runVector.size())
					{
						check = runVector[position];
					}
					else if (position == runVector.size())
					{
						break;
					}
				}
				position--;
				keeper--;

				///////do a position -- for positioning 

				//using the read function that has a vector parameter to execute 
				//returning how many in the run vector have alrealdy been run
				return keeper;

			}
			else
			{
				cout << "The expression wasn't valid";
				return 0;
				//in the case it is a number or another expressino but not t/f
			}



		}
		else if (theVector.substr(0, 4) == "else")
		{
			//doesn't have a math condition to check
	

			if (ifConditional == false || ifStatement == false)
			{
				//get all of the lines that would of been executed and skip over them
				position++;
				keeper++;
				check = runVector[position];
				//get the lines that are to be executed and run them
				//this checks if the next line has an indent
				while (check.substr(0, 5) == "     ")
				{

					position++;
					keeper++;
					if (position < runVector.size())
					{
						check = runVector[position];
					}
					else if (position == runVector.size())
					{
						break;
					}
				}
				position--;
				keeper--;

				///////do a position -- for positioning 

				//using the read function that has a vector parameter to execute 
				//returning how many in the run vector have alrealdy been run
				return keeper;
			}
			else if (ifConditional == true && ifStatement == true)
			{
				ifConditional = false; 
				position++;
				keeper++;
				check = runVector[position];
				//get the lines that are to be executed and run them
				//this checks if the next line has an indent
				while (check.substr(0, 5) == "     ")
				{

					run(check);
					position++;
					keeper++;
					if (position < runVector.size())
					{
						check = runVector[position];
					}
					else if (position == runVector.size())
					{
						break;
					}
				}
				position--;
				keeper--;

				///////do a position -- for positioning 

				//using the read function that has a vector parameter to execute 
				//returning how many in the run vector have alrealdy been run
				return keeper;

			}
			else
			{
				cout << "The expression wasn't valid";
				return 0;
				//in the case it is a number or another expressino but not t/f
			}
		}
		else if (theVector.substr(0,5) == "while")
		{
			//take the substr from 5 because you don't want the while statement 
			check = theVector.substr(5, theVector.size() - 6);
			//send the text to the expression evaluator 
			//mathEvaluator(check);
			//converting the string into a vector
			for (int i = 0; i < check.size(); i++)
			{

				check2 = check[i];
				convert.push_back(check2);

			}
			while (stay == true)
			{
				check2 = mathEvaluator(convert);
				if (check2 == "false")
				{
					
					return keeper;
				}
				else if (check2 == "true")
				{

					//get all of the lines that would of been executed and skip over them
					keeper = position + 1; 
					check = runVector[keeper];
					//get the lines that are to be executed and run them
					//this checks if the next line has an indent
					while (check.substr(0, 5) == "     ")
					{

						run(check);
						keeper++;
						if (keeper < runVector.size())
						{
							check = runVector[keeper];
						}
						else if (keeper == runVector.size())
						{
							break;
						}
					}
					keeper--;
					
					
					///////do a position -- for positioning 

					//using the read function that has a vector parameter to execute 
					//returning how many in the run vector have alrealdy been run
					//return keeper;


				}
				else
				{
					cout << "The expression wasn't valid";
					return 0;
					//in the case it is a number or another expressino but not t/f
				}




			}



		}
		return 0;
	}
	void run(string theVector)
	{
		//change this so the run is taking in theVector line by line like a get line in parameter
		//otherwise 2d Array
		string varaible = "";
		string helper = "";
		string finalVar = "";
		char check = 'a';
		bool isVariable = false; 
		int finalNum = 0; 
		vector<string> sender ; 
		vector < string > forConvert;
		string mapSecond;
		string mapFirst; 
		bool quotes = false; 
		
		//if its in quotes don't check for the symbol Table 
		//if its a comma don't print it out 
		//this is checking assignment 
		
		for (auto y : theVector)
		{
			//also can perform a substring method checking for int(input
			if (isalpha(y))
			{
				for (int x = 0; x <theVector.length(); x++)
				{
					if (theVector[x] == '=')
					{
						for (auto e : theVector)
						{
							if (e == '\'')
							{
								quotes = true;
							}
							else if (e == '\"')
							{
								quotes = true; 
							}

						}
						//for the int input
						if (quotes == true)
						{
							varaible = theVector.substr(0, x);
							varaible.erase(remove(varaible.begin(), varaible.end(), ' '), varaible.end());
							//get everything after that = 
							for (int p = x; p < theVector.length(); p++)
							{
								//this works because we alreadly checked for input(int and now it is only quotes
								if (theVector[p] == '\"' || theVector[p] == '\'')
								{
									p++;
									while (theVector[p] != '\"' && theVector[p] != '\'')
									{
										//shouldn't break out and the exectue the "," else if 
										cout << theVector[p];
										p++;
									}
									//after that do cin to get the user input 
									//cin >> mapFirst;
									getline(cin, mapFirst);
									//erase whitespace
									mapFirst.erase(remove(mapFirst.begin(), mapFirst.end(), ' '), mapFirst.end());
									expEvaluation.symbolTable.insert({ varaible,mapFirst });
									//it is finished with the statment so it can return 
									return;
								}
							}
						}

						//this is for evaluating a regular assignment operation 
						//everything before the assignement operator is the identifier 
						//i-1 to not include the assignement operator 
						if (quotes == false)
						{
							varaible = theVector.substr(0, x);
							//check if there is whitespace 
							for (int y = 0; y < varaible.length(); y++)
							{
								//if its whitespace check if the left and right have a letter
								//if it does hav e aletter the identifier is two words so invalid
								if (varaible[y] == 32)
								{
									//this is ending and beginning whitespace
									if (y != 0 && y != varaible.length() - 1)
									{
										if (isalpha(varaible[y - 1]) && isalpha(varaible[y + 1]))
										{
											cout << "the identifier: " + varaible + " is invalid because it has a space";
											cout << "between the identifiers";
											return;
										}
									}


								}
							}
							//store into mapFirst so that it later can be put into map 
							mapFirst = varaible;
							//erase the whitespace 
							mapFirst.erase(remove(mapFirst.begin(), mapFirst.end(), ' '), mapFirst.end());
							//the get whats after 
							varaible = theVector.substr(x + 1, theVector.length() - x);

							//this occurs in the case that there is no int(input
							//remove the whitespace
							varaible.erase(remove(varaible.begin(), varaible.end(), ' '), varaible.end());
							//check if its is an operation then send it to the evaluator if it is
							for (auto d : varaible)
							{
								if (d == '+' || d == '-' || d == '*' || d == '/' || d == '%')
								{
									for (auto b : varaible)
									{
										helper = b;
										forConvert.push_back(helper);
									}
									varaible = mathEvaluator(forConvert);
								}

								//is = isdigit(d);
								//if (is != true)
								//{

								//	cout << "the value given is not a number so it is invalid";
								//	return;
								//}
								////reseting is 
								//is = false;

							}
							//reset forConvert 
							forConvert.clear();
							mapSecond = varaible;
							//insert into the table 
							//but first check if it is alreadly in the table to replace its 
							if (expEvaluation.symbolTable.find(mapFirst) != expEvaluation.symbolTable.end())
							{
								//change its value 
								expEvaluation.symbolTable.at(mapFirst) = mapSecond;

							}
							else
							{
								expEvaluation.symbolTable.insert({ mapFirst,mapSecond });
								cout << "varaible " << mapFirst << " is " << expEvaluation.symbolTable[mapFirst] << endl;
							}
							return;

						}
					}

				}
					
			}
		}

		
		//add a whitespace to the end to help it recognize it being the end 
		theVector += " ";
		//reset varaible
		varaible = "";
		for (int i = 0; i < theVector.size(); i++)
		{
			
			 if (theVector[i] == '\"'|| theVector[i] == '\'')
			{
				//should have alreadly error checked for quotes with nothing inside 
				i++;
				 
				while (theVector[i] != '\"' && theVector[i] != '\'')
				{
					//shouldn't break out and the exectue the "," else if 
					cout << theVector[i];
					i++;
				}
				//whitespace between 
				cout << " "; 

			}
			else if (theVector[i] == '*' || theVector[i] == '+' || theVector[i] == '/' || theVector[i] == '-' || theVector[i] == '%' || (theVector[i] == 32 && varaible.size() != 0))
			{
				 
				//get the substring of the varaible by whitespace or if it runs into an operator
				//goes outside on either a whitespace or a value and that still needs to be handled 
				//check if its a varible or a value 
				for (auto x : varaible)
				{
					//to tell if its a varaible or a number 
					if (isalpha(x))
					{
						//means its a vararible 
						isVariable = true;
					}
				}

				if (isVariable)
				{
					//then you 	//add x to the i count to account for change  a symbol table check 
					if (expEvaluation.symbolTable.find(varaible) != expEvaluation.symbolTable.end())
					{
						//means it is in symbolTable 
						varaible = expEvaluation.symbolTable[varaible];
						//should work but also might have problems using it in the same statement 
						//finalVar has the number to be converted 
						cout << varaible + " ";

					}
					else
					{
						//means that it is unknown and an error 
						cout << "the variable given is unknown ";
						return;
					}
				}

				//actually it converts inside of evaluator and evaluator only takes strings 
				if(isVariable != true)
				sender.push_back(varaible);
				//push back the operator as well for the evaluator(
			     if (theVector[i] == '*' || theVector[i] == '+' || theVector[i] == '/' || theVector[i] == '-' || theVector[i] == '%')
			     {
				 varaible = theVector[i];
				 sender.push_back(varaible);
					
			     }
			 //reset is Variable 
			 isVariable = false;
			 varaible = "";
			
			}
			else if (isalpha(theVector[i]) || isdigit(theVector[i]))
			{
				varaible += theVector[i];

			}
		
			

		}
		//then send the thing to the math evaluator to be evaluated 
		//but only if sender has something in it meaning its a varaible 
		if (sender.size() != 0)
		{
			cout << mathEvaluator(sender);
			cout << endl;

		}
		sender.clear();
		//cout << "varaible " << varaible << " is " << expEvaluation.symbolTable[varaible];
		
		//cout << endl;
		
	}
	
	
	void clearRunVector()
	{
		runVector.clear(); 
		return; 
	}

	string mathEvaluator(vector<string> expression)
	{
		
		expEvaluation.inflixConvertorPostfix(expression); 
		return expEvaluation.postFixEvaluator(expEvaluation.postfixVect);
	
		

		//expEvaluation.postFixEvaluator(expression); 
	}

	void conditionalWhile(string text)
	{
		vector<string> convert;
		//so that we can change it in the loop 
		string change = text; 
		string check = "";
		string check2 = "";
		string userInput; 
		vector<string> run1; 
		bool stay = true;
	
			if (text[text.size() - 1] == ':')
			{
				while (stay == true)
				{
					cout << "...";
					getline(cin, userInput);
					if (userInput == "")
					{
						 
						break;
					}
					run1.push_back(userInput);


				}
				//now check for indents 
				for (auto x : run1)
				{
					//check for indent 
					if (x.substr(0, 5) != "     ")
					{
						cout << "It isn't in correct syntax because no indent";
						return;
					}
					
				}
				//take the substr from 5 because you don't want the while statement 
				check = text.substr(5, text.size() - 6);
				//send the text to the expression evaluator 
				//mathEvaluator(check);
				//converting the string into a vector
				for (int i = 0; i < check.size(); i++)
				{

					check2 = check[i];
					convert.push_back(check2);

				}
				while (stay == true)
				{
					check2 = mathEvaluator(convert);
						if (check2 == "false")
						{
							return;
						}
						else if (check2 == "true")
						{
							
							//using the read function that has a vector parameter to execute 
							read(run1);
							//then use run to run all of the lines 
							for (auto c : runVector)
							{
								run(c);
							}
							run1.clear();


						}
						else
						{
							cout << "The expressionwasn't valid"; 
							return;
							//in the case it is a number or another expressino but not t/f
						}



					
				}
			}
			else
			stay = false; 
		
	}
	
	void conditionalIf(string text)
	{
		vector<string> convert;
		//so that we can change it in the loop 
		string change = text;
		string check = "";
		string check2 = "";
		string userInput;
		vector<string> run1;
		bool stay = true;
		//pushback text into run1
		run1.push_back(text);

			while (stay == true)
			{
				cout << "..."; 
				getline(cin, userInput);
				if (userInput == "")
				{
					break; 
				}
				run1.push_back(userInput);
			}
			read(run1);
			for (int i = 0; i < runVector.size();i++)
			{
				i += runConditional(runVector[i], i);
			}

			//clear run1
			runVector.clear();
			run1.clear();

		
	
	}

	void clear()
	{
		programCode.clear(); 
	}

};

#endif // !INTERFACE 
