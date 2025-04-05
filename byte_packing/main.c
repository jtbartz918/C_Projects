#include <stdio.h>

// Define a struct with bit fields
struct PackedBits {
    unsigned int bit1 : 1;  // 1 bit
    unsigned int bit2 : 1;  // 1 bit
    unsigned int bit3 : 1;  // 1 bit
    unsigned int bit4 : 1;  // 1 bit
    unsigned int bit5 : 1;  // 1 bit
    unsigned int bit6 : 1;  // 1 bit
    unsigned int bit7 : 1;  // 1 bit
    unsigned int bit8 : 1;  // 1 bit
};

/*Helper function to get user input of 8 bits to form a byte*/
unsigned int* get_bits(){
    static unsigned int bits[8];
  
    int i;
    for(i = 0; i < 8; i++){
        printf("Enter a 1 or 0 for bit %d: ",i);
        scanf("%d", &bits[i]);
        printf("You entered: %d\n", bits[i]);
    }
    return bits;
    
}

void pack(){

    unsigned int* returned_bits = get_bits();
    // Initialize the struct with values
    struct PackedBits bits = {returned_bits[0], returned_bits[1], returned_bits[2], returned_bits[3], returned_bits[4], returned_bits[5], returned_bits[6], returned_bits[7]};  // 8 bits all 1's = 255 (binary 11111111)

    // Pack the struct into a byte
    unsigned char packedByte = 0;

    packedByte |= bits.bit1 << 0;   // Shift bit1 to the first position
    packedByte |= bits.bit2 << 1;   // Shift bit2 to the second position
    packedByte |= bits.bit3 << 2;   // Shift bit3 to the third position
    packedByte |= bits.bit4 << 3;   // Shift bit4 to the fourth position
    packedByte |= bits.bit5 << 4;   // Shift bit5 to the fifth position
    packedByte |= bits.bit6 << 5;   // Shift bit6 to the sixth position
    packedByte |= bits.bit7 << 6;   // Shift bit7 to the seventh position
    packedByte |= bits.bit8 << 7;   // Shift bit8 to the eighth position

    // Print the packed byte
    printf("Packed byte as hex: 0x%02X\n", packedByte);  // Print as hexadecimal
    printf("Packed byte as decimal: %d\n", packedByte);  // Print as decimal
    printf("Packed byte (binary): ");
    for (int i = 7; i >= 0; --i) {
        printf("%d", (packedByte >> i) & 1);
    }
    printf("\n");
}

int main() {
    pack();
    return 0;
}
