/*
 * (c) 2008 Edouard TISSERANT
 *
 * Offered to the public under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details.
 *
 * This code is made available on the understanding that it will not be
 * used in safety-critical situations without a full and competent review.
 */

/*
 * An IEC 61131-3 IL and ST compiler.
 *
 * Based on the
 * FINAL DRAFT - IEC 61131-3, 2nd Ed. (2001-12-10)
 *
 */

/****
 * IEC 61131-3 standard function library
 * generated code, do not edit by hand
 */
 
 
switch(current_function_type){

/****
 *REAL_TO_SINT
 */
    case function_real_to_sint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::real_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::sint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_real_to_sint*/
    break;

/****
 *REAL_TO_LINT
 */
    case function_real_to_lint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::real_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::lint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_real_to_lint*/
    break;

/****
 *REAL_TO_DINT
 */
    case function_real_to_dint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::real_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::dint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_real_to_dint*/
    break;

/****
 *REAL_TO_DATE
 */
    case function_real_to_date :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::real_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__real_to_time"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::date_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_real_to_date*/
    break;

/****
 *REAL_TO_DWORD
 */
    case function_real_to_dword :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::real_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::dword_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_real_to_dword*/
    break;

/****
 *REAL_TO_DT
 */
    case function_real_to_dt :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::real_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__real_to_time"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::dt_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_real_to_dt*/
    break;

/****
 *REAL_TO_TOD
 */
    case function_real_to_tod :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::real_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__real_to_time"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::tod_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_real_to_tod*/
    break;

/****
 *REAL_TO_UDINT
 */
    case function_real_to_udint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::real_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::udint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_real_to_udint*/
    break;

/****
 *REAL_TO_WORD
 */
    case function_real_to_word :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::real_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::word_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_real_to_word*/
    break;

/****
 *REAL_TO_STRING
 */
    case function_real_to_string :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::real_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__real_to_string"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::string_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_real_to_string*/
    break;

/****
 *REAL_TO_LWORD
 */
    case function_real_to_lword :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::real_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::lword_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_real_to_lword*/
    break;

/****
 *REAL_TO_UINT
 */
    case function_real_to_uint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::real_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::uint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_real_to_uint*/
    break;

/****
 *REAL_TO_LREAL
 */
    case function_real_to_lreal :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::real_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::lreal_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_real_to_lreal*/
    break;

/****
 *REAL_TO_BYTE
 */
    case function_real_to_byte :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::real_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::byte_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_real_to_byte*/
    break;

/****
 *REAL_TO_USINT
 */
    case function_real_to_usint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::real_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::usint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_real_to_usint*/
    break;

/****
 *REAL_TO_ULINT
 */
    case function_real_to_ulint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::real_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::ulint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_real_to_ulint*/
    break;

/****
 *REAL_TO_BOOL
 */
    case function_real_to_bool :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::real_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::bool_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_real_to_bool*/
    break;

/****
 *REAL_TO_TIME
 */
    case function_real_to_time :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::real_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__real_to_time"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::time_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_real_to_time*/
    break;

/****
 *REAL_TO_INT
 */
    case function_real_to_int :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::real_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::int_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_real_to_int*/
    break;

/****
 *SINT_TO_REAL
 */
    case function_sint_to_real :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::sint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::real_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_sint_to_real*/
    break;

/****
 *SINT_TO_LINT
 */
    case function_sint_to_lint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::sint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::lint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_sint_to_lint*/
    break;

/****
 *SINT_TO_DINT
 */
    case function_sint_to_dint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::sint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::dint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_sint_to_dint*/
    break;

/****
 *SINT_TO_DATE
 */
    case function_sint_to_date :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::sint_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__int_to_time"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::date_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_sint_to_date*/
    break;

/****
 *SINT_TO_DWORD
 */
    case function_sint_to_dword :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::sint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::dword_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_sint_to_dword*/
    break;

/****
 *SINT_TO_DT
 */
    case function_sint_to_dt :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::sint_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__int_to_time"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::dt_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_sint_to_dt*/
    break;

/****
 *SINT_TO_TOD
 */
    case function_sint_to_tod :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::sint_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__int_to_time"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::tod_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_sint_to_tod*/
    break;

/****
 *SINT_TO_UDINT
 */
    case function_sint_to_udint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::sint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::udint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_sint_to_udint*/
    break;

/****
 *SINT_TO_WORD
 */
    case function_sint_to_word :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::sint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::word_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_sint_to_word*/
    break;

/****
 *SINT_TO_STRING
 */
    case function_sint_to_string :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::sint_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__sint_to_string"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::string_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_sint_to_string*/
    break;

/****
 *SINT_TO_LWORD
 */
    case function_sint_to_lword :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::sint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::lword_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_sint_to_lword*/
    break;

/****
 *SINT_TO_UINT
 */
    case function_sint_to_uint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::sint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::uint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_sint_to_uint*/
    break;

/****
 *SINT_TO_LREAL
 */
    case function_sint_to_lreal :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::sint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::lreal_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_sint_to_lreal*/
    break;

/****
 *SINT_TO_BYTE
 */
    case function_sint_to_byte :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::sint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::byte_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_sint_to_byte*/
    break;

/****
 *SINT_TO_USINT
 */
    case function_sint_to_usint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::sint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::usint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_sint_to_usint*/
    break;

/****
 *SINT_TO_ULINT
 */
    case function_sint_to_ulint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::sint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::ulint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_sint_to_ulint*/
    break;

/****
 *SINT_TO_BOOL
 */
    case function_sint_to_bool :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::sint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::bool_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_sint_to_bool*/
    break;

/****
 *SINT_TO_TIME
 */
    case function_sint_to_time :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::sint_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__int_to_time"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::time_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_sint_to_time*/
    break;

/****
 *SINT_TO_INT
 */
    case function_sint_to_int :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::sint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::int_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_sint_to_int*/
    break;

/****
 *LINT_TO_REAL
 */
    case function_lint_to_real :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::lint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::real_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_lint_to_real*/
    break;

/****
 *LINT_TO_SINT
 */
    case function_lint_to_sint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::lint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::sint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_lint_to_sint*/
    break;

/****
 *LINT_TO_DINT
 */
    case function_lint_to_dint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::lint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::dint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_lint_to_dint*/
    break;

/****
 *LINT_TO_DATE
 */
    case function_lint_to_date :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::lint_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__int_to_time"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::date_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_lint_to_date*/
    break;

/****
 *LINT_TO_DWORD
 */
    case function_lint_to_dword :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::lint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::dword_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_lint_to_dword*/
    break;

/****
 *LINT_TO_DT
 */
    case function_lint_to_dt :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::lint_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__int_to_time"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::dt_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_lint_to_dt*/
    break;

/****
 *LINT_TO_TOD
 */
    case function_lint_to_tod :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::lint_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__int_to_time"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::tod_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_lint_to_tod*/
    break;

/****
 *LINT_TO_UDINT
 */
    case function_lint_to_udint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::lint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::udint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_lint_to_udint*/
    break;

/****
 *LINT_TO_WORD
 */
    case function_lint_to_word :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::lint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::word_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_lint_to_word*/
    break;

/****
 *LINT_TO_STRING
 */
    case function_lint_to_string :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::lint_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__sint_to_string"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::string_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_lint_to_string*/
    break;

/****
 *LINT_TO_LWORD
 */
    case function_lint_to_lword :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::lint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::lword_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_lint_to_lword*/
    break;

/****
 *LINT_TO_UINT
 */
    case function_lint_to_uint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::lint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::uint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_lint_to_uint*/
    break;

/****
 *LINT_TO_LREAL
 */
    case function_lint_to_lreal :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::lint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::lreal_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_lint_to_lreal*/
    break;

/****
 *LINT_TO_BYTE
 */
    case function_lint_to_byte :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::lint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::byte_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_lint_to_byte*/
    break;

/****
 *LINT_TO_USINT
 */
    case function_lint_to_usint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::lint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::usint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_lint_to_usint*/
    break;

/****
 *LINT_TO_ULINT
 */
    case function_lint_to_ulint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::lint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::ulint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_lint_to_ulint*/
    break;

/****
 *LINT_TO_BOOL
 */
    case function_lint_to_bool :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::lint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::bool_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_lint_to_bool*/
    break;

/****
 *LINT_TO_TIME
 */
    case function_lint_to_time :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::lint_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__int_to_time"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::time_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_lint_to_time*/
    break;

/****
 *LINT_TO_INT
 */
    case function_lint_to_int :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::lint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::int_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_lint_to_int*/
    break;

/****
 *DINT_TO_REAL
 */
    case function_dint_to_real :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::dint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::real_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_dint_to_real*/
    break;

/****
 *DINT_TO_SINT
 */
    case function_dint_to_sint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::dint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::sint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_dint_to_sint*/
    break;

/****
 *DINT_TO_LINT
 */
    case function_dint_to_lint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::dint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::lint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_dint_to_lint*/
    break;

/****
 *DINT_TO_DATE
 */
    case function_dint_to_date :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::dint_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__int_to_time"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::date_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_dint_to_date*/
    break;

/****
 *DINT_TO_DWORD
 */
    case function_dint_to_dword :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::dint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::dword_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_dint_to_dword*/
    break;

/****
 *DINT_TO_DT
 */
    case function_dint_to_dt :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::dint_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__int_to_time"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::dt_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_dint_to_dt*/
    break;

/****
 *DINT_TO_TOD
 */
    case function_dint_to_tod :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::dint_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__int_to_time"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::tod_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_dint_to_tod*/
    break;

/****
 *DINT_TO_UDINT
 */
    case function_dint_to_udint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::dint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::udint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_dint_to_udint*/
    break;

/****
 *DINT_TO_WORD
 */
    case function_dint_to_word :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::dint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::word_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_dint_to_word*/
    break;

/****
 *DINT_TO_STRING
 */
    case function_dint_to_string :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::dint_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__sint_to_string"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::string_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_dint_to_string*/
    break;

/****
 *DINT_TO_LWORD
 */
    case function_dint_to_lword :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::dint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::lword_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_dint_to_lword*/
    break;

/****
 *DINT_TO_UINT
 */
    case function_dint_to_uint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::dint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::uint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_dint_to_uint*/
    break;

/****
 *DINT_TO_LREAL
 */
    case function_dint_to_lreal :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::dint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::lreal_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_dint_to_lreal*/
    break;

/****
 *DINT_TO_BYTE
 */
    case function_dint_to_byte :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::dint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::byte_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_dint_to_byte*/
    break;

/****
 *DINT_TO_USINT
 */
    case function_dint_to_usint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::dint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::usint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_dint_to_usint*/
    break;

/****
 *DINT_TO_ULINT
 */
    case function_dint_to_ulint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::dint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::ulint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_dint_to_ulint*/
    break;

/****
 *DINT_TO_BOOL
 */
    case function_dint_to_bool :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::dint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::bool_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_dint_to_bool*/
    break;

/****
 *DINT_TO_TIME
 */
    case function_dint_to_time :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::dint_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__int_to_time"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::time_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_dint_to_time*/
    break;

/****
 *DINT_TO_INT
 */
    case function_dint_to_int :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::dint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::int_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_dint_to_int*/
    break;

/****
 *DATE_TO_REAL
 */
    case function_date_to_real :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::date_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__time_to_real"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::real_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_date_to_real*/
    break;

/****
 *DATE_TO_SINT
 */
    case function_date_to_sint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::date_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__time_to_int"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::sint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_date_to_sint*/
    break;

/****
 *DATE_TO_LINT
 */
    case function_date_to_lint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::date_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__time_to_int"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::lint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_date_to_lint*/
    break;

/****
 *DATE_TO_DINT
 */
    case function_date_to_dint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::date_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__time_to_int"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::dint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_date_to_dint*/
    break;

/****
 *DATE_TO_DWORD
 */
    case function_date_to_dword :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::date_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__time_to_int"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::dword_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_date_to_dword*/
    break;

/****
 *DATE_TO_UDINT
 */
    case function_date_to_udint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::date_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__time_to_int"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::udint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_date_to_udint*/
    break;

/****
 *DATE_TO_WORD
 */
    case function_date_to_word :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::date_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__time_to_int"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::word_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_date_to_word*/
    break;

/****
 *DATE_TO_STRING
 */
    case function_date_to_string :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::date_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__date_to_string"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::string_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_date_to_string*/
    break;

/****
 *DATE_TO_LWORD
 */
    case function_date_to_lword :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::date_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__time_to_int"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::lword_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_date_to_lword*/
    break;

/****
 *DATE_TO_UINT
 */
    case function_date_to_uint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::date_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__time_to_int"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::uint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_date_to_uint*/
    break;

/****
 *DATE_TO_LREAL
 */
    case function_date_to_lreal :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::date_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__time_to_real"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::lreal_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_date_to_lreal*/
    break;

/****
 *DATE_TO_BYTE
 */
    case function_date_to_byte :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::date_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__time_to_int"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::byte_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_date_to_byte*/
    break;

/****
 *DATE_TO_USINT
 */
    case function_date_to_usint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::date_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__time_to_int"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::usint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_date_to_usint*/
    break;

/****
 *DATE_TO_ULINT
 */
    case function_date_to_ulint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::date_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__time_to_int"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::ulint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_date_to_ulint*/
    break;

/****
 *DATE_TO_INT
 */
    case function_date_to_int :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::date_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__time_to_int"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::int_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_date_to_int*/
    break;

/****
 *DWORD_TO_REAL
 */
    case function_dword_to_real :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::dword_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::real_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_dword_to_real*/
    break;

/****
 *DWORD_TO_SINT
 */
    case function_dword_to_sint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::dword_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::sint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_dword_to_sint*/
    break;

/****
 *DWORD_TO_LINT
 */
    case function_dword_to_lint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::dword_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::lint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_dword_to_lint*/
    break;

/****
 *DWORD_TO_DINT
 */
    case function_dword_to_dint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::dword_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::dint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_dword_to_dint*/
    break;

/****
 *DWORD_TO_DATE
 */
    case function_dword_to_date :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::dword_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__int_to_time"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::date_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_dword_to_date*/
    break;

/****
 *DWORD_TO_DT
 */
    case function_dword_to_dt :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::dword_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__int_to_time"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::dt_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_dword_to_dt*/
    break;

/****
 *DWORD_TO_TOD
 */
    case function_dword_to_tod :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::dword_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__int_to_time"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::tod_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_dword_to_tod*/
    break;

/****
 *DWORD_TO_UDINT
 */
    case function_dword_to_udint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::dword_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::udint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_dword_to_udint*/
    break;

/****
 *DWORD_TO_WORD
 */
    case function_dword_to_word :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::dword_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::word_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_dword_to_word*/
    break;

/****
 *DWORD_TO_STRING
 */
    case function_dword_to_string :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::dword_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__bit_to_string"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::string_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_dword_to_string*/
    break;

/****
 *DWORD_TO_LWORD
 */
    case function_dword_to_lword :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::dword_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::lword_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_dword_to_lword*/
    break;

/****
 *DWORD_TO_UINT
 */
    case function_dword_to_uint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::dword_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::uint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_dword_to_uint*/
    break;

/****
 *DWORD_TO_LREAL
 */
    case function_dword_to_lreal :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::dword_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::lreal_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_dword_to_lreal*/
    break;

/****
 *DWORD_TO_BYTE
 */
    case function_dword_to_byte :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::dword_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::byte_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_dword_to_byte*/
    break;

/****
 *DWORD_TO_USINT
 */
    case function_dword_to_usint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::dword_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::usint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_dword_to_usint*/
    break;

/****
 *DWORD_TO_ULINT
 */
    case function_dword_to_ulint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::dword_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::ulint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_dword_to_ulint*/
    break;

/****
 *DWORD_TO_BOOL
 */
    case function_dword_to_bool :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::dword_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::bool_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_dword_to_bool*/
    break;

/****
 *DWORD_TO_TIME
 */
    case function_dword_to_time :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::dword_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__int_to_time"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::time_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_dword_to_time*/
    break;

/****
 *DWORD_TO_INT
 */
    case function_dword_to_int :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::dword_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::int_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_dword_to_int*/
    break;

/****
 *DT_TO_REAL
 */
    case function_dt_to_real :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::dt_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__time_to_real"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::real_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_dt_to_real*/
    break;

/****
 *DT_TO_SINT
 */
    case function_dt_to_sint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::dt_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__time_to_int"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::sint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_dt_to_sint*/
    break;

/****
 *DT_TO_LINT
 */
    case function_dt_to_lint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::dt_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__time_to_int"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::lint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_dt_to_lint*/
    break;

/****
 *DT_TO_DINT
 */
    case function_dt_to_dint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::dt_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__time_to_int"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::dint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_dt_to_dint*/
    break;

/****
 *DT_TO_DWORD
 */
    case function_dt_to_dword :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::dt_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__time_to_int"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::dword_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_dt_to_dword*/
    break;

/****
 *DT_TO_UDINT
 */
    case function_dt_to_udint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::dt_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__time_to_int"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::udint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_dt_to_udint*/
    break;

/****
 *DT_TO_WORD
 */
    case function_dt_to_word :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::dt_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__time_to_int"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::word_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_dt_to_word*/
    break;

/****
 *DT_TO_STRING
 */
    case function_dt_to_string :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::dt_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__dt_to_string"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::string_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_dt_to_string*/
    break;

/****
 *DT_TO_LWORD
 */
    case function_dt_to_lword :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::dt_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__time_to_int"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::lword_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_dt_to_lword*/
    break;

/****
 *DT_TO_UINT
 */
    case function_dt_to_uint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::dt_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__time_to_int"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::uint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_dt_to_uint*/
    break;

/****
 *DT_TO_LREAL
 */
    case function_dt_to_lreal :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::dt_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__time_to_real"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::lreal_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_dt_to_lreal*/
    break;

/****
 *DT_TO_BYTE
 */
    case function_dt_to_byte :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::dt_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__time_to_int"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::byte_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_dt_to_byte*/
    break;

/****
 *DT_TO_USINT
 */
    case function_dt_to_usint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::dt_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__time_to_int"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::usint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_dt_to_usint*/
    break;

/****
 *DT_TO_ULINT
 */
    case function_dt_to_ulint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::dt_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__time_to_int"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::ulint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_dt_to_ulint*/
    break;

/****
 *DT_TO_INT
 */
    case function_dt_to_int :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::dt_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__time_to_int"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::int_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_dt_to_int*/
    break;

/****
 *TOD_TO_REAL
 */
    case function_tod_to_real :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::tod_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__time_to_real"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::real_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_tod_to_real*/
    break;

/****
 *TOD_TO_SINT
 */
    case function_tod_to_sint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::tod_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__time_to_int"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::sint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_tod_to_sint*/
    break;

/****
 *TOD_TO_LINT
 */
    case function_tod_to_lint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::tod_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__time_to_int"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::lint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_tod_to_lint*/
    break;

/****
 *TOD_TO_DINT
 */
    case function_tod_to_dint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::tod_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__time_to_int"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::dint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_tod_to_dint*/
    break;

/****
 *TOD_TO_DWORD
 */
    case function_tod_to_dword :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::tod_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__time_to_int"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::dword_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_tod_to_dword*/
    break;

/****
 *TOD_TO_UDINT
 */
    case function_tod_to_udint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::tod_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__time_to_int"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::udint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_tod_to_udint*/
    break;

/****
 *TOD_TO_WORD
 */
    case function_tod_to_word :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::tod_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__time_to_int"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::word_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_tod_to_word*/
    break;

/****
 *TOD_TO_STRING
 */
    case function_tod_to_string :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::tod_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__tod_to_string"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::string_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_tod_to_string*/
    break;

/****
 *TOD_TO_LWORD
 */
    case function_tod_to_lword :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::tod_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__time_to_int"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::lword_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_tod_to_lword*/
    break;

/****
 *TOD_TO_UINT
 */
    case function_tod_to_uint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::tod_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__time_to_int"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::uint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_tod_to_uint*/
    break;

/****
 *TOD_TO_LREAL
 */
    case function_tod_to_lreal :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::tod_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__time_to_real"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::lreal_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_tod_to_lreal*/
    break;

/****
 *TOD_TO_BYTE
 */
    case function_tod_to_byte :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::tod_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__time_to_int"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::byte_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_tod_to_byte*/
    break;

/****
 *TOD_TO_USINT
 */
    case function_tod_to_usint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::tod_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__time_to_int"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::usint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_tod_to_usint*/
    break;

/****
 *TOD_TO_ULINT
 */
    case function_tod_to_ulint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::tod_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__time_to_int"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::ulint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_tod_to_ulint*/
    break;

/****
 *TOD_TO_INT
 */
    case function_tod_to_int :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::tod_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__time_to_int"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::int_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_tod_to_int*/
    break;

/****
 *UDINT_TO_REAL
 */
    case function_udint_to_real :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::udint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::real_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_udint_to_real*/
    break;

/****
 *UDINT_TO_SINT
 */
    case function_udint_to_sint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::udint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::sint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_udint_to_sint*/
    break;

/****
 *UDINT_TO_LINT
 */
    case function_udint_to_lint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::udint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::lint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_udint_to_lint*/
    break;

/****
 *UDINT_TO_DINT
 */
    case function_udint_to_dint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::udint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::dint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_udint_to_dint*/
    break;

/****
 *UDINT_TO_DATE
 */
    case function_udint_to_date :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::udint_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__int_to_time"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::date_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_udint_to_date*/
    break;

/****
 *UDINT_TO_DWORD
 */
    case function_udint_to_dword :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::udint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::dword_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_udint_to_dword*/
    break;

/****
 *UDINT_TO_DT
 */
    case function_udint_to_dt :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::udint_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__int_to_time"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::dt_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_udint_to_dt*/
    break;

/****
 *UDINT_TO_TOD
 */
    case function_udint_to_tod :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::udint_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__int_to_time"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::tod_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_udint_to_tod*/
    break;

/****
 *UDINT_TO_WORD
 */
    case function_udint_to_word :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::udint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::word_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_udint_to_word*/
    break;

/****
 *UDINT_TO_STRING
 */
    case function_udint_to_string :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::udint_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__uint_to_string"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::string_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_udint_to_string*/
    break;

/****
 *UDINT_TO_LWORD
 */
    case function_udint_to_lword :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::udint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::lword_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_udint_to_lword*/
    break;

/****
 *UDINT_TO_UINT
 */
    case function_udint_to_uint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::udint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::uint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_udint_to_uint*/
    break;

/****
 *UDINT_TO_LREAL
 */
    case function_udint_to_lreal :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::udint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::lreal_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_udint_to_lreal*/
    break;

/****
 *UDINT_TO_BYTE
 */
    case function_udint_to_byte :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::udint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::byte_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_udint_to_byte*/
    break;

/****
 *UDINT_TO_USINT
 */
    case function_udint_to_usint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::udint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::usint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_udint_to_usint*/
    break;

/****
 *UDINT_TO_ULINT
 */
    case function_udint_to_ulint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::udint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::ulint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_udint_to_ulint*/
    break;

/****
 *UDINT_TO_BOOL
 */
    case function_udint_to_bool :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::udint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::bool_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_udint_to_bool*/
    break;

/****
 *UDINT_TO_TIME
 */
    case function_udint_to_time :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::udint_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__int_to_time"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::time_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_udint_to_time*/
    break;

/****
 *UDINT_TO_INT
 */
    case function_udint_to_int :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::udint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::int_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_udint_to_int*/
    break;

/****
 *WORD_TO_REAL
 */
    case function_word_to_real :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::word_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::real_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_word_to_real*/
    break;

/****
 *WORD_TO_SINT
 */
    case function_word_to_sint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::word_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::sint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_word_to_sint*/
    break;

/****
 *WORD_TO_LINT
 */
    case function_word_to_lint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::word_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::lint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_word_to_lint*/
    break;

/****
 *WORD_TO_DINT
 */
    case function_word_to_dint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::word_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::dint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_word_to_dint*/
    break;

/****
 *WORD_TO_DATE
 */
    case function_word_to_date :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::word_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__int_to_time"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::date_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_word_to_date*/
    break;

/****
 *WORD_TO_DWORD
 */
    case function_word_to_dword :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::word_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::dword_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_word_to_dword*/
    break;

/****
 *WORD_TO_DT
 */
    case function_word_to_dt :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::word_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__int_to_time"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::dt_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_word_to_dt*/
    break;

/****
 *WORD_TO_TOD
 */
    case function_word_to_tod :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::word_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__int_to_time"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::tod_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_word_to_tod*/
    break;

/****
 *WORD_TO_UDINT
 */
    case function_word_to_udint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::word_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::udint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_word_to_udint*/
    break;

/****
 *WORD_TO_STRING
 */
    case function_word_to_string :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::word_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__bit_to_string"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::string_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_word_to_string*/
    break;

/****
 *WORD_TO_LWORD
 */
    case function_word_to_lword :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::word_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::lword_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_word_to_lword*/
    break;

/****
 *WORD_TO_UINT
 */
    case function_word_to_uint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::word_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::uint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_word_to_uint*/
    break;

/****
 *WORD_TO_LREAL
 */
    case function_word_to_lreal :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::word_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::lreal_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_word_to_lreal*/
    break;

/****
 *WORD_TO_BYTE
 */
    case function_word_to_byte :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::word_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::byte_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_word_to_byte*/
    break;

/****
 *WORD_TO_USINT
 */
    case function_word_to_usint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::word_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::usint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_word_to_usint*/
    break;

/****
 *WORD_TO_ULINT
 */
    case function_word_to_ulint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::word_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::ulint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_word_to_ulint*/
    break;

/****
 *WORD_TO_BOOL
 */
    case function_word_to_bool :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::word_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::bool_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_word_to_bool*/
    break;

/****
 *WORD_TO_TIME
 */
    case function_word_to_time :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::word_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__int_to_time"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::time_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_word_to_time*/
    break;

/****
 *WORD_TO_INT
 */
    case function_word_to_int :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::word_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::int_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_word_to_int*/
    break;

/****
 *STRING_TO_REAL
 */
    case function_string_to_real :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::string_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__string_to_real"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::real_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_string_to_real*/
    break;

/****
 *STRING_TO_SINT
 */
    case function_string_to_sint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::string_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__string_to_sint"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::sint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_string_to_sint*/
    break;

/****
 *STRING_TO_LINT
 */
    case function_string_to_lint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::string_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__string_to_sint"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::lint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_string_to_lint*/
    break;

/****
 *STRING_TO_DINT
 */
    case function_string_to_dint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::string_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__string_to_sint"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::dint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_string_to_dint*/
    break;

/****
 *STRING_TO_DATE
 */
    case function_string_to_date :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::string_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__string_to_time"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::date_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_string_to_date*/
    break;

/****
 *STRING_TO_DWORD
 */
    case function_string_to_dword :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::string_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__string_to_bit"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::dword_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_string_to_dword*/
    break;

/****
 *STRING_TO_DT
 */
    case function_string_to_dt :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::string_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__string_to_time"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::dt_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_string_to_dt*/
    break;

/****
 *STRING_TO_TOD
 */
    case function_string_to_tod :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::string_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__string_to_time"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::tod_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_string_to_tod*/
    break;

/****
 *STRING_TO_UDINT
 */
    case function_string_to_udint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::string_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__string_to_uint"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::udint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_string_to_udint*/
    break;

/****
 *STRING_TO_WORD
 */
    case function_string_to_word :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::string_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__string_to_bit"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::word_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_string_to_word*/
    break;

/****
 *STRING_TO_LWORD
 */
    case function_string_to_lword :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::string_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__string_to_bit"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::lword_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_string_to_lword*/
    break;

/****
 *STRING_TO_UINT
 */
    case function_string_to_uint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::string_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__string_to_uint"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::uint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_string_to_uint*/
    break;

/****
 *STRING_TO_LREAL
 */
    case function_string_to_lreal :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::string_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__string_to_real"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::lreal_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_string_to_lreal*/
    break;

/****
 *STRING_TO_BYTE
 */
    case function_string_to_byte :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::string_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__string_to_bit"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::byte_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_string_to_byte*/
    break;

/****
 *STRING_TO_USINT
 */
    case function_string_to_usint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::string_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__string_to_uint"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::usint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_string_to_usint*/
    break;

/****
 *STRING_TO_ULINT
 */
    case function_string_to_ulint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::string_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__string_to_uint"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::ulint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_string_to_ulint*/
    break;

/****
 *STRING_TO_BOOL
 */
    case function_string_to_bool :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::string_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__string_to_bool"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::bool_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_string_to_bool*/
    break;

/****
 *STRING_TO_TIME
 */
    case function_string_to_time :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::string_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__string_to_time"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::time_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_string_to_time*/
    break;

/****
 *STRING_TO_INT
 */
    case function_string_to_int :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::string_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__string_to_sint"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::int_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_string_to_int*/
    break;

/****
 *LWORD_TO_REAL
 */
    case function_lword_to_real :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::lword_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::real_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_lword_to_real*/
    break;

/****
 *LWORD_TO_SINT
 */
    case function_lword_to_sint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::lword_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::sint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_lword_to_sint*/
    break;

/****
 *LWORD_TO_LINT
 */
    case function_lword_to_lint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::lword_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::lint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_lword_to_lint*/
    break;

/****
 *LWORD_TO_DINT
 */
    case function_lword_to_dint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::lword_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::dint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_lword_to_dint*/
    break;

/****
 *LWORD_TO_DATE
 */
    case function_lword_to_date :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::lword_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__int_to_time"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::date_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_lword_to_date*/
    break;

/****
 *LWORD_TO_DWORD
 */
    case function_lword_to_dword :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::lword_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::dword_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_lword_to_dword*/
    break;

/****
 *LWORD_TO_DT
 */
    case function_lword_to_dt :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::lword_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__int_to_time"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::dt_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_lword_to_dt*/
    break;

/****
 *LWORD_TO_TOD
 */
    case function_lword_to_tod :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::lword_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__int_to_time"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::tod_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_lword_to_tod*/
    break;

/****
 *LWORD_TO_UDINT
 */
    case function_lword_to_udint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::lword_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::udint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_lword_to_udint*/
    break;

/****
 *LWORD_TO_WORD
 */
    case function_lword_to_word :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::lword_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::word_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_lword_to_word*/
    break;

/****
 *LWORD_TO_STRING
 */
    case function_lword_to_string :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::lword_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__bit_to_string"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::string_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_lword_to_string*/
    break;

/****
 *LWORD_TO_UINT
 */
    case function_lword_to_uint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::lword_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::uint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_lword_to_uint*/
    break;

/****
 *LWORD_TO_LREAL
 */
    case function_lword_to_lreal :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::lword_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::lreal_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_lword_to_lreal*/
    break;

/****
 *LWORD_TO_BYTE
 */
    case function_lword_to_byte :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::lword_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::byte_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_lword_to_byte*/
    break;

/****
 *LWORD_TO_USINT
 */
    case function_lword_to_usint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::lword_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::usint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_lword_to_usint*/
    break;

/****
 *LWORD_TO_ULINT
 */
    case function_lword_to_ulint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::lword_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::ulint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_lword_to_ulint*/
    break;

/****
 *LWORD_TO_BOOL
 */
    case function_lword_to_bool :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::lword_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::bool_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_lword_to_bool*/
    break;

/****
 *LWORD_TO_TIME
 */
    case function_lword_to_time :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::lword_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__int_to_time"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::time_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_lword_to_time*/
    break;

/****
 *LWORD_TO_INT
 */
    case function_lword_to_int :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::lword_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::int_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_lword_to_int*/
    break;

/****
 *UINT_TO_REAL
 */
    case function_uint_to_real :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::uint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::real_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_uint_to_real*/
    break;

/****
 *UINT_TO_SINT
 */
    case function_uint_to_sint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::uint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::sint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_uint_to_sint*/
    break;

/****
 *UINT_TO_LINT
 */
    case function_uint_to_lint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::uint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::lint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_uint_to_lint*/
    break;

/****
 *UINT_TO_DINT
 */
    case function_uint_to_dint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::uint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::dint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_uint_to_dint*/
    break;

/****
 *UINT_TO_DATE
 */
    case function_uint_to_date :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::uint_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__int_to_time"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::date_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_uint_to_date*/
    break;

/****
 *UINT_TO_DWORD
 */
    case function_uint_to_dword :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::uint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::dword_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_uint_to_dword*/
    break;

/****
 *UINT_TO_DT
 */
    case function_uint_to_dt :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::uint_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__int_to_time"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::dt_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_uint_to_dt*/
    break;

/****
 *UINT_TO_TOD
 */
    case function_uint_to_tod :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::uint_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__int_to_time"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::tod_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_uint_to_tod*/
    break;

/****
 *UINT_TO_UDINT
 */
    case function_uint_to_udint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::uint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::udint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_uint_to_udint*/
    break;

/****
 *UINT_TO_WORD
 */
    case function_uint_to_word :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::uint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::word_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_uint_to_word*/
    break;

/****
 *UINT_TO_STRING
 */
    case function_uint_to_string :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::uint_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__uint_to_string"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::string_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_uint_to_string*/
    break;

/****
 *UINT_TO_LWORD
 */
    case function_uint_to_lword :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::uint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::lword_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_uint_to_lword*/
    break;

/****
 *UINT_TO_LREAL
 */
    case function_uint_to_lreal :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::uint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::lreal_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_uint_to_lreal*/
    break;

/****
 *UINT_TO_BYTE
 */
    case function_uint_to_byte :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::uint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::byte_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_uint_to_byte*/
    break;

/****
 *UINT_TO_USINT
 */
    case function_uint_to_usint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::uint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::usint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_uint_to_usint*/
    break;

/****
 *UINT_TO_ULINT
 */
    case function_uint_to_ulint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::uint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::ulint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_uint_to_ulint*/
    break;

/****
 *UINT_TO_BOOL
 */
    case function_uint_to_bool :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::uint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::bool_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_uint_to_bool*/
    break;

/****
 *UINT_TO_TIME
 */
    case function_uint_to_time :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::uint_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__int_to_time"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::time_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_uint_to_time*/
    break;

/****
 *UINT_TO_INT
 */
    case function_uint_to_int :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::uint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::int_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_uint_to_int*/
    break;

/****
 *LREAL_TO_REAL
 */
    case function_lreal_to_real :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::lreal_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::real_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_lreal_to_real*/
    break;

/****
 *LREAL_TO_SINT
 */
    case function_lreal_to_sint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::lreal_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::sint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_lreal_to_sint*/
    break;

/****
 *LREAL_TO_LINT
 */
    case function_lreal_to_lint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::lreal_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::lint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_lreal_to_lint*/
    break;

/****
 *LREAL_TO_DINT
 */
    case function_lreal_to_dint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::lreal_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::dint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_lreal_to_dint*/
    break;

/****
 *LREAL_TO_DATE
 */
    case function_lreal_to_date :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::lreal_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__real_to_time"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::date_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_lreal_to_date*/
    break;

/****
 *LREAL_TO_DWORD
 */
    case function_lreal_to_dword :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::lreal_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::dword_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_lreal_to_dword*/
    break;

/****
 *LREAL_TO_DT
 */
    case function_lreal_to_dt :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::lreal_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__real_to_time"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::dt_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_lreal_to_dt*/
    break;

/****
 *LREAL_TO_TOD
 */
    case function_lreal_to_tod :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::lreal_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__real_to_time"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::tod_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_lreal_to_tod*/
    break;

/****
 *LREAL_TO_UDINT
 */
    case function_lreal_to_udint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::lreal_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::udint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_lreal_to_udint*/
    break;

/****
 *LREAL_TO_WORD
 */
    case function_lreal_to_word :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::lreal_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::word_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_lreal_to_word*/
    break;

/****
 *LREAL_TO_STRING
 */
    case function_lreal_to_string :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::lreal_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__real_to_string"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::string_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_lreal_to_string*/
    break;

/****
 *LREAL_TO_LWORD
 */
    case function_lreal_to_lword :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::lreal_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::lword_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_lreal_to_lword*/
    break;

/****
 *LREAL_TO_UINT
 */
    case function_lreal_to_uint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::lreal_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::uint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_lreal_to_uint*/
    break;

/****
 *LREAL_TO_BYTE
 */
    case function_lreal_to_byte :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::lreal_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::byte_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_lreal_to_byte*/
    break;

/****
 *LREAL_TO_USINT
 */
    case function_lreal_to_usint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::lreal_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::usint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_lreal_to_usint*/
    break;

/****
 *LREAL_TO_ULINT
 */
    case function_lreal_to_ulint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::lreal_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::ulint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_lreal_to_ulint*/
    break;

/****
 *LREAL_TO_BOOL
 */
    case function_lreal_to_bool :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::lreal_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::bool_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_lreal_to_bool*/
    break;

/****
 *LREAL_TO_TIME
 */
    case function_lreal_to_time :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::lreal_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__real_to_time"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::time_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_lreal_to_time*/
    break;

/****
 *LREAL_TO_INT
 */
    case function_lreal_to_int :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::lreal_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::int_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_lreal_to_int*/
    break;

/****
 *BYTE_TO_REAL
 */
    case function_byte_to_real :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::byte_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::real_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_byte_to_real*/
    break;

/****
 *BYTE_TO_SINT
 */
    case function_byte_to_sint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::byte_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::sint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_byte_to_sint*/
    break;

/****
 *BYTE_TO_LINT
 */
    case function_byte_to_lint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::byte_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::lint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_byte_to_lint*/
    break;

/****
 *BYTE_TO_DINT
 */
    case function_byte_to_dint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::byte_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::dint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_byte_to_dint*/
    break;

/****
 *BYTE_TO_DATE
 */
    case function_byte_to_date :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::byte_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__int_to_time"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::date_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_byte_to_date*/
    break;

/****
 *BYTE_TO_DWORD
 */
    case function_byte_to_dword :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::byte_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::dword_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_byte_to_dword*/
    break;

/****
 *BYTE_TO_DT
 */
    case function_byte_to_dt :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::byte_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__int_to_time"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::dt_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_byte_to_dt*/
    break;

/****
 *BYTE_TO_TOD
 */
    case function_byte_to_tod :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::byte_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__int_to_time"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::tod_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_byte_to_tod*/
    break;

/****
 *BYTE_TO_UDINT
 */
    case function_byte_to_udint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::byte_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::udint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_byte_to_udint*/
    break;

/****
 *BYTE_TO_WORD
 */
    case function_byte_to_word :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::byte_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::word_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_byte_to_word*/
    break;

/****
 *BYTE_TO_STRING
 */
    case function_byte_to_string :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::byte_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__bit_to_string"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::string_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_byte_to_string*/
    break;

/****
 *BYTE_TO_LWORD
 */
    case function_byte_to_lword :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::byte_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::lword_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_byte_to_lword*/
    break;

/****
 *BYTE_TO_UINT
 */
    case function_byte_to_uint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::byte_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::uint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_byte_to_uint*/
    break;

/****
 *BYTE_TO_LREAL
 */
    case function_byte_to_lreal :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::byte_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::lreal_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_byte_to_lreal*/
    break;

/****
 *BYTE_TO_USINT
 */
    case function_byte_to_usint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::byte_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::usint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_byte_to_usint*/
    break;

/****
 *BYTE_TO_ULINT
 */
    case function_byte_to_ulint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::byte_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::ulint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_byte_to_ulint*/
    break;

/****
 *BYTE_TO_BOOL
 */
    case function_byte_to_bool :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::byte_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::bool_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_byte_to_bool*/
    break;

/****
 *BYTE_TO_TIME
 */
    case function_byte_to_time :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::byte_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__int_to_time"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::time_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_byte_to_time*/
    break;

/****
 *BYTE_TO_INT
 */
    case function_byte_to_int :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::byte_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::int_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_byte_to_int*/
    break;

/****
 *USINT_TO_REAL
 */
    case function_usint_to_real :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::usint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::real_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_usint_to_real*/
    break;

/****
 *USINT_TO_SINT
 */
    case function_usint_to_sint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::usint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::sint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_usint_to_sint*/
    break;

/****
 *USINT_TO_LINT
 */
    case function_usint_to_lint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::usint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::lint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_usint_to_lint*/
    break;

/****
 *USINT_TO_DINT
 */
    case function_usint_to_dint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::usint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::dint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_usint_to_dint*/
    break;

/****
 *USINT_TO_DATE
 */
    case function_usint_to_date :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::usint_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__int_to_time"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::date_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_usint_to_date*/
    break;

/****
 *USINT_TO_DWORD
 */
    case function_usint_to_dword :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::usint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::dword_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_usint_to_dword*/
    break;

/****
 *USINT_TO_DT
 */
    case function_usint_to_dt :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::usint_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__int_to_time"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::dt_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_usint_to_dt*/
    break;

/****
 *USINT_TO_TOD
 */
    case function_usint_to_tod :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::usint_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__int_to_time"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::tod_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_usint_to_tod*/
    break;

/****
 *USINT_TO_UDINT
 */
    case function_usint_to_udint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::usint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::udint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_usint_to_udint*/
    break;

/****
 *USINT_TO_WORD
 */
    case function_usint_to_word :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::usint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::word_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_usint_to_word*/
    break;

/****
 *USINT_TO_STRING
 */
    case function_usint_to_string :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::usint_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__uint_to_string"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::string_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_usint_to_string*/
    break;

/****
 *USINT_TO_LWORD
 */
    case function_usint_to_lword :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::usint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::lword_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_usint_to_lword*/
    break;

/****
 *USINT_TO_UINT
 */
    case function_usint_to_uint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::usint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::uint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_usint_to_uint*/
    break;

/****
 *USINT_TO_LREAL
 */
    case function_usint_to_lreal :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::usint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::lreal_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_usint_to_lreal*/
    break;

/****
 *USINT_TO_BYTE
 */
    case function_usint_to_byte :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::usint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::byte_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_usint_to_byte*/
    break;

/****
 *USINT_TO_ULINT
 */
    case function_usint_to_ulint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::usint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::ulint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_usint_to_ulint*/
    break;

/****
 *USINT_TO_BOOL
 */
    case function_usint_to_bool :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::usint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::bool_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_usint_to_bool*/
    break;

/****
 *USINT_TO_TIME
 */
    case function_usint_to_time :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::usint_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__int_to_time"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::time_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_usint_to_time*/
    break;

/****
 *USINT_TO_INT
 */
    case function_usint_to_int :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::usint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::int_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_usint_to_int*/
    break;

/****
 *ULINT_TO_REAL
 */
    case function_ulint_to_real :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::ulint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::real_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_ulint_to_real*/
    break;

/****
 *ULINT_TO_SINT
 */
    case function_ulint_to_sint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::ulint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::sint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_ulint_to_sint*/
    break;

/****
 *ULINT_TO_LINT
 */
    case function_ulint_to_lint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::ulint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::lint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_ulint_to_lint*/
    break;

/****
 *ULINT_TO_DINT
 */
    case function_ulint_to_dint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::ulint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::dint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_ulint_to_dint*/
    break;

/****
 *ULINT_TO_DATE
 */
    case function_ulint_to_date :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::ulint_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__int_to_time"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::date_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_ulint_to_date*/
    break;

/****
 *ULINT_TO_DWORD
 */
    case function_ulint_to_dword :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::ulint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::dword_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_ulint_to_dword*/
    break;

/****
 *ULINT_TO_DT
 */
    case function_ulint_to_dt :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::ulint_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__int_to_time"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::dt_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_ulint_to_dt*/
    break;

/****
 *ULINT_TO_TOD
 */
    case function_ulint_to_tod :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::ulint_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__int_to_time"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::tod_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_ulint_to_tod*/
    break;

/****
 *ULINT_TO_UDINT
 */
    case function_ulint_to_udint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::ulint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::udint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_ulint_to_udint*/
    break;

/****
 *ULINT_TO_WORD
 */
    case function_ulint_to_word :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::ulint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::word_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_ulint_to_word*/
    break;

/****
 *ULINT_TO_STRING
 */
    case function_ulint_to_string :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::ulint_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__uint_to_string"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::string_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_ulint_to_string*/
    break;

/****
 *ULINT_TO_LWORD
 */
    case function_ulint_to_lword :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::ulint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::lword_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_ulint_to_lword*/
    break;

/****
 *ULINT_TO_UINT
 */
    case function_ulint_to_uint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::ulint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::uint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_ulint_to_uint*/
    break;

/****
 *ULINT_TO_LREAL
 */
    case function_ulint_to_lreal :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::ulint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::lreal_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_ulint_to_lreal*/
    break;

/****
 *ULINT_TO_BYTE
 */
    case function_ulint_to_byte :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::ulint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::byte_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_ulint_to_byte*/
    break;

/****
 *ULINT_TO_USINT
 */
    case function_ulint_to_usint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::ulint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::usint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_ulint_to_usint*/
    break;

/****
 *ULINT_TO_BOOL
 */
    case function_ulint_to_bool :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::ulint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::bool_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_ulint_to_bool*/
    break;

/****
 *ULINT_TO_TIME
 */
    case function_ulint_to_time :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::ulint_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__int_to_time"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::time_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_ulint_to_time*/
    break;

/****
 *ULINT_TO_INT
 */
    case function_ulint_to_int :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::ulint_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::int_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_ulint_to_int*/
    break;

/****
 *BOOL_TO_REAL
 */
    case function_bool_to_real :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::bool_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::real_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_bool_to_real*/
    break;

/****
 *BOOL_TO_SINT
 */
    case function_bool_to_sint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::bool_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::sint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_bool_to_sint*/
    break;

/****
 *BOOL_TO_LINT
 */
    case function_bool_to_lint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::bool_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::lint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_bool_to_lint*/
    break;

/****
 *BOOL_TO_DINT
 */
    case function_bool_to_dint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::bool_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::dint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_bool_to_dint*/
    break;

/****
 *BOOL_TO_DATE
 */
    case function_bool_to_date :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::bool_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__int_to_time"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::date_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_bool_to_date*/
    break;

/****
 *BOOL_TO_DWORD
 */
    case function_bool_to_dword :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::bool_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::dword_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_bool_to_dword*/
    break;

/****
 *BOOL_TO_DT
 */
    case function_bool_to_dt :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::bool_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__int_to_time"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::dt_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_bool_to_dt*/
    break;

/****
 *BOOL_TO_TOD
 */
    case function_bool_to_tod :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::bool_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__int_to_time"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::tod_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_bool_to_tod*/
    break;

/****
 *BOOL_TO_UDINT
 */
    case function_bool_to_udint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::bool_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::udint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_bool_to_udint*/
    break;

/****
 *BOOL_TO_WORD
 */
    case function_bool_to_word :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::bool_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::word_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_bool_to_word*/
    break;

/****
 *BOOL_TO_STRING
 */
    case function_bool_to_string :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::bool_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__bool_to_string"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::string_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_bool_to_string*/
    break;

/****
 *BOOL_TO_LWORD
 */
    case function_bool_to_lword :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::bool_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::lword_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_bool_to_lword*/
    break;

/****
 *BOOL_TO_UINT
 */
    case function_bool_to_uint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::bool_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::uint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_bool_to_uint*/
    break;

/****
 *BOOL_TO_LREAL
 */
    case function_bool_to_lreal :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::bool_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::lreal_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_bool_to_lreal*/
    break;

/****
 *BOOL_TO_BYTE
 */
    case function_bool_to_byte :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::bool_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::byte_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_bool_to_byte*/
    break;

/****
 *BOOL_TO_USINT
 */
    case function_bool_to_usint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::bool_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::usint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_bool_to_usint*/
    break;

/****
 *BOOL_TO_ULINT
 */
    case function_bool_to_ulint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::bool_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::ulint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_bool_to_ulint*/
    break;

/****
 *BOOL_TO_TIME
 */
    case function_bool_to_time :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::bool_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__int_to_time"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::time_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_bool_to_time*/
    break;

/****
 *BOOL_TO_INT
 */
    case function_bool_to_int :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::bool_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::int_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_bool_to_int*/
    break;

/****
 *TIME_TO_REAL
 */
    case function_time_to_real :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::time_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__time_to_real"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::real_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_time_to_real*/
    break;

/****
 *TIME_TO_SINT
 */
    case function_time_to_sint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::time_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__time_to_int"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::sint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_time_to_sint*/
    break;

/****
 *TIME_TO_LINT
 */
    case function_time_to_lint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::time_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__time_to_int"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::lint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_time_to_lint*/
    break;

/****
 *TIME_TO_DINT
 */
    case function_time_to_dint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::time_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__time_to_int"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::dint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_time_to_dint*/
    break;

/****
 *TIME_TO_DWORD
 */
    case function_time_to_dword :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::time_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__time_to_int"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::dword_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_time_to_dword*/
    break;

/****
 *TIME_TO_UDINT
 */
    case function_time_to_udint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::time_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__time_to_int"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::udint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_time_to_udint*/
    break;

/****
 *TIME_TO_WORD
 */
    case function_time_to_word :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::time_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__time_to_int"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::word_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_time_to_word*/
    break;

/****
 *TIME_TO_STRING
 */
    case function_time_to_string :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::time_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__time_to_string"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::string_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_time_to_string*/
    break;

/****
 *TIME_TO_LWORD
 */
    case function_time_to_lword :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::time_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__time_to_int"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::lword_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_time_to_lword*/
    break;

/****
 *TIME_TO_UINT
 */
    case function_time_to_uint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::time_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__time_to_int"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::uint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_time_to_uint*/
    break;

/****
 *TIME_TO_LREAL
 */
    case function_time_to_lreal :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::time_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__time_to_real"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::lreal_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_time_to_lreal*/
    break;

/****
 *TIME_TO_BYTE
 */
    case function_time_to_byte :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::time_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__time_to_int"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::byte_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_time_to_byte*/
    break;

/****
 *TIME_TO_USINT
 */
    case function_time_to_usint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::time_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__time_to_int"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::usint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_time_to_usint*/
    break;

/****
 *TIME_TO_ULINT
 */
    case function_time_to_ulint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::time_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__time_to_int"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::ulint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_time_to_ulint*/
    break;

/****
 *TIME_TO_INT
 */
    case function_time_to_int :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::time_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__time_to_int"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::int_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_time_to_int*/
    break;

/****
 *INT_TO_REAL
 */
    case function_int_to_real :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::int_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::real_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_int_to_real*/
    break;

/****
 *INT_TO_SINT
 */
    case function_int_to_sint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::int_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::sint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_int_to_sint*/
    break;

/****
 *INT_TO_LINT
 */
    case function_int_to_lint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::int_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::lint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_int_to_lint*/
    break;

/****
 *INT_TO_DINT
 */
    case function_int_to_dint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::int_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::dint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_int_to_dint*/
    break;

/****
 *INT_TO_DATE
 */
    case function_int_to_date :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::int_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__int_to_time"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::date_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_int_to_date*/
    break;

/****
 *INT_TO_DWORD
 */
    case function_int_to_dword :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::int_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::dword_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_int_to_dword*/
    break;

/****
 *INT_TO_DT
 */
    case function_int_to_dt :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::int_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__int_to_time"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::dt_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_int_to_dt*/
    break;

/****
 *INT_TO_TOD
 */
    case function_int_to_tod :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::int_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__int_to_time"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::tod_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_int_to_tod*/
    break;

/****
 *INT_TO_UDINT
 */
    case function_int_to_udint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::int_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::udint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_int_to_udint*/
    break;

/****
 *INT_TO_WORD
 */
    case function_int_to_word :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::int_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::word_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_int_to_word*/
    break;

/****
 *INT_TO_STRING
 */
    case function_int_to_string :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::int_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__sint_to_string"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::string_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_int_to_string*/
    break;

/****
 *INT_TO_LWORD
 */
    case function_int_to_lword :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::int_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::lword_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_int_to_lword*/
    break;

/****
 *INT_TO_UINT
 */
    case function_int_to_uint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::int_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::uint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_int_to_uint*/
    break;

/****
 *INT_TO_LREAL
 */
    case function_int_to_lreal :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::int_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::lreal_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_int_to_lreal*/
    break;

/****
 *INT_TO_BYTE
 */
    case function_int_to_byte :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::int_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::byte_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_int_to_byte*/
    break;

/****
 *INT_TO_USINT
 */
    case function_int_to_usint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::int_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::usint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_int_to_usint*/
    break;

/****
 *INT_TO_ULINT
 */
    case function_int_to_ulint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::int_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::ulint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_int_to_ulint*/
    break;

/****
 *INT_TO_BOOL
 */
    case function_int_to_bool :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::int_type_name, last_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::bool_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_int_to_bool*/
    break;

/****
 *INT_TO_TIME
 */
    case function_int_to_time :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::int_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__int_to_time"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::time_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_int_to_time*/
    break;

/****
 *TRUNC
 */
    case function_trunc :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_real_type(IN_type_symbol))
            {
        
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::constant_int_type_name;
                function_type_prefix = (symbol_c*)(new pragma_c("int"));
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_trunc*/
    break;

/****
 *BCD_TO_UDINT
 */
    case function_bcd_to_udint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::dword_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__bcd_to_uint"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::udint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_bcd_to_udint*/
    break;

/****
 *BCD_TO_UINT
 */
    case function_bcd_to_uint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::word_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__bcd_to_uint"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::uint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_bcd_to_uint*/
    break;

/****
 *BCD_TO_ULINT
 */
    case function_bcd_to_ulint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::lword_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__bcd_to_uint"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::ulint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_bcd_to_ulint*/
    break;

/****
 *BCD_TO_USINT
 */
    case function_bcd_to_usint :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::byte_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__bcd_to_uint"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::usint_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_bcd_to_usint*/
    break;

/****
 *UDINT_TO_BCD
 */
    case function_udint_to_bcd :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::udint_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__uint_to_bcd"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::constant_int_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_udint_to_bcd*/
    break;

/****
 *UINT_TO_BCD
 */
    case function_uint_to_bcd :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::uint_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__uint_to_bcd"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::constant_int_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_uint_to_bcd*/
    break;

/****
 *USINT_TO_BCD
 */
    case function_usint_to_bcd :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::usint_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__uint_to_bcd"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::constant_int_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_usint_to_bcd*/
    break;

/****
 *ULINT_TO_BCD
 */
    case function_ulint_to_bcd :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::ulint_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__uint_to_bcd"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::constant_int_type_name;
                function_type_prefix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_ulint_to_bcd*/
    break;

/****
 *DATE_AND_TIME_TO_TIME_OF_DAY
 */
    case function_date_and_time_to_time_of_day :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::dt_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__date_and_time_to_time_of_day"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::tod_type_name;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_date_and_time_to_time_of_day*/
    break;

/****
 *DATE_AND_TIME_TO_DATE
 */
    case function_date_and_time_to_date :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::dt_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__date_and_time_to_date"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::date_type_name;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_date_and_time_to_date*/
    break;

/****
 *ABS
 */
    case function_abs :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_num_type(IN_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__abs_"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = IN_type_symbol;
                function_type_suffix = IN_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_abs*/
    break;

/****
 *SQRT
 */
    case function_sqrt :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_real_type(IN_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("sqrt"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = IN_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_sqrt*/
    break;

/****
 *LN
 */
    case function_ln :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_real_type(IN_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("ln"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = IN_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_ln*/
    break;

/****
 *LOG
 */
    case function_log :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_real_type(IN_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("log"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = IN_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_log*/
    break;

/****
 *EXP
 */
    case function_exp :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_real_type(IN_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("exp"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = IN_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_exp*/
    break;

/****
 *SIN
 */
    case function_sin :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_real_type(IN_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("sin"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = IN_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_sin*/
    break;

/****
 *COS
 */
    case function_cos :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_real_type(IN_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("cos"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = IN_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_cos*/
    break;

/****
 *TAN
 */
    case function_tan :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_real_type(IN_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("tan"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = IN_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_tan*/
    break;

/****
 *ASIN
 */
    case function_asin :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_real_type(IN_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("asin"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = IN_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_asin*/
    break;

/****
 *ACOS
 */
    case function_acos :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_real_type(IN_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("acos"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = IN_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_acos*/
    break;

/****
 *ATAN
 */
    case function_atan :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_real_type(IN_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("atan"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = IN_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_atan*/
    break;

/****
 *ADD
 */
    case function_add :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN1_param_value = &this->default_variable_name;
        
            symbol_c *IN1_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_num_type(IN1_type_symbol))
            {
        
                {
                    identifier_c param_name("IN2");
                    /* Get the value from a foo(<param_name> = <param_value>) style call */
                    symbol_c *IN2_param_value = function_call_param_iterator.search(&param_name);
                    
                    /* Get the value from a foo(<param_value>) style call */
                    if (IN2_param_value == NULL)
                      IN2_param_value = function_call_param_iterator.next();
                    symbol_c *IN2_type_symbol = search_expression_type->get_type(IN2_param_value);
                    last_type_symbol = last_type_symbol && search_expression_type->is_same_type(IN2_type_symbol, last_type_symbol) ? search_expression_type->common_type(IN2_type_symbol, last_type_symbol) : IN2_type_symbol ;
                    
                    if(search_expression_type->is_num_type(IN2_type_symbol))
                    {
                
                        function_name = (symbol_c*)(new pragma_c("__add_"));
                        
                        char nb_param_str[10];
                        sprintf(nb_param_str, "%d", nb_param);
                        ADD_PARAM_LIST((symbol_c*)(new integer_c(nb_param_str)), (symbol_c*)(new int_type_name_c()), function_param_iterator_c::direction_in)
                        ADD_PARAM_LIST(IN1_param_value, IN1_type_symbol, function_param_iterator_c::direction_in)
                        ADD_PARAM_LIST(IN2_param_value, IN2_type_symbol, function_param_iterator_c::direction_in)
                        
                        int base_num = 3;
                        symbol_c *param_value = NULL;
                        do{
                            char my_name[10];
                            sprintf(my_name, "IN%d", base_num++);
                            identifier_c param_name(my_name);
                            
                            /* Get the value from a foo(<param_name> = <param_value>) style call */
                            param_value = function_call_param_iterator.search(&param_name);
                            
                            /* Get the value from a foo(<param_value>) style call */
                            if (param_value == NULL)
                              param_value = function_call_param_iterator.next();
                            if (param_value != NULL){
                                symbol_c *current_type_symbol = search_expression_type->get_type(param_value);
                                last_type_symbol = last_type_symbol && search_expression_type->is_same_type(current_type_symbol, last_type_symbol) ? search_expression_type->common_type(current_type_symbol, last_type_symbol) : current_type_symbol ;
                            
                                /*Function specific CODE */
                                ADD_PARAM_LIST(param_value, current_type_symbol, function_param_iterator_c::direction_in)
                            }
                            
                        }while(param_value != NULL);
                        symbol_c * return_type_symbol = last_type_symbol;
                        function_type_suffix = return_type_symbol;
                        break;
                        
                    }
                    
                    
                    ERROR;
                }
                
            }
            
            if(search_expression_type->is_same_type(&search_constant_type_c::dt_type_name, last_type_symbol))
            {
        
                {
                    identifier_c param_name("IN2");
                    /* Get the value from a foo(<param_name> = <param_value>) style call */
                    symbol_c *IN2_param_value = function_call_param_iterator.search(&param_name);
                    
                    /* Get the value from a foo(<param_value>) style call */
                    if (IN2_param_value == NULL)
                      IN2_param_value = function_call_param_iterator.next();
                    symbol_c *IN2_type_symbol = search_expression_type->get_type(IN2_param_value);
                    last_type_symbol = last_type_symbol && search_expression_type->is_same_type(IN2_type_symbol, last_type_symbol) ? search_expression_type->common_type(IN2_type_symbol, last_type_symbol) : IN2_type_symbol ;
                    
                    if(search_expression_type->is_same_type(&search_constant_type_c::time_type_name, last_type_symbol))
                    {
                
                        function_name = (symbol_c*)(new pragma_c("__time_add"));
                        ADD_PARAM_LIST(IN1_param_value, IN1_type_symbol, function_param_iterator_c::direction_in)
                        ADD_PARAM_LIST(IN2_param_value, IN2_type_symbol, function_param_iterator_c::direction_in)
                        symbol_c * return_type_symbol = &search_constant_type_c::dt_type_name;
                        break;
                        
                    }
                    
                    
                    ERROR;
                }
                
            }
            
            if(search_expression_type->is_same_type(&search_constant_type_c::tod_type_name, last_type_symbol))
            {
        
                {
                    identifier_c param_name("IN2");
                    /* Get the value from a foo(<param_name> = <param_value>) style call */
                    symbol_c *IN2_param_value = function_call_param_iterator.search(&param_name);
                    
                    /* Get the value from a foo(<param_value>) style call */
                    if (IN2_param_value == NULL)
                      IN2_param_value = function_call_param_iterator.next();
                    symbol_c *IN2_type_symbol = search_expression_type->get_type(IN2_param_value);
                    last_type_symbol = last_type_symbol && search_expression_type->is_same_type(IN2_type_symbol, last_type_symbol) ? search_expression_type->common_type(IN2_type_symbol, last_type_symbol) : IN2_type_symbol ;
                    
                    if(search_expression_type->is_same_type(&search_constant_type_c::time_type_name, last_type_symbol))
                    {
                
                        function_name = (symbol_c*)(new pragma_c("__time_add"));
                        ADD_PARAM_LIST(IN1_param_value, IN1_type_symbol, function_param_iterator_c::direction_in)
                        ADD_PARAM_LIST(IN2_param_value, IN2_type_symbol, function_param_iterator_c::direction_in)
                        symbol_c * return_type_symbol = &search_constant_type_c::tod_type_name;
                        break;
                        
                    }
                    
                    
                    ERROR;
                }
                
            }
            
            if(search_expression_type->is_same_type(&search_constant_type_c::time_type_name, last_type_symbol))
            {
        
                {
                    identifier_c param_name("IN2");
                    /* Get the value from a foo(<param_name> = <param_value>) style call */
                    symbol_c *IN2_param_value = function_call_param_iterator.search(&param_name);
                    
                    /* Get the value from a foo(<param_value>) style call */
                    if (IN2_param_value == NULL)
                      IN2_param_value = function_call_param_iterator.next();
                    symbol_c *IN2_type_symbol = search_expression_type->get_type(IN2_param_value);
                    last_type_symbol = last_type_symbol && search_expression_type->is_same_type(IN2_type_symbol, last_type_symbol) ? search_expression_type->common_type(IN2_type_symbol, last_type_symbol) : IN2_type_symbol ;
                    
                    if(search_expression_type->is_same_type(&search_constant_type_c::time_type_name, last_type_symbol))
                    {
                
                        function_name = (symbol_c*)(new pragma_c("__time_add"));
                        ADD_PARAM_LIST(IN1_param_value, IN1_type_symbol, function_param_iterator_c::direction_in)
                        ADD_PARAM_LIST(IN2_param_value, IN2_type_symbol, function_param_iterator_c::direction_in)
                        symbol_c * return_type_symbol = &search_constant_type_c::time_type_name;
                        break;
                        
                    }
                    
                    
                    ERROR;
                }
                
            }
            
            
            ERROR;
        }
        
    }/*function_add*/
    break;

/****
 *MUL
 */
    case function_mul :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN1_param_value = &this->default_variable_name;
        
            symbol_c *IN1_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_num_type(IN1_type_symbol))
            {
        
                {
                    identifier_c param_name("IN2");
                    /* Get the value from a foo(<param_name> = <param_value>) style call */
                    symbol_c *IN2_param_value = function_call_param_iterator.search(&param_name);
                    
                    /* Get the value from a foo(<param_value>) style call */
                    if (IN2_param_value == NULL)
                      IN2_param_value = function_call_param_iterator.next();
                    symbol_c *IN2_type_symbol = search_expression_type->get_type(IN2_param_value);
                    last_type_symbol = last_type_symbol && search_expression_type->is_same_type(IN2_type_symbol, last_type_symbol) ? search_expression_type->common_type(IN2_type_symbol, last_type_symbol) : IN2_type_symbol ;
                    
                    if(search_expression_type->is_num_type(IN2_type_symbol))
                    {
                
                        function_name = (symbol_c*)(new pragma_c("__mul_"));
                        
                        char nb_param_str[10];
                        sprintf(nb_param_str, "%d", nb_param);
                        ADD_PARAM_LIST((symbol_c*)(new integer_c(nb_param_str)), (symbol_c*)(new int_type_name_c()), function_param_iterator_c::direction_in)
                        ADD_PARAM_LIST(IN1_param_value, IN1_type_symbol, function_param_iterator_c::direction_in)
                        ADD_PARAM_LIST(IN2_param_value, IN2_type_symbol, function_param_iterator_c::direction_in)
                        
                        int base_num = 3;
                        symbol_c *param_value = NULL;
                        do{
                            char my_name[10];
                            sprintf(my_name, "IN%d", base_num++);
                            identifier_c param_name(my_name);
                            
                            /* Get the value from a foo(<param_name> = <param_value>) style call */
                            param_value = function_call_param_iterator.search(&param_name);
                            
                            /* Get the value from a foo(<param_value>) style call */
                            if (param_value == NULL)
                              param_value = function_call_param_iterator.next();
                            if (param_value != NULL){
                                symbol_c *current_type_symbol = search_expression_type->get_type(param_value);
                                last_type_symbol = last_type_symbol && search_expression_type->is_same_type(current_type_symbol, last_type_symbol) ? search_expression_type->common_type(current_type_symbol, last_type_symbol) : current_type_symbol ;
                            
                                /*Function specific CODE */
                                ADD_PARAM_LIST(param_value, current_type_symbol, function_param_iterator_c::direction_in)
                            }
                            
                        }while(param_value != NULL);
                        symbol_c * return_type_symbol = last_type_symbol;
                        function_type_suffix = return_type_symbol;
                        break;
                        
                    }
                    
                    
                    ERROR;
                }
                
            }
            
            if(search_expression_type->is_same_type(&search_constant_type_c::time_type_name, last_type_symbol))
            {
        
                {
                    identifier_c param_name("IN2");
                    /* Get the value from a foo(<param_name> = <param_value>) style call */
                    symbol_c *IN2_param_value = function_call_param_iterator.search(&param_name);
                    
                    /* Get the value from a foo(<param_value>) style call */
                    if (IN2_param_value == NULL)
                      IN2_param_value = function_call_param_iterator.next();
                    symbol_c *IN2_type_symbol = search_expression_type->get_type(IN2_param_value);
                    last_type_symbol = last_type_symbol && search_expression_type->is_same_type(IN2_type_symbol, last_type_symbol) ? search_expression_type->common_type(IN2_type_symbol, last_type_symbol) : IN2_type_symbol ;
                    
                    if(search_expression_type->is_num_type(IN2_type_symbol))
                    {
                
                        function_name = (symbol_c*)(new pragma_c("__time_mul"));
                        ADD_PARAM_LIST(IN1_param_value, IN1_type_symbol, function_param_iterator_c::direction_in)
                        ADD_PARAM_LIST(IN2_param_value, IN2_type_symbol, function_param_iterator_c::direction_in)
                        symbol_c * return_type_symbol = &search_constant_type_c::time_type_name;
                        break;
                        
                    }
                    
                    
                    ERROR;
                }
                
            }
            
            
            ERROR;
        }
        
    }/*function_mul*/
    break;

/****
 *SUB
 */
    case function_sub :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN1_param_value = &this->default_variable_name;
        
            symbol_c *IN1_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_num_type(IN1_type_symbol))
            {
        
                {
                    identifier_c param_name("IN2");
                    /* Get the value from a foo(<param_name> = <param_value>) style call */
                    symbol_c *IN2_param_value = function_call_param_iterator.search(&param_name);
                    
                    /* Get the value from a foo(<param_value>) style call */
                    if (IN2_param_value == NULL)
                      IN2_param_value = function_call_param_iterator.next();
                    symbol_c *IN2_type_symbol = search_expression_type->get_type(IN2_param_value);
                    last_type_symbol = last_type_symbol && search_expression_type->is_same_type(IN2_type_symbol, last_type_symbol) ? search_expression_type->common_type(IN2_type_symbol, last_type_symbol) : IN2_type_symbol ;
                    
                    if(search_expression_type->is_num_type(IN2_type_symbol))
                    {
                
                        function_name = (symbol_c*)(new pragma_c("__sub_"));
                        ADD_PARAM_LIST(IN1_param_value, IN1_type_symbol, function_param_iterator_c::direction_in)
                        ADD_PARAM_LIST(IN2_param_value, IN2_type_symbol, function_param_iterator_c::direction_in)
                        symbol_c * return_type_symbol = last_type_symbol;
                        function_type_suffix = return_type_symbol;
                        break;
                        
                    }
                    
                    
                    ERROR;
                }
                
            }
            
            if(search_expression_type->is_same_type(&search_constant_type_c::date_type_name, last_type_symbol))
            {
        
                {
                    identifier_c param_name("IN2");
                    /* Get the value from a foo(<param_name> = <param_value>) style call */
                    symbol_c *IN2_param_value = function_call_param_iterator.search(&param_name);
                    
                    /* Get the value from a foo(<param_value>) style call */
                    if (IN2_param_value == NULL)
                      IN2_param_value = function_call_param_iterator.next();
                    symbol_c *IN2_type_symbol = search_expression_type->get_type(IN2_param_value);
                    last_type_symbol = last_type_symbol && search_expression_type->is_same_type(IN2_type_symbol, last_type_symbol) ? search_expression_type->common_type(IN2_type_symbol, last_type_symbol) : IN2_type_symbol ;
                    
                    if(search_expression_type->is_same_type(&search_constant_type_c::date_type_name, last_type_symbol))
                    {
                
                        function_name = (symbol_c*)(new pragma_c("__time_sub"));
                        ADD_PARAM_LIST(IN1_param_value, IN1_type_symbol, function_param_iterator_c::direction_in)
                        ADD_PARAM_LIST(IN2_param_value, IN2_type_symbol, function_param_iterator_c::direction_in)
                        symbol_c * return_type_symbol = &search_constant_type_c::time_type_name;
                        break;
                        
                    }
                    
                    
                    ERROR;
                }
                
            }
            
            if(search_expression_type->is_same_type(&search_constant_type_c::dt_type_name, last_type_symbol))
            {
        
                {
                    identifier_c param_name("IN2");
                    /* Get the value from a foo(<param_name> = <param_value>) style call */
                    symbol_c *IN2_param_value = function_call_param_iterator.search(&param_name);
                    
                    /* Get the value from a foo(<param_value>) style call */
                    if (IN2_param_value == NULL)
                      IN2_param_value = function_call_param_iterator.next();
                    symbol_c *IN2_type_symbol = search_expression_type->get_type(IN2_param_value);
                    last_type_symbol = last_type_symbol && search_expression_type->is_same_type(IN2_type_symbol, last_type_symbol) ? search_expression_type->common_type(IN2_type_symbol, last_type_symbol) : IN2_type_symbol ;
                    
                    if(search_expression_type->is_same_type(&search_constant_type_c::dt_type_name, last_type_symbol))
                    {
                
                        function_name = (symbol_c*)(new pragma_c("__time_sub"));
                        ADD_PARAM_LIST(IN1_param_value, IN1_type_symbol, function_param_iterator_c::direction_in)
                        ADD_PARAM_LIST(IN2_param_value, IN2_type_symbol, function_param_iterator_c::direction_in)
                        symbol_c * return_type_symbol = &search_constant_type_c::time_type_name;
                        break;
                        
                    }
                    
                    if(search_expression_type->is_same_type(&search_constant_type_c::time_type_name, last_type_symbol))
                    {
                
                        function_name = (symbol_c*)(new pragma_c("__time_sub"));
                        ADD_PARAM_LIST(IN1_param_value, IN1_type_symbol, function_param_iterator_c::direction_in)
                        ADD_PARAM_LIST(IN2_param_value, IN2_type_symbol, function_param_iterator_c::direction_in)
                        symbol_c * return_type_symbol = &search_constant_type_c::dt_type_name;
                        break;
                        
                    }
                    
                    
                    ERROR;
                }
                
            }
            
            if(search_expression_type->is_same_type(&search_constant_type_c::tod_type_name, last_type_symbol))
            {
        
                {
                    identifier_c param_name("IN2");
                    /* Get the value from a foo(<param_name> = <param_value>) style call */
                    symbol_c *IN2_param_value = function_call_param_iterator.search(&param_name);
                    
                    /* Get the value from a foo(<param_value>) style call */
                    if (IN2_param_value == NULL)
                      IN2_param_value = function_call_param_iterator.next();
                    symbol_c *IN2_type_symbol = search_expression_type->get_type(IN2_param_value);
                    last_type_symbol = last_type_symbol && search_expression_type->is_same_type(IN2_type_symbol, last_type_symbol) ? search_expression_type->common_type(IN2_type_symbol, last_type_symbol) : IN2_type_symbol ;
                    
                    if(search_expression_type->is_same_type(&search_constant_type_c::tod_type_name, last_type_symbol))
                    {
                
                        function_name = (symbol_c*)(new pragma_c("__time_sub"));
                        ADD_PARAM_LIST(IN1_param_value, IN1_type_symbol, function_param_iterator_c::direction_in)
                        ADD_PARAM_LIST(IN2_param_value, IN2_type_symbol, function_param_iterator_c::direction_in)
                        symbol_c * return_type_symbol = &search_constant_type_c::time_type_name;
                        break;
                        
                    }
                    
                    if(search_expression_type->is_same_type(&search_constant_type_c::time_type_name, last_type_symbol))
                    {
                
                        function_name = (symbol_c*)(new pragma_c("__time_sub"));
                        ADD_PARAM_LIST(IN1_param_value, IN1_type_symbol, function_param_iterator_c::direction_in)
                        ADD_PARAM_LIST(IN2_param_value, IN2_type_symbol, function_param_iterator_c::direction_in)
                        symbol_c * return_type_symbol = &search_constant_type_c::tod_type_name;
                        break;
                        
                    }
                    
                    
                    ERROR;
                }
                
            }
            
            if(search_expression_type->is_same_type(&search_constant_type_c::time_type_name, last_type_symbol))
            {
        
                {
                    identifier_c param_name("IN2");
                    /* Get the value from a foo(<param_name> = <param_value>) style call */
                    symbol_c *IN2_param_value = function_call_param_iterator.search(&param_name);
                    
                    /* Get the value from a foo(<param_value>) style call */
                    if (IN2_param_value == NULL)
                      IN2_param_value = function_call_param_iterator.next();
                    symbol_c *IN2_type_symbol = search_expression_type->get_type(IN2_param_value);
                    last_type_symbol = last_type_symbol && search_expression_type->is_same_type(IN2_type_symbol, last_type_symbol) ? search_expression_type->common_type(IN2_type_symbol, last_type_symbol) : IN2_type_symbol ;
                    
                    if(search_expression_type->is_same_type(&search_constant_type_c::time_type_name, last_type_symbol))
                    {
                
                        function_name = (symbol_c*)(new pragma_c("__time_sub"));
                        ADD_PARAM_LIST(IN1_param_value, IN1_type_symbol, function_param_iterator_c::direction_in)
                        ADD_PARAM_LIST(IN2_param_value, IN2_type_symbol, function_param_iterator_c::direction_in)
                        symbol_c * return_type_symbol = &search_constant_type_c::time_type_name;
                        break;
                        
                    }
                    
                    
                    ERROR;
                }
                
            }
            
            
            ERROR;
        }
        
    }/*function_sub*/
    break;

/****
 *DIV
 */
    case function_div :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN1_param_value = &this->default_variable_name;
        
            symbol_c *IN1_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_num_type(IN1_type_symbol))
            {
        
                {
                    identifier_c param_name("IN2");
                    /* Get the value from a foo(<param_name> = <param_value>) style call */
                    symbol_c *IN2_param_value = function_call_param_iterator.search(&param_name);
                    
                    /* Get the value from a foo(<param_value>) style call */
                    if (IN2_param_value == NULL)
                      IN2_param_value = function_call_param_iterator.next();
                    symbol_c *IN2_type_symbol = search_expression_type->get_type(IN2_param_value);
                    last_type_symbol = last_type_symbol && search_expression_type->is_same_type(IN2_type_symbol, last_type_symbol) ? search_expression_type->common_type(IN2_type_symbol, last_type_symbol) : IN2_type_symbol ;
                    
                    if(search_expression_type->is_num_type(IN2_type_symbol))
                    {
                
                        function_name = (symbol_c*)(new pragma_c("__div_"));
                        ADD_PARAM_LIST(IN1_param_value, IN1_type_symbol, function_param_iterator_c::direction_in)
                        ADD_PARAM_LIST(IN2_param_value, IN2_type_symbol, function_param_iterator_c::direction_in)
                        symbol_c * return_type_symbol = last_type_symbol;
                        function_type_suffix = return_type_symbol;
                        break;
                        
                    }
                    
                    
                    ERROR;
                }
                
            }
            
            if(search_expression_type->is_same_type(&search_constant_type_c::time_type_name, last_type_symbol))
            {
        
                {
                    identifier_c param_name("IN2");
                    /* Get the value from a foo(<param_name> = <param_value>) style call */
                    symbol_c *IN2_param_value = function_call_param_iterator.search(&param_name);
                    
                    /* Get the value from a foo(<param_value>) style call */
                    if (IN2_param_value == NULL)
                      IN2_param_value = function_call_param_iterator.next();
                    symbol_c *IN2_type_symbol = search_expression_type->get_type(IN2_param_value);
                    last_type_symbol = last_type_symbol && search_expression_type->is_same_type(IN2_type_symbol, last_type_symbol) ? search_expression_type->common_type(IN2_type_symbol, last_type_symbol) : IN2_type_symbol ;
                    
                    if(search_expression_type->is_num_type(IN2_type_symbol))
                    {
                
                        function_name = (symbol_c*)(new pragma_c("__time_div"));
                        ADD_PARAM_LIST(IN1_param_value, IN1_type_symbol, function_param_iterator_c::direction_in)
                        ADD_PARAM_LIST(IN2_param_value, IN2_type_symbol, function_param_iterator_c::direction_in)
                        symbol_c * return_type_symbol = &search_constant_type_c::time_type_name;
                        break;
                        
                    }
                    
                    
                    ERROR;
                }
                
            }
            
            
            ERROR;
        }
        
    }/*function_div*/
    break;

/****
 *MOD
 */
    case function_mod :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN1_param_value = &this->default_variable_name;
        
            symbol_c *IN1_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_num_type(IN1_type_symbol))
            {
        
                {
                    identifier_c param_name("IN2");
                    /* Get the value from a foo(<param_name> = <param_value>) style call */
                    symbol_c *IN2_param_value = function_call_param_iterator.search(&param_name);
                    
                    /* Get the value from a foo(<param_value>) style call */
                    if (IN2_param_value == NULL)
                      IN2_param_value = function_call_param_iterator.next();
                    symbol_c *IN2_type_symbol = search_expression_type->get_type(IN2_param_value);
                    last_type_symbol = last_type_symbol && search_expression_type->is_same_type(IN2_type_symbol, last_type_symbol) ? search_expression_type->common_type(IN2_type_symbol, last_type_symbol) : IN2_type_symbol ;
                    
                    if(search_expression_type->is_num_type(IN2_type_symbol))
                    {
                
                        function_name = (symbol_c*)(new pragma_c("__mod_"));
                        ADD_PARAM_LIST(IN1_param_value, IN1_type_symbol, function_param_iterator_c::direction_in)
                        ADD_PARAM_LIST(IN2_param_value, IN2_type_symbol, function_param_iterator_c::direction_in)
                        symbol_c * return_type_symbol = last_type_symbol;
                        function_type_suffix = return_type_symbol;
                        break;
                        
                    }
                    
                    
                    ERROR;
                }
                
            }
            
            
            ERROR;
        }
        
    }/*function_mod*/
    break;

/****
 *EXPT
 */
    case function_expt :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN1_param_value = &this->default_variable_name;
        
            symbol_c *IN1_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_num_type(IN1_type_symbol))
            {
        
                {
                    identifier_c param_name("IN2");
                    /* Get the value from a foo(<param_name> = <param_value>) style call */
                    symbol_c *IN2_param_value = function_call_param_iterator.search(&param_name);
                    
                    /* Get the value from a foo(<param_value>) style call */
                    if (IN2_param_value == NULL)
                      IN2_param_value = function_call_param_iterator.next();
                    symbol_c *IN2_type_symbol = search_expression_type->get_type(IN2_param_value);
                    last_type_symbol = last_type_symbol && search_expression_type->is_same_type(IN2_type_symbol, last_type_symbol) ? search_expression_type->common_type(IN2_type_symbol, last_type_symbol) : IN2_type_symbol ;
                    
                    if(search_expression_type->is_num_type(IN2_type_symbol))
                    {
                
                        function_name = (symbol_c*)(new pragma_c("pow"));
                        ADD_PARAM_LIST(IN1_param_value, IN1_type_symbol, function_param_iterator_c::direction_in)
                        ADD_PARAM_LIST(IN2_param_value, IN2_type_symbol, function_param_iterator_c::direction_in)
                        symbol_c * return_type_symbol = last_type_symbol;
                        break;
                        
                    }
                    
                    
                    ERROR;
                }
                
            }
            
            
            ERROR;
        }
        
    }/*function_expt*/
    break;

/****
 *MOVE
 */
    case function_move :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            
            {
        
                function_name = (symbol_c*)(new pragma_c("__move_"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = last_type_symbol;
                function_type_suffix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_move*/
    break;

/****
 *SHL
 */
    case function_shl :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_binary_type(IN_type_symbol))
            {
        
                {
                    identifier_c param_name("N");
                    /* Get the value from a foo(<param_name> = <param_value>) style call */
                    symbol_c *N_param_value = function_call_param_iterator.search(&param_name);
                    
                    /* Get the value from a foo(<param_value>) style call */
                    if (N_param_value == NULL)
                      N_param_value = function_call_param_iterator.next();
                    symbol_c *N_type_symbol = search_expression_type->get_type(N_param_value);
                    last_type_symbol = last_type_symbol && search_expression_type->is_same_type(N_type_symbol, last_type_symbol) ? search_expression_type->common_type(N_type_symbol, last_type_symbol) : N_type_symbol ;
                    
                    if(search_expression_type->is_integer_type(N_type_symbol))
                    {
                
                        function_name = (symbol_c*)(new pragma_c("__shl_"));
                        ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                        ADD_PARAM_LIST(N_param_value, N_type_symbol, function_param_iterator_c::direction_in)
                        symbol_c * return_type_symbol = IN_type_symbol;
                        function_type_suffix = IN_type_symbol;
                        break;
                        
                    }
                    
                    
                    ERROR;
                }
                
            }
            
            
            ERROR;
        }
        
    }/*function_shl*/
    break;

/****
 *SHR
 */
    case function_shr :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_binary_type(IN_type_symbol))
            {
        
                {
                    identifier_c param_name("N");
                    /* Get the value from a foo(<param_name> = <param_value>) style call */
                    symbol_c *N_param_value = function_call_param_iterator.search(&param_name);
                    
                    /* Get the value from a foo(<param_value>) style call */
                    if (N_param_value == NULL)
                      N_param_value = function_call_param_iterator.next();
                    symbol_c *N_type_symbol = search_expression_type->get_type(N_param_value);
                    last_type_symbol = last_type_symbol && search_expression_type->is_same_type(N_type_symbol, last_type_symbol) ? search_expression_type->common_type(N_type_symbol, last_type_symbol) : N_type_symbol ;
                    
                    if(search_expression_type->is_integer_type(N_type_symbol))
                    {
                
                        function_name = (symbol_c*)(new pragma_c("__shr_"));
                        ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                        ADD_PARAM_LIST(N_param_value, N_type_symbol, function_param_iterator_c::direction_in)
                        symbol_c * return_type_symbol = IN_type_symbol;
                        function_type_suffix = IN_type_symbol;
                        break;
                        
                    }
                    
                    
                    ERROR;
                }
                
            }
            
            
            ERROR;
        }
        
    }/*function_shr*/
    break;

/****
 *ROR
 */
    case function_ror :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_nbinary_type(IN_type_symbol))
            {
        
                {
                    identifier_c param_name("N");
                    /* Get the value from a foo(<param_name> = <param_value>) style call */
                    symbol_c *N_param_value = function_call_param_iterator.search(&param_name);
                    
                    /* Get the value from a foo(<param_value>) style call */
                    if (N_param_value == NULL)
                      N_param_value = function_call_param_iterator.next();
                    symbol_c *N_type_symbol = search_expression_type->get_type(N_param_value);
                    last_type_symbol = last_type_symbol && search_expression_type->is_same_type(N_type_symbol, last_type_symbol) ? search_expression_type->common_type(N_type_symbol, last_type_symbol) : N_type_symbol ;
                    
                    if(search_expression_type->is_integer_type(N_type_symbol))
                    {
                
                        function_name = (symbol_c*)(new pragma_c("__ror_"));
                        ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                        ADD_PARAM_LIST(N_param_value, N_type_symbol, function_param_iterator_c::direction_in)
                        symbol_c * return_type_symbol = IN_type_symbol;
                        function_type_suffix = IN_type_symbol;
                        break;
                        
                    }
                    
                    
                    ERROR;
                }
                
            }
            
            
            ERROR;
        }
        
    }/*function_ror*/
    break;

