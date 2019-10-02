#include <bits/stdc++.h>
#define KEY_SIZE 128
#define INPUT_SIZE 128
#define BYTE_SIZE 8
#define WORD_SIZE 32
using namespace std;

// TODO: AES_Decryption and Electronic Code Book input/output

bitset<BYTE_SIZE> SubByteTable[16][16] = {    
    {bitset<BYTE_SIZE>(0x63), bitset<BYTE_SIZE>(0x7C), bitset<BYTE_SIZE>(0x77), bitset<BYTE_SIZE>(0x7B), bitset<BYTE_SIZE>(0xF2), bitset<BYTE_SIZE>(0x6B), bitset<BYTE_SIZE>(0x6F), bitset<BYTE_SIZE>(0xC5), bitset<BYTE_SIZE>(0x30), bitset<BYTE_SIZE>(0x01), bitset<BYTE_SIZE>(0x67), bitset<BYTE_SIZE>(0x2B), bitset<BYTE_SIZE>(0xFE), bitset<BYTE_SIZE>(0xD7), bitset<BYTE_SIZE>(0xAB), bitset<BYTE_SIZE>(0x76)},
    {bitset<BYTE_SIZE>(0xCA), bitset<BYTE_SIZE>(0x82), bitset<BYTE_SIZE>(0xC9), bitset<BYTE_SIZE>(0x7D), bitset<BYTE_SIZE>(0xFA), bitset<BYTE_SIZE>(0x59), bitset<BYTE_SIZE>(0x47), bitset<BYTE_SIZE>(0xF0), bitset<BYTE_SIZE>(0xAD), bitset<BYTE_SIZE>(0xD4), bitset<BYTE_SIZE>(0xA2), bitset<BYTE_SIZE>(0xAF), bitset<BYTE_SIZE>(0x9C), bitset<BYTE_SIZE>(0xA4), bitset<BYTE_SIZE>(0x72), bitset<BYTE_SIZE>(0xC0)},
    {bitset<BYTE_SIZE>(0xB7), bitset<BYTE_SIZE>(0xFD), bitset<BYTE_SIZE>(0x93), bitset<BYTE_SIZE>(0x26), bitset<BYTE_SIZE>(0x36), bitset<BYTE_SIZE>(0x3F), bitset<BYTE_SIZE>(0xF7), bitset<BYTE_SIZE>(0xCC), bitset<BYTE_SIZE>(0x34), bitset<BYTE_SIZE>(0xA5), bitset<BYTE_SIZE>(0xE5), bitset<BYTE_SIZE>(0xF1), bitset<BYTE_SIZE>(0x71), bitset<BYTE_SIZE>(0xD8), bitset<BYTE_SIZE>(0x31), bitset<BYTE_SIZE>(0x15)},
    {bitset<BYTE_SIZE>(0x04), bitset<BYTE_SIZE>(0xC7), bitset<BYTE_SIZE>(0x23), bitset<BYTE_SIZE>(0xC3), bitset<BYTE_SIZE>(0x18), bitset<BYTE_SIZE>(0x96), bitset<BYTE_SIZE>(0x05), bitset<BYTE_SIZE>(0x9A), bitset<BYTE_SIZE>(0x07), bitset<BYTE_SIZE>(0x12), bitset<BYTE_SIZE>(0x80), bitset<BYTE_SIZE>(0xE2), bitset<BYTE_SIZE>(0xEB), bitset<BYTE_SIZE>(0x27), bitset<BYTE_SIZE>(0xB2), bitset<BYTE_SIZE>(0x75)},
    {bitset<BYTE_SIZE>(0x09), bitset<BYTE_SIZE>(0x83), bitset<BYTE_SIZE>(0x2C), bitset<BYTE_SIZE>(0x1A), bitset<BYTE_SIZE>(0x1B), bitset<BYTE_SIZE>(0x6E), bitset<BYTE_SIZE>(0x5A), bitset<BYTE_SIZE>(0xA0), bitset<BYTE_SIZE>(0x52), bitset<BYTE_SIZE>(0x3B), bitset<BYTE_SIZE>(0xD6), bitset<BYTE_SIZE>(0xB3), bitset<BYTE_SIZE>(0x29), bitset<BYTE_SIZE>(0xE3), bitset<BYTE_SIZE>(0x2F), bitset<BYTE_SIZE>(0x84)},
    {bitset<BYTE_SIZE>(0x53), bitset<BYTE_SIZE>(0xD1), bitset<BYTE_SIZE>(0x00), bitset<BYTE_SIZE>(0xED), bitset<BYTE_SIZE>(0x20), bitset<BYTE_SIZE>(0xFC), bitset<BYTE_SIZE>(0xB1), bitset<BYTE_SIZE>(0x5B), bitset<BYTE_SIZE>(0x6A), bitset<BYTE_SIZE>(0xCB), bitset<BYTE_SIZE>(0xBE), bitset<BYTE_SIZE>(0x39), bitset<BYTE_SIZE>(0x4A), bitset<BYTE_SIZE>(0x4C), bitset<BYTE_SIZE>(0x58), bitset<BYTE_SIZE>(0xCF)},
    {bitset<BYTE_SIZE>(0xD0), bitset<BYTE_SIZE>(0xEF), bitset<BYTE_SIZE>(0xAA), bitset<BYTE_SIZE>(0xFB), bitset<BYTE_SIZE>(0x43), bitset<BYTE_SIZE>(0x4D), bitset<BYTE_SIZE>(0x33), bitset<BYTE_SIZE>(0x85), bitset<BYTE_SIZE>(0x45), bitset<BYTE_SIZE>(0xF9), bitset<BYTE_SIZE>(0x02), bitset<BYTE_SIZE>(0x7F), bitset<BYTE_SIZE>(0x50), bitset<BYTE_SIZE>(0x3C), bitset<BYTE_SIZE>(0x9F), bitset<BYTE_SIZE>(0xA8)},
    {bitset<BYTE_SIZE>(0x51), bitset<BYTE_SIZE>(0xA3), bitset<BYTE_SIZE>(0x40), bitset<BYTE_SIZE>(0x8F), bitset<BYTE_SIZE>(0x92), bitset<BYTE_SIZE>(0x9D), bitset<BYTE_SIZE>(0x38), bitset<BYTE_SIZE>(0xF5), bitset<BYTE_SIZE>(0xBC), bitset<BYTE_SIZE>(0xB6), bitset<BYTE_SIZE>(0xDA), bitset<BYTE_SIZE>(0x21), bitset<BYTE_SIZE>(0x10), bitset<BYTE_SIZE>(0xFF), bitset<BYTE_SIZE>(0xF3), bitset<BYTE_SIZE>(0xD2)},
    {bitset<BYTE_SIZE>(0xCD), bitset<BYTE_SIZE>(0x0C), bitset<BYTE_SIZE>(0x13), bitset<BYTE_SIZE>(0xEC), bitset<BYTE_SIZE>(0x5F), bitset<BYTE_SIZE>(0x97), bitset<BYTE_SIZE>(0x44), bitset<BYTE_SIZE>(0x17), bitset<BYTE_SIZE>(0xC4), bitset<BYTE_SIZE>(0xA7), bitset<BYTE_SIZE>(0x7E), bitset<BYTE_SIZE>(0x3D), bitset<BYTE_SIZE>(0x64), bitset<BYTE_SIZE>(0x5D), bitset<BYTE_SIZE>(0x19), bitset<BYTE_SIZE>(0x73)},
    {bitset<BYTE_SIZE>(0x60), bitset<BYTE_SIZE>(0x81), bitset<BYTE_SIZE>(0x4F), bitset<BYTE_SIZE>(0xDC), bitset<BYTE_SIZE>(0x22), bitset<BYTE_SIZE>(0x2A), bitset<BYTE_SIZE>(0x90), bitset<BYTE_SIZE>(0x88), bitset<BYTE_SIZE>(0x46), bitset<BYTE_SIZE>(0xEE), bitset<BYTE_SIZE>(0xB8), bitset<BYTE_SIZE>(0x14), bitset<BYTE_SIZE>(0xDE), bitset<BYTE_SIZE>(0x5E), bitset<BYTE_SIZE>(0x0B), bitset<BYTE_SIZE>(0xDB)},
    {bitset<BYTE_SIZE>(0xE0), bitset<BYTE_SIZE>(0x32), bitset<BYTE_SIZE>(0x3A), bitset<BYTE_SIZE>(0x0A), bitset<BYTE_SIZE>(0x49), bitset<BYTE_SIZE>(0x06), bitset<BYTE_SIZE>(0x24), bitset<BYTE_SIZE>(0x5C), bitset<BYTE_SIZE>(0xC2), bitset<BYTE_SIZE>(0xD3), bitset<BYTE_SIZE>(0xAC), bitset<BYTE_SIZE>(0x62), bitset<BYTE_SIZE>(0x91), bitset<BYTE_SIZE>(0x95), bitset<BYTE_SIZE>(0xE4), bitset<BYTE_SIZE>(0x79)},
    {bitset<BYTE_SIZE>(0xE7), bitset<BYTE_SIZE>(0xC8), bitset<BYTE_SIZE>(0x37), bitset<BYTE_SIZE>(0x6D), bitset<BYTE_SIZE>(0x8D), bitset<BYTE_SIZE>(0xD5), bitset<BYTE_SIZE>(0x4E), bitset<BYTE_SIZE>(0xA9), bitset<BYTE_SIZE>(0x6C), bitset<BYTE_SIZE>(0x56), bitset<BYTE_SIZE>(0xF4), bitset<BYTE_SIZE>(0xEA), bitset<BYTE_SIZE>(0x65), bitset<BYTE_SIZE>(0x7A), bitset<BYTE_SIZE>(0xAE), bitset<BYTE_SIZE>(0x08)},
    {bitset<BYTE_SIZE>(0xBA), bitset<BYTE_SIZE>(0x78), bitset<BYTE_SIZE>(0x25), bitset<BYTE_SIZE>(0x2E), bitset<BYTE_SIZE>(0x1C), bitset<BYTE_SIZE>(0xA6), bitset<BYTE_SIZE>(0xB4), bitset<BYTE_SIZE>(0xC6), bitset<BYTE_SIZE>(0xE8), bitset<BYTE_SIZE>(0xDD), bitset<BYTE_SIZE>(0x74), bitset<BYTE_SIZE>(0x1F), bitset<BYTE_SIZE>(0x4B), bitset<BYTE_SIZE>(0xBD), bitset<BYTE_SIZE>(0x8B), bitset<BYTE_SIZE>(0x8A)},
    {bitset<BYTE_SIZE>(0x70), bitset<BYTE_SIZE>(0x3E), bitset<BYTE_SIZE>(0xB5), bitset<BYTE_SIZE>(0x66), bitset<BYTE_SIZE>(0x48), bitset<BYTE_SIZE>(0x03), bitset<BYTE_SIZE>(0xF6), bitset<BYTE_SIZE>(0x0E), bitset<BYTE_SIZE>(0x61), bitset<BYTE_SIZE>(0x35), bitset<BYTE_SIZE>(0x57), bitset<BYTE_SIZE>(0xB9), bitset<BYTE_SIZE>(0x86), bitset<BYTE_SIZE>(0xC1), bitset<BYTE_SIZE>(0x1D), bitset<BYTE_SIZE>(0x9E)},
    {bitset<BYTE_SIZE>(0xE1), bitset<BYTE_SIZE>(0xF8), bitset<BYTE_SIZE>(0x98), bitset<BYTE_SIZE>(0x11), bitset<BYTE_SIZE>(0x69), bitset<BYTE_SIZE>(0xD9), bitset<BYTE_SIZE>(0x8E), bitset<BYTE_SIZE>(0x94), bitset<BYTE_SIZE>(0x9B), bitset<BYTE_SIZE>(0x1E), bitset<BYTE_SIZE>(0x87), bitset<BYTE_SIZE>(0xE9), bitset<BYTE_SIZE>(0xCE), bitset<BYTE_SIZE>(0x55), bitset<BYTE_SIZE>(0x28), bitset<BYTE_SIZE>(0xDF)},
    {bitset<BYTE_SIZE>(0x8C), bitset<BYTE_SIZE>(0xA1), bitset<BYTE_SIZE>(0x89), bitset<BYTE_SIZE>(0x0D), bitset<BYTE_SIZE>(0xBF), bitset<BYTE_SIZE>(0xE6), bitset<BYTE_SIZE>(0x42), bitset<BYTE_SIZE>(0x68), bitset<BYTE_SIZE>(0x41), bitset<BYTE_SIZE>(0x99), bitset<BYTE_SIZE>(0x2D), bitset<BYTE_SIZE>(0x0F), bitset<BYTE_SIZE>(0xB0), bitset<BYTE_SIZE>(0x54), bitset<BYTE_SIZE>(0xBB), bitset<BYTE_SIZE>(0x16)}
};

