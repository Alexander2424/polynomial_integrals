/*
 *Final Programming Project by ah760
 */

#include <stdio.h>
#include <math.h>
#define NMAX 10

/*
 *This struture is used to pass the values for the order (a), coefficients (coef[NMAX]) and
 *limits of integration (l1 and l2) from main to the functions and to avoid having to pass
 *each variable individually as a pointer from main to the functions. Using the coef[] array
 *also helps keep track of which number coefficient is where in the calculation.
 */

struct coeffs{
    int a, l1, l2;
    int coef[NMAX];
};

/*
 *Here there are four functions that perform different types of integration, they will be
 *selected via a menu. The correct_answer function calculates an accurate correct value
 *to use for comparison.
 */

void correct_answer(struct coeffs z);
void trapezoid(struct coeffs z);
void simpsons(struct coeffs z);
void algebraic(struct coeffs z);

int main() {
    struct coeffs z;
    /*
     *Variable a is the order of the polynomial, this program allows the user to enter a
     *polynomial of order between 1 and 3. The coefficients are stored in the coef[] array
     *contained in the structure
     */
    printf("This program will perform integration of various types.\n");
    printf("What order polynomial do you want to integrate?\n");
    scanf("%d", &z.a);
    if(z.a==1){
        printf("You will need %d coefficients for a %d order polynomial, what are they going to be?\n", z.a +1, z.a);
        scanf("%d %d", &z.coef[0], &z.coef[1]);
        
        printf("Your polynomial is y= %dx + %d\n", z.coef[0], z.coef[1]);
        
    } else if(z.a==2){
        printf("You will need %d coefficients for a %d order polynomial, what are they going to be?\n", z.a+1, z.a);
        scanf("%d %d %d", &z.coef[0], &z.coef[1], &z.coef[2]);
        
        printf("Your polynomial is y= %dx^2 + %dx + %d\n", z.coef[0], z.coef[1], z.coef[2]);
        
    }else if(z.a==3){
        printf("You will need %d coefficients for a %d order polynomial, what are they going to be?\n", z.a+1, z.a);
        scanf("%d %d %d %d", &z.coef[0], &z.coef[1], &z.coef[2], &z.coef[3]);
        
        printf("Your polynomial is y= %dx^3 + %dx^2 + %dx + %d\n", z.coef[0], z.coef[1], z.coef[2], z.coef[3]);
        
    }else if(z.a>3){
        printf("You must select a polynomial of an order of 3 or less!\n\n");
        return -1;
        
    }
    
    printf("What method would you like to choose to integrate your polynomial?\n"
           "\t 1. Use the trapezoidal rule\n"
           "\t 2. Use the Simpson's rule\n"
           "\t 3. Perform algebraic integration\n"
           "\t 0. Quit\n");
    
    int option;
    scanf("%d", &option);
    
    switch (option){
        case 0:
            printf("You have quit the program.\n");
            break;
            
        case 1:
            printf("What are your two integer limits of integration?\n");
            scanf("%d %d", &z.l1, &z.l2);
            trapezoid(z);
            correct_answer(z);
            break;
            
        case 2:
            printf("What are your two integer limits of integration?\n");
            scanf("%d %d", &z.l1, &z.l2);
            simpsons(z);
            correct_answer(z);
            break;
            
        case 3:
            algebraic(z);
            break;
    }
    
    return 0;
    
}

