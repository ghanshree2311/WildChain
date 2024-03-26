#ifndef __C_CHAIN_INCLUDED__
#define __C_CHAIN_INCLUDED__
#include "Block.h"
#include <vector>

namespace Blockchain
{
    class Chain{
        private:
            std::vector<block> chain; // List of blocks
            block* CurrentBlock;      // Pointer to current block
            int difficulty;           // Difficulty - PoW
        public:
            Chain(int difficulty);    // Constructor
            void appendToCurrentBlock(Data* data); 
            void nextBlock();         // Create a new block
            block* getCurrentBlock(); // pointer to the Current Block
    };

}
#endif