bitset<4> HexToBinary(char c){
    bitset<4> retval;
    switch(c)
    {
        case '0': retval = bitset<4>(0x0); break;
        case '1': retval = bitset<4>(0x1); break;
        case '2': retval = bitset<4>(0x2); break;
        case '3': retval = bitset<4>(0x3); break;
        case '4': retval = bitset<4>(0x4); break;
        case '5': retval = bitset<4>(0x5); break;
        case '6': retval = bitset<4>(0x6); break;
        case '7': retval = bitset<4>(0x7); break;
        case '8': retval = bitset<4>(0x8); break;
        case '9': retval = bitset<4>(0x9); break;
        case 'a': retval = bitset<4>(0xA); break;
        case 'b': retval = bitset<4>(0xB); break;
        case 'c': retval = bitset<4>(0xC); break;
        case 'd': retval = bitset<4>(0xD); break;
        case 'e': retval = bitset<4>(0xE); break;
        case 'f': retval = bitset<4>(0xF); break;
    }
    return retval;
}

char BinaryToHex(bitset<4> b)
{
    char retval;
    int int_val = (int) b.to_ulong();
    switch(int_val)
    {
        case 0: retval = '0'; break;
        case 1: retval = '1'; break;
        case 2: retval = '2'; break;
        case 3: retval = '3'; break;
        case 4: retval = '4'; break;
        case 5: retval = '5'; break;
        case 6: retval = '6'; break;
        case 7: retval = '7'; break;
        case 8: retval = '8'; break;
        case 9: retval = '9'; break;
        case 10: retval = 'a'; break;
        case 11: retval = 'b'; break;
        case 12: retval = 'c'; break;
        case 13: retval = 'd'; break;
        case 14: retval = 'e'; break;
        case 15: retval = 'f'; break;
    }
    return retval;
}

