#include <iostream>
#include <blt/parse/argparse.h>
#include <blt/std/logging.h>
#include <fstream>
#include "load_file.h"

int main(int argc, const char** argv)
{
    blt::arg_parse parser;
    
    parser.addArgument(blt::arg_builder("--generator").setAction(blt::arg_action_t::STORE).setDefault("./gl_doc_generator.py")
                                                      .setHelp("Path to the OpenGL doc generator python script").setNArgs(1).build());
    
    parser.addArgument(blt::arg_builder("--python").setAction(blt::arg_action_t::STORE).setDefault("python3")
                                                   .setHelp("Path / command to execute python with")
                                                   .setNArgs(1).build());
    
    parser.addArgument(blt::arg_builder("--output", "-o").setAction(blt::arg_action_t::STORE)
                                                         .setHelp("set the output file to write to. Defaults to $(gl_file)_doc.$(ext)").setNArgs(1)
                                                         .build());
    
    parser.addArgument(blt::arg_builder("--no-see", "-s").setAction(blt::arg_action_t::STORE_TRUE).setHelp("Don't include see also").build());
    parser.addArgument(blt::arg_builder("--no-desc", "-d").setAction(blt::arg_action_t::STORE_TRUE).setHelp("Don't include description").build());
    parser.addArgument(
            blt::arg_builder("--brief", "-b").setAction(blt::arg_action_t::STORE_TRUE).setHelp("Make the comments as short as possible").build());
    
    parser.addArgument(blt::arg_builder("gl_file").setAction(blt::arg_action_t::STORE).setHelp("OpenGL header file to put the docs into").setNArgs(1)
                                                  .setRequired().build());
    
    auto args = parser.parse_args(argc, argv);
    
    auto generatorPath = args.get<std::string>("generator");
    auto pythonPath = args.get<std::string>("python");
    auto filePath = args.get<std::string>("gl_file");
    
    std::string outputFilePath;
    if (args.contains("output"))
    {
        outputFilePath = args.get<std::string>("output");
    } else
    {
        auto exts = blt::string::split(filePath, '.');
        if (blt::string::contains(filePath, '.'))
        {
            // cancer
            for (size_t i = 0; i < exts.size() - 1; i++)
            {
                outputFilePath += exts[i];
                if (i != exts.size() - 2)
                    outputFilePath += '.';
            }
            outputFilePath += "_doc.";
            outputFilePath += exts[exts.size() - 1];
        } else
        {
            outputFilePath += filePath += "_doc";
        }
    }
    
    BLT_INFO("Using '%s' on file '%s' output to '%s'", generatorPath.c_str(), filePath.c_str(), outputFilePath.c_str());
    
    blt::parser file_parser(filePath, pythonPath, generatorPath, args.contains("no-see"), args.contains("no-desc"), args.contains("brief"));
    file_parser.load_file().parse();
    auto vec = file_parser.get();
    
    std::ofstream output(outputFilePath);
    
    output << vec;
    output.flush();
    output.close();
    //BLT_DEBUG("Result:\n%s", vec.c_str());
    
    return 0;
}
