/*��renci dolmu�a biner cihaz�n ��renci butonuna basar ve ��renci butonuna 
ba�l� led yanar ve �of�r�n �n�ndeki LCD de 13.Ogrenci(bastaki 13. kutuya para
atan yolcu say�s�d�r �imdilik rastgele bir yolcu s�ras� verdim) yazar ve at�lan
para miktar� anl�k olarak ekranda g�r�n�r bu arada 1.5 Tl kutuya at�lana kadar
Kutunun �zerindeki ��renci ledi yanmaya devam eder, 1.5 TL veya �st�
bir miktar at�ld���nda led s�ner ve yolcu para �st�n� hazneden al�p 
yerine ge�ebilir yerine ge�ebilir...*/
//---------------------------------------------------------------------------
#include <16F877A.h>

#FUSES XT
#FUSES NOWDT
#FUSES NOPROTECT
#FUSES NOBROWNOUT
#FUSES NOLVP
#FUSES NOPUT
#FUSES NOWRT
#FUSES NODEBUG
#FUSES NOCPD

#use delay(crystal=4000000)

#define use_portb_lcd TRUE //LCD B portuna bagli
#include <lcd.c>

#define CNY1 RA0   //CNY70 ba�lant� pinleri
#define CNY2 RA1
#define CNY3 RA2
#define CNY4 RA3
#define CNY5 RA4
#define CNY6 RA5


// Degisken tanimlamalari
int Tam=0, Ogrenci=0;
int CNY1=0, CNY2=0, CNY3=0, CNY4=0, CNY5=0, CNY6=0;
int TL=0, KRS=0 ;
int Tutar=0 ;
int Sira=0 ; // para atan yolcu sira numarasi
int ekranaBas = 0;
int iade=0, iade50KRS=0, iade25KRS=0, iade10KRS=0, iade5KRS=0, iade1KRS=0;

 void parasay ( ) //Para sayma i�lemi
 {
   if(input(pin_A0))
      {
      while (input(pin_A0));
      CNY1++;
      ekranaBas = 1;
      }
   if(input(pin_A1))
      {
      while (input(pin_A1));
      CNY2++;
      ekranaBas = 1;
      }
   if(input(pin_A2))
      {
      while (input(pin_A2));
      CNY3++;
      ekranaBas = 1;
      }
   if(input(pin_A3))
      {
      while (input(pin_A3));
      CNY4++;
      ekranaBas = 1;
      }
   if(input(pin_A4))
      {
      while (input(pin_A4));
      CNY5++;
      ekranaBas = 1;
      }
   if(input(pin_A5))
      {
      while (input(pin_A5));
      CNY6++;
      ekranaBas = 1;
      }
 }