int get_degree(bitset<BYTE_SIZE>& polynomial)
{
    for(int i = BYTE_SIZE-1; i >=0; i--){
        if(polynomial.test(i))
        {
            return i;
        }
    }
    return 0;
}

bitset<BYTE_SIZE> polynomial_multiplication(bitset<BYTE_SIZE>& poly1, bitset<BYTE_SIZE>& poly2)
{
    bitset<BYTE_SIZE> modulo_polynomial(0b00011011);
    //int degree = get_degree(poly1);
    bitset<BYTE_SIZE> Poly2 = poly2;
    bitset<BYTE_SIZE> result;
    bool xor_flag = false;
    for(int i = 0; i < 8; i++)
    {
        if(Poly2.test(7)){
            xor_flag = true;
        }
        if(poly1.test(i)){
            result = result ^ Poly2;
        }
        Poly2 = Poly2 << 1;
        if(xor_flag){
            Poly2 = Poly2 ^ modulo_polynomial;
            xor_flag = false;
        } 
        //cout << Poly2 << endl;   
    }
    //cout << result;
    return result;
}

bitset<8> multiplicative_inverse(bitset<8> input_polynomial)
{
    //pass
}

bitset<WORD_SIZE> RotWord(bitset<WORD_SIZE> input_word)
{
    /*
    string res = "";   
    for(int i = 0; i < WORD_SIZE-1; i += BYTE_SIZE)
    {
        bitset<BYTE_SIZE> temp(input_word.to_string().substr(i, 8));
        temp = temp << 1 | temp >> (BYTE_SIZE-1); // Rotate every byte to the left by one position
        res = res + temp.to_string();
    }
    */
    bitset<WORD_SIZE> retval(input_word.to_string().substr(8, 24) + input_word.to_string().substr(0,8));
    return retval;
}

