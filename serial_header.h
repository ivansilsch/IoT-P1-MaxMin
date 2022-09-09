#include <cstdint>
#include <cstring>

class serial_class {
  private:
    bool is_unsigned = false;
  public:
    int get_data();
    void post_data(int bits);
    uint64_t ugetmax(int bits);
    int64_t getmax(int bits);
    int64_t getmin(int bits);
    int clear_type(char *char_arr);
  private:
    int clear_type__(char *char_arr, int index);
};


int serial_class::clear_type__(char *char_bytes, int index) {
  // Dependiendo de la posicion de index, se extrae el entero 
  // del tipo de dato introducido.

  char byte2[2];
  if (char_bytes[index+1]=='_' && char_bytes[index+2]=='t') {
      return char_bytes[index] - '0';
  } else if (char_bytes[index+2]=='_' && char_bytes[index+3]=='t') {
      byte2[0] = char_bytes[index];
      byte2[1] = char_bytes[index+1];
      return atoi(byte2);
  }
  return 0;
}


int serial_class::clear_type(char *char_bytes) {
  // Prepara el entero a ser extraido del array, dependiendo 
  // del tipo de dato con signo o sin signo.

  if (strstr(char_bytes, "uint")) { is_unsigned = true; }
  else if (strstr(char_bytes, "int")) { is_unsigned = false; }

  if (is_unsigned) {
      return clear_type__(char_bytes, 4);
  } else {
      return clear_type__(char_bytes, 3);
  }
  return 0;
}


int serial_class::get_data() { 
  // Se obtienen los datos entrantes del puerto serial,
  // y se guardan como un array de caracteres.

    char char_bytes[8];
    char in_byte;
    int i = 0;
    while (Serial.available()) {
        in_byte = Serial.read();
        char_bytes[i] = in_byte;
        i++;
    }
    return clear_type(char_bytes);
}


void serial_class::post_data(int bits) {
  // Imprime los resultados.

    Serial.println("________________________");
    if (is_unsigned) {
        Serial.print(bits, DEC);
        Serial.println(" Bits sin signo");
        Serial.print("max: ");
        Serial.println(ugetmax(bits), DEC);
        Serial.println("min: 0");
    } else {
        Serial.print(bits, DEC);
        Serial.println(" Bits con signo");
        Serial.print("max: ");
        Serial.println(getmax(bits), DEC);
        Serial.print("min: ");
        Serial.println(getmin(bits), DEC);
    }
    Serial.println("________________________");
    Serial.print("> ");
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
