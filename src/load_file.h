/*
 *  <Short Description>
 *  Copyright (C) 2023  Brett Terpstra
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
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef GL_DOC_GENERATOR_LOAD_FILE_H
#define GL_DOC_GENERATOR_LOAD_FILE_H

#include <string>
#include <string_view>
#include <blt/std/logging.h>
#include <cctype>
#include <blt/std/hashmap.h>

namespace blt
{
    
    enum class state_type
    {
        OTHER,                  // literally anything else (we do not care about it)
        PREPROCESSOR_DEFINE,    // #define
        IDENTIFIER,             // either a variable or a type (void / thisismyvar)
        POSSIBLE_FUNC,          // we had an identifier and found a space
        FUNCTION                // myfunctioname(
    };
    
    struct partial_container
    {
        // the complete previous block of data we parsed through
        std::string parsed;
        // the function documentation we are waiting for
        std::string waiting_for;
        // the next block will contain the actual function definition
        partial_container(std::string parsed, std::string waitingFor);
    };
    
    class parser
    {
        private:
            bool clear_see_also = false;
            bool clear_desc = false;
            bool brief = false;
            std::string path;
            std::string file;
            std::string data;
            std::string parsed;
            
            std::string pythonPath;
            std::string generatorPath;
            state_type state = state_type::OTHER;
            
            // holds the owning memory for the comment strings
            std::vector<std::string> doc_string_storage;
            // holds a mapping between all param names and a corresponding string_view to a string stored in doc_string_storage containing the doc
            HASHMAP<std::string, std::string_view> found_docs;
            
            // list of partially compiled blocks we will need to loop through
            std::vector<partial_container> partial_blocks;
            // list of not found docs. useful for debug.
            HASHSET<std::string> notfound;
            
            inline void reset()
            {
                state = state_type::OTHER;
                parsed += data;
                data.clear();
            }
            
            inline static bool is_ident_b(char c)
            {
                return std::isalpha(c) || c == '_';
            }
            
            inline static bool is_ident(char c)
            {
                return std::isalnum(c) || c == '_';
            }
            
            static std::string strip_func(std::string_view func);
            
            void strip_extras(std::string& str) const;
            
            static std::string strip_codes(const std::string& str, const std::string& func_name);
            
            void process_gl_func(std::string_view func_name);
        
        public:
            explicit parser(std::string_view path, std::string_view pythonPath, std::string_view generatorPath, bool seeAlso, bool desc, bool brief):
                    clear_see_also(seeAlso), clear_desc(desc), brief(brief), path(path), pythonPath(pythonPath), generatorPath(generatorPath)
            {}
            
            parser& load_file();
            
            parser& parse();
            
            inline const std::string& get()
            {
                return parsed;
            }
    };
    
}

#endif //GL_DOC_GENERATOR_LOAD_FILE_H