bitset<WORD_SIZE> SubWord(bitset<WORD_SIZE> input)
{
    string result = "";
    for(int i = 0; i < WORD_SIZE-1; i+=BYTE_SIZE)
    {
        bitset<4> row(input.to_string().substr(i, 4));
        bitset<4> col(input.to_string().substr(i+4, 4));
        int r = (int) BinaryToHex(row) - '0';
        int c = (int) BinaryToHex(col) - '0';
        if(r > 9) {
            r = (int) BinaryToHex(row) - 'a' + 10;
        }
        if(c > 9) {
            c = (int) BinaryToHex(col) - 'a' + 10;
        }
        //cout << "row = " << r << " col = " << c << endl;
        result = result + (SubByteTable[r][c]).to_string();
    }
    return bitset<WORD_SIZE>(result); 
}

void printBitsetInHex(bitset<WORD_SIZE>& word)
{
    string word_string = word.to_string();
    for(int i = 0; i < WORD_SIZE; i+=4){
        cout << BinaryToHex(bitset<4>(word_string.substr(i, 4)));
    }
    cout << " ";
}

class AES
{
    private:
        bitset<INPUT_SIZE> Input;
        bitset<INPUT_SIZE> Output;
        vector<vector<bitset<BYTE_SIZE>>> state;
        bitset<KEY_SIZE> AES_key;
        bitset<BYTE_SIZE> ConstMatrix[4][4] = {
            {bitset<BYTE_SIZE>(0x02), bitset<BYTE_SIZE>(0x03), bitset<BYTE_SIZE>(0x01), bitset<BYTE_SIZE>(0x01)},
            {bitset<BYTE_SIZE>(0x01), bitset<BYTE_SIZE>(0x02), bitset<BYTE_SIZE>(0x03), bitset<BYTE_SIZE>(0x01)},
            {bitset<BYTE_SIZE>(0x01), bitset<BYTE_SIZE>(0x01), bitset<BYTE_SIZE>(0x02), bitset<BYTE_SIZE>(0x03)},
            {bitset<BYTE_SIZE>(0x03), bitset<BYTE_SIZE>(0x01), bitset<BYTE_SIZE>(0x01), bitset<BYTE_SIZE>(0x02)}
        };
        bitset<BYTE_SIZE> InvConstMatrix[4][4] = {
            {bitset<BYTE_SIZE>(0x0E), bitset<BYTE_SIZE>(0x0B), bitset<BYTE_SIZE>(0x0D), bitset<BYTE_SIZE>(0x09)},
            {bitset<BYTE_SIZE>(0x09), bitset<BYTE_SIZE>(0x0E), bitset<BYTE_SIZE>(0x0B), bitset<BYTE_SIZE>(0x0D)},
            {bitset<BYTE_SIZE>(0x0D), bitset<BYTE_SIZE>(0x09), bitset<BYTE_SIZE>(0x0E), bitset<BYTE_SIZE>(0x0B)},
            {bitset<BYTE_SIZE>(0x0B), bitset<BYTE_SIZE>(0x0D), bitset<BYTE_SIZE>(0x09), bitset<BYTE_SIZE>(0x0E)}
        };
        
