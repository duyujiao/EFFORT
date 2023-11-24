void reverseString(char* s, int sSize) {
    int p;
    int q;
    int m=sSize;
    int n=0;

    for(int i=0;i<sSize/2;i++)
    {

        p=n;
        q=m-1;
        char t;
        t=s[p];
        s[p]=s[q];
        s[q]=t;
        n++;
        m--;
    }
}