void main ( )
{
 setup_psp(PSP_DISABLED); // PSP birimi devre d���
 setup_spi(SPI_SS_DISABLED); // SPI birimi devre d���
 setup_timer_1(T1_DISABLED); // T1 zamanlay�c�s� devre d���
 setup_timer_2(T2_DISABLED,0,1); // T2 zamanlay�c�s� devre d���
 setup_adc_ports(NO_ANALOGS); // ANALOG giri� yok
 setup_adc(ADC_OFF); // ADC birimi devre d���
 setup_CCP1(CCP_OFF); // CCP1 birimi devre d���
 setup_CCP2(CCP_OFF); // CCP2 birimi devre d���
 
         output_low(pin_C3); //Anlamad���m bir �ekilde smilasyon esnas�nda RC3
         output_low(pin_C5); //ve RC5 c�k�s� aktif oldugu icin eklemek zorunda kald�m
         lcd_init();
         printf (lcd_putc, "HOSGELDINIZ");
         printf (lcd_putc, "\nSistem Calisiyor");
 
while (TRUE) //Ana d�ng�
    {
      
  ///////////////////////////////////////////////////////////////////////       
      if(input(pin_D0)) // Tam butonuna bas�l�rsa
         {
          while(input(pin_D0));  //Cekene kadar bekle
          output_high(pin_C0);   //Tam �s�g�n� yak
          output_low(pin_C1);    //M��terinin fikir de�i�tirmesine kar�� yan�yorsa Ogrenci isigini kapat
          Tam=1;
          Sira++;
          Tutar=0;
          TL = 0;
          KRS =0;
          CNY1 = 0;
          CNY2 = 0;
          CNY3 = 0;
          CNY4 = 0;
          CNY5 = 0;
          CNY6 = 0;
          ekranaBas = 1;
         }
      if(Tam==1)
        {
         parasay();
         Tutar= CNY1*100 + CNY2*50 + CNY3*25 + CNY4*10 + CNY5*5 + CNY6*1;
         TL=Tutar/100;
         KRS=Tutar%100;
         
         if(ekranaBas){
            printf (lcd_putc, "\f%d.Tam", Sira);
            printf (lcd_putc, "\n%dTL %dKRS", TL , KRS);
            ekranaBas = 0;
         } 
            if(Tutar>=175)
               {
               output_low(pin_C0);
               printf (lcd_putc, "\fUCRET ALINDI");
               printf (lcd_putc, "\nTESEKKURLER");
               Tam=0;
               iade = Tutar - 175;
               iade50KRS = iade / 50;
               iade25KRS = (iade - iade50KRS*50) / 25;
               iade10KRS = (iade - iade50KRS*50 - iade25KRS*25) / 10;
               iade5KRS  = (iade - iade50KRS*50 - iade25KRS*25 - iade10KRS*10) / 5;
               iade1KRS  = (iade - iade50KRS*50 - iade25KRS*25 - iade10KRS*10 - iade5KRS*5)  / 1;
                  if(iade50KRS>0) //50 Kurus para ustunu iade eder
                     {
                        while(iade50KRS > 0)  //50 Kurus para ustunu iade eder
                        {
                           output_high(pin_C2);
                           delay_ms(2000);
                           output_low(pin_C2);
                           output_high(pin_D2);
                           delay_ms(2200);
                           output_low(pin_D2);
                           iade50KRS--;
                        }
                     }
                  if(iade25KRS>0)// 25 Kurus para ustunu iade eder
                     {
                        while(iade25KRS > 0)
                        {
                           output_high(pin_C3);
                           delay_ms(2000);
                           output_low(pin_C3);
                           output_high(pin_D3);
                           delay_ms(2200);
                           output_low(pin_D3);
                           iade25KRS--;
                        }//50 kurus d�s�nda para �st� vermeye ihtiyac�m�z yok
                     }
                  if(iade10KRS>0)// 10 Kurus para ustunu iade eder
                     {
                        while(iade10KRS > 0)
                        {
                           output_high(pin_C4);
                           delay_ms(200);
                           output_low(pin_C4);
                           output_high(pin_D4);
                           delay_ms(220);
                           output_low(pin_D4);
                           iade10KRS--;
                        }
                     }
                  if(iade5KRS>0)// 5 Kurus para ustunu iade eder
                     {
                        while(iade5KRS > 0)
                        {
                           output_high(pin_C5);
                           delay_ms(200);
                           output_low(pin_C5);
                           output_high(pin_D5);
                           delay_ms(220);
                           output_low(pin_D5);
                           iade5KRS--;
                        }
                     }
                  if(iade1KRS>0)// 1 Kurus para ustunu iade eder
                     {
                        while(iade1KRS > 0)
                        {
                           output_high(pin_C5);
                           delay_ms(200);
                           output_low(pin_C5);
                           output_high(pin_D5);
                           delay_ms(220);
                           output_low(pin_D5);
                           iade1KRS--;
                        }//Asl�nda ogrencide 25 kurus d�s�nda para �st� vermeye ihtiyac�m�z yok yinede ekledim
                     }
               }
        }
  /////////////////////////////////////////////////////////////////////////////      
      if(input(pin_D1)) // Ogrenci butonuna bas�l�rsa Tam �s�g�n� yak
         {
          while(input(pin_D1));
          output_high(pin_C1);
          output_low(pin_C0);
          Ogrenci=1;
          Sira++;
          Tutar=0;
          TL = 0;
          KRS =0;
          CNY1 = 0;
          CNY2 = 0;
          CNY3 = 0;
          CNY4 = 0;
          CNY5 = 0;
          CNY6 = 0;
          ekranaBas = 1;
         }
      if(Ogrenci==1)
        {
         parasay ();
         Tutar= CNY1*100 + CNY2*50 + CNY3*25 + CNY4*10 + CNY5*5 + CNY6*1;
         TL=Tutar/100;
         KRS=Tutar%100;         
         
         if(ekranaBas)
         {
            printf (lcd_putc, "\f%d.Ogrenci", Sira);
            printf (lcd_putc, "\n%dTL %dKRS", TL , KRS);
            ekranaBas = 0;
         }
            if(Tutar>=150)
               {
               output_low(pin_C1);
               printf (lcd_putc, "\fUCRET ALINDI");
               printf (lcd_putc, "\nTESEKKURLER");
               Ogrenci = 0;
               iade = Tutar - 150;
               iade50KRS = iade / 50;
               iade25KRS = (iade - iade50KRS*50) / 25;
               iade10KRS = (iade - iade50KRS*50 - iade25KRS*25) / 10;
               iade5KRS  = (iade - iade50KRS*50 - iade25KRS*25 - iade10KRS*10) / 5;
               iade1KRS  = (iade - iade50KRS*50 - iade25KRS*25 - iade10KRS*10 - iade5KRS*5)  / 1;
               
                  if(iade50KRS>0) //50 Kurus para ustunu iade eder
                     {
                        while(iade50KRS > 0)  //50 Kurus para ustunu iade eder
                        {
                           output_high(pin_C2);
                           delay_ms(2000);
                           output_low(pin_C2);
                           output_high(pin_D2);
                           delay_ms(2200);
                           output_low(pin_D2);
                           iade50KRS--;
                        }
                     }
                  if(iade25KRS>0)// 25 Kurus para ustunu iade eder
                     {
                        while(iade25KRS > 0)
                        {
                           output_high(pin_C3);
                           delay_ms(2000);
                           output_low(pin_C3);
                           output_high(pin_D3);
                           delay_ms(2200);
                           output_low(pin_D3);
                           iade25KRS--;
                        }//50 kurus d�s�nda para �st� vermeye ihtiyac�m�z yok
                     }
                  if(iade10KRS>0)// 10 Kurus para ustunu iade eder
                     {
                        while(iade10KRS > 0)
                        {
                           output_high(pin_C4);
                           delay_ms(200);
                           output_low(pin_C4);
                           output_high(pin_D4);
                           delay_ms(220);
                           output_low(pin_D4);
                           iade10KRS--;
                        }
                     }
                  if(iade5KRS>0)// 5 Kurus para ustunu iade eder
                     {
                        while(iade5KRS > 0)
                        {
                           output_high(pin_C5);
                           delay_ms(200);
                           output_low(pin_C5);
                           output_high(pin_D5);
                           delay_ms(220);
                           output_low(pin_D5);
                           iade5KRS--;
                        }
                     }
                  if(iade1KRS>0)// 1 Kurus para ustunu iade eder
                     {
                        while(iade1KRS > 0)
                        {
                           output_high(pin_C5);
                           delay_ms(200);
                           output_low(pin_C5);
                           output_high(pin_D5);
                           delay_ms(220);
                           output_low(pin_D5);
                           iade1KRS--;
                        }//Asl�nda ogrencide 50 kurus d�s�nda para �st� vermeye ihtiyac�m�z yok yinede ekledim
                     }
               }
        }
 
   }
//////////////////////////////////////////////////////////////////////////// 
}   // Program sonu
