
void merge(int a[],int l, int m, int h) {

	int x,y,j=0,k=0;
	
	for (int i=l; i<=h; i++) {
		
		x = (j<=m) ? a[j] : (int)1e+9;
		y = (k<=h) ? a[k] : (int)1e+9;

		if (x<=y)	
				{ a[i]=a[j]; j++; }
		else 		
				{ a[i]=a[k]; k++; }
	}

}

void merge(int a[],int l, int m, int h) {
	
	int p[m-l+2], q[h-m+1];
	p[m-l+1]=inf, q[h-m]=inf;
	
	int j=0;
	for (int i=l; i<=m; i++)
		p[j++]=a[i];
	
	int k=0;
	for (int i=m+1; i<=h; i++)
		q[k++]=a[i];
	
	j=0,k=0;
	for (int i=l; i<=h; i++)
		if (p[j]<=q[k])  { a[i]=p[j]; j++; }
		else  			 { a[i]=q[k]; k++; }

	j=0,k=0;
	for (int i=l; i<=h; i++) {
		
		x = (j<=m) ? a[j] : (int)1e+9;
		y = (k<=h) ? a[k] : (int)1e+9;

		if (x<=y)	{ a[i]=p[j]; j++; }
		else 		{ a[i]=q[k]; k++; }
	}

}


void merge_sort(int a[],int l, int h) {
		
	if (l==h) return;

	int mid=(l+h)/2;
	merge_sort(a,l,mid);
	merge_sort(a,mid+1,h);
	merge(a,l,mid,h);

}