/****
 *ROL
 */
    case function_rol :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_nbinary_type(IN_type_symbol))
            {
        
                {
                    identifier_c param_name("N");
                    /* Get the value from a foo(<param_name> = <param_value>) style call */
                    symbol_c *N_param_value = function_call_param_iterator.search(&param_name);
                    
                    /* Get the value from a foo(<param_value>) style call */
                    if (N_param_value == NULL)
                      N_param_value = function_call_param_iterator.next();
                    symbol_c *N_type_symbol = search_expression_type->get_type(N_param_value);
                    last_type_symbol = last_type_symbol && search_expression_type->is_same_type(N_type_symbol, last_type_symbol) ? search_expression_type->common_type(N_type_symbol, last_type_symbol) : N_type_symbol ;
                    
                    if(search_expression_type->is_integer_type(N_type_symbol))
                    {
                
                        function_name = (symbol_c*)(new pragma_c("__rol_"));
                        ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                        ADD_PARAM_LIST(N_param_value, N_type_symbol, function_param_iterator_c::direction_in)
                        symbol_c * return_type_symbol = IN_type_symbol;
                        function_type_suffix = IN_type_symbol;
                        break;
                        
                    }
                    
                    
                    ERROR;
                }
                
            }
            
            
            ERROR;
        }
        
    }/*function_rol*/
    break;

