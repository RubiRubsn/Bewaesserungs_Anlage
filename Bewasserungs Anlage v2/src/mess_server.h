#include<arduino.h>
#include"Kalibrierung.h"

class mess_server{
    private:
    public:
    int brerechnung_proz(Kalibrierung& kalibrierung, kali_dat& dat);
    void server_init(Kalibrierung& kalibrierung, kali_dat& dat);
};
