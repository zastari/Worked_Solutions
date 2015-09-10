import byte_conversions

a = byte_conversions.change_format("1c0111001f010100061a024b53535009181c", "hex2bin")
b = byte_conversions.change_format("686974207468652062756c6c277320657965", "hex2bin")

c = byte_conversions.binary_xor(a, b)
print "%s" % byte_conversions.change_format(c, "bin2hex")
