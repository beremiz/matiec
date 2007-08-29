/*
 * (c) 2003 Mario de Sousa
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


/*
 * This file contains the code that stores the output generated
 * by each specific version of the 4th stage.
 */


#include "../absyntax/absyntax.hh"

class stage4out_c {
  public:
    std::string indent_level;
    std::string indent_spaces;

  public:
    stage4out_c(std::string indent_level = "  ");
    stage4out_c(const char *dir, const char *radix, const char *extension, std::string indent_level = "  ");
    ~stage4out_c(void);

    void indent_right(void);
    void indent_left(void);

    void *print(const char *str);
    void *print(std::string str);
    
    void *print_integer(int integer);

    void *printupper(const char *str);
    void *printupper(std::string str);

    void *printlocation(const char *str);
    void *printlocation(std::string str);

    void *printlocation_comasep(const char *str);

  protected:
    std::ostream *out;
    std::fstream *m_file;

};





int stage4(symbol_c *tree_root);
