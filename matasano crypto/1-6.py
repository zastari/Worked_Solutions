import sys
import array
import byte_conversions
import score_plaintext

def hamming_distance(a, b):
    sum = 0
    for (i, j) in zip(a, b):
        sum += i ^ j

    return sum


def guess_keysize(ciphertext, range_min, range_max, block_avg):
    for i in range(range_min, range_max):
        cum_hamming_distance = 0
        for j in range(1, block_avg):
            cum_hamming_distance += hamming_distance(ciphertext[(j-1)*i:j*i], ciphertext[j*i:(j+1)*i])
        cum_hamming_distance /= float(i * (block_avg-1))
        print "%s: %f" % (i, cum_hamming_distance)


def vignere_profile(ciphertext, keysize, score_threshold):
    for register_shift in range(0,keysize):
        guess_dict = {}
        for key in range(0,255):
            guess = byte_conversions.change_format(byte_conversions.binary_xor_cyclic(''.join(format(i, '08b') for i in ciphertext[register_shift::keysize]), format(key, '08b')), "bin2hex")
            score = score_plaintext.score_prob(guess.decode("hex").lower())
        
            if score < 0.6:
                guess_dict[score] = [key, guess.decode("hex")]
        
        for key in sorted(guess_dict, reverse=True):
            print "Register %s -- %s: %s" % (register_shift, key, guess_dict[key])


def main():
    ciphertext = bytearray(open('1-6.input', 'rb').read().decode('base64'))
    guess_keysize(ciphertext, 2, 40, 30) # 29 bytes has lowest score
    vignere_profile(ciphertext, 29, 1)

    key = [84, 101, 114, 109, 105, 110, 97, 116, 111, 114, 32, 88, 58, 32, 66, 114, 105, 110, 103, 32, 116, 104, 101, 32, 110, 111, 105, 115, 101] # Terminator X: Bring the noise
    decoded_cipher = byte_conversions.change_format(byte_conversions.binary_xor_cyclic(''.join(format(i, '08b') for i in ciphertext), ''.join(format(i, '08b') for i in key)), "bin2hex")
    print decoded_cipher.decode("hex")


if __name__ == '__main__':
    sys.exit(main())
