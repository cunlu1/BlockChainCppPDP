#include <iostream>
#include <ctime>
#include <vector>
#include "TransactionData.h"
#include "Block.h"
#include "Blockchain.h"

using namespace std;

int main()
{
    // BlockChain Ba�lang�c�.
    Blockchain cengizCoin;

    // �lk blocktaki veri.
    time_t data1Time;
    TransactionData data1(1.5, "Cengiz", "Emre", time(&data1Time));
    cengizCoin.addBlock(data1);

    time_t data2Time;
    TransactionData data2(0.2233, "Selman", "Hizal", time(&data2Time));
    cengizCoin.addBlock(data2);

    // Block zincirini ekrana basal�m.
    cengizCoin.printChain();

    // Hala aktif mi kontrol�.
    printf("\nIs valid? %d\n", cengizCoin.isChainValid());


    Block* hackBlock = cengizCoin.getLatestBlock();
    hackBlock->data.amount = 10000; 
    hackBlock->data.receiverKey = "receiverKey"; 

    // Veriyi ekrana basal�m.
    cengizCoin.printChain();

    // Aktiflik kontrol�
    printf("\nIs valid? %d\n", cengizCoin.isChainValid());

    return 0;
}