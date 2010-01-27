void main() {
  PORTA = 0;
  TRISA = 0;

 while(1) {
    PORTA =  ~PORTA;
    Delay_ms(1000);
  }
}
