#include <iostream>
#include <blt/parse/argparse.h>
#include <blt/std/logging.h>
#include "load_file.h"

int main(int argc, const char** argv)
{
    blt::arg_parse parser;
    
    parser.addArgument(blt::arg_builder("--generator").setAction(blt::arg_action_t::STORE).setDefault("./gl_doc_generator.py")
                                                      .setHelp("Path to the OpenGL doc generator python script").setNArgs(1).build());
    
    parser.addArgument(blt::arg_builder("--python").setAction(blt::arg_action_t::STORE).setDefault("python3")
                                                   .setHelp("Path / command to execute python with")
                                                   .setNArgs(1).build());
    
    parser.addArgument(blt::arg_builder("gl_file").setAction(blt::arg_action_t::STORE).setHelp("OpenGL header file to put the docs into").setNArgs(1)
                                                  .setRequired().build());
    
    auto args = parser.parse_args(argc, argv);
    
    auto generatorPath = args.get<std::string>("generator");
    auto pythonPath = args.get<std::string>("python");
    auto filePath = args.get<std::string>("gl_file");
    
    BLT_INFO("Using %s on file %s", generatorPath.c_str(), filePath.c_str());
    
    blt::parser file_parser(filePath, pythonPath, generatorPath);
    file_parser.load_file().parse();
    auto vec = file_parser.get();
    
    //BLT_DEBUG("Result:\n%s", vec.c_str());
    
    return 0;
}
