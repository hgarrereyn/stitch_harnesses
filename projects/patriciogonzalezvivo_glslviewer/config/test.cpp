#include <iostream>
#include <string>
#include <vector>
#include <chrono>

#include "tools/files.h"
#include "tools/command.h"
#include "tools/tracker.h"

int main() {
    WatchFile wf; wf.path = "shader.frag"; wf.type = FRAG_SHADER; wf.lastChange = 0; wf.vFlip = false;
    Command cmd{"print", [](const std::string& s){ (void)s; return true; }, "print <msg>", "Print a message", true};
    StatTrack track; track.stack = "demo"; track.durationAverage = 1.0;

    std::cout << "WatchFile: " << wf.path << ", type=" << wf.type << "\n";
    std::cout << "Command: " << cmd.trigger << ", desc=" << cmd.description << "\n";
    std::cout << "Track avg: " << track.durationAverage << " ms\n";
    return 0;
}
