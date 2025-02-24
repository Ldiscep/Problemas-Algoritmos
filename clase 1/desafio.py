# Anagram Checker
def are_anagram(word1, word2):
    """
    Checks if two words are anagrams of each other.
    
    :param word1: str - First word
    :param word2: str - Second word
    :return: bool - True if the words are anagrams, False otherwise
    """
    # Implement the algorithm to check for anagrams here
    if len(word1) != len(word2):
        return False
    
    dictionary_w1={}
    dictionary_w2={}
    for char in word1:
        if char not in dictionary_w1:
            dictionary_w1[char]=1
        else:
            dictionary_w1[char]+=1
    
    for char in word2:
        if char not in dictionary_w2:
            dictionary_w2[char]=1
        else:
            dictionary_w2[char]+=1

    for characters in dictionary_w1:
        if characters in dictionary_w2:
            if dictionary_w1[characters] != dictionary_w2[characters]:
                return False
        else: return False
    return True

# Test Cases
def test_are_anagram():
    test_cases = [
        ("roma", "amor", True),
        ("python", "typhon", True),
        ("hola", "halo", True),
        ("listen", "silent", True),
        ("rat", "tar", True),
        ("hello", "world", False),
        ("night", "thing", True),
        ("abc", "def", False),
        ("aabbcc", "abcabc", True),
        ("", "", True),  # Two empty strings are anagrams
        ("a", "a", True),
        ("a", "b", False),
        ("abcd", "abc", False),  # Different lengths
    ]
    
    for i, (word1, word2, expected) in enumerate(test_cases):
        result = are_anagram(word1, word2)
        assert result == expected, f"FAILED on case {i + 1}: expected {expected}, but got {result}"
    print("All tests PASSED.")

# Run Tests
if __name__ == "__main__":
    test_are_anagram()
