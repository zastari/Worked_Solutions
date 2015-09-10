from collections import Counter

def score_prob(decrypted_text):
    decrypted_text = decrypted_text.lower().translate(None, " ,.'")
    letters = "abcdefghijklmnopqrstuvwxyz"
    frequencies = [0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 0.02015, 0.06094, 0.06966, 0.00153, 0.00772, 0.04025, 0.02406, 0.06749,
                   0.07507, 0.01929, 0.00095, 0.05987, 0.06327, 0.09056, 0.02758, 0.00978, 0.02360, 0.00150, 0.01974, 0.00074]
    score = 0
    for i in range(0,26):
        score += abs(frequencies[i] - (decrypted_text.count(letters[i]) / float(len(decrypted_text))))
    
    return score

def score_freq(decrypted_text):
    freq_order = """ etaoinshrdlcumwfgypb.vkjxq,z"""
    count_list = Counter(decrypted_text)
    score = 0
    for i in count_list:
        score += ((26 - (freq_order.find(i) if freq_order.find(i) != -1 else 50)) * count_list[i])

    return score
