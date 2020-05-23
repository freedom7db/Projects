
int partition (int a[], int li, int ls) 
{	
	int x=a[ls], p=li;
	for(int i=li; i<(ls-li), i++) 
		if (a[i]<=x) 
			swap(a[i],a[p]),p++;
	
	swap(a[ls],a[p]);
	return p;
}

void quiksort (int a[],int p, int q) 
{
	if (p>=q) return;
	int x = partition(a,p,q);
	quiksort(a,p,x-1);
	quiksort(a,x+1,q);
}

