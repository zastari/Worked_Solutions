import byte_conversions

string = byte_conversions.change_format("49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d", "hex2bin")
print "%s" % byte_conversions.change_format(string, "bin2base64")