/****
 *AND
 */
    case function_and :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN1_param_value = &this->default_variable_name;
        
            symbol_c *IN1_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_binary_type(IN1_type_symbol))
            {
        
                {
                    identifier_c param_name("IN2");
                    /* Get the value from a foo(<param_name> = <param_value>) style call */
                    symbol_c *IN2_param_value = function_call_param_iterator.search(&param_name);
                    
                    /* Get the value from a foo(<param_value>) style call */
                    if (IN2_param_value == NULL)
                      IN2_param_value = function_call_param_iterator.next();
                    symbol_c *IN2_type_symbol = search_expression_type->get_type(IN2_param_value);
                    last_type_symbol = last_type_symbol && search_expression_type->is_same_type(IN2_type_symbol, last_type_symbol) ? search_expression_type->common_type(IN2_type_symbol, last_type_symbol) : IN2_type_symbol ;
                    
                    if(search_expression_type->is_binary_type(IN2_type_symbol))
                    {
                
                        function_name = (symbol_c*)(new pragma_c("__and_"));
                        
                        char nb_param_str[10];
                        sprintf(nb_param_str, "%d", nb_param);
                        ADD_PARAM_LIST((symbol_c*)(new integer_c(nb_param_str)), (symbol_c*)(new int_type_name_c()), function_param_iterator_c::direction_in)
                        ADD_PARAM_LIST(IN1_param_value, IN1_type_symbol, function_param_iterator_c::direction_in)
                        ADD_PARAM_LIST(IN2_param_value, IN2_type_symbol, function_param_iterator_c::direction_in)
                        
                        int base_num = 3;
                        symbol_c *param_value = NULL;
                        do{
                            char my_name[10];
                            sprintf(my_name, "IN%d", base_num++);
                            identifier_c param_name(my_name);
                            
                            /* Get the value from a foo(<param_name> = <param_value>) style call */
                            param_value = function_call_param_iterator.search(&param_name);
                            
                            /* Get the value from a foo(<param_value>) style call */
                            if (param_value == NULL)
                              param_value = function_call_param_iterator.next();
                            if (param_value != NULL){
                                symbol_c *current_type_symbol = search_expression_type->get_type(param_value);
                                last_type_symbol = last_type_symbol && search_expression_type->is_same_type(current_type_symbol, last_type_symbol) ? search_expression_type->common_type(current_type_symbol, last_type_symbol) : current_type_symbol ;
                            
                                /*Function specific CODE */
                                ADD_PARAM_LIST(param_value, current_type_symbol, function_param_iterator_c::direction_in)
                            }
                            
                        }while(param_value != NULL);
                        symbol_c * return_type_symbol = last_type_symbol;
                        function_type_suffix = return_type_symbol;
                        break;
                        
                    }
                    
                    
                    ERROR;
                }
                
            }
            
            
            ERROR;
        }
        
    }/*function_and*/
    break;

