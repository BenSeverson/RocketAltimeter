#line 1 "C:/Documents and Settings/ben/Desktop/lites_test/lites_test.c"
void main() {
 PORTA = 0;
 TRISA = 0;

 while(1) {
 PORTA = ~PORTA;
 Delay_ms(1000);
 }
}