        bitset<WORD_SIZE> KeyMatrix[11][4];
        bitset<WORD_SIZE> RCons[10] = {
            bitset<WORD_SIZE>(0x01000000),
            bitset<WORD_SIZE>(0x02000000),
            bitset<WORD_SIZE>(0x04000000),
            bitset<WORD_SIZE>(0x08000000),
            bitset<WORD_SIZE>(0x10000000),
            bitset<WORD_SIZE>(0x20000000),
            bitset<WORD_SIZE>(0x40000000),
            bitset<WORD_SIZE>(0x80000000),
            bitset<WORD_SIZE>(0x1B000000),
            bitset<WORD_SIZE>(0x36000000)
        };
        void KeyExpansion();
        void AddRoundKey(int round_number);
        // Encryption methods
        void SubBytes();
        void ShiftRows();
        void MixColumns();
        void AES_Encryption_Round(int round_number);
        // Decryption methods
        void InvSubBytes();
        void InvShiftRows();
        void InvMixColumns();
        void AES_Decryption_Round(int round_number);
    public:
        AES(string& AES_Key);
        void printState();
        string AES_Encryption(string& PlainText);
        string AES_Decryption(string& CipherText);
        
};

AES::AES(string& AES_key)
{
    this->AES_key = bitset<KEY_SIZE>(AES_key);
    this->KeyExpansion();
}

