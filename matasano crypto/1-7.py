from Crypto.Cipher import AES

ciphertext = open('1-7.input', 'rb').read().decode('base64')
key = b'YELLOW SUBMARINE'

cipher = AES.new(key, AES.MODE_ECB)
print cipher.decrypt(ciphertext)