void trapezoid(struct coeffs z){
    double l1 = z.l1;
    double l2 = z.l2;
    double y[NMAX]={0}, I=0;
    /*
     *Using double to assign variable I to give a more precise result, using int can result
     *in inaccurate divisions. For this reason l1 and l2 are areassigned above as double
     *instead of int.
     */
    double x = (l2 - l1)/4;
    /*
     *Variable x is the width of the trapezium sections, each polynomial curve is split into
     *four equal width trapeziums. To integrate a higher order, the same pattern can be
     *followed where more coefficients and more 'else if' checks are needed.
     */
    if(z.a==1){
        for(int i=0; i<5; i++){
            y[i] = z.coef[0] * ((i*x)+l1) + z.coef[1];
            I = x*((y[0]+y[1])/2) +x*((y[1]+y[2])/2) +x*((y[2]+y[3])/2) +x*((y[3]+y[4])/2);
        }
        printf("The value of your integral using the trapezoid rule is %g\n", I);
        
    } else if(z.a==2){
        for(int i=0; i<5; i++){
            y[i] = z.coef[0] * pow(((i*x)+l1), 2) + z.coef[1] *((i*x)+l1) + z.coef[2];
            I = x*((y[0]+y[1])/2) +x*((y[1]+y[2])/2) +x*((y[2]+y[3])/2) +x*((y[3]+y[4])/2);
        }
        printf("%g\n", x);
        printf("The value of your integral using the trapezoid rule is %g\n", I);
        
    }else if(z.a==3){
        for(int i=0; i<5; i++){
            y[i] = z.coef[0]*pow(((i*x)+l1), 3) + z.coef[1] * pow(((i*x)+l1), 2) + z.coef[2] * ((i*x)+l1) + z.coef[3];
            I = x*((y[0]+y[1])/2) +x*((y[1]+y[2])/2) +x*((y[2]+y[3])/2) +x*((y[3]+y[4])/2);
        }
        printf("The value of your integral using the trapezoid rule is %g\n", I);
        
    }
}

void simpsons(struct coeffs z){
    double l1 = z.l1;
    double l2 = z.l2;
    double y[NMAX]={0}, I=0;
    /*
     *Using 7 values for y going from y[0] to y[6] for increased accuracy in the answer for
     *Simpsons rule. For Simpsons rule the max n in Y[n] must be even e.g. y[4], y[6],
     *y[8],... etc.
     */
    double x = (l2 - l1)/6;
    
    if(z.a==1){
        for(int i=0; i<7; i++){
            y[i] = z.coef[0] * ((i*x) + l1) + z.coef[1];
            I = (x/3)*(y[0] + 4*(y[1] + y[3] + y[5]) + 2*(y[2]+y[4]) + y[6]);
        }
        printf("The value of your integral using the Simpson's rule is %g\n", I);
        
    } else if(z.a==2){
        for(int i=0; i<7; i++){
            y[i] = z.coef[0] * pow(((i*x)+l1), 2) + z.coef[1] * ((i*x)+l1) + z.coef[2];
            I = (x/3)*(y[0] +4*(y[1]+y[3]+y[5]) + 2*(y[2]+y[4]) + y[6]);
        }
        printf("The value of your integral using the Simpson's rule is %g\n", I);
        
    }else if(z.a==3){
        for(int i=0; i<7; i++){
            y[i] = z.coef[0]*pow(((i*x)+l1), 3) + z.coef[1] * pow(((i*x)+l1), 2) + z.coef[2] * ((i*x)+l1) + z.coef[3];
            I = (x/3)*(y[0] +4*(y[1] + y[3] + y[5]) + 2*(y[2] + y[4]) + y[6]);
        }
        printf("The value of your integral using the Simpson's rule is %g\n", I);
        
    }
    
}

void algebraic(struct coeffs z){
    /*
     *Array b holds the powers of x, and array c holds the coefficients of x. The two arrays
     *are initialized to zero. A double type for the arrays is used because it avoids the
     *errors from using int type in division and it also avoids the unnecessary sig. figs.
     *that come from the float type, so the answer looks nicer and is still accurate.
     */
    double b[NMAX]={0}, c[NMAX]={0};
    if(z.a==1){
        for(int i=0; i<2; i++){
            b[i] = z.a+1 - i;
            c[i] = z.coef[i]/b[i];
        }
        printf("The algebraic solution to your polynmial is %gx^%g + %gx + constant\n", c[0], b[0], c[1]);
        
    }else if(z.a==2){
        for(int i=0; i<3; i++){
            b[i] = z.a+1 -i;
            c[i] = z.coef[i]/c[i];
        }
        printf("The algebraic solution to your polynmial is %gx^%g + %gx^%g + %gx + constant\n", c[0], b[0], c[1], b[1], c[2]);
        
    }else if(z.a==3){
        for(int i=0; i<4; i++){
            b[i] = z.a + 1 - i;
            c[i] = z.coef[i]/b[i];
        }
        printf("The algebraic solution to your polynmial is %gx^%g + %gx^%g + %gx^%g + %gx + constant\n", c[0], b[0], c[1], b[1], c[2], b[2], c[3]);
        
    }
    
}