/****
 *OR
 */
    case function_or :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN1_param_value = &this->default_variable_name;
        
            symbol_c *IN1_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_binary_type(IN1_type_symbol))
            {
        
                {
                    identifier_c param_name("IN2");
                    /* Get the value from a foo(<param_name> = <param_value>) style call */
                    symbol_c *IN2_param_value = function_call_param_iterator.search(&param_name);
                    
                    /* Get the value from a foo(<param_value>) style call */
                    if (IN2_param_value == NULL)
                      IN2_param_value = function_call_param_iterator.next();
                    symbol_c *IN2_type_symbol = search_expression_type->get_type(IN2_param_value);
                    last_type_symbol = last_type_symbol && search_expression_type->is_same_type(IN2_type_symbol, last_type_symbol) ? search_expression_type->common_type(IN2_type_symbol, last_type_symbol) : IN2_type_symbol ;
                    
                    if(search_expression_type->is_binary_type(IN2_type_symbol))
                    {
                
                        function_name = (symbol_c*)(new pragma_c("__or_"));
                        
                        char nb_param_str[10];
                        sprintf(nb_param_str, "%d", nb_param);
                        ADD_PARAM_LIST((symbol_c*)(new integer_c(nb_param_str)), (symbol_c*)(new int_type_name_c()), function_param_iterator_c::direction_in)
                        ADD_PARAM_LIST(IN1_param_value, IN1_type_symbol, function_param_iterator_c::direction_in)
                        ADD_PARAM_LIST(IN2_param_value, IN2_type_symbol, function_param_iterator_c::direction_in)
                        
                        int base_num = 3;
                        symbol_c *param_value = NULL;
                        do{
                            char my_name[10];
                            sprintf(my_name, "IN%d", base_num++);
                            identifier_c param_name(my_name);
                            
                            /* Get the value from a foo(<param_name> = <param_value>) style call */
                            param_value = function_call_param_iterator.search(&param_name);
                            
                            /* Get the value from a foo(<param_value>) style call */
                            if (param_value == NULL)
                              param_value = function_call_param_iterator.next();
                            if (param_value != NULL){
                                symbol_c *current_type_symbol = search_expression_type->get_type(param_value);
                                last_type_symbol = last_type_symbol && search_expression_type->is_same_type(current_type_symbol, last_type_symbol) ? search_expression_type->common_type(current_type_symbol, last_type_symbol) : current_type_symbol ;
                            
                                /*Function specific CODE */
                                ADD_PARAM_LIST(param_value, current_type_symbol, function_param_iterator_c::direction_in)
                            }
                            
                        }while(param_value != NULL);
                        symbol_c * return_type_symbol = last_type_symbol;
                        function_type_suffix = return_type_symbol;
                        break;
                        
                    }
                    
                    
                    ERROR;
                }
                
            }
            
            
            ERROR;
        }
        
    }/*function_or*/
    break;

