
// sort increasingly  using max heap

void sink (int a[], int n, int p) {
	
	while (p*2<=n)
	{
		int s=p*2;
		if (s<n && a[s+1]>a[s]) s++;
		if (a[p]>=a[s]) return;
		swap(a[p],a[s]);
		p=s;
	}
}

void floyd_heap_construction (int a[],int n) {
	for (int i=n-1;i>=1;i--)
		sink(a,n,i);
}

void heap_sort(int a[], int n) {
	while (n>1)
	{
		swap(a[1],a[n--]);
		sink(a,n,1);
	}
}
