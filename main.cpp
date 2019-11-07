#include <iostream>


using namespace std;

void clearAllSpaces(string *str)
{
    string resultString = "";
    for (int i = 0; i < str->length(); ++i)
    {
        if(str->at(i)!=' ')
        {
            resultString.append(1,str->at(i));
        }
    }
    str->clear();
    str->append(resultString);
}

bool isStatement(string input)
{

}

bool isStatementComparingConstruction(string input)
{
    string comparingSigns[]{"==","<",">","<=",">=","!="};
    bool isFound = false;
    string stringFound = "";
    for(int i = 0;i< sizeof(comparingSigns)/ sizeof(string);i++)
    {
        if(input.find(comparingSigns[i])!=string::npos)
        {
            isFound^= true;
            stringFound = comparingSigns[i];
        }
    }
    if(isFound)
    {
        return isStatement(input.substr(0,input.find(stringFound)))
        &&isStatement(input.substr(input.find(stringFound)+stringFound.length()-1));
    }
}

bool isBoolExpression(string input)
{
    if(input[0] == '!')
    {
        input.erase(0,1);
    }

    int openedBracketIndex = input.find('(');
    if(openedBracketIndex!=string::npos)
    {
        int closedBracketIndex = -1;
        int openedBracketsAmount = 1;
        int closedBracketsAmount = 0;
        for (int i = openedBracketIndex+1;i < input.length(); i++)
        {
              if(input[i] == '(')
              {
                  openedBracketsAmount++;
              } else if(input[i] == ')')
              {
                  closedBracketsAmount++;
                  if(closedBracketsAmount == openedBracketsAmount)
                  {
                      closedBracketIndex = i;
                      break;
                  }
              }
        }
        if(isBoolExpression(input.substr(openedBracketIndex+1,closedBracketIndex-openedBracketIndex-1)))
        {
            input.erase(openedBracketIndex,closedBracketIndex-openedBracketIndex+1);
            input.insert(openedBracketIndex,"true");
        }
        else
        {
            return false;
        }
    }

    if(input == "true" || input == "false")
    {
        return true;
    }

    /* if(input[0]>='0'&&input[0]<='9')
    {
        cerr<<"Unallowed variable name."<<endl;
    }*/


    if(isStatementComparingConstruction(input))
    {
        return true;
    }

    if(input.find("||")!=string::npos)
    {
        return isBoolExpression(input.substr(0,input.find("||")))&&isBoolExpression(input.substr(input.find("||")+1));
    }
    else if(input.find("&&")!=string::npos)
    {
        return isBoolExpression(input.substr(0,input.find("&&")))&&isBoolExpression(input.substr(input.find("&&")+1));
    }
    else if(input.find("^")!=string::npos)
    {
        return isBoolExpression(input.substr(0,input.find("^")))&&isBoolExpression(input.substr(input.find("^")));
    }

    return false;
}

bool isIfConstruction(string input)
{
    clearAllSpaces(&input);
    if(input.substr(0,3) == "if(")
    {
        input.erase(0,3);
        if(isBoolExpression(input.substr(0,input.find("){"))))
        {
            cout<<"Everything is right";
            return true;
        }
        else
        {
            cerr<<"Error recognising your string expected <bool expression>, found "<<input.substr(0,input.find(')'))<<endl;
            return false;
        }
    }
    else
    {
        cerr<<"Error recognising your string. Expected \"if(\", found \""<<input.substr(0,3)<<"\""<<endl;
        return false;
    }
}

int main() {
    string lol;
    getline(cin,lol);
    clearAllSpaces(&lol);

    cout<<endl<<isIfConstruction(lol);
    return 0;
}