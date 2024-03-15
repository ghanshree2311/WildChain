#include "Block.h"
#include <iostream>
#include <string.h>

using namespace Blockchain;

block::block(block *prevBlock)
{
    previous_block = prevBlock;
    next_update = NULL;
    if (prevBlock)
    {
        memcpy(previousHash, prevBlock->gethash(), SHA256_DIGEST_LENGTH);
        // previousHash = prevBlock->gethash();
    }
    else
    {
        memcpy(previousHash, 0, SHA256_DIGEST_LENGTH); // Genesis block-> no previous block -> previous hash=0
    }

    timestamp_currBlock = time(0); // current date and time.
    details->key = 2198765;
    memcpy(details->data_hash, 0, SHA256_DIGEST_LENGTH);
    nonce = 0;
    calculateHash();
}

void block::calculateHash()
{
    uint32_t size_payload = (SHA256_DIGEST_LENGTH * sizeof(uint8_t)) + sizeof(time_t) + sizeof(Data) + sizeof(uint32_t);
    // payload -> input to sha256-> prev. hash, timestamp, data, nonce
    uint8_t *buf = new uint8_t[size_payload];
    // initialize a pointer of the size of the payload
    uint8_t *ptr = buf;
    // a ptr. to the beginning of the buffer

    // Data concatenation
    memcpy(ptr, previousHash, SHA256_DIGEST_LENGTH * sizeof(uint8_t));
    ptr += SHA256_DIGEST_LENGTH * sizeof(uint8_t);
    memcpy(ptr, &timestamp_currBlock, sizeof(time_t));
    ptr += sizeof(time_t);
    if (sizeof(Data) != 0)
    {
        memcpy(ptr, &details, sizeof(Data));
        ptr += sizeof(Data);
    }
    memcpy(ptr, &nonce, sizeof(uint32_t));
    ptr += sizeof(uint32_t);

    // hashing
    SHA256_CTX sha256;                         // declaring SHA256_CTX structure
    SHA256_Init(&sha256);                      // Initializing
    SHA256_Update(&sha256, buf, size_payload); // Repeatedly called with chunks of message to be hashed
    SHA256_Final(Hash, &sha256);               // places the message digest- hashed value to currentHash and erases the SHA256_CTX
}
uint8_t *block::gethash()
{
    return Hash;
}
std::string block::getHashstr()
{
    std::string Hashstr;
}
block *block::getpreviousblock()
{
    return previous_block;
}
void block::appendData(Data *data)
{
    uint8_t *newData = new uint8_t[sizeof(details) + sizeof(data)];
    uint8_t *ptr = newData;

    if (&details != 0)
    {
        memcpy(ptr, &details, sizeof(details));
        ptr += sizeof(details);
        delete[] &details;
    }
    memcpy(ptr, data, sizeof(data));
    details = data;
}

// Mining Block

bool block::isdifficulty(int difficulty)
{
    for (uint32_t n = 0; n < difficulty; n++)
    {
        if (Hash[n] != 0)
        {
            return false;
        }
    }
    return true;
}
void block::mine(int difficulty)
{
    while (!isdifficulty(difficulty))
    {
        nonce++;
        calculateHash();
    }
}

uint32_t block::getnonce()
{
    return nonce;
}
