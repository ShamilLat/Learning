def longestCommonPrefix(x):
    if len(x) == 0:
        return ""

    if len(x) == 1:
        return x[0]

    end = 0
    check = False
    str = ""
    first_sp_pos = 0
    for j in range(len(x[0])):
        if x[0][j] == " ":
            first_sp_pos += 1
            continue
        for i in range(1, len(x)):
            sp_pos = j - first_sp_pos 
            null_pos = 0
            while null_pos < len(x[i]) and x[i][null_pos] == " ":
                null_pos += 1
            sp_pos += null_pos
            if sp_pos == len(x[i]) or x[0][j] != x[i][sp_pos]:
                check = True
                break
        if check == True:
            break

        end += 1
        str = str + x[0][j]
    return str
