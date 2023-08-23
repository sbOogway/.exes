#include <iostream>
#include <cstdlib>
#include <string>

#include "/home/uomosucco/c_headers/utils.hpp"

using str = std::string;

int main(int argc, char* argv[])
{    
    str emoji   = "✅";
    str color   = "green";
    str failure = "❌";
    str basic_log = "echo $(ansi_wrapper -c $WRAP_COLOR [)$(ansi_wrapper -c $CLOCK_COLOR $(date $FORMAT))$(ansi_wrapper -c $WRAP_COLOR ]) [$(ansi_wrapper -c magenta -g swg_tmr)] [$(ansi_wrapper -c red -g -u \"";

    str command = "";
    for (int i=1; i < argc -1; i++) {
        command += argv[i] + str(" ");
    }
    command += argv[argc-1];

    str entry_cmd = str(basic_log) + str(command.c_str()) + str("\")] ⏲️ ");
    system(entry_cmd.c_str());

    str start = utils::capture_stdout("date +%s%N | cut -b1-13", 2);
    system(command.c_str());
    str end   = utils::capture_stdout("date +%s%N | cut -b1-13", 2);

    long _start = std::stol(start);
    long _stop  = std::stol(end);

    auto duration = _stop - _start;
    double seconds = static_cast<double>(duration) / 1000.0;
    std::stringstream ss;
    ss << std::fixed << std::setprecision(3) << seconds;

    // system("echo $?");

    str exit_code  = utils::capture_stdout("echo -n $?", 2);
    int _exit_code = std::stoi(exit_code);
    if (_exit_code != 0) {
        emoji = failure;
        color = "red";
    }  
    str exit_cmd = str(basic_log) + str(command.c_str()) + str("\")] " + emoji + str(" [$(ansi_wrapper -c yellow ") + ss.str() + str(")] ") + str(" [$(ansi_wrapper -c ") + color + str(" ") + exit_code + str(")]"));
    system(exit_cmd.c_str());

    return EXIT_SUCCESS;
}