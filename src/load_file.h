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

namespace blt
{
    
    enum class state_type
    {
        OTHER,                  // literally anything else (we do not care about it)
        PREPROCESSOR_DEFINE,    // #define
        IDENTIFIER,             // either a variable or a type (void / thisismyvar)
        POSSIBLE_FUNC,
        FUNCTION                // myfunctioname(
    };
    
    struct state_container
    {
        std::string full_data;   // the entire parsed string
        std::string_view data;   // a view into full_data containing relevant data (GL function name)
        state_type type;         // the type of data stored
    };
    
    class parser
    {
        private:
            std::string path;
            std::string file;
            std::string data;
            std::string parsed;
            state_type state = state_type::OTHER;
            std::vector<state_container> parsed_tokens;
            
            inline void reset()
            {
                state = state_type::OTHER;
                parsed += data;
                data.clear();
            }
            
            void process_gl_func(std::string_view func_name);
        
        public:
            explicit parser(std::string_view path): path(path)
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
