from typing import List
def findAllConcatenatedWordsInADict(words: List[str]) -> List[str]:
  word_set = set(words)

  def dfs(word):
    for i in range(1, len(word)):
      prefix = word[:i]
      suffix = word[i:]

      if prefix in word_set and (suffix in word_set or dfs(suffix)):
        return True
    return False

  final_result = []
  for word in words:
    if dfs(word):
      final_result.append(word)

  return final_result

# Open the file to read
results = []
f = open("data/wordsforproblem.txt", "r")

# Read the dictionary file of words into a list
line = f.readline()
while len(line):
  line = line.strip()
  results.append(line)
  line = f.readline()

concatenatedWords = findAllConcatenatedWordsInADict(results)

overall_dict = {}
for w in concatenatedWords:
  curr_len = len(w)
  if curr_len not in overall_dict:
    overall_dict[curr_len] = [w]
  else:
    overall_dict[curr_len].append(w)
key_list = overall_dict.keys()
sorted_key_list = sorted(key_list, reverse=True)
print("Longest Word = ", overall_dict[sorted_key_list[0]])
print("2nd longest word = ", overall_dict[sorted_key_list[1]])
print("total count of concatenated words in the file = ", len(concatenatedWords))

