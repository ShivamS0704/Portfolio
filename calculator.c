i#include <stdio.h>
#include <math.h>

double memory = 0;

void basicCalc();
void scientificCalc();
void trigonometry();
void statistics();
void matrixMenu();
void storeMemory();

double inputWithMemory() {
    int choice;
    double x;

    printf("1. Enter number\n2. Use Memory (MR)\n");
    scanf("%d", &choice);

    if(choice == 2) {
        printf("Using Memory: %lf\n", memory);
        return memory;
    } else {
        printf("Enter value: ");
        scanf("%lf", &x);
        return x;
    }
}
\

int main() {
    int choice;

    while (1) {
        printf("\n========= SCIENTIFIC CALCULATOR =========\n");
        printf("1. Basic Calculator\n");
        printf("2. Scientific Functions\n");
        printf("3. Trigonometry\n");
        printf("4. Statistics\n");
        printf("5. Matrix Operations\n");
        printf("6. Store Value in Memory (MS)\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: basicCalc(); break;
            case 2: scientificCalc(); break;
            case 3: trigonometry(); break;
            case 4: statistics(); break;
            case 5: matrixMenu(); break;
            case 6: storeMemory(); break;
            case 7: return 0;
            default: printf("Invalid choice!\n");
        }
    }
}

void storeMemory() {
    printf("Enter value to store: ");
    scanf("%lf", &memory);
    printf("Stored successfully: %lf\n", memory);
}

void basicCalc() {
    int ch;
    double a, b;

    printf("\n1.Add 2.Sub 3.Mul 4.Div\n");
    scanf("%d", &ch);

    a = inputWithMemory();
    b = inputWithMemory();

    switch(ch) {
        case 1: printf("Result = %.2lf\n", a + b); break;
        case 2: printf("Result = %.2lf\n", a - b); break;
        case 3: printf("Result = %.2lf\n", a * b); break;
        case 4:
            if(b != 0) printf("Result = %.2lf\n", a / b);
            else printf("Divide by zero!\n");
            break;
    }
}

void scientificCalc() {
    int ch;
    double x, y;

    printf("\n1.Sqrt 2.Power 3.Log 4.Log10 5.Exp 6.Factorial\n");
    scanf("%d", &ch);

    if(ch == 2) {
        x = inputWithMemory();
        y = inputWithMemory();
    } 
    else if(ch == 6) {
        int n = (int)inputWithMemory();
        if(n < 0) {
            printf("Invalid input!\n");
            return;
        }
        long long fact = 1;
        for(int i = 1; i <= n; i++)
            fact *= i;
        printf("Factorial = %lld\n", fact);
        return;
    }
    else {
        x = inputWithMemory();
    }

    switch(ch) {
        case 1: if(x>=0) printf("%lf\n", sqrt(x)); else printf("Invalid\n"); break;
        case 2: printf("%lf\n", pow(x,y)); break;
        case 3: if(x>0) printf("%lf\n", log(x)); else printf("Invalid\n"); break;
        case 4: if(x>0) printf("%lf\n", log10(x)); else printf("Invalid\n"); break;
        case 5: printf("%lf\n", exp(x)); break;
    }
}

void trigonometry() {
    int ch;
    double angle, rad;

    printf("\n1.Sin 2.Cos 3.Tan\n");
    scanf("%d",&ch);

    angle = inputWithMemory();
    rad = angle * M_PI / 180;

    if(ch==1) printf("%lf\n", sin(rad));
    else if(ch==2) printf("%lf\n", cos(rad));
    else if(ch==3) {
        if(cos(rad)==0) printf("Undefined\n");
        else printf("%lf\n", tan(rad));
    }
}

void statistics() {
    int n;
    printf("Enter n: ");
    scanf("%d",&n);

    double arr[n], sum=0;

    printf("Enter %d numbers:\n", n);
    for(int i=0;i<n;i++){
        scanf("%lf",&arr[i]);
        sum+=arr[i];
    }

    double mean = sum/n;

    for(int i=0;i<n-1;i++) //bubble sort
        for(int j=i+1;j<n;j++)
            if(arr[i]>arr[j]){
                double temp=arr[i];
                arr[i]=arr[j];
                arr[j]=temp;
            }

    double median = (n%2==0) ? (arr[n/2-1]+arr[n/2])/2 : arr[n/2];

    double mode = arr[0];
    int maxCount = 1;

    for(int i=0;i<n;i++){
        int count=1;
        for(int j=i+1;j<n;j++){
            if(arr[i]==arr[j]) count++;
        }
        if(count>maxCount){
            maxCount=count;
            mode=arr[i];
        }
    }

    printf("Mean=%lf\nMedian=%lf\nMode=%lf\n", mean, median, mode);


}

void matrixMenu() {
    int ch,r,c;
    int A[10][10], B[10][10], C[10][10];

    printf("1.Add 2.Subtract 3.Transpose 4.Determinant\n");
    scanf("%d",&ch);

    printf("Enter rows cols: ");
    scanf("%d%d",&r,&c);

    printf("Enter Matrix A:\n");
    for(int i=0;i<r;i++)
        for(int j=0;j<c;j++)
            scanf("%d",&A[i][j]);

    if(ch==1 || ch==2){
        printf("Enter Matrix B:\n");
        for(int i=0;i<r;i++)
            for(int j=0;j<c;j++)
                scanf("%d",&B[i][j]);
    }

    if(ch==1){
        for(int i=0;i<r;i++)
            for(int j=0;j<c;j++)
                C[i][j]=A[i][j]+B[i][j];
    }
    else if(ch==2){
        for(int i=0;i<r;i++)
            for(int j=0;j<c;j++)
                C[i][j]=A[i][j]-B[i][j];
    }
    else if(ch==3){
        for(int i=0;i<r;i++)
            for(int j=0;j<c;j++)
                C[j][i]=A[i][j];
        r=c;
    }
    else if(ch==4){
        if(r != c){
            printf("Determinant only for square matrix!\n");
            return;
        }

        if(r == 2){
            int det = A[0][0]*A[1][1] - A[0][1]*A[1][0];
            printf("Determinant = %d\n", det);
        }
        else if(r == 3){
            int det =
                A[0][0]*(A[1][1]*A[2][2] - A[1][2]*A[2][1])
              - A[0][1]*(A[1][0]*A[2][2] - A[1][2]*A[2][0])
              + A[0][2]*(A[1][0]*A[2][1] - A[1][1]*A[2][0]);

            printf("Determinant = %d\n", det);
        }
        else{
            printf("Only 2x2 or 3x3 supported\n");
        }
        return;
    }

    printf("Result:\n");
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++)
            printf("%d ",C[i][j]);
        printf("\n");
    }
}
