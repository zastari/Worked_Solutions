import byte_conversions
import binascii

plaintext = """Burning 'em, if you ain't quick and nimble
I go crazy when I hear a cymbal"""
xor_key = "ICE"

print "%s" % byte_conversions.change_format(byte_conversions.repeating_key_xor(plaintext, xor_key), 'bin2hex')
