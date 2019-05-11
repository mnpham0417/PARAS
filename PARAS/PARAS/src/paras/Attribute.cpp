#include "paras/Attribute.hpp"
#include "util/Convert.hpp"
#include "util/json/json.h"

#include <algorithm>
#include <limits>
#include <iostream>
#include <string>

using namespace PARASProgram;

/**
 * @brief Attribute::Attribute constructor
 * @param name the name of the attribute
 * @param attributes the values that belong in this attribute.
 * @param names the names of those attributes.
 */
Attribute::Attribute(string* name, vector<string> *attributes, vector<string> *names)
{
    this->attributeMembers = attributes;
    this->name = name;
    this->memberNames = names;
    this->minAttr = std::numeric_limits<int>::max();
    this->maxAttr = std::numeric_limits<int>::min();
    for(vector<string>::iterator j = attributes->begin(); j != attributes->end(); ++j)
    {
        int jVal = Convert::stringToInt(&(*j));
        if(jVal < minAttr) minAttr = jVal;
        if(jVal > maxAttr) maxAttr = jVal;
    }
}

/**
 * @brief Attribute::convertToNamed converts the given vector of values to named values.
 * @param toBeConverted the vector of numerical values to be converted.
 * @param putHere the cache to place the converted values into
 */
void Attribute::convertToNamed(vector<string*> *toBeConverted, vector<string*> *putHere)
{
    for(vector<string*>::iterator i = toBeConverted->begin(); i != toBeConverted->end(); ++i)
    {
        string *valPtr = *i;
        string val = *valPtr;
        string *nameForValue = new string(getNameForValue(val));
        if(nameForValue->compare("") != 0 && name->compare("") != 0)
        {
            (*nameForValue) = *name+ "="+(*nameForValue).substr(0,3);
            putHere->push_back(nameForValue);
        } else if (nameForValue->compare("") != 0) {
            (*nameForValue) = (*nameForValue);
            putHere->push_back(nameForValue);
        }
    }
}

/**
 * @brief Attribute::getAttributeName
 * @return the attribute name
 */
string* Attribute::getAttributeName()
{
    return this->name;
}

/**
 * @brief Attribute::detailText returns the detail text for the given vector of values.
 * @param fromVector the vector to return detail text for.
 * @param count the index of the given value.
 * @return the detail text of the attribute information.
 */
string Attribute::detailText(vector<string*> *fromVector, int count)
{
    string *fromCount = Convert::intToString(count);
    for(vector<string*>::iterator i = fromVector->begin(); i != fromVector->end(); ++i)
    {
        string val = *(*i);
        string nameForValue = getNameForValue(val);
        if(nameForValue.compare("") != 0)
        {
            return "<b>(" + *fromCount + ") " + *this->name + "</b>" + ": " + nameForValue + "<br>";
        }
    }
    return "";
}

/**
 * @brief Attribute::getNameForValue returns the corresponding name for the attribute member
 * @param member the member to map to an actual name
 * @return the name of the attribute member.
 */
string Attribute::getNameForValue(string member)
{
    vector<string>::iterator locale = std::find(attributeMembers->begin(), attributeMembers->end(), member);
    if(locale == attributeMembers->end()) return "";

    int index = locale - attributeMembers->begin();

    return memberNames->at(index);
}

/**
 * @brief Attribute::getValueForName returns the value corresponding to the given name
 * @param member the member to map to a numerical value.
 * @return  the value of the given name/
 */
string Attribute::getValueForName(string member)
{
    vector<string>::iterator locale = std::find(attributeMembers->begin(), attributeMembers->end(), member);
    if(locale == memberNames->end()) return "";

    int index = locale - memberNames->begin();

    return attributeMembers->at(index);
}

/**
 * @brief Attribute::isMember
 * @param possibleMember the member to check
 * @return if the member is part of this attribute or not
 */
bool Attribute::isMember(string possibleMember)
{
    return std::find(attributeMembers->begin(), attributeMembers->end(), possibleMember) != attributeMembers->end();
}

/**
 * @brief Attribute::getRelativePosition
 * @param attribute the attribute to check
 * @return the relative position compared to the rest of the members of the attribute.
 */
double Attribute::getRelativePosition(string attribute)
{
    string realAttr = attribute;
    if(!isMember(realAttr)) return 1;
    if(maxAttr == minAttr) return 1;
    return (Convert::stringToInt(&realAttr) - minAttr) / (maxAttr - minAttr);
}

/**
 * @brief Attribute::jsonify
 * @return the json representation of the attribute.
 */
Json::Value  Attribute::jsonify()
{
    Json::Value attrRoot;
    attrRoot["name"] = *this->name;
    attrRoot["mapped"] = this->mapped;
    for(size_t i = 0; i < this->attributeMembers->size(); i++)
    {
        attrRoot["val"].append((attributeMembers->at(i)));
    }

    for(size_t i = 0; i < this->memberNames->size(); i++)
    {
        attrRoot["names"].append((memberNames->at(i)));
    }

    return attrRoot;
}

