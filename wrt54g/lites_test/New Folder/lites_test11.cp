#line 1 "C:/Documents and Settings/ben/Desktop/lites_test/New Folder/lites_test11.c"
void main() {
 PORTC = 0;
 TRISC = 0;

 while(1) {
 PORTC = ~PORTC;
 Delay_ms(1000);
 }
}
