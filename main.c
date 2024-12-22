#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_OFFER_COUNT 1000
#define MAX_OFFER_AMT_LEN 30  

int* get_min_am_counts(float* offers , int n_offers , float total_cost);
float calc_payment(float* offers , int n_offers , float total_cost);

float* input_offers(int* offer_count);

int main(void)
{
    int offer_count;
    float* offers = input_offers(&offer_count);

    float total_amt;
    char inp[MAX_OFFER_AMT_LEN];
    printf("Enter total amt: ");
    fgets(inp , MAX_OFFER_AMT_LEN , stdin);
    total_amt = atof(inp);

    for (int i=0 ; i<offer_count ; i++) {
        printf("Offer %i: %0.2f\n" , i , offers[i]);
    }
    printf("Total amt: %0.2f\n" , total_amt);

    printf("Must pay: %0.3f\n" , calc_payment(offers , offer_count , total_amt));
}


int* get_min_am_counts(float* offers , int n_offers , float total_cost)
{
    int* min_am_counts = malloc(sizeof(int) * n_offers);
    for (int i=0 ; i<n_offers ; i++)
    {
        float min_am_i = total_cost / offers[i];

        if (min_am_i > (int)min_am_i) { min_am_counts[i] = (int)min_am_i + 1; }
        else { min_am_counts[i] = (int)min_am_i; }
    }

    return min_am_counts;
}

float calc_payment(float* offers , int n_offers , float total_cost)
{
    int* min_am_counts = get_min_am_counts(offers , n_offers , total_cost);

    int am_count = n_offers;
    int stable = 0;

    while (stable != 1)
    {
        stable = 1;
        for (int i=0 ; i<n_offers ; i++)
        {
            if (min_am_counts[i] > am_count && min_am_counts[i] != -1) {
                am_count--;
                min_am_counts[i] = -1;
                stable = 0;
            }
        }
    }

    if (am_count == 0.0f) { return 0.0f; }
    return total_cost / am_count;
}


float* input_offers(int* offer_count)
{
    int count = 0;

    char inp[MAX_OFFER_AMT_LEN] = "1";

    float* offers = malloc(sizeof(float) * MAX_OFFER_COUNT);

    while (count < MAX_OFFER_COUNT)
    {
        printf("Enter next offer (n to exit): ");
        fgets(inp , MAX_OFFER_AMT_LEN , stdin);
        
        if (inp[0] == 'n') { break; }

        offers[count] = atof(inp);
        count++;
    }

    *offer_count = count;
    return offers;
}