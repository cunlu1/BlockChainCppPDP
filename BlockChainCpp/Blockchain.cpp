#include <stdio.h>
#include <ctime>
#include <vector>
#include <string>
#include "Block.h"
#include "Blockchain.h"


// Blockchain Constructor
Blockchain::Blockchain()
{
    Block genesis = createGenesisBlock();
    chain.push_back(genesis);
}

// Public Chain Getter
std::vector<Block> Blockchain::getChain() {
    return chain;
}

// Genesis Block olu�turma
Block Blockchain::createGenesisBlock()
{
    // Ge�erli Saati Al
    std::time_t current;

    // �lk ��lem Verilerini Ayarlayal�m
    TransactionData d(0, "Genesis", "Genesis", time(&current));

    // Return Genesis Block
    Block genesis(0, d, 0);
    return genesis;
}

//��lem verilerinin manip�lasyonunu g�stermek i�in burada yaln�zca i�aret�iye ihtiyac�m�z var
Block* Blockchain::getLatestBlock()
{
    return &chain.back();
}

void Blockchain::addBlock(TransactionData d)
{
    int index = (int)chain.size();
    std::size_t previousHash = (int)chain.size() > 0 ? getLatestBlock()->getHash() : 0;
    Block newBlock(index, d, previousHash);
    chain.push_back(newBlock);
}

bool Blockchain::isChainValid()
{
    std::vector<Block>::iterator it;

    for (it = chain.begin(); it != chain.end(); ++it)
    {
        Block currentBlock = *it;
        if (!currentBlock.isHashValid())
        {
            return false;
        }

        // Bunun ilk ��e olup olmad���n� kontrol edelim
        if (it != chain.begin())
        {
            Block previousBlock = *(it - 1);
            if (currentBlock.getPreviousHash() != previousBlock.getHash())
            {
                return false;
            }
        }
    }

    return true;
}

void Blockchain::printChain() {
    std::vector<Block>::iterator it;

    for (it = chain.begin(); it != chain.end(); ++it)
    {
        Block currentBlock = *it;
        printf("\n\nBlock ===================================");
        printf("\nIndex: %d", currentBlock.getIndex());
        printf("\nAmount: %f", currentBlock.data.amount);
        printf("\nSenderKey: %s", currentBlock.data.senderKey.c_str());
        printf("\nReceiverKey: %s", currentBlock.data.receiverKey.c_str());
        printf("\nTimestamp: %ld", currentBlock.data.timestamp);
        printf("\nHash: %zu", currentBlock.getHash());
        printf("\nPrevious Hash: %zu", currentBlock.getPreviousHash());
        printf("\nIs Block Valid?: %d", currentBlock.isHashValid());
    }
}
