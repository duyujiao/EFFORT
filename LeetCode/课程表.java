class Solution {
    public boolean canFinish(int numCourses, int[][] prerequisites) {
        List<List<Integer>> list=new ArrayList<>();
        int count=0;
        //初始化
        for(int i=0;i<numCourses;i++)
        {
            list.add(new ArrayList());
        }
        int[] indegree=new int[numCourses];
        //构建邻接表
        for(int[] e:prerequisites)
        {
            int b=e[0];
            int a=e[1];
            list.get(a).add(b);
            indegree[b]++;
        }
        Stack<Integer> stack=new Stack<>();
        //入度为0的点入栈
        for(int i=0;i<numCourses;i++)
        {
            if(indegree[i]==0)
            stack.push(i);
        }
        //更新indegree数组
        while(!stack.isEmpty())
        {
            int top=stack.pop();
            count++;
            for(int n:list.get(top))
            {
            indegree[n]--;
            if(indegree[n]==0)
            stack.push(n);
            }
        }
        if(count==numCourses)
        return true;
        else
        return false;

    }
}