/****
 *XOR
 */
    case function_xor :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN1_param_value = &this->default_variable_name;
        
            symbol_c *IN1_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_binary_type(IN1_type_symbol))
            {
        
                {
                    identifier_c param_name("IN2");
                    /* Get the value from a foo(<param_name> = <param_value>) style call */
                    symbol_c *IN2_param_value = function_call_param_iterator.search(&param_name);
                    
                    /* Get the value from a foo(<param_value>) style call */
                    if (IN2_param_value == NULL)
                      IN2_param_value = function_call_param_iterator.next();
                    symbol_c *IN2_type_symbol = search_expression_type->get_type(IN2_param_value);
                    last_type_symbol = last_type_symbol && search_expression_type->is_same_type(IN2_type_symbol, last_type_symbol) ? search_expression_type->common_type(IN2_type_symbol, last_type_symbol) : IN2_type_symbol ;
                    
                    if(search_expression_type->is_binary_type(IN2_type_symbol))
                    {
                
                        function_name = (symbol_c*)(new pragma_c("__xor_"));
                        
                        char nb_param_str[10];
                        sprintf(nb_param_str, "%d", nb_param);
                        ADD_PARAM_LIST((symbol_c*)(new integer_c(nb_param_str)), (symbol_c*)(new int_type_name_c()), function_param_iterator_c::direction_in)
                        ADD_PARAM_LIST(IN1_param_value, IN1_type_symbol, function_param_iterator_c::direction_in)
                        ADD_PARAM_LIST(IN2_param_value, IN2_type_symbol, function_param_iterator_c::direction_in)
                        
                        int base_num = 3;
                        symbol_c *param_value = NULL;
                        do{
                            char my_name[10];
                            sprintf(my_name, "IN%d", base_num++);
                            identifier_c param_name(my_name);
                            
                            /* Get the value from a foo(<param_name> = <param_value>) style call */
                            param_value = function_call_param_iterator.search(&param_name);
                            
                            /* Get the value from a foo(<param_value>) style call */
                            if (param_value == NULL)
                              param_value = function_call_param_iterator.next();
                            if (param_value != NULL){
                                symbol_c *current_type_symbol = search_expression_type->get_type(param_value);
                                last_type_symbol = last_type_symbol && search_expression_type->is_same_type(current_type_symbol, last_type_symbol) ? search_expression_type->common_type(current_type_symbol, last_type_symbol) : current_type_symbol ;
                            
                                /*Function specific CODE */
                                ADD_PARAM_LIST(param_value, current_type_symbol, function_param_iterator_c::direction_in)
                            }
                            
                        }while(param_value != NULL);
                        symbol_c * return_type_symbol = last_type_symbol;
                        function_type_suffix = return_type_symbol;
                        break;
                        
                    }
                    
                    
                    ERROR;
                }
                
            }
            
            
            ERROR;
        }
        
    }/*function_xor*/
    break;

