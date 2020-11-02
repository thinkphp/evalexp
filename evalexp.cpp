#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <stack>
#include <algorithm>
#include <stdexcept>
#include <map>
#include <cctype>
#include <cmath>
#define FIN "evaluare.in"
#define FOUT "evaluare.out"

using namespace std;


long doOperation(char op, long left, long right) {

                 switch( op ) {

                        case '+': return left+right;
                        case '-': return left-right;
                        case '*': return left*right;                        
                        case '/': return (left/right);

                        default: {
                        	return 0;
                        }

                 }
}


void computeNextInStack(stack<long> & numberStack, stack<char> & operatorStack) {

                char op = operatorStack.top();
                     operatorStack.pop();

                long right = numberStack.top();
                     numberStack.pop();       

                long left = numberStack.top();
                     numberStack.pop();                            

                long result = doOperation(op, left, right);
                
                     numberStack.push( result );
}

unsigned int priority(char op) {

             switch( op ) {

                    case '+': 
                    case '-':
                            return 1;
                    case '*':
                    case '/':
                            return 2;
                    default: 
                            return 0;
             }
}


long parseExpression(string const expression) {

    stack<long> numberStack;
    stack<char> operatorStack;


    string::const_iterator pos = expression.begin();


    while(pos != expression.end()) {

               char current = *pos;

               switch(current) {

                      case '+':
                      case '-':
                      case '*':
                      case '/':

                      {

                        while(
                               !operatorStack.empty() && 

                               priority(operatorStack.top()) >= priority(current)
                             ) 

                               {
                                  computeNextInStack(numberStack, operatorStack);
                               }

                        operatorStack.push(current); 

                        break;
                      }


                      //if we have an opening paranthes, then push it on the stack, simply
                      case '(': {

                         operatorStack.push(current);

                         break;
                      }

                      //if we have a closing paranthes, then keep calculating until opending paranthes
                      case ')': {

                           if(operatorStack.empty()) {

                                      //thow a runtime error. Syntax error in expression.
                                      //no matching ')' found
                                      return 0;
                            }

                            while(operatorStack.top() != '(') {
                                   
                                  computeNextInStack(numberStack, operatorStack);
                                  

                                  if(operatorStack.empty()) {

                                      //thow a runtime error. Syntax error in expression.
                                      //no matching ')' found
                                      return 0;
                                  }
                            }

                             operatorStack.pop();
                         break;
                      }



                      default: {

                               if(isdigit(current)) {
                               //we parse the number

                                    long number = 0;
                               
                                    while( pos != expression.end() && isdigit(*pos)) {

                                     number *= 10;
                                     number += (*pos)-'0';  
                                     pos++;

                                    } 


                                    numberStack.push(static_cast<long>(number));

                                    pos--;

                               } else {
                                 //
                               }
                               
                         break;
                      }
               }

          pos++;
    }

    while(!operatorStack.empty()) {

          computeNextInStack(numberStack, operatorStack);
    }          

    return numberStack.top();  
}


int main(int argc, char const *argv[])
{

             ifstream fin(FIN); 
             ofstream fout(FOUT);

             string expression;

             getline(fin, expression);             

             long result = parseExpression(expression);

             fout<<result<<endl;

             fin.close();
             fout.close();          
	
	return 0;
}