void AES::KeyExpansion()
{
    string AES_Key_string = AES_key.to_string();
    for(int j = 0; j < KEY_SIZE; j += WORD_SIZE)
    {
        KeyMatrix[0][j / WORD_SIZE] = bitset<WORD_SIZE>(AES_Key_string.substr(j, WORD_SIZE));
    }
    for(int i = 1; i < 11; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(j != 0) 
            {
                KeyMatrix[i][j] = KeyMatrix[i][j-1] ^ KeyMatrix[i-1][j];
            }
            else
            {
                // printBitsetInHex(KeyMatrix[i-1][3]); cout << endl;
                bitset<WORD_SIZE> t = SubWord(RotWord(KeyMatrix[i-1][3])) ^ RCons[i-1];
                // cout << " Round # "<< i <<" t = "; printBitsetInHex(t); cout << endl;
                KeyMatrix[i][j] = t ^ KeyMatrix[i-1][0];
            }   
        }
    }
    /*
    for(int i = 0; i < 11; i++){
        for(int j = 0; j < 4; j++){
            printBitsetInHex(KeyMatrix[i][j]);
        }
        cout << endl;
    }
    */
}

void AES::printState()
{
    string str;
    for(int i = 0; i < 4; i++){
	    for(int j = 0; j < 4; j++){
	        str = state[j][i].to_string();
            cout << BinaryToHex(bitset<4>(str.substr(0,4))) << BinaryToHex(bitset<4>(str.substr(4,4)));
	    }
	}
    cout << endl;
}

string AES::AES_Encryption(string& PlainText)
{
    //cout << PlainText << endl;
    // Build initial state
    for(int i = 0; i < 4; i++)
    {
        vector<bitset<BYTE_SIZE>> word;
        for(int j = BYTE_SIZE*i; j < INPUT_SIZE-1; j+=32)
        {
            word.push_back(bitset<BYTE_SIZE>(PlainText.substr(j, BYTE_SIZE)));
        }
        state.push_back(word);
    }
    //cout << "Initial State!" << endl;
    //printState();
    for(int round = 0; round <= 10; round++)
    {
        AES_Encryption_Round(round);
    }
    //cout << "Encryption is: " << endl;
    // printState();
    string result = "";
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            string temp = state[j][i].to_string();
            result = result + BinaryToHex(bitset<4>(temp.substr(0,4))) + BinaryToHex(bitset<4>(temp.substr(4,4)));
        }
    }
    return result;
}   

