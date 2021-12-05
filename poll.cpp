//
//  main.cpp
//  CS31_Project3
//
//  Created by Akrit Shrikant on 10/23/20.
//
#include <string>
#include <iostream>
#include <cctype>
#include <sstream>
#include <cassert>
using namespace std;

int getNumberIndex(string data, int pos)
{
    //If we're at the end of the string, this is false because the string Cannot end with a number
    if (pos == data.size()-1)
        return 0;
    while (isdigit(data[pos]))
    {
        if(pos == data.size()-1)
            return 0;
        //making sure there are letters after number
        pos++;
    }
    return pos;
}

bool isValidUppercaseStateCode(string stateCode)
{
    //checks 2 length string for validity against list of good state codes
    const string codes =
        "AL.AK.AZ.AR.CA.CO.CT.DE.DC.FL.GA.HI.ID.IL.IN.IA.KS."
        "KY.LA.ME.MD.MA.MI.MN.MO.MS.MT.NE.NV.NH.NJ.NM.NY.NC."
        "ND.OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
    return (stateCode.size() == 2  &&
            stateCode.find('.') == string::npos  &&  // no '.' in stateCode
            codes.find(stateCode) != string::npos);  // match found
}


bool isSyntacticallyCorrect(string pollData)
{
    string upperCase;
    if (pollData.empty())
        return true;
    //getting string uppercase
    
    for (size_t k = 0; k != pollData.size(); k++)
        upperCase += toupper(pollData.at(k));
    //looping thru string first
    /*for (int i = 0; i < upperCase.size(); i++)
    {
        //checking for non numbers/letters
        if ((!(isdigit(upperCase[i])) && !(isalpha(upperCase[i]))))
            return false;
    }*/
    int j = 0;
    while (j < upperCase.size())
    {
        //if character is a digit, state code must come next
        if(isdigit(upperCase.at(j)))
        {
            int k = j;
            //incrementing til there are no more digits
            j = getNumberIndex(upperCase, j);
            if (j == 0)
                return false;
            if (j - k > 2)
                return false;
            //getting state code, substring of 2
            string stateChecker = upperCase.substr(j,2);
            //if state code aint valid
            if (!isValidUppercaseStateCode(stateChecker))
                return false;
            //if party isnt an alphabet or there is no party code
            if ((j+2) >= upperCase.size())
                return false;
            if (!isalpha(upperCase.at(j+2)))
                return false;
            //j is currently at start of state code. This takes it to the next int
            j+=3;
            //if end of code is here, it works fine
            if (j == upperCase.size())
                break;
        }
        else
            return false;
        
    }
    
    return true;
}
                
int tallyVotes(string pollData, char party, int& voteTally)
{
    int startFromZero = 0;
    int numberConv;
    string number;
    //checking if data is valid
    if(! isSyntacticallyCorrect(pollData))
        return 1;
    //checking if party is not a character
    if (! isalpha(party))
        return 2;
    if (pollData.empty())
    {
        voteTally = 0;
        return 0;
    }
    //looping thru pollData n checking for 0 elec votes
    for (int k = 0; k < pollData.size(); k += 3)
    {
        number = "";
        numberConv = 0;
        while(isdigit(pollData.at(k)))
        {
            number += pollData.at(k);
            k++;
        }
        //converting string to int
        stringstream intValue(number);
        intValue >> numberConv;
        if (numberConv == 0)
            return 3;
        //if not 0 votes and party matches char, add votes to start from zero
        if(toupper(pollData.at(k+2)) == toupper(party))
            startFromZero += numberConv;
    }
    voteTally = startFromZero;
    return 0;
}

int main()
{
}
