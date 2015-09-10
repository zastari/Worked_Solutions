import byte_conversions
import score_plaintext

secret_binary = byte_conversions.change_format("1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736", "hex2bin")
guess_dict = {}
for key in range(0,255):
    guess = byte_conversions.change_format(byte_conversions.binary_xor_cyclic(secret_binary, '{0:08b}'.format(key)), "bin2hex")
    score = score_plaintext.score_prob(guess.decode("hex").lower())
    print "Score %s -- %s: %s" % ( score, '{0:08b}'.format(key), guess.decode("hex") )
    
    if score > 0:
        guess_dict[score] = guess.decode("hex")

for key in sorted(guess_dict):
    print "%s: %s" % (key, guess_dict[key])
