
#include "Argument.h"
#include <fstream>

#define RESET   "\033[0m"
#define RED     "\033[31m"      

Argument_Parser::Argument_Parser(std::ostream & error_stream) : error_output_(error_stream) {

}

std::shared_ptr<Argument_Parser> Argument_Parser::make_argument_parser(std::ostream & error_stream) {
    return std::make_shared<Argument_Parser>(Argument_Parser(error_stream));
}

bool Argument_Parser::parse_argument(int argc, char* argv[]){

    try{
        if (argc < 2) { 

            throw std::runtime_error("No input file provided.");
        
        }

        if (std::string(argv[1]) == "--help") {
            std::cout << "Usage: qborrow [input_file] [options]\n"
                      << "Options:\n"
                      << "  --pretty-print          Print the parsed program in a human-readable format.\n"
                      << "  --no-print-preprocess   Do not print the result of preprocessor.\n";
            exit(0);
        }


        std::ifstream input_file(argv[1]);

        if (!input_file.is_open()) {
            
            throw std::runtime_error("Cannot open input file: " + std::string(argv[1]));
        }    

        parse_result_ = "";
        std::string line;
        while (std::getline(input_file, line)) 
            parse_result_ += line + "\n";

        input_file.close(); 


        int idx = 2;
        while (idx < argc) {
            if (std::string(argv[idx]) == "--pretty-print") {
                need_print_ = true;
            } else 
            if (std::string(argv[idx]) == "--no-print-preprocess") {
                need_print_preprocess_ = false;
            } else {
                throw std::runtime_error("Unknown argument: " + std::string(argv[idx]));
            }
            idx++;
        }

        return true;
    }
    catch (const std::exception& e) {
        error_output_ << RED << "[Argument parsing failed] " << e.what() << RESET << std::endl;
        return false;
    }

}

const std::string& Argument_Parser::get_parse_result() const {
    return parse_result_;
}

const bool& Argument_Parser::get_need_print() const {
    return need_print_;
}


const bool& Argument_Parser::get_need_print_preprocess() const {
    return need_print_preprocess_;
}





