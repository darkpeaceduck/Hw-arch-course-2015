#define VGA_START_ADDRESS 0xb8000
#define SCREEN_SIZE 20*85
#define PIXEL_MODE 15

const char * string = "Hello, world!";
char * const vga = (char *) (VGA_START_ADDRESS);

void clean_screen(){  
  int i = 0;
  for(i = 0; i < 2 * SCREEN_SIZE ; i++) {
    vga[i] = 0;
  }
}

void print_phrase(){
  int i = 0;
  for(i = 0; string[i] != '\0'; i++) {
    vga[2*i] = string[i];
    vga[2*i+1] = PIXEL_MODE;
  }
}

void main(){
  clean_screen();
  print_phrase();
  while(1){
  }
  
  return;
}