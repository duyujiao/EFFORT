class Solution {
    public int hammingDistance(int x, int y) {
        //栈实现
        // Stack<Integer> s1=new Stack<>();
        // Stack<Integer> s2=new Stack<>();
        Deque<Integer> s1 = new LinkedList<>();
        Deque<Integer> s2 = new LinkedList<>();
        int count=0;
        while(x!=0||y!=0)
        {
            s1.push(x%2);
            s2.push(y%2);
            x/=2;
            y/=2;
        }
        int size=Math.max(s1.size(),s2.size());
        for(int i=0;i<size;i++)
        {
            if(s1.pop()!=s2.pop())
            count++;
        }
        return count;

    }
}