def check(s, filename):
    s = s.lower()
    words = s.split(" ")
    words.sort()
    
    words_cnt = {}
    for i in words:
        if i in words_cnt:
            words_cnt[i] += 1
        else:
            words_cnt[i] = 1
    file = open(filename, "w")
    for i in words_cnt:
        file.write(str(i) + " " + str(words_cnt[i]) + "\n")
    file.close()
