#include <iostream>
#include <openssl/sha.h>
#include <ctime>
#include<string>
using namespace std;
class block{
    private:
        struct Data{
            int key;
            uint8_t data_hash[SHA256_DIGEST_LENGTH];
        };
    private:
        uint8_t current_Hash[SHA256_DIGEST_LENGTH]; //byte array storing Hash of current block
        uint8_t previousHash[SHA256_DIGEST_LENGTH]; //byte array-> Hash of previous block
        block* previous_block; // prev. pointer -> pointer to previous block
        block* next_update; // pointer to the block containing updated value of this current block
        struct Data details;// Data-> encrypted key, hash of data
        time_t timestamp_currBlock; // timestamp of current block
        uint8_t nonce; // nonce value to match pattern of hash

    public:    
    block(block* prevBlock);    // constructor
    void calculateHash();       // calculate hash of data
    uint8_t* gethash();         // get hash of current block -> current_hash
    std::string getHashstr();   // current_hash in string form
    block* getpreviousblock();  // get pointer of the previous block
    void appendData(Data* data); // append data-> details

    // Add functions for mining block - PoW

};