/****
 *NOT
 */
    case function_not :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_binary_type(IN_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__not_"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = IN_type_symbol;
                function_type_suffix = return_type_symbol;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_not*/
    break;

/****
 *SEL
 */
    case function_sel :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *G_param_value = &this->default_variable_name;
        
            symbol_c *G_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::bool_type_name, last_type_symbol))
            {
        
                {
                    identifier_c param_name("IN0");
                    /* Get the value from a foo(<param_name> = <param_value>) style call */
                    symbol_c *IN0_param_value = function_call_param_iterator.search(&param_name);
                    
                    /* Get the value from a foo(<param_value>) style call */
                    if (IN0_param_value == NULL)
                      IN0_param_value = function_call_param_iterator.next();
                    symbol_c *IN0_type_symbol = search_expression_type->get_type(IN0_param_value);
                    last_type_symbol = last_type_symbol && search_expression_type->is_same_type(IN0_type_symbol, last_type_symbol) ? search_expression_type->common_type(IN0_type_symbol, last_type_symbol) : IN0_type_symbol ;
                    
                    
                    {
                
                        {
                            identifier_c param_name("IN1");
                            /* Get the value from a foo(<param_name> = <param_value>) style call */
                            symbol_c *IN1_param_value = function_call_param_iterator.search(&param_name);
                            
                            /* Get the value from a foo(<param_value>) style call */
                            if (IN1_param_value == NULL)
                              IN1_param_value = function_call_param_iterator.next();
                            symbol_c *IN1_type_symbol = search_expression_type->get_type(IN1_param_value);
                            last_type_symbol = last_type_symbol && search_expression_type->is_same_type(IN1_type_symbol, last_type_symbol) ? search_expression_type->common_type(IN1_type_symbol, last_type_symbol) : IN1_type_symbol ;
                            
                            
                            {
                        
                                function_name = (symbol_c*)(new pragma_c("__sel_"));
                                ADD_PARAM_LIST(G_param_value, G_type_symbol, function_param_iterator_c::direction_in)
                                ADD_PARAM_LIST(IN0_param_value, IN0_type_symbol, function_param_iterator_c::direction_in)
                                ADD_PARAM_LIST(IN1_param_value, IN1_type_symbol, function_param_iterator_c::direction_in)
                                symbol_c * return_type_symbol = last_type_symbol;
                                function_type_suffix = IN0_type_symbol;
                                break;
                                
                            }
                            
                            
                            ERROR;
                        }
                        
                    }
                    
                    
                    ERROR;
                }
                
            }
            
            
            ERROR;
        }
        
    }/*function_sel*/
    break;

/****
 *MAX
 */
    case function_max :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN1_param_value = &this->default_variable_name;
        
            symbol_c *IN1_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            
            {
        
                {
                    identifier_c param_name("IN2");
                    /* Get the value from a foo(<param_name> = <param_value>) style call */
                    symbol_c *IN2_param_value = function_call_param_iterator.search(&param_name);
                    
                    /* Get the value from a foo(<param_value>) style call */
                    if (IN2_param_value == NULL)
                      IN2_param_value = function_call_param_iterator.next();
                    symbol_c *IN2_type_symbol = search_expression_type->get_type(IN2_param_value);
                    last_type_symbol = last_type_symbol && search_expression_type->is_same_type(IN2_type_symbol, last_type_symbol) ? search_expression_type->common_type(IN2_type_symbol, last_type_symbol) : IN2_type_symbol ;
                    
                    
                    {
                
                        function_name = (symbol_c*)(new pragma_c("__max_"));
                        
                        char nb_param_str[10];
                        sprintf(nb_param_str, "%d", nb_param);
                        ADD_PARAM_LIST((symbol_c*)(new integer_c(nb_param_str)), (symbol_c*)(new int_type_name_c()), function_param_iterator_c::direction_in)
                        ADD_PARAM_LIST(IN1_param_value, IN1_type_symbol, function_param_iterator_c::direction_in)
                        ADD_PARAM_LIST(IN2_param_value, IN2_type_symbol, function_param_iterator_c::direction_in)
                        
                        int base_num = 3;
                        symbol_c *param_value = NULL;
                        do{
                            char my_name[10];
                            sprintf(my_name, "IN%d", base_num++);
                            identifier_c param_name(my_name);
                            
                            /* Get the value from a foo(<param_name> = <param_value>) style call */
                            param_value = function_call_param_iterator.search(&param_name);
                            
                            /* Get the value from a foo(<param_value>) style call */
                            if (param_value == NULL)
                              param_value = function_call_param_iterator.next();
                            if (param_value != NULL){
                                symbol_c *current_type_symbol = search_expression_type->get_type(param_value);
                                last_type_symbol = last_type_symbol && search_expression_type->is_same_type(current_type_symbol, last_type_symbol) ? search_expression_type->common_type(current_type_symbol, last_type_symbol) : current_type_symbol ;
                            
                                /*Function specific CODE */
                                ADD_PARAM_LIST(param_value, current_type_symbol, function_param_iterator_c::direction_in)
                            }
                            
                        }while(param_value != NULL);
                        symbol_c * return_type_symbol = last_type_symbol;
                        function_type_suffix = return_type_symbol;
                        break;
                        
                    }
                    
                    
                    ERROR;
                }
                
            }
            
            
            ERROR;
        }
        
    }/*function_max*/
    break;

/****
 *MIN
 */
    case function_min :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN1_param_value = &this->default_variable_name;
        
            symbol_c *IN1_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            
            {
        
                {
                    identifier_c param_name("IN2");
                    /* Get the value from a foo(<param_name> = <param_value>) style call */
                    symbol_c *IN2_param_value = function_call_param_iterator.search(&param_name);
                    
                    /* Get the value from a foo(<param_value>) style call */
                    if (IN2_param_value == NULL)
                      IN2_param_value = function_call_param_iterator.next();
                    symbol_c *IN2_type_symbol = search_expression_type->get_type(IN2_param_value);
                    last_type_symbol = last_type_symbol && search_expression_type->is_same_type(IN2_type_symbol, last_type_symbol) ? search_expression_type->common_type(IN2_type_symbol, last_type_symbol) : IN2_type_symbol ;
                    
                    
                    {
                
                        function_name = (symbol_c*)(new pragma_c("__min_"));
                        
                        char nb_param_str[10];
                        sprintf(nb_param_str, "%d", nb_param);
                        ADD_PARAM_LIST((symbol_c*)(new integer_c(nb_param_str)), (symbol_c*)(new int_type_name_c()), function_param_iterator_c::direction_in)
                        ADD_PARAM_LIST(IN1_param_value, IN1_type_symbol, function_param_iterator_c::direction_in)
                        ADD_PARAM_LIST(IN2_param_value, IN2_type_symbol, function_param_iterator_c::direction_in)
                        
                        int base_num = 3;
                        symbol_c *param_value = NULL;
                        do{
                            char my_name[10];
                            sprintf(my_name, "IN%d", base_num++);
                            identifier_c param_name(my_name);
                            
                            /* Get the value from a foo(<param_name> = <param_value>) style call */
                            param_value = function_call_param_iterator.search(&param_name);
                            
                            /* Get the value from a foo(<param_value>) style call */
                            if (param_value == NULL)
                              param_value = function_call_param_iterator.next();
                            if (param_value != NULL){
                                symbol_c *current_type_symbol = search_expression_type->get_type(param_value);
                                last_type_symbol = last_type_symbol && search_expression_type->is_same_type(current_type_symbol, last_type_symbol) ? search_expression_type->common_type(current_type_symbol, last_type_symbol) : current_type_symbol ;
                            
                                /*Function specific CODE */
                                ADD_PARAM_LIST(param_value, current_type_symbol, function_param_iterator_c::direction_in)
                            }
                            
                        }while(param_value != NULL);
                        symbol_c * return_type_symbol = last_type_symbol;
                        function_type_suffix = return_type_symbol;
                        break;
                        
                    }
                    
                    
                    ERROR;
                }
                
            }
            
            
            ERROR;
        }
        
    }/*function_min*/
    break;

/****
 *LIMIT
 */
    case function_limit :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *MN_param_value = &this->default_variable_name;
        
            symbol_c *MN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            
            {
        
                {
                    identifier_c param_name("IN");
                    /* Get the value from a foo(<param_name> = <param_value>) style call */
                    symbol_c *IN_param_value = function_call_param_iterator.search(&param_name);
                    
                    /* Get the value from a foo(<param_value>) style call */
                    if (IN_param_value == NULL)
                      IN_param_value = function_call_param_iterator.next();
                    symbol_c *IN_type_symbol = search_expression_type->get_type(IN_param_value);
                    last_type_symbol = last_type_symbol && search_expression_type->is_same_type(IN_type_symbol, last_type_symbol) ? search_expression_type->common_type(IN_type_symbol, last_type_symbol) : IN_type_symbol ;
                    
                    
                    {
                
                        {
                            identifier_c param_name("MX");
                            /* Get the value from a foo(<param_name> = <param_value>) style call */
                            symbol_c *MX_param_value = function_call_param_iterator.search(&param_name);
                            
                            /* Get the value from a foo(<param_value>) style call */
                            if (MX_param_value == NULL)
                              MX_param_value = function_call_param_iterator.next();
                            symbol_c *MX_type_symbol = search_expression_type->get_type(MX_param_value);
                            last_type_symbol = last_type_symbol && search_expression_type->is_same_type(MX_type_symbol, last_type_symbol) ? search_expression_type->common_type(MX_type_symbol, last_type_symbol) : MX_type_symbol ;
                            
                            
                            {
                        
                                function_name = (symbol_c*)(new pragma_c("__limit_"));
                                ADD_PARAM_LIST(MN_param_value, MN_type_symbol, function_param_iterator_c::direction_in)
                                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                                ADD_PARAM_LIST(MX_param_value, MX_type_symbol, function_param_iterator_c::direction_in)
                                symbol_c * return_type_symbol = IN_type_symbol;
                                function_type_suffix = IN_type_symbol;
                                break;
                                
                            }
                            
                            
                            ERROR;
                        }
                        
                    }
                    
                    
                    ERROR;
                }
                
            }
            
            
            ERROR;
        }
        
    }/*function_limit*/
    break;

/****
 *MUX
 */
    case function_mux :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *K_param_value = &this->default_variable_name;
        
            symbol_c *K_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_integer_type(K_type_symbol))
            {
        
                {
                    identifier_c param_name("IN0");
                    /* Get the value from a foo(<param_name> = <param_value>) style call */
                    symbol_c *IN0_param_value = function_call_param_iterator.search(&param_name);
                    
                    /* Get the value from a foo(<param_value>) style call */
                    if (IN0_param_value == NULL)
                      IN0_param_value = function_call_param_iterator.next();
                    symbol_c *IN0_type_symbol = search_expression_type->get_type(IN0_param_value);
                    last_type_symbol = last_type_symbol && search_expression_type->is_same_type(IN0_type_symbol, last_type_symbol) ? search_expression_type->common_type(IN0_type_symbol, last_type_symbol) : IN0_type_symbol ;
                    
                    
                    {
                
                        {
                            identifier_c param_name("IN1");
                            /* Get the value from a foo(<param_name> = <param_value>) style call */
                            symbol_c *IN1_param_value = function_call_param_iterator.search(&param_name);
                            
                            /* Get the value from a foo(<param_value>) style call */
                            if (IN1_param_value == NULL)
                              IN1_param_value = function_call_param_iterator.next();
                            symbol_c *IN1_type_symbol = search_expression_type->get_type(IN1_param_value);
                            last_type_symbol = last_type_symbol && search_expression_type->is_same_type(IN1_type_symbol, last_type_symbol) ? search_expression_type->common_type(IN1_type_symbol, last_type_symbol) : IN1_type_symbol ;
                            
                            
                            {
                        
                                function_name = (symbol_c*)(new pragma_c("__mux_"));
                                
                                char nb_param_str[10];
                                sprintf(nb_param_str, "%d", nb_param);
                                ADD_PARAM_LIST((symbol_c*)(new integer_c(nb_param_str)), (symbol_c*)(new int_type_name_c()), function_param_iterator_c::direction_in)
                                ADD_PARAM_LIST(K_param_value, K_type_symbol, function_param_iterator_c::direction_in)
                                ADD_PARAM_LIST(IN0_param_value, IN0_type_symbol, function_param_iterator_c::direction_in)
                                ADD_PARAM_LIST(IN1_param_value, IN1_type_symbol, function_param_iterator_c::direction_in)
                                
                                int base_num = 2;
                                symbol_c *param_value = NULL;
                                do{
                                    char my_name[10];
                                    sprintf(my_name, "IN%d", base_num++);
                                    identifier_c param_name(my_name);
                                    
                                    /* Get the value from a foo(<param_name> = <param_value>) style call */
                                    param_value = function_call_param_iterator.search(&param_name);
                                    
                                    /* Get the value from a foo(<param_value>) style call */
                                    if (param_value == NULL)
                                      param_value = function_call_param_iterator.next();
                                    if (param_value != NULL){
                                        symbol_c *current_type_symbol = search_expression_type->get_type(param_value);
                                        last_type_symbol = last_type_symbol && search_expression_type->is_same_type(current_type_symbol, last_type_symbol) ? search_expression_type->common_type(current_type_symbol, last_type_symbol) : current_type_symbol ;
                                    
                                        /*Function specific CODE */
                                        ADD_PARAM_LIST(param_value, current_type_symbol, function_param_iterator_c::direction_in)
                                    }
                                    
                                }while(param_value != NULL);
                                symbol_c * return_type_symbol = last_type_symbol;
                                function_type_suffix = return_type_symbol;
                                break;
                                
                            }
                            
                            
                            ERROR;
                        }
                        
                    }
                    
                    
                    ERROR;
                }
                
            }
            
            
            ERROR;
        }
        
    }/*function_mux*/
    break;

