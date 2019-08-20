from math import ceil
import time

universe = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
plain_dict = dict(zip(list(universe), range(26)))
key_dict = dict(zip(list(universe.lower()), range(26)))
tableau = list()

def get_coordinates(plain_character, key_character):
    return (plain_dict[plain_character], key_dict[key_character])

def create_vigenere_tableau():
    tableau.append(list(universe))
    for i in range(1, 26):
        tableau.append(list(universe[i:] + universe[:i]))

def get_vigenere_value(coordinates):
    p, k = coordinates
    return tableau[p][k]

def vigenere_cipher(plain_text, key):
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

create_vigenere_tableau()

input_plain_text = input('Enter plain text: ')
input_key = input('Enter key: ')

start_time = time.time()
print(vigenere_cipher(input_plain_text.upper(), input_key.lower()))
end_time = time.time()

print('Time taken = {} seconds'.format(end_time-start_time))