void AES::SubBytes()
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            bitset<4> row(state[j][i].to_string().substr(0, 4));
            bitset<4> col(state[j][i].to_string().substr(4, 4));
            int r = (int) BinaryToHex(row) - '0';
            int c = (int) BinaryToHex(col) - '0';
            if(r > 9) {
                r = (int) BinaryToHex(row) - 'a' + 10;
            }
            if(c > 9) {
                c = (int) BinaryToHex(col) - 'a' + 10;
            }
            state[j][i] = SubByteTable[r][c];
        }
    }
}

void AES::ShiftRows()
{
    vector<vector<bitset<BYTE_SIZE>>> temp;
    for(int i = 0; i < 4; i++){
        vector<bitset<BYTE_SIZE>> t;
        for(int j = 0; j < 4; j++){
            t.push_back(state[i][(i+j)%4]);
        }
        temp.push_back(t);
    }
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            state[i][j] = temp[i][j];
        }
    }
}

void AES::MixColumns()
{
    for(int i = 0; i < 4; i++)
    {
        vector<bitset<BYTE_SIZE>> column;
        vector<bitset<BYTE_SIZE>> multiplied_column;
        for(int j = 0; j < 4; j++)
        {
            column.push_back(state[j][i]); // (j, i) for column
        }
        for(int k = 0; k < 4; k++)
        {
            bitset<BYTE_SIZE> xor_result;
            for(int l = 0; l < 4; l++)
            {
                xor_result = xor_result ^ polynomial_multiplication(ConstMatrix[k][l], column[l]);
            }
            multiplied_column.push_back(xor_result);
        }
        for(int j = 0; j < 4; j++)
        {
            state[j][i] = multiplied_column[j];
        }
    }
}

void AES::AddRoundKey(int round_number)
{
    for(int i = 0; i < 4; i++)
    {
        string current_key = (KeyMatrix[round_number-1][i]).to_string();
        //cout << "i = " << i << " current key: "; printBitsetInHex(KeyMatrix[round_number-1][i]); cout << endl;
        for(int j = 0; j < 4; j++)
        {
            state[j][i] = state[j][i] ^ bitset<BYTE_SIZE>(current_key.substr(BYTE_SIZE*j, BYTE_SIZE));
        }
    }
}

void AES::AES_Encryption_Round(int round_number)
{
    if(round_number == 0){
        // Pre-Round transformation
        AddRoundKey(1);
    }else if(round_number < 10){
        SubBytes();
        ShiftRows();
        MixColumns();
        AddRoundKey(round_number+1);
    }else if(round_number == 10){
        SubBytes();
        ShiftRows();
        AddRoundKey(11);
    }
    //cout << "Output of Round " << round_number << " is " << endl;
    //printState();
}

int main()
{
    //cout << "Hello AES!" << endl;
    string plain_text_hex; string plain_text_bin = "";
    string AES_key_hex; string AES_key_bin = "";
    cin >> plain_text_hex;
    cin >> AES_key_hex;
    
    for(int i = 0; i < plain_text_hex.length(); i++){
        plain_text_bin = plain_text_bin + HexToBinary(plain_text_hex.at(i)).to_string();
    }
    //cout << plain_text_bin << endl;
    for(int i = 0; i < AES_key_hex.length(); i++){
        AES_key_bin = AES_key_bin + HexToBinary(AES_key_hex.at(i)).to_string();
    }
    //cout << AES_key_bin << endl;
    //bitset<INPUT_SIZE> input(plain_text_bin);
    //bitset<KEY_SIZE> AES_key(AES_key_bin);
    
    AES* obj = new AES(AES_key_bin);
    string enc = obj->AES_Encryption(plain_text_bin);
    cout << enc << endl;
    return 0;
}
// Sample Input: 00112233445566778899aabbccddeeff Key: 000102030405060708090a0b0c0d0e0f
// SampleOutput: 69c4e0d86a7b0430d8cdb78070b4c55a DEc: 00112233445566778899aabbccddeeff