/****
 *GT
 */
    case function_gt :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN1_param_value = &this->default_variable_name;
        
            symbol_c *IN1_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            
            {
        
                {
                    identifier_c param_name("IN2");
                    /* Get the value from a foo(<param_name> = <param_value>) style call */
                    symbol_c *IN2_param_value = function_call_param_iterator.search(&param_name);
                    
                    /* Get the value from a foo(<param_value>) style call */
                    if (IN2_param_value == NULL)
                      IN2_param_value = function_call_param_iterator.next();
                    symbol_c *IN2_type_symbol = search_expression_type->get_type(IN2_param_value);
                    last_type_symbol = last_type_symbol && search_expression_type->is_same_type(IN2_type_symbol, last_type_symbol) ? search_expression_type->common_type(IN2_type_symbol, last_type_symbol) : IN2_type_symbol ;
                    
                    
                    {
                
                        function_name = (symbol_c*)(new pragma_c("__gt_"));
                        
                        char nb_param_str[10];
                        sprintf(nb_param_str, "%d", nb_param);
                        ADD_PARAM_LIST((symbol_c*)(new integer_c(nb_param_str)), (symbol_c*)(new int_type_name_c()), function_param_iterator_c::direction_in)
                        ADD_PARAM_LIST(IN1_param_value, IN1_type_symbol, function_param_iterator_c::direction_in)
                        ADD_PARAM_LIST(IN2_param_value, IN2_type_symbol, function_param_iterator_c::direction_in)
                        
                        int base_num = 3;
                        symbol_c *param_value = NULL;
                        do{
                            char my_name[10];
                            sprintf(my_name, "IN%d", base_num++);
                            identifier_c param_name(my_name);
                            
                            /* Get the value from a foo(<param_name> = <param_value>) style call */
                            param_value = function_call_param_iterator.search(&param_name);
                            
                            /* Get the value from a foo(<param_value>) style call */
                            if (param_value == NULL)
                              param_value = function_call_param_iterator.next();
                            if (param_value != NULL){
                                symbol_c *current_type_symbol = search_expression_type->get_type(param_value);
                                last_type_symbol = last_type_symbol && search_expression_type->is_same_type(current_type_symbol, last_type_symbol) ? search_expression_type->common_type(current_type_symbol, last_type_symbol) : current_type_symbol ;
                            
                                /*Function specific CODE */
                                ADD_PARAM_LIST(param_value, current_type_symbol, function_param_iterator_c::direction_in)
                            }
                            
                        }while(param_value != NULL);
                        symbol_c * return_type_symbol = &search_constant_type_c::bool_type_name;
                        function_type_suffix = last_type_symbol;
                        break;
                        
                    }
                    
                    
                    ERROR;
                }
                
            }
            
            
            ERROR;
        }
        
    }/*function_gt*/
    break;

/****
 *GE
 */
    case function_ge :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN1_param_value = &this->default_variable_name;
        
            symbol_c *IN1_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            
            {
        
                {
                    identifier_c param_name("IN2");
                    /* Get the value from a foo(<param_name> = <param_value>) style call */
                    symbol_c *IN2_param_value = function_call_param_iterator.search(&param_name);
                    
                    /* Get the value from a foo(<param_value>) style call */
                    if (IN2_param_value == NULL)
                      IN2_param_value = function_call_param_iterator.next();
                    symbol_c *IN2_type_symbol = search_expression_type->get_type(IN2_param_value);
                    last_type_symbol = last_type_symbol && search_expression_type->is_same_type(IN2_type_symbol, last_type_symbol) ? search_expression_type->common_type(IN2_type_symbol, last_type_symbol) : IN2_type_symbol ;
                    
                    
                    {
                
                        function_name = (symbol_c*)(new pragma_c("__ge_"));
                        
                        char nb_param_str[10];
                        sprintf(nb_param_str, "%d", nb_param);
                        ADD_PARAM_LIST((symbol_c*)(new integer_c(nb_param_str)), (symbol_c*)(new int_type_name_c()), function_param_iterator_c::direction_in)
                        ADD_PARAM_LIST(IN1_param_value, IN1_type_symbol, function_param_iterator_c::direction_in)
                        ADD_PARAM_LIST(IN2_param_value, IN2_type_symbol, function_param_iterator_c::direction_in)
                        
                        int base_num = 3;
                        symbol_c *param_value = NULL;
                        do{
                            char my_name[10];
                            sprintf(my_name, "IN%d", base_num++);
                            identifier_c param_name(my_name);
                            
                            /* Get the value from a foo(<param_name> = <param_value>) style call */
                            param_value = function_call_param_iterator.search(&param_name);
                            
                            /* Get the value from a foo(<param_value>) style call */
                            if (param_value == NULL)
                              param_value = function_call_param_iterator.next();
                            if (param_value != NULL){
                                symbol_c *current_type_symbol = search_expression_type->get_type(param_value);
                                last_type_symbol = last_type_symbol && search_expression_type->is_same_type(current_type_symbol, last_type_symbol) ? search_expression_type->common_type(current_type_symbol, last_type_symbol) : current_type_symbol ;
                            
                                /*Function specific CODE */
                                ADD_PARAM_LIST(param_value, current_type_symbol, function_param_iterator_c::direction_in)
                            }
                            
                        }while(param_value != NULL);
                        symbol_c * return_type_symbol = &search_constant_type_c::bool_type_name;
                        function_type_suffix = last_type_symbol;
                        break;
                        
                    }
                    
                    
                    ERROR;
                }
                
            }
            
            
            ERROR;
        }
        
    }/*function_ge*/
    break;

/****
 *EQ
 */
    case function_eq :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN1_param_value = &this->default_variable_name;
        
            symbol_c *IN1_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            
            {
        
                {
                    identifier_c param_name("IN2");
                    /* Get the value from a foo(<param_name> = <param_value>) style call */
                    symbol_c *IN2_param_value = function_call_param_iterator.search(&param_name);
                    
                    /* Get the value from a foo(<param_value>) style call */
                    if (IN2_param_value == NULL)
                      IN2_param_value = function_call_param_iterator.next();
                    symbol_c *IN2_type_symbol = search_expression_type->get_type(IN2_param_value);
                    last_type_symbol = last_type_symbol && search_expression_type->is_same_type(IN2_type_symbol, last_type_symbol) ? search_expression_type->common_type(IN2_type_symbol, last_type_symbol) : IN2_type_symbol ;
                    
                    
                    {
                
                        function_name = (symbol_c*)(new pragma_c("__eq_"));
                        
                        char nb_param_str[10];
                        sprintf(nb_param_str, "%d", nb_param);
                        ADD_PARAM_LIST((symbol_c*)(new integer_c(nb_param_str)), (symbol_c*)(new int_type_name_c()), function_param_iterator_c::direction_in)
                        ADD_PARAM_LIST(IN1_param_value, IN1_type_symbol, function_param_iterator_c::direction_in)
                        ADD_PARAM_LIST(IN2_param_value, IN2_type_symbol, function_param_iterator_c::direction_in)
                        
                        int base_num = 3;
                        symbol_c *param_value = NULL;
                        do{
                            char my_name[10];
                            sprintf(my_name, "IN%d", base_num++);
                            identifier_c param_name(my_name);
                            
                            /* Get the value from a foo(<param_name> = <param_value>) style call */
                            param_value = function_call_param_iterator.search(&param_name);
                            
                            /* Get the value from a foo(<param_value>) style call */
                            if (param_value == NULL)
                              param_value = function_call_param_iterator.next();
                            if (param_value != NULL){
                                symbol_c *current_type_symbol = search_expression_type->get_type(param_value);
                                last_type_symbol = last_type_symbol && search_expression_type->is_same_type(current_type_symbol, last_type_symbol) ? search_expression_type->common_type(current_type_symbol, last_type_symbol) : current_type_symbol ;
                            
                                /*Function specific CODE */
                                ADD_PARAM_LIST(param_value, current_type_symbol, function_param_iterator_c::direction_in)
                            }
                            
                        }while(param_value != NULL);
                        symbol_c * return_type_symbol = &search_constant_type_c::bool_type_name;
                        function_type_suffix = last_type_symbol;
                        break;
                        
                    }
                    
                    
                    ERROR;
                }
                
            }
            
            
            ERROR;
        }
        
    }/*function_eq*/
    break;

/****
 *LT
 */
    case function_lt :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN1_param_value = &this->default_variable_name;
        
            symbol_c *IN1_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            
            {
        
                {
                    identifier_c param_name("IN2");
                    /* Get the value from a foo(<param_name> = <param_value>) style call */
                    symbol_c *IN2_param_value = function_call_param_iterator.search(&param_name);
                    
                    /* Get the value from a foo(<param_value>) style call */
                    if (IN2_param_value == NULL)
                      IN2_param_value = function_call_param_iterator.next();
                    symbol_c *IN2_type_symbol = search_expression_type->get_type(IN2_param_value);
                    last_type_symbol = last_type_symbol && search_expression_type->is_same_type(IN2_type_symbol, last_type_symbol) ? search_expression_type->common_type(IN2_type_symbol, last_type_symbol) : IN2_type_symbol ;
                    
                    
                    {
                
                        function_name = (symbol_c*)(new pragma_c("__lt_"));
                        
                        char nb_param_str[10];
                        sprintf(nb_param_str, "%d", nb_param);
                        ADD_PARAM_LIST((symbol_c*)(new integer_c(nb_param_str)), (symbol_c*)(new int_type_name_c()), function_param_iterator_c::direction_in)
                        ADD_PARAM_LIST(IN1_param_value, IN1_type_symbol, function_param_iterator_c::direction_in)
                        ADD_PARAM_LIST(IN2_param_value, IN2_type_symbol, function_param_iterator_c::direction_in)
                        
                        int base_num = 3;
                        symbol_c *param_value = NULL;
                        do{
                            char my_name[10];
                            sprintf(my_name, "IN%d", base_num++);
                            identifier_c param_name(my_name);
                            
                            /* Get the value from a foo(<param_name> = <param_value>) style call */
                            param_value = function_call_param_iterator.search(&param_name);
                            
                            /* Get the value from a foo(<param_value>) style call */
                            if (param_value == NULL)
                              param_value = function_call_param_iterator.next();
                            if (param_value != NULL){
                                symbol_c *current_type_symbol = search_expression_type->get_type(param_value);
                                last_type_symbol = last_type_symbol && search_expression_type->is_same_type(current_type_symbol, last_type_symbol) ? search_expression_type->common_type(current_type_symbol, last_type_symbol) : current_type_symbol ;
                            
                                /*Function specific CODE */
                                ADD_PARAM_LIST(param_value, current_type_symbol, function_param_iterator_c::direction_in)
                            }
                            
                        }while(param_value != NULL);
                        symbol_c * return_type_symbol = &search_constant_type_c::bool_type_name;
                        function_type_suffix = last_type_symbol;
                        break;
                        
                    }
                    
                    
                    ERROR;
                }
                
            }
            
            
            ERROR;
        }
        
    }/*function_lt*/
    break;

/****
 *LE
 */
    case function_le :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN1_param_value = &this->default_variable_name;
        
            symbol_c *IN1_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            
            {
        
                {
                    identifier_c param_name("IN2");
                    /* Get the value from a foo(<param_name> = <param_value>) style call */
                    symbol_c *IN2_param_value = function_call_param_iterator.search(&param_name);
                    
                    /* Get the value from a foo(<param_value>) style call */
                    if (IN2_param_value == NULL)
                      IN2_param_value = function_call_param_iterator.next();
                    symbol_c *IN2_type_symbol = search_expression_type->get_type(IN2_param_value);
                    last_type_symbol = last_type_symbol && search_expression_type->is_same_type(IN2_type_symbol, last_type_symbol) ? search_expression_type->common_type(IN2_type_symbol, last_type_symbol) : IN2_type_symbol ;
                    
                    
                    {
                
                        function_name = (symbol_c*)(new pragma_c("__le_"));
                        
                        char nb_param_str[10];
                        sprintf(nb_param_str, "%d", nb_param);
                        ADD_PARAM_LIST((symbol_c*)(new integer_c(nb_param_str)), (symbol_c*)(new int_type_name_c()), function_param_iterator_c::direction_in)
                        ADD_PARAM_LIST(IN1_param_value, IN1_type_symbol, function_param_iterator_c::direction_in)
                        ADD_PARAM_LIST(IN2_param_value, IN2_type_symbol, function_param_iterator_c::direction_in)
                        
                        int base_num = 3;
                        symbol_c *param_value = NULL;
                        do{
                            char my_name[10];
                            sprintf(my_name, "IN%d", base_num++);
                            identifier_c param_name(my_name);
                            
                            /* Get the value from a foo(<param_name> = <param_value>) style call */
                            param_value = function_call_param_iterator.search(&param_name);
                            
                            /* Get the value from a foo(<param_value>) style call */
                            if (param_value == NULL)
                              param_value = function_call_param_iterator.next();
                            if (param_value != NULL){
                                symbol_c *current_type_symbol = search_expression_type->get_type(param_value);
                                last_type_symbol = last_type_symbol && search_expression_type->is_same_type(current_type_symbol, last_type_symbol) ? search_expression_type->common_type(current_type_symbol, last_type_symbol) : current_type_symbol ;
                            
                                /*Function specific CODE */
                                ADD_PARAM_LIST(param_value, current_type_symbol, function_param_iterator_c::direction_in)
                            }
                            
                        }while(param_value != NULL);
                        symbol_c * return_type_symbol = &search_constant_type_c::bool_type_name;
                        function_type_suffix = last_type_symbol;
                        break;
                        
                    }
                    
                    
                    ERROR;
                }
                
            }
            
            
            ERROR;
        }
        
    }/*function_le*/
    break;

/****
 *NE
 */
    case function_ne :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN1_param_value = &this->default_variable_name;
        
            symbol_c *IN1_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            
            {
        
                {
                    identifier_c param_name("IN2");
                    /* Get the value from a foo(<param_name> = <param_value>) style call */
                    symbol_c *IN2_param_value = function_call_param_iterator.search(&param_name);
                    
                    /* Get the value from a foo(<param_value>) style call */
                    if (IN2_param_value == NULL)
                      IN2_param_value = function_call_param_iterator.next();
                    symbol_c *IN2_type_symbol = search_expression_type->get_type(IN2_param_value);
                    last_type_symbol = last_type_symbol && search_expression_type->is_same_type(IN2_type_symbol, last_type_symbol) ? search_expression_type->common_type(IN2_type_symbol, last_type_symbol) : IN2_type_symbol ;
                    
                    
                    {
                
                        function_name = (symbol_c*)(new pragma_c("__ne_"));
                        
                        char nb_param_str[10];
                        sprintf(nb_param_str, "%d", nb_param);
                        ADD_PARAM_LIST((symbol_c*)(new integer_c(nb_param_str)), (symbol_c*)(new int_type_name_c()), function_param_iterator_c::direction_in)
                        ADD_PARAM_LIST(IN1_param_value, IN1_type_symbol, function_param_iterator_c::direction_in)
                        ADD_PARAM_LIST(IN2_param_value, IN2_type_symbol, function_param_iterator_c::direction_in)
                        
                        int base_num = 3;
                        symbol_c *param_value = NULL;
                        do{
                            char my_name[10];
                            sprintf(my_name, "IN%d", base_num++);
                            identifier_c param_name(my_name);
                            
                            /* Get the value from a foo(<param_name> = <param_value>) style call */
                            param_value = function_call_param_iterator.search(&param_name);
                            
                            /* Get the value from a foo(<param_value>) style call */
                            if (param_value == NULL)
                              param_value = function_call_param_iterator.next();
                            if (param_value != NULL){
                                symbol_c *current_type_symbol = search_expression_type->get_type(param_value);
                                last_type_symbol = last_type_symbol && search_expression_type->is_same_type(current_type_symbol, last_type_symbol) ? search_expression_type->common_type(current_type_symbol, last_type_symbol) : current_type_symbol ;
                            
                                /*Function specific CODE */
                                ADD_PARAM_LIST(param_value, current_type_symbol, function_param_iterator_c::direction_in)
                            }
                            
                        }while(param_value != NULL);
                        symbol_c * return_type_symbol = &search_constant_type_c::bool_type_name;
                        function_type_suffix = last_type_symbol;
                        break;
                        
                    }
                    
                    
                    ERROR;
                }
                
            }
            
            
            ERROR;
        }
        
    }/*function_ne*/
    break;

/****
 *LEN
 */
    case function_len :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::string_type_name, last_type_symbol))
            {
        
                function_name = (symbol_c*)(new pragma_c("__len"));
                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                symbol_c * return_type_symbol = &search_constant_type_c::int_type_name;
                break;
                
            }
            
            
            ERROR;
        }
        
    }/*function_len*/
    break;

/****
 *LEFT
 */
    case function_left :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::string_type_name, last_type_symbol))
            {
        
                {
                    identifier_c param_name("L");
                    /* Get the value from a foo(<param_name> = <param_value>) style call */
                    symbol_c *L_param_value = function_call_param_iterator.search(&param_name);
                    
                    /* Get the value from a foo(<param_value>) style call */
                    if (L_param_value == NULL)
                      L_param_value = function_call_param_iterator.next();
                    symbol_c *L_type_symbol = search_expression_type->get_type(L_param_value);
                    last_type_symbol = last_type_symbol && search_expression_type->is_same_type(L_type_symbol, last_type_symbol) ? search_expression_type->common_type(L_type_symbol, last_type_symbol) : L_type_symbol ;
                    
                    if(search_expression_type->is_integer_type(L_type_symbol))
                    {
                
                        function_name = (symbol_c*)(new pragma_c("__left"));
                        ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                        ADD_PARAM_LIST(L_param_value, L_type_symbol, function_param_iterator_c::direction_in)
                        symbol_c * return_type_symbol = &search_constant_type_c::string_type_name;
                        break;
                        
                    }
                    
                    
                    ERROR;
                }
                
            }
            
            
            ERROR;
        }
        
    }/*function_left*/
    break;

