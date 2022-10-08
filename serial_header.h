
class serial_class {
  public:
    bool get_data(void);
    void post_data(void);
    void clean(void);
    uint64_t ugetmax(int bits);
    int64_t getmax(int bits);
    int64_t getmin(int bits);
    void print_unsigned(int bits);
    void print_signed(int bits);
};


#define BUFFER_SIZE 9

char serial_input[BUFFER_SIZE]; 
char character;
int i;

bool serial_class::get_data(void) {
  character = (char) Serial.read();
  if (character != '\n') {
    serial_input[i] = character;
    i++;
  } else {
    return true;
  }
  return false;
}


// Limpia el mensaje para poder ingresar uno nuevo
void serial_class::clean(void) {
  for (int j=0; j<BUFFER_SIZE; j++) {
    serial_input[j] = 0;
  }
  i=0;
}


// Formula para obtener el maximo de un entero sin signo
uint64_t serial_class::ugetmax(int bits) {
  return pow(2, bits) - 1;
}

// Formula para obtener el maximo de un entero con signo
int64_t serial_class::getmax(int bits) {
  return pow(2, bits - 1) - 1;
}

// Formula para obtener el minimo de un entero con signo
int64_t serial_class::getmin(int bits) {
  return - pow(2, bits - 1);
}


void serial_class::print_unsigned(int bits) {
  Serial.println("----------------");
  Serial.print(bits, DEC);
  Serial.println(" Bits sin signo");
  Serial.print("max: ");
  Serial.println(ugetmax(bits), DEC);
  Serial.println("min: 0");
}


void serial_class::print_signed(int bits) {
  Serial.println("----------------");
  Serial.print(bits, DEC);
  Serial.println(" Bits con signo");
  Serial.print("max: ");
  Serial.println(getmax(bits), DEC);
  Serial.print("min: ");
  Serial.println(getmin(bits), DEC);  
}


// Imprime los resultados.
void serial_class::post_data(void) {
  // strcpm compara serial_input con la cadena de caracteres
  if ( strcmp(serial_input, "uint4_t") == 0 ) {
    print_unsigned(4);
  } else if ( strcmp(serial_input, "uint8_t") == 0 ) {
    print_unsigned(8);
  } else if ( strcmp(serial_input, "uint16_t") == 0 ) {
    print_unsigned(16);
  } else if ( strcmp(serial_input, "uint32_t") == 0 ) {
    print_unsigned(32);
  } else if ( strcmp(serial_input, "uint64_t") == 0 ) {
    print_unsigned(64);
  } else if ( strcmp(serial_input, "int4_t") == 0 ) {
    print_signed(4);
  } else if ( strcmp(serial_input, "int8_t") == 0 ) {
    print_signed(8);
  } else if ( strcmp(serial_input, "int16_t") == 0 ) {
    print_signed(16);
  } else if ( strcmp(serial_input, "int32_t") == 0 ) {
    print_signed(32);
  } else if ( strcmp(serial_input, "int64_t") == 0 ) {
    print_signed(64);
  }
  clean();
}