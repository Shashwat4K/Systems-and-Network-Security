from math import ceil
import time

universe = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
character_dict = dict(zip(list(universe), range(26)))
character_dict_inv = dict(enumerate(list(universe.lower())))
tableau = list()

'''
This code can even be written without using above dictionaries by using 'ord()' and 'chr()'
But use of dictionaries can calculate answer faster, as I observed.
'''

def get_coordinates(plain_character, key_character):
    return (character_dict[plain_character], character_dict[key_character.upper()])

def create_vigenere_tableau():
    tableau.append(list(universe))
    for i in range(1, 26):
        tableau.append(list(universe[i:] + universe[:i]))

def get_vigenere_value(coordinates):
    p, k = coordinates
    return tableau[p][k]

def vigenere_cipher_using_tableau(plain_text, key):
    text_size = len(plain_text)
    block_size = len(key)
    result = ''
    for j in range(ceil(text_size/block_size)):
        offset = j * block_size
        for i in range(block_size):
            if i + offset == text_size:
                break
            coords = get_coordinates(plain_text[i+offset], key[i])
            result += get_vigenere_value(coords)
            
    return result

def vigenere_cipher_without_tableau(plain_text, key):
    text_size = len(plain_text)
    block_size = len(key)
    result = ''
    for j in range(ceil(text_size / block_size)):
        offset = j * block_size
        for i in range(block_size):
            if i+offset == text_size:
                break
            c = get_coordinates(plain_text[i+offset], key[i])
            result = result + character_dict_inv[(c[0] + c[1]) % 26]
    
    return result.upper()       

def vigenere_cipher_decryption(cipher_text, key):
    block_size = len(key)
    text_size = len(cipher_text)
    result = ''
    for j in range(ceil(text_size / block_size)):
        offset = j * block_size
        for i in range(block_size):
            if i+offset == text_size:
                break
            c = get_coordinates(cipher_text[i+offset], key[i])
            result = result + character_dict_inv[(c[0] + (26 - c[1])) % 26]

    return result.upper()   

create_vigenere_tableau()

input_plain_text = input('Enter plain text: ')
input_key = input('Enter key: ')

start_time = time.time()
print(vigenere_cipher_using_tableau(input_plain_text.upper(), input_key.lower()))
end_time = time.time()

print('Time taken (with tableu)= {} seconds'.format(end_time-start_time))

start_time = time.time()
cipher = vigenere_cipher_without_tableau(input_plain_text.upper(), input_key.lower())
print(cipher)
end_time = time.time()

print('Time taken (without tableu)= {} seconds'.format(end_time-start_time))

print('Decrypted plain-text: {}'.format(vigenere_cipher_decryption(cipher, input_key)))
