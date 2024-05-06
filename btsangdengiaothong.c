#include <16f887.h>
#fuses HS
#use delay(clock = 20M)

#define  SER PIN_D0
#define  SCK PIN_D1
#define  RCK PIN_D2

#define X1_X2 0X11
#define V1_D2 0X14
#define D1_X2 0X0A
#define D1_V2 0X22

#define TG_DO 29
#define TG_XANH 26
#define TG_VANG 2

unsigned int8 DEM1, DEM2;
unsigned int8 LED4, LED3, LED2, LED1;
unsigned int8 MA7D[10]={0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};

void XUAT_1BYTE(unsigned int8 BYTEXUAT) {
    unsigned int8 I;
    for (I = 0; I < 8; I++) {
        output_bit(SER, (BYTEXUAT & 0x80) >> 7);
        output_low(SCK);
        output_high(SCK);
        BYTEXUAT <<= 1;
    }
}

void XUAT_4LED_7DOAN(unsigned int8 LED4, unsigned int8 LED3, unsigned int8 LED2, unsigned int8 LED1) {
    XUAT_1BYTE(LED4);
    XUAT_1BYTE(LED3);
    XUAT_1BYTE(LED2);
    XUAT_1BYTE(LED1);
    output_low(RCK);
    output_high(RCK);
}

void main() {
    set_tris_d(0x00);
    set_tris_c(0x00);

    while (true) {
        // TR?NG TH핱 X1_D2
        output_c(X1_X2);
        DEM1 = TG_XANH;
        DEM2 = TG_DO;
        do {
            XUAT_4LED_7DOAN(MA7D[DEM1 / 10], MA7D[DEM1 % 10], MA7D[DEM2 / 10], MA7D[DEM2 % 10]);
            delay_ms(1000);
            DEM1--;
            DEM2--;
        } while (DEM1 != 255);

        // TR?NG TH핱 V1_D2
        output_c(V1_D2);
        DEM1 = TG_VANG;
        do {
            XUAT_4LED_7DOAN(MA7D[DEM1 / 10], MA7D[DEM1 % 10], MA7D[DEM2 / 10], MA7D[DEM2 % 10]);
            delay_ms(1000);
            DEM1--;
            DEM2--;
        } while (DEM1 != 255);

        // TR?NG TH핱 D1_X2
        output_c(D1_X2);
        DEM1 = TG_DO;
        DEM2 = TG_XANH;
        do {
            XUAT_4LED_7DOAN(MA7D[DEM1 / 10], MA7D[DEM1 % 10], MA7D[DEM2 / 10], MA7D[DEM2 % 10]);
            delay_ms(1000);
            DEM1--;
            DEM2--;
        } while (DEM2 != 255);

        // TR?NG TH핱 D1_V2
        output_c(D1_V2);
        DEM2 = TG_VANG;
        do {
            XUAT_4LED_7DOAN(MA7D[DEM1 / 10], MA7D[DEM1 % 10], MA7D[DEM2 / 10], MA7D[DEM2 % 10]);
            delay_ms(1000);
            DEM1--;
            DEM2--;
        } while (DEM1 != 255);
    }
}
