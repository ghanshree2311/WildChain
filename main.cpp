#include <iostream>
#include <cstring>
#include "Chain.h"
#include "Block.h"
using namespace std;
using namespace Blockchain;

int main(){
    cout<<"Hello";
    Chain AChain(1);
    cout<< "Chain initialized....\n";
    block* genesis = AChain.getCurrentBlock();

    Data details;
    details.key = 1;
    memcpy(details.data_hash, 0, SHA256_DIGEST_LENGTH);

    AChain.appendToCurrentBlock(&details);

    cout<< "Details added to Blockchain...\n";
    AChain.nextBlock();
    cout<<"Next Block Mined....\n";

    details.key = 2;
    memset(details.data_hash, 0, SHA256_DIGEST_LENGTH);
    AChain.appendToCurrentBlock(&details);

    AChain.nextBlock();
    cout<<"Previous Hash: "<< AChain.getCurrentBlock()->getpreviousblock()->getHashstr();

    return 0;

}