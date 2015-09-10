import sys
import array

def main():
    ciphertext = open('1-8.input', 'r')
    for line in ciphertext:
        line = line.rstrip('\n');
        line_split = [line[i:i+32] for i in range(0, len(line), 32)] # Split line into 16 byte segments
        print "%d -- %s" % (len(set(line_split)), line)                                   # Count the amount of unique elements

if __name__ == '__main__':
    sys.exit(main())

