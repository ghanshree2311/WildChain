#include "Chain.h"
#include "Block.h"
using namespace Blockchain;

Chain::Chain(int difficulty){
    difficulty = difficulty;
    chain.push_back(block(0));  //genesis block
    CurrentBlock = &chain[0];
}

void Chain::appendToCurrentBlock(Data* data){
    CurrentBlock ->appendData(data);
}

void Chain::nextBlock(){
    block block(CurrentBlock);
    block.mine(difficulty);
    chain.push_back(block);
    CurrentBlock = &chain.back();
}

block* Chain::getCurrentBlock(){
    return CurrentBlock;
}