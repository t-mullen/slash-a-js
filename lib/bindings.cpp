#include <emscripten/bind.h>
#include <iostream>
#include <fstream>
#include <string>
#include "slash-a/lib/SlashA.hpp"

using namespace emscripten;

static bool lastFailed = false;
static bool DIS_inserted = false;
static SlashA::InstructionSet iset(32768); // initializes the Default Instruction Set with 32768 numeric instructions

std::vector<double>
runByteCode(SlashA::ByteCode bc,
            std::vector<double> input,
            const unsigned DSize,
            const unsigned LSize,
            long randseed,
            long max_rtime,
            int max_loop_depth) {
    std::vector<double> output;
    SlashA::MemCore memcore(DSize, // length of the data tape D[]
                LSize, // length of the label tape L[]
                input, // input buffer (will use keyboard if empty)
                output); // output buffer
    if (!DIS_inserted) {
        iset.insert_DIS_full();
        DIS_inserted = true;
    }
    bool failed = SlashA::runByteCode(iset, // instruction set pointer
                            memcore,          // memory core pointer
                            bc,               // ByteCoded program to be run (pointer)
                            randseed,         // random seed for random number instructions
                            max_rtime,        // max run time in seconds (0 for no limit)
                            max_loop_depth);  // max loop depth
    lastFailed = failed;
    return output;
}

SlashA::ByteCode
source2ByteCode(std::string src) {
    if (!DIS_inserted) {
        iset.insert_DIS_full();
        DIS_inserted = true;
    }
    SlashA::ByteCode bc;
    SlashA::source2ByteCode(src, bc, iset);
    return bc;
}

bool
checkFailed() {
    return lastFailed;
}

EMSCRIPTEN_BINDINGS(module) {
    function("runByteCode", &runByteCode);
    function("source2ByteCode", &source2ByteCode);
    function("checkFailed", &checkFailed);
}

EMSCRIPTEN_BINDINGS(stl_wrappers) {
    register_vector<double>("VectorDouble");
    register_vector<unsigned>("ByteCode");
}