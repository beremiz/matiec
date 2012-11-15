/*
 *  matiec - a compiler for the programming languages defined in IEC 61131-3
 *
 *  Copyright (C) 2009-2012  Mario de Sousa (msousa@fe.up.pt)
 *  Copyright (C) 2012       Manuele Conti  (conti.ma@alice.it)
 *
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * This code is made available on the understanding that it will not be
 * used in safety-critical situations without a full and competent review.
 */

/*
 * An IEC 61131-3 compiler.
 *
 * Based on the
 * FINAL DRAFT - IEC 61131-3, 2nd Ed. (2001-12-10)
 *
 */


#include "derived_conversion_functions.hh"
#include <sstream>

static const int debug = 0;

derived_conversion_functions_c::derived_conversion_functions_c(symbol_c *ignore) {

}

derived_conversion_functions_c::~derived_conversion_functions_c(void) {

}

std::string &derived_conversion_functions_c::get_declaration(symbol_c *root) {
    text = "";
    if (NULL != root) {
        root->accept(*this);
    }

    return text;
}

void *derived_conversion_functions_c::visit(identifier_c *symbol) {
    currentToken = symbol->value;

    return NULL;
}

void *derived_conversion_functions_c::visit(enumerated_type_declaration_c *symbol) {
    std::string enumerateName;
    std::string functionName;
    std::list <std::string> enumerateValues;

    symbol->enumerated_type_name->accept(*this);
    enumerateName = currentToken;

    symbol->enumerated_spec_init->accept(*this);
    enumerateValues = currentTokenList;

    printStringToEnum  (enumerateName, enumerateValues);
    printEnumToString  (enumerateName, enumerateValues);
    for (size_t s = 8; s <= 64; s*= 2) {
        printIntegerToEnum (enumerateName, enumerateValues, true , s);
        printEnumToInteger (enumerateName, enumerateValues, true , s);
        printIntegerToEnum (enumerateName, enumerateValues, false, s);
        printEnumToInteger (enumerateName, enumerateValues, false, s);
    }
    if (debug) std::cout << text << std::endl;
    
    return NULL;
}

void *derived_conversion_functions_c::visit(enumerated_value_list_c *symbol) {
    list_c *list;

    currentTokenList.clear();
    list = (list_c *)symbol;
    for (int i = 0; i < list->n; i++) {
        list->elements[i]->accept(*this);
        currentTokenList.push_back(currentToken);
    }

    return NULL;
}

std::string derived_conversion_functions_c::getIntegerName(bool isSigned, size_t size) {
    std::string integerType = "";
    if (! isSigned) {
        integerType = "U";
    }
    switch(size) {
    case 8 : integerType += "S"; break;
    case 16:                     break;
    case 32: integerType += "D"; break;
    case 64: integerType += "L"; break;
    default:                     break;
    }
    integerType +="INT";

    return integerType;
}

void derived_conversion_functions_c::printStringToEnum  (std::string &enumerateName, std::list<std::string> &enumerateValues) {
    std::list <std::string>::const_iterator itr;
    std::string functionName;

    functionName = "STRING_TO_" + enumerateName;
    text += "FUNCTION " + functionName + " : " + enumerateName;
    text += "\nVAR_INPUT\nIN : STRING;\nEND_VAR\n";
    for (itr = enumerateValues.begin(); itr != enumerateValues.end(); ++itr) {
       std::string value = *itr;
       text += "IF IN = '" + value + "' THEN\n";
       text += " " + functionName + " := " + value + ";\n";
       text += " RETURN;\n";
       text += "END_IF;\n";
    }
    text += "END_FUNCTION\n\n";
}

void derived_conversion_functions_c::printEnumToString  (std::string &enumerateName, std::list<std::string> &enumerateValues) {
    std::list <std::string>::const_iterator itr;
    std::string functionName;

    functionName = enumerateName + "_TO_STRING";
    text += "FUNCTION " + functionName + " : STRING";
    text += "\nVAR_INPUT\nIN : " + enumerateName + ";\nEND_VAR\n";
    for (itr = enumerateValues.begin(); itr != enumerateValues.end(); ++itr) {
        std::string value = *itr;
        text += "IF IN = " + value + " THEN\n";
        text += " " + functionName + " := '" + value + "';\n";
        text += " RETURN;\n";
        text += "END_IF;\n";
    }
    text += "END_FUNCTION\n\n";
}

void derived_conversion_functions_c::printIntegerToEnum (std::string &enumerateName, std::list<std::string> &enumerateValues, bool isSigned, size_t size) {
    std::list <std::string>::const_iterator itr;
    std::string functionName;
    std::string integerType;
    int count;

    integerType  = getIntegerName(isSigned, size);
    functionName = integerType + "_TO_" + enumerateName;
    text += "FUNCTION " + functionName + " : " + enumerateName;
    text += "\nVAR_INPUT\nIN : " + integerType + ";\nEND_VAR\n";
    count = 0;
    for (itr = enumerateValues.begin(); itr != enumerateValues.end(); ++itr) {
        std::string value = *itr;
        std::stringstream out;
        out << count;
        text += "IF IN = " + out.str() + " THEN\n";
        text += " " + functionName + " := " + value + ";\n";
        text += " RETURN;\n";
        text += "END_IF;\n";
        count++;
    }
    text += "END_FUNCTION\n\n";
}

void derived_conversion_functions_c::printEnumToInteger (std::string &enumerateName, std::list<std::string> &enumerateValues, bool isSigned, size_t size) {
    std::list <std::string>::const_iterator itr;
    std::string functionName;
    std::string integerType;
    int count;

    integerType  = getIntegerName(isSigned, size);
    functionName = enumerateName + "_TO_" + integerType;
    text += "FUNCTION " + functionName + " : " + integerType;
    text += "\nVAR_INPUT\nIN : " + enumerateName + ";\nEND_VAR\n";
    count = 0;
    for (itr = enumerateValues.begin(); itr != enumerateValues.end(); ++itr) {
        std::string value = *itr;
        std::stringstream out;
        out << count;
        text += "IF IN = " + value + " THEN\n";
        text += " " + functionName + " := " + out.str() + ";\n";
        text += " RETURN;\n";
        text += "END_IF;\n";
        count++;
    }
    text += "END_FUNCTION\n\n";
}



