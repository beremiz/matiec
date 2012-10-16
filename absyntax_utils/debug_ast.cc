/*
 *  matiec - a compiler for the programming languages defined in IEC 61131-3
 *  Copyright (C) 2012  Mario de Sousa (msousa@fe.up.pt)
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


/*
 * Some classes to help with debuging.
 *
 * These classes will print out the current state of a symbol or a portion of the Abstract Syntax Tree.
 */

/* TODO: Use a class similar to stage4out_c so that we can have nice indentation when printing an AST
 *       Create a template so that we can TRACE the execution of other visitor classes doing usefull work!
 */



#include <unistd.h>
#include <stdio.h>  /* required for NULL */
#include "absyntax_utils.hh"












print_symbol_c *print_symbol_c::singleton = NULL;


void print_symbol_c::print(symbol_c* symbol) {
  if (NULL == singleton)   singleton = new print_symbol_c();
  if (NULL == singleton)   ERROR;

  symbol->accept(*singleton);
}








void print_symbol_c::fcall(symbol_c* symbol) {
  dump_symbol(symbol);
  fprintf(stderr, "\n");
}


void print_symbol_c::dump_symbol(symbol_c* symbol) {
  fprintf(stderr, "(%03d:%03d..%03d:%03d) \t%s\t", symbol->first_line, symbol->first_column, symbol->last_line, symbol->last_column, symbol->absyntax_cname());

  fprintf(stderr, "  datatype=");
  if (NULL == symbol->datatype)
    fprintf(stderr, "NULL\t\t");
  else 
    fprintf(stderr, symbol->datatype->absyntax_cname());
  fprintf(stderr, "\t<-{");
  if (symbol->candidate_datatypes.size() == 0) {
    fprintf(stderr, "\t\t\t\t\t");
  } else if (symbol->candidate_datatypes.size() <= 2) {
    for (unsigned int i = 0; i < 2; i++)
      if (i < symbol->candidate_datatypes.size())
        fprintf(stderr, " %s,", symbol->candidate_datatypes[i]->absyntax_cname());
      else
        fprintf(stderr, "\t\t\t");
  } else {
    fprintf(stderr, "(%d)\t\t\t\t\t", symbol->candidate_datatypes.size());
  }
  fprintf(stderr, "}\t");          
}



void *print_symbol_c::visit(il_instruction_c *symbol) {
   dump_symbol(symbol);

  fprintf(stderr, "  next_il_=%d ", symbol->next_il_instruction.size());
  fprintf(stderr, "  prev_il_=%d ", symbol->prev_il_instruction.size());
  
  if (symbol->prev_il_instruction.size() == 0)
    fprintf(stderr, "(----,");
  else if (symbol->prev_il_instruction[0]->datatype == NULL)
    fprintf(stderr, "(NULL,");
  else if (!get_datatype_info_c::is_type_valid(symbol->prev_il_instruction[0]->datatype))
    fprintf(stderr, "(****,");
  else
    fprintf(stderr, "(    ,");
  
  if (symbol->next_il_instruction.size() == 0)
    fprintf(stderr, "----)");
  else if (symbol->next_il_instruction[0]->datatype == NULL)
    fprintf(stderr, "NULL)");
  else if (!get_datatype_info_c::is_type_valid(symbol->next_il_instruction[0]->datatype))
    fprintf(stderr, "****)");
  else 
    fprintf(stderr, "    )");
  
  fprintf(stderr, "\n");
  
  return NULL;
};













print_ast_c *print_ast_c::singleton = NULL;


void print_ast_c::print(symbol_c* symbol) {
  if (NULL == singleton)   singleton = new print_ast_c();
  if (NULL == singleton)   ERROR;

  symbol->accept(*singleton);
}

  
void print_ast_c::prefix_fcall(symbol_c* symbol) {print_symbol_c::print(symbol);}
void print_ast_c::suffix_fcall(symbol_c* symbol) {}
  