/****
 *RIGHT
 */
    case function_right :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::string_type_name, last_type_symbol))
            {
        
                {
                    identifier_c param_name("L");
                    /* Get the value from a foo(<param_name> = <param_value>) style call */
                    symbol_c *L_param_value = function_call_param_iterator.search(&param_name);
                    
                    /* Get the value from a foo(<param_value>) style call */
                    if (L_param_value == NULL)
                      L_param_value = function_call_param_iterator.next();
                    symbol_c *L_type_symbol = search_expression_type->get_type(L_param_value);
                    last_type_symbol = last_type_symbol && search_expression_type->is_same_type(L_type_symbol, last_type_symbol) ? search_expression_type->common_type(L_type_symbol, last_type_symbol) : L_type_symbol ;
                    
                    if(search_expression_type->is_integer_type(L_type_symbol))
                    {
                
                        function_name = (symbol_c*)(new pragma_c("__right"));
                        ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                        ADD_PARAM_LIST(L_param_value, L_type_symbol, function_param_iterator_c::direction_in)
                        symbol_c * return_type_symbol = &search_constant_type_c::string_type_name;
                        break;
                        
                    }
                    
                    
                    ERROR;
                }
                
            }
            
            
            ERROR;
        }
        
    }/*function_right*/
    break;

/****
 *MID
 */
    case function_mid :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::string_type_name, last_type_symbol))
            {
        
                {
                    identifier_c param_name("L");
                    /* Get the value from a foo(<param_name> = <param_value>) style call */
                    symbol_c *L_param_value = function_call_param_iterator.search(&param_name);
                    
                    /* Get the value from a foo(<param_value>) style call */
                    if (L_param_value == NULL)
                      L_param_value = function_call_param_iterator.next();
                    symbol_c *L_type_symbol = search_expression_type->get_type(L_param_value);
                    last_type_symbol = last_type_symbol && search_expression_type->is_same_type(L_type_symbol, last_type_symbol) ? search_expression_type->common_type(L_type_symbol, last_type_symbol) : L_type_symbol ;
                    
                    if(search_expression_type->is_integer_type(L_type_symbol))
                    {
                
                        {
                            identifier_c param_name("P");
                            /* Get the value from a foo(<param_name> = <param_value>) style call */
                            symbol_c *P_param_value = function_call_param_iterator.search(&param_name);
                            
                            /* Get the value from a foo(<param_value>) style call */
                            if (P_param_value == NULL)
                              P_param_value = function_call_param_iterator.next();
                            symbol_c *P_type_symbol = search_expression_type->get_type(P_param_value);
                            last_type_symbol = last_type_symbol && search_expression_type->is_same_type(P_type_symbol, last_type_symbol) ? search_expression_type->common_type(P_type_symbol, last_type_symbol) : P_type_symbol ;
                            
                            if(search_expression_type->is_integer_type(P_type_symbol))
                            {
                        
                                function_name = (symbol_c*)(new pragma_c("__mid"));
                                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                                ADD_PARAM_LIST(L_param_value, L_type_symbol, function_param_iterator_c::direction_in)
                                ADD_PARAM_LIST(P_param_value, P_type_symbol, function_param_iterator_c::direction_in)
                                symbol_c * return_type_symbol = &search_constant_type_c::string_type_name;
                                break;
                                
                            }
                            
                            
                            ERROR;
                        }
                        
                    }
                    
                    
                    ERROR;
                }
                
            }
            
            
            ERROR;
        }
        
    }/*function_mid*/
    break;

/****
 *CONCAT
 */
    case function_concat :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN1_param_value = &this->default_variable_name;
        
            symbol_c *IN1_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::date_type_name, last_type_symbol))
            {
        
                {
                    identifier_c param_name("IN2");
                    /* Get the value from a foo(<param_name> = <param_value>) style call */
                    symbol_c *IN2_param_value = function_call_param_iterator.search(&param_name);
                    
                    /* Get the value from a foo(<param_value>) style call */
                    if (IN2_param_value == NULL)
                      IN2_param_value = function_call_param_iterator.next();
                    symbol_c *IN2_type_symbol = search_expression_type->get_type(IN2_param_value);
                    last_type_symbol = last_type_symbol && search_expression_type->is_same_type(IN2_type_symbol, last_type_symbol) ? search_expression_type->common_type(IN2_type_symbol, last_type_symbol) : IN2_type_symbol ;
                    
                    if(search_expression_type->is_same_type(&search_constant_type_c::tod_type_name, last_type_symbol))
                    {
                
                        function_name = (symbol_c*)(new pragma_c("__time_add"));
                        ADD_PARAM_LIST(IN1_param_value, IN1_type_symbol, function_param_iterator_c::direction_in)
                        ADD_PARAM_LIST(IN2_param_value, IN2_type_symbol, function_param_iterator_c::direction_in)
                        symbol_c * return_type_symbol = &search_constant_type_c::dt_type_name;
                        break;
                        
                    }
                    
                    
                    ERROR;
                }
                
            }
            
            if(search_expression_type->is_same_type(&search_constant_type_c::string_type_name, last_type_symbol))
            {
        
                {
                    identifier_c param_name("IN2");
                    /* Get the value from a foo(<param_name> = <param_value>) style call */
                    symbol_c *IN2_param_value = function_call_param_iterator.search(&param_name);
                    
                    /* Get the value from a foo(<param_value>) style call */
                    if (IN2_param_value == NULL)
                      IN2_param_value = function_call_param_iterator.next();
                    symbol_c *IN2_type_symbol = search_expression_type->get_type(IN2_param_value);
                    last_type_symbol = last_type_symbol && search_expression_type->is_same_type(IN2_type_symbol, last_type_symbol) ? search_expression_type->common_type(IN2_type_symbol, last_type_symbol) : IN2_type_symbol ;
                    
                    if(search_expression_type->is_same_type(&search_constant_type_c::string_type_name, last_type_symbol))
                    {
                
                        function_name = (symbol_c*)(new pragma_c("__concat"));
                        
                        char nb_param_str[10];
                        sprintf(nb_param_str, "%d", nb_param);
                        ADD_PARAM_LIST((symbol_c*)(new integer_c(nb_param_str)), (symbol_c*)(new int_type_name_c()), function_param_iterator_c::direction_in)
                        ADD_PARAM_LIST(IN1_param_value, IN1_type_symbol, function_param_iterator_c::direction_in)
                        ADD_PARAM_LIST(IN2_param_value, IN2_type_symbol, function_param_iterator_c::direction_in)
                        
                        int base_num = 3;
                        symbol_c *param_value = NULL;
                        do{
                            char my_name[10];
                            sprintf(my_name, "IN%d", base_num++);
                            identifier_c param_name(my_name);
                            
                            /* Get the value from a foo(<param_name> = <param_value>) style call */
                            param_value = function_call_param_iterator.search(&param_name);
                            
                            /* Get the value from a foo(<param_value>) style call */
                            if (param_value == NULL)
                              param_value = function_call_param_iterator.next();
                            if (param_value != NULL){
                                symbol_c *current_type_symbol = search_expression_type->get_type(param_value);
                                last_type_symbol = last_type_symbol && search_expression_type->is_same_type(current_type_symbol, last_type_symbol) ? search_expression_type->common_type(current_type_symbol, last_type_symbol) : current_type_symbol ;
                            
                                /*Function specific CODE */
                                ADD_PARAM_LIST(param_value, current_type_symbol, function_param_iterator_c::direction_in)
                            }
                            
                        }while(param_value != NULL);
                        symbol_c * return_type_symbol = &search_constant_type_c::string_type_name;
                        break;
                        
                    }
                    
                    
                    ERROR;
                }
                
            }
            
            
            ERROR;
        }
        
    }/*function_concat*/
    break;

/****
 *INSERT
 */
    case function_insert :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN1_param_value = &this->default_variable_name;
        
            symbol_c *IN1_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::string_type_name, last_type_symbol))
            {
        
                {
                    identifier_c param_name("IN2");
                    /* Get the value from a foo(<param_name> = <param_value>) style call */
                    symbol_c *IN2_param_value = function_call_param_iterator.search(&param_name);
                    
                    /* Get the value from a foo(<param_value>) style call */
                    if (IN2_param_value == NULL)
                      IN2_param_value = function_call_param_iterator.next();
                    symbol_c *IN2_type_symbol = search_expression_type->get_type(IN2_param_value);
                    last_type_symbol = last_type_symbol && search_expression_type->is_same_type(IN2_type_symbol, last_type_symbol) ? search_expression_type->common_type(IN2_type_symbol, last_type_symbol) : IN2_type_symbol ;
                    
                    if(search_expression_type->is_same_type(&search_constant_type_c::string_type_name, last_type_symbol))
                    {
                
                        {
                            identifier_c param_name("P");
                            /* Get the value from a foo(<param_name> = <param_value>) style call */
                            symbol_c *P_param_value = function_call_param_iterator.search(&param_name);
                            
                            /* Get the value from a foo(<param_value>) style call */
                            if (P_param_value == NULL)
                              P_param_value = function_call_param_iterator.next();
                            symbol_c *P_type_symbol = search_expression_type->get_type(P_param_value);
                            last_type_symbol = last_type_symbol && search_expression_type->is_same_type(P_type_symbol, last_type_symbol) ? search_expression_type->common_type(P_type_symbol, last_type_symbol) : P_type_symbol ;
                            
                            if(search_expression_type->is_integer_type(P_type_symbol))
                            {
                        
                                function_name = (symbol_c*)(new pragma_c("__insert"));
                                ADD_PARAM_LIST(IN1_param_value, IN1_type_symbol, function_param_iterator_c::direction_in)
                                ADD_PARAM_LIST(IN2_param_value, IN2_type_symbol, function_param_iterator_c::direction_in)
                                ADD_PARAM_LIST(P_param_value, P_type_symbol, function_param_iterator_c::direction_in)
                                symbol_c * return_type_symbol = &search_constant_type_c::string_type_name;
                                break;
                                
                            }
                            
                            
                            ERROR;
                        }
                        
                    }
                    
                    
                    ERROR;
                }
                
            }
            
            
            ERROR;
        }
        
    }/*function_insert*/
    break;

/****
 *DELETE
 */
    case function_delete :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN_param_value = &this->default_variable_name;
        
            symbol_c *IN_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::string_type_name, last_type_symbol))
            {
        
                {
                    identifier_c param_name("L");
                    /* Get the value from a foo(<param_name> = <param_value>) style call */
                    symbol_c *L_param_value = function_call_param_iterator.search(&param_name);
                    
                    /* Get the value from a foo(<param_value>) style call */
                    if (L_param_value == NULL)
                      L_param_value = function_call_param_iterator.next();
                    symbol_c *L_type_symbol = search_expression_type->get_type(L_param_value);
                    last_type_symbol = last_type_symbol && search_expression_type->is_same_type(L_type_symbol, last_type_symbol) ? search_expression_type->common_type(L_type_symbol, last_type_symbol) : L_type_symbol ;
                    
                    if(search_expression_type->is_integer_type(L_type_symbol))
                    {
                
                        {
                            identifier_c param_name("P");
                            /* Get the value from a foo(<param_name> = <param_value>) style call */
                            symbol_c *P_param_value = function_call_param_iterator.search(&param_name);
                            
                            /* Get the value from a foo(<param_value>) style call */
                            if (P_param_value == NULL)
                              P_param_value = function_call_param_iterator.next();
                            symbol_c *P_type_symbol = search_expression_type->get_type(P_param_value);
                            last_type_symbol = last_type_symbol && search_expression_type->is_same_type(P_type_symbol, last_type_symbol) ? search_expression_type->common_type(P_type_symbol, last_type_symbol) : P_type_symbol ;
                            
                            if(search_expression_type->is_integer_type(P_type_symbol))
                            {
                        
                                function_name = (symbol_c*)(new pragma_c("__delete"));
                                ADD_PARAM_LIST(IN_param_value, IN_type_symbol, function_param_iterator_c::direction_in)
                                ADD_PARAM_LIST(L_param_value, L_type_symbol, function_param_iterator_c::direction_in)
                                ADD_PARAM_LIST(P_param_value, P_type_symbol, function_param_iterator_c::direction_in)
                                symbol_c * return_type_symbol = &search_constant_type_c::string_type_name;
                                break;
                                
                            }
                            
                            
                            ERROR;
                        }
                        
                    }
                    
                    
                    ERROR;
                }
                
            }
            
            
            ERROR;
        }
        
    }/*function_delete*/
    break;

/****
 *REPLACE
 */
    case function_replace :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN1_param_value = &this->default_variable_name;
        
            symbol_c *IN1_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::string_type_name, last_type_symbol))
            {
        
                {
                    identifier_c param_name("IN2");
                    /* Get the value from a foo(<param_name> = <param_value>) style call */
                    symbol_c *IN2_param_value = function_call_param_iterator.search(&param_name);
                    
                    /* Get the value from a foo(<param_value>) style call */
                    if (IN2_param_value == NULL)
                      IN2_param_value = function_call_param_iterator.next();
                    symbol_c *IN2_type_symbol = search_expression_type->get_type(IN2_param_value);
                    last_type_symbol = last_type_symbol && search_expression_type->is_same_type(IN2_type_symbol, last_type_symbol) ? search_expression_type->common_type(IN2_type_symbol, last_type_symbol) : IN2_type_symbol ;
                    
                    if(search_expression_type->is_same_type(&search_constant_type_c::string_type_name, last_type_symbol))
                    {
                
                        {
                            identifier_c param_name("L");
                            /* Get the value from a foo(<param_name> = <param_value>) style call */
                            symbol_c *L_param_value = function_call_param_iterator.search(&param_name);
                            
                            /* Get the value from a foo(<param_value>) style call */
                            if (L_param_value == NULL)
                              L_param_value = function_call_param_iterator.next();
                            symbol_c *L_type_symbol = search_expression_type->get_type(L_param_value);
                            last_type_symbol = last_type_symbol && search_expression_type->is_same_type(L_type_symbol, last_type_symbol) ? search_expression_type->common_type(L_type_symbol, last_type_symbol) : L_type_symbol ;
                            
                            if(search_expression_type->is_integer_type(L_type_symbol))
                            {
                        
                                {
                                    identifier_c param_name("P");
                                    /* Get the value from a foo(<param_name> = <param_value>) style call */
                                    symbol_c *P_param_value = function_call_param_iterator.search(&param_name);
                                    
                                    /* Get the value from a foo(<param_value>) style call */
                                    if (P_param_value == NULL)
                                      P_param_value = function_call_param_iterator.next();
                                    symbol_c *P_type_symbol = search_expression_type->get_type(P_param_value);
                                    last_type_symbol = last_type_symbol && search_expression_type->is_same_type(P_type_symbol, last_type_symbol) ? search_expression_type->common_type(P_type_symbol, last_type_symbol) : P_type_symbol ;
                                    
                                    if(search_expression_type->is_integer_type(P_type_symbol))
                                    {
                                
                                        function_name = (symbol_c*)(new pragma_c("__replace"));
                                        ADD_PARAM_LIST(IN1_param_value, IN1_type_symbol, function_param_iterator_c::direction_in)
                                        ADD_PARAM_LIST(IN2_param_value, IN2_type_symbol, function_param_iterator_c::direction_in)
                                        ADD_PARAM_LIST(L_param_value, L_type_symbol, function_param_iterator_c::direction_in)
                                        ADD_PARAM_LIST(P_param_value, P_type_symbol, function_param_iterator_c::direction_in)
                                        symbol_c * return_type_symbol = &search_constant_type_c::string_type_name;
                                        break;
                                        
                                    }
                                    
                                    
                                    ERROR;
                                }
                                
                            }
                            
                            
                            ERROR;
                        }
                        
                    }
                    
                    
                    ERROR;
                }
                
            }
            
            
            ERROR;
        }
        
    }/*function_replace*/
    break;

/****
 *FIND
 */
    case function_find :
    {
        symbol_c *last_type_symbol = NULL;

        {
            /* Get the value from a foo(<param_name> = <param_value>) style call */
            symbol_c *IN1_param_value = &this->default_variable_name;
        
            symbol_c *IN1_type_symbol = param_data_type;
            last_type_symbol = param_data_type;
            
            if(search_expression_type->is_same_type(&search_constant_type_c::string_type_name, last_type_symbol))
            {
        
                {
                    identifier_c param_name("IN2");
                    /* Get the value from a foo(<param_name> = <param_value>) style call */
                    symbol_c *IN2_param_value = function_call_param_iterator.search(&param_name);
                    
                    /* Get the value from a foo(<param_value>) style call */
                    if (IN2_param_value == NULL)
                      IN2_param_value = function_call_param_iterator.next();
                    symbol_c *IN2_type_symbol = search_expression_type->get_type(IN2_param_value);
                    last_type_symbol = last_type_symbol && search_expression_type->is_same_type(IN2_type_symbol, last_type_symbol) ? search_expression_type->common_type(IN2_type_symbol, last_type_symbol) : IN2_type_symbol ;
                    
                    if(search_expression_type->is_same_type(&search_constant_type_c::string_type_name, last_type_symbol))
                    {
                
                        function_name = (symbol_c*)(new pragma_c("__find"));
                        ADD_PARAM_LIST(IN1_param_value, IN1_type_symbol, function_param_iterator_c::direction_in)
                        ADD_PARAM_LIST(IN2_param_value, IN2_type_symbol, function_param_iterator_c::direction_in)
                        symbol_c * return_type_symbol = &search_constant_type_c::int_type_name;
                        break;
                        
                    }
                    
                    
                    ERROR;
                }
                
            }
            
            
            ERROR;
        }
        
    }/*function_find*/
    break;

    case function_none :
    ERROR;
}
