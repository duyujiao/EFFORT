class Solution {
    public boolean isPalindrome(String s) {
        String str = s.toLowerCase();
        char[] ss = str.toCharArray();
        int l = str.length();
        int left = 0;
        int right = l - 1;

        // 验证回文串
        while (left < right) {
            while (left < right && !Character.isLetterOrDigit(ss[left])) {
                left++;
            }
            while (left < right && !Character.isLetterOrDigit(ss[right])) {
                right--;
            }

            if (ss[left] != ss[right]) {
                return false;
            }

            left++;
            right--;
        }

        return true;
    }
}