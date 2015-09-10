# Convert the following string from hexadecimal to base64:
# 49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d
# Done using built-in python functions decode() and encode()

print "%s" % "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d".decode("hex").encode("base64")
