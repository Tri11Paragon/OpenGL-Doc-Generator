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
#include <regex>
#include <utility>

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
            
            //BLT_TRACE("We have '%c' with '%s' at index %d state %d", c, data.c_str(), index, state);
            
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
                        if (blt::string::starts_with(full_data, "#define gl"))
                            process_gl_func(std::string_view(&full_data[s1], s3 - s1));
                        reset();
                    } else if (c == '\n')
                        last = false;
                    else if (c == '\\')
                        last = true;
                    else if (!(is_ident(c) || std::isspace(c)))
                        reset();
                    break;
                case state_type::IDENTIFIER:
                    if (c == '(')
                        state = state_type::FUNCTION;
                    else if (std::isspace(c))
                        state = state_type::POSSIBLE_FUNC;
                    else if (!is_ident(c))
                        reset();
                    break;
                case state_type::POSSIBLE_FUNC:
                    if (c == '(')
                        state = state_type::FUNCTION;
                    else if (!std::isspace(c))
                    {
                        if (is_ident(c))
                            state = state_type::FUNCTION;
                        else
                            reset();
                    }
                    break;
                case state_type::FUNCTION:
                    if (c == ')')
                    {
                        // Jacob if you're actually reading this, this is all ugly & hacky code :3
                        // please dm that you've read to here <3
                        // enjoy trying to understand it.
                        auto end = data.find('(') - 1;
                        // gotta remove whitespace
                        while (end > 0 && std::isspace(data[end]))
                            end--;
                        // end isn't inclusive
                        end += 1;
                        // begin is
                        auto begin = end - 1;
                        while (begin > 0 && is_ident(data[begin]))
                            begin--;
                        // skip the ws
                        begin += 1;
                        auto sv = std::string_view(&data[begin], end - begin);
                        if (blt::string::starts_with(sv, "gl"))
                            process_gl_func(sv);
                        reset();
                    } else if (!(c == '(' || is_ident(c) || c == ',' || std::isspace(c)))
                        reset();
                    break;
                case state_type::OTHER:
                    if (c == '#')
                        state = state_type::PREPROCESSOR_DEFINE;
                    else if (std::isspace(c))
                        reset();
                    else if (data.size() <= 1 && is_ident_b(c))
                        state = state_type::IDENTIFIER;
                    break;
            }
        }
        std::string finished;
        for (auto& v : partial_blocks)
        {
            finished += v.parsed;
            auto p = found_docs.find(v.waiting_for);
            if (p != found_docs.end())
            {
                BLT_TRACE0_STREAM << "I was able to find the docs for " << v.waiting_for << "\n";
                finished += strip_codes(std::string(p->second), v.waiting_for);
            } else
            {
                BLT_TRACE1_STREAM << "I was unable to find the docs for " << v.waiting_for << "\n";
                finished += "// Unable to find the docs for this function!\n";
                notfound.insert(v.waiting_for);
                BLT_WARN("Unable to find docs for function '%s'", v.waiting_for.c_str());
            }
        }
        finished += parsed;
        parsed = std::move(finished);
//        BLT_DEBUG("Finished in state %d", (int) state);
        //BLT_DEBUG("With data %s", parsed.c_str());
        for (auto& v : notfound)
        {
            BLT_WARN("Unable to find docs for function '%s'", v.c_str());
        }
        return *this;
    }
    
    void parser::process_gl_func(std::string_view func_name)
    {
        auto p = found_docs.find(std::string(func_name));
        if (p != found_docs.end())
        {
            BLT_TRACE("Using cached docs!");
            parsed += p->second;
            return;
        }
        std::string reference_link = "https://registry.khronos.org/OpenGL-Refpages/gl4/html/";
        reference_link.reserve(func_name.length() + 6);
        reference_link += strip_func(func_name);
        reference_link += ".xhtml";
        std::string command = pythonPath + " " + generatorPath + " " + reference_link;
        auto pFile = popen(command.c_str(), "r");
        
        std::string doc;
        char buf[4096];
        size_t readn;
        while ((readn = fread(buf, 1, sizeof(buf), pFile)) > 0)
            doc += std::string(buf, readn);
        
        pclose(pFile);
        
        blt::string::trim(doc);
        // no way for a proper generated doc to be this small
        const std::string NULL_STR = "NULL";
        if (doc.length() <= NULL_STR.length() * 2)
        {
            partial_blocks.emplace_back(parsed, std::string(func_name));
            parsed.clear();
            BLT_DEBUG("Failed to find function '%s'", std::string(func_name).c_str());
            return;
        }
        strip_extras(doc);
        
        BLT_INFO("Running on function %s", std::string(func_name).c_str());
        
        doc_string_storage.push_back(std::move(doc));
        auto& doc_ref = doc_string_storage.back();
        
        size_t search = doc_ref.find("@code");
        while (search != std::string::npos)
        {
            // skip through @code
            search += 5;
            // skip through spaces
            while (search < doc_ref.size() && std::isspace(doc_ref[search]))
                search++;
            // then through the first identifier
            while (search < doc_ref.size() && is_ident(doc_ref[search]))
                search++;
            // then more space
            while (search < doc_ref.size() && std::isspace(doc_ref[search]))
                search++;
            
            auto s2 = doc_ref.find('(', search);
            auto var = doc_ref.substr(search, s2 - search);
            BLT_TRACE("Found docs for function '%s'", var.c_str());
            
            found_docs.insert({var, std::string_view(doc_ref.data(), doc_ref.size())});
            
            search = doc_ref.find("@code", search);
        }
        
        parsed += strip_codes(doc_ref, std::string(func_name));
        
        //BLT_INFO("Docs: %s", doc_ref.c_str());
    }
    
    std::string parser::strip_func(std::string_view func)
    {
        std::string f(func);
        
        std::regex matrx(R"(((Matrix)(\d|\w)+)|\d+(i|u|f|d|v|s|N|b|I|^(Is))+)");
        
        return std::regex_replace(f, matrx, "");
    }
    
    std::string parser::strip_codes(const std::string& str, const std::string& func_name)
    {
        static volatile bool b = true;
        if (b)
            return str;
        std::string new_str;
        
        auto lines = blt::string::split(str, '\n');
        for (auto& line : lines)
        {
            if (line.empty())
                continue;
            if (blt::string::contains(line, "@code") && !blt::string::contains(line, func_name + "("))
                continue;
            new_str += line += '\n';
        }
        
        
        return new_str;
    }
    
    void parser::strip_extras(std::string& str) const
    {
        std::string new_str;
        
        auto lines = blt::string::split(str, '\n');
        for (size_t i = 0; i < lines.size(); i++)
        {
            auto& line = lines[i];
            if (brief)
            {
                if (!(blt::string::contains(line, "@name") || blt::string::contains(line, "@code") || blt::string::contains(line, "@usage") ||
                      blt::string::contains(line, "/**") || blt::string::contains(line, "*/")))
                    continue;
                
                new_str += line += '\n';
                continue;
            }
            if (line.empty())
                continue;
            if (clear_see_also && blt::string::contains(line, "@see"))
                continue;
            if (clear_desc && blt::string::contains(line, "@description"))
            {
                while (i < lines.size())
                {
                    if (lines[i] == " * ")
                        break;
                    i++;
                }
                continue;
            }
            
            new_str += line += '\n';
        }
        
        str = new_str;
    }
    
    partial_container::partial_container(std::string parsed, std::string waitingFor): parsed(std::move(parsed)), waiting_for(std::move(waitingFor))
    {}
}