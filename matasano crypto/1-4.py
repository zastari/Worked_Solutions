import byte_conversions
import score_plaintext


guess_dict = {}
with open("1-4.input", "r") as encrypted_list:
    for encrypted_text in encrypted_list:
        encrypted_text = encrypted_text.rstrip('\n')
        secret_binary = byte_conversions.change_format(str(encrypted_text), "hex2bin")
        for key in range(0,255):
            guess = byte_conversions.change_format(byte_conversions.binary_xor_cyclic(secret_binary, '{0:08b}'.format(key)), "bin2hex")
            score = score_plaintext.score_freq(guess.decode("hex").lower())
            
            if score > 0:
                guess_dict[score] = [guess.decode("hex"), encrypted_text]
        
for key in sorted(guess_dict):
    print "%s: %s" % (key, guess_dict[key])
