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
#include "load_file.h"
#include <blt/std/loader.h>

namespace blt
{
    
    parser& parser::load_file()
    {
        file = blt::fs::getFile(path);
        return *this;
    }
    
    void func
            ()
    {
    
    }
    
    parser& parser::parse()
    {
        size_t index = 0;
        bool last = false;
        while (index < file.size())
        {
            char c = file[index++];
            data += c;
            // skip comments
            if (c == '/' && index < file.size())
            {
                reset();
                if (file[index] == '/')
                    while (index < file.size() && file[index] != '\n')
                    { parsed += file[index++]; }
                if (file[index] == '*')
                {
                    while (index + 2 < file.size() && !(file[index + 1] == '*' && file[index + 2] == '/'))
                    { parsed += file[index++]; }
                    parsed += file[index];
                    parsed += file[index + 1];
                    index += 2;
                }
                continue;
            }
            
            BLT_TRACE("We have '%c' with '%s' at index %d state %d", c, data.c_str(), index, state);
            
            switch (state)
            {
                case state_type::PREPROCESSOR_DEFINE:
                    if (c == '\n' && !last)
                    {
                        std::string full_data = data.substr(0, data.size() - 1);
                        
                        auto s1 = full_data.find(' ') + 1;
                        auto s2 = s1;
                        while (s2 < full_data.size() && std::isspace(full_data[s2++]));
                        auto s3 = full_data.find(' ', s2);
                        if (s3 == std::string_view::npos)
                            s3 = full_data.size();
                        if (blt::string::starts_with(full_data, "#define"))
                            process_gl_func(std::string_view(&full_data[s1], s3 - s1));
                        reset();
                    } else if (c == '\n')
                        last = false;
                    else if (c == '\\')
                        last = true;
                    else if (!(std::isalpha(c) || c == '_' || std::isspace(c)))
                        reset();
                    break;
                case state_type::IDENTIFIER:
                    if (c == '(')
                        state = state_type::FUNCTION;
                    else if (std::isspace(c))
                        state = state_type::POSSIBLE_FUNC;
                    else if (!(std::isalnum(c) || c == '_'))
                        reset();
                    break;
                case state_type::POSSIBLE_FUNC:
                    if (c == '(')
                        state = state_type::POSSIBLE_FUNC;
                    else if (!std::isspace(c))
                        reset();
                    break;
                case state_type::FUNCTION:
                    if (c == '{')
                    {
//                        state = state_type::OTHER;
//                        state_container con;
//                        con.type = state_type::FUNCTION;
//                        con.full_data = data;
//                        data = "";
//                        con.data = std::string_view(con.full_data.data(), con.full_data.find('('));
                        BLT_DEBUG(data);
                        reset();
                    } else if (!(c == ')' || std::isalnum(c) || c == ',' || std::isblank(c)))
                        reset();
                    break;
                case state_type::OTHER:
                    if (c == '#')
                        state = state_type::PREPROCESSOR_DEFINE;
                    else if (c == '\n')
                        reset();
                    else if (data.size() <= 1 && (std::isalpha(c) || c == '_'))
                        state = state_type::IDENTIFIER;
                    break;
            }
        }
        BLT_DEBUG("Finished in state %d", (int) state);
//        BLT_DEBUG("With data %s", parsed.c_str());
        return *this;
    }
    
    void parser::process_gl_func(std::string_view func_name)
    {
        BLT_INFO("Running on function %s", std::string(func_name).c_str());
    }
    
}