void correct_answer(struct coeffs z){
    double l1 = z.l1;
    double l2 = z.l2;
    double b[NMAX]={0}, c[NMAX]={0}, I=0;
    if(z.a==1){
        for(int i=0; i<2; i++){
            b[i] = z.a+1 - i;
            c[i] = z.coef[i]/b[i];
            I = (c[0] * pow(l2, b[0]) + c[1] * l2) - (c[0] * pow(l1, b[0]) + c[1] * l1);
        }
        printf("For comparison with the method chosen, the correct answer is %g\n", I);
        
    }else if(z.a==2){
        for(int i=0; i<3; i++){
            b[i] = z.a + 1 - i;
            c[i] = z.coef[i]/b[i];
            I = (c[0] * pow(l2, b[0]) + c[1] * pow(l2, b[1]) + c[2]*l2) - (c[0] * pow(l1, b[0]) + c[1] * pow(l1, b[1]) + c[2]*l1);
        }
        printf("For comparison with the method chosen, the correct answer is %g\n", I);
        
    }else if(z.a==3){
        for(int i=0; i<4; i++){
            b[i] = z.a + 1 - i;
            c[i] = z.coef[i]/b[i];
            I = (c[0] * pow(l2, b[0]) + c[1] * pow(l2, b[1]) + c[2]*pow(l2, b[2]) + c[3]*l2) - (c[0] * pow(l1, b[0]) + c[1] * pow(l1, b[1]) + c[2]*pow(l1, b[2]) + c[3]*l1);
        }
        printf("For comparison with the method chosen, the correct answer is %g\n", I);
        
    }
    
}

/*
 RESULTS
 
 Have managed to successfully perform each integral type:
 
 This program will perform integration of various types.
 What order polynomial do you want to integrate?
 2
 You will need 3 coefficients for a 2 order polynomial, what are they going to be?
 3 5 7
 Your polynomial is y= 3x^2 + 5x + 7
 What method would you like to choose to integrate your polynomial?
 1. Use the trapezoidal rule
 2. Use the Simpson's rule
 3. Perform algebraic integration
 0. Quit
 1
 You have chosen the trapezoidal rule.
 What are your two integer limits of integration?
 2 9
 The value of your integral using the trapezoid rule is 973.219
 For comparison with the method chosen, the correct answer is 962.5
 Program ended with exit code: 0
 
 
 This program will perform integration of various types.
 What order polynomial do you want to integrate?
 3
 You will need 4 coefficients for a 3 order polynomial, what are they going to be?
 4 6 7 2
 Your polynomial is y= 4x^3 + 6x^2 + 7x + 2
 What method would you like to choose to integrate your polynomial?
 1. Use the trapezoidal rule
 2. Use the Simpson's rule
 3. Perform algebraic integration
 0. Quit
 2
 You have chosen Simpson's rule.
 What are your two integer limits of integration?
 3 10
 The value of your integral using the Simpson's rule is 12197.5
 For comparison with the method chosen, the correct answer is 12197.5
 Program ended with exit code: 0
 
 
 This program will perform integration of various types.
 What order polynomial do you want to integrate?
 1
 You will need 2 coefficients for a 1 order polynomial, what are they going to be?
 3 9
 Your polynomial is y= 3x + 9
 What method would you like to choose to integrate your polynomial?
 1. Use the trapezoidal rule
 2. Use the Simpson's rule
 3. Perform algebraic integration
 0. Quit
 3
 You have chosen algebraic integration.
 The algebraic solution to your polynmial is 1.5x^2 + 9x + constant
 Program ended with exit code: 0
 */
