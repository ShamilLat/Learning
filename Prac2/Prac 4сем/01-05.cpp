#include <iostream>
#include <cstdint>

enum
{
    OKT_COUNT = 17,
    HEX_PLUS = 0x100
};

int main()
{
    uint32_t okt, okt_count = 0, num = 0, okt_number = 0;
    
    while (std::cin >> std::hex >> okt) {
        if (okt_count % OKT_COUNT != 0) {
            num *= HEX_PLUS;
            num += okt;
            okt_number++;
            if (okt_number == 4) {
                std::cout << num << std::endl;
                num = 0;
                okt_number = 0;
            }
        }
        okt_count++;
    }
}